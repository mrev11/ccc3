
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

//XMLRPC wrapper (forgalom iranyito)

#include "ssl.ch"
#include "rpcwrapper.ver"

static starttime:=time()
static listener:={}     // listener objektumok
static con:={}          // connection objektumok  
static queue:={}        // sorban allo requestek {{client,request,module},...} 

static keyfile
static cafile
static capath
static sslcontext
static reuseaddress:=.f.

*****************************************************************************
static function errorhandler(e)
    
    if( valtype(e)!="O" )
        //nem objektum
        ? e

    elseif( !e:isderivedfrom(errorClass()) ) 
        //objektum, de nem error leszarmazott
        ? e

    elseif( getclassid(e)!=errorClass() )
        //error leszarmazott, de nem error
        ? e:classname, e:operation, e:description

    else
        //error
        ? "ERROR", e
        callstack()
        varstack()
    end

*****************************************************************************
function main()

local opt:=aclone(argv())
local sck,c,n,i,e

    set date format "yyyy.mm.dd"
    set alternate to log-rpcwrapper additive
    set alternate on
    //set console off
    alertblock({|t,a|xmlrpc_alert(t,a)})
    breakblock({|e|errorhandler(e)})

    for n:=1 to len(opt)
        if( opt[n]=="-l" .or. opt[n]=="--listener" )
            aadd(listener,listenerNew(opt[++n]))
        elseif( opt[n]=="-k" .or. opt[n]=="--key" )
            keyfile:=opt[++n]
        elseif( opt[n]=="--cafile" )
            cafile:=opt[++n]
        elseif( opt[n]=="--capath" )
            capath:=opt[++n]
        elseif( opt[n]=="--reuseaddr" )
            reuseaddress:=.t.
        else
            usage()
        end
    end
    
    if( empty(listener) )
        usage()
    end

    ? ">>>", date(), time(), "start"

    while( .t. )
    
        sck:=array(len(listener)+len(con))
        for i:=1 to len(listener)
            n:=i
            sck[n]:=listener[i]
        next
        for i:=1 to len(con)
            n:=len(listener)+i
            sck[n]:=con[i]
        next
        
        select(sck,,,5000)

        for n:=1 to len(sck)

            if( 0<ascan(listener,sck[n]) )
                begin
                    aadd(con,connectionNew(c:=sck[n]:accept))
                    sck[n]:counter++
                recover e
                    ? e
                end
            else
                sck[n]:timeout:=seconds()
                begin
                    sck[n]:read 
                recover e <socketerror>
                    sck[n]:destruct
                recover e <apperror>
                    sck[n]:destruct
                recover e 
                    //egyeb hiba
                    //az error-okat errorhandler logolja
                end
            end
        next
        
        if( len(sck)==0 )
            for n:=len(con) to 1 step -1
                if( con[n]:module==NIL .and.;
                    seconds()-con[n]:timeout>xmlrpc_timeout() )
                    con[n]:destruct(n)
                end
            next
        end

        fflush()
    end

*****************************************************************************
static function usage()
    ? "Usage: rpcwrapper [--key <keyfile>] [--cafile <cafile>] [--capath <capath>] [--reuseaddr] --listener [iface]:port[:ssl] ..."
    ?
    quit

*****************************************************************************
class listener(object)
    method  initialize
    method  fd
    method  accept
    method  bind
    method  listen
    method  address

    attrib  socket
    attrib  iface
    attrib  port
    attrib  counter

*****************************************************************************
static function listener.initialize(this,opt)
local iface,port,ssl,e

    this:(object)initialize

    opt:=split(opt,":")
    asize(opt,3)
    iface:=opt[1]
    port:=val(opt[2])
    ssl:=opt[3]

    if( empty(iface) )
        iface:=NIL
    else
        if( NIL==(iface:=gethostbyname(iface)) )
            e:=socketerrorNew()
            e:description("gethostbyname failed")
            e:operation("listener.initialize")
            break(e)
        end
    end
   
    if( empty(ssl) )
        this:socket:=socketNew()
    elseif( upper(alltrim(ssl))=="PLAIN" )
        this:socket:=socketNew()
    elseif( upper(alltrim(ssl))=="SSL" )
        if( sslcontext==NIL )
            sslcontext:=makeSSLcontext()
        end
        this:socket:=sslconNew(sslcontext)
    else
        usage()
    end

    this:iface:=iface
    this:port:=port
    this:counter:=0
    if(reuseaddress==.t.)
        this:socket:reuseaddress(.t.)
    end
    this:bind
    this:listen(20)
    return this

