
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

#ifdef _UNIX_
//----------------------------------------------------------------------------
void __bt_pagelock(BTREE *t, pgno_t pgno, int type)
{
    //page lockolasa irasra     __bt_pagelock(t,pgno,1);
    //page lockolasa olvasasra  __bt_pagelock(t,pgno,0);
 
    struct flock fl;

    fl.l_whence = SEEK_SET;
    fl.l_start  = ((off_t)pgno)*t->bt_psize;
    fl.l_len    = 1;
    fl.l_type   = F_WRLCK;
    fcntl(t->bt_fd,F_SETLKW,&fl);  

    fl.l_whence = SEEK_SET;
    fl.l_start  = ((off_t)pgno)*t->bt_psize+1; 
    fl.l_len    = 1;
    fl.l_type   = type?F_WRLCK:F_RDLCK;
    fcntl(t->bt_fd,F_SETLKW,&fl);  

    fl.l_whence = SEEK_SET;
    fl.l_start  = ((off_t)pgno)*t->bt_psize; 
    fl.l_len    = 1;
    fl.l_type   = F_UNLCK;
    fcntl(t->bt_fd,F_SETLK,&fl);  
}
 
//----------------------------------------------------------------------------
void __bt_pageunlock(BTREE *t, pgno_t pgno)
{
    struct flock fl;

    fl.l_whence = SEEK_SET;
    fl.l_start  = ((off_t)pgno)*t->bt_psize+1;
    fl.l_len    = 1;
    fl.l_type   = F_UNLCK;
    fcntl(t->bt_fd,F_SETLK,&fl);  
}


#else
//-----------------------------------------------------------------------------
// Szuksegmegoldas Windows-ra.
// 1) a lockolt terulet nem olvashato
// 2) hianyzik a shared lock

//pagelock: (2GB-1KB-pgno) pozicion 1 byte
#define PAGE2POS(pgno) ((unsigned)2*1024*1024*1024-1024-(pgno))
 
#include <windows.h>
#include <io.h>
#include <sys\locking.h>

#ifdef BORLAND
#define _locking   locking
#define _LK_LOCK   LK_LOCK  
#define _LK_NBLCK  LK_NBLCK  
#define _LK_UNLCK  LK_UNLCK  
#endif

//----------------------------------------------------------------------------
static int __bt_fsetlock(int fd, long pos, int nbyte) 
{
    int result=-1;
    long curpos=_lseek(fd,0L,SEEK_CUR);
    if( -1L!=_lseek(fd,pos,SEEK_SET) )
    {
        while( 0!=(result=_locking(fd,_LK_NBLCK,nbyte)) )
        {
            Sleep(100);
        }
    }
    _lseek(fd,curpos,SEEK_SET);
    return result;  //0,-1
}

//----------------------------------------------------------------------------
static int __bt_funlock(int fd, long pos, int nbyte)  
{
    int result=-1;
    long curpos=_lseek(fd,0L,SEEK_CUR);
    if( -1L!=_lseek(fd,pos,SEEK_SET) )
    {
        result=_locking(fd,_LK_UNLCK,nbyte);
    }
    _lseek(fd,curpos,SEEK_SET);
    
    return result;  //0,-1
}

//----------------------------------------------------------------------------
void __bt_pagelock(BTREE *t, pgno_t pgno, int type)
{
    __bt_fsetlock(t->bt_fd,PAGE2POS(pgno),1);  
} 


//----------------------------------------------------------------------------
void __bt_pageunlock(BTREE *t, pgno_t pgno)
{
    __bt_funlock(t->bt_fd,PAGE2POS(pgno),1);  
}
 
#endif
//----------------------------------------------------------------------------

