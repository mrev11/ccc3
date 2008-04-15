
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
class gladeprogressbar(gtkprogressbar,gladewidget) new:
    method initialize

****************************************************************************
static function gladeprogressbar.initialize(this)

local orientation:=this:widget_hash:get("orientation")
local fraction:=this:widget_hash:get("fraction")
local pulse_step:=this:widget_hash:get("pulse_step")
local text:=this:widget_hash:get("text")

    this:gobject:=gtk.progress_bar.new()

    return this

****************************************************************************

#ifdef NOT_DEFINED
        <widget class="GtkProgressBar" id="progressbar1">
          <property name="visible">True</property>
          <property name="orientation">GTK_PROGRESS_LEFT_TO_RIGHT</property>
          <property name="fraction">0</property>
          <property name="pulse_step">0.10000000149</property>
          <property name="text" translatable="yes">Türelem rózsát terem</property>
          <property name="ellipsize">PANGO_ELLIPSIZE_NONE</property>
        </widget>
#endif
