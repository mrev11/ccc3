
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


#define SWRITE(s,x)      xswrite(s,x)

function main( )

local cr:=x"0d0a"
local crcr:=x"0d0a0d0a"

//local hdr200:=a"HTTP/1.1 200 OK"+crcr
local hdr200:=a"HTTP/1.1 200 OK"+cr+a"Transfer-Encoding: chunked"+crcr
local hdr404:=a"HTTP/1.1 404 Not Found"+cr+a"Transfer-Encoding: chunked"+crcr
local s,c,get,doc
local req,chunk,n,w

    ? "socket ", s:=socket()
    setsockopt(s,"REUSEADDR",.t.)
    ? "bind   ", bind(s,PORT)
    ? "listen ", listen(s)

    while( .t. )
        ? "accept ", c:=accept(s)

        ? req:=http_readmessage(c)
        
        get:=split(req," ")        

        if( get[1]==a"GET" )        
        
            doc:=BASE+get[2]
            if( file(doc) )
                doc:=memoread(doc,.t.) //binary
                SWRITE(c,hdr200)
            else
                SWRITE(c,hdr404)
            end
            
            
            n:=1
            w:=1
            chunk:=doc::substr(n,w)

            while( .t. )
                SWRITE(c,chunk::len::l2hex::str2bin)
                SWRITE(c,cr)
                SWRITE(c,chunk)
                SWRITE(c,cr)
                
                if( len(chunk)==0  )
                    exit
                end

                n+=w
                w++
                chunk:=doc::substr(n,w)
            end

            sclose(c)
        end
    end



static function xswrite(c,x)
    sleep(10)
    swrite(c,x)
    ?? x



