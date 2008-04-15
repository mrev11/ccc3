
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

******************************************************************************
function main()

local window,item_factory,table,accel_group
local toolbar,tooltips,button,sw,contents,buffer,statusbar

local menu_items:={;
{'/_File', NIL, NIL, '<Branch>' },;
{'/File/_New', '<control>N', {|i|cb_menu(i,window)}, '<StockItem>', GTK_STOCK_NEW},;
{'/File/_Open', '<control>O', {|i|cb_menu(i,window)}, '<StockItem>', GTK_STOCK_OPEN},;
{'/File/_Save', '<control>S', {|i|cb_menu(i,window)}, '<StockItem>', GTK_STOCK_SAVE},;
{'/File/Save _As...',, {|i|cb_menu(i,window)}, '<StockItem>', GTK_STOCK_SAVE},;
{'/File/sep1',,,'<Separator>'},;
{'/File/_Quit', '<control>Q', {|i|cb_menu(i,window)}, '<StockItem>', GTK_STOCK_QUIT},;
{'/_Preferences',,,'<Branch>'},;
{'/_Preferences/_Color',,,'<Branch>'},;
{'/_Preferences/Color/_Red',,{|i|cb_menu(i,window)},'<RadioItem>'},;
{'/_Preferences/Color/_Green',,{|i|cb_menu(i,window)},'/Preferences/Color/Red'},;
{'/_Preferences/Color/_Blue',,{|i|cb_menu(i,window)},'/Preferences/Color/Red'},;
{'/_Preferences/_Shape',,,'<Branch>'},;
{'/_Preferences/Shape/_Square',,{|i|cb_menu(i,window)},'<RadioItem>'},;
{'/_Preferences/Shape/_Rectangle',,{|i|cb_menu(i,window)},'/Preferences/Shape/Square'},;
{'/_Preferences/Shape/_Oval',,{|i|cb_menu(i,window)},'/Preferences/Shape/Rectangle'},;
{'/_Help',,,'<Branch>'},; //<LastBranch>
{'/Help/_About',,{|i|cb_menu(i,window)},''};
}
    //gdb info
    set alternate on
    set alternate to pid
    ?? getpid()
    set alternate to exe
    ?? exename()
    set alternate to
    set alternate off

    gtk.init()
    
    window:=gtkwindowNew()
    window:set_title('Application Window')
    window:set_default_size(400,300)
    window:signal_connect('destroy',{||gtk.main_quit()})

    table:=gtktableNew(1,4,.f.)
    window:add(table)

    //1-Menu
    accel_group:=gtkaccelgroupNew()
    item_factory:=gtkitemfactoryNew(GTK_TYPE_MENU_BAR,'<main>',accel_group)
    item_factory:create_items(menu_items)
    window:add_accel_group(accel_group)
    table:attach(item_factory:get_widget('<main>'),0,1,0,1,GTK_EXPAND+GTK_FILL,0)

    //2-Toolbar
    toolbar:=gtkToolbarNew()
    tooltips:=gtktooltipsNew()
    toolbar:insert(button:=gtktoolbuttonNew_from_stock("gtk-open"))
        button:set_tooltip(tooltips,"This is a demo button with an 'open' icon")
        button:signal_connect("clicked",{||cb_toolbar(window,"Open")})
    toolbar:insert(button:=gtktoolbuttonNew_from_stock("gtk-close"))
        button:set_tooltip(tooltips,"This is a demo button with an 'close' icon")
        button:signal_connect("clicked",{||cb_toolbar(window,"Close")})
    toolbar:insert(gtkseparatortoolitemNew())
    toolbar:insert(button:=gtktoolbuttonNew_from_stock("gtk-help"))
        button:set_tooltip(tooltips,"This is a demo button with an 'help' icon")
        button:signal_connect("clicked",{||cb_toolbar(window,"Help")})
    //toolbar:insert(button:=gtkfontbuttonNew())
    //ezt nem lehet ide betenni, mint a Swingben
    table:attach(toolbar,0,1,1,2,GTK_EXPAND+GTK_FILL,0)

    //3-Contents
    sw:=gtkScrolledWindowNew()
    sw:set_policy(GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC)
    sw:set_shadow_type(GTK_SHADOW_IN)
    contents:=gtkTextViewNew()
    sw:add(contents)
    buffer:=contents:get_buffer()
    buffer:signal_connect('changed',{||cb_changed(buffer,statusbar)})
    buffer:signal_connect('mark-set',{||cb_mark_set(buffer,statusbar)})
    table:attach(sw,0,1,2,3,GTK_EXPAND+GTK_FILL,GTK_EXPAND+GTK_FILL)

    //4-Statusbar
    statusbar:=gtkStatusbarNew()
    update_statusbar(buffer,statusbar)
    table:attach(statusbar,0,1,3,4,,0)

    window:show_all()

    gtk.main()

******************************************************************************
static function cb_menu(i,window)
local dlg,x
    ? i, gtk.gobject.type_name(i)
    if( gtk.gobject.type_name(i)=="GtkRadioMenuItem";
        .and. !gtk.check_menu_item.get_active(i)  )
        ? "Kikapcs:", gtk.item_factory.path_from_widget(i)
        return NIL
    end
    x:='Ezt választottad: '
    x+=gtk.item_factory.path_from_widget(i)
    dlg:=gtkmessagedialogNew(   window,;
                                GTK_DIALOG_DESTROY_WITH_PARENT,;
                                GTK_MESSAGE_INFO,;
                                GTK_BUTTONS_CLOSE,;
                                x)
    dlg:signal_connect('response',{||dlg:destroy})
    dlg:show()

******************************************************************************
static function cb_toolbar(window,x)
local dlg
    dlg:=gtkmessagedialogNew(   window,;
                                GTK_DIALOG_DESTROY_WITH_PARENT,;
                                GTK_MESSAGE_INFO,;
                                GTK_BUTTONS_CLOSE,;
                                "Ezt választottad: "+x)
    dlg:signal_connect('response',{||dlg:destroy})
    dlg:show()

******************************************************************************
static function cb_mark_set(buffer,statusbar)
    //? "cb_mark_set"
    update_statusbar(buffer,statusbar)

******************************************************************************
static function cb_changed(buffer,statusbar)
    //? "cb_changed"
    update_statusbar(buffer,statusbar)

******************************************************************************
static function update_statusbar(buffer,statusbar)

local row,col,x
local mark:=buffer:get_insert()
local count:=buffer:get_char_count()
local iter:=gtk.text_iter.new()

    buffer:get_iter_at_mark(iter,mark)
    row:=gtk.text_iter.get_line(iter)
    col:=gtk.text_iter.get_line_offset(iter)

    x:='Cursor at row %ROW column %COL - %COUNT chars in document'
    x:=strtran(x,"%ROW",alltrim(str(row)))
    x:=strtran(x,"%COL",alltrim(str(col)))
    x:=strtran(x,"%COUNT",alltrim(str(count)))
    statusbar:pop(0)
    statusbar:push(0,x)

    //clean up
    gtk.text_iter.free(iter)
    
    gc()

******************************************************************************
