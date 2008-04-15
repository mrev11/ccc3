
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

#define CHECK_SIZE      10
#define SPACING         4

******************************************************************************
function main()
local window
    gtk.init()
    window:=make_window()
    gtk.widget.show_all(window)
    gtk.main()

******************************************************************************
function make_window()

local window,vbox,label,frame,area

    window:=gtk.window.new()
    gtk.window.set_title(window,"GtkDrawingArea Demo")
    gtk.window.set_default_size(window, 280, 250)
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,8)

    vbox:=gtk.vbox.new(.f.,8)
    gtk.container.set_border_width(vbox,8)
    gtk.container.add(window,vbox)

    label:=gtk.label.new()
    gtk.label.set_markup(label,"<u>Checkerboard pattern</u>")
    gtk.box.pack_start(vbox,label,.f.,.f.,0)
      
    frame:=gtk.frame.new()
    gtk.frame.set_shadow_type(frame,GTK_SHADOW_IN)
    gtk.box.pack_start(vbox,frame,.t.,.t.,0)
      
    area:=gtk.drawing_area.new()
    gtk.widget.set_size_request(area,100,100)
    gtk.gobject.signal_connect(area,"expose_event",{|w,e|cb_expose_event(w,e)})
    gtk.container.add(frame,area)

    return window

******************************************************************************
static function cb_expose_event(area,event)

local draw:=gtk.widget.get_drawable(area) //GdkDrawable
local alloc:=gtk.widget.get_allocation(area) //GtkAllocation -> {x,y,w,h}
local width:=alloc[3]
local height:=alloc[4]

local color:=gdk.color.new()
local gc1:=gdk.gc.new(draw)
local gc2:=gdk.gc.new(draw)

local i,j,gc,xcount,ycount

    ? "cb_expose_event",alloc
    
    gdk.color.parse("#880088",color)
    gdk.gc.set_rgb_fg_color(gc1,color)

    gdk.color.parse("#ffffff",color)
    gdk.gc.set_rgb_fg_color(gc2,color)

    xcount:=0
    i:=SPACING

    while( i<width-10 )
        j:=SPACING
        ycount:=xcount%2 //start with even/odd depending on row

        while( j<height-10 )
            if( ycount%2==0 )
                gc:=gc1
            else
                gc:=gc2
            end

            gdk.drawable.draw_rectangle(draw,gc,.t.,i,j,CHECK_SIZE,CHECK_SIZE)

            j+=CHECK_SIZE+SPACING
            ++ycount
        end
        i+=CHECK_SIZE+SPACING
        ++xcount
    end
    
    //clean up
    gdk.color.free(color)
    gtk.gobject.unref(gc1)
    gtk.gobject.unref(gc2)

    return .f.

******************************************************************************
