
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

#include "inkey.ch"

function main(ipaddr)

local k:=0,s,sms

    //memowrit("pid",alltrim(str(getpid())))

    if( ipaddr==NIL )
        ipaddr:="127.0.0.1"
    end

    alert(ipaddr)

    ? s:=socket()
    ? connect(s,ipaddr,45000)
    
    sms:=smessageNew(s)
    
    while( k!=K_ESC )
        ? sms:message:={"Próba szerencse!"}, sms:counter
        k:=inkey(0)
    end

    return NIL

