
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

#include <sckcompat.h>
#include <cccapi.h>

DEFINE_METHOD(operation);
DEFINE_METHOD(oscode);
DEFINE_METHOD(description);

//------------------------------------------------------------------------
void _clp_unix_socketpair(int argno)
{
    CCC_PROLOG("unix_socketpair",0);

    int sv[2]={-1,-1}; 
    if( 0==socketpair(AF_LOCAL,SOCK_STREAM,0,sv) )
    {
        number(sv[0]);
        number(sv[1]);
        array(2);
        _rettop();
    }
    else 
    {
        _clp_socketerrornew(0);

        DUP();
        stringn(CHRLIT("unix_socketpair"));
        _o_method_operation.eval(2);
        POP();

        DUP();
        number(errno);
        _o_method_oscode.eval(2);
        POP();

        DUP();
        stringn(CHRLIT("unix_socketpair failed"));
        _o_method_description.eval(2);
        POP();

        _clp_break(1);
        _ret(); //NIL
    }

    CCC_EPILOG();
}

//------------------------------------------------------------------------
