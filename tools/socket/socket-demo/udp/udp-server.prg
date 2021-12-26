
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

function main()

local sck
local host:="localhost"
local port:=4321
local client_addr
local message
local maxlen:=8192

    ? sck:=socket_udp()
    ? bind(sck,port)
    

    while(.t.)

        if( 0==select({sck},,,5000) )
            ?? "."
            loop
        end
        
        message:=recvfrom(sck,maxlen,@client_addr)
        ? message::len, message::bin2str::padr(32)
        hexdump(client_addr)
        sleep(100)
        ? sendto(sck,upper(message),client_addr) //response
    end

    ?
    
    

