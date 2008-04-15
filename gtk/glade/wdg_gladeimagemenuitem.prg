
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
class gladeimagemenuitem(gtkimagemenuitem,gladewidget) new:
    method initialize

****************************************************************************
static function gladeimagemenuitem.initialize(this)
local label:=TEXT2(this:widget_hash:get("label"),this:widgetid)
local stock:=FLAG1(this:widget_hash:get("use_stock"))
    if( stock )
        this:gobject:=gtk.image_menu_item.new_from_stock(label,this:accelgroup)
    else
        this:gobject:=gtk.image_menu_item.new_with_mnemonic(label)
    end
    return this

****************************************************************************
