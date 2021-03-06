
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
    
  window := gtk.window.new ()
  gtk.window.set_title (window, "Frame Example")
  gtk.gobject.signal_connect (window, "destroy", {||gtk.main_quit()})
  gtk.widget.set_size_request (window, 300, 300)
  gtk.container.set_border_width (window, 10)

  frame := gtk.frame.new ()
  gtk.container.add (window, frame)
  gtk.frame.set_label (frame, "GTK Frame Widget")
  gtk.frame.set_label_align (frame, 1.0, 0.0)
  //gtk.frame.set_shadow_type(frame,GTK_SHADOW_NONE)
  gtk.frame.set_shadow_type (frame, GTK_SHADOW_ETCHED_IN)

  gtk.widget.show (frame)
  gtk.widget.show (window)
  gtk.main ()
  ?

