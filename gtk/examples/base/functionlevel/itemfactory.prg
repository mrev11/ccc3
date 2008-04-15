
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

static xtext:="Öt szép szűzlány"
static ytext:="Őrült írót nyúz"
static ztext:="ЙЦÉКЕНÚÍÓЗ"

static menu_items:={;
{ "/_File",         NIL,          NIL,                  "<Branch>" },;
{ "/File/_New",     "<control>N", {||print_new()},      "<Item>" },;
{ "/File/_Open",    "<control>O", {||print_open()},     "<Item>" },;
{ "/File/_Save",    "<control>S", {||print_save()},     "<Item>" },;
{ "/File/Save _As", NIL,          {||print_save_as()},  "<Item>" },;
{ "/File/sep1",     NIL,          NIL,                  "<Separator>" },;
{ "/File/"+xtext,   "<control>X", {||print_text(xtext)},"<Item>" },;
{ "/File/"+ytext,   "<control>Y", {||print_text(ytext)},"<Item>" },;
{ "/File/"+ztext,   "<control>Z", {||print_text(ztext)},"<Item>" },;
{ "/File/Quit",     "<control>Q", {||gtk.main_quit()},  "<Item>" },;
{ "/_Options",      NIL,          NIL,                  "<Branch>" },;
{ "/Options/tear",  NIL,          NIL,                  "<Tearoff>" },;
{ "/Options/Check", NIL,          {|w|print_toggle(w)}, "<CheckItem>" },;
{ "/Options/sep1",  NIL,          NIL,                  "<Separator>" },;
{ "/Options/Rad1",  NIL,          {|w|print_sel(w,1)},  "<RadioItem>" },;
{ "/Options/Rad2",  NIL,          {|w|print_sel(w,2)},  "/Options/Rad1" },;
{ "/Options/Rad3",  NIL,          {|w|print_sel(w,3)},  "/Options/Rad1" },;
{ "/Options/sep1",  NIL,          NIL,                  "<Separator>" },;
{ "/Options/Rad4",  NIL,          {|w|print_sel(w,4)},  "<RadioItem>" },;
{ "/Options/Rad5",  NIL,          {|w|print_sel(w,5)},  "/Options/Rad4" },;
{ "/Options/Rad6",  NIL,          {|w|print_sel(w,6)},  "/Options/Rad4" },;
{ "/Options/Rad7",  NIL,          {|w|print_sel(w,7)},  "/Options/Rad4" },;
{ "/_Help",         NIL,          NIL,                  "<LastBranch>" },;
{ "/_Help/About",   NIL,          NIL,                  "<Item>" }}

  /* possible type values:
   * NIL                -> "<Item>"
   * ""                 -> "<Item>"
   * "<Title>"          -> create a title item
   * "<Item>"           -> create a simple item
   * "<ImageItem>"      -> create an item holding an image
   * "<StockItem>"      -> create an item holding a stock image
   * "<CheckItem>"      -> create a check item
   * "<ToggleItem>"     -> create a toggle item
   * "<RadioItem>"      -> create a radio item
   * <path>             -> path of a radio item to link against
   * "<Separator>"      -> create a separator
   * "<Tearoff>"        -> create a tearoff separator
   * "<Branch>"         -> create an item to hold sub items
   * "<LastBranch>"     -> create a right justified item to hold sub items
   */


*******************************************************************************
static function print_new()
    ? "New"

static function print_open()
    ? "Open"

static function print_save()
    ? "Save"

static function print_save_as()
    ? "Save as"

static function print_text(x)
    ? x

*******************************************************************************
static function print_toggle(menu_item)
    ? "Check button state", gtk.check_menu_item.get_active(menu_item)

*******************************************************************************
static function print_sel(menu_item,action)
    if( gtk.check_menu_item.get_active(menu_item) )
         ? "Radio button selected", action
    end

*******************************************************************************
function  get_menubar_menu(window)

