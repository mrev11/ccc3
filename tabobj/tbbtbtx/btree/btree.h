
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

#include <db.h>
#include <mpool.h>

#define  _BTREE_H_

#define  BTREEMAGIC    0x053162
#define  BTREEVERSION  1
 
#define  F_SET(p,f)     (p)->flags |= (f)
#define  F_CLR(p,f)     (p)->flags &= ~(f)
#define  F_ISSET(p,f)   ((p)->flags & (f))

// Page 0 of a btree file contains a copy of the meta-data.  This page is also
// used as an out-of-band page, i.e. page pointers that point to nowhere point
// to page 0.  Page 1 is the root of the btree.

#define  P_INVALID      0        // Invalid tree page number. 
#define  P_META         0        // Tree metadata page number. 

// Tree root page number.  
#define  P_ROOT(t)      t->bt_order[t->bt_curord].root        
#define  P_NAME(t)      t->bt_order[t->bt_curord].name
#define  P_LASTPAGE(t)  t->bt_order[t->bt_curord].lastpage
 
// There are three page layouts in the btree
// 1) btree internal pages (P_BINTERNAL)
// 2) btree leaf pages (P_BLEAF)
// 3) data pages (P_DATA)
 
#define  P_FREE        0x00      // page in the free list 
#define  P_BINTERNAL   0x01      // btree internal page 
#define  P_BLEAF       0x02      // leaf page 
#define  P_DATA        0x03      // data page
#define  P_MEMO        0x04      // memo page
#define  P_TYPE        0x07      // type mask
 
typedef struct _page 
{
  pgno_t    pgno;              // this page's page number 
  pgno_t    linkpg;            // link to the next page 
  pgno_t    prevpg;            // left (leaf) sibling 
  pgno_t    nextpg;            // right (leaf) sibling 
  u_int32_t flags;             // page type
  indx_t    lower;             // lower bound of free space on page 
  indx_t    upper;             // upper bound of free space on page 
  indx_t    linp[1];           // indx_t-aligned VAR. LENGTH DATA 
} PAGE;

// First and next index. 
#define  BTDATAOFF     (4*sizeof(pgno_t)+sizeof(u_int32_t)+2*sizeof(indx_t))
#define  NEXTINDEX(p)  (((p)->lower-BTDATAOFF)/sizeof(indx_t))

// For any pages there is an array of offsets (items in linp) into the
// rest of the page immediately following the page header.  Each offset is to
// an item which is unique to the type of page.  The h_lower offset is just
// past the last filled-in index.  The h_upper offset is the first item on the
// page.  Offsets are from the beginning of the page.

#define  LALIGN(n)  (((n) + sizeof(pgno_t)-1) & ~(sizeof(pgno_t)-1))

// For the btree internal pages, the item is a key.  BINTERNALs are {key,pgno}
// pairs, such that the key compares less than or equal to all of the records
// on that page.  For a tree without duplicate keys, an internal page with two
// consecutive keys, a and b, will have all records greater than or equal to a
// and less than b stored on the page associated with a.  

typedef struct _binternal 
{
  u_int32_t ksize;          // key size 
  pgno_t    pgno;           // page number stored on 
  char      bytes[1];       // key data 
} BINTERNAL;

// Get the page's BINTERNAL structure at index indx. 
#define  GETBINTERNAL(pg,indx)  ((BINTERNAL*)((char*)(pg)+(pg)->linp[indx]))

// Get the number of bytes in the entry. 
#define  NBINTERNAL(len)  LALIGN(sizeof(u_int32_t)+sizeof(pgno_t)+(len))

// Copy a BINTERNAL entry to the page. 
#define   WR_BINTERNAL(p, size, pgno) {            \
    *(u_int32_t *)p = size; p+=sizeof(u_int32_t);  \
    *(pgno_t *)   p = pgno; p+=sizeof(pgno_t);     \
}

// For the btree leaf pages, the item is a key.
typedef struct _bleaf 
{
  u_int32_t ksize;          // size of key 
  char      bytes[1];       // data
} BLEAF;

// Get the page's BLEAF structure at index indx.
#define  GETBLEAF(pg,indx)  ((BLEAF*)((char*)(pg)+(pg)->linp[indx]))

// Get the number of bytes in the entry. 
#define NBLEAF(p)  NBLEAFDBT((p)->ksize)

// Get the number of bytes in the user's key. 
#define NBLEAFDBT(ksize)  LALIGN(sizeof(u_int32_t)+(ksize))

// Copy a BLEAF entry to the page. 
#define  WR_BLEAF(p, key) {                                   \
    *(u_int32_t *)p = key->size;       p+=sizeof(u_int32_t);  \
    memmove(p, key->data, key->size);  p+=key->size;          \
}

// A record in the tree is either a pointer to a page and an index in the page
// or a page number and an index.  These structures are used as a cursor, stack
// entry and search returns as well as to pass records to other routines.
//
// One comment about searches.  Internal page searches must find the largest
// record less than key in the tree so that descents work.  Leaf page searches
// must find the smallest record greater than key so that the returned index
// is the record's correct position for insertion.

typedef struct _epgno 
{
  pgno_t  pgno;            // the page number 
  indx_t  index;           // the index on the page 
} EPGNO;

typedef struct _epg 
{
  PAGE    *page;           // the (pinned) page 
  indx_t  index;           // the index on the page 
} EPG;


typedef struct _cursor 
{
  EPGNO   pg;              // saved tree reference. 
  DBT     key;             // saved key, or key.data == NULL. 
} CURSOR;


typedef struct _order 
{
  pgno_t     root;         // number of root page
  pgno_t     lastpage;     // number of last inserted page
  u_int32_t  flags;        // flags of the order
  u_int32_t  reserved;     // reserved
  char       name[16];     // name of the order
} ORDER;


#define  BT_CLR(t)      (t->bt_sp=t->bt_stack)
#define  BT_POP(t)      (t->bt_sp==t->bt_stack?NULL:--t->bt_sp)
#define  BT_PUSH(t,p,i) (t->bt_sp->pgno=p, t->bt_sp->index=i, ++t->bt_sp)

#define BT_MAXORDER     16
 
typedef struct _btree 
{
  // permanent data 

  u_int32_t  magic;                    // magic number 
  u_int32_t  version;                  // version 
  u_int32_t  bt_psize;                 // page size 
  u_int32_t  bt_nrecs;                 // number of data records  

  pgno_t     bt_free;                  // next free page 
  pgno_t     bt_lastdatapage;          // last data page
  pgno_t     bt_memo;                  // next memo page
  u_int32_t  bt_nords;                 // number of orders
 
  ORDER      bt_order[BT_MAXORDER];    // array of orders
  
  // temporary data
 
  u_int32_t  flags;                    // type
  MPOOL     *bt_mp;                    // memory pool cookie 
  EPG        bt_cur;                   // current (pinned) page 
  CURSOR     bt_cursor;                // cursor 
  EPGNO      bt_stack[128];            // stack of parent pages (50)
  EPGNO     *bt_sp;                    // current stack pointer 
  int        bt_fd;                    // tree file descriptor 
  int        bt_lorder;                // byte order 
  int      (*bt_cmp)(DBT*, DBT*);      // key comparison function 
  int        bt_curord;                // selected order
  int        bt_exact;                 // last result of __bt_seq
  int        bt_lockcount;             // lockcount of header page
  int        bt_dirtyflag;             // dirty flag of header page 
} BTREE;

#define  B_NEEDSWAP    0x00008   // if byte order requires swapping 

#include <extern.h>

