
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
static function create_bbox(horizontal,title,spacing,child_w,child_h,layout)
local frame, bbox, button

    frame:=gtkframeNew(title)

    if( horizontal )
        bbox:=gtkhbuttonboxNew()
    else
        bbox:=gtkvbuttonboxNew()
    end

    bbox:set_border_width(5)
    frame:add(bbox)

    bbox:set_layout(layout)
    bbox:set_spacing(spacing)
    //bbox:set_child_size(child_w,child_h) //deprecated

    button:=gtkbuttonNew_from_stock("gtk-ok")
    bbox:add(button)

    button:=gtkbuttonNew_from_stock("gtk-cancel")
    bbox:add(button)

    button:=gtkbuttonNew_from_stock("gtk-help")
    bbox:add(button)

    return frame

******************************************************************************
function main()

local window, main_vbox
local vbox, hbox, frame_horz, frame_vert

    gtk.init()

    window:=gtkwindowNew()
    window:set_title("Button Boxes")
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(10)
    main_vbox:=gtkvboxNew(FALSE, 0)
    window:add(main_vbox)
    

    frame_horz:=gtkframeNew("Horizontal Button Boxes")
    main_vbox:pack_start(frame_horz,TRUE,TRUE,10)

    vbox:=gtkvboxNew(FALSE,0)
    vbox:set_border_width(10)
    frame_horz:add(vbox)

    vbox:pack_start(;
        create_bbox(TRUE,"Spread (spacing 40)",40,85,20,GTK_BUTTONBOX_SPREAD),;
        TRUE,TRUE,0)

    vbox:pack_start(;
        create_bbox(TRUE,"Edge (spacing 30)",30,85,20,GTK_BUTTONBOX_EDGE),;
        TRUE,TRUE,5)

    vbox:pack_start(;
        create_bbox(TRUE,"Start (spacing 20)",20,85,20,GTK_BUTTONBOX_START),;
        TRUE,TRUE,5)

    vbox:pack_start(;
        create_bbox(TRUE,"End (spacing 10)",10,85,20,GTK_BUTTONBOX_END),;
        TRUE,TRUE,5)


    frame_vert:=gtkframeNew("Vertical Button Boxes")
    main_vbox:pack_start(frame_vert,TRUE,TRUE,10)

    hbox:=gtkhboxNew(FALSE,0)
    hbox:set_border_width(10)
    frame_vert:add(hbox)

    hbox:pack_start(;
        create_bbox(FALSE,"Spread (spacing 5)",5,85,20,GTK_BUTTONBOX_SPREAD),;
        TRUE,TRUE,0)

    hbox:pack_start(;
        create_bbox(FALSE,"Edge (spacing 30)",30,85,20,GTK_BUTTONBOX_EDGE),;
        TRUE,TRUE,5)

    hbox:pack_start(;
        create_bbox(FALSE,"Start (spacing 20)",20,85,20,GTK_BUTTONBOX_START),;
        TRUE,TRUE,5)

    hbox:pack_start(;
        create_bbox(FALSE,"End (spacing 20)",20,85,20,GTK_BUTTONBOX_END),;
        TRUE,TRUE,5)


    window:show_all
    gtk.main()
    ?

******************************************************************************
