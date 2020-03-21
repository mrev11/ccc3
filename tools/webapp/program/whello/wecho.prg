
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

***************************************************************************************
function main(sessionid,sckstr,*)

    printlog()
    //set console off
    ? {*}
    webapp.demo.defaults()

    //ez nagyon megterheli a böngészőt
    //a timeoutok tesztelésére hasznos
    webapp.debug(.f.)

    echotest()


***************************************************************************************
static function echotest()

local data,n,k:=0

    data:=a"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    data+=data::lower
    data::=replicate(2000)

    webapp.innerhtml("display_webapp","WEcho")

    while( k<1000  )
        for n:=-29 to 20
            echo( (++k)::str::alltrim::str2bin + data::left(126+n) )
            ?? k
        next
        for n:=-29 to 20
            echo( (++k)::str::alltrim::str2bin + data::left( 65535+n) )
            ?? k
        next

        webapp.innerhtml("display_webapp","WEcho"+str(k))
    next

    sleep(1000)
    

***************************************************************************************
static function echo(snd)
local rsp

    memowrit( "log-snd",snd )
    websocket.writemessage( webapp.ffsocket(), a"XCODE.echo('XX')"::strtran(a'XX',snd) )
    rsp:=websocket.readmessage( webapp.ffsocket() )

    if( rsp==NIL )
        ? "websocket closed"
        quit
    end
    memowrit( "log-rsp",rsp )

    if( snd==rsp )
        ? "egyezik  ", len(snd)
    else
        ? "eltér    ", len(snd)
        quit
    end


***************************************************************************************
    
    
