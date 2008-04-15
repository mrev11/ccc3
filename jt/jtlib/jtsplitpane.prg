
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
//jtsplitpane
****************************************************************************
class  jtsplitpane(jtelem) 
    method  initialize
    attrib  orientation
    attrib  divider
    method  setdialogid
    method  setitem
    method  xmladd

****************************************************************************
static function jtsplitpane.initialize(this,t,l,b,r) 
    this:(jtelem)initialize(t,l,b,r)
    this:itemlist:=array(2)
    this:itemlist[1]:=jtlabelNew("")    //ne szálljon el üresen
    this:itemlist[2]:=this:itemlist[1]  //ne szálljon el üresen
    this:orientation:="ver"             //ver/hor
    this:divider:=0                     //top/left méret
    this:name:=""
    return this

****************************************************************************
static function jtsplitpane.setdialogid(this,id)     
    this:dialogid:=id
    aeval(this:itemlist,{|i|if(i==NIL,NIL,i:setdialogid(this:dialogid))})
    return id

****************************************************************************
static function jtsplitpane.setitem(this,x,item)
    item:setdialogid(this:dialogid)
    this:itemlist[x]:=item
    return item

 
****************************************************************************
static function jtsplitpane.xmladd(this) 
local n, x:=""
    x+="<orientation>"+this:orientation+"</orientation>"+EOL
    if( this:divider!=0  )
        x+="<divider>"+alltrim(str(this:divider))+"</divider>"+EOL
    end
    for n:=1 to len(this:itemlist)
        x+=this:itemlist[n]:xmlout+EOL
    next
    return x
 
****************************************************************************
 