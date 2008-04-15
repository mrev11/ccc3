
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

local window 
local menu, menu_bar, root_menu, menu_items
local vbox, button, buf, i

    gtk.init ()

    window := gtk.window.new()
    gtk.widget.set_size_request (window, 200, 100)
    gtk.window.set_title (window, "GTK Menu Test")
    gtk.gobject.signal_connect (window, "delete_event", {||gtk.main_quit(),FALSE})

    /* Init the menu-widget, and remember -- never
     * gtk.show_widget() the menu widget!! 
     * This is the menu that holds the menu items, the one that
     * will pop up when you click on the "Root Menu" in the app */
    menu:=gtk.menu.new()
    ? gtk.menu.get_type()

    /* Next we make a loop that makes three menu-entries for "test-menu".
     * Notice the call to gtk.menu_shell.append.  Here we are adding a list
     * of menu items to our menu.  Normally, we'd also catch the "clicked"
     * signal on each of the menu items and setup a callback for it,
     * but it's omitted here to save space. */

    for i:=1 to 3
        buf:="Test-undermenu"+str(i)
        menu_items := gtk.menu_item.new_with_label (buf)
        gtk.menu_shell.append(menu, menu_items) //add it to the menu
        gtk.gobject.signal_connect(menu_items,"activate",blkresponse(buf))
        //gtk.widget.show (menu_items)
    next 

    /* This is the root menu, and will be the label
     * displayed on the menu bar.  There won't be a signal handler attached,
     * as it only pops up the rest of the menu when pressed. */

    root_menu:=gtk.menu_item.new_with_label("Root Menu")
    //gtk.widget.show (root_menu)

    /* Now we specify that we want our newly created "menu" to be the menu
     * for the "root menu" */
    gtk.menu_item.set_submenu (root_menu, menu)

    /* A vbox to put a menu and a button in: */
    vbox := gtk.vbox.new (FALSE, 0)
    gtk.container.add (window, vbox)
    //gtk.widget.show (vbox)

    /* Create a menu-bar to hold the menus and add it to our main window */
    menu_bar := gtk.menu_bar.new ()
    gtk.box.pack_start (vbox, menu_bar, FALSE, FALSE, 2)
    //gtk.widget.show (menu_bar)

    /* Create a button to which to attach menu as a popup */
    button := gtk.button.new_with_label ("press me")
    gtk.gobject.signal_connect(button, "event", {|w,e|button_press(w,e,menu)})
    gtk.box.pack_end (vbox, button, TRUE, TRUE, 2)
    //gtk.widget.show (button)

    /* And finally we append the menu-item to the menu-bar -- this is the
     * "root" menu-item I have been raving about :=) */
    gtk.menu_shell.append (menu_bar, root_menu)

    /* always display the window as the last step so it all splashes on
     * the screen at once. */
    //gtk.widget.show (window)

    gtk.widget.show_all (window)
    
    // A tutorialban nincs benne show_all:
    // a végén egyszerre mindent láthatóvá tesz.

    gtk.main ()
    ?

*******************************************************************************
static function button_press(button,event,menu)

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
