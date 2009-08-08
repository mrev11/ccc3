
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

#include "spawn.ch"
#include "ssl.ch"

static sck  //kapcsolat a terminállal

static jtsocket
static jtssl:=.f.
static jtkey
static jtca
static jtdebug:=.f.
static jtauto:=.f.
 
****************************************************************************
#ifdef MEGJEGYZES //a -jtsocket opció használatához
    1. -jtsocket s 
    
    Ahol s a parent-től örökölt socket.

    A listener így indítja a szervert: 
        run( torun+str(c)+" &" )
    ahol c az acceptnél kapott socket. Ha torun-ba ezt rakjuk:
        "main.exe -jtsocket" 
    akkor éppen a -jtsocket után következik a socket paraméter.

    2. -jtsocket ip:port  
    
    A program az ip:port címen hallgatózik, és az ide érkező
    connect-ből képződik a socket. Ez alkalmassá teszi a programokat
    listener nélküli használatra.

#endif

****************************************************************************
function jtsocket(setsck)
local n, e

    if( setsck!=NIL )
        sck:=setsck

    elseif( sck==NIL )

        for n:=1 to argc()-1
            if( "-jtsocket"==argv(n) )
                jtsocket:=argv(n+1)
            elseif( "-jtauto"==argv(n) )
                jtauto:=.t.
            elseif( "-jtssl"==argv(n) )
                jtssl:=.t.
            elseif( "-jtkey"==argv(n) )
                jtssl:=.t.
                jtkey:=argv(n+1)
            elseif( "-jtca"==argv(n) )
                jtssl:=.t.
                jtca:=argv(n+1)
            elseif( "-jtdebug"==argv(n) )
                jtdebug:=.t.
            end
        next 
        
        if( jtauto )
            jtautostart()
        elseif( !empty(jtsocket) )
            sck:=jtsocketNew( jtsocket )
        elseif( !empty(getenv("JTSOCKET")) )
            sck:=jtsocketNew( getenv("JTSOCKET")  )
        else
            jtautostart()
        end
        
        //Itt még számításba jönne konnektálni egy listenerhez,
        //ami indítaná a terminált, csakhogy nem tudom, hogyan
        //kaphatná meg az örökölt socketet a Jáva program.

        if( getenv("JTDEBUG")=="on" )
            jtdebug:=.t.
        end
 
        if( sck==NIL )
            e:=socketerrorNew()
            e:operation:="jtsocket"
            e:description:="no socket"
            break(e)
        end
    end

    return sck


****************************************************************************
function jtautostart()

//Ha egy  program valahol az elején meghívja a jtautostart() függvényt, 
//akkor az keres egy szabad portot, ezen a porton fogja várni a jterminal
//konnektálását, egyúttal el is indítja a terminált úgy, hogy kapcsolódjon
//erre a portra. A JTERMINAL változóban kell megadni jterminal.jar helyét.

local s:=socket(),p,c
local jterminal:=getenv("JTERMINAL")
local cnt:=0

    if( empty(jterminal) )
        ? "jtautostart: JTERMINAL not set" 
        ?
        quit
    end

    rand(gettickcount())
    p:=numor(0xf000,random())
    while( 0>bind(s,"127.0.0.1",p) )
        p:=numor(0xf000,random())
        if( ++cnt>1024 )
            ? "jtautostart: no free port" 
            ?
            quit
        end
    end
    
    //? "port",p,cnt; inkey(1)

    if( 0>listen(s) )
        ? "jtautostart: listen failed", p
        ?
        quit
    end
    
    //Hiba, hogy itt más processz is konnektálhat!

    spawn(SPAWN_NOWAIT+SPAWN_PATH,"java","-jar",jterminal,"127.0.0.1",alltrim(str(p)))
            
    if( 0>(c:=accept(s)) )
        ? "jtautostart: accept failed", p
        ?
        quit
    end

    sclose(s) //listener
    jtssl:=.f.
    sck:=jtsocketNew(str(c))

****************************************************************************
class jtsocket(object) 
    method  initialize
    method  send
    method  recv
    attrib  connection
    method  socket          {|this|this:connection:fd} //compatibility

    attrib  queue
    method  enqueue
    method  dequeue

