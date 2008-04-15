
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
local scrolled_window, table, button
local vbox,action_area,buffer, i, j
    
    gtk.init()
    
    window:=gtkdialogNew()
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_title("GtkScrolledWindow example")
    window:set_border_width(0)
    window:set_size_request(300,300)
    
    scrolled_window:=gtkscrolledwindowNew()
    scrolled_window:set_border_width(10)

    // The policy is one of GTK_POLICY AUTOMATIC, or GTK_POLICY_ALWAYS.
    // AUTOMATIC  will automatically decide whether you need scrollbars, 
    // ALWAYS     will always leave the scrollbars there.  

    scrolled_window:set_policy(GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS)

    vbox:=window:get_vbox()
    vbox:pack_start(scrolled_window,.t.,.t.,0)

    table:=gtktableNew(10,10,.f.)
    table:set_row_spacings(10)
    table:set_col_spacings(10)
    
    scrolled_window:add_with_viewport(table)
    
    for i := 1 to 10
        for j:=1 to 10
            buffer:="button("+ltrim(str(i))+","+ltrim(str(j))+")"
            button:=gtktogglebuttonNew(buffer)
            //button:=gtktogglebuttonNew_with_label(buffer)
            //button:=gtkbuttonNew(buffer)
            button:signal_connect("clicked",{|w|cb_button(w)})
            table:attach(button,i-1,i,j-1,j)
        next
    next
    
    // Add a "close" button to the bottom of the dialog
    button:=gtkbuttonNew("close")
    button:signal_connect("clicked",{||window:destroy})
    action_area:=window:get_action_area //box
    action_area:pack_start(button,.t.,.t.,0)

    // This grabs this button to be the default button. 
    // Simply hitting the "Enter" will cause this button to activate.
    // Nem működik a default button (az eredeti C-ben sem), miért?
    button:grab_default

    window:show_all
    gtk.main()
    ?

******************************************************************************
static function cb_button(widget)
    ? widget
    ? widget:get_label


******************************************************************************
