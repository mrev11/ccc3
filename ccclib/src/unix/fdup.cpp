
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

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include <cccapi.h>

//--------------------------------------------------------------------------
void _clp_fdup(int argno) 
{
    //fdup(fd)          : közönséges dup
    //fdup(fd1,.f.)     : dup, az új fd nem öröklődik
    //fdup(fd1,.f.,.t)  : dup, az új fd nem öröklődik, a régi lezáródik
    //fdup(fd1,fd2)     : közönséges dup2
    //fdup(fd1,fd2,.t.) : dup2, a régi fd lezáródik 
 
    CCC_PROLOG("fdup",3);
    
    int oldfd=_parni(1);
    int closeflag=ISNIL(3)?0:_parl(3);
    
    if( ISNIL(2) ) //közönséges dup
    {
        _retni( dup(oldfd) );
    }

    else if( ISNUMBER(2) ) //közönséges dup2
    {
        int newfd=_parni(2);
        _retni( dup2(oldfd,newfd) );
    }

    else //dup + öröklődés
    {
        int inheritflag=_parl(2);
        int newfd=dup(oldfd);
        int r=fcntl(newfd,F_SETFD,inheritflag?0:FD_CLOEXEC);
        _retni( r==0 ? newfd : -1 );
    }
    
    if( closeflag )
    {
        close(oldfd);
    }
 
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_hdup(int argno) 
{
    _clp_fdup(argno); //UNIX-on fdup
}

//--------------------------------------------------------------------------
