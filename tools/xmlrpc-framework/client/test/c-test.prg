
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

*****************************************************************************
function main(host,port,ssl)

local k:="?"
local client, sid
local p, n, e

    set printer to log-test
    set printer on
    set date format "yyyy-mm-dd"

    if( host==NIL )
        host:="localhost"
    end

    if( port==NIL )
        port:=45000
    end
    
    client:=xmlrpcclientNew(host,port)
    
    if(ssl!=NIL)
        client:sslcontext:=sslctxNew()
    end
    
    
    //client:timeout:=1000 
    client:keepalive:=.t.
    client:debug:=.t.
    
    ? client:host, client:port
    ?
    
    while( .t. )

        k:=chr(inkey(0))

        if( k=="x" )
            exit
        end

        begin
            if( k=="l" ) 
                ? sid:=client:call("session.login",{"vanaki","forron"} )

            elseif( k=="o" ); ? client:call("session.logout",sid)
            elseif( k=="s" ); ? client:call("session.getversion",sid)
            elseif( k=="V" ); ? client:call("session.validate",{sid,.t.})  //prolong
            elseif( k=="v" ); ? client:call("session.validatex",{sid,.t.})  //prolong
            elseif( k=="T" ); ? client:call("session.gettimeout",{sid})
            elseif( k=="w" ); ? client:call("session.who",sid)  //prolong 
            elseif( k=="p" ); ? client:call("session.permission",{sid,"konyvel"}) //prolong
            elseif( k=="P" ); ? client:call("session.permission",{sid,"konyvel.append"}) //prolong
            elseif( k=="g" ); ? client:call("session.groupid",sid) //prolong
            elseif( k=="u" ); ? client:call("session.userid",sid) //prolong
            elseif( k=="n" ); ? client:call("session.username",sid) //prolong
            elseif( k=="t" ); ? client:call("session.usertype",sid) //prolong

            elseif( k=="h" )
                ? client:call("teszt.hello",sid)     
            elseif( k=="m" )
                ? client:call("teszt.gettime",sid)     
            elseif( k=="e" )
                ? client:call("teszt.echo",{sid,1,"&A<",.t.,{},date()})     
            elseif( k=="r" )
                ? client:call("teszt.error",{sid})     
            elseif( k=="S" )
                client:call("system.printstate",sid)
            end
        
        recover  e
            ? e:classname, e:operation, e:description, e:subsystem, e:args
        end
    end
    ?

*****************************************************************************

 