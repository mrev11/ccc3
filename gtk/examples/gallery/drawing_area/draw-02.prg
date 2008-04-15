
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
function main()
local window
    gtk.init()
    window:=make_window()
    gtk.widget.show_all(window)
    gtk.main()

******************************************************************************
function make_window()

local window,vbox,label,frame,area,mask

    window:=gtk.window.new()
    gtk.window.set_title(window,"GtkDrawingArea Demo")
    gtk.window.set_default_size(window, 280, 250)
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,8)

    vbox:=gtk.vbox.new(.f.,8)
    gtk.container.set_border_width(vbox,8)
    gtk.container.add(window,vbox)

    label:=gtk.label.new()
    gtk.label.set_markup(label,"<u>Scribble area</u>")
    gtk.box.pack_start(vbox,label,.f.,.f.,0)
      
    frame:=gtk.frame.new()
    gtk.frame.set_shadow_type(frame,GTK_SHADOW_IN)
    gtk.box.pack_start(vbox,frame,.t.,.t.,0)
      
    area:=gtk.drawing_area.new()
    gtk.widget.set_size_request(area,100,100)
    gtk.gobject.signal_connect(area,"configure_event",{|w,e|cb_configure_event(w,e)})
    gtk.gobject.signal_connect(area,"expose_event",{|w,e|cb_expose_event(w,e)})
    gtk.gobject.signal_connect(area,"motion_notify_event",{|w,e|cb_motion_notify_event(w,e)})
    gtk.gobject.signal_connect(area,"button_press_event",{|w,e|cb_button_press_event(w,e)})
    //receive events the area doesn't normally subscribe to
    mask:=gtk.widget.get_events(area)
    //mask:=numor(mask,GDK_LEAVE_NOTIFY_MASK)
    mask:=numor(mask,GDK_BUTTON_PRESS_MASK)
    mask:=numor(mask,GDK_POINTER_MOTION_MASK)
    //mask:=numor(mask,GDK_POINTER_MOTION_HINT_MASK)
    gtk.widget.set_events(area,mask)
    gtk.container.add(frame,area)

    return window

******************************************************************************
static function cb_configure_event(area,event)
local draw:=gtk.widget.get_drawable(area) //GdkDrawable
local alloc:=gtk.widget.get_allocation(area) //GtkAllocation -> {x,y,w,h}
local style:=gtk.widget.get_style(area)
local gc:=gtk.style.get_white_gc(style)
local width:=alloc[3]
local height:=alloc[4]
    if( pixmap!=NIL )
        gtk.gobject.unref(pixmap)
    end
    pixmap:=gdk.pixmap.new(draw,width,height,-1)
    gdk.drawable.draw_rectangle(pixmap,gc,.t.,0,0,width,height)
    //? "configure_event"
    return .t.

******************************************************************************
static function cb_expose_event(area,event)
local draw:=gtk.widget.get_drawable(area) //GdkDrawable
local style:=gtk.widget.get_style(area)
local gc:=gtk.style.get_fg_gc(style)
local rect:=gdk.event_expose.get_area(event) //{x,y,w,h}
local x:=rect[1],y:=rect[2],w:=rect[3],h:=rect[4]
    gdk.drawable.draw_drawable(draw,gc,pixmap,x,y,x,y,w,h)
    //? "expose_event", rect
    return .f.

******************************************************************************
static function cb_motion_notify_event(area,event)
local wnd:=gtk.widget.get_drawable(area) //GdkDrawable/GdkWindow
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
local draw:=gtk.widget.get_drawable(area) //GdkDrawable
local style:=gtk.widget.get_style(area)
local gc:=gtk.style.get_black_gc(style)
local x:=px-2,y:=py-2,w:=4,h:=4
    //paint to the pixmap, where we store our state 
    gdk.drawable.draw_rectangle(pixmap,gc,.t.,x,y,w,h)
    gdk.window.invalidate_rect(draw,x,y,w,h,.f.)


******************************************************************************
