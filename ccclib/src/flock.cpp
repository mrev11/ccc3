
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
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#include <cccapi.h>
#include <flock.h>

//#define DEBUG


#ifdef UNIX
//------------------------------------------------------------------------------------------
int _ccc_lock(int fd, unsigned low, unsigned high, unsigned length, unsigned flags)
{
    off_t start=high;
    start=(start<<32)+low;
    int type=(flags&CCCLK_READ) ? F_RDLCK : F_WRLCK;
    int lock=(flags&CCCLK_WAIT) ? F_SETLKW : F_SETLK;

    struct flock fl;
    fl.l_whence = SEEK_SET;
    fl.l_start  = start;
    fl.l_len    = length;
    fl.l_type   = type;
    int result=fcntl(fd,lock,&fl); //OK 0, error -1

#ifdef DEBUG
    printf("pid=%d fd=%d  %llx  %-6s  %-9s  %s\n",
                getpid(),
                fd,
                (long long)start,
                lock==F_SETLKW ? "wait":"nowait",
                type==F_RDLCK ? "shared":"exclusive",
                result==0 ? "Ok":"Failed");
#endif
    return result; //OK 0, error -1
}

//------------------------------------------------------------------------------------------
int _ccc_unlock(int fd, unsigned low, unsigned high, unsigned length)
{
    off_t start=high;
    start=(start<<32)+low;
    int type=F_UNLCK;
    int lock=F_SETLK;

    struct flock fl;
    fl.l_whence = SEEK_SET;
    fl.l_start  = start;
    fl.l_len    = length;
    fl.l_type   = type;
    return fcntl(fd,lock,&fl); //OK 0, error -1
}

//------------------------------------------------------------------------------------------
#else //WINDOWS
//------------------------------------------------------------------------------------------
int _ccc_lock(int fd, unsigned low, unsigned high, unsigned length, unsigned flags)
{
    OVERLAPPED overlapped={0,0,0,0,NULL};
    overlapped.Offset=low;
    overlapped.OffsetHigh=high;

    int mode=0;
    mode+=(flags&CCCLK_READ) ? 0 : LOCKFILE_EXCLUSIVE_LOCK; 
    mode+=(flags&CCCLK_WAIT) ? 0 : LOCKFILE_FAIL_IMMEDIATELY;  

    int result=LockFileEx(  (HANDLE)_get_osfhandle(fd),
                            mode,
                            0,
                            length,
                            0,
                            &overlapped );
#ifdef DEBUG
    off_t start=high;
    start=(start<<32)+low;

    printf("pid=%d fd=%d  %llx  %-6s  %-9s  %s\n",
                getpid(),
                fd,
                (long long)start,
                (flags&CCCLK_WAIT) ? "wait":"nowait",
                (flags&CCCLK_READ) ? "shared":"exclusive",
                result==0 ? "Ok":"Failed");
#endif

    return (result==0)?-1:0; //OK 0, error -1                       
}

//------------------------------------------------------------------------------------------
int _ccc_unlock(int fd, unsigned low, unsigned high, unsigned length)
{
    int result=UnlockFile(  (HANDLE)_get_osfhandle(fd),
                            low,
                            high,
                            length,
                            0 );

    return (result==0)?-1:0;  //OK 0, error -1                       
}
//------------------------------------------------------------------------------------------

#endif