local item_factory
local accel_group
//local wdg

    // Make an accelerator group (shortcut keys)
    accel_group := gtk.accel_group.new ()

    // Make an ItemFactory (that makes a menubar)
    item_factory := gtk.item_factory.new (GTK_TYPE_MENU_BAR, "<main>", accel_group)

    // This function generates the menu items. Pass the item factory,
    // the number of items in the array, the array itself, and any
    // callback data for the the menu items. 
    gtk.item_factory.create_items(item_factory, menu_items)

    // Attach the new accelerator group to the window. 
    gtk.window.add_accel_group (window, accel_group)

    //A kézi kódblokk regisztrálás is működne:
    //wdg:=gtk.item_factory.get_widget(item_factory, "/File/New")
    //gtk.gobject.signal_connect(wdg,"activate",{||print_new()})

    // Return the actual menu bar created by the item factory.
    return gtk.item_factory.get_widget (item_factory, "<main>")


******************************************************************************   
static function get_popup_menu()

// Same as with get_menubar_menu() but just return 
// a button with a signal to call a popup menu.
// Don't bother with the accelerators.

local item_factory
local button, menu
  
   item_factory := gtk.item_factory.new (GTK_TYPE_MENU, "<main>", NIL)
   gtk.item_factory.create_items (item_factory, menu_items)
   menu := gtk.item_factory.get_widget(item_factory, "<main>")
  
   // Make a button to activate the popup menu
   button := gtk.button.new_with_label("Popup")
   gtk.gobject.signal_connect(button, "event", {|w,e|cb_popup(w,e,menu)})
   return button

static function cb_popup(widget,event,menu)

local button_id
local timestamp

    if( gdk.event.get_type(event) != GDK_BUTTON_PRESS )
        return FALSE
    end

    button_id:=gdk.event_button.get_button(event)
    timestamp:=gdk.event.get_time(event)
    gtk.menu.popup(menu, NIL, NIL, NIL, NIL, button_id, timestamp)

    return TRUE
    
    //ez nagyon béna!

******************************************************************************   
function get_option_menu()

// Same as with get_menubar_menu(), 
// not bothering with the accelerators.

local item_factory
local option_menu
  
    item_factory := gtk.item_factory.new (GTK_TYPE_OPTION_MENU, "<main>")
    gtk.item_factory.create_items (item_factory, menu_items)
    option_menu := gtk.item_factory.get_widget(item_factory, "<main>")
    return option_menu

    //Figyelem!
    //Ez felesleges warningokat ír ki az stdout-ra,
    //ami nem a CCCGTK interfész hibája, mert az eredeti
    //C mintaprogram is ugyanzokat írja.

******************************************************************************   
function main()

local window, main_vbox
local menubar, option_menu, popup_button
 
    gtk.init()
 
    window := gtk.window.new (GTK_WINDOW_TOPLEVEL)
    gtk.gobject.signal_connect (window, "destroy",{||gtk.main_quit()})
    gtk.window.set_title (window, "Item Factory")
    gtk.widget.set_size_request (window, 300, 200)
 
    // Make a vbox to put the three menus in 
    main_vbox := gtk.vbox.new (FALSE, 1)
    gtk.container.set_border_width (main_vbox, 1)
    gtk.container.add (window, main_vbox)
 
    // Get the three types of menu 
    // Note: all three menus are separately created, 
    // so they are not the same menu 
    menubar := get_menubar_menu (window)
    popup_button := get_popup_menu()
    option_menu := get_option_menu()
  
    // Pack it all together
    gtk.box.pack_start (main_vbox, menubar, FALSE, TRUE, 0)
    gtk.box.pack_end (main_vbox, popup_button, FALSE, TRUE, 0)
    gtk.box.pack_end (main_vbox, option_menu, FALSE, TRUE, 0)

    gtk.widget.show_all (window)
    gtk.main ()
    ?

******************************************************************************   
  