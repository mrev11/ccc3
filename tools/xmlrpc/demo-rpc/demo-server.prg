
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

//Demó XMLRPC szerver
 
*****************************************************************************
function main(sslflag)

local server
local ctx

    set printer to log-server
    set printer on
   
    if( !empty(sslflag) )
        ctx:=sslctxNew("SSLv23_server") 
        ctx:use_certificate_file("localhost.pem")
        ctx:use_privatekey_file("localhost.pem")
    end
    
    
  //server:=xmlrpcserverNew(":45000")           //minden interfészen figyel
    server:=xmlrpcserverNew("localhost:45000")  //csak localhost-on figyel
  //server:=xmlrpcserverNew("127.0.0.1:45000")  //csak localhost-on figyel
  //server:=xmlrpcserverNew("xxxyyyzzz:45000")  //socketerror-t dob
  //server:=xmlrpcserverNew("127.0.0.2:45000")  //nem veszi észre a hibát

    server:keepalive    :=.t.   //default .f.
    server:debug        :=.f.   //default .f.
    server:recover      :=.t.   //default .t.
    server:reuseaddr    :=.t.   //default .f.
    
    server:sslcontext   :=ctx   //bekapcsolja az SSL-t (ha ctx nem NIL)
 
    server:addmethod("sample.echo"    ,{|*|{*}})
    server:addmethod("sample.gettime" ,{||time()})
    server:addmethod("sample.sum"     ,{|x,y|x+y})
    server:addmethod("sample.dif"     ,{|x,y|x-y})
    server:addmethod("sample.mul"     ,{|x,y|x*y})
    server:addmethod("sample.div"     ,{|x,y|x/y})

    server:addmethod("sample.struct"  ,{|x,y|demostructNew(x,y)})
    //server:addmethod("sample.struct"  ,{|x,y|xmlrpcstructNew({{"x",x},{"y",y}})})
    //server:addmethod("sample.struct"  ,{||objectNew(objectClass())})
    server:addmethod("sample.array"   ,{|x,y|{x,y}})
    server:addmethod("sample.b64"     ,{|x|xmlrpcbase64(x)})
    
    server:closeblock({|srv,sck|qout("Closed:",sck)})

    server:loopfreq:=5000 //msec
    server:loopblock({|srv|qout("loop",time())})
    
    server:loop

*****************************************************************************
