
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

//hashcode metódusnevek kikereséséhez
//használja: xmethod2.cpp, class.prg

#include <cccapi.h>

//----------------------------------------------------------------------------
unsigned int hashcode(const BYTE *p)
{
    unsigned hcode;
    for( hcode=0; *p; p++ )
    {
        hcode+=(unsigned)*p;
        hcode*=99817; //prím
    }
    return hcode;
}

//----------------------------------------------------------------------------
unsigned int hashcode(const CHAR *p)
{
    unsigned hcode;
    for( hcode=0; *p; p++ )
    {
        hcode+=(unsigned)*p;
        hcode*=99817; //prím
    }
    return hcode;
}

//----------------------------------------------------------------------------
void _clp_hashcode(int argno)
{
    CCC_PROLOG("hashcode",1);
    if( ISBINARY(1) )
    {
        _retni(hashcode(_parb(1)));
    }
    else if( ISSTRING(1) )
    {
        _retni(hashcode(_parc(1)));
    }
    else
    {
        ARGERROR();
    }
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
