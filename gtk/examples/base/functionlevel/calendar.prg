
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

local window, cal

  gtk.init()
    
  window := gtk.window.new ()
  gtk.window.set_title (window, "Calendar Example")
  gtk.gobject.signal_connect (window, "destroy", {||gtk.main_quit()})
  gtk.widget.set_size_request (window, 300, 300)
  gtk.container.set_border_width (window, 10)

  cal := gtk.calendar.new ()
  gtk.container.add (window, cal)
  gtk.gobject.signal_connect(cal,"day_selected",{||cb_day_selected(cal)})

  gtk.widget.show (cal)
  gtk.widget.show (window)
  gtk.main ()
  ?

******************************************************************************
static function cb_day_selected(w)
    ? gtk.calendar.get_date(w)

******************************************************************************
    