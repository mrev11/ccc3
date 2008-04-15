
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
#include <unistd.h>
#include <fcntl.h>

#include <cccapi.h>

// CloseOnExecFlag==.t.  -- a filédescriptor nem öröklődik
// CloseOnExecFlag==.f.  -- a filédescriptor öröklődik

//--------------------------------------------------------------------------
void _clp_setcloexecflag(int argno) 
{
    //beállítja a CloseOnExecFlag-et
    //visszatérés: .t./.f. jelzi, hogy sikerült-e

    CCC_PROLOG("setcloexecflag",2);
    int fd=_parni(1);
    int fl=_parl(2);
    _retl( 0==fcntl(fd,F_SETFD,fl?FD_CLOEXEC:0) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_getcloexecflag(int argno) 
{
    //lekérdezi a CloseOnExecFlag-et
    //visszatérés: .t./.f., vagy NIL érvénytelen descriptor esetén

    CCC_PROLOG("getcloexecflag",1);
    int fd=_parni(1);
    int fl=fcntl(fd,F_GETFD);

    if( fl==-1 ) 
    {
        _ret();
    }
    else
    {
        _retl( fl&FD_CLOEXEC );
    }

    CCC_EPILOG();
}
 
//--------------------------------------------------------------------------
