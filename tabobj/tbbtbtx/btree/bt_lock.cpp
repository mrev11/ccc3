
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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <btree.h>
#include <flock.h>


//----------------------------------------------------------------------------
void __bt_pagelock(BTREE *t, pgno_t pgno, int type)
{
    //page lockolasa irasra     __bt_pagelock(t,pgno,1);
    //page lockolasa olvasasra  __bt_pagelock(t,pgno,0);

    int fd=t->bt_fd;
    unsigned low=2*pgno;
    unsigned high=LK_OFFSET_PAGE;
    unsigned length=1;
    
    _ccc_lock  ( fd, low+1 , high, 1, CCCLK_WAIT+CCCLK_WRITE);  
    _ccc_lock  ( fd, low   , high, 1, CCCLK_WAIT+(type?CCCLK_WRITE:CCCLK_READ));  
    _ccc_unlock( fd, low+1 , high, 1 );  
}

//----------------------------------------------------------------------------
void __bt_pageunlock(BTREE *t, pgno_t pgno)
{
    int fd=t->bt_fd;
    unsigned low=2*pgno;
    unsigned high=LK_OFFSET_PAGE;
    unsigned length=1;
    
    _ccc_unlock( fd, low   , high, 1 );  
}

//----------------------------------------------------------------------------

