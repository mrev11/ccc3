
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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <btree.h>

static int __bt_seqadv (BTREE *, EPG *, int);
static int __bt_seqset (BTREE *, EPG *, DBT *, int, int*);
static int __bt_gteq   (BTREE *, DBT *, EPG *, int *);
 
// Sequential scan support. 
// The tree can be scanned sequentially, 
// starting from either end of the tree or from any specified key.  

//----------------------------------------------------------------------------
 
/*
 * __bt_seq 
 *    Btree sequential scan interface.
 *
 * Parameters:
 *    t     :  pointer to the BTREE structure
 *    key   :  key for positioning and return value
 *    flags :  R_FIRST, R_LAST, R_NEXT, R_PREV.
 *
 * Returns:
 *    RET_ERROR, RET_SUCCESS or RET_SPECIAL if there's no next key.
 */

int __bt_seq(BTREE *t, DBT *key, int flags)
{
    EPG e;
    int status;

    int lock_file=(flags&R_LOCKFILE);
    int lock_root=(flags&R_LOCKROOT);
    flags&=R_FLAGS;
 
    mpool_count(t->bt_mp, "seq-0");
    
    if( lock_file )
    {
        __bt_pagelock(t,0,0); //for reading
    }
    if( lock_root )
    {
        __bt_pagelock(t,P_ROOT(t),0); //for reading
    }
    
    // __bt_seq rekurziv a kurzor helyreallitasa miatt,
    // a lockot azonban nem szabad rekurzivan alkalmazni,
    // mert visszatereskor a kelletenel hamarabb elengedne.
 
    // If scan uninitialized as yet, or starting at a specific record, 
    // set the scan to a specific key.  Both __bt_seqset and __bt_seqadv pin
    // the page the cursor references if they're successful.    
    
    t->bt_exact=0;
 
    switch (flags) 
    {
        case R_NEXT:
        case R_PREV:
            status = __bt_seqadv(t, &e, flags);
            break;

        case R_FIRST:
        case R_LAST:
        case R_CURSOR:
            status = __bt_seqset(t, &e, key, flags, &t->bt_exact);
            break;

        default:
            errno = EINVAL;
            status = RET_ERROR; 
    }

 
    if( status==RET_SUCCESS ) 
    {
        DBT crskey;
        crskey=__bt_getkey(t,&e);
        __bt_setcur(t, e.page->pgno, e.index, &crskey);
        if( key )
        {
            *key=t->bt_cursor.key;
        }
        mpool_put(t->bt_mp, e.page, 0);
    }
    else
    {
        __bt_setcur(t,0,0,0);
    }

    if( lock_file )
    {
        __bt_pageunlock(t,0); 
    }
    if( lock_root )
    {
        __bt_pageunlock(t,P_ROOT(t)); 
    }
 
    mpool_count(t->bt_mp, "seq-1");
    return status;
}


//----------------------------------------------------------------------------
 
/*
 * __bt_seqset
 *    Set the sequential scan to a specific key.
 *
 * Parameters
 *    t     :   tree
 *    ep    :   storage for returned key
 *    key   :   key for initial scan position
 *    flags :   R_CURSOR, R_FIRST, R_LAST, R_NEXT, R_PREV
 *
 * Side effects:
 *    Pins the page the cursor references.
 *
 * Returns:
 *    RET_ERROR, RET_SUCCESS or RET_SPECIAL if there's no next key.
 */

