
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
class gladetable(gtktable,gladewidget) new:
    method initialize
    method packitem

****************************************************************************
static function gladetable.initialize(this)

local nrow:=val(this:widget_hash:get("n_rows"))
local ncol:=val(this:widget_hash:get("n_columns"))
local homo:=FLAG1(this:widget_hash:get("homogeneous"))
local rspac:=this:widget_hash:get("row_spacing")
local cspac:=this:widget_hash:get("column_spacing")

    this:gobject:=gtk.table.new(nrow,ncol,homo)
    
    if( rspac!=NIL )
        this:set_row_spacings(val(rspac))
    end

    if( cspac!=NIL )
        this:set_col_spacings(val(cspac))
    end
    
    return this


****************************************************************************
static function gladetable.packitem(this,w)
local la,ra,ta,ba
local xopt,yopt

    la:=val(w:packing_hash:get("left_attach"))
    ra:=val(w:packing_hash:get("right_attach"))
    ta:=val(w:packing_hash:get("top_attach"))
    ba:=val(w:packing_hash:get("bottom_attach"))

    xopt:=w:packing_hash:get("x_options")
    if( xopt=="fill" )
        xopt:=GTK_FILL
    elseif( xopt=="expand" )
        xopt:=GTK_EXPAND
    else
        xopt:=NIL
    end

    yopt:=w:packing_hash:get("y_options")
    if( yopt=="fill" )
        yopt:=GTK_FILL
    elseif( yopt=="expand" )
        yopt:=GTK_EXPAND
    else
        yopt:=NIL
    end
    
    this:attach(w,la,ra,ta,ba,xopt,yopt)

****************************************************************************
