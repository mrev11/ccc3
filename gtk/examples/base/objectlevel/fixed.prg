
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

static x := 50
static y := 50

******************************************************************************
static function move_button(widget,fixed)
    x := (x + 30) % 300
    y := (y + 50) % 300
    fixed:move(widget,x,y) 

******************************************************************************
function main()

local window, fixed, button, i

    gtk.init()
    
    window:=gtkwindowNew()
    window:set_title("Fixed Container")
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(10)

    fixed:=gtkfixedNew()
    window:add(fixed)
  
    for i:=1 to 3
        button:=gtkbuttonNew("Press me")
        button:signal_connect("clicked",{|w|move_button(w,fixed)})
        fixed:put(button,i*50,i*50)
    next

    window:show_all
    gtk.main()

******************************************************************************
