
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
//jtmenuitem
****************************************************************************
class jtmenuitem(jtelem) 
    method  initialize

****************************************************************************
static function jtmenuitem.initialize(this) 
    this:(jtelem)initialize()
    return this


****************************************************************************
//jtmenucheck 
****************************************************************************
class jtmenucheck(jtcheck) 
    method initialize

****************************************************************************
static function jtmenucheck.initialize(this) 
    this:(jtcheck)initialize()
    return this


****************************************************************************
//jtmenuradio
****************************************************************************
class jtmenuradio(jtradio) 
    method  initialize

****************************************************************************
static function jtmenuradio.initialize(this) 
    this:(jtradio)initialize()
    return this
 
 
****************************************************************************
//jtmenusep
****************************************************************************
class jtmenusep(jtelem) 
    method  initialize
    method  xmlout

****************************************************************************
static function jtmenusep.initialize(this) 
    this:(jtelem)initialize
    return this

****************************************************************************
static function jtmenusep.xmlout(this) 
    return "<jtmenusep/>" 


****************************************************************************
//jtmenu
****************************************************************************
class  jtmenu(jtelem) 
    method  initialize
    attrib  defaultradiogroup
    method  setdialogid
    method  additem
    method  xmladd


****************************************************************************
static function jtmenu.initialize(this) 
    this:(jtelem)initialize
    this:itemlist:={}
    this:defaultradiogroup:=jtradiogroup()
    return this

****************************************************************************
static function jtmenu.setdialogid(this,id)     
    this:dialogid:=id
    aeval(this:itemlist,{|i|i:setdialogid(this:dialogid)})
    return id

****************************************************************************
static function jtmenu.additem(this,item)     
    item:setdialogid(this:dialogid)
    aadd(this:itemlist,item) 
    if( item:classname=="jtmenusep" )
        this:defaultradiogroup:=jtradiogroup()
    elseif( item:classname=="jtmenuradio" .and. item:group==NIL )
        item:setgroup(this:defaultradiogroup)
    end
    return item

****************************************************************************
static function jtmenu.xmladd(this) 
local n, x:=EOL
    for n:=1 to len(this:itemlist)
        x+=this:itemlist[n]:xmlout+EOL
    next
    return x
 
****************************************************************************
 