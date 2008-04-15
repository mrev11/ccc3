
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
    gtk.widget.show_all(window)
    gtk.main()

******************************************************************************
function make_window()

local window    //GtkWidget
local combo     //GtkWidget

    window:=gtk.window.new()
    gtk.window.set_title(window,"GtkComboBox")
    gtk.window.set_default_size(window, 280, 50)
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,8)
    
    combo:=gtk.combo_box.new_text()
    gtk.combo_box.append_text(combo,"First choice")
    gtk.combo_box.append_text(combo,"Second choice")
    gtk.combo_box.append_text(combo,"Third choice")
    gtk.combo_box.append_text(combo,"Fourth choice")

    gtk.combo_box.set_active(combo,0) //-1: deselect
    
    gtk.container.add(window,combo)
    
    return window


******************************************************************************
