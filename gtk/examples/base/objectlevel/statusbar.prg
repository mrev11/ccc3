
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


*******************************************************************************
static function push_item(status_bar,context_id )
static count:=1
    status_bar:push(context_id,"Item"+str(count++))

*******************************************************************************
static function pop_item(status_bar, context_id )
    status_bar:pop(context_id)

*******************************************************************************
function main()

local window, vbox, button
local status_bar
local context_id

    gtk.init()

    window:=gtkwindowNew()
    window:set_size_request(200,100)
    window:set_title("GTK Statusbar Example")
    window:signal_connect("delete_event",{||gtk.main_quit(),.f.})
 
    vbox:=gtkvboxNew(FALSE,1)
    window:add(vbox)
          
    status_bar:=gtkstatusbarNew()      
    vbox:pack_start(status_bar,TRUE,TRUE,0)

    context_id:=status_bar:get_context_id("Statusbar example")

    button:=gtkbuttonNew("push item")
    button:signal_connect("clicked",{||push_item(status_bar,context_id)})
    vbox:pack_start(button,TRUE,TRUE,2)

    button:=gtkbuttonNew("pop last item")
    button:signal_connect("clicked",{||pop_item(status_bar,context_id)})
    vbox:pack_start(button,TRUE,TRUE,2)

    window:show_all

    gtk.main()
    ?


*******************************************************************************
