
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
local icon1,menu
local icon2

    gtk.init()

    menu:=mkmenu()

    icon1:=gtkstatusiconNew_from_stock("gtk-execute") 
    icon1:liststruct
    icon1:set_visible(.t.) //default
    icon1:set_tooltip("Próba szerencse")
    icon1:signal_connect("activate",{||qout("activate")}) //bal gomb
    //icon1:signal_connect("popup-menu",{||qout("popup-menu"),menu:popup}) //jobb gomb
    icon1:signal_connect("popup-menu",{||qout("popup-menu"),icon1:popup(menu)}) //jobb gomb

    //icon2:=gtkstatusiconNew_from_stock("gtk-cancel") 
    icon2:=gtkstatusiconNew() 
    icon2:set_from_stock("gtk-cancel") 


    icon2:signal_connect("activate",{||proba(icon1,icon2)}) 
    icon2:set_blinking(.t.)

    gtk.main()

******************************************************************************
static function mkmenu()
local menu:=gtkmenuNew()
local buf,i,menu_item
    for i:=1 to 6
        buf:="Öt szép szűzlány örült írót nyúz"+str(i)
        menu_item:=gtkmenuitemNew_with_label(buf)
        menu:append(menu_item)
        menu_item:signal_connect("activate",blkresponse(buf))
    next 
    menu:show_all //enélkül nem jelenik meg!
    return menu

static function blkresponse(buf)
    return {||menuitem_response(buf)}

static function menuitem_response(data)
    ? data

******************************************************************************
static function proba(icon1,icon2)
    ? "blinking1",icon1:get_blinking
    ? "blinking2",icon2:get_blinking
    ? "embedded1",icon1:is_embedded
    ? "embedded2",icon2:is_embedded
    ? "stock1",icon1:get_stock
    ? "stock2",icon2:get_stock
    ? "storage1",icon1:get_storage_type
    ? "storage2",icon2:get_storage_type
    //? "screen1",icon1:get_screen
    //? "screen2",icon2:get_screen
    ? "size1",icon1:get_size
    ? "size2",icon2:get_size
    
    icon1:set_from_stock("gtk-about")

******************************************************************************
