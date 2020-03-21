
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

namespace _nsp_websocket{

void _clp_mask(int argno)
{
    CCC_PROLOG("websocket.mask",2);
    char *buf=_parb(1);
    int len=_parblen(1);
    char *key=_parb(2);
    if( 4!=_parblen(2) )
    {
        ARGERROR();
    }
    for(int i=0; i<len; i++)
    {
        buf[i]^=key[i%4];
    }
    stack=base+1; // retv(base);
    CCC_EPILOG();
}

}//namespace