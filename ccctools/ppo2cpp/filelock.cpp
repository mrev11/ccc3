
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

#ifdef WINDOWS  //lock/unlock
    #include <windows.h>
    #include <io.h>
#else
    #include <sys/file.h>
#endif


//------------------------------------------------------------------------------------
void file_lock(FILE *f)
{
    int fd=fileno(f);
    if( fd<0 )
    {
        return;
    }

#ifdef WINDOWS
    HANDLE fh=(HANDLE)_get_osfhandle(fd);
    OVERLAPPED ol;
    memset(&ol,0,sizeof(ol));
    LockFileEx(fh,LOCKFILE_EXCLUSIVE_LOCK,0,1,0,&ol);
#else
    flock(fd,LOCK_EX);
#endif    
}


//------------------------------------------------------------------------------------
void file_unlock(FILE *f)
{
    int fd=fileno(f);
    if( fd<0 )
    {
        return;
    }

#ifdef WINDOWS
    HANDLE fh=(HANDLE)_get_osfhandle(fd);
    OVERLAPPED ol;
    memset(&ol,0,sizeof(ol));
    UnlockFileEx(fh,0,1,0,&ol);
#else
    flock(fd,LOCK_UN);
#endif    
}

//------------------------------------------------------------------------------------


