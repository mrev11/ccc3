
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
class gladelabel(gtklabel,gladewidget) new:
    method initialize

****************************************************************************
static function gladelabel.initialize(this)

local label:=TEXT2(this:widget_hash:get("label"),this:widgetid)
local use_markup:=this:widget_hash:get("use_markup")
local xa:=this:widget_hash:get("xalign")
local ya:=this:widget_hash:get("yalign")
local xp:=this:widget_hash:get("xpad")
local yp:=this:widget_hash:get("ypad")

    if( "_"$label )
        this:gobject:=gtk.label.new_with_mnemonic(label)
    else
        this:gobject:=gtk.label.new(label)
    end

    if( xa!=NIL .or. ya!=NIL )
        this:set_alignment(VAL2(xa,0.5),VAL2(ya,0.5))
    end

    if( xp!=NIL .or. yp!=NIL )
        this:set_padding(VAL2(xp,0),VAL2(yp,0))
    end
    
    if( use_markup!=NIL )
        this:set_use_markup(FLAG1(use_markup))
    end

    return this

****************************************************************************
