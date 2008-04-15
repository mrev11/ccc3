
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
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <btree.h>

static int __bt_dleaf   (BTREE*, DBT*, PAGE*, indx_t);
static int __bt_pdelete (BTREE*, PAGE*);
static int __bt_relink  (BTREE*, PAGE*);


/*
 * __bt_delete
 *    Delete a specified key.
 *
 * Parameters:
 *      t:    tree
 *    key:    key to delete
 *
 * Returns:
 *    RET_ERROR, RET_SUCCESS and RET_SPECIAL if the key not found.
 */

int __bt_delete( BTREE *t,  DBT *key)
{
    EPG *e;
    PAGE *h;
    int  exact;

    mpool_count(t->bt_mp, "del0");
 
    // Find any matching record; __bt_search pins the page. 

    if( (e=__bt_search(t, key, &exact))==NULL )
    {
        return RET_ERROR;
    }

    if( !exact ) 
    {
        mpool_put(t->bt_mp, e->page, 0);
        return RET_SPECIAL;
    }

    h = e->page;

    if( __bt_dleaf(t, key, h, e->index) ) 
    {
        mpool_put(t->bt_mp, h, 0);
        return RET_ERROR;
    }

    if( NEXTINDEX(h)==0 ) 
    {
        if( __bt_pdelete(t, h) )
        {
            return RET_ERROR;
        }
    } 
    else
    {
        mpool_put(t->bt_mp, h, MPOOL_DIRTY);
    }

    mpool_count(t->bt_mp, "del1");
    return RET_SUCCESS;
}


/*
 * __bt_dleaf
 *    Delete a single record from a leaf page.
 *
 * Parameters
 *    t     :   tree
 *    key   :   referenced key
 *    h     :   page
 *    index :   index on page to delete
 *
 * Returns
 *    RET_SUCCESS, RET_ERROR.
 */

static int __bt_dleaf( BTREE *t, DBT *key,  PAGE *h, indx_t index)
{
    BLEAF *bl;
    indx_t cnt, *ip, offset;
    u_int32_t nbytes;
    void *to;
    char *from;

    to = bl = GETBLEAF(h, index);

    // Pack the remaining key items at the end of the page.
    nbytes = NBLEAF(bl);
    from = (char*)h + h->upper;
    memmove(from + nbytes, from, (char*)to - from);
    h->upper += nbytes;

    // Adjust the indices' offsets, shift the indices down. 
    offset = h->linp[index];
    for( cnt=index, ip=&h->linp[0]; cnt--; ++ip )
    {
        if( ip[0]<offset )
        {
            ip[0] += nbytes;
        }
    }
    for( cnt=NEXTINDEX(h)-index; --cnt; ++ip )
    {
        ip[0] = ip[1]<offset ? ip[1]+nbytes : ip[1];
    }
    h->lower -= sizeof(indx_t);

    return RET_SUCCESS;
}

 
/*
 * __bt_pdelete
 *    Delete a single page from the tree.
 *
 * Parameters:
 *    t:    tree
 *    h:    leaf page
 *
 * Returns:
 *    RET_SUCCESS, RET_ERROR.
 *
 * Side-effects:
 *    mpool_put's the page
 */

static int __bt_pdelete( BTREE *t, PAGE *h)
{
    BINTERNAL *bi;
    PAGE *pg;
    EPGNO *parent;
    indx_t cnt, index, *ip, offset;
    u_int32_t nksize;
    char *from;

    // Walk the parent page stack -- a LIFO stack of the pages that were
    // traversed when we searched for the page where the delete occurred.
    // Each stack entry is a page number and a page index offset.  The
    // offset is for the page traversed on the search.  We've just deleted
    // a page, so we have to delete the key from the parent page.
    //
    // If the delete from the parent page makes it empty, this process may
    // continue all the way up the tree.  We stop if we reach the root page
    // (which is never deleted, it's just not worth the effort) or if the
    // delete does not empty the page.

    while ((parent=BT_POP(t))!=NULL ) 
    {
        // Get the parent page. 
        if( (pg=(PAGE*)mpool_get(t->bt_mp, parent->pgno)) == NULL )
        {
            return (RET_ERROR);
        }

        index = parent->index;
        bi = GETBINTERNAL(pg, index);

        // Free the parent if it has only the one key and it's not the
        // root page. If it's the rootpage, turn it back into an empty
        // leaf page.

        if( NEXTINDEX(pg) == 1 ) 
        {
            if( pg->pgno == P_ROOT(t) ) 
            {
                pg->lower = BTDATAOFF;
                pg->upper = t->bt_psize;
                pg->flags = P_BLEAF;
            } 
            else 
            {
                if( __bt_relink(t, pg) || __bt_free(t, pg) )
                {
                    return (RET_ERROR);
                }
                continue;
            }
        } 
        else 
        {
            // Pack remaining key items at the end of the page. 
            nksize = NBINTERNAL(bi->ksize);
            from = (char*)pg + pg->upper;
            memmove(from + nksize, from, (char*)bi - from);
            pg->upper += nksize;

            // Adjust indices' offsets, shift the indices down. 
            offset = pg->linp[index];
            for( cnt=index, ip=&pg->linp[0]; cnt--; ++ip)
            {
                if( ip[0] < offset )
                {
                    ip[0] += nksize;
                }
            }
            for (cnt = NEXTINDEX(pg) - index; --cnt; ++ip)
            {
                ip[0] = ip[1]<offset ? ip[1]+nksize : ip[1];
            }
            pg->lower -= sizeof(indx_t);
        }

        mpool_put(t->bt_mp, pg, MPOOL_DIRTY);
        break;
    }

    // Free the leaf page, as long as it wasn't the root. 
    if( h->pgno == P_ROOT(t) ) 
    {
        mpool_put(t->bt_mp, h, MPOOL_DIRTY);
        return (RET_SUCCESS);
    }
    return __bt_relink(t, h) || __bt_free(t, h);
}

/*
 * __bt_relink
 *    Link around a deleted page.
 *
 * Parameters:
 *    t:    tree
 *    h:    page to be deleted
 */

static int __bt_relink( BTREE *t, PAGE *h)
{
    PAGE *pg;

    if( h->nextpg != P_INVALID ) 
    {
        if( (pg=(PAGE*)mpool_get(t->bt_mp, h->nextpg)) == NULL )
        {
            return (RET_ERROR);
        }
        pg->prevpg = h->prevpg;
        mpool_put(t->bt_mp, pg, MPOOL_DIRTY);
    }
    if( h->prevpg != P_INVALID ) 
    {
        if( (pg=(PAGE*)mpool_get(t->bt_mp, h->prevpg)) == NULL )
        {
            return (RET_ERROR);
        }
        pg->nextpg = h->nextpg;
        mpool_put(t->bt_mp, pg, MPOOL_DIRTY);
    }
    return 0;
}