*****************************************************************************
static function listener.fd(this)
    return this:socket:fd

static function listener.accept(this)
    return this:socket:accept

static function listener.bind(this)
    return this:socket:bind(this:iface,this:port)

static function listener.listen(this,q)
    return this:socket:listen(q)

static function listener.address(this)
local iface
    if( this:iface==NIL )
        iface:=""
    else
        iface:=bin2str(this:iface)
    end
    return iface+":"+alltrim(str(this:port))

*****************************************************************************
static function makeSSLcontext()
local sslcontext:=sslctxNew()
    sslcontext:use_certificate_file(keyfile)
    sslcontext:use_privatekey_file(keyfile)
    sslcontext:check_private_key
    sslcontext:set_session_id_context("rpcwrapper") //CCC default=argv(0)+pid
    //sslcontext:session_cache_mode:=0 //default=SSL_SESS_CACHE_SERVER
    //sslcontext:session_cache_timeout:=60 //default=300
    sslcontext:session_cache_size:=1024 //default=1024*20
    sslcontext:quiet_shutdown:=.t.

    if( capath!=NIL .or. cafile!=NIL )
        sslcontext:set_verify(SSL_VERIFY_PEER_CERT)
        sslcontext:set_verify_depth(1)
        sslcontext:load_verify_locations(cafile,capath)
        if( cafile!=NIL )
            sslcontext:load_client_ca_file(cafile)
            //kerdes, hogy nem kellene-e kulon file,
            //igy a firefox csak olyan certificate-et kuld,
            //amit a cafile-beli ca irt ala
        end
    end
    return sslcontext

*****************************************************************************
class connection(object) 
    attrib  socket          // a szerver/kliens elerhetosege (objektum)
    attrib  message         // az utolso http message (mar beolvasott resze)
    attrib  client          // szerver eseten a varakozo kliens
    attrib  module          // szerver eseten a module neve
    attrib  request         // az utolso http message komplett torzse
    attrib  http            // az utolso message HTTP verzioja
    attrib  timeout         // timeout meresenek kezdete: seconds()
    attrib  time            // kapcsolat kezdo ideje: time()
    attrib  counter
 
    method  initialize
    method  fd
    method  read
    method  write
    method  forward
    method  server
    method  destruct
    method  conidx

*****************************************************************************
static function connection.initialize(this,s,m) 
    this:(object)initialize
    this:socket:=s
    this:message:=a""
    this:module:=m
    this:time:=time()
    this:counter:=0
    this:timeout:=seconds()
    printevent(this,"con")
    return this

*****************************************************************************
static function connection.fd(this) //select-hez
    return this:socket:fd

*****************************************************************************
static function connection.destruct(this,idx) 
local n
    begin
        if(this:socket==NIL)
            return NIL
        end
        
        printevent(this,"del")
    
        //con array-bol torolni
        if( idx==NIL )
            idx:=this:conidx 
        end
        xdel(con,idx)
    
        //megszunt szerverek varakozo klienseit ertesiteni kell

        if( this:client!=NIL )
            this:client:write(noservice(this:module+".*"))
        end
        
        if( findsrv(this:module)==NIL )
            //nincs masik hasonlo peldany
            //amelyik atvehetne a szerepet
            for n:=len(queue) to 1 step -1
                if( queue[n][3]==this:module  )
                    queue[n][1]:write(noservice(this:module+".*"))
                    xdel(queue,n)
                end
            next
        end
    
        this:socket:close
    recover
        //az errorokat errorhandler logolja
        ? "destruct failed", this
    finally    
        this:socket:=NIL
    end

*****************************************************************************
static function connection.conidx(this)
local s,i,e
    s:=this:socket
    i:=ascan(con,{|c|c:socket==s})    
    if( i==0 )
        e:=errorNew()
        e:operation:="conidx"
        e:description:="connection not found"
        break(e)
    end
    return i

