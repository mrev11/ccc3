
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

#include <sys/types.h>
#include <stdio.h>

#include <btree.h>

//#define DEBUG
#ifdef  DEBUG
    #define PRINTF printf
#else
    #define PRINTF(...)
#endif

//----------------------------------------------------------------------------
int __bt_free(BTREE *t, PAGE *h)  //Put a page on the freelist.
{
    __bt_header_read(t,1);

    h->flags      = P_FREE;
    h->prevpg     = P_INVALID;
    h->nextpg     = P_LASTFREE(t);
    P_LASTFREE(t) = h->pgno;

    PRINTF("\n>>>> __BT_FREE %4x ->%4x               [%s]", P_LASTFREE(t), h->nextpg, P_NAME(t)); fflush(0);

    __bt_header_write(t);

    return mpool_put(t->bt_mp, h, MPOOL_DIRTY);
}

//----------------------------------------------------------------------------
PAGE *__bt_new0(BTREE *t, pgno_t *npg) //New nonindex page.
{
    PAGE *h;

    __bt_header_read(t,1);

    if( (h=(PAGE*)mpool_new(t->bt_mp, npg))==NULL )
    {
        __bt_error("__bt_new: mpool_new failed");
    }
    PRINTF("\n>>>> __BT_NEW0 brand new page %4x",*npg); fflush(0);

    __bt_header_write(t);
    return h;
}

//----------------------------------------------------------------------------
PAGE *__bt_new(BTREE *t, pgno_t *npg) //New nonindex page, prefer freelist.
{
    //_clp_callstack(0);pop();

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
        PRINTF("\n>>>> __BT_NEW  from global free %4x",*npg); fflush(0);
        //printf("o");fflush(0);
    }
    else
    {
        if( (h=(PAGE*)mpool_new(t->bt_mp, npg))==NULL )
        {
            __bt_error("__bt_new: mpool_new failed");
        }
        PRINTF("\n>>>> __BT_NEW  brand new page %4x",*npg); fflush(0);
        //printf("O");fflush(0);
    }

    __bt_header_write(t);
    return h;
}

//----------------------------------------------------------------------------
PAGE *__bt_newx(BTREE *t, pgno_t *npg) //New index page, prefer freelist.
{
    PAGE *h;

    __bt_header_read(t,1);

    if( P_LASTFREE(t) )
    {
        if( (h=(PAGE*)mpool_get(t->bt_mp,P_LASTFREE(t)))==NULL )
        {
            __bt_error("__bt_newx: invalid index-free list");
        }
        *npg = P_LASTFREE(t);
        P_LASTFREE(t) = h->nextpg;
        PRINTF("\n>>>> __BT_NEWX from index-free %4x      [%s]",*npg, P_NAME(t));  fflush(0);
        //printf(".");fflush(0);
    }
    else if( t->bt_free!=P_INVALID  )
    {
        if( (h=(PAGE*)mpool_get(t->bt_mp,t->bt_free))==NULL )
        {
            __bt_error("__bt_newx: invalid global-free list");
        }
        *npg = t->bt_free;
        t->bt_free = h->linkpg;
        h->linkpg=P_LASTPAGE(t);
        P_LASTPAGE(t) = *npg;
        PRINTF("\n>>>> __BT_NEWX from global-free %4x     [%s]",*npg, P_NAME(t)); fflush(0);
        //printf("x");fflush(0);
    }
    else
    {
        if( (h=(PAGE*)mpool_new(t->bt_mp, npg))==NULL )
        {
            __bt_error("__bt_new: mpool_new failed");
        }
        h->linkpg=P_LASTPAGE(t);
        P_LASTPAGE(t) = *npg;
        PRINTF("\n>>>> __BT_NEWX brand new page %4x       [%s]",*npg, P_NAME(t)); fflush(0);
        //printf("X");fflush(0);
    }

    __bt_header_write(t);
    return h;
}

//----------------------------------------------------------------------------

