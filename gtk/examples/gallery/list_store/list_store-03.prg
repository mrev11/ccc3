
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

static data:={;
{"proba-1","szerencse-1"},;
{"proba-2","szerencse-2"},;
{"proba-3","szerencse-3"},;
{"xx-proba-4","szerencse-4"},;
{"proba-5","szerencse-5"},;
{"proba-6","szerencse-6"},;
{"proba-7","szerencse-7"},;
{"proba-8","szerencse-8"},;
{"VEGRE","VALAHARA"};
}

******************************************************************************
function main()
local window
    gtk.init()
    window:=make_window()
    gtk.widget.show_all(window)
    gtk.main()

******************************************************************************
function make_window()

local window    //GtkWidget
local sw        //GtkWidget
local model     //GtkTreeModel
local treeview  //GtkWidget

    window:=gtk.window.new()
    gtk.window.set_title(window,"GtkListStore Minimal Demo")
    gtk.window.set_default_size(window, 280, 250)
    gtk.gobject.signal_connect(window,"destroy",{||dump(treeview),gtk.main_quit()})
    gtk.container.set_border_width(window,8)

    sw:=gtk.scrolled_window.new()
    gtk.scrolled_window.set_shadow_type(sw,GTK_SHADOW_ETCHED_IN)
    gtk.scrolled_window.set_policy(sw,GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC)
    gtk.container.add(window,sw)

    model:=gtk.list_store.new_array_data(data) //lemásolja data-t
    treeview:=gtk.tree_view.new_with_model(model)
    gtk.gobject.unref(model) //már a treeview refeli
    asize(data,0) //már a treeview tárolja
    
    gtk.tree_view.set_rules_hint(treeview,TRUE)  //ettől lesz sávos
    gtk.tree_view.set_search_column(treeview,0)
    gtk.container.add(sw,treeview)
    
    gtk.tree_view.append_column(treeview,column_proba())
    gtk.tree_view.append_column(treeview,column_szerencse())

    return window

******************************************************************************
static function column_proba()
local column:=gtk.tree_view_column.new()
local renderer:=gtk.cell_renderer_text.new()
    gtk.tree_view_column.set_title(column,"Proba")
    gtk.tree_view_column.pack_start(column,renderer,.t.)
    gtk.cell_layout.set_cell_data_func(column,renderer,{|c,r,m,i|data1(c,r,m,i)})
    return column

static function data1(column,renderer,model,iter)
local data:=gtk.tree_model.get(model,iter)
    gtk.gobject.set_property(renderer,"text",data[1])

******************************************************************************
static function column_szerencse()
local column:=gtk.tree_view_column.new()
local renderer:=gtk.cell_renderer_text.new()
    gtk.tree_view_column.set_title(column,"Szerencse")
    gtk.tree_view_column.pack_start(column,renderer,.t.)
    gtk.cell_layout.set_cell_data_func(column,renderer,{|c,r,m,i|data2(c,r,m,i)})
    return column

static function data2(column,renderer,model,iter)
local data:=gtk.tree_model.get(model,iter)
    gtk.gobject.set_property(renderer,"text",data[2])


******************************************************************************
static function dump(treeview)

local iter:=gtk.tree_iter.new()
local path:=gtk.tree_path.new_first()
local model:=gtk.tree_view.get_model(treeview)
local data0,data1

    ? "-----------------"

    while( gtk.tree_model.get_iter(model,iter,path) )

        ? gtk.tree_model.get(model,iter)
        //gtk.tree_model.get_value(model,iter,0,@data0)
        //gtk.tree_model.get_value(model,iter,1,@data1)
        //? data0,data1

        gtk.tree_path.next(path)
    end

    ? "-----------------"
    ?

    // clean up
    gtk.tree_path.free(path)
    gtk.tree_iter.free(iter)


******************************************************************************