*****************************************************************************
static function connection.read(this)

local s:=this:socket 
local r:=s:recvall
//local r:=s:recv(s:pending)
local clen,body,vpos,e

    if( r==NIL )
        e:=socketerrorNew()
        e:operation("connection.read")
        e:description:="no data"
        e:args:={s:fd}
        break(e)
    end
    this:message+=r

    clen:=val(http_getheader(this:message,"Content-Length"))

    if( 0<clen .and. clen<=len(body:=http_body(this:message)) )
        //komplett az uzenet

        vpos:=at("HTTP/",this:message)
        if( vpos==0 )
            e:=invalidformaterrorNew()
            e:operation("connection.read")
            e:description:="no HTTP version"
            break(e)
        end
        
        this:http:=substr(this:message,vpos,8)
        this:request:=body
        
        this:forward
    end
    //tovabb olvasunk

*****************************************************************************
static function connection.write(this,msg)
    if( this:socket!=NIL )
        this:counter++
        http_writemessage(this:socket,msg)
    else
        ? "response to connection destructed earlier"
    end
    
    //itt mindenkeppen vissza kell terni,
    //mert ha a fociklus hibaaga kapna el a hibat,
    //akkor elmaradhat a forward client es sor kezelese,
    //http_writemessage nem kivetelt dob,
    //hanem visszaadja az elkuldott bajtok szamat
    //(ezert nem kell itt kulon vedelem)


*****************************************************************************
static function connection.forward(this)
 
local s,n
    
    if( this:client==NIL )
        //kerdest tovabbitunk egy szervernek

        s:=this:server

        if( valtype(s)=="C" ) //kozvetlen valasz 
            this:write(s) 

        elseif( s:client==NIL ) //a szerver szabad
            s:client:=this
            s:write(this:message)

        else //a szerver foglalt
            aadd(queue,{this,this:message,s:module})
        end
 
    else
        //valaszt tovabbitunk egy kliensnek

        this:client:write(this:message)
        if( this:client:http<a"HTTP/1.1" )
            this:client:destruct
        end
        this:client:=NIL

        // egy szerver felszabadult
        // megnezzuk, van-e a sorban olyan request
        // ami ennek a szervernek kuldendo
        
        for n:=1 to len(queue)
            if( queue[n][3]==this:module )
                this:client:=queue[n][1]
                this:write(queue[n][2])
                xdel(queue,n)
                exit
            end
        next
    end

    this:message:=a""
    this:request:=NIL

*****************************************************************************
static function connection.server(this)
local p, m, m0, s
local r,n,module,host,port,c

    p:=xmlparser2New() 
    p:contentblock:={|p,node|methodname(p,node,@m)}
    p:parsestring(this:request) //reszleges elemzes
 
    m0:=left(m,at(".",m)-1)
    
    if( m0=="system" )

        if( m=="system.register" )
            r:=xmlrpcserver.rpcdataCall(NIL,this:request) //{"system.register",{module}}}
            this:module:=r[2][1]
            s:=rpcresponse(.t.)

        elseif( m=="system.listservices" )
            r:=xmlrpcserver.rpcdataCall(NIL,this:request) //{"system.listservices",{sid}}}
            s:=rpcresponse(listservices())

        elseif( m=="system.listclients" )
            r:=xmlrpcserver.rpcdataCall(NIL,this:request) //{"system.listclients",{sid}}}
            s:=rpcresponse(listclients())

        elseif( m=="system.getversion" )
            s:=rpcresponse(VERSION)
 
        elseif( m=="system.down" )
            r:=xmlrpcserver.rpcdataCall(NIL,this:request) //{"system.down",{sid,module}}}
            if( check(r[2][1]) )
                down(r[2][2])
            end
            s:=rpcresponse()
 
        elseif( m=="system.printstate" ) 
            printstate()
            s:=rpcresponse()
 
        else
            s:=noservice(m) 
        end

    else
        s:=findsrv(m0)
        if( s==NIL )
            s:=noservice(m)  
        end
    end
    return  s

