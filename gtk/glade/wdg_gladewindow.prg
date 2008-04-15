
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
class gladewindow(gtkwindow,gladewidget) new:
    method initialize

****************************************************************************
static function gladewindow.initialize(this)

local type:=GTKSYM2(this:widget_hash:get("type"),GTK_WINDOW_TOPLEVEL)
local defwidth:=VAL2(this:widget_hash:get("default_width"),300)
local defheight:=VAL2(this:widget_hash:get("default_height"),200)
local title:=TEXT2(this:widget_hash:get("title"),this:widgetid)
local resize:=FLAG2(this:widget_hash:get("resizable"),.t.)
local modal:=FLAG2(this:widget_hash:get("modal"),.f.)
local window_position:=GTKSYM2(this:widget_hash:get("window_position"),1)

    this:gobject:=gtk.window.new(type)
    this:set_title(title)
    this:set_default_size(defwidth,defheight)
    this:set_resizable(resize)
    this:set_modal(modal)
    this:set_position(window_position)

    if( this:accelgroup!=NIL )    
        this:add_accel_group(this:accelgroup)
    end
   
    return this

****************************************************************************
