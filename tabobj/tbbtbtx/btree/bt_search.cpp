
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

/*
 * __bt_search --
 *    Search a btree for a key.
 *
 * Parameters:
 *    t      :  tree to search
 *    key    :  key to find
 *    exactp :  pointer to exact match flag
 *
 * Returns:
 *    The EPG for matching record, if any, or the EPG for the location
 *    of the key, if it were inserted into the tree, is entered into
 *    the bt_cur field of the tree.  A pointer to the field is returned.
 */

EPG * __bt_search(BTREE *t, DBT *key, int *exactp)
{
    PAGE *h;
    indx_t base, index, lim;
    pgno_t pg;
    int cmp;
    
    BT_CLR(t);

    for( pg=P_ROOT(t) ;; ) 
    {

        if ((h=(PAGE*)mpool_get(t->bt_mp, pg))==NULL )
        {
            return NULL;
        }

        // Do a binary search on the current page. 

        t->bt_cur.page = h;
        for( base=0, lim=NEXTINDEX(h); lim; lim>>=1 ) 
        {
            t->bt_cur.index = index = base + (lim >> 1);

            if ((cmp = __bt_cmp(t, key, &t->bt_cur)) == 0) 
            {
                if (h->flags & P_BLEAF) 
                {
                    *exactp = 1;
                    return &t->bt_cur;
                }
                goto next;
            }
 
            if (cmp > 0) 
            {
                base = index + 1;
                --lim;
            }
        }

 
        // If it's a leaf page, we're done. 
        if( h->flags & P_BLEAF ) 
        {
            *exactp = 0;
            t->bt_cur.index = base;
            return &t->bt_cur;
        }

        // No match found.  Base is the smallest index greater than
        // key and may be zero or a last + 1 index.  If it's non-zero,
        // decrement by one, and record the internal page which should
        // be a parent page for the key.  If a split later occurs, the
        // inserted page will be to the right of the saved page.

        index = base ? base - 1 : base;

next:   BT_PUSH(t, h->pgno, index);
        pg = GETBINTERNAL(h, index)->pgno;
        mpool_put(t->bt_mp, h, 0);
    }
}