static int __bt_seqset(BTREE *t, EPG *ep, DBT *key, int flags, int *exactp)
{
    PAGE *h;
    pgno_t pg;

    // Find the first, last or specific key in the tree
    
    switch (flags) 
    {
        case R_CURSOR: //Keyed scan. 

            // Find the first instance of the key or the smallest key
            // which is greater than or equal to the specified key.
   
            if( key->data==NULL || key->size==0 ) 
            {
                errno = EINVAL;
                return RET_ERROR;
            }
            
            return __bt_gteq(t, key, ep, exactp);

        case R_FIRST: 

            // Walk down the left-hand side of the tree. 

            for( pg=P_ROOT(t); ; ) 
            {
                if( (h=(PAGE*)mpool_get(t->bt_mp, pg))==NULL )
                {
                    return RET_ERROR;
                }

                // Check for an empty tree. 
                if( NEXTINDEX(h)==0 ) 
                {
                    mpool_put(t->bt_mp, h, 0);
                    return RET_SPECIAL;
                }

                if( h->flags & P_BLEAF )
                {
                    break;
                }
                pg=GETBINTERNAL(h,0)->pgno;
                mpool_put(t->bt_mp, h, 0);
            }
            ep->page = h;
            ep->index = 0;
            break;
            
        case R_LAST: 

            // Walk down the right-hand side of the tree. 

            for( pg=P_ROOT(t); ; ) 
            {
                if( (h=(PAGE*)mpool_get(t->bt_mp, pg))==NULL )
                {
                    return RET_ERROR;
                }

                // Check for an empty tree. 
                if( NEXTINDEX(h)==0 ) 
                {
                    mpool_put(t->bt_mp, h, 0);
                    return RET_SPECIAL;
                }

                if( h->flags & P_BLEAF )
                {
                    break;
                }
                pg = GETBINTERNAL(h, NEXTINDEX(h) - 1)->pgno;
                mpool_put(t->bt_mp, h, 0);
            }

            ep->page = h;
            ep->index = NEXTINDEX(h) - 1;
            break;
    }

    return RET_SUCCESS;
}


//----------------------------------------------------------------------------
 
/*
 * __bt_seqadv
 *    Advance the sequential scan.
 *
 * Parameters
 *    t     :  tree
 *    flags :  R_NEXT, R_PREV
 *
 * Returns:
 *    RET_ERROR, RET_SUCCESS or RET_SPECIAL if there's no next key.
 */

static int __bt_seqadv(BTREE *t, EPG *ep, int flags)
{
    CURSOR *c;
    PAGE *h;
    indx_t index=0;
    pgno_t pg;
    int exact;
    BLEAF *bl;

    // Get the page referenced by the cursor. 
    // mpool_get returns NULL, if the cursor not initialized.

    c = &t->bt_cursor;
    if( (h=(PAGE*)mpool_get(t->bt_mp, c->pg.pgno))==NULL )
    {
        return RET_ERROR;
    }
    index = c->pg.index;


    //---- reset cursor position begin -----------------
    
    if( !( (h->flags==P_BLEAF) &&
           (index<NEXTINDEX(h)) &&
           (bl=GETBLEAF(h,index),1) && 
           (c->key.size==bl->ksize) &&
           (0==memcmp(c->key.data,bl->bytes,c->key.size)) )  )
    {
        mpool_put(t->bt_mp,h,0); 

        if( RET_SUCCESS==__bt_seq(t,&t->bt_cursor.key,R_CURSOR) )
        {
            // There was a key greater than or equal to the original.
    
            if( (!t->bt_exact) && (flags==R_NEXT) )
            {
                flags=0; //ready    
            }
        }
        else if( (flags==R_PREV) && 
                 (RET_SUCCESS==__bt_seq(t,&t->bt_cursor.key,R_LAST)) ) 
        {
            // There was a key less than the original.
            flags=0; //ready    
        }
        else
        {
            return RET_SPECIAL; 
        }

        t->bt_exact=0;
 
        if( (h=(PAGE*)mpool_get(t->bt_mp, c->pg.pgno))==NULL )
        {
            return RET_ERROR;
        }
        index = c->pg.index;
    }

    //---- reset cursor position end -----------------
 

    if( flags==R_NEXT ) 
    {
        if( ++index>=NEXTINDEX(h) ) 
        {
            pg=h->nextpg;
            mpool_put(t->bt_mp, h, 0);
            if( pg==P_INVALID )
            {
                return RET_SPECIAL;
            }
            if( (h=(PAGE*)mpool_get(t->bt_mp, pg))==NULL )
            {
                return RET_ERROR;
            }
            index = 0;
        }
    }

    else if( flags==R_PREV )
    {
        if( index==0 ) 
        {
            pg = h->prevpg;
            mpool_put(t->bt_mp, h, 0);
            if( pg==P_INVALID )
            {
                return RET_SPECIAL;
            }
            if( (h=(PAGE*)mpool_get(t->bt_mp, pg))==NULL )
            {
                return RET_ERROR;
            }
            index = NEXTINDEX(h) - 1;
        } 
        else
        {
            --index;
        }
    }

    ep->page = h;
    ep->index = index;
    return RET_SUCCESS;
}

