
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
    button:=gtkbuttonNew()
    arrow:=gtkarrowNew(arrow_type, shadow_type)
    button:add(arrow)

    if( arrow_type==GTK_ARROW_UP )
        button:signal_connect("clicked",{||qout("up")})
    elseif( arrow_type==GTK_ARROW_DOWN)
        button:signal_connect("clicked",{||qout("down")})
    elseif( arrow_type==GTK_ARROW_LEFT)
        button:signal_connect("clicked",{||qout("left")})
    elseif( arrow_type==GTK_ARROW_RIGHT)
        button:signal_connect("clicked",{||qout("right")})
    end

    return button


******************************************************************************
function main()
local window, button, box

    gtk.init()

    window:=gtkwindowNew()
    window:set_title("Arrow Buttons")
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(10)

    box:=gtkhboxNew(FALSE,0)
    box:set_border_width(2)
    window:add(box)

    button:=create_arrow_button(GTK_ARROW_UP,GTK_SHADOW_IN)
    box:pack_start(button,FALSE,FALSE,3)

    button:=create_arrow_button(GTK_ARROW_DOWN,GTK_SHADOW_OUT)
    box:pack_start(button,FALSE,FALSE,3)
  
    button:=create_arrow_button(GTK_ARROW_LEFT,GTK_SHADOW_ETCHED_IN)
    box:pack_start(button,FALSE,FALSE,3)
  
    button:=create_arrow_button(GTK_ARROW_RIGHT, GTK_SHADOW_ETCHED_OUT)
    box:pack_start(button,FALSE,FALSE,3)
  
    window:show_all
    gtk.main()
    ?

******************************************************************************

