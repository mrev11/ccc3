
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

#define FALSE .f.
#define TRUE  .t.

#define COL_ID      0
#define COL_MACRO   1
#define COL_LABEL   2
#define COL_ACCEL   3
#define COL_PIXBUF  4

******************************************************************************
function main()
local window
    gtk.init()
    window:=make_window()
    window:show_all()
    gtk.main()

******************************************************************************
function make_window()

local window,hbox,sw,align,frame
local vbox,labtyp,iconimg,lablab,labmac,labid
local model,treeview

    window:=gtkwindowNew()
    window:set_title("Stock Demo")
    window:set_default_size( 280, 250)
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(8)
    
    hbox:=gtkhboxNew(FALSE,8)
    window:add(hbox)

    sw:=gtkscrolledwindowNew()
    sw:set_shadow_type(GTK_SHADOW_ETCHED_IN)
    sw:set_policy(GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC)
    hbox:pack_start(sw,.f.)

    align:=gtkalignmentNew(1/2,1/2,0,0)
    hbox:pack_start(align)
    
    frame:=gtkframeNew("Selected Item")
    align:add(frame)

    vbox:=gtkvboxNew(FALSE,8)
    vbox:set_border_width(4)
    frame:add(vbox)
    
    vbox:pack_start(labtyp:=gtklabelNew())
    vbox:pack_start(iconimg:=gtkimageNew_from_pixbuf()) //üres
    vbox:pack_start(lablab:=gtklabelNew())
    vbox:pack_start(labmac:=gtklabelNew())
    vbox:pack_start(labid:=gtklabelNew())

    model:=create_model(window)
    treeview:=gtktreeviewNew_with_model(model)
    treeview:set_rules_hint(TRUE)  //ettől lesz sávos
    treeview:set_search_column(1)
    treeview:get_selection():signal_connect("changed",;
        {||cb_changed(treeview,labtyp,iconimg,lablab,labmac,labid)})
    sw:add(treeview)
    
    treeview:append_column(column_icon())
    treeview:append_column(column_label())
    treeview:append_column(column_accel())
    treeview:append_column(column_id())
    return window

******************************************************************************
static function create_model(window)

local stock_list:=gtk.stock.list_ids()
local item:=gtk.stock_item.new(),n
local id,macro,label,accel,pixbuf
local key,modif
local data:={}
    asort(stock_list)
    for n:=1 to len(stock_list)
        id:=stock_list[n]
        macro:=upper(strtran(id,"gtk-","GTK_STOCK_"))
        if( gtk.stock.lookup(id,item) )
            label:=gtk.stock_item.get_label(item)
            key:=gtk.stock_item.get_keyval(item)
            modif:=gtk.stock_item.get_modifier(item)
            accel:=gtk.accelerator.name(key,modif)
        else
            label:=""
            accel:=""
        end
        //így lehet szert tenni az ikon pixbuf-jára:
        pixbuf:=window:render_icon(id,GTK_ICON_SIZE_MENU)
        aadd(data,{id,macro,label,accel,pixbuf})
    next
    gtk.stock_item.free(item)
    return gtkliststoreNew_array_data(data)

******************************************************************************
static function column_icon()
local column:=gtktreeviewcolumnNew()
local renderer1:=gtkcellrendererpixbufNew()
local renderer2:=gtkcellrenderertextNew()
    column:set_title("Macro")
    column:pack_start(renderer1,FALSE) //noexpand
    column:pack_start(renderer2,FALSE) //noexpand
    column:set_cell_data_func(renderer1,{|c,r,m,i|data_icon(c,r,m,i)})
    column:set_cell_data_func(renderer2,{|c,r,m,i|data_macro(c,r,m,i)})
    return column

static function data_icon(column,renderer,model,iter)
local pixbuf:=gtk.tree_model.get_value(model,iter,COL_PIXBUF)
    renderer:set_property("pixbuf",pixbuf)

static function data_macro(column,renderer,model,iter)
local macro:=gtk.tree_model.get_value(model,iter,COL_MACRO)
    renderer:set_property("text",macro)

******************************************************************************
static function column_id()
local column:=gtktreeviewcolumnNew()
local renderer:=gtkcellrenderertextNew()
    column:set_title("ID")
    column:pack_start(renderer,FALSE) //noexpand
    column:set_cell_data_func(renderer,{|c,r,m,i|data_id(c,r,m,i)})
    return column

static function data_id(column,renderer,model,iter)
local id:=gtk.tree_model.get_value(model,iter,COL_ID)
    renderer:set_property("text",id)

******************************************************************************
static function column_label()
local column:=gtktreeviewcolumnNew()
local renderer:=gtkcellrenderertextNew()
    column:set_title("Label")
    column:pack_start(renderer,FALSE) //noexpand
    column:set_cell_data_func(renderer,{|c,r,m,i|data_label(c,r,m,i)})
    return column

static function data_label(column,renderer,model,iter)
local label:=gtk.tree_model.get_value(model,iter,COL_LABEL)
    renderer:set_property("text",label)

******************************************************************************
static function column_accel()
local column:=gtktreeviewcolumnNew()
local renderer:=gtkcellrenderertextNew()
    column:set_title("Accel")
    column:pack_start(renderer,FALSE) //noexpand
    column:set_cell_data_func(renderer,{|c,r,m,i|data_accel(c,r,m,i)})
    return column

static function data_accel(column,renderer,model,iter)
local accel:=gtk.tree_model.get_value(model,iter,COL_ACCEL)
    renderer:set_property("text",accel)

******************************************************************************
static function cb_changed(treeview,typ,img,lab,mac,id)
local row:=treeview:get_selection:get_selected_data()
    if( !empty(row) )
        typ:set_text(if(empty(row[COL_LABEL+1]),"Icon only","Icon and item"))
        lab:set_text_with_mnemonic(row[COL_LABEL+1]+row[COL_ACCEL+1])
        mac:set_text(row[COL_MACRO+1])
        id:set_text(row[COL_ID+1])
        //img:set_from_stock(row[COL_ID+1],GTK_ICON_SIZE_DIALOG)
        img:set_from_stock(row[COL_ID+1],GTK_ICON_SIZE_SMALL_TOOLBAR)
    else
        typ:set_text("")
        lab:set_text("")
        mac:set_text("")
        id:set_text("")
        img:set_from_image()
    end
    ? "selected:", row

******************************************************************************
