
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

local window, vbox
local menu_bar, root_menu, menu, menu_item
local icon

    gtk.init ()

    icon:=gtkstatusiconnew()
    icon:set_from_icon_name(GTK_STOCK_HOME)

    window:=gtkwindowNew()
    window:set_size_request(200,100)
    window:set_title("GTK Menu Test")
    window:signal_connect("delete_event",{||gtk.main_quit()})
    vbox:=gtkvboxNew(.f.,0)
    window:add(vbox)

    menu_bar:=gtkmenubarNew()
    root_menu:=gtkmenuitemNew_with_label("Menü")
    menu_bar:append(root_menu)

    menu:=gtkmenuNew()
    menu_item:=gtkmenuitemNew_with_label("Home")
    menu:append(menu_item)
    menu_item:signal_connect("activate",{||icon:set_from_icon_name(GTK_STOCK_HOME)})
    menu_item:=gtkmenuitemNew_with_label("Ok")
    menu:append(menu_item)
    menu_item:signal_connect("activate",{||icon:set_from_icon_name(GTK_STOCK_OK)} )

    root_menu:set_submenu(menu)

    vbox:pack_start(menu_bar,.f.,.f.,2)
    window:show_all
    gtk.main ()

