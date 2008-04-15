
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
{.t.    ,"proba-1"      ,"szerencse-1"  ,1.11},;
{.f.    ,"proba-2"      ,"szerencse-2"  ,2.22},;
{.f.    ,"proba-3"      ,"szerencse-3"  ,3.33},;
{.f.    ,"xx-proba-4"   ,"szerencse-4"  ,4.44},;
{.t.    ,"proba-5"      ,"szerencse-5"  ,5.55},;
{.f.    ,"proba-6"      ,"szerencse-6"  ,6.66},;
{.t.    ,"proba-7"      ,"szerencse-7"  ,7.77},;
{.t.    ,"proba-8"      ,"szerencse-8"  ,888.8},;
{.f.    ,"VEGRE"        ,"VALAHARA"     ,9.99};
}

******************************************************************************
function main()
local window,n
    gtk.init()
    window:=make_window()
    gtk.widget.show_all(window)
    gtk.main()
    
    for n:=1 to len(data)
        ? data[n]
    next

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
    gtk.tree_view.set_search_column(treeview,0)
    gtk.container.add(sw,treeview)
    
    gtk.tree_view.append_column(treeview,column_proba())
    gtk.tree_view.append_column(treeview,column_szerencse())
    gtk.tree_view.append_column(treeview,column_float())

    return window

******************************************************************************
static function column_proba()
local column:=gtk.tree_view_column.new()
local renderer1:=gtk.cell_renderer_toggle.new()
local renderer2:=gtk.cell_renderer_text.new()
    gtk.tree_view_column.set_title(column,"Proba")
    gtk.tree_view_column.pack_start(column,renderer1,.t.) //expand
    gtk.tree_view_column.pack_start(column,renderer2,.t.) //expand
    gtk.cell_layout.set_cell_data_func(column,renderer1,{|c,r,m,i|data11(c,r,m,i)})
    gtk.cell_layout.set_cell_data_func(column,renderer2,{|c,r,m,i|data12(c,r,m,i)})
    gtk.gobject.signal_connect(renderer1,"toggled",{|r,p|cb_toggle(r,p)})
    return column

static function data11(column,renderer,model,iter)
local idx:=gtk.tree_model.get(model,iter)[1] //datarow[1]
    gtk.gobject.set_property(renderer,"active",data[idx][1])

static function data12(column,renderer,model,iter)
local idx:=gtk.tree_model.get(model,iter)[1] //datarow[1]
    gtk.gobject.set_property(renderer,"text",data[idx][2])

static function cb_toggle(renderer,pathstr)
local idx:=1+val(pathstr) //0-val kezdődik!
    data[idx][1]:=!data[idx][1]

    //Ez az egész oszlopra szól.
    //if( data[idx][1] )
    //    gtk.gobject.set_property(renderer,"activatable",.f.)
    //end

******************************************************************************
static function column_szerencse()
local column:=gtk.tree_view_column.new()
local renderer:=gtk.cell_renderer_text.new()
    gtk.tree_view_column.set_title(column,"Szerencse")
    gtk.tree_view_column.pack_start(column,renderer,.f.) //no-expand
    gtk.cell_layout.set_cell_data_func(column,renderer,{|c,r,m,i|data2(c,r,m,i)})
    return column

static function data2(column,renderer,model,iter)
local idx:=gtk.tree_model.get(model,iter)[1] //datarow[1]
    gtk.gobject.set_property(renderer,"text",data[idx][3])

******************************************************************************
static function column_float() //ez tisztább
local column:=gtk.tree_view_column.new()
local renderer:=gtk.cell_renderer_text.new()
    gtk.tree_view_column.set_title(column,"Float")
    gtk.tree_view_column.pack_start(column,renderer,.f.) //no-expand
    gtk.cell_layout.set_cell_data_func(column,renderer,{|c,r,m,i|data3(c,r,m,i)})
    return column

static function column_float_() //ugyanaz
local renderer:=gtk.cell_renderer_text.new()
local column:=gtk.tree_view_column.new_with_attributes("Float",renderer)
    gtk.cell_layout.set_cell_data_func(column,renderer,{|c,r,m,i|data3(c,r,m,i)})
    return column

static function data3(column,renderer,model,iter)
local idx:=gtk.tree_model.get(model,iter)[1] //datarow[1]
    gtk.gobject.set_property(renderer,"text",transform(data[idx][4],"999,999.99"))

******************************************************************************
