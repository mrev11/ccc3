
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

#include "gdk.ch"
#include "gtk.ch"

#define FALSE .f.
#define TRUE  .t.

*******************************************************************************
function main()

local window, vbox
local menu_bar, root_menu, menu, menu_item
local button, buf, i

    gtk.init ()

    window:=gtkwindowNew()
    window:set_size_request(200,100)
    window:set_title("GTK Menu Test")
    window:signal_connect("delete_event",{||gtk.main_quit(),FALSE})
    vbox:=gtkvboxNew(FALSE,0)
    window:add(vbox)

    menu_bar:=gtkmenubarNew()
    root_menu:=gtkmenuitemNew_with_label("Vanaki forrón")
    menu_bar:append(root_menu)
    menu:=gtkmenuNew()
    //menu:liststruct
    for i:=1 to 3
        buf:="Öt szép szűzlány"+str(i)
        menu_item:=gtkmenuitemNew_with_label(buf)
        menu:append(menu_item)
        menu_item:signal_connect("activate",blkresponse(buf))
    next 
    root_menu:set_submenu(menu)

    button:=gtkbuttonNew_with_label("Próba szerencse")
    button:signal_connect("event",{|w,e|button_press(w,e,menu)})

    vbox:pack_start(menu_bar,FALSE,FALSE,2)
    vbox:pack_end(button,TRUE,TRUE,2)
    window:show_all
    gtk.main ()
    ?

*******************************************************************************
static function button_press(button,event,menu) //egyszerűsítve

// button : ezt nyomták meg (nem kell)
// event  : esemény, bármilyen típusú lehet
// menu   : ezt a menüt kell felrakni

    if( gdk.event.get_type(event)==GDK_BUTTON_PRESS )
        menu:popup
        return TRUE // handled
    end
    return FALSE //not handled

static function button_press_orig(button,event,menu) //eredeti

// button : ezt nyomták meg (nem kell)
// event  : esemény, bármilyen típusú lehet
// menu   : ezt a menüt kell felrakni

local button_id, timestamp
    
    if( gdk.event.get_type(event)==GDK_BUTTON_PRESS )
        button_id:=gdk.event_button.get_button(event)
        timestamp:=gdk.event.get_time(event)
        gtk.menu.popup(menu,NIL,NIL,NIL,NIL,button_id,timestamp) //hűha
        return TRUE // handled
    end
    return FALSE //not handled

*******************************************************************************
static function menuitem_response(data)
    ? data

static function blkresponse(buf)
    return {||menuitem_response(buf)}

*******************************************************************************
