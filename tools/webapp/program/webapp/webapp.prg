
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

#include "webapp.ch"

static brwsocket
static appsocket


***************************************************************************************
function main()
local err,sck

    set alternate to log-webapp additive
    set alternate on

    set date format "yyyy-mm-dd"
    signalblock({|s|sighandler(s)})

    if( param_ssl() )
        ssl_context()
    end

    sck_listener():listen
    while(.t.)
        if( 0<select({sck_listener()},,,10*1000) )
            begin
                sck:=sck_listener():accept
            recover err <socketerror>
                ? err:description
                loop
            end

            if( fork()==0 ) 
                //child
                sck_listener():close
                dofork(sck)
            else
                //parent
                sck:close
            end
        end
        while(0<waitpid(,,1));end //zombi takarítás, 1==WNOHANG
    end


***************************************************************************************
static function dofork(sck)

local sel:={},n,err

    set alternate to log-webapp additive
    set alternate on

    ? "ACCEPT ",date(),time(),getpeername(sck:fd),sck:fd,getpid(), if(param_ssl(),"SSL","")
    quitblock({||qout("QUIT",getpid())})

    if( param_ssl() )
        begin
            brwsocket:=sslconAccept(ssl_context(),sck) //ssl
        recover err <sslerror>
            ? err:operation, err:description
            quit
        end
    else
        brwsocket:=sck //plain
    end

    while(.t.)

        sel:={brwsocket}
        if(appsocket!=NIL)
            aadd(sel,appsocket)
        end

        dbgsel(chr(10)+"sel",sel)
        select(sel)
        dbgsel("-->",sel)

        for n:=1 to len(sel)
            socket_event(sel[n])
        next
    end


***************************************************************************************
static function socket_event(sck)
local req,wsuri,page,msg

    if( appsocket==NIL  )
        req:=http_readmessage(brwsocket,10000)

        if( req==NIL )
            ? "FAKE",getpid()
            quit

            //Az FF egyből egy csomó connecttel támad, aztán rájön,
            //hogy a connectek egy része felesleges, ezeket lezárja (req==NIL).
            //Legalább udvarias: Lejátssza az SSL handshake-et, csak azután bont,
            //ezért nem az sslconAccept-ben száll el a szerver.

            //Megfigyelés: A felesleges connectek rögtön az első 0.5 sec-ben
            //beesnek, azonban csak 4-5 sec múlva jönnek ki a sslconAccept-ból.
            //A http_readmessage timeoutjából semmi sem fogy, azonnal észleli
            //a kapcsolat lezáródását.
        end

        ? "REQUEST", brwsocket:fd, requrl(req), http_body(req)::left(32)

        if( req::startswith(a"GET /webapp ") )
            if( param_ssl() )
                wsuri:=a"wss://" //ssl
            else
                wsuri:=a"ws://" //plain
            end
            wsuri+=http_getheader(req,"host")+a"/websocket"
            brwsocket:send( page_main(wsuri) )
            brwsocket:close
            quit

        elseif( req::startswith(a"GET /websocket ") )
            brwsocket:send(websocket.handshake(req))
            start_session()

        elseif( req::startswith(a"GET /webapp/dnload/") )
            //session file request
            page:=sessiondata(req)
            if( page!=NIL )
                brwsocket:send(page)
            else
                brwsocket:send(empty_response("404 Not Found"))
            end
            brwsocket:close
            quit

        elseif( (page:=commondata(req))!=NIL )
            //common file request, e.g. favicon.ico
            brwsocket:send(page)
            brwsocket:close
            quit
            
        else
            brwsocket:send(empty_response("404 Not Found")) 
            brwsocket:close
            quit
        end

    elseif( sck==brwsocket )
        //forward: brw -> app
        if( (msg:=brwsocket:recvall)!=NIL )
            appsocket:send(msg)
        else
            appsocket:close
            quit //brw kilépett
        end

    elseif( sck==appsocket )
        //forward: app -> brw
        if( (msg:=appsocket:recvall)!=NIL )
            brwsocket:send(msg)
        else
            brwsocket:send(x"8800")  //websocket close
            brwsocket:close
            quit //app kilépett
        end
    end
    

***************************************************************************************
static function start_session()

local sp:=unix_socketpair() //{sa,sc}  plain fd-k
local sid:=sessionid()
local pid,n
//local env0,env1

    appsocket:=socketNew(sp[2]) //plain

    pid:=fork()

    if( pid==0 )
        //itt le kell zárni azokat a dolgokat,
        //amik nem kellenek az alkalmazásnak
        
        brwsocket:close
        sclose(sp[2])

        exec(param_exec(),sid,sp[1]::str::alltrim,.t.)
        //ide csak akkor jön, ha nem sikerült az exec
        ? "exec-error",param_exec()
        quit
    else
        sclose(sp[1])
    end


***************************************************************************************
function sessionid() //egyedi session id-t generál
local sid
    sid:=getpid()::str::alltrim::str2bin
    sid+=date()::dtos::str2bin
    sid+=time()::str2bin
    sid+=crypto_rand_pseudo_bytes(8)
    sid::=crypto_md5::crypto_bin2hex
    return sid  //X típus



***************************************************************************************
static function dbgsel(txt,sel)
#ifdef NOTDEFINED
local n
    ?? txt, "("
    for n:=1 to len(sel)
        if( n>1 )
            ?? ","
        end
        ?? sel[n]:fd::str::alltrim,sel[n]:classname
    next
    ?? ") "
#endif

***************************************************************************************
