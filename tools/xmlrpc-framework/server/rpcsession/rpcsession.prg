
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

//XMLRPC session manager 

#ifdef NOT_DEFINED
    login(uid,pwd) --> sid
        xmlrpcsessionerror(incorrect password)

    logout(sid) --> NIL
        xmlrpcinvalidsiderror

    getversion(sid) --> version
        xmlrpcinvalidsiderror

    validate(sid,prolong) --> t/f

    validatex(sid,prolong) --> session
        xmlrpcinvalidsiderror
    
    gettimeout(sid) --> timeout
        xmlrpcinvalidsiderror

    who(sid) -> {s:uid,s:tid,s:start} (prolong)
        xmlrpcinvalidsiderror

    permission(sid,module) --> perm/{{met,perm}...} (prolong)
        xmlrpcinvalidsiderror

    groupid(sid) --> gid (prolong)
        xmlrpcinvalidsiderror

    userid(sid) --> uid  (prolong)
        xmlrpcinvalidsiderror

    username(sid) --> name (prolong)
        xmlrpcinvalidsiderror

    usertype(sid) -->tid (prolong)
        xmlrpcinvalidsiderror
#endif


#include "table.ch"
#include "_rpcauth.ch"
#include "_rpcuser.ch"

#include "rpcsession.ver"

*****************************************************************************
function main(iface_port)

local server

    set printer to log-rpcsession additive
    set printer on
    set console off
    set dosconv fileshare

    alertblock({|t,a|xmlrpc_alert(t,a)})

    RPCUSER:open(OPEN_READONLY);  RPCUSER:control:="user"
    RPCAUTH:open(OPEN_READONLY);  RPCAUTH:control:="tid"

 
    server:=xmlrpcserverNew(iface_port) 
    server:keepalive:=.t.
    //server:debug:=.t. 
    //server:recover:=.f.
 
    server:addmethod("session.login",{|u,p|login(u,p)})
    server:addmethod("session.logout",{|sid|logout(sid)})
    server:addmethod("session.getversion",{|sid|getversion(sid)})
    server:addmethod("session.validate",{|sid,prolong|validate(sid,prolong)})
    server:addmethod("session.validatex",{|sid,prolong|validatex(sid,prolong,.t.)})
    server:addmethod("session.gettimeout",{|sid|gettimeout(sid)})
    server:addmethod("session.who",{|sid|who(sid)})
    server:addmethod("session.permission",{|sid,module|permission(sid,module)})
    server:addmethod("session.groupid",{|sid|groupid(sid)})
    server:addmethod("session.userid",{|sid|userid(sid)})
    server:addmethod("session.username",{|sid|username(sid)})
    server:addmethod("session.usertype",{|sid|usertype(sid)})
    
    server:loopfreq:=5000
    server:loopblock:={||fflush()}
    server:closeblock:={|s,r|xmlrpc_verifyconnection(s,r)}

    xmlrpc_register(server,"session",VERSION)

    server:loop


*****************************************************************************
static function getversion(sid)  //verziószám
    validatex(sid)    
    return VERSION
 
*****************************************************************************
static function login(uid,psw)
local s:=rpcsessionNew(uid,psw)
    session_ini(s)
    return s:hash

*****************************************************************************
static function logout(sid)
    validatex(sid)
    session_out(sid)

*****************************************************************************
static function validate(sid,prolong)  //.t./.f.
    return session_get(sid,,prolong)  

*****************************************************************************
static function validatex(sid,prolong,load)  //exception
    return session_get(sid,.t.,prolong,load)
 
*****************************************************************************
static function gettimeout(sid)  //mekkora a timeout?
    validatex(sid)
    return xmlrpc_timeout() 
 
*****************************************************************************
static function who(sid) 
//egyszerűsítés: csak saját magát adja
local s:=validatex(sid,,.t.)
    return {{alltrim(s:uid),alltrim(s:tid),s:start}}

*****************************************************************************
static function permission(sid,module)
local s:=validatex(sid,,.t.), auth
    
    if( "."$module )
        if( RPCAUTH:seek( {s:tid,module} ) )
            auth:=RPCAUTH_PERMISSION
        end
       
    else
    
        RPCAUTH:seek({s:tid,module+="."})
        auth:={}
 
        while( !RPCAUTH:eof .and.;
               s:tid==alltrim(RPCAUTH_TID) .and.;
               module$RPCAUTH_METHOD  )

            aadd( auth, {alltrim(RPCAUTH_METHOD),RPCAUTH_PERMISSION} )
            RPCAUTH:skip
        end
    end

    return auth


*****************************************************************************
static function userid(sid)
    return alltrim(validatex(sid,,.t.):uid)

*****************************************************************************
static function usertype(sid)
    return alltrim(validatex(sid,,.t.):tid)
 
*****************************************************************************
static function groupid(sid)
local s:=validatex(sid,,.t.)
    return if(RPCUSER:seek({s:uid}),alltrim(RPCUSER_GID),NIL)
 
*****************************************************************************
static function username(sid)
local s:=validatex(sid,,.t.)
    return if(RPCUSER:seek({s:uid}),alltrim(RPCUSER_NAME),NIL)

*****************************************************************************

