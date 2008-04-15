
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

#include "gtk.ch"
#include "gladeutil.ch"

****************************************************************************
class gladetoolbutton(gtktoolbutton,gladewidget) new:
    method initialize

****************************************************************************
static function gladetoolbutton.initialize(this)
local stock_id:=this:widget_hash:get("stock_id")
local label:=this:widget_hash:get("label")
    if( stock_id!=NIL )
        this:gobject:=gtk.tool_button.new_from_stock(stock_id)
    else
        this:gobject:=gtk.tool_button.new()
    end
    if( label!=NIL )
        this:set_label(label)
    end
    
    return this

****************************************************************************
