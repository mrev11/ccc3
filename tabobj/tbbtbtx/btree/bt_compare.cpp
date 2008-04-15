
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
#include <string.h>

#include <btree.h>

 
/*
 * __BT_CMP -- Compare a key to a given record.
 *
 * Parameters:
 *    t:    tree
 *    k1:    DBT pointer of first arg to comparison
 *    e:    pointer to EPG for comparison
 *
 * Returns:
 *    < 0 if k1 is < record
 *    = 0 if k1 is = record
 *    > 0 if k1 is > record
 */
int __bt_cmp( BTREE *t, DBT *k1,  EPG *e)
{
    BINTERNAL *bi;
    BLEAF *bl;
    DBT k2;
    PAGE *h;

    /*
     * The left-most key on internal pages, at any level of the tree, is
     * guaranteed by the following code to be less than any user key.
     * This saves us from having to update the leftmost key on an internal
     * page when the user inserts a new key in the tree smaller than
     * anything we've yet seen.
     */
    h = e->page;
    if (e->index == 0 && h->prevpg == P_INVALID && !(h->flags & P_BLEAF))
        return (1);

    if (h->flags & P_BLEAF) 
    {
        bl = GETBLEAF(h, e->index);
        k2.data = bl->bytes;
        k2.size = bl->ksize;
    } 
    else 
    {
        bi = GETBINTERNAL(h, e->index);
        k2.data = bi->bytes;
        k2.size = bi->ksize;
    }

    return ((*t->bt_cmp)(k1, &k2));
}


/*
 * __BT_DEFCMP -- Default comparison routine.
 *
 * Parameters:
 *    a:    DBT #1
 *    b:     DBT #2
 *
 * Returns:
 *    < 0 if a is < b
 *    = 0 if a is = b
 *    > 0 if a is > b
 */
int __bt_defcmp(DBT *a, DBT *b)
{
    size_t len;
    unsigned char *p1, *p2;

    len=a->size;
    if( b->size<len )
    {
        len=b->size;
    }

    for( p1=(unsigned char*)(a->data),p2=(unsigned char*)(b->data); len--; ++p1,++p2 )
    {
        if( *p1!=*p2 )
        {
            return (int)*p1-(int)*p2;
        }
    }
    return ((int)a->size - (int)b->size);
}


