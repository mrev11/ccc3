
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
function main(host,port)

local client, e, sid, n:=0, blk:={||garbage()}

    set printer to ("log-test2")
    set printer on

    if(host==NIL)
        host:="localhost"
    end

    if(port==NIL)
        port:="45000"
    end
    
    while( .t. )
    
        client:=xmlrpcclientNew(host,port)
        client:keepalive:=.t.
        client:debug:=.t.

        begin
            //? sid:=client:call("session.login",{"proba","szerencse"})
            ? client:call("teszt.echo",{ sid, blk })  //szemetet kuld
            ? client:call("session.logout",sid)

        recover e
            //valojaban a hiba kiirasa erdektelen,
            //mert a szerver megszakitja a kapcsolatot,
            //ezert a hiba (a kliensben) mindig 
            //"http_readmessage failed"
            //? "ERROR",e:description
            sleep(100)
        end
        
        client:close

        ?? ","+alltrim(str(++n))
        sleep(20)
    end


*****************************************************************************
static function garbage()
local abc:=chr(0)+'"""<&><&><&><&>ABCDEFGHIJKLMNOPQRSTUWVXYZ'+"'''"
local x:="",i
    for i:=1 to 128
        x+=substr(abc,random()%len(abc)+1,1)
    next
    return x


*****************************************************************************
 