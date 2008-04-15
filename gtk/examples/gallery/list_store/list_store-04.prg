
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
"alma",;
"korte",;
"szilva",;
"barack",;
"szolo",;
"narancs",;
"fuge",;
"malna",;
"eper";
}

#define CHANGED cb_changed2

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
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,8)

    sw:=gtk.scrolled_window.new()
    gtk.scrolled_window.set_shadow_type(sw,GTK_SHADOW_ETCHED_IN)
    gtk.scrolled_window.set_policy(sw,GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC)
    gtk.container.add(window,sw)

    model:=gtk.list_store.new_array_index(data)
    treeview:=gtk.tree_view.new_with_model(model)
    gtk.tree_view.set_rules_hint(treeview,TRUE)  //ettől lesz sávos
    //gtk.tree_view.set_search_column(treeview,0)
    gtk.tree_selection.set_mode(gtk.tree_view.get_selection(treeview),GTK_SELECTION_MULTIPLE)
    gtk.gobject.signal_connect(gtk.tree_view.get_selection(treeview),"changed",{||CHANGED(treeview)})
    gtk.container.add(sw,treeview)
    
    gtk.tree_view.append_column(treeview,column_gyumolcs(model))

    return window

******************************************************************************
static function column_gyumolcs()
local column:=gtk.tree_view_column.new()
local renderer:=gtk.cell_renderer_text.new()
    gtk.tree_view_column.set_title(column,"Gyumolcs")
    gtk.tree_view_column.pack_start(column,renderer,TRUE) //expand
    gtk.cell_layout.set_cell_data_func(column,renderer,{|c,r,m,i|data(c,r,m,i)})
    return column

static function data(column,renderer,model,iter)
local idx:=gtk.tree_model.get(model,iter)[1] //datarow[1]
    gtk.gobject.set_property(renderer,"text",data[idx])


******************************************************************************
static function cb_changed1(treeview)
local selection:=gtk.tree_view.get_selection(treeview)
local rows:=gtk.tree_selection.get_selected_rows_data(selection)
    ? "changed1:", rows

//egyszerűsített/összevont logika:
//gtk.tree_selection.get_selected_rows_data(selection)
//egyből a kiválasztott sorok adatait adja

******************************************************************************
static function cb_changed2(treeview)

local model //:=gtk.tree_view.get_model(treeview)
local selection:=gtk.tree_view.get_selection(treeview)
local path:=gtk.tree_selection.get_selected_rows(selection,@model)
local iter:=gtk.tree_iter.new()
local rows:={},n

    for n:=1 to len(path)
        gtk.tree_model.get_iter(model,iter,path[n])
        gtk.tree_path.free(path[n])
        aadd(rows,gtk.tree_model.get(model,iter))
    next
    gtk.tree_iter.free(iter)

    ? "changed2:", rows

******************************************************************************
