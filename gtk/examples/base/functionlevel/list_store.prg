
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

#define COLUMN_FIXED        0
#define COLUMN_NUMBER       1 
#define COLUMN_SEVERITY     2
#define COLUMN_DESCRIPTION  3
#define NUM_COLUMNS         4

#define idx_fixed           1
#define idx_number          2
#define idx_severity        3
#define idx_description     4

static data:={;
{ FALSE, 60482, "Normal",     "scrollable notebooks and hidden tabs" },;
{ FALSE, 60620, "Critical",   "gdk_window_clear_area (gdkwindow-win32.c) is not thread-safe" },;
{ FALSE, 50214, "Major",      "Xft support does not clean up correctly" },;
{ TRUE,  52877, "Major",      "GtkFileSelection needs a refresh method. " },;
{ FALSE, 56070, "Normal",     "Can't click button after setting in sensitive" },;
{ TRUE,  56355, "Normal",     "GtkLabel - Not all changes propagate correctly" },;
{ FALSE, 50055, "Normal",     "Rework width/height computations for TreeView" },;
{ FALSE, 58278, "Normal",     "gtk.dialog_set_response_sensitive () doesn't work" },;
{ FALSE, 55767, "Normal",     "Getters for all setters" },;
{ FALSE, 56925, "Normal",     "Gtkcalender size" },;
{ FALSE, 56221, "Normal",     "Selectable label needs right-click copy menu" },;
{ TRUE,  50939, "Normal",     "Add shift clicking to GtkTextView" },;
{ FALSE, 6112,  "Enhancement","netscape-like collapsable toolbars" },;
{ FALSE, 1,     "Normal",     "First bug :=)" };
}


******************************************************************************
function main()
local window
    gtk.init()
    window:=do_list_store()
    gtk.widget.show_all(window)
    gtk.main()


******************************************************************************
function do_list_store()

local window    //GtkWidget
local vbox      //GtkWidget
local label     //GtkWidget
local sw        //GtkWidget
local model     //GtkTreeModel
local treeview  //GtkWidget

    window:=gtk.window.new()
    gtk.window.set_title(window,"GtkListStore demo")
    gtk.window.set_default_size(window, 280, 250)
    gtk.gobject.signal_connect(window,"destroy",{||dump(model),gtk.main_quit()})
    gtk.container.set_border_width(window,8)

    vbox:=gtk.vbox.new(FALSE, 8)
    gtk.container.add(window,vbox)

    label:=gtk.label.new("This is the bug list (note: not based on real data, it would be nice to have a nice ODBC interface to bugzilla or so, though).")
    gtk.box.pack_start(vbox,label,FALSE,FALSE,0)

    sw:=gtk.scrolled_window.new()
    gtk.scrolled_window.set_shadow_type(sw,GTK_SHADOW_ETCHED_IN)
    gtk.scrolled_window.set_policy(sw,GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC)
    gtk.box.pack_start(vbox,sw,TRUE,TRUE,0)

    model:=create_model()
    treeview:=gtk.tree_view.new_with_model(model)
    gtk.gobject.unref(model)
    gtk.tree_view.set_rules_hint(treeview,TRUE)
    gtk.tree_view.set_search_column(treeview,COLUMN_DESCRIPTION)
    add_columns(treeview)
    gtk.container.add(sw,treeview)

    gtk.widget.show_all (window)

    return window

******************************************************************************
static function create_model() //GtkTreeModel

local i:=0
local store //GtkListStore
local iter  //GtkTreeIter

    store:=gtk.list_store.new("BISS") //Boolean,Integer,String,String

    // add data to the list store 
    iter:=gtk.tree_iter.new()
    for i:=1 to len(data)
        gtk.list_store.append(store,iter)
        //gtk.list_store.set(store,iter,data[i])
        gtk.list_store.set(store,iter,{{0,data[i][1]},{1,data[i][2]},{2,data[i][3]},{3,data[i][4]}})

        //Ha egy string oszlopot nem töltünk ki, 
        //akkor a lista működik (az oszlop üresnek látszik)
        //de a program kilépéskor SIGSEGV keletkezik,
        //gondolom azért, mert a GTK fel akarja szabadítani
        //a lista adattagját, de a semmibe nyúl.
        //Ez a GTK hibája, nem lehet rajta másképp segíteni,
        //mint hogy mindig ki kell tölteni az oszlopokat.        
    end
    gtk.tree_iter.free(iter)

    return store


******************************************************************************
static function add_columns(treeview)

local renderer //GtkCellRenderer
local column  //GtkTreeViewColumn
local model:=gtk.tree_view.get_model(treeview)

    // column for fixed toggles
    renderer:=gtk.cell_renderer_toggle.new()
    gtk.gobject.signal_connect(renderer,"toggled",{|r,p|fixed_toggled(r,p,model)})
    column:=gtk.tree_view_column.new_with_attributes("Fixed?",renderer)
    gtk.tree_view_column.add_attribute(column,renderer,"active",COLUMN_FIXED)
    // set this column to a fixed sizing (of 50 pixels)
    gtk.tree_view_column.set_sizing(column,GTK_TREE_VIEW_COLUMN_FIXED)
    gtk.tree_view_column.set_fixed_width(column,50)
    gtk.tree_view.append_column(treeview,column)

    // column for bug numbers
    renderer:=gtk.cell_renderer_text.new()
    column:=gtk.tree_view_column.new_with_attributes("Bug number",renderer)
    gtk.tree_view_column.add_attribute(column,renderer,"text",COLUMN_NUMBER)
    gtk.tree_view_column.set_sort_column_id(column,COLUMN_NUMBER)
    gtk.tree_view.append_column(treeview,column)

    // column for severities
    renderer:=gtk.cell_renderer_text.new()
    column:=gtk.tree_view_column.new_with_attributes("Severity",renderer)
    gtk.tree_view_column.add_attribute(column,renderer,"text",COLUMN_SEVERITY)
    gtk.tree_view_column.set_sort_column_id(column,COLUMN_SEVERITY)
    gtk.tree_view.append_column(treeview,column)

    // column for description
    renderer:=gtk.cell_renderer_text.new()
    column:=gtk.tree_view_column.new_with_attributes("Description",renderer)
    gtk.tree_view_column.add_attribute(column,renderer,"text",COLUMN_DESCRIPTION)
    gtk.tree_view_column.set_sort_column_id(column,COLUMN_DESCRIPTION)
    gtk.tree_view.append_column (treeview,column)


******************************************************************************
static function  fixed_toggled(cell,path_str,model)

local iter:=gtk.tree_iter.new()
local path:=gtk.tree_path.new_from_string(path_str)
local row

    if( gtk.tree_model.get_iter(model,iter,path) )
        ? row:=gtk.tree_model.get(model,iter)
        gtk.list_store.set(model,iter,!row[1])
    end

    // clean up
    gtk.tree_path.free(path)
    gtk.tree_iter.free(iter)
    
    gc()


******************************************************************************
static function dump(model)

local iter:=gtk.tree_iter.new()
local path:=gtk.tree_path.new_first()
local row, n

    ? "-----------------"

    while( gtk.tree_model.get_iter(model,iter,path) )
        ? row:=gtk.tree_model.get(model,iter)
        gtk.tree_path.next(path)
    end

    ? "-----------------"
    ?

    // clean up
    gtk.tree_path.free(path)
    gtk.tree_iter.free(iter)



******************************************************************************

