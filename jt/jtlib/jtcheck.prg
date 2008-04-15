
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
//jtcheck
****************************************************************************
class jtcheck(jtelem) 

    method  initialize

    method  xmladd
    method  xmlput          {|this,x|this:state:=(x:gettext=="true")}
    method  xmlget          {|this|if(this:state,"true","false")}

    method  changed         {|this|this:laststate!=this:state}
    method  savestate       {|this|this:laststate:=this:state}
    method  varput          {|this,x|this:state:=!empty(x)}
    method  varget          {|this|this:state}
 
    method  select          {|this,x|this:state:=!empty(x)}
    attrib  state
    attrib  selectedicon


****************************************************************************
static function jtcheck.initialize(this,t,l,b,r,x) 
    if( valtype(t)=="C" )
        this:(jtelem)initialize
        this:text:=t
    else
        this:(jtelem)initialize(t,l,b,r)
        this:text:=if(x==NIL,"",x) 
    end
    this:state:=.f.
    this:selectedicon:=NIL
    return this

****************************************************************************
static function jtcheck.xmladd(this)
local x:=""
    if( this:state )
        x+="<selected/>"
    end
    if( !empty(this:selectedicon) )
        x+="<selectedicon>"+this:selectedicon+"</selectedicon>"
    end
    return x
 
****************************************************************************
