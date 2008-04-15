
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

#include "jtelem.ch"

****************************************************************************
//jttextarea
****************************************************************************
class  jttextarea(jtelem) 
    method  initialize

    method  xmladd
    method  xmlput              {|this,x|this:text:=x:gettext}
    method  xmlget              {|this|cdataif(this:text)}

    method  changed             {|this|!this:laststate==this:text}
    method  savestate           {|this|this:laststate:=this:text}
    method  changelinewrap

    attrib  editable
    attrib  linewrap

****************************************************************************
static function jttextarea.initialize(this,t,l,b,r) 
    this:(jtelem)initialize(t,l,b,r)
    this:editable:=.t.
    this:linewrap:=.f.
    return this

****************************************************************************
static function jttextarea.xmladd(this)
local x:=""
    if( !this:editable )
        x+="<editable>"
        x+=if(this:editable,"true","false")
        x+="</editable>"
    end
    if( this:linewrap )
        x+="<linewrap>"
        x+=if(this:linewrap,"true","false")
        x+="</linewrap>"
    end
    return x

****************************************************************************
static function jttextarea.changelinewrap(this,v)
local x
    if( v!=NIL )
        this:linewrap:=v
    end
    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<linewrap>"
    x+=if(this:linewrap,"true","false")
    x+="</linewrap>"
    x+="</jtmessage>"
    this:send(x)
    return NIL
 

****************************************************************************
