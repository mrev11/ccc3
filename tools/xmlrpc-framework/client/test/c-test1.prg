
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

local client,sid,n,e,cnt:=0

    set console off
    set printer to ("log-test1-"+alltrim(str(getpid())))
    set printer on
    set date format "yyyy-mm-dd"

    if( host==NIL )
        host:="localhost"
    end

    if( port==NIL )
        port:="45000"
    end
    
    client:=xmlrpcclientNew(host,port)

    if(ssl!=NIL)
        client:sslcontext:=sslctxNew()
    end

    client:keepalive:=.t.
    //client:debug:=.t.
    
    while( .t. )

        ? sid:=client:call("session.login",{"proba","szerencse"})

        begin

            for n:=1 to 20

                if( !file("sema") )
                    //hogy könnyű legyen egyszerre
                    //rengeteg processt kiléptetni
                    quit
                end

                client:call("session.validate",sid)     
                client:call("session.who",sid)     
                client:call("teszt.hello",sid)     
                client:call("teszt.gettime",sid)     
                client:call("teszt.echo",{ sid,1,"A",.t.,{}, date() })     

                ?? " "+alltrim(str(++cnt))
                fflush()
                sleep( rand1()*4000 ) //4 sec, egyenletes
            
                //ha az XMLRPC_TIMEOUT 4 sec-re van beállítva,
                //akkor a programok kellemesen gyakran elszállnak,
                //itt éppen ez kell a nyúzópróbához
            next

            client:call("session.logout",sid)
        
        recover e
        
            ?? " X", e:classname //, e:operation, e:description
            cnt:=0
        end
    end


*****************************************************************************
static function rand1()
static ff:=bin2w(bin(255)+bin(255)) 
    return bin2w(crypto_rand_bytes(2))/ff //[0,1] egyenletes 

*****************************************************************************
 