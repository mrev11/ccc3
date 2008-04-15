
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
   
   
******************************************************************************
function main()

local window, vpaned, b1,b2

    gtk.init()
   
    window:=gtk.window.new()
    gtk.window.set_title(window,"Paned Windows")
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,10)
    gtk.widget.set_size_request(window,350,300)

    vpaned:=gtk.vpaned.new()
    gtk.container.add(window,vpaned)
    
    gtk.paned.add1(vpaned, b1:=gtk.button.new_with_label("Press me UPPER"))
    gtk.paned.add2(vpaned, b2:=gtk.button.new_with_label("Press me LOWER"))
    
    gtk.gobject.signal_connect(b1,"clicked",{|w|clicked(w)})
    gtk.gobject.signal_connect(b2,"clicked",{|w|clicked(w)})

    gtk.widget.show_all(window)
    gtk.main()

******************************************************************************
static function clicked(w)
    ? gtk.button.get_label(w)


******************************************************************************
