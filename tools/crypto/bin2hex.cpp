
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
#include <string.h>

#include <cccapi.h>
 
//---------------------------------------------------------------------------- 
void _clp_crypto_bin2hex(int argno)
{
    CCC_PROLOG("crypto_bin2hex",1);

    str2bin(base);

    char *text=_parb(1);
    int length=_parblen(1);
    
    char *buf=binaryl(2*length);
    
    int i;
    for( i=0; i<length; i++ )
    {
        sprintf(buf+2*i,"%02x", 255&(int)text[i]);
    }
    _retblen(buf, 2*length);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 

