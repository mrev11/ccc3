
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

#include "gdk.ch"
#include "gtk.ch"

static pixmap


******************************************************************************
function draw(area)

local mask
      
    area:signal_connect("configure_event",{|w,e|cb_configure_event(w,e)})
    area:signal_connect("expose_event",{|w,e|cb_expose_event(w,e)})
    area:signal_connect("motion_notify_event",{|w,e|cb_motion_notify_event(w,e)})
    area:signal_connect("button_press_event",{|w,e|cb_button_press_event(w,e)})

    //receive events the area doesn't normally subscribe to
    mask:=area:get_events
    mask:=numor(mask,GDK_BUTTON_PRESS_MASK)
    mask:=numor(mask,GDK_POINTER_MOTION_MASK)
    area:set_events(mask)


******************************************************************************
static function cb_configure_event(area,event)
local draw:=area:get_drawable() //GdkDrawable
local alloc:=area:get_allocation() //GtkAllocation -> {x,y,w,h}
local gc:=area:get_style:get_white_gc()
local width:=alloc[3], height:=alloc[4]
local pixprev:=pixmap
    pixmap:=gdk.pixmap.new(draw,width,height,-1)
    gdk.drawable.draw_rectangle(pixmap,gc,.t.,0,0,width,height)
    if( pixprev!=NIL )
        gdk.drawable.draw_drawable(pixmap,gc,pixprev,0,0,0,0,width,height)
        gtk.gobject.unref(pixprev)
    end
    //? "configure_event"
    return .t.

static function cb_configure_event1(area,event)
local draw:=area:get_drawable() //GdkDrawable
local alloc:=area:get_allocation() //GtkAllocation -> {x,y,w,h}
local gc:=area:get_style:get_white_gc()
local width:=alloc[3], height:=alloc[4]
    if( pixmap!=NIL )
        gtk.gobject.unref(pixmap)
    end
    pixmap:=gdk.pixmap.new(draw,width,height,-1)
    gdk.drawable.draw_rectangle(pixmap,gc,.t.,0,0,width,height)
    //? "configure_event"
    return .t.

******************************************************************************
static function cb_expose_event(area,event)
local draw:=area:get_drawable() //GdkDrawable
local gc:=area:get_style:get_fg_gc()
local rect:=gdk.event_expose.get_area(event) //{x,y,w,h}
local x:=rect[1],y:=rect[2],w:=rect[3],h:=rect[4]
    gdk.drawable.draw_drawable(draw,gc,pixmap,x,y,x,y,w,h)
    //? "expose_event", rect
    return .f.

******************************************************************************
static function cb_motion_notify_event(area,event)
local wnd:=area:get_drawable() //GdkDrawable/GdkWindow
local ptr:=gdk.window.get_pointer(wnd) //{x,y,mask}
    if( ptr[3]==GDK_BUTTON1_MASK )
        draw_brush(area,ptr[1],ptr[2])
    end
    //? "motion_notify_event", ptr
    return .t.

******************************************************************************
static function cb_button_press_event(area,event)
local but:=gdk.event_button.get_button(event) //1,2,3 -- bal,köz,jobb
local xy:=gdk.event.get_coords(event)
local x:=xy[1],y:=xy[2]
    if( but==1 )
        draw_brush(area,x,y)
    end
    //? "button_press_event",xy
    return .t.

******************************************************************************
static function draw_brush(area,px,py)
local draw:=area:get_drawable() //GdkDrawable
local gc:=color_gc(draw,"red")
local x:=px-3,y:=py-3,w:=6,h:=6
    //paint to the pixmap, where we store our state 
    gdk.drawable.draw_rectangle(pixmap,gc,.t.,x,y,w,h)
    gdk.window.invalidate_rect(draw,x,y,w,h,.f.)
    gtk.gobject.unref(gc)

static function draw_brush1(area,px,py)
local draw:=area:get_drawable() //GdkDrawable
local gc:=area:get_style:get_black_gc()
local x:=px-3,y:=py-3,w:=6,h:=6
    //paint to the pixmap, where we store our state 
    gdk.drawable.draw_rectangle(pixmap,gc,.t.,x,y,w,h)
    gdk.window.invalidate_rect(draw,x,y,w,h,.f.)

******************************************************************************
static function color_gc(draw,colstr)
local color:=gdk.color.new()
local gc:=gdk.gc.new(draw)
    gdk.color.parse(colstr,color)
    gdk.gc.set_rgb_fg_color(gc,color)
    gdk.color.free(color)
    return gc

******************************************************************************
