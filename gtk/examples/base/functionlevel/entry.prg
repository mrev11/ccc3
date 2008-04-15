
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
static function enter_callback(entry)
local entry_text
    entry_text:=gtk.entry.get_text(entry)
    ? "Entry contents:", entry_text

*******************************************************************************
static function entry_toggle_editable(checkbutton,entry)
local flag:=gtk.toggle_button.get_active(checkbutton)
    gtk.editable.set_editable(entry,flag)

*******************************************************************************
static function entry_toggle_visibility(checkbutton,entry)
local flag:=gtk.toggle_button.get_active(checkbutton)
    gtk.entry.set_visibility(entry,flag)

*******************************************************************************
function main()
local window, vbox, hbox
local entry, button, check, pos

    gtk.init()

    window:=gtk.window.new()
    gtk.widget.set_size_request(window, 200, 100)
    gtk.window.set_title(window, "GTK Entry")
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})

    vbox:=gtk.vbox.new (FALSE, 0)
    gtk.container.add(window, vbox)

    entry:=gtk.entry.new()
    gtk.entry.set_max_length(entry,50)
    gtk.gobject.signal_connect(entry,"activate",{||enter_callback(entry)})
    gtk.entry.set_text(entry, "hello")
    pos:=gtk.entry.get_text_length(entry)
    gtk.editable.insert_text(entry," world",@pos)
    gtk.editable.insert_text(entry," proba",@pos)
    gtk.editable.insert_text(entry," szerencse",@pos)
    ? pos
    gtk.editable.select_region(entry,0,gtk.entry.get_text_length(entry))

    gtk.box.pack_start(vbox, entry, TRUE, TRUE, 0)

    hbox:=gtk.hbox.new(FALSE, 0)
    gtk.container.add(vbox, hbox)
                                  
    check:=gtk.check_button.new_with_label("Editable")
    gtk.box.pack_start(hbox, check, TRUE, TRUE, 0)
    gtk.gobject.signal_connect(check,"toggled",{|w|entry_toggle_editable(w,entry)})
    gtk.toggle_button.set_active(check,TRUE)
    
    check:=gtk.check_button.new_with_label("Visible")
    gtk.box.pack_start(hbox, check, TRUE, TRUE, 0)
    gtk.gobject.signal_connect(check,"toggled",{|w|entry_toggle_visibility(w,entry)})
    gtk.toggle_button.set_active(check, TRUE)
                                   
    button:=gtk.button.new_from_stock("gtk-close")
    gtk.gobject.signal_connect(button,"clicked",{||gtk.widget.destroy(window)})
    gtk.box.pack_start(vbox,button,TRUE,TRUE, 0)
    gtk.widget.set_flags(button, GTK_CAN_DEFAULT)
    gtk.widget.grab_default (button)
    
    gtk.widget.show_all(window)

    gtk.main()
    ?

*******************************************************************************


