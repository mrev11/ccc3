
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

//#include "gtk.ch"

******************************************************************************
function main()
local window, button, table

    gtk.init()

    window:=gtkwindowNew()
    window:set_title("Table")
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(20)

    table:=gtktableNew(2,2,.t.)
    table:set_row_spacings(4)
    table:set_col_spacings(4)
    window:add(table)

    // first button

    button:=gtkbuttonNew("button 1")
    button:signal_connect("clicked",{||callback("button 1")})
    //Insert button 1 into the upper left quadrant of the table 
    table:attach(button, 0, 1, 0, 1)

    // second button

    button:=gtkbuttonNew_with_label("button 2")
    button:signal_connect("clicked",{||callback("button 2")})
    button:signal_connect("clicked",{|x|qout("pressed:",x:get_label)})
    //Insert button 2 into the upper right quadrant of the table 
    table:attach(button, 1, 2, 0, 1)

    // "Quit" button
    button:=gtkbuttonNew("_Quit")
    //button:set_label("Quit")
    ? button:get_label
    button:signal_connect("clicked",{||window:destroy})
    //Insert the quit button into the both lower quadrants of the table
    table:attach(button, 0, 2, 1, 2)

    button:grab_default //ez nem működik

    window:show_all

    gtk.main()
    ?

******************************************************************************
static function callback(data)
    ? "Hello again - ",data,"was pressed"

******************************************************************************
