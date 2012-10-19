
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

// Lock függvények  (fsetlock, funlock)

#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#include <cccapi.h>


//-----------------------------------------------------------------------------
void _clp_fsetlock(int argno)  //UNIX
{
    CCC_PROLOG("fsetlock",4);
    
    int fd=0;
    off_t pos=0, nbyte=0;

    if( argno==3 ) 
    {
        fd    = _parni(1);
        pos   = _parnuw(2); 
        nbyte = _parnuw(3);
    }
    else if( argno==4 ) //large file support  
    {
        off_t low,high;

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
 
    struct flock fl;

    fl.l_whence = SEEK_SET;
    fl.l_start  = pos;
    fl.l_len    = nbyte;
    fl.l_type   = F_WRLCK;

    _retni( fcntl(fd,F_SETLK,&fl) ); //OK 0, error -1

    CCC_EPILOG();
}

//-----------------------------------------------------------------------------
void _clp_funlock(int argno)  //UNIX
{
    CCC_PROLOG("funlock",4);

    int fd=0;
    off_t pos=0,nbyte=0;
 
    if( argno==3 ) 
    {
        fd    = _parni(1);
        pos   = _parnuw(2); 
        nbyte = _parnuw(3); 
    }
    else if( argno==4 ) //large file support 
    {
        off_t low,high;
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
 
    struct flock fl;

    fl.l_whence = SEEK_SET;
    fl.l_start  = pos;
    fl.l_len    = nbyte;
    fl.l_type   = F_UNLCK;

    _retni( fcntl(fd,F_SETLK,&fl) );  //OK 0, error -1

    CCC_EPILOG();
}

//-----------------------------------------------------------------------------

