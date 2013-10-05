
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

#include "xmlrpc.ver"

*****************************************************************************
class xmlrpcclient(object)

    method initialize
    method call
    method close
    method connect
    method write
    method read
 
    attrib useragent  //kliens id (HTTP header)
    attrib hostname   //szerver neve/ip címe
    attrib host       //szerver ip címe
    attrib port       //szerver portszám
    attrib socket     //socket (object)
    attrib keepalive  //tartja-e a kapcsolatot
    attrib debug      //printeli-e a debug infót
    attrib URI        //HTTP header (általában /RPC2)
    attrib timeout    //ennyit vár a válaszra (ezred sec)
    attrib sslcontext //ha ez nem NIL, akkor bekapcsolja az SSL-t


*****************************************************************************
static function xmlrpcclient.initialize(this,host,port,ctx) 
local e
    this:(object)initialize
    
    if( host==NIL )
        this:hostname:=""
    else
        this:hostname:=host
        this:host:=gethostbyname(host)
        if( this:host==NIL )
            e:=socketerrorNew()
            e:operation:="xmlrpcclientIni"
            e:description:="gethostbyname failed"
            e:subsystem("XMLRPC")
            e:args:={host}
            break(e)
        end
    end
    
    if( port==NIL )
        //nincs magdva
    elseif( valtype(port)=="C" )
        this:port:=val(port)
    else
        this:port:=port //number
    end

    #ifdef NOT_DEFINED
      Ha meg van adva a host:port, akkor a kliens automatikusan 
      tud konnektálni (amikor kell). Viszont lehet úgy is használni
      az objektumot, hogy egyszerűen belerakunk egy élő socketet,
      pl. client:socket:=sckobj. Ilyenkor nincs szükség a host:port-ra.
    #endif
    
    this:sslcontext := ctx
    
    this:debug      := .f.
    this:keepalive  := .f.     
    this:timeout    := 30000    //fél perc
    this:URI        := "/RPC2"
    this:useragent  := ID_CLIENT
    
    return this

*****************************************************************************
static function xmlrpcclient.close(this)
    if( this:socket!=NIL )
        //session cache?
        //if( !this:socket:classname=="socket" )
        //    this:socket:shutdown
        //end
        this:socket:close
        this:socket:=NIL
    end

*****************************************************************************
static function xmlrpcclient.connect(this)
local e

    this:close
    if( this:sslcontext==NIL )
        this:socket:=socketNew()
    else
        #ifdef SSL_SUPPORT        
            this:socket:=sslconNew(this:sslcontext)
        #else
            e:=errorNew()
            e:operation:="xmlrpcclient.connect"
            e:description:="no SSL support"
            e:subsystem("XMLRPC")
            break(e)
        #endif
    end
    this:socket:connect(this:host,this:port) //kivételt dobhat

    //? "CONNECT",this:host,this:port

*****************************************************************************
static function xmlrpcclient.write(this,req)
local hdr, e

    hdr:="POST "+this:URI+"  HTTP/1.1"+crlf()
    hdr+="User-Agent: "+this:useragent+crlf()
    hdr+="Host: "+this:hostname+crlf()
    hdr+="Content-Type: text/xml"+crlf()
    hdr+="Content-Length: "+alltrim(str(len(req)))+crlf()

    if( this:debug )
        ? "-----------------------------------------------------------"
        ? "xml-rpc request"
        ? "-----------------------------------------------------------"
        ? hdr+crlf()+req 
    end

    if( this:socket==NIL .or. 0<select({this:socket:fd},,,0) )
        //A select veszi észre, ha a socket lezáródott.
        //A socket lezárása és újbóli megnyitása (connect)
        //semmiképp sem árt, mert része a protokollnak,
        //és a szerver nem kezdeményezhet.
        this:connect
    end
    
    while( 0>http_writemessage(this:socket,hdr+crlf()+req) )
        e:=socketerrorNew()
        e:operation:="xmlrpcclient.write"
        e:description:="http_writemessage failed"
        e:subsystem("XMLRPC")
        e:args:={this:host,this:port}
        break(e)
    end


*****************************************************************************
static function xmlrpcclient.read(this)
local rsp, e

    while( 1>select({this:socket:fd},,,this:timeout) )
        e:=xmlrpctimeouterrorNew()
        e:operation:="xmlrpcclient.read"
        e:description:="no response within timeout"
        e:subsystem("XMLRPC")
        e:args:={this:host,this:port}
        e:canretry:=.t.
        break(e)
    end
    
    if( NIL==(rsp:=http_readmessage(this:socket)) )
        e:=socketerrorNew()
        e:operation:="xmlrpcclient.read"
        e:description:="http_readmessage failed"
        e:subsystem("XMLRPC")
        e:args:={this:host,this:port}
        break(e)
    end

    if( this:debug )
        ? "-----------------------------------------------------------"
        ? "xml-rpc response"
        ? "-----------------------------------------------------------"
        ? rsp
    end

    if( !this:keepalive )
        this:close
    end
 
    return rsp
 
 
*****************************************************************************
static function xmlrpcclient.call(this,metnam,params)

local e, result
local faultcode,faultstring

    if( params==NIL )
        params:={}
    elseif( !valtype(params)=="A" )
        params:={params}
    end

    this:write( rpcmethodCall(metnam,params) )
    result:=rpcdataResponse(http_body( this:read ))

 
    if( !result[1] )
        //a szerver hibát jelzett

        faultcode:=result[2][1][2]
        faultstring:=result[2][2][2]

        e:=xmlrpcerrorNew()
        e:operation:="xmlrpcclient.call"
        e:description:=faultstring
        e:subsystem("XMLRPC")
        e:subcode:=faultcode
        e:args:=params
        break(e)

    else
        // válasz kicsomagolása
        // csak a második eset fordulhat elő,
        // mert a válasz mindig kötelezően egy elemű
        //
        // {}    --> NIL
        // {x}   --> x
        // {x,y} --> {x,y} 

        result:=result[2] 
        if( len(result)==0 )
            result:=NIL
        elseif( len(result)==1 ) 
            result:=result[1]
        end
    end

    return result 


*****************************************************************************

