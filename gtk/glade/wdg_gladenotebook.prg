
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
#include "gladeutil.ch"

****************************************************************************
class gladenotebook(gtknotebook,gladewidget) new:
    method initialize
    method packitem
    attrib number_of_pages

****************************************************************************
static function gladenotebook.initialize(this)

//local show_tabs:=FLAG2(this:widget_hash:get("show_tabs"),.t.)
//local show_border:=FLAG2(this:widget_hash:get("show_border"),.t.)
local tab_pos:=GTKSYM2(this:widget_hash:get("tab_pos"),GTK_POS_TOP)
local scrollable:=FLAG2(this:widget_hash:get("scrollable"),.f.)
local enable_popup:=FLAG2(this:widget_hash:get("enable_popup"),.f.)

    this:gobject:=gtk.notebook.new()
    this:number_of_pages:=0

    this:set_tab_pos(tab_pos)
    this:set_scrollable(scrollable)
    if( enable_popup )
        this:popup_enable(enable_popup)
    end
    return this

****************************************************************************
static function gladenotebook.packitem(this,w)
local type:=w:packing_hash:get("type")
    if( type=="tab" )
        this:set_tab_label(this:get_nth_page(-1),w)
    else
        this:add(w)
    end

****************************************************************************
