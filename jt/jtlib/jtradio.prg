
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
function jtradiogroup()
local grp:={}
    return {||grp}
 
****************************************************************************
//jtradio
****************************************************************************
class jtradio(jtelem) 
    method  initialize

    method  xmladd
    method  xmlput          {|this,x|this:state:=(x:gettext=="true")}
    method  xmlget          {|this|if(this:state,"true","false")}

    method  changed         {|this|this:laststate!=this:state}
    method  savestate       {|this|this:laststate:=this:state}
    method  varput          {|this,x|this:state:=x}
    method  varget          {|this|this:state}

    method  setgroup
    method  select
    attrib  group
    attrib  state
    attrib  selectedicon

****************************************************************************
static function jtradio.initialize(this,t,l,b,r,x) 
    if( valtype(t)=="C" )
        this:(jtelem)initialize()
        this:text:=t
    else
        this:(jtelem)initialize(t,l,b,r)
        this:text:=if(x==NIL,"",x) 
    end
    this:state:=.f.
    this:selectedicon:=NIL
    return this

****************************************************************************
static function jtradio.setgroup(this,group)
local g,i

    if( this:group!=NIL ) //ha már van csoportja, kivesszük
        g:=eval(this:group)
        if( 0<(i:=ascan(g,{|rb|this==rb})) )
            adel(g,i)
            asize(g,len(g)-1)
        end
    end

    this:group:=group
    aadd(eval(group),this)
    return NIL

****************************************************************************
static function jtradio.select(this)
local n, g:=eval(this:group)
    for n:=1 to len(g)
        g[n]:state:=(this==g[n])
    next
    return NIL

****************************************************************************
static function jtradio.xmladd(this)
local x:=""
    if( this:state )
        x+="<selected/>"
    end
    if( !empty(this:selectedicon) )
        x+="<selectedicon>"+this:selectedicon+"</selectedicon>"
    end
    return x
 
****************************************************************************
 