
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

******************************************************************************
function main()
local window

    //gdb info
    set alternate on
    set alternate to pid
    ?? getpid()
    set alternate to exe
    ?? exename()
    set alternate to
    set alternate off

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
    gtk.window.set_title(window,"GtkTreeStore Minimal Demo")
    gtk.window.set_default_size(window, 280, 250)
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,8)

    sw:=gtk.scrolled_window.new()
    gtk.scrolled_window.set_shadow_type(sw,GTK_SHADOW_ETCHED_IN)
    gtk.scrolled_window.set_policy(sw,GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC)
    gtk.container.add(window,sw)

    model:=create_model()
    
    treeview:=gtk.tree_view.new_with_model(model)
    gtk.tree_view.set_rules_hint(treeview,TRUE)  //ettől lesz sávos
    //gtk.tree_view.set_search_column(treeview,0)
    gtk.container.add(sw,treeview)
    gtk.gobject.signal_connect(gtk.tree_view.get_selection(treeview),"changed",{||cb_changed(treeview)})

    gtk.tree_view.append_column(treeview,column_proba())
    
    return window


******************************************************************************
static function create_model()

local model:=gtk.tree_store.new("S")
local iter1:=gtk.tree_iter.new()
local iter2:=gtk.tree_iter.new()
local iter3:=gtk.tree_iter.new()

    gtk.tree_store.append(model,iter1,NIL)
    gtk.tree_store.set(model,iter1,{"AAAA"})

    gtk.tree_store.append(model,iter2,iter1)
    gtk.tree_store.set(model,iter2,{"AAAA-1"})
    gtk.tree_store.append(model,iter2,iter1)
    gtk.tree_store.set(model,iter2,{"AAAA-2"})

    gtk.tree_store.append(model,iter3,iter2)
    gtk.tree_store.set(model,iter3,{"AAAA-2-1"})
    gtk.tree_store.append(model,iter3,iter2)
    gtk.tree_store.set(model,iter3,{"AAAA-2-2"})

    gtk.tree_store.append(model,iter1,NIL)
    gtk.tree_store.set(model,iter1,{"BBBB"})

    gtk.tree_store.append(model,iter2,iter1)
    gtk.tree_store.set(model,iter2,{"BBBB-1"})
    gtk.tree_store.append(model,iter2,iter1)
    gtk.tree_store.set(model,iter2,{"BBBB-2"})

    gtk.tree_iter.free(iter1)
    gtk.tree_iter.free(iter2)
    gtk.tree_iter.free(iter3)
    return model

******************************************************************************
static function column_proba()
local column:=gtk.tree_view_column.new()
local renderer:=gtk.cell_renderer_text.new()
    //gtk.tree_view_column.set_title(column,"No selection")
    gtk.tree_view_column.pack_start(column,renderer,TRUE) //expand
    gtk.cell_layout.set_cell_data_func(column,renderer,{|c,r,m,i|data(c,r,m,i)})
    return column

static function data(column,renderer,model,iter)
local txt:=gtk.tree_model.get(model,iter)[1]
    gtk.gobject.set_property(renderer,"text",txt)

******************************************************************************
static function cb_changed(treeview)
local selection:=gtk.tree_view.get_selection(treeview)
local row:=gtk.tree_selection.get_selected_data(selection)
local col:=gtk.tree_view.get_column(treeview,0)
    if( row!=NIL )
        gtk.tree_view_column.set_title(col,row[1])
    else
        gtk.tree_view_column.set_title(col,"No selection")
    end
    ? "selected:", row

******************************************************************************
