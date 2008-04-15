
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

#include <cccapi.h>

static int errorlevel=0;

//----------------------------------------------------------------------------
void _clp_errorlevel(int argno)
{
    CCC_PROLOG("errorlevel",1);
    int current_level=errorlevel;
    if( !ISNIL(1) )
    {
        errorlevel=_parni(1);
    }
    _retni(current_level);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp___quit(int argno)
{
    static int flag=0;

    if( !flag )
    {   
        flag=1; //védekezni kell a rekurzívvá válás ellen
        _clp_quitblock(0);
        _clp_eval(1);
        pop();
    }
    exit(errorlevel);  
}

//----------------------------------------------------------------------------
void _clp_quit(int argno)
{
    _clp___quit(argno);
}

//----------------------------------------------------------------------------
