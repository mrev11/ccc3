
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
class gladealignment(gtkalignment,gladewidget) new:
    method initialize

****************************************************************************
static function gladealignment.initialize(this)

local xa:=VAL2(this:widget_hash:get("xalign"),0.5)
local ya:=VAL2(this:widget_hash:get("yalign"),0.5)
local xs:=VAL2(this:widget_hash:get("xscale"),0)
local ys:=VAL2(this:widget_hash:get("yscale"),0)

local tp:=this:widget_hash:get("top_padding")
local bp:=this:widget_hash:get("bottom_padding")
local lp:=this:widget_hash:get("left_padding")
local rp:=this:widget_hash:get("right_padding")

    this:gobject:=gtk.alignment.new(xa,ya,xs,ys)
    
    if( tp!=NIL .or. bp!=NIL .or. lp!=NIL .or. rp!=NIL )
        this:set_padding(val(tp),val(bp),val(lp),val(rp))
    end
    
    return this

****************************************************************************


#ifdef EMLEKEZTETO
widget_hash gladealignment
         4 {xalign,0.5}
         5 {yalign,0.5}
         9 {xscale,0}
        10 {yscale,0}
        11 {top_padding,0}
        12 {bottom_padding,0}
        13 {left_padding,0}
        14 {right_padding,0}
        15 {visible,True}

(define-function gtk_alignment_new
  (c-name "gtk_alignment_new")
  (is-constructor-of GtkAlignment)
  (return-type "GtkWidget*")
  (parameters
    '("gfloat" "xalign" (default "0.0"))
    '("gfloat" "yalign" (default "0.0"))
    '("gfloat" "xscale" (default "0.0"))
    '("gfloat" "yscale" (default "0.0"))
  )
)

(define-method set_padding
  (of-object "GtkAlignment")
  (c-name "gtk_alignment_set_padding")
  (return-type "none")
  (parameters
    '("guint" "padding_top"     (default "0"))
    '("guint" "padding_bottom"  (default "0"))
    '("guint" "padding_left"    (default "0"))
    '("guint" "padding_right"   (default "0"))
  )
)

#endif
