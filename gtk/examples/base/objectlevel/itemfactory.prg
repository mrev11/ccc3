
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

static menu_items:={;
{ "/_File",         NIL,          NIL,                  "<Branch>" },;
{ "/File/_New",     "<control>N", {||print_new()},      "<Item>" },;
{ "/File/_Open",    "<control>O", {||print_open()},     "<Item>" },;
{ "/File/_Save",    "<control>S", {||print_save()},     "<Item>" },;
{ "/File/Save _As", NIL,          {||print_save_as()},  "<Item>" },;
{ "/File/sep1",     NIL,          NIL,                  "<Separator>" },;
{ "/File/Quit",     "<control>Q", {||gtk.main_quit()},  "<Item>" },;
{ "/_Opciók",      NIL,          NIL,                  "<Branch>" },;
{ "/Opciók/tear",  NIL,          NIL,                  "<Tearoff>" },;
{ "/Opciók/Check", NIL,          {|w|print_toggle(w)}, "<CheckItem>" },;
{ "/Opciók/sep1",  NIL,          NIL,                  "<Separator>" },;
{ "/Opciók/Rad1",  NIL,          {|w|print_sel(w,1)},  "<RadioItem>" },;
{ "/Opciók/Rad2",  NIL,          {|w|print_sel(w,2)},  "/Opciók/Rad1" },;
{ "/Opciók/Rad3",  NIL,          {|w|print_sel(w,3)},  "/Opciók/Rad1" },;
{ "/Opciók/sep1",  NIL,          NIL,                  "<Separator>" },;
{ "/Opciók/Rad4",  NIL,          {|w|print_sel(w,4)},  "<RadioItem>" },;
{ "/Opciók/Rad5",  NIL,          {|w|print_sel(w,5)},  "/Opciók/Rad4" },;
{ "/Opciók/Rad6",  NIL,          {|w|print_sel(w,6)},  "/Opciók/Rad4" },;
{ "/Opciók/Rad7",  NIL,          {|w|print_sel(w,7)},  "/Opciók/Rad4" },;
{ "/_Help",        NIL,          NIL,                  "<LastBranch>" },;
{ "/_Help/About",  NIL,          NIL,                  "<Item>" }}

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

    accel_group:=gtkaccelgroupNew()
    item_factory:=gtkitemfactoryNew(GTK_TYPE_MENU_BAR,"<main>",accel_group)
    item_factory:create_items(menu_items)
    window:add_accel_group(accel_group)
    return item_factory:get_widget("<main>")

    //A kézi kódblokk regisztrálás is működne:
    //wdg:=gtk.item_factory.get_widget(item_factory, "/File/New")
    //gtk.signal_connect(wdg,"activate",{||print_new()})


******************************************************************************   
static function get_popup_menu()

// Same as with get_menubar_menu() but just return 
// a button with a signal to call a popup menu.
// Don't bother with the accelerators.

local item_factory, button, menu
  
   item_factory:=gtkitemfactoryNew(GTK_TYPE_MENU,"<main>",NIL)
   item_factory:create_items(menu_items)
   menu:=item_factory:get_widget("<main>")

   ? g_type_check_instance_is_a(menu:gobject,gtk.widget.get_type())
   ? g_type_check_instance_is_a(menu:gobject,gtk.menu.get_type())
   ? g_type_check_instance_is_a(menu:gobject,gtk.window.get_type())

   //objektum konverzió,
   //másképp menu osztálya gtkwidget marad,
   //annak pedig nincs popup metódusa
   //? menu:classname //gtkwidget
   menu:=gobjectNew(gtkmenuClass(),menu:gobject)
   //? menu:classname //gtkmenu
  
   // Make a button to activate the popup menu
   button:=gtkbuttonNew("Popup")
   button:signal_connect("event",{|w,e|cb_popup(w,e,menu)})
   return button


static function cb_popup(button,event,menu)
    if( gdk.event.get_type(event) != GDK_BUTTON_PRESS )
        return FALSE
    end
    //gtk.menu.popup(menu:gobject)
    menu:popup
    return TRUE

******************************************************************************   
function get_option_menu()

// Same as with get_menubar_menu(), 
// not bothering with the accelerators.

local item_factory, option_menu
  
    item_factory:=gtkitemfactoryNew(GTK_TYPE_OPTION_MENU,"<main>")
    item_factory:create_items(menu_items)
    option_menu:=item_factory:get_widget("<main>")
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
 
    window:=gtkwindowNew()
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_title("Item Factory")
    window:set_size_request(300,200)
 
    // Make a vbox to put the three menus in 
    main_vbox:=gtkvboxNew(FALSE,1)
    main_vbox:set_border_width(1)
    window:add(main_vbox)
 
    // Get the three types of menu 
    // Note: all three menus are separately created, 
    // so they are not the same menu 

    menubar := get_menubar_menu (window)
    popup_button := get_popup_menu()
    //option_menu := get_option_menu()
  
    // Pack it all together

    main_vbox:pack_start(menubar,FALSE,TRUE,0)
    main_vbox:pack_end(popup_button,FALSE,TRUE,0)
    //main_vbox:pack_end(option_menu,FALSE,TRUE,0)

    window:show_all
    gtk.main ()
    ?

******************************************************************************   
  