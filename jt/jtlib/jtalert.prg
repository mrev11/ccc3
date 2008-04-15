
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

******************************************************************************
function jtalert(msg,opt,cap)
    msg:="<html><p>"+strtran(msg,";","<p>")
    opt:=if(opt==NIL,{@"OK"},opt)
    cap:=if(cap==NIL,argv(0),cap)
    return jtalertNew(msg,opt,cap):loop
 
****************************************************************************
class jtalert(object) 
    method  initialize
    method  xmlout
    method  loop
    attrib  message
    attrib  caption
    attrib  type
    attrib  options

****************************************************************************
static function jtalert.initialize(this,msg,opt,cap) 
    this:(object)initialize
    this:message:=msg
    this:options:=if(opt==NIL,{},opt)
    this:caption:=if(cap==NIL,"",cap)
    this:type:=if(len(opt)<=1,"w","q")
    return this

****************************************************************************
static function jtalert.xmlout(this)
local x, n
    x:="<jtalert>"
    x+="<message>"+cdataif(this:message)+"</message>" 
    x+="<caption>"+cdataif(this:caption)+"</caption>" 
    x+="<options>"
    for n:=1 to len(this:options)
        x+="<opt>"+cdataif(this:options[n])+"</opt>" 
    next
    x+="</options>"
    x+="<type>"+this:type+"</type>" 
    x+="</jtalert>"
    return x

****************************************************************************
static function jtalert.loop(this)
local rsp,dom,node
    jtsocket():send(this:xmlout)
    while( (rsp:=jtsocket():recv)!=NIL  )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="alert" )
            return val(node:gettext) 
        end
    end
    return 0 

****************************************************************************
 