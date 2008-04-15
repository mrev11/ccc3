
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
local fontdesc,color
    
    gtk.init()
    
    window:=gtkdialogNew()
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_title("GtkTextView example")
    window:set_border_width(0)
    window:set_size_request(300,300)
    
    scrolled_window:=gtkscrolledwindowNew()
    scrolled_window:set_border_width(10)
    scrolled_window:set_policy(1,1)

    // The dialog window is created with a vbox packed into it.
    vbox:=window:get_vbox()
    vbox:pack_start(scrolled_window,.t.,.t.,0)

    view:=gtktextviewNew()

    fontdesc:=pango.font_description.new_from_string("Courier 24")
    view:modify_font(fontdesc)
    pango.font_description.free(fontdesc)

    //color:=gdk.color.new_from_string("green")
    color:=gdk.color.new_from_string("#007f7f") //RGB
    view:modify_text(GTK_STATE_NORMAL,color)
    gdk.color.free(color)

    buffer:=view:get_buffer
    buffer:set_text(initialtext,-1) //!
    scrolled_window:add_with_viewport(view)

    action_area:=window:get_action_area() //box
    button:=gtkbuttonNew_with_label("Save")
    button:signal_connect("clicked",{||cb_save(buffer)})
    action_area:pack_start(button,.t.,.t.,0)

    button:=gtkbuttonNew_with_label("Close")
    button:signal_connect("clicked",{||window:destroy})
    action_area:pack_start(button,.t.,.t.,0)

    window:show_all()
    gtk.main()
    ?

******************************************************************************
static function cb_save(buffer,fspec)
local text:=buffer:get_text
    memowrit (if(empty(fspec),"save",fspec),text)


******************************************************************************
