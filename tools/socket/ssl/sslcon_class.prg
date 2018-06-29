
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

#ifdef EMLEKEZTETO
  Burkoló objektum SSL socketekhez.
  A metódusok vissza vannak vezetve
  az sslcon_funif modulban levő függvényinterfészre.
  Az sslconAccept és sslconConnect sslerror-t dobhat.

  Az interfész megegyezik az socket-beli interfésszel. 
  Ez lehetővé teszi, hogy (az SSL bekapcsolásától eltekintve) 
  ugyanaz a kód képes legyen SSL-lel és anélkül működni.
  
  Úgy kell bekapcsolni az SSL-t, hogy
  kliens oldalon: connect után a plain socketet SSL-lé konvertáljuk,
  szerver oldalon: accept után a plain socketet SSL-lé konvertáljuk.
  
  Szerver:

    function server_main(sslflag)
    local ss,s,ctx

    ctx:=sslctxNew() 
    ctx:use_certificate_file("localhost.pem")
    ctx:use_privatekey_file("localhost.pem")

    ss:=socketNew()
    ss:bind("localhost",40000)
    ss:listen
    
    while( .t. )
        s:=ss:accept()

        if( sslflag!=NIL )        
            s:=sslconAccept(ctx,s) //s: plain socket --> SSL socket
        end
        
        ? s:recv(64) //plain VAGY ssl
        s:close
    end
    
  Kliens:

    function client_main(sslflag)
    local s,ctx

    ctx:=sslctxNew() 

    s:=socketNew()
    s:connect("localhost",40000)

    if( sslflag!=NIL ) 
        s:=sslconConnect(ctx,s) //s: plain socket --> SSL socket
    end

    s:send("Öt szép szűzlány őrült írót nyúz") //plain VAGY ssl
    s:close
#endif  

******************************************************************************
function sslconAccept(ctx,sck) //objektumgyártó: plain socket -> ssl socket
local scon,code,err
    scon:=sslconNew(ctx,sck)
    code:=sslcon_accept(scon:ssl,ctx:handshake_timeout)
    if( code!=1 )
        err:=sslerrorNew("sslconAccept")
        scon:close
        if(code==-1000) //saját hibakód
            err:description:="SSL_accept timeout"
            err:subcode:=0
        end
        break(err)
    end
    return scon

******************************************************************************
function sslconConnect(ctx,sck) //objektumgyártó: plain socket -> ssl socket
local scon,code,err
    scon:=sslconNew(ctx,sck)
    code:=sslcon_connect(scon:ssl)
    if( code!=1 )
        err:=sslerrorNew("sslconConnect")
        scon:close
        break(err)
    end
    return scon

******************************************************************************
class sslcon(socket)
    attrib ctx
    attrib ssl
    method initialize
    method accept
    method connect
    method session_reused

    method send
    method recv
    method pending
    method waitforrecv
    method recvall

    method shutdown
    method close
    
    //örökölve
    //attrib fd
    //method reuseaddress
    //method bind
    //method listen

******************************************************************************
static function sslcon.initialize(this,context,sck)
    this:ctx:=context
    this:ssl:=sslcon_new(this:ctx:handle)
    if( valtype(sck)=="N" )
        this:fd:=sck
    elseif( valtype(sck)=="O" )
        this:fd:=sck:fd
    else
        this:fd:=socket()
    end
    sslcon_set_fd(this:ssl,this:fd)
    return this

******************************************************************************
static function sslcon.accept(this)  //objektumgyártó!
local scon,fd,code,err
    fd:=.accept(this:fd)
    if( fd<0 )
        err:=socketerrorNew("sslcon.accept")
        err:description:="accept failed"
        break(err)
    end
    scon:=sslconNew(this:ctx,fd)
    code:=sslcon_accept(scon:ssl,this:ctx:handshake_timeout)
    if( code!=1 )
        err:=sslerrorNew("sslcon.accept")
        scon:close
        if(code==-1000)//saját hibakód
            err:description:="SSL_accept timeout"
            err:subcode:=0
        end
        break(err)
    end
    return scon //sslcon objektum

******************************************************************************
static function sslcon.connect(this,host,port) 
local code,err
    code:=.connect(this:fd,host,port)
    if( code!=0 )
        err:=socketerrorNew("sslcon.connect")
        err:description:="connect failed"
        err:args:={this:fd,host,port}
        break(err)
    end
    code:=sslcon_set_tlsext_host_name(this:ssl,host)
    if( code!=1 )
        err:=sslerrorNew("sslcon.connect")
        err:description:="unable to set TLS servername extension"
        err:args:={this:fd,host,port}
        break(err)
    end
    code:=sslcon_connect(this:ssl)
    if( code!=1 )
        err:=sslerrorNew("sslcon.connect")
        this:close
        break(err)
    end
    return code

******************************************************************************
static function sslcon.session_reused(this)
    return 1==sslcon_session_reused(this:ssl)

******************************************************************************
static function sslcon.send(this,buffer)
local len1:=0,buf,len,nbyte
    buf:=str2bin(buffer)
    len:=len(buf)
    nbyte:=sslcon_write(this:ssl,buf)
    while( 0<=nbyte .and. (len1+=nbyte)<len )
        nbyte:=sslcon_write(this:ssl,substr(buf,len1+1))
    end
    return len1

******************************************************************************
static function sslcon.recv(this,nbyte,timeout)
    return sslcon_read(this:ssl,nbyte,timeout)

******************************************************************************
static function sslcon.pending(this)
    return sslcon_pending(this:ssl)

******************************************************************************
static function sslcon.waitforrecv(this,wtime)
    return 0<this:pending .or. 0<select({this:fd},,{this:fd},wtime)

******************************************************************************
static function sslcon.recvall(this,wtime)
local buf:=a"",inc
    if( empty(wtime) .or. this:waitforrecv(wtime) )
        while( 0<len(inc:=this:recv(4096,0)) )
            buf+=inc
        end
        if( inc==NIL .and. len(buf)==0 )
            buf:=NIL
        end
    end
    return buf

******************************************************************************
static function sslcon.shutdown(this)
    return sslcon_shutdown(this:ssl)

// "close notify" üzenetet küld a peernek (ezzel csak baj van)
// "jónak" minősíti a session-t, amitől az megmarad a cache-ben
// a shutdown nélküli SSL_free a session-t a cache-ből is törli,
// tehát shutdown nélkül nem működik a cache

******************************************************************************
static function sslcon.close(this)
    sclose(this:fd)
    if( this:ssl!=NIL )
        sslcon_free(this:ssl)
        this:ssl:=NIL
    end

******************************************************************************
    