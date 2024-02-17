
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
#include <cccapi.h>
#include <termapi.h>


//----------------------------------------------------------------------------
void _clp_setcaption(int argno)
{
    CCC_PROLOG("setcaption",1);
    if( ISSTRING(1) )
    {
        #ifdef _CCC3_
            str2bin(base);
        #else
            extern void _clp_codeset_letter_and_box_latin2_to_utf8(int);
            _clp_codeset_letter_and_box_latin2_to_utf8(1);
        #endif
    }
    setcaption(_parb(1),_parblen(1));
    CCC_EPILOG();
}

//----------------------------------------------------------------------------

