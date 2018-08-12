
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
class xmlrpcserver(object) 

    method initialize
    method response
    method addmethod
    method loop
 
    method methodidx
    method methodblk
    method methodhlp
    method methodsig
    method methodlst
 
    attrib iface        //ezen az interfészen figyel
    attrib port         //ezen a porton figyel
    attrib reuseaddr    //reuse address flag
    attrib methods      //metódusok: {{m,b,h,s},...} 
    attrib keepalive    //tartja-e a kapcsolatot
    attrib reqencoding  //required encoding in requests
    attrib debug        //printeli-e a debug infót
    attrib recover      //elkapja-e a hibákat
    attrib server       //szerver név (HTTP header)
    attrib evalarray    //kibontva adja-e át a <params> tagot
    attrib loopfreq     //a select timeout-ja (ezred sec-ben)
    attrib loopblock    //a select lejártakor végrehajtódik 
    attrib closeblock   //minden socket lezárásakor végrehajtódik 
    attrib socketlist   //az összes élő socket objektum
    attrib scklisten    //ezen a socket objektumon figyel
    attrib sslcontext   //ha ez nem NIL, akkor bekapcsolja az SSL-t
    attrib rpcstruct    //hogy veszi at a struct-okat: attrvals/hash

*****************************************************************************
static function xmlrpcserver.initialize(this,ifport,ctx) 
local a,e

    this:(object)initialize
    
    if( valtype(ifport)=="C" )
        if( ":"$ifport )
            a:=split(ifport,":")
            if( !empty(a[1]) )
                this:iface:=gethostbyname(a[1])
                if(this:iface==NIL)
                    e:=socketerrorNew()
                    e:operation:="xmlrpcserver.initialize"
                    e:description:="gethostbyname failed"
                    e:args:={a[1]}
                    break(e)
                end
            else
                this:iface:=NIL //minden interfész
            end
            if( !empty(a[2]) )
                this:port:=val(a[2])
            else
                this:port:=NIL //sehol sem figyel
            end
        else
            //compatibility
            this:iface:=NIL //minden interfészen
            this:port:=val(ifport) //itt figyel
        end

    elseif( valtype(ifport)=="N" )
        this:iface:=NIL //minden interfészen
        this:port:=ifport //itt figyel

    else
        this:iface:=NIL
        this:port:=NIL  //sehol sem figyel
    end
    
    this:sslcontext:=ctx
    this:reuseaddr:=.f.  //Windowson nem szabad beállítani!
    this:methods:={}
    this:keepalive:=.f.
    this:debug:=.f.
    this:recover:=.t.
    this:evalarray:=.t.
    this:socketlist:={}
 
    this:server:=ID_SERVER

    this:addmethod("system.listMethods",{||this:methodlst})
    this:addmethod("system.methodHelp",{|m|this:methodhlp(m)}) 
    this:addmethod("system.methodSignature",{|m|this:methodsig(m)})  

    return this

*****************************************************************************
static function xmlrpcserver.addmethod(this,m,b,h,s) 
    aadd(this:methods,{m,b,h,s}) 
    return this

*****************************************************************************
static function xmlrpcserver.methodlst(this)
local metlst:=array(len(this:methods)),n
    for n:=1 to len(metlst)
        metlst[n]:=this:methods[n][1]
    next
    return metlst

*****************************************************************************
static function xmlrpcserver.methodidx(this,metnam) 
local e, metidx:=ascan(this:methods,{|x|x[1]==metnam}) 
    if( 0==metidx )
        e:=xmlrpcerrorNew()
        e:operation:="xmlrpcserver.methodidx"
        e:description:="unknown method"
        e:args:={metnam}
        e:subsystem:="XMLRPC"
        break(e)
    end
    return metidx

*****************************************************************************
static function xmlrpcserver.methodblk(this,m) 
local idx:=this:methodidx(m)
    return this:methods[idx][2]

*****************************************************************************
static function xmlrpcserver.methodhlp(this,m) 
local idx:=this:methodidx(m) 
local hlp:=this:methods[idx][3] 
    return hlp
 
*****************************************************************************
static function xmlrpcserver.methodsig(this,m) 
local idx:=this:methodidx(m) 
local sig:=this:methods[idx][4] 
    return sig

*****************************************************************************
static function xmlrpcserver.response(this,sck) 
 
static errtyp:=errorNew()
//static errtyp:=xmlrpcinvalidsiderrorNew()
//static errtyp:=apperrorNew()
//Nincs sok értelme az elkapott hibák közötti szelektálásnak,
//ui. egy request-ben levő adathiba símán okozhat argument error-t
//(például, ha egy dátum helyett NIL jön, akkor elszáll a dtos).
//Az errorblock-kal kapcsolatos üzelmek ki lettek takarítva,
//nincs olyan régi program, ami break helyett eval(errorblock)-ot
//használna, viszont káros, mert végtelen rekurziót okozhat.

