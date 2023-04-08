
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



// Egyszerusitett valtozat (fordulnia kell MSYS2-ben is)


#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>

#include <flock.h>
#include <cccapi.h>


//----------------------------------------------------------------------------------------
static int lowlevel_lock(int fd, unsigned low, unsigned high, unsigned length, int rwtype, int timeout)
{
    off_t start=high;
    start=(start<<32)+low;

    struct flock fl;
    fl.l_whence = SEEK_SET;
    fl.l_start  = start;
    fl.l_len    = length;
    fl.l_type   = rwtype?F_WRLCK:F_RDLCK;

    if( 0==fcntl(fd,F_SETLK,&fl) )
    {
        return 0;
    }
    else if( timeout==0 )
    {
        return -1;
    }
    else
    {
        return fcntl(fd,F_SETLKW,&fl);
    }
}

//----------------------------------------------------------------------------------------
static int lowlevel_unlock(int fd, unsigned low, unsigned high, unsigned length)
{
    off_t start=high;
    start=(start<<32)+low;

    struct flock fl;
    fl.l_whence = SEEK_SET;
    fl.l_start  = start;
    fl.l_len    = length;
    fl.l_type   = F_UNLCK;
    return fcntl(fd,F_SETLK,&fl); // OK 0, error -1
}



//----------------------------------------------------------------------------------------
// public interface
//----------------------------------------------------------------------------------------
int fsetlock(int fd, unsigned low, unsigned high, unsigned length, int rwtype)
{
    return lowlevel_lock(fd,low,high,length,rwtype,0);
}
//----------------------------------------------------------------------------------------
int fwaitlock(int fd, unsigned low, unsigned high, unsigned length, int rwtype)
{
    return lowlevel_lock(fd,low,high,length,rwtype,-1);
}
//----------------------------------------------------------------------------------------
int ftimeoutlock(int fd, unsigned low, unsigned high, unsigned length, int rwtype, int timeout)
{
    return lowlevel_lock(fd,low,high,length,rwtype,timeout);
}
//----------------------------------------------------------------------------------------
int funlock(int fd, unsigned low, unsigned high, unsigned length)
{
    return lowlevel_unlock(fd,low,high,length);
}
//----------------------------------------------------------------------------------------


