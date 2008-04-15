
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
      
    window:=gtkwindowNew()
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_title("radio buttons")
    window:set_border_width(0)

    box1:=gtkvboxNew(FALSE,0)
    window:add(box1)

    box2:=gtkvboxNew(FALSE,10)
    box2:set_border_width(10)
    box1:pack_start(box2,TRUE,TRUE,0)

    button:=gtkradiobuttonNew_with_label(NIL,"Öt szép szűzlány")
    box2:pack_start(button,TRUE,TRUE,0)

    group:=button:get_group()
    button:=gtkradiobuttonNew_with_label(group,"button2")
    button:set_active(TRUE)
    box2:pack_start(button,TRUE,TRUE,0)

    button:=gtkradiobuttonNew_with_label_from_widget(button,"button3")
    box2:pack_start(button,TRUE,TRUE,0)

    separator:=gtkhseparatorNew()
    box1:pack_start(separator,FALSE,TRUE,0)

    box2:=gtkvboxNew(FALSE,10)
    box2:set_border_width(10)
    box1:pack_start(box2,FALSE,TRUE,0)

    button:=gtkbuttonNew("_Close")
    button:signal_connect("clicked",{||window:destroy})
    box2:pack_start(button,TRUE,TRUE,0)
    //!GTK_widget.SET_FLAGS(button, GTK_CAN_DEFAULT)
    button:grab_default

    window:show_all
    gtk.main()
   
    ?

******************************************************************************

