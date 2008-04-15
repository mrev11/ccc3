
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
local window, button, table

    gtk.init()

    window:=gtk.window.new (GTK_WINDOW_TOPLEVEL)
    gtk.window.set_title (window, "Table")
    //gtk.gobject.signal_connect(window,"delete_event",{||gtk.main_quit(),.f.})
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,20)

    table:=gtk.table.new(2,2,.t.)
    gtk.container.add(window,table)
    gtk.table.set_row_spacings(table,4)
    gtk.table.set_col_spacings(table,4)

    // first button

    button:=gtk.button.new_with_label("button 1")
    gtk.gobject.signal_connect(button,"clicked",{||callback("button 1")})
    //Insert button 1 into the upper left quadrant of the table 
    gtk.table.attach(table,button, 0, 1, 0, 1)
    gtk.widget.show(button)

    // second button

    button:=gtk.button.new_with_label("button 2")
    gtk.gobject.signal_connect(button,"clicked",{||callback("button 2")})
    //Insert button 2 into the upper right quadrant of the table 
    gtk.table.attach (table, button, 1, 2, 0, 1)
    gtk.widget.show (button)

    // "Quit" button
    button:=gtk.button.new_with_label("Quit")
    gtk.gobject.signal_connect(button,"clicked",{||gtk.widget.destroy(window)})
    //Insert the quit button into the both lower quadrants of the table
    gtk.table.attach(table, button, 0, 2, 1, 2)
    gtk.widget.show (button)

    gtk.widget.show(table)
    gtk.widget.show(window)

    gtk.main()
    ?
******************************************************************************
static function callback(data)
    ? "Hello again - ",data,"was pressed"

******************************************************************************
