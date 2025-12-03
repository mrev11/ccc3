
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

    if( ISBLOCK(2) || ISFLAG(2) )
    {
        blk=PARPTR(2);
    }    
    else
    {
        start=ISNIL(2)?start:_parnu(2);
        count=ISNIL(3)?count:_parnu(3);
        if( ISNIL(4) || ISFLAG(4) || ISBLOCK(4) )
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
        // valusort kozben 
        // a compare block van a stack tetejen TOP()
        // az lkx(lock index) van alatta       TOP2()
        // a stack nem valtozhat

        int lkx=mark_lock(base);
        number(lkx);
        push_symbol(blk);
        valuesort_cmp(arr+start-1,count);
        mark_unlock(lkx);
    }

    _retv(base); //array   
    CCC_EPILOG();
}

//------------------------------------------------------------------------
static void valuesort_cmp(VALUE *v, int n)
{
    qsort(v,n,sizeof(VALUE),valuecompare_cmp);
}

//------------------------------------------------------------------------
static int valuecompare_cmp(const void *x, const void *y)
{
    // Az osszehasonlitast ket iranyban is el kell vegezni,
    // hogy detektalhato legyen az egyenlo eset. A Clipper
    // osszehasonlito operatorok stringeken ugy mukodnek, 
    // hogy eloszor a baloldalt csonkitjak a jobboldal hosszara,
    // es az igy csonkitott baloldalt vetik ossze a jobboldallal.
    // Emiatt csak a < es >= operatorok mukodnek a vart modon.
    // A >, <=, != operatorok furcsa eredmenyt adnak, amikor
    // a balodal egyezik a jobboldallal a jobboldal hosszaban.
    // Celszeru a compare blokkban a <-t vagy >=-t hasznalni.

    int lkx=D2INT(TOP2()->data.number);
    mark_unlock(lkx);

    int result=0;

    if( TOP()->type==TYPE_NIL )
    {
        result=stdcmp((VALUE*)x,(VALUE*)y);
    }
    else if( TOP()->type==TYPE_FLAG )
    {
        result=TOP()->data.flag ? stdcmp((VALUE*)x,(VALUE*)y) : stdcmp((VALUE*)y,(VALUE*)x);
    }
    else
    {
        DUP();
        push_symbol((VALUE*)x);
        push_symbol((VALUE*)y);
        _clp_eval(3);

        if( TOP()->type==TYPE_FLAG )
        {
            int f1=flag() ;//egyik irany
            DUP();
            push_symbol((VALUE*)y);
            push_symbol((VALUE*)x);
            _clp_eval(3);
            int f2=flag(); //masik irany
            result=(f1==f2)?0:(f1?-1:1); 
        }
        else if( TOP()->type==TYPE_NUMBER )
        {
            result=(int)TOP()->data.number;
            pop();
        }
        else
        {
            error_gen(CHRLIT("wrong return type"),"compare block of sorting",TOP(),1);
            exit(1);
        }
    }

    mark_lock(lkx);
    return result;
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



