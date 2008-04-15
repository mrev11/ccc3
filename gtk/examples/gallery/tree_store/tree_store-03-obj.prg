
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

static stock_ids:=asort(gtk.stock.list_ids())

******************************************************************************
function main()
local window

    gtk.init()
    window:=make_window()
    window:show_all()
    gtk.main()

******************************************************************************
function make_window()

local window    //GtkWidget
local sw        //GtkWidget
local model     //GtkTreeModel
local treeview  //GtkWidget

    window:=gtkwindowNew()
    window:set_title("GtkTreeStore Pixbuf")
    window:set_default_size( 280, 250)
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(8)

    sw:=gtkscrolledwindowNew()
    sw:set_shadow_type(GTK_SHADOW_ETCHED_IN)
    sw:set_policy(GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC)
    window:add(sw)

    model:=create_model()
    
    treeview:=gtktreeviewNew_with_model(model)
    treeview:set_rules_hint(TRUE)  //ettől lesz sávos
    //treeview:set_search_column(0)
    sw:add(treeview)
    treeview:get_selection:signal_connect("changed",{||cb_changed(treeview)})

    treeview:append_column(column1())
    treeview:append_column(column2())
    
    return window


******************************************************************************
static function create_model()

local model:=gtktreestoreNew("SI")
local iter1:=gtk.tree_iter.new()
local iter2:=gtk.tree_iter.new()
local iter3:=gtk.tree_iter.new()

    model:append(iter1,NIL)
    model:set(iter1,{"AAAA",1})

    model:append(iter2,iter1)
    model:set(iter2,{"AAAA-1",2})
    model:append(iter2,iter1)
    model:set(iter2,{"AAAA-2",3})

    model:append(iter3,iter2)
    model:set(iter3,{"AAAA-2-1",4})
    model:append(iter3,iter2)
    model:set(iter3,{"AAAA-2-2",5})

    model:append(iter1,NIL)
    model:set(iter1,{"BBBB",6})

    model:append(iter2,iter1)
    model:set(iter2,{"BBBB-1",7})
    model:append(iter2,iter1)
    model:set(iter2,{"BBBB-2",8})

    gtk.tree_iter.free(iter1)
    gtk.tree_iter.free(iter2)
    gtk.tree_iter.free(iter3)
    return model

******************************************************************************
static function column1()
local column:=gtktreeviewcolumnNew()
local renderer1:=gtkcellrendererpixbufNew()
local renderer2:=gtkcellrenderertextNew()
    column:pack_start(renderer1,TRUE) //expand
    column:pack_start(renderer2,TRUE) //expand
    column:set_cell_data_func(renderer1,{|c,r,m,i|data11(c,r,m,i)})
    column:set_cell_data_func(renderer2,{|c,r,m,i|data12(c,r,m,i)})
    return column

static function data11(column,renderer,model,iter)
local num:=gtk.tree_model.get(model,iter)[2]
    renderer:set_property("stock-id",stock_ids[num])
    renderer:set_property("stock-size",GTK_ICON_SIZE_MENU)

static function data12(column,renderer,model,iter)
local txt:=gtk.tree_model.get(model,iter)[1]
    renderer:set_property("text",txt)

******************************************************************************
static function column2()
local column:=gtktreeviewcolumnNew()
local renderer:=gtkcellrenderertextNew()
    column:set_title("Aux data")
    column:pack_start(renderer,TRUE) //expand
    column:set_cell_data_func(renderer,{|c,r,m,i|data2(c,r,m,i)})
    return column

static function data2(column,renderer,model,iter)
local num:=gtk.tree_model.get(model,iter)[2]
    renderer:set_property("text",str(num))

******************************************************************************
static function cb_changed(treeview)
local row:=treeview:get_selection:get_selected_data()
local col:=treeview:get_column(0)
    if( row!=NIL )
        col:set_title(row[1])
    else
        col:set_title("No selection")
    end
    ? "selected:", row

******************************************************************************