*****************************************************************************
static function findsrv( module )

local n,srv

    for n:=1 to len(con)
        if( con[n]:module==module )
            srv:=con[n]
            if( srv:client==NIL )
                exit
            end
        end
    next
    return srv // megfelelo tipusu (esetleg foglalt) szerver vagy NIL

*****************************************************************************
static function methodname(parser,node,m)
    if( node:type=="#TEXT" )
        return .t. //epit
    elseif( node:type=="methodName" )
        m:=node:content[1]:content[1]
        //? "methodname =",m
    end
    return .f. //eldob
 
*****************************************************************************
static function addheader(rsp)
local hdr:="HTTP/1.1 200 OK"+crlf()
    hdr+="Content-Length: "+alltrim(str(len(rsp)))+crlf()
    hdr+="Content-Type: text/xml"+crlf()
    return hdr+crlf()+rsp

*****************************************************************************
static function noservice(name)
    return rpcfault(0,name+"|service not available") 

*****************************************************************************
static function rpcfault(code,description)
local rsp:=xmlrpcserver.rpcmethodFault(NIL,code,description)     
    return addheader(rsp)

*****************************************************************************
static function rpcresponse(value)
local rsp:=xmlrpcserver.rpcmethodResponse(NIL,{value})    
    return addheader(rsp)

*****************************************************************************
static function xdel(a,x)
    adel(a,x)
    asize(a,len(a)-1)

*****************************************************************************
static function listservices()
local n,l,a,c,list:={}
    for n:=1 to len(listener)
        l:=listener[n]
        aadd(list,{"system",l:socket:classname,l:fd,starttime,l:address,l:counter})
    next
    for n:=1 to len(con)
        c:=con[n]
        if( c:module!=NIL )
            aadd(list,{c:module,c:socket:classname,c:fd,c:time,getpeername(c:socket:fd),c:counter})
        end
    next
    return list

*****************************************************************************
static function listclients()
local n, c, list:={}
    for n:=1 to len(con)
        c:=con[n]
        if( c:module==NIL )
            aadd(list,{str(seconds()-c:timeout(),4,0),c:socket:classname,c:socket:fd,c:time,getpeername(c:socket:fd),c:counter})
        end
    next
    return list

*****************************************************************************
static function down(module)
local n, c
    if( module=="system" )
        ? "<<<", date(), time(), "down"
        quit //a wrapper (es vele az egesz rendszer) kilep
    end

    for n:=1 to len(con)
        c:=con[n]
        if( c:module==module )
            c:destruct
            exit
        end
    next
 
*****************************************************************************
static function printstate()
local n, c

    ? 
    ? date(),time(), "system.printstate", len(queue)
    ? "------------------------------------------------------------------"
 
    for n:=1 to len(con)
        c:=con[n]
        if( c:module!=NIL )
            ? padr(c:module,16),c:http,;
              c:socket:classname,c:socket:fd,;
              c:time,;
              if(c:client==NIL," ","C")
        end
    next
    
    ?

    for n:=1 to len(con)
        c:=con[n]
        if( c:module==NIL )
            ? padr("client",16),c:http,;
              c:socket:classname,c:socket:fd,;
              c:time 
        end
    next
 
    ? "------------------------------------------------------------------"


*****************************************************************************
static function printevent(this,event)
    ? date(),time(),event,;
      if(this:module==NIL,"client",this:module),;
      this:socket:fd,;
      len(con)


*****************************************************************************
static function check(sid)
local n,c,tid

    //Szabad session szervert keres,
    //ahhoz csinal egy xmlrpcclient-et,
    //es ellenorizteti vele a sid-et.
    //Csak _szabad_ szervert lehet igy hasznalni,
    //maskepp osszekeverednenek az uzenetek.
    //Ha eppen nincs szabad session szerver,
    //akkor az eredmeny false.

    for n:=1 to len(con)
        if( con[n]:module=="session" .and. con[n]:client==NIL )
            c:=xmlrpcclientNew()
            c:keepalive:=.t.
            c:socket:=con[n]:socket
            tid:=c:call("session.usertype",sid)
            exit
        end
    next

    return tid=="poweruser"

*****************************************************************************

