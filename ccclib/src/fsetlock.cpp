
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

#ifdef UNIX // UNIX headerek
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#else //WATCOM, MSVC, MINGW, BORLAND headerek

#include <stdio.h>
#include <io.h>
 
#ifdef MSVC
#include <sys\locking.h>
#endif

#ifdef MINGW
#include <sys\locking.h>
#endif
 
#ifdef BORLAND
#include <sys\locking.h>
#endif

#endif
 
#include <cccapi.h>


#ifdef WATCOM
//-----------------------------------------------------------------------------
void _clp_fsetlock(int argno)  //WATCOM
{
    CCC_PROLOG("fsetlock",3);

    int  fhnd  = _parni(1);
    long pos   = _parnl(2);
    long nbyte = _parnl(3);

    _retni( lock(fhnd,pos,nbyte) );  //0, ha OK, -1, ha sikertelen
    
    CCC_EPILOG();
}

//-----------------------------------------------------------------------------
void _clp_funlock(int argno)  //WATCOM
{
    CCC_PROLOG("funlock",3);

    int  fhnd  = _parni(1);
    long pos   = _parnl(2);
    long nbyte = _parnl(3);

    _retni( unlock(fhnd,pos,nbyte) );  //0, ha OK, -1, ha sikertelen

    CCC_EPILOG();
}
#endif


#if defined MSVC || defined MINGW
//-----------------------------------------------------------------------------
void _clp_fsetlock(int argno)  //MSVC, MINGW
{
    CCC_PROLOG("fsetlock",3);

    int  fhnd  = _parni(1);
    long pos   = _parnl(2);
    long nbyte = _parnl(3);
    
    int result = -1;

    long curpos=_lseek(fhnd,0L,SEEK_CUR);
    if( -1L!=_lseek(fhnd,pos,SEEK_SET) )
    {
        result=_locking(fhnd,_LK_NBLCK,nbyte);
    }
    _lseek(fhnd,curpos,SEEK_SET);
    
    _retni( result );  //0, ha OK, -1, ha sikertelen
    
    CCC_EPILOG();
}

//-----------------------------------------------------------------------------
void _clp_funlock(int argno)  //MSVC, MINGW
{
    CCC_PROLOG("funlock",3);

    int  fhnd  = _parni(1);
    long pos   = _parnl(2);
    long nbyte = _parnl(3);

    int result = -1;

    long curpos=_lseek(fhnd,0L,SEEK_CUR);
    if( -1L!=_lseek(fhnd,pos,SEEK_SET) )
    {
        result=_locking(fhnd,_LK_UNLCK,nbyte);
    }
    _lseek(fhnd,curpos,SEEK_SET);
    
    _retni( result );  //0, ha OK, -1, ha sikertelen
 
    CCC_EPILOG();
}
#endif


#ifdef BORLAND
//-----------------------------------------------------------------------------
void _clp_fsetlock(int argno)  //BORLAND
{
    CCC_PROLOG("fsetlock",3);

    int  fhnd  = _parni(1);
    long pos   = _parnl(2);
    long nbyte = _parnl(3);
    
    int result = -1;

    long curpos=lseek(fhnd,0L,SEEK_CUR);
    if( -1L!=lseek(fhnd,pos,SEEK_SET) )
    {
        result=locking(fhnd,LK_NBLCK,nbyte);
    }
    lseek(fhnd,curpos,SEEK_SET);
    
    _retni( result );  //0, ha OK, -1, ha sikertelen
    
    CCC_EPILOG();
}

//-----------------------------------------------------------------------------
void _clp_funlock(int argno)  //BORLAND 
{
    CCC_PROLOG("funlock",3);

    int  fhnd  = _parni(1);
    long pos   = _parnl(2);
    long nbyte = _parnl(3);

    int result = -1;

    long curpos=lseek(fhnd,0L,SEEK_CUR);
    if( -1L!=lseek(fhnd,pos,SEEK_SET) )
    {
        result=locking(fhnd,LK_UNLCK,nbyte);
    }
    lseek(fhnd,curpos,SEEK_SET);
    
    _retni( result );  //0, ha OK, -1, ha sikertelen
 
    CCC_EPILOG();
}
#endif

 
#ifdef UNIX
//-----------------------------------------------------------------------------
void _clp_fsetlock(int argno)  //UNIX
{
    CCC_PROLOG("fsetlock",4);
    
    int fd=0;
    off_t pos=0, nbyte=0;

    if( argno==3 ) 
    {
        fd    = _parni(1);
        pos   = (off_t)(_parnd(2)+0.5); 
        nbyte = (off_t)(_parnd(3)+0.5);
    }
    else if( argno==4 ) //large file support  
    {
        off_t low,high;

        fd    = _parni(1);
        low   = _parnu(2); 
        high  = _parnu(3); 
        nbyte = (off_t)(_parnd(4)+0.5); 
      #ifdef _LFS_
        pos   = (high<<32)+low;
      #else
        pos   = low;
      #endif
    }
    else
    {
        ARGERROR();
    }
 
    struct flock fl;
    struct timeval t;
    int w;
    int i=0;

    fl.l_whence = SEEK_SET;
    fl.l_start  = pos;
    fl.l_len    = nbyte;
    fl.l_type   = F_WRLCK;

    w=fcntl(fd,F_SETLK,&fl);

    while ((w==-1) && (i<10))
    {
        i++;
        t.tv_sec=0;
        t.tv_usec=50;
        select(0,NULL,NULL,NULL,&t);
        w=fcntl(fd,F_SETLK,&fl);
    }

    _retni( w==-1?-1:0 );

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
        pos   = (off_t)(_parnd(2)+0.5); 
        nbyte = (off_t)(_parnd(3)+0.5);
    }
    else if( argno==4 ) //large file support 
    {
        off_t low,high;
        fd    = _parni(1);
        low   = _parnu(2); 
        high  = _parnu(3); 
        nbyte = (off_t)(_parnd(4)+0.5);
      #ifdef _LFS_
        pos   = (high<<32)+low;
      #else
        pos   = low;
      #endif
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

    _retni( fcntl(fd,F_SETLK,&fl) );

    CCC_EPILOG();
}
#endif

//-----------------------------------------------------------------------------
