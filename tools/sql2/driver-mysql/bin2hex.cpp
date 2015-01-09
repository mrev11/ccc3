
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

namespace _nsp_sql2 {
namespace _nsp_mysql {

static const char hextbl[] = "0123456789abcdef";
 
//---------------------------------------------------------------------------- 
void _clp_bin2hex_x(int argno)  // x"123456789abcdef0" -> a"123456789abcdef0"
{
    CCC_PROLOG("crypto_bin2hex",1);

    str2bin(base);

    char *text=_parb(1);
    int length=_parblen(1);
    
    char *buf=binaryl(2*length);
    
    for( int i=0; i<length; i++ )
    {
        int c=0xFF&(int)text[i];
        buf[2*i]=hextbl[(c>>4) & 0xF];
        buf[2*i+1]=hextbl[c & 0xF];
    }

    _retblen(buf, 2*length);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_bin2hex_c(int argno)  // x"123456789abcdef0" -> "123456789abcdef0"
{
    CCC_PROLOG("crypto_bin2hexc",1);

    str2bin(base);

    char *text=_parb(1);
    int length=_parblen(1);
    
    CHAR *buf=stringl(2*length);
    
    for( int i=0; i<length; i++ )
    {
        int c=0xFF&(int)text[i];
        buf[2*i]=hextbl[(c>>4) & 0xF];
        buf[2*i+1]=hextbl[c & 0xF];
    }

    _retclen(buf, 2*length);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 

}}
