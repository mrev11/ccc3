
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
#include <swap.h>
#include <btree.h>

//----------------------------------------------------------------------------
void __bt_swapin(PAGE *h)
{
    u_int32_t flags=h->flags;
    M_32_SWAP(flags);
    if( (flags&P_TYPE)==P_MEMO )
    {
        u_int32_t *memopg=(u_int32_t*)h;
        u_int32_t lower=memopg[2];
        M_32_SWAP(lower);

        for( u_int32_t i=0; i<lower; i++ )
        {
            P_32_SWAP(memopg+i);
        }
        return;
    }
    

    indx_t i, top;

    M_32_SWAP(h->pgno);
    M_32_SWAP(h->linkpg);
    M_32_SWAP(h->prevpg);
    M_32_SWAP(h->nextpg);
    M_32_SWAP(h->flags);
    M_16_SWAP(h->lower);
    M_16_SWAP(h->upper);

    top=NEXTINDEX(h);

    if( (h->flags&P_TYPE)==P_BINTERNAL )
    {
        for( i=0; i<top; i++ ) 
        {
            BINTERNAL *p;
            M_16_SWAP(h->linp[i]);
            p=GETBINTERNAL(h,i);
            M_32_SWAP( p->ksize );
            M_32_SWAP( p->pgno );
        }
    }

    else // if( ((h->flags&P_TYPE)==P_BLEAF) || ((h->flags&P_TYPE)==P_DATA) )
    {
        for( i=0; i<top; i++ ) 
        {
            BLEAF *p;
            M_16_SWAP( h->linp[i] );
            p=GETBLEAF(h,i);
            M_32_SWAP( p->ksize );
        }
    }
}

//----------------------------------------------------------------------------
void __bt_swapout(PAGE *h)
{
    u_int32_t flags=h->flags;
    if( (flags&P_TYPE)==P_MEMO )
    {
        u_int32_t *memopg=(u_int32_t*)h;
        u_int32_t lower=memopg[2];

        for( u_int32_t i=0; i<lower; i++ )
        {
            P_32_SWAP(memopg+i);
        }
        return;
    }


    indx_t i, top;
    top=NEXTINDEX(h);

    if( (h->flags&P_TYPE)==P_BINTERNAL )
    {
        for( i=0; i<top; i++ ) 
        {
            BINTERNAL *p=GETBINTERNAL(h,i); 
            M_32_SWAP( p->ksize );
            M_32_SWAP( p->pgno );
            M_16_SWAP( h->linp[i] );
        }
    }

    else // if( ((h->flags&P_TYPE)==P_BLEAF) || ((h->flags&P_TYPE)==P_DATA) )
    {
        for( i=0; i<top; i++ ) 
        {
            BLEAF *p=GETBLEAF(h,i); 
            M_32_SWAP( p->ksize );
            M_16_SWAP( h->linp[i] );
        }
    }
 
    M_32_SWAP(h->pgno);
    M_32_SWAP(h->linkpg);
    M_32_SWAP(h->prevpg);
    M_32_SWAP(h->nextpg);
    M_32_SWAP(h->flags);
    M_16_SWAP(h->lower);
    M_16_SWAP(h->upper);
}


//----------------------------------------------------------------------------

