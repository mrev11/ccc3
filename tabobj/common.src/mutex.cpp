
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

#include <cccapi.h>

static int lockcount=0;

//----------------------------------------------------------------------------
#ifdef _UNIX_
//----------------------------------------------------------------------------
void _clp__writechangelog_mutex(int argno)
{
    CCC_PROLOG("_writechangelog_mutex",2);

    int fd=_parni(1);
    int flag=_parl(2);

    struct flock fl;
    
    if( flag )
    {
        if( lockcount==0  )
        {
            fl.l_whence = SEEK_SET;
            fl.l_start  = 0;
            fl.l_len    = 1;
            fl.l_type   = F_WRLCK;
            fcntl(fd,F_SETLKW,&fl);  
        }
        lockcount++;
    }
    else
    {
        lockcount--;
        if( lockcount<=0 )
        {
            fl.l_whence = SEEK_SET;
            fl.l_start  = 0;
            fl.l_len    = 1;
            fl.l_type   = F_UNLCK;
            fcntl(fd,F_SETLK,&fl);  
            lockcount=0;
        }
    }
    _retni(lockcount);
    CCC_EPILOG();
}

//-----------------------------------------------------------------------------
#else  //Windows
//-----------------------------------------------------------------------------
 
#include <io.h>
#include <sys\locking.h>

#ifdef BORLAND
#define _locking   locking
#define _LK_LOCK   LK_LOCK  
#define _LK_NBLCK  LK_NBLCK  
#define _LK_UNLCK  LK_UNLCK  
#endif

//----------------------------------------------------------------------------
void _clp__writechangelog_mutex(int argno)
{
    CCC_PROLOG("_writechangelog_mutex",2);

    int fd=_parni(1);
    int flag=_parl(2);

    _lseek(fd,0,SEEK_SET);
    
    if( flag )
    {
        if( lockcount==0  )
        {
            while( _locking(fd,_LK_NBLCK,1) )
            {
                Sleep(60);
            }
        }
        lockcount++;
    }
    else
    {
        lockcount--;
        if( lockcount<=0 )
        {
            _locking(fd,_LK_UNLCK,1);
            lockcount=0;
        }
    }
    _retni(lockcount);
    CCC_EPILOG();
}
 
//----------------------------------------------------------------------------
#endif
