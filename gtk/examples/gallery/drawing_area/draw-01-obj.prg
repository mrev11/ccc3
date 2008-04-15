
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

#define CHECK_SIZE      20
#define SPACING         4

******************************************************************************
function main()
local window
    gtk.init()
    window:=make_window()
    window:show_all()
    gtk.main()

******************************************************************************
function make_window()

local window,vbox,label,frame,area

    window:=gtkwindowNew()
    window:set_title("GtkDrawingArea Demo")
    window:set_default_size(280, 250)
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_border_width(8)

    vbox:=gtkvboxNew(.f.,8)
    vbox:set_border_width(8)
    window:add(vbox)

    label:=gtklabelNew()
    label:set_markup("<u>Checkerboard pattern</u>")
    vbox:pack_start(label,.f.,.f.,0)
      
    frame:=gtkframeNew()
    frame:set_shadow_type(GTK_SHADOW_IN)
    vbox:pack_start(frame,.t.,.t.,0)
      
    area:=gtkdrawingareaNew()
    area:set_size_request(100,100)
    area:signal_connect("expose_event",{|w,e|cb_expose_event(w,e)})
    frame:add(area)

    return window

******************************************************************************
static function cb_expose_event(area,event)

local draw:=area:get_drawable //GdkDrawable
local alloc:=area:get_allocation //GtkAllocation -> {x,y,w,h} 
local width:=alloc[3]
local height:=alloc[4]

local color:=gdk.color.new()
local gc1:=gdk.gc.new(draw)
local gc2:=gdk.gc.new(draw)

local i,j,gc,xcount,ycount

    ? "cb_expose_event", alloc

    gdk.color.parse("#880088",color)
    gdk.gc.set_rgb_fg_color(gc1,color)

    gdk.color.parse("#ffffff",color)
    gdk.gc.set_rgb_fg_color(gc2,color)

    xcount:=0
    i:=SPACING

    while( i<width )
        j:=SPACING
        ycount:=xcount%2 //start with even/odd depending on row

        while( j<height )
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
