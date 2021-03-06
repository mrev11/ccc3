
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

******************************************************************************
function main()
local window
    gtk.init()
    window:=make_window()
    window:show_all()
    gtk.main()
    ?

******************************************************************************
function make_window()

local window
local button

    window:=gtkwindowNew()
    window:set_title("FontButton")
    window:set_default_size(180,50)
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(8)
    
    button:=gtkfontbuttonNew()
    window:add(button)
    button:set_use_font:=.t.
    button:set_use_size:=.t.
    button:set_show_style:=.t.
    button:set_title("Font Button Demo")
    button:signal_connect("font-set",{|w|cb_font_set(w)})
   
    return window


******************************************************************************
static function cb_font_set(w)
    ? "font-set:", w:get_font_name
    w:set_font_name(w:get_font_name)
    

******************************************************************************
