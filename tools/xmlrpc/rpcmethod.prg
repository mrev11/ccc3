
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

//CCC adatokat XMLRPC hívásokká alakít

#ifdef _CCC2_
static xmlheader:='<?xml version="1.0" encoding="ISO-8859-1"?>'
#endif

#ifdef _CCC3_
static xmlheader:='<?xml version="1.0" encoding="UTF-8"?>'
#endif



****************************************************************************
function rpcmethodCall(name, params) 
local x:=xmlheader+crlf()
    x+="<methodCall>"+crlf()
    x+="<methodName>"+name+"</methodName>"+crlf()
    x+=rpcparams(params)
    x+="</methodCall>"+crlf() 
    return x

****************************************************************************
function rpcmethodResponse(params) 
local x:=xmlheader+crlf() 
    x+="<methodResponse>"+crlf()
    x+=rpcparams(params)
    x+="</methodResponse>"+crlf() 
    return x

****************************************************************************
function rpcmethodFault(code,errmsg) 
local x:=xmlheader+crlf() 
    x+="<methodResponse>"+crlf()
    x+="<fault>"+crlf()
    x+=" <value>"+crlf() 
    x+="  <struct>"+crlf()
    x+="   "+rpcmember({"faultCode",code})
    x+="   "+rpcmember({"faultString",errmsg})
    x+="  </struct>"+crlf()
    x+=" </value>"+crlf()
    x+="</fault>"+crlf()
    x+="</methodResponse>"+crlf() 
    return x
 
****************************************************************************
//A "B" típusú adatokat úgy küldjük át, hogy a blockot kiértékeljük,
//és a kapott eredményt (ami komplett XML tag kell legyen) elküldjük.
//Az alábbi függvény base64 típus küldését segíti.

****************************************************************************
function xmlrpcbase64(x)
    return {||"<base64>"+bin2str(base64_encode(x))+"</base64>"}
 
****************************************************************************
//Az "O" típusú adatok struct típusban lesznek átadva úgy,
//hogy az objektum attrvals metódusától kapott tömbből képezzük 
//a {név,érték} párokat. A jelen segédosztályban az attrvals felül 
//van definiálva közvetlenül megadható attribútumra, így külön 
//osztálydefiníció nélkül (röptében) is küldhetó struct típus.

class xmlrpcstruct(object) 
    method initialize
    attrib attrvals    //felüldefiniálás: method -> attr

static function xmlrpcstruct.initialize(this,av) 
    this:(object)initialize
    this:attrvals:=av
    return this
 
****************************************************************************
static function rpcparams(params)
local x:="<params>"+crlf()
local n
    for n:=1 to len(params)
        x+=rpcparam(params[n]) 
    next
    x+="</params>"+crlf() 
    return x

****************************************************************************
static function rpcparam(v)
    return "<param>"+rpcvalue(v)+"</param>"+crlf() 

****************************************************************************
static function rpcvalue(v)
    return "<value>"+rpctype(v)+"</value>"

****************************************************************************
static function rpctype(v)
local x, t:=valtype(v), n
    if( t=="U" )
        x:="" 
    elseif( t=="C" )
        v:=strtran(v,"&","&amp;")
        v:=strtran(v,"<","&lt;")
        x:="<string>"+v+"</string>" 
    elseif( t=="X" )
        v:=bin2str(v)
        v:=strtran(v,"&","&amp;")
        v:=strtran(v,"<","&lt;")
        x:="<string>"+v+"</string>" 
    elseif( t=="N" ) 
        x:="<double>"+alltrim(str(v))+"</double>" 
    elseif( t=="L" ) 
        x:="<boolean>"+if(v,"1","0")+"</boolean>" 
    elseif( t=="D" ) 
        x:="<dateTime.iso8601>"+dtos(v)+"T00:00:00"+"</dateTime.iso8601>" 
    elseif( t=="A" ) 
        x:="<array><data>"
        for n:=1 to len(v)
            x+=rpcvalue(v[n])
        next
        x+="</data></array>"
    elseif( t=="O" ) 
        x:="<struct>"+crlf()  
        v:=v:attrvals
        for n:=1 to len(v)
            x+=rpcmember(v[n])
        next
        x+="</struct>"
    elseif( t=="B" ) 
        x:=eval(v) //megformázza magát!
    else
        //error
    end
    return x
 
****************************************************************************
static function rpcmember(v)
    return "<member><name>"+bin2str(v[1])+"</name>"+rpcvalue(v[2])+"</member>"+crlf()
    
****************************************************************************
    
 