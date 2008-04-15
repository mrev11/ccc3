
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

local window

    set date format "yyyy-mm-dd"

    gtk.init()
    
    window:=gladeloadgui("project3.glade")
    window:signal_connect("destroy",{||gtk.main_quit()})

    cb_button_orig_clicked(window)

    window:lookup("button_orig"):signal_connect("clicked",{|w|cb_button_orig_clicked(w)})
    window:lookup("button_cancel"):signal_connect("clicked",{||window:destroy})
    window:lookup("button_ok"):signal_connect("clicked",{|w|cb_button_ok_clicked(w)})

    window:lookup("entry1"):signal_connect("key-release-event",{|w|cb_entry1_key_release_event(w)})

    window:show_all()
    gtk.main()
    ?

    return NIL


**************************************************************************** 
static function cb_entry1_key_release_event(w)
    ? w:get_text

**************************************************************************** 
static function cb_button_orig_clicked(w)
    w:lookup("entry1"):set_text("A")
    w:lookup("entry2"):set_text("BB")
    w:lookup("entry3"):set_text("CCC")
    w:lookup("entry4"):set_text("DDDD")

**************************************************************************** 
static function cb_button_ok_clicked(w)
    ? w:lookup("entry1"):get_text
    ? w:lookup("entry2"):get_text
    ? w:lookup("entry3"):get_text
    ? w:lookup("entry4"):get_text
    w:lookup("window1"):destroy

**************************************************************************** 

