
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

static x := 50
static y := 50

******************************************************************************
static function move_button(widget,fixed)
    x := (x + 30) % 300
    y := (y + 50) % 300
    gtk.fixed.move(fixed,widget,x,y) 

******************************************************************************
function main()

local window, fixed, button, i

    gtk.init()
    
    window:=gtk.window.new()
    gtk.window.set_title(window,"Fixed Container")
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,10)

    fixed:=gtk.fixed.new()
    gtk.container.add(window,fixed)
  
    for i:=1 to 3
        button:=gtk.button.new_with_label("Press me")
        gtk.gobject.signal_connect(button,"clicked",{|w|move_button(w,fixed)})
        gtk.fixed.put(fixed, button, i*50, i*50)
    next

    gtk.widget.show_all(window)
    gtk.main()

******************************************************************************
