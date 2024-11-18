
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

namespace websocket


***************************************************************************************
function handshake(hsreq) //handshake request

local hsrsp:=<<HANDSHAKE>>HTTP/1.1 101 Switching Protocols
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Accept: ACCEPTKEY

<<HANDSHAKE>>::str2bin

local magic:=a"258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
local wsv,wse,key,akey

    wsv:=http_getheader(hsreq,"Sec-WebSocket-Version")
    wse:=http_getheader(hsreq,"Sec-WebSocket-Extensions")
    key:=http_getheader(hsreq,"Sec-WebSocket-Key")

    wsv:=if(empty(wsv),"",wsv::bin2str)
    wse:=if(empty(wse),"",wse::bin2str)

    putenv("Sec-WebSocket-Version="+wsv)
    putenv("Sec-WebSocket-Extensions=")

    akey:=key
    akey+=magic
    akey::=crypto_sha1()
    akey::=base64_encode

    hsrsp::=strtran("ACCEPTKEY",akey)
    
    hsrsp::=strtran(x"0d",x"")
    hsrsp::=strtran(x"0a",x"0d0a")  // Chromium!

    if( param_permessage_deflate() .and. "permessage-deflate"$wse )
        //akkor jon ide, ha a bongeszo engedi a tomoritest
        //az alabbi valasszal a szerver beleegyezik a tomoritesbe 
        //a tomorites RSV1 bitben uzenetenkent kibekapcsolhato

        hsrsp::=http_setheader("Sec-WebSocket-Extensions","permessage-deflate; client_no_context_takeover; server_no_context_takeover")
        putenv("Sec-WebSocket-Extensions="+wse)

        //nem tudom megoldani azt a problemat
        //hogy a tomorites folytatolagosan mukodik (a bongeszoben)
        //de a tomorites allapotat (a zstream strukturat es nyulvanyait)
        //nem lehet atadni a child processeknek
        //ezert egyelore ki van kapcsolva a tomorites
    end

    ? "HANDSHAKE"
    
    //memowrit("handshake_req",hsreq)
    //memowrit("handshake_rsp",hsrsp)
    
    return hsrsp  //handshake response  (X típus)


***************************************************************************************
