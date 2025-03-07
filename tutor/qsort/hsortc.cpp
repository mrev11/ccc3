
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

#define LEFT(x)     (2*(x)+1)
#define RIGHT(x)    (2*(x)+2)
#define PARENT(x)   ((x-1)/2)


//----------------------------------------------------------------------------------------
static void hsort(VALUE *arr, int p, int r, VALUE* blk) 
{
    int count=r-p+1;
    int start=count/2;
    int final=count;
    int root, child;
    
    while( final>1 )
    {
        if( start>0 )
        {
            --start;
        }
        else
        {
            --final;
            swap(arr+final+p-1,arr+p-1);
        }

        root=start;
        while( LEFT(root)<final )
        {
            child=LEFT(root);
            if( child+1<final && 0>compare(arr+child+p-1,arr+child+p,blk) )
            {
                ++child;
            }
            
            if( 0>compare(arr+root+p-1,arr+child+p-1,blk) )
            {
                swap(arr+root+p-1,arr+child+p-1);
                root=child;
            }
            else
            {
                break;
            }
        }
    }
}

//----------------------------------------------------------------------------------------
void _clp_hsortc(int argno)
{
    printf("%-16s","hsortc");fflush(0);

    CCC_PROLOG("hsort",4);

    VALUE *arr=_para(1);        // first element of the array to sort (&a[1])
    unsigned len=_paralen(1);   // length of the array
    unsigned start=1;           // start index
    unsigned count=len;         // count of elements to sort
    VALUE *blk=&NIL;            // compare block

    // hivasi formak:
    //  asort(a,b)
    //  asort(a,[s],[c],[b])

    if( ISBLOCK(2) || ISFLAG(2)  )
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
        hsort(arr,start,start+count-1,blk);
    }


    stack=base+1;
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------

