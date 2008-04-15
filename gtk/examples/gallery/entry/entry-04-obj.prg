
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

******************************************************************************
function make_window()

local window
local table
local align
local entry1
local entry2

    window:=gtkwindowNew()
    window:set_title("GtkEntry")
    window:set_default_size(280,50)
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(8)
    
    table:=gtktableNew(2,2,.f.)
    window:add(table)
    table:set_row_spacings(4)
    table:set_col_spacings(4)

    align:=gtkalignmentNew(1,1/2,0,0)    
    align:add(gtklabelNew("First entry:"))

    entry1:=gtkentryNew()
    entry1:signal_connect("activate",{|w|cb_activate(w)})
    table:attach(align,0,1,0,1)
    table:attach(entry1,1,2,0,1)

    align:=gtkalignmentNew(1,1/2,0,0)    
    align:add(gtklabelNew("Second entry:"))

    entry2:=gtkentryNew()
    entry2:signal_connect("activate",{|w|cb_activate(w)})
    table:attach(align,0,1,1,2)
    table:attach(entry2,1,2,1,2)
   
    return window


******************************************************************************
static function cb_activate(entry)
    ? "activate:", entry, entry:get_text

******************************************************************************
