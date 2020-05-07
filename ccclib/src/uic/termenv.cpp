
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

//----------------------------------------------------------------------------
void _clp_termgetenv(int argno)
{
    CCC_PROLOG("termgetenv",1);
    str2bin(base);
    char *env=_parb(1);
    extern char *termgetenv(char *env);
    char *val=termgetenv(env);
    if(val)
    {
        _retcb(val);
        free(val);
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_termputenv(int argno)  // termputenv("ENVIR=value")
{
    CCC_PROLOG("termputenv",1);
    str2bin(base);
    char *env=_parb(1);
    extern char *termputenv(char *env);
    termputenv(env);
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------

