
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

//XMLRPC teszt szerver
#define VERSION "1.2.00"  //2007.11.18 CCC3 port
//#define VERSION "1.0.01"
 
*****************************************************************************
function main(iface_port)

local server

    set printer to log-rpctest additive
    set printer on
    set console off
    alertblock({|t,a|xmlrpc_alert(t,a)})
    
    server:=xmlrpcserverNew(iface_port) 
    server:keepalive:=.t.
    //server:debug:=.t.
    //server:recover:=.f.
 
    server:addmethod("teszt.getversion",{||VERSION})
    server:addmethod("teszt.hello",{|sid|hello(sid)})
    server:addmethod("teszt.gettime",{|sid|gettime(sid)})
    server:addmethod("teszt.echo",{|sid,p1,p2,p3,p4,p5,p6|echo(sid,p1,p2,p3,p4,p5,p6)})

    server:closeblock:={|s,r|xmlrpc_verifyconnection(s,r)}
    server:loopfreq:=1000
    server:loopblock:={||fflush()}

    xmlrpc_register(server,"teszt",VERSION)
 
    server:loop

    return NIL


*****************************************************************************
static function hello(sid)
local un:=wrapper():call("session.username",{sid}) 
    return "Hello '"+upper(un)+"'!"


*****************************************************************************
static function gettime(sid)
    validate_session_id(sid)
    return time()


*****************************************************************************
static function echo(sid,p1,p2,p3,p4,p5,p6)
    validate_session_id(sid)
    return {p1,p2,p3,p4,p5,p6}
 

*****************************************************************************
static function  validate_session_id(sid)
local e
    if( !wrapper():call("session.validate",{sid,.t.}) )
        e:=xmlrpcinvalidsiderrorNew()
        break(e)
    end

*****************************************************************************
 



