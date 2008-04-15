
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
    window:show_all(window)
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

    window:=gtkwindowNew()
    window:set_title("GtkListStore Minimal Demo")
    window:set_default_size(280, 250)
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(8)

    sw:=gtkscrolledwindowNew()
    sw:set_shadow_type(GTK_SHADOW_ETCHED_IN)
    sw:set_policy(GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC)
    window:add(sw)

    model:=gtkliststoreNew_array_index(data)
    treeview:=gtktreeviewNew_with_model(model)
    treeview:set_rules_hint(TRUE)  //ettől lesz sávos
    treeview:set_search_column(0)
    sw:add(treeview)
    
    treeview:append_column(column_proba(model))
    treeview:append_column(column_szerencse())
    treeview:append_column(column_float())
    
    dump(model)

    return window

******************************************************************************
static function column_proba(model)
local column:=gtktreeviewcolumnNew()
local renderer1:=gtkcellrenderertoggleNew()
local renderer2:=gtkcellrenderertextNew()
    column:set_title("Proba")
    column:pack_start(renderer1,.t.) //expand
    column:pack_start(renderer2,.t.) //expand
    column:set_cell_data_func(renderer1,{|c,r,m,i|data11(c,r,model,i)})
    column:set_cell_data_func(renderer2,{|c,r,m,i|data12(c,r,model,i)})
    renderer1:signal_connect("toggled",{|r,p|cb_toggle(r,p)})
    return column

//Probléma, hogy ahol a set_cell_data_func-ot meghívjuk,
//ott általában nem ismert a model. A modelt a GTK szolgáltatja,
//az viszont nem tudja, hogy milyen CCC objectbe kell becsomagolni.
//Ezért a modelt nem becsomagolva, hanem pointerként kapjuk.
//Az iter-nek eleve nincs definiálva csomagoló osztálya.
//
//Ha a modelt is becsomagolva akarjuk megkapni, akkor láthatóvá
//tesszük a változót set_cell_data_func meghívásának helyén,
//és beírjuk a változót a kódblokkba, pl.:
//
//column:set_cell_data_func(renderer2,{|c,r,m,i|data12(c,r,model,i)})

static function data11(column,renderer,model,iter)
local idx:=model:get_value(iter,0)
    renderer:set_property("active",data[idx][1])

static function data12(column,renderer,model,iter)
local idx:=model:get_value(iter,0)
    renderer:set_property("text",data[idx][2])

//Figyelem: 
//Itt egy  gtk.tree_iter.free(iter) azonnali SIGSEGV-t okozna.
//Csak azt az iter-t szabad felszabadítani, amit mi csinaltunk.


static function cb_toggle(renderer,pathstr)
local idx:=1+val(pathstr) //0-val kezdődik!
    data[idx][1]:=!data[idx][1]

******************************************************************************
static function column_szerencse()
local column:=gtktreeviewcolumnNew()
local renderer:=gtkcellrenderertextNew()
    column:set_title("Szerencse")
    column:pack_start(renderer,.f.) //no-expand
    column:set_cell_data_func(renderer,{|c,r,m,i|data2(c,renderer,m,i)})
    return column

static function data2(column,renderer,model,iter)
local idx:=gtk.tree_model.get(model,iter)[1] //datarow[1]
    renderer:set_property("text",data[idx][3])

******************************************************************************
static function column_float() //ez tisztább
local column:=gtktreeviewcolumnNew()
local renderer:=gtkcellrenderertextNew()
    column:set_title("Float")
    column:pack_start(renderer,.f.) //no-expand
    column:set_cell_data_func(renderer,{|c,r,m,i|data3(c,renderer,m,i)})
    return column

static function column_float_(model) //ugyanaz
local renderer:=gtkcellrenderertextNew()
local column:=gtktreeviewcolumnNew_with_attributes("Float",renderer)
    column:set_cell_data_func(renderer,{|c,r,m,i|data3(c,renderer,m,i)})
    return column

static function data3(column,renderer,model,iter)
local idx:=gtk.tree_model.get(model,iter)[1] //datarow[1]
    renderer:set_property("text",transform(data[idx][4],"999,999.99"))


******************************************************************************
static function dump(model)
local iter:=gtk.tree_iter.new()
local positioned:=model:get_iter_first(iter)
    while( positioned  )
        ? model:get(iter)
        positioned:=model:iter_next(iter)
    end
    // clean up
    gtk.tree_iter.free(iter)

******************************************************************************
