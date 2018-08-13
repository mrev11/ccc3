
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

//XML-RPC dokumentumot CCC struktúrába alakít

****************************************************************************
function xmlrpcserver.rpcdataCall(this,xml,qmxml)  //this:server
local p, o, name, params, n
local style

    //xmldom 1.4.00 előtt
    //
    //o:=xmlparserNew():parsestring(xml)
    //if( !lower(o:content[1]:type)=="?xml" )
    //    invalidformat("Not an XML document") 
    //end
    //if( !o:content[2]:type=="methodCall" )
    //    expected("methodCall",o:content[2]:type) 
    //end
    //o:=o:content[2]

    //Megj:
    //A fentebbi régi megoldás (fix indexekkel) a lehető legrosszabb.
    //Helyette jobb lett volna egy olyan processblock, ami kiszedi 
    //a methodCall node-ot, minden mást elereszt. Akkor most nem volna
    //inkompatibilitás az új xmldom könyvtárral.


    //xmldom 1.4.00 után
    p:=xmlparserNew()
    p:rootflag:=.f.
    p:entityconv:=.t.
    
    if( this!=NIL .and. this:rpcstruct!=NIL )
        //server objektum nelkul is meghivhato 
        style:=xmlattribNew("style",'"'+this:rpcstruct+'"')
        p:contentblock:={|p,n|if(n:type=="struct",n:addattrib(style),NIL),.t.}
    end
    o:=p:parsestring(xml)
    //o:xmloutind
    qmxml:=p:qmxml
    if( !o:type=="methodCall" )
        expected("methodCall",o:type) 
    end

    //innen ugyanaz, mint a régi

    if( !o:content[1]:type=="methodName" )
        expected("methodName",o:content[1]:type) 
    end
    if( !o:content[2]:type=="params" )
        expected("params",o:content[2]:type) 
    end
    
    name:=o:content[1]:content[1]:content[1] 

    o:=o:content[2]
    
    params:=array(len(o:content))
    for n:=1 to len(o:content)
        params[n]:=rpcparam(o:content[n])
    next
    
    return {name,params}


****************************************************************************
function xmlrpcclient.rpcdataResponse(this,xml) //this:client
local p, o, params, fault, n
local style

    //xmldom 1.4.00 előtt
    //
    //o:=xmlparserNew():parsestring(xml)
    //if( !lower(o:content[1]:type)=="?xml" )
    //    invalidformat("Not an XML document") 
    //end
    //if( !o:content[2]:type=="methodResponse" )
    //    expected("methodResponse",o:content[2]:type) 
    //end
    //o:=o:content[2]


    //xmldom 1.4.00 után

    p:=xmlparserNew()
    p:rootflag:=.f.
    p:entityconv:=.t.
    if( this!=NIL .and. this:rpcstruct!=NIL ) 
        //server objektum nelkul is meghivhato 
        style:=xmlattribNew("style",'"'+this:rpcstruct+'"')
        p:contentblock:={|p,n|if(n:type=="struct",n:addattrib(style),NIL),.t.}
    end
    o:=p:parsestring(xml)
    //o:xmloutind
    if( !o:type=="methodResponse" )
        expected("methodResponse",o:type) 
    end

    //innen ugyanaz, mint a régi

    o:=o:content[1]
 
    if( o:type=="params" )
        params:=array(len(o:content))
        for n:=1 to len(o:content)
            params[n]:=rpcparam(o:content[n])
        next
        return {.t.,params}
   
    elseif( o:type=="fault" ) 
        fault:=rpcvalue(o:content[1])
        return {.f.,fault}
 
    else
        expected(" params> or <fault", o:content[1]:type) 

    end
  
    return params
 

****************************************************************************
static function rpcparam(o)
    if( !o:type=="param" )
        expected("param",o:type,"params") 
    end
    if( len(o:content)!=1 )
        invalidformat("Invalid <param> length"+str(len(o:content))) 
    end
    return rpcvalue( o:content[1] )


