
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
#include <stdlib.h>
#include <string.h>

#include <btree.h>

#define DEBUG


/*
 * __bt_put 
 *
 * Add a btree item to the tree.
 *
 * Parameters:
 *    t    :  pointer to the BTREE structure.
 *    key  :  key
 *    crs  :  if true, set cursor to the new position
 *
 * Returns:
 *    RET_ERROR, 
 *    RET_SUCCESS,
 *    RET_SPECIAL if the key is already in the tree.
 */

int __bt_put(BTREE *t, DBT*key, int crs)
{
    
    EPG *e;
    PAGE *h;
    indx_t index, nxtindex;
    pgno_t pg;
    u_int32_t nbytes;
    int  exact, status;
    char *dest;
    EPGNO newcrs;

    mpool_count(t->bt_mp, "put0");
 
    if( (e=__bt_search(t, key, &exact))==NULL )
    {
        #ifdef DEBUG
          fprintf(stderr,"PUTERR search\n");
          fflush(0);
        #endif
        return RET_ERROR;
    }

    h = e->page;
    index = e->index;
 
    // Duplicates not allowed.
    if( exact ) 
    {
        #ifdef DEBUG
          fprintf(stderr,"PUTERR duplicate\n");
          fflush(0);
        #endif

        mpool_put(t->bt_mp, h, 0);
        return RET_SPECIAL;
    }
 
    newcrs.pgno = e->page->pgno;
    newcrs.index = e->index;

    // If not enough room, or the user has put a ceiling on the number of
    // keys permitted in the page, split the page.  The split code will
    // insert the key and data and unpin the current page.  If inserting
    // into the offset array, shift the pointers up.

    nbytes = NBLEAFDBT(key->size);
    if( (u_int32_t)(h->upper-h->lower) < (nbytes+sizeof(indx_t)) ) 
    {
        if( (status=__bt_split(t,h,key,nbytes,index,&newcrs))!=RET_SUCCESS )
        {
            #ifdef DEBUG
              if( status )
              {
                  fprintf(stderr,"PUTERR split\n");
                  fflush(0);
              }
            #endif
            mpool_count(t->bt_mp,"put");
            return status;
        }
        
        #ifdef VERIFY_POSITION
          printf("SPLIT %d %d",newcrs.pgno,newcrs.index);
          if( ((e=__bt_search(t,key,&exact))==NULL) || !exact  )
          {
              return RET_ERROR;
          }
          newcrs.pgno = e->page->pgno;
          newcrs.index = e->index;
          printf(" --> %d %d\n",newcrs.pgno, newcrs.index);fflush(0);
          mpool_put(t->bt_mp, e->page, 0);
        #endif
    }
    else
    {
        if( index<(nxtindex=NEXTINDEX(h)) )
        {
            memmove(h->linp+index+1, 
                    h->linp+index, (nxtindex-index)*sizeof(indx_t));
        }
        h->lower+=sizeof(indx_t);
        h->linp[index]=h->upper-=nbytes;
        dest=(char*)h+h->upper;
        WR_BLEAF(dest,key);
        mpool_put(t->bt_mp, h, MPOOL_DIRTY);
    }
    
    if( crs )
    {
        __bt_setcur(t,newcrs.pgno,newcrs.index,key);
    }

    mpool_count(t->bt_mp, "put1");
    return RET_SUCCESS;
}


//----------------------------------------------------------------------------


