
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

//Ugyanúgy használható, mint a UNIX-os pipe,
//csak bajlódni kell a buffer mérettel,
//a buffer default mérete 32*32K=1MB.

#include <fcntl.h>
#include <io.h>
#include <cccapi.h>
 
//-----------------------------------------------------------------------
void _clp_pipe(int argno)
{
    CCC_PROLOG("pipe",1);
    int bufsiz=ISNUMBER(1)?_parni(1):32*0x8000;

    int fildes[2];

    if( 0==_pipe(fildes,bufsiz,O_BINARY) )
    {
        number( fildes[0] );
        number( fildes[1] );
        array( 2 );
        _rettop();
    }
    else
    {
        _ret();
    }
    
    CCC_EPILOG();
}

//-----------------------------------------------------------------------

