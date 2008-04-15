
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

******************************************************************************
function main()
local window, button

    gtk.init()
    window:=gtkwindowNew()
    window:signal_connect("delete_event",{||cb_delete()})
    window:signal_connect("destroy",{||cb_destroy()})
    window:set_border_width(30)

    //button:=gtkbuttonNew("Hello _World")
    //button:=gtkbuttonNew_with_label("Hello World")
    //button:=gtkbuttonNew_with_mnemonic("_Hello World")
    button:=gtkbuttonNew_with_mnemonic("_Öt szép szűzlány")
    button:signal_connect("clicked",{||cb_hello()})
    button:signal_connect("clicked",{||window:destroy})


    window:add(button)

    window:show_all
    gtk.main()


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
