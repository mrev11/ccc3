
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

#define FALSE .f.
#define TRUE  .t.

******************************************************************************
function main()

local window, box1, box2
local button, separator
local group
  
    gtk.init()
      
    window:=gtk.window.new()
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.window.set_title (window,"radio buttons")
    gtk.container.set_border_width(window,0)

    box1:=gtk.vbox.new(FALSE, 0)
    gtk.container.add(window,box1)
    gtk.widget.show(box1)

    box2:=gtk.vbox.new(FALSE,10)
    gtk.container.set_border_width(box2, 10)
    gtk.box.pack_start(box1, box2, TRUE, TRUE, 0)
    gtk.widget.show(box2)

    button:=gtk.radio_button.new_with_label(NIL,"button1")
    gtk.box.pack_start(box2, button, TRUE, TRUE, 0)
    gtk.widget.show(button)

    group:=gtk.radio_button.get_group(button)
    button:=gtk.radio_button.new_with_label(group, "button2")
    gtk.toggle_button.set_active(button, TRUE)
    gtk.box.pack_start(box2, button, TRUE, TRUE, 0)
    gtk.widget.show (button)

    button:=gtk.radio_button.new_with_label_from_widget(button,"button3")
    gtk.box.pack_start(box2, button, TRUE, TRUE, 0)
    gtk.widget.show(button)

    separator:=gtk.hseparator.new ()
    gtk.box.pack_start(box1, separator, FALSE, TRUE, 0)
    gtk.widget.show(separator)

    box2:=gtk.vbox.new(FALSE, 10)
    gtk.container.set_border_width(box2, 10)
    gtk.box.pack_start(box1, box2, FALSE, TRUE, 0)
    gtk.widget.show(box2)

    button:=gtk.button.new_with_label("close")
    gtk.gobject.signal_connect(button,"clicked",{||gtk.widget.destroy(window)})

    gtk.box.pack_start(box2, button, TRUE, TRUE, 0)

    //!GTK_widget.SET_FLAGS(button, GTK_CAN_DEFAULT)

    gtk.widget.grab_default(button)
    gtk.widget.show (button)
    gtk.widget.show (window)
     
    gtk.main()
    
    ?

******************************************************************************

