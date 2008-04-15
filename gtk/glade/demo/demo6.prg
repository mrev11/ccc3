
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

//Minimális képnéző.

function main()
local window, fcb

    gtk.init()
    window:=gladeloadgui("project6.glade")
    window:signal_connect("destroy",{||gtk.main_quit()})


    fcb:=window:lookup("filechooserbutton1")
    fcb:signal_connect("selection-changed",{|w|cb_selection_changed(w)})
    fcb:signal_connect("current-folder-changed",{|w|cb_current_folder_changed(w)})


    window:show_all()
    gtk.main()
    ?
   
    return window


******************************************************************************
static function cb_selection_changed(w)
local img:=w:lookup("image1")
    ? "selection-changed:", w:get_filename
    img:set_from_file(w:get_filename)

******************************************************************************
static function cb_current_folder_changed(w)
    ? "current-folder-changed:", w:get_current_folder

******************************************************************************

