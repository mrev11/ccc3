
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

//tárolja/előszedi a session adatokat

#include "table.ch"
#include "_session.ch"

#define TIMEOUT  xmlrpc_timeout()

*****************************************************************************
static function initialize() //táblát kreál, ha nincs
static ini:=.f.

    if( ini )
        return NIL
    end
    ini:=.t.

    dirmake("rpcbase")
    //SESSION:path:="rpcbase"
    //SESSION:file:="session"
    SESSION:create

    //"set dosconv fileshare" kell minimum
    if( SESSION:open(OPEN_EXCLUSIVE,{||.f.}) )
        SESSION:zap
    end

    SESSION:open(OPEN_SHARED)
    SESSION:control:="sid"

*****************************************************************************
function session_ini(s) //letárol egy session objektumot

    initialize() 

    SESSION:append
    SESSION_SID      := s:hash
    SESSION_SRVNAME  := "session"
    SESSION_SECONDS  := s:seconds
    SESSION_UID      := s:uid
    SESSION_TID      := s:tid
    SESSION_DATETIME := dtos(date())+time()
    SESSION_DBMDATA  := arr2bin(s:asarray)
    SESSION:unlock

    ? getpid(), "app", SESSION_SID, SESSION:position
    
*****************************************************************************
function session_out(sid) //érvénytelenít egy sid-et

    initialize() 

    SESSION:seek(sid)
    while( !SESSION:eof .and. alltrim(SESSION_SID)==sid )

        ? getpid(), "out", SESSION_SID, SESSION:position

        SESSION:rlock
        SESSION_SECONDS:=0
        SESSION:unlock
        SESSION:skip
    end

*****************************************************************************
function  session_get(sid,errflag,prolongflag,loadflag) //ellenőriz/előszed egy sessiont
local valid, sec, result

    initialize() 
 
    valid := valtype(sid)$"XC" .and.;
             SESSION:seek({sid,"session"}) .and.;
             (sec:=seconds())>=SESSION_SECONDS .and.;
             (sec-SESSION_SECONDS)<TIMEOUT 
 
    if( !valid .and. errflag==.t. )
        ? getpid(), "err", sid
        xmlrpc_invalidsid(sid)
    end

    if( valid .and. prolongflag==.t. )
        SESSION:rlock
        SESSION_SECONDS:=seconds()
        SESSION:unlock
    end
    
    if( !loadflag==.t. )
        result:=valid
    elseif( valid )
        result:=rpcsessionNew(bin2arr(SESSION_DBMDATA)) 
    else
        result:=NIL
    end
    
    sleep(20) //debug

    return result  //.t./.f./object/NIL
 
*****************************************************************************

 