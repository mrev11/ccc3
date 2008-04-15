
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
//jttabpane
****************************************************************************
class jttabpane(jtelem) 
    method  initialize
    method  setdialogid

    method  additem
    method  xmladd
    method  xmlput          {|this,x|this:selectedindex:=val(x:gettext)}
    method  xmlget          {|this|alltrim(str(this:selectedindex))}

    method  changed         {|this|this:laststate!=this:selectedindex}
    method  savestate       {|this|this:laststate:=this:selectedindex}
    method  varput          {|this,x|this:selectedindex:=x}
    method  varget          {|this|this:selectedindex}
    method  select          {|this,x|this:selectedindex:=x}
 
    attrib  selectedindex
    attrib  placement

****************************************************************************
static function jttabpane.initialize(this,t,l,b,r) 
    this:(jtelem)initialize(t,l,b,r)
    this:itemlist:={}
    this:selectedindex:=1
    return this

****************************************************************************
static function jttabpane.setdialogid(this,id)     
    this:dialogid:=id
    aeval(this:itemlist,{|i|i:setdialogid(this:dialogid)})
    return id

****************************************************************************
static function jttabpane.additem(this,item)     
    item:setdialogid(this:dialogid)
    aadd(this:itemlist,item) 
    return item

****************************************************************************
static function jttabpane.xmladd(this) 
local n, x:=""
    for n:=1 to len(this:itemlist)
        x+=this:itemlist[n]:xmlout+EOL
    next
    if( this:selectedindex!=1 )
        x+="<selectedindex>"+alltrim(str(this:selectedindex))+"</selectedindex>"+EOL
    end
    if( NIL!=this:placement )
        x+="<placement>"+this:placement+"</placement>"+EOL
    end
    return x
 
****************************************************************************
 