****************************************************************************
static function rpcvalue(o)
    if( !o:type=="value" )
        expected("value",o:type) 
    end
    if( len(o:content)==1 )
        return rpctype( o:content[1] )
    end
    if( len(o:content)==0 )
        return ""  // <value></value> 
    end
    invalidformat("Invalid <value> length"+str(len(o:content))) 
    return NIL


****************************************************************************
static function rpctype(o)
local t:=o:type, x
    
    if( t=="i4" )
        x:=val(o:content[1]:content[1])

    elseif( t=="int" )
        x:=val(o:content[1]:content[1])

    elseif( t=="double" )
        x:=val(o:content[1]:content[1])

    elseif( t=="boolean" )
        x:=o:content[1]:content[1] 
        if( x=="1" )
            x:=.t.
        elseif( x=="0" )
            x:=.f.
        else
            invalidformat("Invalid boolean value "+x)
        end
           
    elseif( t=="string" )
        if( empty(o:content) )
            x:=""
        else
            x:=o:content[1]:content[1] 
            //x:=strtran(x,"&lt;","<")
            //x:=strtran(x,"&amp;","&")
        end

    elseif( t=="dateTime.iso8601" )
        x:=left(o:content[1]:content[1],8)
        if( x=="00010101" )
            x:="        "
        end
        x:=stod(x)
        
    elseif( t=="base64" )
        x:=base64_decode(o:content[1]:content[1])
 
    elseif( t=="#TEXT" ) 

        //amikor nincs semmilyen type megadva,
        //akkor ezt kapjuk, amit a szabvány szerint
        //string-ként kell kezelni a többi ágban
        //az implicit #TEXT node-ot átugrottuk
        //a :content[1]:content[1] hivatkozással
        
        if( empty(o:content) )
            x:=""
        else
            x:=o:content[1]
            //x:=strtran(x,"&lt;","<")
            //x:=strtran(x,"&amp;","&")
        end
 
    elseif( t=="array" )
        x:=rpcarray(o:content[1])

    elseif( t=="struct" )
        x:=rpcstruct(o)
 
    else
        invalidformat("Invalid type "+t ) 
    end
 
    return x
    

****************************************************************************
static function rpcarray(o)
local x,data,n
    if( !o:type=="data" )
        expected("data",o:type,"array")
    end
    data:=o:content
    x:=array(len(data))
    for n:=1 to len(data)
        x[n]:=rpcvalue(data[n]) 
    end
    return x


****************************************************************************
static function rpcstruct(o)
local x,n
local item
local style:=o:getattrib("style")
    if( style==NIL .or. style=="attrvlas"  )
        x:=array(len(o:content))
        for n:=1 to len(x)
            x[n]:=rpcmember(o:content[n]) 
        end
    elseif( style=="hash" )
        x:=simplehashNew()
        for n:=1 to len(o:content)
            item:=rpcmember(o:content[n])
            x[item[1]]:=item[2] 
        end
    end
    return x


****************************************************************************
static function rpcmember(o)
local x:=array(2)
    if( !o:type=="member" )
        expected("member",o:type,"struct")
    end
    x[1]:=rpcname(o:content[1])
    x[2]:=rpcvalue(o:content[2])
    return x


****************************************************************************
static function rpcname(o)
    if( !o:type=="name" )
        expected("name",o:type,"member")
    end
    return o:content[1]:content[1]
 

****************************************************************************
static function expected(what,instead,intag)
local msg:="Expected <"+what+">"
    if( instead!=NIL )
        msg+=" instead of <"+instead+">"
    end
    if( intag!=NIL )
        msg+=" in <"+intag+"> tag"
    end
    invalidformat(msg)
    return NIL


****************************************************************************
static function invalidformat(errmsg)
local e:=invalidformaterrorNew()
    e:operation("rpcdata")
    e:description(errmsg)
    break(e)


****************************************************************************

