
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

#define FALSE .f.
#define TRUE  .t.

******************************************************************************
static function create_arrow_button(arrow_type, shadow_type)
local button, arrow
    button:=gtk.button.new()
    arrow:=gtk.arrow.new(arrow_type, shadow_type)
    gtk.container.add(button,arrow)
    return button


******************************************************************************
function main()
local window, button, box

    gtk.init()

    window:=gtk.window.new()
    gtk.window.set_title(window,"Arrow Buttons")
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,10)

    box:=gtk.hbox.new(FALSE,0)
    gtk.container.set_border_width(box,2)
    gtk.container.add(window,box)

    button:=create_arrow_button(GTK_ARROW_UP,GTK_SHADOW_IN)
    gtk.box.pack_start(box,button,FALSE,FALSE,3)

    button:=create_arrow_button(GTK_ARROW_DOWN,GTK_SHADOW_OUT)
    gtk.box.pack_start(box,button,FALSE,FALSE,3)
  
    button:=create_arrow_button(GTK_ARROW_LEFT,GTK_SHADOW_ETCHED_IN)
    gtk.box.pack_start(box,button,FALSE,FALSE,3)
  
    button:=create_arrow_button(GTK_ARROW_RIGHT, GTK_SHADOW_ETCHED_OUT)
    gtk.box.pack_start(box,button,FALSE,FALSE,3)
  
    gtk.widget.show_all(window)
    gtk.main()
    ?

******************************************************************************

