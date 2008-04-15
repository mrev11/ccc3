
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

    frame:=gtk.frame.new(title)

    if( horizontal )
        bbox:=gtk.hbutton_box.new()
    else
        bbox:=gtk.vbutton_box.new()
    end

    gtk.container.set_border_width(bbox,5)
    gtk.container.add(frame,bbox)

    gtk.button_box.set_layout(bbox,layout)
    gtk.box.set_spacing(bbox, spacing)
    //gtk.button_box.set_child_size(bbox,child_w,child_h)

    button:=gtk.button.new_from_stock("gtk-ok")
    gtk.container.add(bbox, button)

    button:=gtk.button.new_from_stock("gtk-cancel")
    gtk.container.add(bbox, button)

    button:=gtk.button.new_from_stock("gtk-help")
    gtk.container.add (bbox, button)

    return frame

******************************************************************************
function main()
static window
local main_vbox, vbox, hbox, frame_horz, frame_vert

    gtk.init()

    window:=gtk.window.new()
    gtk.window.set_title(window,"Button Boxes")
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,10)

    main_vbox:=gtk.vbox.new(FALSE, 0)
    gtk.container.add(window,main_vbox)

    frame_horz:=gtk.frame.new("Horizontal Button Boxes")
    gtk.box.pack_start(main_vbox,frame_horz,TRUE,TRUE,10)

    vbox:=gtk.vbox.new(FALSE,0)
    gtk.container.set_border_width(vbox,10)
    gtk.container.add(frame_horz,vbox)

    gtk.box.pack_start(vbox,;
        create_bbox(TRUE,"Spread (spacing 40)",40,85,20,GTK_BUTTONBOX_SPREAD),;
        TRUE,TRUE,0)

    gtk.box.pack_start(vbox,;
        create_bbox(TRUE,"Edge (spacing 30)",30,85,20,GTK_BUTTONBOX_EDGE),;
        TRUE,TRUE,5)

    gtk.box.pack_start(vbox,;
        create_bbox(TRUE,"Start (spacing 20)",20,85,20,GTK_BUTTONBOX_START),;
        TRUE,TRUE,5)

    gtk.box.pack_start(vbox,;
        create_bbox(TRUE,"End (spacing 10)",10,85,20,GTK_BUTTONBOX_END),;
        TRUE,TRUE,5)


    frame_vert:=gtk.frame.new("Vertical Button Boxes")
    gtk.box.pack_start(main_vbox,frame_vert,TRUE,TRUE,10)

    hbox:=gtk.hbox.new(FALSE,0)
    gtk.container.set_border_width(hbox,10)
    gtk.container.add(frame_vert,hbox)

    gtk.box.pack_start(hbox,;
        create_bbox(FALSE,"Spread (spacing 5)",5,85,20,GTK_BUTTONBOX_SPREAD),;
        TRUE,TRUE,0)

    gtk.box.pack_start(hbox,;
        create_bbox(FALSE,"Edge (spacing 30)",30,85,20,GTK_BUTTONBOX_EDGE),;
        TRUE,TRUE,5)

    gtk.box.pack_start(hbox,;
        create_bbox(FALSE,"Start (spacing 20)",20,85,20,GTK_BUTTONBOX_START),;
        TRUE,TRUE,5)

    gtk.box.pack_start(hbox,;
        create_bbox(FALSE,"End (spacing 20)",20,85,20,GTK_BUTTONBOX_END),;
        TRUE,TRUE,5)

    gtk.widget.show_all(window)
    gtk.main ()
    ?

******************************************************************************
