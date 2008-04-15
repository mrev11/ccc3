
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

****************************************************************************
class tbcolumn(object) 

    method initialize
    method width
    method datawidth
    method color
 
    attrib block
    attrib cargo
    attrib colorblock
    attrib defcolor
    attrib footing
    attrib footsep
    attrib heading
    attrib headsep
    attrib picture

    attrib _width_
    attrib _datawidth_

****************************************************************************
function tbcolumnIni(this,heading,block) //compatibility
    return this:(tbcolumn)initialize(heading,block) 

****************************************************************************
static function tbcolumn.initialize(this,heading,block) 
    this:(object)initialize()
    this:heading:=heading
    this:block:=block
    this:footing:=""
    this:defcolor:={1,2}
    //this:colorblock:={||this:defcolor} 
    return this

**************************************************************************** 
static function tbcolumn.width(this,w)
    if( w!=NIL )
        this:_width_:=w
    elseif( this:_width_==NIL )
        this:_width_:=len(transform(eval(this:block),this:picture))
        this:_width_:=max(this:_width_,len(this:heading))
        this:_width_:=min(this:_width_,maxcol()-2)
    end
    return this:_width_

**************************************************************************** 
static function tbcolumn.datawidth(this)
    if( this:_datawidth_==NIL )
        this:_datawidth_:=len(transform(eval(this:block),this:picture))
        this:_datawidth_:=min(this:_datawidth_,this:_width_) 
    end
    return this:_datawidth_

**************************************************************************** 
static function tbcolumn.color(this,x)  //color index
local cx
    if( this:colorblock==NIL )
        cx:=this:defcolor
    else
        cx:=eval(this:colorblock,x)
    end
    return cx

**************************************************************************** 





