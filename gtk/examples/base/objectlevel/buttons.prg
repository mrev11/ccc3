
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

local box,label,image

    box:=gtkhboxNew(FALSE,0)
    box:set_border_width(2)
    image:=gtkimageNew_from_file(xpm_filename)
    label:=gtklabelNew(label_text)

    box:pack_start(image, FALSE, FALSE, 3)
    box:pack_start(label, FALSE, FALSE, 3)

    return box

*******************************************************************************
static function callback(data)
    ?  "Hello again - ",data,"was pressed"

*******************************************************************************
function main()
local window, button, box

    gtk.init()

    window:=gtkwindowNew()
    window:set_title("Pixmap'd Buttons!")
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(10)

    button:=gtkbuttonNew()
    button:signal_connect("clicked",{||callback("cool button")})

    box:=xpm_label_box("info.xpm","Cool button")
    button:add(box)
    window:add(button)
    window:show_all

    gtk.main()
    ?

*******************************************************************************
