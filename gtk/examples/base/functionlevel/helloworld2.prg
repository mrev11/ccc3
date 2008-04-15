
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

******************************************************************************
function main()
local window, button, box1, sep

    gtk.init()

    window:=gtk.window.new()
    //window:=gtk.window.new_popup()
    gtk.window.set_title(window,"Hello Buttons!")
    gtk.container.set_border_width(window,30)
    //gtk.gobject.signal_connect(window,"delete_event",{||gtk.main_quit(),.f.})
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit(),.f.})

    box1:=gtk.vbox.new(.f.,0)
    gtk.container.add(window,box1)

    button:=gtk.button.new_with_label("Button 1")
    gtk.gobject.signal_connect(button,"clicked",{||callback("Button 1")})
    gtk.box.pack_start(box1, button, .t., .t., 0)
    gtk.widget.show(button)

    button:=gtk.button.new_with_label("Button 2")
    gtk.gobject.signal_connect(button,"clicked",{||callback("Button 2")})
    gtk.box.pack_start(box1,button,.t.,.t.,0)
    gtk.widget.show(button)

    button:=gtk.button.new_with_mnemonic("_Quit")
    gtk.gobject.signal_connect(button,"clicked", {||gtk.widget.destroy(window)})
    gtk.box.pack_end(box1,button,.t.,.t.,0)
    gtk.widget.show(button)

    gtk.widget.show(box1)
    gtk.widget.show(window)
    
    gtk.main()
    ?

******************************************************************************
static function callback(data)
    ? "Hello again - ", data, "was pressed"

******************************************************************************
