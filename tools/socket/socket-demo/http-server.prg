
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

#define BASE a"."
#define PORT 8080

function main( )

local crcr:=x"0d0a0d0a"
local hdr200:=a"HTTP/1.1 200 OK"+crcr
local hdr404:=a"HTTP/1.1 404 Not Found"+crcr
local s,c,get,htm,doc
local req,rsp,n

    ? "socket ", s:=socket()
    setsockopt(s,"REUSEADDR",.t.)
    ? "bind   ", bind(s,PORT)
    ? "listen ", listen(s)

    while( .t. )
        ? "accept ", c:=accept(s)
    
        req:=x""
        while( empty(req) .or. len(get:=split(req," "))<2 )
            req+=sread(c,1024,200)
        end
        ? req
        
        if( get[1]==a"GET" )        
            
            if( file(htm:=BASE+get[2]) )
                doc:=memoread(htm,.t.) //binary
                rsp:=hdr200+doc
            else
                doc:=htm+a" NOT FOUND"+x"0d0a"
                rsp:=hdr404+doc
            end

            //#define SLOW_RESPONSE
            #ifdef SLOW_RESPONSE
                for n:=1 to len(rsp) step 100
                    swrite(c,rsp::substr(n,100))  //swrite-nak csak 2 paramétere van!
                    sleep(100)
                next
            #else
                swrite(c,rsp) 
            #endif


            ?? rsp::left(12)
            sclose(c)
        end
    end
