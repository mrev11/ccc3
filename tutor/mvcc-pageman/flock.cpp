
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

#include <sys/file.h>
#include <cccapi.h>
#include <flock.ch>

namespace _nsp_pageman {


void _clp_flock(int argno)
{
    CCC_PROLOG("flock",2);

    int fd=_parni(1);
    int cccop=_parni(2);

    int op=0;
    if( cccop&FLOCK_SH ) op|=LOCK_SH;
    if( cccop&FLOCK_EX ) op|=LOCK_EX;
    if( cccop&FLOCK_UN ) op|=LOCK_UN;
    if( cccop&FLOCK_NB ) op|=LOCK_NB;
    
    _retni( flock(fd,op) );  //success 0, error -1

    CCC_EPILOG();
}



void _clp_rlock(int argno)  //UNIX
{
    CCC_PROLOG("rlock",3);
    
    int   fd    = _parni(1);
    off_t pos   = (off_t)_parnu(2); 
    off_t nbyte = (off_t)_parnu(3);
 
    struct flock fl;

    fl.l_whence = SEEK_SET;
    fl.l_start  = pos;
    fl.l_len    = nbyte;
    fl.l_type   = F_WRLCK;

    _retni( fcntl(fd,F_SETLK,&fl))  ;

    CCC_EPILOG();
}


void _clp_runlock(int argno)  //UNIX
{
    CCC_PROLOG("runlock",3);
    
    int   fd    = _parni(1);
    off_t pos   = (off_t)_parnu(2); 
    off_t nbyte = (off_t)_parnu(3);
 
    struct flock fl;

    fl.l_whence = SEEK_SET;
    fl.l_start  = pos;
    fl.l_len    = nbyte;
    fl.l_type   = F_UNLCK;

    _retni( fcntl(fd,F_SETLK,&fl))  ;

    CCC_EPILOG();
}

}//namespace
