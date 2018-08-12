
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

#include "inkey.ch"

*****************************************************************************
function main(host,port,sslflag)

local k:=0
local client
local metlst,m
local ctx
local e

    set printer to log-client
    set printer on

    if(host==NIL)
        host:="localhost"
    end

    if(port==NIL)
        port:="45000"
    end

    if( sslflag!=NIL ) 
        ctx:=sslctxNew() 
    end
    
    client:=xmlrpcclientNew(host,val(port))
    client:timeout:=1000 
    client:keepalive:=.t.
    //client:debug:=.t.
    client:rpcstruct:="hash"
    
    ? client:host, client:port
    ?
    
    client:sslcontext:=ctx
 
    while( .t. )
    
        k:=chr(inkey(0));  
        
        if( k=="x" )
            exit

        elseif( k=="c" )
            client:close //amikor kell, automatikusan konnektál

        elseif( k=="0" )
            ? client:call("sample.echo")          //0 db paraméter
            //? client:call("sample.echo",NIL)      //0 db paraméter (ugyanaz)
            //? client:call("sample.echo",{} )      //0 db paraméter (ugyanaz)
 
        elseif( k=="N" )
            // "x" -> <value><string>x</string></value>
            // ""  -> <value><string></string></value>
            // NIL -> <value></value>
            // A szabvány szerint, ha hiányzik a típus, akkor az string,
            // ezért a NIL és a "" között nem lehet különbséget tenni.
        
            ? client:call("sample.echo","" )      //1 db paraméter: ""
            //? client:call("sample.echo",{NIL} )   //1 db paraméter: NIL (ugyanaz)

        elseif( k=="1" )
            ? client:call("sample.echo",{1} )     //1

        elseif( k=="2" )
            ? client:call("sample.echo",{1,2} )   //1,2

        elseif( k=="a" )
            ? client:call("sample.echo",{{1,2}} ) //{1,2}   

        elseif( k=="e" )
            ? client:call("sample.echo",{1,.t.,date(),NIL,"","öt <szép> &lt &amp szűzlány",{}})


        elseif( k=="b" )
            // <base64> típusban kódolva küldi vissza,
            // az interfész automatikusan kicsomagolja,
            //tehát az eredeti szöveget írja ki.

            ? client:call("sample.b64","Próba szerencse!")
 
        elseif( k=="t" )
            ? client:call("sample.gettime")

        elseif( k=="+" )
            ? client:call("sample.sum",{11,3})

        elseif( k=="-" )
            ? client:call("sample.dif",{11,3})

        elseif( k=="*" )
            ? client:call("sample.mul",{11,3})

        elseif( k=="/" )
            ? client:call("sample.div",{11,3})

        elseif( k=="z" )
            begin
                ? client:call("sample.div",{1,0}) //nullával oszt!
            recover e
                e:list
            end
 
        elseif( k=="s" )
            ? client:call("sample.struct",{11,{3,"A","B","C"}})

        elseif( k=="m" )
            ? metlst:=client:call("system.listMethods")

            //ezek nincsenek implementálva
            //for m:=1 to len(metlst)
            //    ? client:call("system.methodHelp",metlst[m]) 
            //next

        elseif( k=="h" )
            begin
                ? client:call("sample.hopp",{"Próba szerencse!"}) //nincs ilyen!
            recover e
                e:list
            end

        elseif( k=="B" )
            //A blokkok kiértékelt eredményét küldi. 
            //Az eredmény egy <value> tag belsejébe kerül, pl: 
            //<string>szintaktikailag helyes tartalom</string>
            //Ez itt direkt szemetet küld teszteléshez.

            begin
                ? client:call("sample.echo",{||"a<"}) //szemét
                //? client:call("sample.echo",{||"<hopp>xx</hopp>"}) //rossz típus
            recover e
                e:list
            end

        elseif( k=="!" )
            //? client:call("sample.echo1", "Próba szerencse" )
            //? client:call("sample.echo1", 3.141592 )
            ? client:call("sample.echo1", proba.PStructNew() )

        end
    end

    ?


*****************************************************************************
class proba.PStruct(object)
    attrib  __classname__
    attrib  text1
    attrib  text2
    attrib  text3

    method  initialize
    
static function proba.PStruct.initialize(this)
    this:__classname__:="proba.PStruct"  //a java miatt case sensitive
    this:text1:="egy"
    this:text2:="ketto"
    this:text3:="harom"
    return this

*****************************************************************************


