
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

//-----------------------------------------------------------------------------
void _clp_fwaitlock(int argno)
{
    // lock varakozassal

    // fwaitlock(fd, offset, length [,flag])
    // fwaitlock(fd, low, high, length [,flag])
    // flag defaultja: .t. (exclusive)

    CCC_PROLOG("fwaitlock",5);
    
    int xp=0;
    int exclusive_lock=1; //default: write lock
    if( ISFLAG(argno) )
    {
        xp=1;
        exclusive_lock=_parl(argno);
    }
 
    int fd=0;
    off_t pos=0,low=0,high=0,nbyte=0;

    if( (argno-xp)==3 ) 
    {
        fd    = _parni(1);
        pos   = _parnuw(2);
        nbyte = _parnuw(3);
        low   = pos&0xffffffff;
        high  = pos>>32;
    }
    else if( (argno-xp)==4 ) //large file support  
    {
        fd    = _parni(1);
        low   = _parnuw(2); 
        high  = _parnuw(3); 
        nbyte = _parnuw(4);
        pos   = (high<<32)+low;
    }
    else
    {
        ARGERROR();
    }

#ifdef UNIX 

    struct flock fl;
    fl.l_whence = SEEK_SET;
    fl.l_start  = pos;
    fl.l_len    = nbyte;
    fl.l_type   = exclusive_lock?F_WRLCK:F_RDLCK;
    _retni( fcntl(fd,F_SETLKW,&fl) ); //OK 0, error -1

#else

    OVERLAPPED overlapped={0,0,0,0,NULL};
    overlapped.Offset=low;
    overlapped.OffsetHigh=high;
    int result=LockFileEx(  (HANDLE)_get_osfhandle(fd),
                            exclusive_lock?LOCKFILE_EXCLUSIVE_LOCK:0,
                            0,
                            nbyte&0xffffffff,
                            nbyte>>32,
                            &overlapped );
    _retni( result==0?-1:0 ); //OK 0, error -1                       

#endif

    CCC_EPILOG();
}

//-----------------------------------------------------------------------------

