
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
class gladespinbutton(gtkspinbutton,gladewidget) new:
    method initialize

****************************************************************************
static function gladespinbutton.initialize(this)

local adjustment:=this:widget_hash:get("adjustment")
local adj,a1,a2,a3,a4,a5,a6

    if( adjustment!=NIL )
        adj:=alltrim(adjustment)
        while("  "$adj)
            adj:=strtran(adj,"  "," ")
        end
        adj:=split(adj," ")
        asize(adj,6)
        a1:=val(adj[1])
        a2:=val(adj[2])
        a3:=val(adj[3])
        a4:=val(adj[4])
        a5:=val(adj[5])
        a6:=val(adj[6])
        adj:=gtk.adjustment.new(a1,a2,a3,a4,a5,a6)
    end
    this:gobject:=gtk.spin_button.new(adj)
    return this

****************************************************************************

#ifdef NOT_DEFINED
          <property name="climb_rate">1</property>
          <property name="digits">0</property>
          <property name="numeric">False</property>
          <property name="update_policy">GTK_UPDATE_ALWAYS</property>
          <property name="snap_to_ticks">False</property>
          <property name="wrap">False</property>
          <property name="adjustment">1 0 100 1 10 10</property>
#endif