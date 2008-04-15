
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
   
function main()
local window, aspect_frame, drawing_area   

    gtk.init()
   
    window:=gtkwindowNew()
    window:set_title("Aspect Frame")
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(10)
   
    aspect_frame:=gtkaspectframeNew("2x1 öőüű",0.5,0.5,2,FALSE)

    // "2x1"    label
    // 0.5      center x
    // 0.5      center y
    // 2        xsize/ysize = 2
    // FALSE    ignore child's aspect
   
    window:add(aspect_frame)
   
    drawing_area:=gtkdrawingareaNew()
   
    // Ask for a 200x200 window, 
    // but the AspectFrame will give us a 200x100
    // window since we are forcing a 2x1 aspect ratio */

    drawing_area:set_size_request(200,200)
    aspect_frame:add(drawing_area)
   
    window:show_all
    gtk.main()
    ?
