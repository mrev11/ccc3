
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

*******************************************************************************
function main()

local window, vbox, hbox
local entry, button, check, pos

    gtk.init()

    window:=gtkwindowNew()
    window:set_size_request(200,100)
    window:set_title("GTK Entry Demó")
    window:signal_connect("destroy",{||gtk.main_quit()})

    vbox:=gtkvboxNew(FALSE,0)
    window:add(vbox)

    entry:=gtkentryNew()
    entry:set_max_length(50)
    entry:signal_connect("activate",{||cb_activate(entry)})

    entry:set_text("Öt")
    ? pos:=entry:get_text_length()
    ? pos:=entry:insert_text(" szép",pos)
    ? pos:=entry:insert_text(" szűzlány",pos)
    ? pos:=entry:insert_text(" őrült",pos)
    ? pos:=entry:insert_text(" írót",pos)
    ? pos:=entry:insert_text(" nyúz",pos)

    // Ez nem működik, 
    // mert a metódus argumentumok nem működnek in-out módban.
    // entry:insert_text(" world",@pos); ?pos
    // entry:insert_text(" proba",@pos); ?pos
    // entry:insert_text(" szerencse",@pos); ?pos

    entry:select_region(5,10)
    vbox:pack_start(entry,TRUE,TRUE,0)

    hbox:=gtkhboxNew(FALSE, 0)
    vbox:add(hbox)
                                  
    check:=gtkcheckbuttonNew("Editable")
    hbox:pack_start(check,TRUE,TRUE,0)
    check:signal_connect("toggled",{|w|cb_toggle_editable(w,entry)})
    check:set_active(TRUE)
    
    check:=gtkcheckbuttonNew_with_label("Visible")
    hbox:pack_start(check,TRUE,TRUE,0)
    check:signal_connect("toggled",{|w|cb_toggle_visibility(w,entry)})
    check:set_active(TRUE)
                                   
    button:=gtkbuttonNew_from_stock("gtk-close")
    button:signal_connect("clicked",{||window:destroy})
    vbox:pack_start(button,TRUE,TRUE,0)
    button:grab_default()

    window:show_all()

    gtk.main()
    ?

*******************************************************************************
static function cb_activate(entry)
local text:=entry:get_text
    ? "Entry contents:", text

*******************************************************************************
static function cb_toggle_editable(checkbutton,entry)
local flag:=checkbutton:get_active()
    entry:set_editable(flag)

*******************************************************************************
static function cb_toggle_visibility(checkbutton,entry)
local flag:=checkbutton:get_active()
    entry:set_visibility(flag)

*******************************************************************************


