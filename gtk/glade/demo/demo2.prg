
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

#include "directry.ch"

****************************************************************************
function main()

local window, treeview, model

    set date format "yyyy-mm-dd"

    gtk.init()
    
    window:=gladeloadgui("project2.glade")
    window:signal_connect("destroy",{||gtk.main_quit()})

    window:lookup("new1"):signal_connect("activate",{|w|cb_new1_activate(w)})
    window:lookup("open1"):signal_connect("activate",{|w|cb_open1_activate(w)})
    window:lookup("save1"):signal_connect("activate",{|w|cb_save1_activate(w)})
    window:lookup("save_as1"):signal_connect("activate",{|w|cb_save_as1_activate(w)})
    window:lookup("quit1"):signal_connect("activate",{||cb_quit1_activate(window)})
    window:lookup("copy1"):signal_connect("activate",{||cb_copy1_activate(window)})
    window:lookup("paste1"):signal_connect("activate",{||cb_paste1_activate(window)})
    window:lookup("proba1"):signal_connect("activate",{||cb_proba1_activate(window)})
    window:lookup("forron1"):signal_connect("activate",{||cb_forron1_activate(window)})

    treeview:=window:lookup("treeview1")
    treeview:set_model(create_model())

    treeview:append_column:=create_column("File",F_NAME)
    treeview:append_column:=create_column("Size",F_SIZE,"999,999,999")
    treeview:append_column:=create_column("Date",F_DATE)
    treeview:append_column:=create_column("Time",F_TIME)
    treeview:append_column:=create_column("Attr",F_ATTR)

    treeview:get_selection():signal_connect("changed",{||cb_changed(treeview)})

    window:show_all()
    gtk.main()
    ?

    return NIL


**************************************************************************** 
static function create_model()
local d:=directory(fullmask(),"DH"),n
    for n:=1 to len(d)
         d[n][F_DATE]:=dtoc(d[n][F_DATE])
    next
    return gtkliststoreNew_array_data(d)

**************************************************************************** 
static function cb_changed(treeview)
local textview:=treeview:lookup("textview1")
local datarow:=treeview:get_selection:get_selected_data()
    ? datarow
    if( datarow!=NIL )
        textview:get_buffer:set_text(memoread(datarow[F_NAME]))
    end

**************************************************************************** 
static function cb_new1_activate(w)
    ? "cb_new1_activate"

**************************************************************************** 
static function cb_open1_activate(w)
    ? "cb_open1_activate"

**************************************************************************** 
static function cb_save1_activate(w)
    ? "cb_save1_activate"

**************************************************************************** 
static function cb_save_as1_activate(w)
    ? "cb_save_as1_activate"

**************************************************************************** 
static function cb_quit1_activate(w)
    ? "cb_quit1_activate"
    w:destroy

**************************************************************************** 
static function cb_copy1_activate(w)
    ? "cb_copy1_activate"

**************************************************************************** 
static function cb_paste1_activate(w)
local view:=w:lookup("textview1")
local buffer:=view:get_buffer
    gtk.text_buffer.insert_at_cursor(buffer,"<INS>")
    ? "cb_paste1_activate"

**************************************************************************** 
static function cb_proba1_activate(w)
    ? "cb_proba1_activate"

**************************************************************************** 
static function cb_forron1_activate(w)
    ? "cb_forron1_activate"

****************************************************************************
