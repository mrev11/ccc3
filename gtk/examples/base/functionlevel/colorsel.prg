
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

#define FALSE .f.
#define TRUE  .t.

static colorseldlg
static drawingarea
static color:=gdk.color.new()

******************************************************************************
static function cb_color_changed(colorsel)
local ncolor:=gdk.color.new() //fel kell szabadítani!
    gtk.color_selection.get_current_color(colorsel,ncolor)
    gtk.widget.modify_bg(drawingarea,GTK_STATE_NORMAL,ncolor)
    gdk.color.free(ncolor)

******************************************************************************
static function  cb_area_event(widget,event,drawingarea)

local handled:=FALSE
local response
local colorsel
local id

    if( gdk.event.get_type(event)==GDK_BUTTON_PRESS )
        handled:=TRUE

        if( colorseldlg==NIL )
            colorseldlg:=gtk.color_selection_dialog.new("Select background color")
        end

        // Get the ColorSelection widget
        colorsel:=gtk.color_selection_dialog.get_colorsel(colorseldlg)

        gtk.color_selection.set_previous_color(colorsel,color)
        gtk.color_selection.set_current_color(colorsel,color)
        gtk.color_selection.set_has_palette(colorsel,TRUE)

        id:=gtk.gobject.signal_connect(colorsel,"color_changed",{||cb_color_changed(colorsel)})

        response:=gtk.dialog.run(colorseldlg)
        if( response==GTK_RESPONSE_OK )
            gtk.color_selection.get_current_color(colorsel,color)
        else 
            gtk.widget.modify_bg(drawingarea,GTK_STATE_NORMAL,color)
        end
        gtk.widget.hide(colorseldlg)

        gtk.gobject.signal_handler_disconnect(colorsel,id)
        
        //Az eredeti példaprogram hibás, 
        //mert halmozódik benne a signal_connect,
        //azaz fogyasztja a memóriát (persze elég lassan),
        //ezért signal_handler_disconnect kell.
    end

    return handled

******************************************************************************
function main()

local window

    gtk.init()

    window:=gtk.window.new()
    gtk.window.set_title(window,"Color selection test")
    //gtk.window.set_resizable(window,TRUE)
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
  
    drawingarea:=gtk.drawing_area.new()
    //gdk.color.parse("blue",color) //kéket rak color-ba
    gdk.color.parse("#8080ff",color)

    gtk.widget.modify_bg(drawingarea,GTK_STATE_NORMAL,color)
    gtk.widget.set_size_request(drawingarea,200,200)
    gtk.widget.set_events(drawingarea,GDK_BUTTON_PRESS_MASK)
    gtk.gobject.signal_connect(drawingarea,"event",{|w,e|cb_area_event(w,e,drawingarea)})
    gtk.container.add(window,drawingarea)

    gtk.widget.show_all(window)
    gtk.main()
    ?


******************************************************************************
