
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
function main(fspec)

local window
local scrolled_window,button
local view,buffer,vbox,action_area
local initialtext:=if(fspec==NIL,"",memoread(fspec))
local textlen
    
    gtk.init()
    
    window:=gtk.dialog.new ()
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.window.set_title (window,"GtkTextView example")
    gtk.container.set_border_width(window,0)
    gtk.widget.set_size_request(window,300,300)
    
    scrolled_window:=gtk.scrolled_window.new ()
    gtk.container.set_border_width (scrolled_window, 10)
    gtk.scrolled_window.set_policy(scrolled_window,1,1)

    // The dialog window is created with a vbox packed into it.
    vbox:=gtk.dialog.get_vbox(window)
    gtk.box.pack_start(vbox, scrolled_window,.t.,.t.,0)

    view:=gtk.text_view.new()
    buffer:=gtk.text_view.get_buffer(view)
    //gtk.text_buffer.set_text(buffer,initialtext,textlen:=-1) 
    gtk.text_buffer.set_text(buffer,initialtext) 
    
    // Pack the table into the scrolled window.
    gtk.scrolled_window.add_with_viewport (scrolled_window,view)
    
    action_area:=gtk.dialog.get_action_area(window) //box

    button := gtk.button.new_with_label ("Save")
    gtk.gobject.signal_connect (button, "clicked",{||cb_save(buffer)})
    gtk.box.pack_start(action_area, button, .t., .t., 0)

    button := gtk.button.new_with_label ("Close")
    gtk.gobject.signal_connect (button, "clicked",{||gtk.widget.destroy(window)})
    gtk.box.pack_start(action_area, button, .t., .t., 0)


    gtk.widget.show_all (window)
    gtk.main()
    ?

******************************************************************************
static function cb_save(buffer,fspec)
local text:=gtk.text_buffer.get_text(buffer)
    memowrit (if(empty(fspec),"save",fspec),text)


******************************************************************************
