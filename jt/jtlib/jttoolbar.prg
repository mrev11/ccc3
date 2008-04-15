
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
//jttoolbar
****************************************************************************
class  jttoolbar(jtelem) 
    method  initialize
    attrib  orientation
    attrib  defaultradiogroup
    attrib  floatable
    method  setdialogid
    method  additem
    method  xmladd
    method  xmlname         {||"jttoolbar"}

****************************************************************************
static function jttoolbar.initialize(this) 
    this:(jtelem)initialize
    this:orientation:=NIL
    this:floatable:=NIL //.f.
    this:itemlist:={}
    this:defaultradiogroup:=jtradiogroup()
    this:name:=""
    return this

****************************************************************************
static function jttoolbar.setdialogid(this,id)     
    this:dialogid:=id
    aeval(this:itemlist,{|i|i:setdialogid(this:dialogid)})
    return id


****************************************************************************
static function jttoolbar.additem(this,item)     
    item:setdialogid(this:dialogid)
    aadd(this:itemlist,item) 
    if( item:classname=="jtradio" .and. item:group==NIL )
        item:setgroup(this:defaultradiogroup)
    end
    return item

 
****************************************************************************
static function jttoolbar.xmladd(this) 
local n, x:=""
    if( !empty(this:orientation) )
        x+="<orientation>"+this:orientation+"</orientation>"
    end
    if( this:floatable!=NIL )
        x+="<floatable>"+if(this:floatable,"true","false")+"</floatable>"
    end
    x+=EOL 
    for n:=1 to len(this:itemlist)
        x+=this:itemlist[n]:xmlout+EOL
    next
    return x
 
****************************************************************************
 
