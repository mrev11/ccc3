
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

//Ez nem akarja

#include "gtk.ch"

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
    window:show_all()
    gtk.main()

******************************************************************************
function make_window()

local window
local combo
local cell
local renderer

    window:=gtkwindowNew()
    window:set_title("GtkComboBox")
    window:set_default_size(280,50)
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(8)
    
    combo:=gtkcomboboxNew_with_model(create_model())
   
    //? combo:get_child:type_name //GtkCellView
    cell:=combo:get_child:cast(gtkcellviewClass())
    renderer:=gtkcellrenderertextNew()
    cell:pack_start(renderer,.t.)
    cell:set_cell_data_func(renderer,{|c,r,m,i|data(c,r,m,i)})

    combo:signal_connect("changed",{|w|cb_changed(w)})
    combo:set_active(3) //-1: deselect
    
    window:add(combo)
   
    return window

******************************************************************************
static function data(c,renderer,model,iter)
local txt:=gtk.tree_model.get(model,iter)[1]
    ? "data:",txt //,c,renderer,model,iter
    renderer:set_property("text",txt)

******************************************************************************
static function cb_changed(combo)
    ? "selected:", combo:get_active, combo:get_active_text

******************************************************************************
static function create_model() //list

local model:=gtkliststoreNew("S")
local iter:=gtk.tree_iter.new()

    model:append(iter)
    model:set(iter,{"AAAA"})
    model:append(iter)
    model:set(iter,{"BBBBBBBBB"})
    model:append(iter)
    model:set(iter,{"CCCCCCCCCCCCCCCC"})
    model:append(iter)
    model:set(iter,{"DDDDDDD"})

    gtk.tree_iter.free(iter)
    return model

******************************************************************************
static function create_model1()  //fa

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
