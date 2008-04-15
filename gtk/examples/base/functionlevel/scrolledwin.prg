
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
    
    window := gtk.dialog.new ()
    gtk.gobject.signal_connect(window, "destroy",{||gtk.main_quit()})
    gtk.window.set_title (window, "GtkScrolledWindow example")
    gtk.container.set_border_width (window, 0)
    gtk.widget.set_size_request ( window, 300, 300)
    
    scrolled_window := gtk.scrolled_window.new ()
    gtk.container.set_border_width (scrolled_window, 10)

    // The policy is one of GTK_POLICY AUTOMATIC, or GTK_POLICY_ALWAYS.
    // AUTOMATIC  will automatically decide whether you need scrollbars, 
    // ALWAYS     will always leave the scrollbars there.  
    gtk.scrolled_window.set_policy(scrolled_window,GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS)

    // The dialog window is created with a vbox packed into it.
    vbox:=gtk.dialog.get_vbox(window)
    gtk.box.pack_start(vbox, scrolled_window,.t.,.t.,0)

    // Create a table of 10 by 10 squares.
    table := gtk.table.new (10, 10, .f.)
    
    // Set the spacing to 10 on x and 10 on y.
    gtk.table.set_row_spacings (table, 10)
    gtk.table.set_col_spacings (table, 10)
    
    // Pack the table into the scrolled window.
    gtk.scrolled_window.add_with_viewport (scrolled_window, table)
    
    // This simply creates a grid of toggle buttons on the 
    // table to demonstrate the scrolled window.
    for i := 1 to 10
        for j:=1 to 10
            buffer:="button("+ltrim(str(i))+","+ltrim(str(j))+")"//+chr(10)
            button := gtk.toggle_button.new_with_label (buffer)
            gtk.gobject.signal_connect(button,"clicked",{|b|cb_button(b)},button)
            //gtk.table.attach (table,button,i,i+1,j,j+1)
            gtk.table.attach (table,button,i-1,i,j-1,j)
        next
    next
    //Benyomva maradnak a buttonok (az eredeti C-ben is), miért?
    
    // Add a "close" button to the bottom of the dialog
    button := gtk.button.new_with_label ("close")
    gtk.gobject.signal_connect (button, "clicked",{||gtk.widget.destroy(window)})
    action_area:=gtk.dialog.get_action_area(window) //box
    gtk.box.pack_start(action_area, button, .t., .t., 0)

    // This grabs this button to be the default button. 
    // Simply hitting the "Enter" will cause this button to activate.
    // Nem működik a default button (az eredeti C-ben sem), miért?
    gtk.widget.grab_default (button)
   
    gtk.widget.show_all (window)
    gtk.main()
    ?

******************************************************************************
static function cb_button(button)
    ? gtk.button.get_label(button)


******************************************************************************
