
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
   
    window:=gtk.window.new()
    gtk.window.set_title(window,"Aspect Frame")
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,10)
   
    aspect_frame:=gtk.aspect_frame.new("2x1",0.5,0.5,2,FALSE)

    // "2x1"    label
    // 0.5      center x
    // 0.5      center y
    // 2        xsize/ysize = 2
    // FALSE    ignore child's aspect
   
    gtk.container.add(window,aspect_frame)
   
    drawing_area:=gtk.drawing_area.new()
   
    // Ask for a 200x200 window, 
    // but the AspectFrame will give us a 200x100
    // window since we are forcing a 2x1 aspect ratio */

    gtk.widget.set_size_request(drawing_area,200,200)
    gtk.container.add(aspect_frame,drawing_area)
   
    gtk.widget.show_all(window)
    gtk.main()
    ?
