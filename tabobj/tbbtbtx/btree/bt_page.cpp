
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

#include <signal.h>
#include <sys/types.h>
#include <stdio.h>

#include <btree.h>

//----------------------------------------------------------------------------
int __bt_free(BTREE *t, PAGE *h)  //Put a page on the freelist. 
{
    __bt_header_read(t,1);

    h->flags   = P_FREE;
    h->prevpg  = P_INVALID;
    h->nextpg  = P_INVALID; 
    h->linkpg  = t->bt_free;
    t->bt_free = h->pgno;

    __bt_header_write(t);

    return mpool_put(t->bt_mp, h, MPOOL_DIRTY);
}

//----------------------------------------------------------------------------
PAGE *__bt_new0(BTREE *t, pgno_t *npg, pgno_t *lpg) //New page.
{
    PAGE *h;

    __bt_header_read(t,1);
 
    if( (h=(PAGE*)mpool_new(t->bt_mp, npg))==NULL )
    {
        __bt_error("__bt_new: mpool_new failed");
    }

    if( lpg )
    {
        h->linkpg=*lpg; 
        *lpg=*npg;
    }

    __bt_header_write(t);
    return h;
}
 
//----------------------------------------------------------------------------
PAGE *__bt_new(BTREE *t, pgno_t *npg, pgno_t *lpg) //New page, prefer freelist. 
{
    PAGE *h;

    __bt_header_read(t,1);
 
    if( t->bt_free!=P_INVALID  ) 
    {
        if( (h=(PAGE*)mpool_get(t->bt_mp,t->bt_free))==NULL )
        {
            __bt_error("__bt_new: invalid free list");
        }
        *npg = t->bt_free;
        t->bt_free = h->linkpg;
        //printf("from free %d\n",*npg);
    }
    else
    {
        if( (h=(PAGE*)mpool_new(t->bt_mp, npg))==NULL )
        {
            __bt_error("__bt_new: mpool_new failed");
        }
        //printf("brand new %d\n",*npg);
    }

    if( lpg )
    {
        h->linkpg=*lpg; 
        *lpg=*npg;
    }

    __bt_header_write(t);
    return h;
}

//----------------------------------------------------------------------------

