
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

******************************************************************************
function main()
local window
    gtk.init()
    window:=make_window()
    window:show_all()
    gtk.main()
    ?

******************************************************************************
function make_window()

local window
local button

    window:=gtkwindowNew()
    window:set_title("FileButton")
    window:set_default_size(180,50)
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(8)
    
    button:=gtkfilechooserbuttonNew("File Chooser Button Demo",GTK_FILE_CHOOSER_ACTION_OPEN)
    button:set_local_only:=.f.
    //button:set_select_multiple:=.t. //not supported

    ? button:get_select_multiple
    ? button:get_current_folder
    ? button:get_local_only

    window:add(button)
    button:signal_connect("selection-changed",{|w|cb_selection_changed(w)})
    button:signal_connect("current-folder-changed",{|w|cb_current_folder_changed(w)})
   
    return window


******************************************************************************
static function cb_selection_changed(w)
    ? "selection-changed:", w:get_filename

******************************************************************************
static function cb_current_folder_changed(w)
    ? "current-folder-changed:", w:get_current_folder
    

******************************************************************************
