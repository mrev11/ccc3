
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
local table
local align
local spin1
local spin2
local adjust

    window:=gtkwindowNew()
    window:set_title("GtkSpinButton")
    window:set_default_size(280,50)
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(8)
    
    table:=gtktableNew(2,2,.f.)
    window:add(table)
    table:set_row_spacings(4)
    table:set_col_spacings(4)

    align:=gtkalignmentNew(0,1/2,0,0)    
    align:add(gtklabelNew("First spin (0-100):"))
    spin1:=gtkspinbuttonNew_with_range(0,100,1)
    spin1:signal_connect("value-changed",{|w|cb_value_changed(w)})
    table:attach(align,0,1,0,1)
    table:attach(spin1,1,2,0,1)

    align:=gtkalignmentNew(0,1/2,0,0)    
    align:add(gtklabelNew("Second spin (120-130):"))
    spin2:=gtkspinbuttonNew()
    spin2:signal_connect("value-changed",{|w|cb_value_changed(w)})
    table:attach(align,0,1,1,2)
    table:attach(spin2,1,2,1,2)
    
    adjust:=gtkadjustmentNew(123,120,130,0.01,1,1) 
                        //val=123, min=120, max=130, step=0.01, pge1=1, pge2=1
    spin2:configure(adjust,0,2)
                        //climb=0, decimals=2
   
    return window


******************************************************************************
static function cb_value_changed(spin)
    ? "value-changed:", spin, spin:get_adjustment:get_value

******************************************************************************
