
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

local s,c,req,get,htm,doc

    ? "socket ", s:=socket()
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
            else
                doc:=htm+a" NOT FOUND"+x"0d0a"
            end

            swrite(c,doc,len(doc)) 
            sclose(c)
        end
    end

    return NIL
