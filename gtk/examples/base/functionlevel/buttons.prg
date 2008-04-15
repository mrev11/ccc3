
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
function xpm_label_box(xpm_filename,label_text)

local box, label, image

    box:=gtk.hbox.new (FALSE, 0)
    gtk.container.set_border_width(box, 2)
    image:=gtk.image.new_from_file(xpm_filename)
    label:=gtk.label.new(label_text)

    gtk.box.pack_start(box,image, FALSE, FALSE, 3)
    gtk.box.pack_start(box,label, FALSE, FALSE, 3)

    gtk.widget.show(image)
    gtk.widget.show(label)

    return box

*******************************************************************************
static function callback(data)
    ?  "Hello again - ",data,"was pressed"

*******************************************************************************
function main()
local window, button, box

    gtk.init()

    window:=gtk.window.new()
    gtk.window.set_title(window,"Pixmap'd Buttons!")
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window, 10)

    button:=gtk.button.new()
    gtk.gobject.signal_connect(button,"clicked",{||callback("cool button")})

    box:=xpm_label_box("info.xpm","Cool button")
    //box:=xpm_label_box("SVI_0136.png","Cool button") //png-t is tud
    gtk.widget.show(box)
    gtk.container.add(button, box)

    //gtk.button.set_use_underline(button,TRUE)
    //gtk.button.set_label(button,"Cool button")

    gtk.widget.show(button)

    gtk.container.add(window, button)
    gtk.widget.show (window)

    gtk.main()
    ?


*******************************************************************************
