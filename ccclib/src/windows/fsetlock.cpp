
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


#include <stdio.h>
#include <io.h>
#include <sys\locking.h>
 
#include <cccapi.h>

//-----------------------------------------------------------------------------
void _clp_fsetlock(int argno)
{
    CCC_PROLOG("fsetlock",4);

    int fd=0;
    unsigned long long pos=0;
    unsigned long long nbyte=0;

    if( argno==3 ) 
    {
        fd    = _parni(1);
        pos   = _parnuw(2); 
        nbyte = _parnuw(3);
    }
    else if( argno==4 ) //large file support  
    {
        unsigned long long low,high;

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

    int result=LockFile((HANDLE)_get_osfhandle(fd),
                         pos&0xffffffff,pos>>32,
                         nbyte&0xffffffff,nbyte>>32); //Boolean
                         
    if( result )
    {
        _retni(0);
    }
    else
    {
        errno=GetLastError(); //printf("\nLOCK %d",errno);
        _retni(-1);
    }

    //0, ha OK, -1, ha sikertelen
    
    CCC_EPILOG();
}

//-----------------------------------------------------------------------------
void _clp_funlock(int argno)
{
    CCC_PROLOG("funlock",4);

    int fd=0;
    unsigned long long pos=0; 
    unsigned long long nbyte=0;

    if( argno==3 ) 
    {
        fd    = _parni(1);
        pos   = _parnuw(2); 
        nbyte = _parnuw(3);
    }
    else if( argno==4 ) //large file support  
    {
        unsigned long long low,high;

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

    int result=UnlockFile((HANDLE)_get_osfhandle(fd),
                         pos&0xffffffff,pos>>32,
                         nbyte&0xffffffff,nbyte>>32); //Boolean
                         
    if( result )
    {
        _retni(0);
    }
    else
    {
        errno=GetLastError(); //printf("\nUNLOCK %d",errno);
        _retni(-1);
    }

    //0, ha OK, -1, ha sikertelen
 
    CCC_EPILOG();
}

//-----------------------------------------------------------------------------

