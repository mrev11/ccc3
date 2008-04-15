
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

local window,vpaned,list,text,button

    gtk.init()
   
    window:=gtk.window.new()
    gtk.window.set_title(window,"Paned Windows")
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,10)
    gtk.widget.set_size_request(window,450,400)

    vpaned:=gtk.vpaned.new()
    gtk.container.add(window,vpaned)
   
    text:=create_text()
    button:=gtk.button.new_with_label("Insert")
    gtk.gobject.signal_connect(button,"clicked",{||insert(text)})

    gtk.paned.add1(vpaned,button)
    gtk.paned.add2(vpaned,text)

    gtk.widget.show_all(window)
    gtk.main()


******************************************************************************
static function insert(scrolled_window)
local view:=gtk.bin.get_child(scrolled_window)
local buffer:=gtk.text_view.get_buffer(view)
    gtk.text_buffer.insert_at_cursor(buffer,"<INS>")

******************************************************************************
static function create_text()

local txt:=<<TEXT>>0
1 From: pathfinder@nasa.gov
2 To: mom@nasa.gov
3 Subject: Made it!
4yyyyyyyyyyyyyyyyyyy
5 We just got in this morning. The weather has been
6 great - clear but cold, and there are lots of fun sights.
7 Sojourner says hi. See you soon.
8 -Path
<<TEXT>>

local ins:="<<XXX>>"

local view:=gtk.text_view.new()
local buffer:=gtk.text_view.get_buffer(view)
local scrolled_window:=gtk.scrolled_window.new()
local text_iter

    gtk.scrolled_window.set_policy(scrolled_window,1,1)
    gtk.container.add(scrolled_window,view)

#define WITH_TEXT_ITER
#ifdef  WITH_TEXT_ITER
    text_iter:=gtk.text_iter.new() //nincs rá referenciaszámlálás!
    gtk.text_buffer.get_iter_at_offset(buffer,text_iter,0)
    gtk.text_buffer.insert(buffer,text_iter,txt,-1) //length==-1 (whole text)

    //karakterpozícióra pozícionál
    //gtk.text_buffer.get_iter_at_offset(buffer,text_iter,20)

    //sorra pozícionál
    //gtk.text_buffer.get_iter_at_line(buffer,text_iter,5)

    //megadott soron belül karakterre pozicionál
    gtk.text_buffer.get_iter_at_line_offset(buffer,text_iter,4,5)

    gtk.text_buffer.insert(buffer,text_iter,ins)
    gtk.text_iter.free(text_iter) //fel kell szabadítani

#else
    gtk.text_buffer.set_text(buffer,txt,-1)
#endif

    return scrolled_window

******************************************************************************
