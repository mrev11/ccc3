
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
  Burkoló objektum socketekhez.
  A metódusok közvetlenül vissza vannak vezetve
  a ccc3_socket könyvtárban levő függvényinterfészre.
  A bind,listen,accept,connect hiba esetén socketerror-t dob.

  Az interfész megegyezik az sslcon-beli interfésszel. 
  Ez lehetővé teszi, hogy (az SSL bekapcsolásától eltekintve) 
  ugyanaz a kód képes legyen SSL-lel és anélkül működni.
  
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
class socket(object)
    attrib fd
    method initialize
    method inherit
    method reuseaddress
    method bind
    method listen
    method accept
    method connect
    method send
    method recv
    method pending
    method waitforrecv
    method recvall
    method close

******************************************************************************
static function socket.initialize(this,fd)    
    if( fd==NIL )
        this:fd:=socket()
    else
        this:fd:=fd
    end
    return this

******************************************************************************
static function socket.inherit(this,inheritflag)

local prev,success,e

#ifdef NOT_DEFINED
    //Ennek hibái vannak:
    //XP-n socketre nem működik a hdup,
    //nincs lekérdezés,
    //kicserélődik a socket az objektumban.

    #ifdef _UNIX_
        this:fd:=fdup(this:fd,inheritflag,.t.)
    #else
        this:fd:=hdup(this:fd,inheritflag,.t.)
    #endif
    if( this:fd<0 )
        e:=socketerrorNew("socket.inherit")
        e:description("duplicate socket failed")
        break(e)
    end

#else

    #ifdef _UNIX_
        prev:=!getcloexecflag(this:fd) //fordítani!
    #else //_WINDOWS_
        prev:=gethandleinheritflag(this:fd)
    #endif

    if( inheritflag!=NIL ) 
        //beállítás
        #ifdef _UNIX_
            success:=setcloexecflag(this:fd,!inheritflag) //fordítani!
        #else //_WINDOWS_
            success:=sethandleinheritflag(this:fd,inheritflag)
        #endif

        if( !success )
            e:=socketerrorNew("socket.inherit")
            e:description("failed")
            break(e)
        end
    end

    return prev
#endif

******************************************************************************
static function socket.reuseaddress(this,flag) 
    setsockopt(this:fd,"REUSEADDR",flag)

******************************************************************************
static function socket.bind(this,iface,port) 
local code,err
    if( iface==NIL )
        code:=.bind(this:fd,port)
    else
        code:=.bind(this:fd,iface,port)
    end
    if( code!=0 )
        err:=socketerrorNew("socket.bind")
        err:description:="bind failed"
        err:args:={this:fd,iface,port}
        break(err)
    end
    return code

******************************************************************************
static function socket.listen(this,len) 
local code,err
    code:=.listen(this:fd,len)
    if( code!=0 )
        err:=socketerrorNew("socket.listen")
        err:description:="listen failed"
        err:args:={this:fd,len}
        break(err)
    end
    return code

******************************************************************************
static function socket.accept(this)  //objektumgyártó!
local fd,err
    fd:=.accept(this:fd)
    if( fd<0 )
        err:=socketerrorNew("socket.accept")
        err:description:="accept failed"
        break(err)
    end
    return socketNew(fd)

******************************************************************************
static function socket.connect(this,host,port) 
local code,err
    code:=.connect(this:fd,host,port)
    if( code!=0 )
        err:=socketerrorNew("socket.connect")
        err:description:="connect failed"
        err:args:={this:fd,host,port}
        break(err)
    end
    return code

******************************************************************************
static function socket.send(this,buffer)
local len1:=0,buf,len,nbyte
    buf:=str2bin(buffer)
    len:=len(buf)
    nbyte:=swrite(this:fd,buf)
    while( 0<=nbyte .and. (len1+=nbyte)<len )
        nbyte:=swrite(this:fd,substr(buf,len1+1))
    end
    return len1

******************************************************************************
static function socket.recv(this,nbyte,timeout)
    return sread(this:fd,nbyte,timeout)

******************************************************************************
static function socket.pending(this)
    return sready(this:fd)

******************************************************************************
static function socket.waitforrecv(this,wtime)
    return 0<this:pending .or. 0<select({this:fd},,{this:fd},wtime)

******************************************************************************
static function socket.recvall(this,wtime)
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
static function socket.close(this)
    sclose(this:fd)

******************************************************************************
