
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

#define FALSE .f.
#define TRUE  .t.

static status_bar

*******************************************************************************
static function push_item(data )
static count:=1
    gtk.statusbar.push (status_bar, data, "Item"+str(count++))


*******************************************************************************
static function pop_item( data )
  gtk.statusbar.pop (status_bar,data)


*******************************************************************************
function main()

local window, vbox, button
local context_id

    gtk.init()

    window := gtk.window.new()
    gtk.widget.set_size_request (window, 200, 100)
    gtk.window.set_title (window, "GTK Statusbar Example")
    gtk.gobject.signal_connect (window, "delete_event",{||gtk.main_quit(),.f.})
 
    vbox := gtk.vbox.new (FALSE, 1)
    gtk.container.add (window, vbox)
    gtk.widget.show (vbox)
          
    status_bar := gtk.statusbar.new ()      
    gtk.box.pack_start (vbox, status_bar, TRUE, TRUE, 0)
    gtk.widget.show (status_bar)

    context_id:=gtk.statusbar.get_context_id(status_bar,"Statusbar example")

    button:=gtk.button.new_with_label("push item")
    gtk.gobject.signal_connect(button,"clicked",{||push_item(context_id)})
    gtk.box.pack_start (vbox, button, TRUE, TRUE, 2)
    gtk.widget.show (button)              

    button := gtk.button.new_with_label ("pop last item")
    gtk.gobject.signal_connect (button, "clicked",{||pop_item(context_id)})
    gtk.box.pack_start (vbox, button, TRUE, TRUE, 2)
    gtk.widget.show (button)

    gtk.widget.show (window)

    gtk.main ()
    ?


*******************************************************************************
