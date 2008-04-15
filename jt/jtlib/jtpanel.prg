
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
//jtpanel
****************************************************************************
class jtpanel(jtelem) 
    method  initialize
    attrib  hscroll
    attrib  vscroll
    attrib  layout
    attrib  defaultradiogroup
    method  setdialogid
    method  additem
    method  xmladd
    method  xmlname             {||"jtpanel"}


****************************************************************************
static function jtpanel.initialize(this,t,l,b,r,x) 

    if( valtype(t)=="C"  )
        this:(jtelem)initialize()
        this:text:=t
    else
        this:(jtelem)initialize(t,l,b,r)
        if( x!=NIL )
            this:text:=x
        end
    end 

    this:hscroll:=.f.
    this:vscroll:=.f.
    this:layout:="hbox"
    this:itemlist:={}
    this:defaultradiogroup:=jtradiogroup()
    this:name:=""
    return this

function jtpanelIni(this,t,l,b,r)//compatibility
    return this:(jtpanel)initialize(t,l,b,r)

****************************************************************************
static function jtpanel.setdialogid(this,id)     
    this:dialogid:=id
    aeval(this:itemlist,{|i|i:setdialogid(this:dialogid)})
    return id


****************************************************************************
static function jtpanel.additem(this,item)     
    item:setdialogid(this:dialogid)
    aadd(this:itemlist,item) 
    if( item:classname=="jtradio" .and. item:group==NIL )
        item:setgroup(this:defaultradiogroup)
    end
    return item

 
****************************************************************************
static function jtpanel.xmladd(this) 
local n, x:=""

    if( this:hscroll )
        x+="<hscroll/>"
    end
    if( this:vscroll )
        x+="<vscroll/>"
    end
    if( !empty(this:layout) )
        x+="<layout>"+this:layout+"</layout>"
    end

    x+=EOL 
    for n:=1 to len(this:itemlist)
        x+=this:itemlist[n]:xmlout+EOL
    next
    return x
 
****************************************************************************
 