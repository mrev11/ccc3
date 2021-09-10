
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

****************************************************************************
class xmlnode(object)

    method  initialize
    method  addattrib       {|this,x|aadd(this:attrib,x)}
    method  setattrib
    method  delattrib
    method  addcontent      {|this,x|aadd(this:content,x)}
    method  addtext
    method  settext
    method  getattrib
    method  gettext
    method  nsprefix
    method  uqname
    method  xmlout          //kiírás: minden külön sorba
    method  xmloutpre       //kiírás: semmit nem változtat
    method  xmloutind       //kiírás: indentálva

    attrib  type
    attrib  attrib
    attrib  content

****************************************************************************
static function xmlnode.initialize(this,type) 

    this:(object)initialize(this)

    this:type:=type
    this:attrib:={}
    this:content:={}

    return this


****************************************************************************
static function xmlnode.setattrib(this,oattr,value)
local x,name
    if( valtype(oattr)=="O" )
        name:=oattr:name
        x:=ascan(this:attrib,{|a|a:name==name})
        if( x>0 )
            this:attrib[x]:=oattr
        else
            this:addattrib(oattr)
        end
    else
        name:=oattr
        x:=ascan(this:attrib,{|a|a:name==name})
        if( x>0 )
            this:attrib[x]:value:=quote(value)
            //this:attrib[x]:=xmlattribNew(name,quote(value))
        else
            this:addattrib(xmlattribNew(name,quote(value)))
        end
    end


****************************************************************************
static function xmlnode.delattrib(this,attrname)
local x:=ascan(this:attrib,{|a|a:name==attrname})
    if( x>0 )
        adel(this:attrib,x)
        asize(this:attrib,len(this:attrib)-1)
    end


****************************************************************************
static function xmlnode.getattrib(this,attrname)
local attrval
local x:=ascan(this:attrib,{|a|a:name==attrname})
    if( x>0 )
        attrval:=this:attrib[x]:value 
        attrval:=substr(attrval,2,len(attrval)-2) //idézőjelek
    end
    return attrval

****************************************************************************
static function xmlnode.addtext(this,text)
local child
    if( "<"$text .or. "&"$text )
        child:=xmlnodeNew("#CDATA") 
    else
        child:=xmlnodeNew("#TEXT") 
    end
    child:addcontent(text)
    this:addcontent(child)
    return child


****************************************************************************
static function xmlnode.settext(this,text)
    this:content::asize(0)
    return this:addtext(text)


****************************************************************************
static function xmlnode.gettext(this)
local i, c, x:="", n
    if( this:type=="#TEXT" .or. this:type=="#CDATA" )
        for n:=1 to len(this:content)
            x+=this:content[n]
        end
    else
        for i:=1 to len(this:content)
            c:=this:content[i] 
            if( c:type=="#TEXT" .or. c:type=="#CDATA" )
                for n:=1 to len(c:content)
                    x+=c:content[n]
                end
            end
        next
    end
    return x


****************************************************************************
static function xmlnode.nsprefix(this)
local pos:=at(":",this:type)
    if( pos>0 )
        return left(this:type,pos-1)
    end
    return ""


****************************************************************************
static function xmlnode.uqname(this)
local pos:=at(":",this:type)
    if( pos>0 )
        return substr(this:type,pos+1)
    end
    return this:type


****************************************************************************
static function xmlnode.xmlout(this) 
local n

    if( this:type=="#ROOT" )
        for n:=1 to len(this:content)
            this:content[n]:xmlout
        next

    elseif( left(this:type,1)=="?" )
        ? "<"+this:type
        for n:=1 to len(this:attrib)
            ? "  ",this:attrib[n]:name+"="+this:attrib[n]:value
        next
        ?? "?"+">" //?? "?>" volt, de azon MSVC internal error-ral elhasal!
 
    elseif( this:type=="#TEXT" )
        for n:=1 to len(this:content)
            ? this:content[n]
        next
 
    elseif( this:type=="#CDATA" )
        for n:=1 to len(this:content)
            ? "<![CDATA["
            ?? this:content[n]
            ?? "]]>"
        next

    else
        ? "<"+this:type
        for n:=1 to len(this:attrib)
            ? "  "+this:attrib[n]:name+"="+this:attrib[n]:value
        next
        if( empty(this:content) )
            ?? "/>"
        else
            ?? ">"
            for n:=1 to len(this:content)
                this:content[n]:xmlout
            next
            ? "</"+this:type+">"
        end
    end

