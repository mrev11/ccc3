
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

static void valuesort_key(VALUE *v, int n);
static int valuecompare_key(const void *x, const void *y);

//------------------------------------------------------------------------
void _clp_asortkey(int argno)

// hasonlo az asort-hoz csak mas tipusu a block:
// nem osszehasonlito blockot kell megadni,
// hanem egy olyan blockot, ami a tombelembol eloallitja azt a kulcsot,
// amit mar egyszeruen ossze lehet hasonlitani a < operatorral

{
    CCC_PROLOG("asortkey",5);

    VALUE *arr=_para(1);    // first element of array to sort (a[1])
    unsigned start=1;       // start index
    unsigned count=0;       // count of elements to sort
    VALUE *blk=&NIL;        // key block
    int ascend=1;           // ascend/descend flag

    // hivasi formak:
    //  asortkey(a,f)
    //  asortkey(a,b,[f])
    //  asortkey(a,[s],[c],[b],[f])

    if( ISFLAG(2) )
    {
        ascend=_parl(2);
    }
    else if( ISBLOCK(2) )
    {
        blk=PARPTR(2);
        if( !ISNIL(3) )
        {
            ascend=_parl(3);
        }
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
            error_arg("asortkey",base,5);
        }
        ascend=ISNIL(5)?ascend:_parl(5);
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
        logical(ascend);
        push_symbol(blk);

        // valusort kozben
        // a key block van a stack tetejen
        // az ascend/descend flag van alatta
        // a stack nem valtozhat

        valuesort_key(arr+start-1,count);
    }

    _retv(base); //array
    CCC_EPILOG();
}

//------------------------------------------------------------------------
static void valuesort_key(VALUE *v, int n)
{
    qsort(v,n,sizeof(VALUE),valuecompare_key);
}

//------------------------------------------------------------------------
static int valuecompare_key(const void *x, const void *y)
{

    //TOP2=ascend/descend flag
    //TOP=kulcs eloallito blokk
    //stack valtozatlan marad

    VALUE *ascend=TOP2();
    VALUE *keyblk=TOP();

    int result=0;

    if( keyblk->type==TYPE_NIL  )
    {
        result=stdcmp((VALUE*)x,(VALUE*)y);
    }
    else
    {
        push_symbol(keyblk);
        push_symbol((VALUE*)x);
        _clp_eval(2);
        x=TOP();

        push_symbol(keyblk);
        push_symbol((VALUE*)y);
        _clp_eval(2);
        y=TOP();

        result=stdcmp((VALUE*)x,(VALUE*)y);
        POP2();
    }

    if( !ascend->data.flag  )
    {
        result=-result;
    }

    return result;
}

//------------------------------------------------------------------------

