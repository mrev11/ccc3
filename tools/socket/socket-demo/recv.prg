
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

function main(sck)

local s,c,r
local sms

    set printer to log-recv
    set printer on

#ifdef BIND
    ? "socket ", s:=socket()
    ? "bind   ", bind(s,45000)
    ? "listen ", listen(s)
    ? "accept ", c:=accept(s)
    sclose(s)
#else    
    c:=val(sck)
#endif
    
    sms:=smessageNew(c)

    while( NIL!=(r:=sms:receive) ) //message loop
        
        ? r[1], sms:counter
        
        sms:send( {upper(r[1])} )
    end
    
    return NIL

    
    