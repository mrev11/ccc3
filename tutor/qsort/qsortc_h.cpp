
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

#include <math.h>
#include <cccapi.h>
#include <qsort.ch>
#include <qsort.h>

#define PERCENT(x) (int)(100.0*(x)/(r-p+1))

//----------------------------------------------------------------------------------------
void prnstat(int p, int q, int r)
{
    printf("\n");
    printf( "%8d:  %8d%% %8d%%",
             r-p+1, PERCENT(q-p+1), PERCENT(r-q) );
}


//----------------------------------------------------------------------------------------
static int qsplit( VALUE *arr, int p, int r, VALUE *blk )
{
    int i=p-1; // 1 based
    int j=r+1; // 1 based

    VALUE *pivot=push_pivot(arr,p,r-1,blk);

    while( 1 )
    {
        while( 0>compare(arr+(++i-1),pivot,blk) );
        while( 0<compare(arr+(--j-1),pivot,blk) );

        if( i>=j )
        {
            break;
        }
        swap(arr+i-1,arr+j-1);
    }

    POP(); //pivot
    //prnstat(p,j,r);
    return j;
}


//----------------------------------------------------------------------------------------
static void qsort(VALUE *arr, int p, int r, VALUE* blk) // tail recursion
{
    while( p+ISORT_TRESHOLD<r )
    {
        int q=qsplit(arr,p,r,blk);

        // kisebbik reszre rekurzio
        // nagyobbik reszre ciklus

        if( q-p<r-q )
        {
            qsort(arr,p,q,blk);
            p=q+1;
        }
        else
        {
            qsort(arr,q+1,r,blk);
            r=q;
        }
    }

    if( p<r )
    {
        isort(arr,p,r,blk);
    }
}

//----------------------------------------------------------------------------------------
void _clp_qsortc_h(int argno)
{
    printf("%-16s","qsortc_h");fflush(0);

    CCC_PROLOG("qsort",4);

    VALUE *arr=_para(1);        // first element of the array to sort (&a[1])
    unsigned len=_paralen(1);   // length of the array
    unsigned start=1;           // start index
    unsigned count=len;         // count of elements to sort
    VALUE *blk=&NIL;            // compare block

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

    if( count>1  )
    {
        qsort(arr,start,start+count-1,blk);
    }


    stack=base+1;
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------

