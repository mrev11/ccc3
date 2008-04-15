
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
class gladeframe(gtkframe,gladewidget) new:
    method initialize
    method packitem

****************************************************************************
static function gladeframe.initialize(this)
    this:gobject:=gtk.frame.new()
    return this

****************************************************************************
static function gladeframe.packitem(this,w)
    if( empty(this:get_child:gobject) )
        this:add(w) //first <child>
    else
        this:set_label_widget(w) //second <child>
    end

****************************************************************************