****************************************************************************
static function xmlnode.xmloutpre(this) 

//Formázás nélkül írja ki az XML-t.
//Ha a DOM parser:preservespace:=.t.-val készült,
//akkor a bemenet és a kimenet ugyanaz.
//Ha szükséges, CDATA-ra tér át a texteknél.

local n

    if( this:type=="#ROOT" )
        for n:=1 to len(this:content)
            this:content[n]:xmloutpre
        next

    elseif( left(this:type,1)=="?" )
        ?? "<"+this:type
        for n:=1 to len(this:attrib)
            ?? " "+this:attrib[n]:name+"="+this:attrib[n]:value
        next
        ?? "?"+">"
 
    elseif( this:type=="#TEXT" )
        for n:=1 to len(this:content)
            ?? cdataif(this:content[n])
        next
 
    elseif( this:type=="#CDATA" )
        for n:=1 to len(this:content)
            ?? "<![CDATA["
            ?? this:content[n]
            ?? "]]>"
        next

    else
        ?? "<"+this:type
        for n:=1 to len(this:attrib)
            ?? " "+this:attrib[n]:name+"="+this:attrib[n]:value
        next
        if( empty(this:content) )
            ?? "/>"
        else
            ?? ">"
            for n:=1 to len(this:content)
                this:content[n]:xmloutpre
            next
            ?? "</"+this:type+">"
        end
    end


****************************************************************************
static function xmlnode.xmloutind(this,indent:="") 

//Indentálva írja ki az xml-t.
//Akkor ad jó eredményt, ha a fa leveleiben text van,
//és az elemzés parser:preservespace:=.f.-val készült.
//Ha szükséges, CDATA-ra tér át a texteknél.

local n,ind

    if( this:type=="#ROOT" )
        for n:=1 to len(this:content)
            this:content[n]:xmloutind(indent)
        next

    elseif( left(this:type,1)=="?" )
        ?? "<"+this:type
        for n:=1 to len(this:attrib)
            ?? " "+this:attrib[n]:name+"="+this:attrib[n]:value
        next
        ?? "?"+">" //?? "?>" volt, de azon MSVC internal error-ral elhasal!
 
    elseif( this:type=="#TEXT" )
        for n:=1 to len(this:content)
            ?? cdataif(this:content[n])
        next
 
    elseif( this:type=="#CDATA" )
        for n:=1 to len(this:content)
            ?? "<![CDATA["
            ?? this:content[n]
            ?? "]]>"
        next

    else
        ? indent+"<"+this:type
        for n:=1 to len(this:attrib)
            ?? " "+this:attrib[n]:name+"="+this:attrib[n]:value
        next
        if( empty(this:content) )
            ?? "/>"
        else
            ?? ">"
            for n:=1 to len(this:content)
                this:content[n]:xmloutind(indent+"    ")
            next
            if( "#" $ this:content[1]:type )
                ?? "</"+this:type+">"
            else
                ? indent+"</"+this:type+">"
            end
        end
    end


****************************************************************************
static function cdata(x)
local cd:="", n
    while( .t. )
        n:=at("]]>",x)
        if( n==0 )
            cd+="<![CDATA["+x+"]]>"
            exit
        else
            cd+="<![CDATA["+left(x,n+1)+"]]>" 
            x:=substr(x,n+2)
        end
    end
    return  cd
 

static function cdataif(x)
    if( "<"$x .or. "&"$x )
        return  cdata(x) 
    end
    return x


****************************************************************************
static function quote(x)
    if( !'"'$x  )
        return '"'+x+'"'
    elseif( !"'"$x  )
        return "'"+x+"'"
    end
    return '"'+x::strtran('"','&quot;')+'"'


****************************************************************************
                       