
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

static clid_xmlnode:=xmlnodeRegister()
 
****************************************************************************
function xmlnodeClass() 
    return clid_xmlnode

****************************************************************************
static function xmlnodeRegister() 
local clid:=classRegister("xmlnode",{objectClass()})
    classMethod(clid,"initialize",{|this,type|xmlnodeIni(this,type)})
    classMethod(clid,"addattrib",{|this,x|aadd(this:attrib,x)})
    classMethod(clid,"addcontent",{|this,x|aadd(this:content,x)})
    classMethod(clid,"getattrib",{|this,a|getattrib(this,a)})
    classMethod(clid,"gettext",{|this|gettext(this)})
    classMethod(clid,"xmlout",{|this|xmlout(this)})
    classAttrib(clid,"type")  
    classAttrib(clid,"attrib")  
    classAttrib(clid,"content")  
    return clid


****************************************************************************
function xmlnodeNew(type) 
local clid:=xmlnodeClass()
    return objectNew(clid):initialize(type)

****************************************************************************
function xmlnodeIni(this,type) 

    objectIni(this)

    this:type:=type
    this:attrib:={}
    this:content:={}

    return this


****************************************************************************
static function getattrib(this,attrname)
local attrval
local x:=ascan(this:attrib,{|a|a:name==attrname})
    if( x>0 )
        attrval:=this:attrib[x]:value 
        attrval:=substr(attrval,2,len(attrval)-2) //idézőjelek
    end
    return attrval


****************************************************************************
static function gettext(this)
local i, c, x:=""
    for i:=1 to len(this:content)
        c:=this:content[i] 
        if( c:type=="#TEXT" .or. c:type=="#CDATA" )
            x+=c:content[1]
        end
    next
    return x


****************************************************************************
static function xmlout(this) 
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
    return NIL


****************************************************************************