//----------------------------------------------------------------------------
 
/*
 * __bt_gteq 
 *    Find the first greater or equal entry.
 *
 * Parameters
 *    t      :  the tree
 *    key    :  the key
 *    erval  :  return EPG
 *    exactp :  pointer to exact match flag
 *
 * Returns:
 *    The first entry in the tree greater than or equal to key,
 *    or RET_SPECIAL if no such key exists.
 */

static int __bt_gteq(BTREE *t, DBT *key, EPG *erval, int *exactp)
{
    PAGE *h;
    EPG *ep, save;
    pgno_t pg;
 
    // Find any matching record, __bt_search pins the page.
    // Make sure it's a valid key (__bt_search may return an index 
    // just past the end of a page) and return it.

    if( (ep=__bt_search(t,key,exactp))==NULL )
    {
        return RET_SPECIAL;
    }

    if( *exactp ) 
    {
        *erval = *ep;
        return RET_SUCCESS;
    }

    // If at the end of a page, find the next entry. 

    if( ep->index>=NEXTINDEX(ep->page) ) 
    {
        h = ep->page;
        pg = h->nextpg;
        mpool_put(t->bt_mp, h, 0);

        if( pg==P_INVALID )
        {
            return RET_SPECIAL;
        }

        if( (h=(PAGE*)mpool_get(t->bt_mp, pg))==NULL )
        {
            return RET_ERROR;
        }
        ep->index = 0;
        ep->page = h;
    }

    *erval = *ep;
    return RET_SUCCESS;
}

//----------------------------------------------------------------------------
 
/*
 * __bt_getkey 
 *    Creates a DBT to the current key.
 *
 * Parameters
 *    t     :  the tree
 *    e     :  *page,index
 *
 * Returns
 *    Key value as a DBT.
 */

DBT __bt_getkey( BTREE *t, EPG *e)
{
    BLEAF *bl;
    DBT key;
    bl = GETBLEAF(e->page, e->index);
    key.size = bl->ksize;  
    key.data = bl->bytes; 
    return key;
}

//----------------------------------------------------------------------------
int __bt_getcur(BTREE *t, pgno_t *pgno, indx_t *index, DBT *key) //debug info
{
    if( pgno )
    {
        *pgno=t->bt_cursor.pg.pgno;
    }
    if( index )
    {
        *index=t->bt_cursor.pg.index;
    }
    if( key )
    {
        *key=t->bt_cursor.key;
    }
    return t->bt_cursor.pg.pgno;  // pgno, vagy 0 ha nincs pozicionalva
}

//----------------------------------------------------------------------------
void __bt_setcur(BTREE *t, pgno_t pgno, indx_t index, DBT *key)
{
    if( t->bt_cursor.key.data ) 
    {
        free(t->bt_cursor.key.data);
        t->bt_cursor.key.size = 0;
        t->bt_cursor.key.data = NULL;
    }

    // Update the cursor. 
    t->bt_cursor.pg.pgno = pgno;
    t->bt_cursor.pg.index = index;
    
    if( key )
    {
        t->bt_cursor.key.size = key->size;
        t->bt_cursor.key.data = malloc(key->size); 
        memmove(t->bt_cursor.key.data, key->data, key->size);
    }
}


//----------------------------------------------------------------------------

