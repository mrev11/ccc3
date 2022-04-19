
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
    method  xmlout          //kiiras: minden kulon sorba
    method  xmloutpre       //kiiras: semmit nem valtoztat
    method  xmloutind       //kiiras: indentalva

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
        attrval:=substr(attrval,2,len(attrval)-2) //idezojelek
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

//Formazas: minden adat kulon sorba.
//Ha szukseges, CDATA-ra ter at a texteknel.

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
        ?? "?>" // az eltero "?>" lezaras miatt nem mehet a normal agon

    elseif( this:type=="#TEXT" )
        for n:=1 to len(this:content)
            ? cdataif(this:content[n])
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

//Formazas nelkul irja ki az XML-t.
//Ha a DOM parser:preservespace:=.t.-val keszult,
//akkor a bemenet es a kimenet ugyanaz.
//Ha szukseges, CDATA-ra ter at a texteknel.

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
        ?? "?>" // az eltero "?>" lezaras miatt nem mehet a normal agon

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
static function xmlnode.xmloutind(this,rflag:=.f.,indent:="") 

// Indentalva irja ki az xml-t.
// Akkor ad jo eredmenyt, ha preservespace:=.f. volt beallitva.
// Ha szukseges, CDATA-t hasznal a textek kiirasakor.
//
// Az osszetett node-ok kiirasa mindig indentalt:
//  <aaa>
//      <bbb/>
//  </aaa>
//
// A tisztan szoveg tartalmu node-ok kiirasa egysoros: 
//  <aaa>text</aaa>.
//
// A vegyes tartamu node-okban a text-eket is indentalva irja ki:
//  <aaa>
//      text
//      <bbb>text</bbb>
//  </aaa>


local n,ind

    if( this:type=="#ROOT" .and. rflag==.f. )
        // Ha rflag==.f. (default)
        //  akkor a #ROOT gyermekei sorban kiirodnak,
        //  a kimeneten nem jelenik meg a <#ROOT> hej.
        //
        // Ha rflag==.t. (teszteleshez)
        //  akkor nem ide jon, hanem a normal agon irodik ki 
        //  a node, es a <#ROOT> hej is megjelenik a kimeneten.
    
        for n:=1 to len(this:content)
            this:content[n]:xmloutind(rflag,indent)
        next

    elseif( left(this:type,1)=="?" )
        ?? "<"+this:type
        for n:=1 to len(this:attrib)
            ?? " "+this:attrib[n]:name+"="+this:attrib[n]:value
        next
        ?? "?>" // az eltero "?>" lezaras miatt nem mehet a normal agon

    elseif( this:type=="#TEXT" )
        if( len(indent)>0 )
            ? indent
        end
        for n:=1 to len(this:content)
            ?? cdataif(this:content[n])
        next

    elseif( this:type=="#CDATA" )
        if( len(indent)>0 )
            ? indent
        end
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
            if( textcontent(this) )
                for n:=1 to len(this:content)
                    this:content[n]:xmloutind(rflag,"")
                next
                ?? "</"+this:type+">"
            else
                for n:=1 to len(this:content)
                    this:content[n]:xmloutind(rflag,indent+"    ")
                next
                ? indent+"</"+this:type+">"
            end
        end
    end


****************************************************************************
static function textcontent(node) 

// => .t.
//  ha a content ures, vagy
//  csak #TEXT/#CDATA node-okat tartalmaz

local n
    for n:=1 to len(node:content)
        if( node:content[n]:type::asc!=35 ) // asc("#")==35
            return .f.
        elseif( node:content[n]:type=="#ROOT" )
            return .f.
        end
    next 
    return .t.


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
                       