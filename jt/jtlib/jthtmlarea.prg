
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
//jthtmlarea
****************************************************************************
class  jthtmlarea(jtelem) 

    method  initialize

    method  xmladd
    method  xmlput          {|this,x|this:text:=x:gettext}
    method  xmlget          {|this|cdataif(this:text)}

    method  changed         {|this|!this:laststate==this:text}
    method  savestate       {|this|this:laststate:=this:text}
 
    attrib  followlink
    method  changeurl


****************************************************************************
static function jthtmlarea.initialize(this,t,l,b,r) 
    this:(jtelem)initialize(t,l,b,r)
    this:followlink:=.t.
    return this

****************************************************************************
static function jthtmlarea.xmladd(this)
local x:=""
    if( !this:followlink )
        x+="<followlink>"
        x+=if(this:followlink,"true","false")
        x+="</followlink>"
    end
    return x

****************************************************************************
static function jthtmlarea.changeurl(this,v)
local x
    if( v!=NIL )
        this:text:=v
    end
    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<changeurl>"
    x+=cdataif(this:text)
    x+="</changeurl>"
    x+="</jtmessage>"
    this:send(x)
    return NIL
 
****************************************************************************
