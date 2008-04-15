
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

//Hogyan lehet megkapni a begépelt szöveget?

#include "gtk.ch"

******************************************************************************
function main()
local window
    gtk.init()
    window:=make_window()
    window:show_all()
    gtk.main()

******************************************************************************
function make_window()

local window
local combo

    window:=gtkwindowNew()
    window:set_title("GtkComboBox")
    //window:set_default_size(280,50)
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(8)
    
    combo:=gtkcomboboxentryNew_text()
    combo:append_text("First choice")
    combo:append_text("Second choice")
    combo:append_text("Third choice")
    combo:append_text("Fourth choice")

    combo:signal_connect("changed",{|w|cb_changed(w)})
    combo:get_child:cast(gtkentryClass()):signal_connect("activate",{|w|cb_activate(w)})
    combo:set_active(0) //-1: deselect
    
    window:add(combo)
   
    return window


******************************************************************************
static function cb_activate(entry)
    ? "activate:", entry:get_text

******************************************************************************
static function cb_changed(combo)
    ? "changed:", combo:get_child:cast(gtkentryClass()):get_text
    //? "changed:", combo:get_active, combo:get_active_text
    //? combo:get_child
    //? combo:get_child:type_name

******************************************************************************
