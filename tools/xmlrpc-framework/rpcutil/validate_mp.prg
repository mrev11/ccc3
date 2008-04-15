
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

#include "table.ch"
#include "_session.ch"


// A session szerver az xmlrpc_timeout()-nál hosszabb ideig inaktív 
// session-t érvényteleníti. A közönséges szerverek xmlrpc_timeout()/3
// ideig saját hatáskörben validálják a sessiont, utána megkérdezik 
// a session szervert. Így a session biztonságosan életben van tartva, 
// mégsem piszkáljuk feleslegesen sokat a session szervert.

// Minden szerver definiálja a session_create_object(sid) függvényt, 
// ami legyártja az adott szerverre jellemző session objektumot.


static VERIFTIME:=xmlrpc_timeout()/3
 
*****************************************************************************
static function initialize()
    dirmake("rpcbase")
    //SESSION:path:="rpcbase"
    //SESSION:file:="rpcsession"
    SESSION:create
    SESSION:open(OPEN_SHARED)
    SESSION:control:="sid"

*****************************************************************************
function  session_validate_mp(sid,srvname,accessmode)

// sid
// 24 byte-os session azonosító (base64(md5))

// srvname
// a szolgáltatás neve, pl. "arcforg"

// accessmode
// 1) NIL: ellenőrzi sid-et, de nem tölti be a session objektumot 
//
// 2) .f./0/"": ellenőrzi sid-et, beolvassa a session objektumot  
//
// 3) "r"/"m"/"d"/"a": ellenőrzi sid-et, beolvassa a session objektumot,
//    ellenőrzi a read/modify/delete/append jogosultságot


static ini:=.f.
local e,s,t:=seconds() 

    if( !ini ) 
        initialize() 
        ini:=.t.
    end

    if( !SESSION:seek({sid,srvname}) )
    
        if( !wrapper():call("session.validate",{sid,.t.}) )
            e:=xmlrpcinvalidsiderrorNew("session_validate_mp")
            e:args:={sid}
            break(e)
        end

        s:=session_create_object(sid)
        s:seconds:=t
        session_append(s)

    elseif( t-SESSION_SECONDS>VERIFTIME )
        
        if( !wrapper():call("session.validate",{sid,.t.}) )
            e:=xmlrpcinvalidsiderrorNew("session_validate_mp")
            e:args:={sid}
            break(e)
        end

        SESSION:rlock
        SESSION_SECONDS:=t
        SESSION:unlock
    end
        
    if( s==NIL .and. accessmode!=NIL )
        s:=session_load()
        s:seconds:=t
    end

    if( !empty(accessmode) )
        s:access(accessmode)
    end
    
    return s

*****************************************************************************
static function session_append(s)
    SESSION:append
    SESSION_SID      := s:sid
    SESSION_SRVNAME  := s:srvname
    SESSION_SECONDS  := s:seconds
    SESSION_UID      := s:userid
    SESSION_TID      := s:usertype
    SESSION_DATETIME := dtos(date())+time()
    SESSION_DBMDATA  := arr2bin(s:asarray)
    SESSION:unlock
    return s

*****************************************************************************
static function session_load()
local a:=bin2arr(SESSION_DBMDATA)
local s:=session_create_object(a)
    return s

*****************************************************************************
function session_store(s)
local e
    SESSION:rlock
    if( SESSION_SID!=s:sid .or. SESSION_SRVNAME!=s:srvname )
        e:=xmlrpcsessionerrorNew()
        e:operation:="session_store"
        e:description:="wrong position"
        break(e)
    end
    SESSION_DBMDATA:=arr2bin(s:asarray)
    SESSION:unlock
    return s
 
*****************************************************************************

 