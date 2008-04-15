
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
static color:=gdk.color.new("blue")

******************************************************************************
static function cb_color_changed(colorsel)
local ncolor:=gdk.color.new()
    colorsel:get_current_color(ncolor)
    drawingarea:modify_bg(GTK_STATE_NORMAL,ncolor)
    gdk.color.free(ncolor)

******************************************************************************
static function  cb_area_event(widget,event,drawingarea)

local handled:=FALSE
local response
local colorsel

    if( gdk.event.get_type(event)==GDK_BUTTON_PRESS )
        handled:=TRUE

        if( colorseldlg==NIL )
            colorseldlg:=gtkcolorselectiondialogNew("Select background color")
            colorsel:=colorseldlg:get_colorsel()
            //colorsel:signal_connect("color_changed",{||cb_color_changed(colorsel)})
            colorsel:signal_connect("color_changed",{|w|cb_color_changed(w)})
            colorsel:set_has_palette(TRUE)
        else
            colorsel:=colorseldlg:get_colorsel()
        end

        colorsel:set_previous_color(color)
        colorsel:set_current_color(color)

        response:=colorseldlg:run()
        if( response==GTK_RESPONSE_OK )
            colorsel:get_current_color(color) //beírja color-ba az új értéket
        else 
            drawingarea:modify_bg(GTK_STATE_NORMAL,color) //visszaállítja
        end
        colorseldlg:hide()
    end

    return handled

******************************************************************************
function main()
local window

    gtk.init()

    window:=gtkwindowNew()
    window:set_title("Color selection test")
    window:set_resizable(TRUE)
    window:signal_connect("destroy",{||gtk.main_quit()})
  
    drawingarea:=gtkdrawingareaNew()
    drawingarea:modify_bg(GTK_STATE_NORMAL,color)
    drawingarea:set_size_request(200,200)
    drawingarea:set_events(GDK_BUTTON_PRESS_MASK)
    drawingarea:signal_connect("event",{|w,e|cb_area_event(w,e,drawingarea)})
    window:add(drawingarea)

    window:show_all
    gtk.main()
    ?

******************************************************************************
