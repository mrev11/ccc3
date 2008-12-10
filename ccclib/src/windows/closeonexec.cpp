
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

#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <cccapi.h>

//--------------------------------------------------------------------------
void _clp_sethandleinheritflag(int argno) //használható socketre!
{
    CCC_PROLOG("sethandleinheritflag",2);
    HANDLE handle=(HANDLE)_parnu(1);
    int flag=_parl(2);
    _retl(SetHandleInformation(handle,HANDLE_FLAG_INHERIT,flag?HANDLE_FLAG_INHERIT:0));
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_gethandleinheritflag(int argno) 
{
    CCC_PROLOG("gethandleinheritflag",1);
    HANDLE handle=(HANDLE)_parnu(1);
    unsigned long flag=0;
    if( GetHandleInformation(handle,&flag) )
    {
        _retl(flag&HANDLE_FLAG_INHERIT);
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_setcloexecflag(int argno) //nem használható socketre!
{
    CCC_PROLOG("setcloexecflag",2);
    int fd=_parni(1);
    int flag=_parl(2);
    long handle=_get_osfhandle(fd);
    _retl(SetHandleInformation((HANDLE)handle,HANDLE_FLAG_INHERIT,!flag?HANDLE_FLAG_INHERIT:0)); //fordítani!
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_getcloexecflag(int argno) //nem használható socketre!
{
    CCC_PROLOG("getcloexecflag",1);
    int fd=_parni(1);
    long handle=_get_osfhandle(fd);
    unsigned long flag=0;
    if( GetHandleInformation((HANDLE)handle,&flag) )
    {
        _retl(!(flag&HANDLE_FLAG_INHERIT)); //fordítani!
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}
 
//--------------------------------------------------------------------------
