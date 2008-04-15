
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
//jtprogbar
****************************************************************************
class jtprogbar(jtelem) 
    method  initialize
    method  xmladd
    method  setbar
    method  clearbar
    attrib  caption
    attrib  value
    attrib  minvalue
    attrib  maxvalue

****************************************************************************
static function jtprogbar.initialize(this,t,l,b,r,x) 
    this:(jtelem)initialize(t,l,b,r)
    this:name:="progressbar"
    this:text:=if(x==NIL,"",x) 
    this:value:=0
    this:minvalue:=0
    this:maxvalue:=100
    return this


****************************************************************************
static function jtprogbar.setbar(this,v,t,c)
local x

    if( v!=NIL  )
        this:value:=int(v)
    end

    if( t!=NIL  )
        this:text:=t
    end

    if( c!=NIL  )
        this:caption:=c
    end
 
    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'

    x+="<control>"+this:name+"</control>"

    x+="<setbar>"

    x+="<value>"+alltrim(str(this:value%this:maxvalue))+"</value>" 

    if( t!=NIL )
        x+="<text>"+cdataif(alltrim(this:text))+"</text>" 
    end

    if( c!=NIL )
        x+="<caption>"+cdataif(alltrim(this:caption))+"</caption>" 
    end

    x+="</setbar>"
    x+="</jtmessage>"

    this:send(x)
    this:value++
    return NIL


****************************************************************************
static function jtprogbar.clearbar(this)
local x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<clearbar/>"
    x+="</jtmessage>"
    this:send(x)
    return NIL

 
****************************************************************************
static function jtprogbar.xmladd(this)
local x:=""
    if( this:minvalue!=0 )
        x+="<min>"+alltrim(str(int(this:minvalue)))+"</min>"
    end
    if( this:maxvalue!=0 )
        x+="<max>"+alltrim(str(int(this:maxvalue)))+"</max>"
    end
    if( this:caption!=NIL )
        x+="<caption>"+cdataif(this:caption)+"</caption>"
    end
    return x
 

****************************************************************************
 