
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


****************************************************************************
class gladetoolbar(gtktoolbar,gladewidget) new:
    method initialize
    method packitem

****************************************************************************
static function gladetoolbar.initialize(this)

//local orientation:=this:widget_hash:get("orientation")
local toolbar_style:=this:widget_hash:get("toolbar_style")
//local tooltips:=this:widget_hash:get("tooltips")
//local show_arrow:=this:widget_hash:get("show_arrow")

    this:gobject:=gtk.toolbar.new()
    
    if( toolbar_style!=NIL )
        this:set_style(gtksym(toolbar_style))
    end

    return this

****************************************************************************
static function gladetoolbar.packitem(this,w)

    //this:add(w) //deprecated??
    
    if( w:isderivedfrom(gtktoolitemClass()) )
        //itt a placeholdereket kerülöm ki,
        //amik helyére jelenleg GtKVBox kerül

        this:insert(w,-1) //a végére
    end
    


****************************************************************************
