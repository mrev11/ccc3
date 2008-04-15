
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
#define COL_LABEL   1
#define COL_MACRO   2
#define COL_ACCEL   3
#define COL_PIXBUF  4

******************************************************************************
function main()
local window
    gtk.init()
    window:=make_window()
    gtk.widget.show_all(window)
    gtk.main()

******************************************************************************
function make_window()

local window,hbox,sw,align,frame
local vbox,lab_type,icon_image,lab_label,lab_macro,lab_id
local model,treeview

    window:=gtk.window.new()
    gtk.window.set_title(window,"Stock Demo")
    gtk.window.set_default_size(window, 280, 250)
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,8)
    
    hbox:=gtk.hbox.new()
    gtk.container.add(window,hbox)

    sw:=gtk.scrolled_window.new()
    gtk.scrolled_window.set_shadow_type(sw,GTK_SHADOW_ETCHED_IN)
    gtk.scrolled_window.set_policy(sw,GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC)
    gtk.box.pack_start(hbox,sw,FALSE)

    align:=gtk.alignment.new(1/2,1/2,0,0)
    gtk.box.pack_start(hbox,align)
    
    frame:=gtk.frame.new("Selected Item")
    gtk.container.add(align,frame)

    vbox:=gtk.vbox.new(FALSE,8)
    gtk.container.set_border_width(vbox,4)
    gtk.container.add(frame,vbox)
    
    lab_type:=gtk.label.new();  gtk.box.pack_start(vbox,lab_type)
    icon_image:=gtk.image.new_from_pixbuf();  gtk.box.pack_start(vbox,icon_image)
    lab_label:=gtk.label.new();  gtk.box.pack_start(vbox,lab_label)
    lab_macro:=gtk.label.new();  gtk.box.pack_start(vbox,lab_macro)
    lab_id:=gtk.label.new();  gtk.box.pack_start(vbox,lab_id)

    model:=create_model(window)
    treeview:=gtk.tree_view.new_with_model(model)
    gtk.tree_view.set_rules_hint(treeview,TRUE)  //ettől lesz sávos
    gtk.tree_view.set_search_column(treeview,1)
    gtk.gobject.signal_connect(gtk.tree_view.get_selection(treeview),"changed",;
        {||cb_changed(treeview,lab_type,icon_image,lab_label,lab_macro,lab_id)})
    gtk.container.add(sw,treeview)
    
    gtk.tree_view.append_column(treeview,column_icon())
    gtk.tree_view.append_column(treeview,column_label())
    gtk.tree_view.append_column(treeview,column_accel())
    gtk.tree_view.append_column(treeview,column_id())
    return window

******************************************************************************
static function create_model(window)

local stock_list:=gtk.stock.list_ids()
local item:=gtk.stock_item.new(),n
local id,label,macro,accel,pixbuf
local key,modif
local data:={}
    asort(stock_list)
    for n:=1 to len(stock_list)
        id:=stock_list[n]
        if( gtk.stock.lookup(id,item) )
            label:=gtk.stock_item.get_label(item)
            key:=gtk.stock_item.get_keyval(item)
            modif:=gtk.stock_item.get_modifier(item)
            accel:=gtk.accelerator.name(key,modif)
        else
            label:=""
            accel:=""
        end
        macro:=upper(strtran(id,"gtk-","GTK_STOCK_"))
        //így lehet szert tenni az ikon pixbuf-jára:
        pixbuf  :=gtk.widget.render_icon(window,id,GTK_ICON_SIZE_MENU)
        aadd(data,{id,label,macro,accel,pixbuf})
    next
    gtk.stock_item.free(item)
    return gtk.list_store.new_array_data(data)

******************************************************************************
static function column_icon()
local column:=gtk.tree_view_column.new()
local renderer1:=gtk.cell_renderer_pixbuf.new()
local renderer2:=gtk.cell_renderer_text.new()
    gtk.tree_view_column.set_title(column,"Macro")
    gtk.tree_view_column.pack_start(column,renderer1,TRUE) //expand
    gtk.tree_view_column.pack_start(column,renderer2,TRUE) //expand
    gtk.cell_layout.set_cell_data_func(column,renderer1,{|c,r,m,i|data_icon(c,r,m,i)})
    gtk.cell_layout.set_cell_data_func(column,renderer2,{|c,r,m,i|data_macro(c,r,m,i)})
    return column

static function data_icon(column,renderer,model,iter)
local pixbuf:=gtk.tree_model.get_value(model,iter,COL_PIXBUF)
    gtk.gobject.set_property(renderer,"pixbuf",pixbuf)

static function data_macro(column,renderer,model,iter)
local macro:=gtk.tree_model.get_value(model,iter,COL_MACRO)
    gtk.gobject.set_property(renderer,"text",macro)

******************************************************************************
static function column_id()
local column:=gtk.tree_view_column.new()
local renderer:=gtk.cell_renderer_text.new()
    gtk.tree_view_column.set_title(column,"ID")
    gtk.tree_view_column.pack_start(column,renderer,TRUE) //expand
    gtk.cell_layout.set_cell_data_func(column,renderer,{|c,r,m,i|data_id(c,r,m,i)})
    return column

static function data_id(column,renderer,model,iter)
local id:=gtk.tree_model.get_value(model,iter,COL_ID)
    gtk.gobject.set_property(renderer,"text",id)

******************************************************************************
static function column_label()
local column:=gtk.tree_view_column.new()
local renderer:=gtk.cell_renderer_text.new()
    gtk.tree_view_column.set_title(column,"Label")
    gtk.tree_view_column.pack_start(column,renderer,TRUE) //expand
    gtk.cell_layout.set_cell_data_func(column,renderer,{|c,r,m,i|data_label(c,r,m,i)})
    return column

static function data_label(column,renderer,model,iter)
local label:=gtk.tree_model.get_value(model,iter,COL_LABEL)
    gtk.gobject.set_property(renderer,"text",label)

******************************************************************************
static function column_accel()
local column:=gtk.tree_view_column.new()
local renderer:=gtk.cell_renderer_text.new()
    gtk.tree_view_column.set_title(column,"Accel")
    gtk.tree_view_column.pack_start(column,renderer,TRUE) //expand
    gtk.cell_layout.set_cell_data_func(column,renderer,{|c,r,m,i|data_accel(c,r,m,i)})
    return column

static function data_accel(column,renderer,model,iter)
local accel:=gtk.tree_model.get_value(model,iter,COL_ACCEL)
    gtk.gobject.set_property(renderer,"text",accel)

******************************************************************************
static function cb_changed(treeview,typ,img,lab,mac,id)
local selection:=gtk.tree_view.get_selection(treeview)
local row:=gtk.tree_selection.get_selected_data(selection)
    if( row!=NIL )
        gtk.label.set_text(typ,if(empty(row[COL_LABEL+1]),"Icon only","Icon and item"))
        gtk.label.set_text_with_mnemonic(lab,row[COL_LABEL+1]+row[COL_ACCEL+1])
        gtk.label.set_text(mac,row[COL_MACRO+1])
        gtk.label.set_text(id,row[COL_ID+1])
        gtk.image.set_from_stock(img,row[COL_ID+1],6)
    else
        gtk.label.set_text(typ,"")
        gtk.label.set_text(lab,"")
        gtk.label.set_text(mac,"")
        gtk.label.set_text(id,"")
        gtk.image.set_from_image(img,NIL)
    end
    ? "selected:", row

******************************************************************************
