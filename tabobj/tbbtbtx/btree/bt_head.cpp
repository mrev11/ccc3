
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <btree.h>
#include <swap.h>

#ifdef WIN32
#include <io.h>
#endif
 
// __bt_header_read(t,1) noveli a lockcount-ot
// __bt_header_write/release csokkenti a lockcount-ot 
// ezeknek szigoruan parban kell allniuk

//----------------------------------------------------------------------------
static void swap_in(BTREE *t)
{
    unsigned int i;

    P_32_SWAP(&t->magic);   
    P_32_SWAP(&t->version);
    P_32_SWAP(&t->bt_psize);
    P_32_SWAP(&t->bt_nrecs);

    P_32_SWAP(&t->bt_free);
    P_32_SWAP(&t->bt_lastdatapage);
    P_32_SWAP(&t->bt_memo);
    P_32_SWAP(&t->bt_nords);
   
    for( i=0; (i<t->bt_nords) && (i<BT_MAXORDER); i++ ) 
    {
        ORDER *o=&t->bt_order[i];
        P_32_SWAP( &o->root );
        P_32_SWAP( &o->lastpage );
        P_32_SWAP( &o->flags );
    }
}

//----------------------------------------------------------------------------
static void swap_out(BTREE *t)
{
    unsigned int i;

    for( i=0; i<t->bt_nords; i++ ) 
    {
        ORDER *o=&t->bt_order[i];
        P_32_SWAP( &o->root );
        P_32_SWAP( &o->lastpage );
        P_32_SWAP( &o->flags );
    }
 
    P_32_SWAP(&t->magic);   
    P_32_SWAP(&t->version);
    P_32_SWAP(&t->bt_psize);
    P_32_SWAP(&t->bt_nrecs);

    P_32_SWAP(&t->bt_free);
    P_32_SWAP(&t->bt_lastdatapage);
    P_32_SWAP(&t->bt_memo);
    P_32_SWAP(&t->bt_nords);
}


//---------------------------------------------------------------------------
static int hread(BTREE*t)
{
    int fd=t->bt_fd;
    int disksize=(char*)&t->flags-(char*)t; // 544
    lseek(fd,0,SEEK_SET);
    int nbyte=read(fd,t,disksize);
    if( nbyte<256 )
    {
        return -1;
    }
    if( nbyte<disksize )
    {
        memset((char*)t+nbyte,0,disksize-nbyte);
    }
    if( F_ISSET(t,B_NEEDSWAP) ) 
    {
        swap_in(t);
    }
    int pagesize=t->bt_psize;
    if( pagesize<disksize )
    {
        memset((char*)t+pagesize,0,disksize-pagesize);
    }
    return 0;

    // megjegyzes
    // disksize: a btree struct tarolt resze (eleje)
    // pagesize: 256,512,...,8192 (default: 4096)
    // pagesize lehet kisebb vagy nagyobb mint disksize
}

//---------------------------------------------------------------------------
static int hwrite(BTREE*t)
{
    int fd=t->bt_fd;
    int pagesize=t->bt_psize;
    int disksize=(char*)&t->flags-(char*)t; // 544
    int nbyte=MIN(pagesize,disksize);

    if( F_ISSET(t,B_NEEDSWAP) ) 
    {
        swap_out(t);
    }
    lseek(fd,0,SEEK_SET);
    nbyte=write(fd,t,nbyte);
    if( F_ISSET(t,B_NEEDSWAP) ) 
    {
        swap_in(t);
    }
    return (nbyte==MIN(pagesize,disksize)) ? 0:-1;
}

//---------------------------------------------------------------------------
int __bt_header_read(BTREE *t, int lock)
{
    int rbyte;
    
    if( 0==t->bt_lockcount )
    {
        if( lock )
        {
            __bt_pagelock(t,0,1);
        }
        if( 0!=hread(t) )
        {
            __bt_error("__bt_header_read: i/o error");
        }
        t->bt_dirtyflag=0;
    }
    if( lock )
    {
        t->bt_lockcount++;
    }
    return RET_SUCCESS;
}
 

//---------------------------------------------------------------------------
int __bt_header_write(BTREE *t)
{
    int rbyte;

    if( 0>=t->bt_lockcount )
    {
        __bt_error("__bt_header_write: no lock");
    }

    if( 0==--t->bt_lockcount )
    {
        if( 0!=hwrite(t) )
        {
            __bt_error("__bt_header_write: i/o error");
        }
        __bt_pageunlock(t,0);
        t->bt_dirtyflag=0; 
    }
    else
    {
        t->bt_dirtyflag=1; 
    }

    return RET_SUCCESS;
}


//---------------------------------------------------------------------------
int __bt_header_sync(BTREE *t)
{
    int rbyte;

    if( 0>=t->bt_lockcount )
    {
        __bt_error("__bt_header_sync: no lock");
    }

    if( 0!=hwrite(t) )
    {
        __bt_error("__bt_header_sync: i/o error");
    }
    t->bt_dirtyflag=0; 
 
    return RET_SUCCESS;
}


//---------------------------------------------------------------------------
int __bt_header_release(BTREE *t)
{
    int rbyte;

    if( 0>=t->bt_lockcount )
    {
        __bt_error("__bt_header_release: no lock");
    }

    if( 0==--t->bt_lockcount )
    {
        if( t->bt_dirtyflag )
        {
            if( 0!=hwrite(t) )
            {
                __bt_error("__bt_header_write: i/o error");
            }
        }
        __bt_pageunlock(t,0);
        t->bt_dirtyflag=0; 
    }
    return RET_SUCCESS;
}
 

//---------------------------------------------------------------------------
int __bt_lastrec(BTREE *t)
{
    __bt_header_read(t,0);
    return t->bt_nrecs;
}

//---------------------------------------------------------------------------