local req,metnam,params,metblk,rsp,hdr
local e,faultCode,faultString 
local qmxml,docenc

    req:=http_readmessage(sck)
    if( req==NIL )
        return .f.
    end

    if( this:debug )
        ? "-----------------------------------------------------------"
        ? "XML-RPC REQUEST", date(), time()
        ? "-----------------------------------------------------------"
        ? req 
    end
    
    req:=http_body(req) //xml request

    begin
 
        req:=xmlrpcserver.rpcdataCall(this,req,@qmxml)
        
        if( this:reqencoding!=NIL )
            //? qmxml
            if( !empty(qmxml) )
                docenc:=qmxml:getattrib("encoding")
            end
            if( empty(docenc) )
                docenc:="UTF-8"
            end
            //? docenc
            if( !docenc==this:reqencoding )
                e:=xmlrpcerrorNew()
                e:operation:="xmlrpcserver.response"
                e:description:="required encoding:"+this:reqencoding
                e:args:={docenc}
                break(e)
            end
        end
        

        metnam:=req[1]                   //methodname
        params:=req[2]                   //array of params
        metblk:=this:methodblk(metnam)   //method codeblock

        if( this:evalarray )
            rsp:=evalarray( metblk, params )
        
            //evalarray a standard eval függvény olyan változata,
            //ahol a kódblokk paramétereit nem felsorolva, 
            //hanem arrayben kell megadni (C++ primitív)
        else
            rsp:=eval( metblk, params )
        end


    recover  e if(this:recover,errtyp,0)
    
        //Ha this:recover==.t. (default),
        //akkor elkapjuk a hibákat, és XMLRPC fault-ra konvertáljuk,
        //egyébként hagyjuk futni a standard hibakezelést.
        
        if( this:debug )
            e:list
            callstack()
            //varstack()
        end
        
        faultCode:=e:subcode

        faultString:=e:classname
        
        if( !empty(metnam) )
            faultString+="|"
            faultString+=metnam
        end
        if( !empty(e:operation) )
            faultString+="|"
            faultString+=e:operation
        end
        if( !empty(e:description) )
            faultString+="|"
            faultString+=e:description 
        end
        if( !empty(e:subsystem) )
            faultString+="|"
            faultString+=e:subsystem
        end
        //faultString: "classname|metnam|operation|description|subsystem"
    end

    if( faultString!=NIL )
        rsp:=xmlrpcserver.rpcmethodFault(this,faultCode,faultString)  
    else
        rsp:=xmlrpcserver.rpcmethodResponse(this,{rsp})
    end

    hdr:="HTTP/1.1 200 OK"+crlf()
    hdr+="Content-Length: "+alltrim(str(len(str2bin(rsp))))+crlf()
    hdr+="Content-Type: text/xml"+crlf()
    hdr+="Server: "+this:server+crlf()
    
    rsp:=hdr+crlf()+rsp  

    if( this:debug )
        ? "-----------------------------------------------------------"
        ? "XML-RPC RESPONSE", date(), time()
        ? "-----------------------------------------------------------"
        ? rsp 
    end
    
    rsp:=str2bin(rsp) //http_writemessage byteokban mér!

    return len(rsp)==http_writemessage(sck,rsp)

 
*****************************************************************************
static function xmlrpcserver.loop(this)

local readable,n,i,p,e,s,r

    if( this:port!=NIL )
        this:scklisten:=socketNew() //ezen figyel
        this:scklisten:reuseaddress:=this:reuseaddr //teszteléshez
        this:scklisten:bind(this:iface,this:port)
        this:scklisten:listen
        aadd(this:socketlist,this:scklisten)
    end

    while( .t. )

        select( readable:=aclone(this:socketlist),,,this:loopfreq )

        for n:=1 to len(readable)

            if( readable[n]==this:scklisten )
                begin
                    s:=this:scklisten:accept
                    if( this:sslcontext!=NIL )
                        #ifdef SSL_SUPPORT
                            s:=sslconAccept(this:sslcontext,s) //socket -> sslcon
                        #else
                            e:=errorNew()
                            e:operation:="xmlrpcserver.loop"
                            e:description:="no SSL support"
                            e:subsystem("XMLRPC")
                            break(e)
                        #endif
                    end
                recover e <socketerror>
                end
                aadd(this:socketlist,s)
                //? "ACCEPT",s
            else
                if( !(r:=this:response(readable[n])) .or. !this:keepalive )

                    if( this:closeblock!=NIL )
                        eval(this:closeblock,this,readable[n])
                    end

                    if( r .and. !readable[n]:classname=="socket" )
                        readable[n]:shutdown //session cache
                    end

                    readable[n]:close
                    i:=ascan(this:socketlist,readable[n])
                    xdel(this:socketlist,i)
                end
            end
        next
        
        if( this:loopblock!=NIL )
            eval(this:loopblock,this)
        end
    end


*****************************************************************************
static function xdel(a,x)
    adel(a,x)
    asize(a,len(a)-1)

*****************************************************************************
