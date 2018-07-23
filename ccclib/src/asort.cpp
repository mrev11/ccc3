
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <cccapi.h>

static void valuesort_cmp(VALUE *v, int n);
static int valuecompare_cmp(const void *x, const void *y);

//------------------------------------------------------------------------
void _clp_asort(int argno) // asort(arr,[st],[cn],[blk])
{
    CCC_PROLOG("asort",4);

    VALUE *arr=_para(1);    // first element of array to sort (a[1])
    unsigned start=1;       // start index
    unsigned count=0;       // count of elements to sort
    VALUE *blk=&NIL;        // compare block

    // hivasi formak:
    //  asort(a,b)
    //  asort(a,[s],[c],[b])

    if( ISBLOCK(2) )
    {
        blk=PARPTR(2);
    }    
    else
    {
        start=ISNIL(2)?start:_parnu(2);
        count=ISNIL(3)?count:_parnu(3);
        if( ISNIL(4) )
        {
            blk=PARPTR(4);
        }
        else if( ISBLOCK(4) )
        {
            blk=PARPTR(4);
        }
        else
        {
            error_arg("asort",base,4);
        }
    }

    unsigned len=_paralen(1);
    start=max(start,1);
    start=min(start,len);
    if( count==0 )
    {
        count=len;
    }
    count=min(count,len-start+1);

    if( count>1  )
    {
        push_symbol(blk);

        // valusort kozben 
        // a compare block van a stack tetejen
        // a stack nem valtozhat

        valuesort_cmp(arr+start-1,count);
    }

    _retv(base); //array   
    CCC_EPILOG();
}

//------------------------------------------------------------------------
static void valuesort_cmp(VALUE *v, int n)
{
#if ! defined MULTITHREAD

    SIGNAL_LOCK();
    qsort(v,n,sizeof(VALUE),valuecompare_cmp);
    SIGNAL_UNLOCK();

#else
    if( thread_data::tdata_count==1 )
    {
        SIGNAL_LOCK();
        qsort(v,n,sizeof(VALUE),valuecompare_cmp);
        SIGNAL_UNLOCK();
    }
    else
    {
        SIGNAL_LOCK();
        thread_data_ptr->lock();
        qsort(v,n,sizeof(VALUE),valuecompare_cmp);
        thread_data_ptr->unlock();
        SIGNAL_UNLOCK();
    }

#endif  //MULTITHREAD
}

//------------------------------------------------------------------------
static int valuecompare_cmp(const void *x, const void *y)
{
#ifdef MULTITHREAD
    //Mikozben qsort meghivja az osszehasonlitast,
    //engedni kell a szemetgyujtest, maskulonben deadlock keletkezik,
    //ha az osszehasonlito bokkban objektumok is keszulnek.
    if( thread_data::tdata_count>1 )    
    {
        thread_data_ptr->unlock();
    }
#endif    

    SIGNAL_UNLOCK();
    
    //TOP=osszehasonlito block
    //stack valtozatlan marad

    // Az osszehasonlitast ket iranyban is el kell vegezni,
    // hogy detektalhato legyen az egyenlo eset. A Clipper
    // osszehasonlito operatorok stringeken ugy mukodnek, 
    // hogy eloszor a baloldalt csonkitjak a jobboldal hosszara,
    // es az igy csonkitott baloldalt vetik ossze a jobboldallal.
    // Emiatt csak a < es >= operatotok mukodnek a vart modon.
    // A >, <=, != operatorok furcsa eredmenyt adnak, amikor
    // a balodal egyezik a jobboldallal a jobboldal hosszaban.
    // Celszeru a compare blokkban a <-t vagy >=-t hasznalni.


    //egyik irany
    if( TOP()->type==TYPE_BLOCK )
    {
        DUP();
    }
    else
    {
        _clp__asort_ascendblock(0);
    }
    push_symbol((VALUE*)x);
    push_symbol((VALUE*)y);
    _clp_eval(3);
    int f1=flag();

    //masik irany
    if( TOP()->type==TYPE_BLOCK )
    {
        DUP();
    }
    else
    {
        _clp__asort_ascendblock(0);
    }
    push_symbol((VALUE*)y);
    push_symbol((VALUE*)x);
    _clp_eval(3);
    int f2=flag();

    SIGNAL_LOCK();

#ifdef MULTITHREAD
    if( thread_data::tdata_count>1 )    
    {
        thread_data_ptr->lock();
    }
#endif    

    return (f1==f2)?0:(f1?-1:1);
}

//------------------------------------------------------------------------

#ifdef NOTDEFINED

function main()
    test("aaa","a")
    
    
function test(a,b)
    ?  a> b, a, "> ", b, "  "
    ?? b> a, b, "> ", a, "vigyazz"

    ?  a< b, a, "< ", b, "  "
    ?? b< a, b, "< ", a, "  "

    ?  a>=b, a, ">=", b, "  "
    ?? b>=a, b, ">=", a, "  "

    ?  a<=b, a, "<=", b, "  "
    ?? b<=a, b, "<=", a, "vigyazz"


    ?  a!=b, a, "!=", b, "  "
    ?? b!=a, b, "!=", a, "vigyazz"

    ?


// eredmeny
//
// .F. aaa >  a   .F. a >  aaa vigyazz
// .F. aaa <  a   .T. a <  aaa   
// .T. aaa >= a   .F. a >= aaa   
// .T. aaa <= a   .T. a <= aaa vigyazz
// .F. aaa != a   .T. a != aaa vigyazz
//
// Tehat:
// Nem string argumentumokra mindegyik osszehasonlito operator "jo".
// Fix hosszu stringekre mindegyik osszehasonlito operator "jo".
// Olyan esetekben, amnikor a baloldal a jobboldal hosszabbitasa (ax>b)
// azonban a >, <=, != operatorok "furcsan" mukodnek.
// A furcsasag nem a CCC hibaja, hanem kompatibilitas miatt pontosan
// reprodukalni kellett a Clipper mukodeset. Ugyanezert nem is lehet
// most utolag kijavitani.
//
//  ax <= a   -> .t., mert a baloldal csonkitodik 'a'-ra
//  a  <= aa  -> .t., mert a jobboldal hosszabb
//  ax <= aa  -> .f., mert 'x' nagyobb, mint 'a'
//
// Azt kapjuk, hogy ez a relacio nem tranzitiv, tehat nem lehet rendezes.
// Ha pedig nem rendezes, akkor a qsort mukodese bizonytalan az olyan
// kodblokkokkal, amik a > es <= operatorral hasonlitanak ossze stringeket.
// Tehat (legalabb stringeknel) a < es >= operatorokra kell szoritkozni!

#endif



