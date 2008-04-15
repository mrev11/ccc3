
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
local window, button

    gtk.init()
    window:=gtk.window.new(GTK_WINDOW_TOPLEVEL)
    button:=gtk.button.new_with_label("Hello World")
    gtk.container.add(window,button)
    gtk.container.set_border_width(window,30)

    gtk.gobject.signal_connect(button,"clicked",{||cb_hello()})
    gtk.gobject.signal_connect(button,"clicked",{||gtk.widget.destroy(window)})
    gtk.gobject.signal_connect(window,"delete_event",{||cb_delete()})
    gtk.gobject.signal_connect(window,"destroy",{||cb_destroy()})

    gtk.widget.show(button)
    gtk.widget.show(window)

    gtk.main()

    return NIL

******************************************************************************
static function cb_hello()
    ? "Hello World"

******************************************************************************
static function cb_delete()
    ? "delete event occured"
    return .t. //.t.-re nem lép ki

******************************************************************************
static function cb_destroy()
    ? "Destroyed"
    ?
    gtk.main_quit()

******************************************************************************