****************************************************************************
static function jtsocket.initialize(this,s) 
local ss, ip, port, ctx

    this:(object)initialize

    if( ":"$s ) //s=ip:port

        if( empty(ip:=left(s,at(":",s)-1)) )
            ip:="127.0.0.1"
        end
        port:=val(substr(s,at(":",s)+1))

        ss:=socketNew()
        //ss:reuseaddress(.t.)
        ss:bind(ip,port)
        ss:listen
        this:connection:=ss:accept
        ss:close
        //? "accepted socket",this
    
    else //s=örökölt socket 
        this:connection:=socketNew(val(s))
        //? "inherited socket",this
    end

    #ifdef SSL_SUPPORT
    if( jtssl )    
        //socket -> sslcon
        this:connection:=sslconAccept(ssl_context(),this:connection)
    end
    #endif //SSL_SUPPORT
    
    this:queue:={}
    
    return this

****************************************************************************
static function jtsocket.send(this,xx)

local x:=str2bin(xx)
local hdr1:=str2bin(padl(alltrim(str(len(x))),8,"0"))
local hdr2:=str2bin(padl(alltrim(right(str(crc(x)),8)),8,"0"))
local err, nbyte

    nbyte:=this:connection:send(hdr1+hdr2+x)

    if( nbyte!=len(x)+16 )
        err:=socketerrorNew()
        err:operation:="jtsocket.send"
        err:description:="send failed"
        err:subcode:=nbyte
        err:args:={xx}
        break(err)
    end
    
    if( jtdebug )
        ? ">>>send:",x
    end

    return nbyte

****************************************************************************
static function jtsocket.recv(this,wtime)

local hdr1
local hdr2
local x, err

    if( NIL!=wtime .and.; 
        this:connection:pending==0 .and.;
        0==select({this:connection:fd},,,wtime) )
        return ""
    end

    hdr1:=this:connection:recv(8)
    hdr2:=this:connection:recv(8)
 
    if( hdr1==NIL .or. hdr2==NIL )
        return NIL
    end

    x:=this:connection:recv(val(hdr1)) 

    if( !hdr2==str2bin(padl(alltrim(right(str(crc(x)),8)),8,"0")) )
        ? this:connection
        ? "hdr1",hdr1
        ? "hdr2",hdr2
        ? "crc ",str2bin(padl(alltrim(right(str(crc(x)),8)),8,"0")), crc(x)
        ? "len",len(x)

        err:=socketerrorNew()
        err:operation:="jtsocket.recv"
        err:description:="recv failed"
        err:subcode:=ferror()
        break(err)
    end
    
    if( jtdebug )
        ? ">>>recv:",x
    end

    return x

****************************************************************************
static function jtsocket.enqueue(this,x)
local err
    //? "ENQUEUE"
    if( len(this:queue)>32 ) 
        //támadás?
        err:=apperrorNew()
        err:operation:="jtsocket.enqueue"
        err:description:="queue overflow"
        err:args:=this:queue
        break(err)
    end
    aadd(this:queue,x)

****************************************************************************
static function jtsocket.dequeue(this)
local x
    if( !empty(this:queue) )
        //? "DEQUEUE"
        x:=this:queue[1]
        adel(this:queue,1)
        asize(this:queue,len(this:queue)-1)
    end
    return x

****************************************************************************
static function crc(x)
local n, sum:=0,c
    for n:=1 to len(x)
        sum+=(c:=asc(substr(x,n,1)))
    next
    return sum


****************************************************************************
static function ssl_context()
#ifdef SSL_SUPPORT
local ctx

    ctx:=sslctxNew() 
    if( jtkey!=NIL )
        ctx:use_certificate_file(jtkey)
        ctx:use_privatekey_file(jtkey)
    else
        ctx:use_certificate_file("server.pem")
        ctx:use_privatekey_file("server.pem")
    end
    if( jtca!=NIL )
        ctx:set_verify(SSL_VERIFY_PEER_CERT)
        ctx:set_verify_depth(1)
        ctx:load_verify_locations(jtca)
        ctx:load_client_ca_file(jtca)
    end
    //? "ssl_context",ctx
    return ctx

#endif //SSL_SUPPORT

****************************************************************************
