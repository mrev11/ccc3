
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

function main()

local window, frame

    gtk.init()
    
    window:=gtkwindowNew()
    //window:liststruct
    window:set_title("Frame Example")
    window:signal_connect("destroy",{||gtk.main_quit()})      
    window:set_size_request(300,300)
    window:set_border_width(10)

    frame:=gtkframeNew()
    //frame:=gtkframeNew("XXX-YYY")
    frame:set_label("GTK Frame Widget")
    frame:set_label_align(1,0)
    frame:set_shadow_type(GTK_SHADOW_ETCHED_IN)
    window:add(frame)

    window:show_all

    gtk.main()
    ?

