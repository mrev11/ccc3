
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
class gladetogglebutton(gtktogglebutton,gladewidget) new:
    method initialize

****************************************************************************
static function gladetogglebutton.initialize(this)

//nincsen new_from_stock

local label:=this:widget_hash:get("label")
local use_stock:=this:widget_hash:get("use_stock")
local active:=this:widget_hash:get("active")
local focus_on_click:=this:widget_hash:get("focus_on_click")

    if( label==NIL )
        this:gobject:=gtk.toggle_button.new()
    else
        this:gobject:=gtk.toggle_button.new_with_mnemonic(label)
        if( use_stock!=NIL )
            //ilyenkor a label-ben van a stock-id
            this:set_use_stock(FLAG1(use_stock))
        end
    end

    if( active!=NIL )
        this:set_active(FLAG1(active))
    end

    if( focus_on_click!=NIL )
        this:set_focus_on_click(FLAG1(focus_on_click))
    end

    return this

****************************************************************************
