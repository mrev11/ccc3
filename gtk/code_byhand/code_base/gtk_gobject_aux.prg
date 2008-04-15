
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

#define DEBUG_REGISTER

namespace gtk.gobject

static signal_codeblock:={}

*******************************************************************************
function signal_initialize_codeblock()
    signal_codeblock:={}

*******************************************************************************
function signal_unregister_codeblock(idx)
    signal_codeblock[idx]:=NIL

*******************************************************************************
function signal_register_codeblock(widget_ptr, code_blk, widget_obj)

local r:={widget_ptr, code_blk, widget_obj}
local x:=ascan(signal_codeblock,{|a|a==NIL})

    if( x>0 )
        signal_codeblock[x]:=r
    else
        aadd(signal_codeblock,r)
        x:=len(signal_codeblock)
    end

    #ifdef DEBUG_REGISTER
    ? "REGISTER",len(signal_codeblock), widget_ptr
    #endif
    
    return x

*******************************************************************************
function signal_execute_codeblock(idx,widget,data1,data2,data3)

local wdg:=signal_codeblock[idx][1]
local blk:=signal_codeblock[idx][2]
local obj:=signal_codeblock[idx][3]

    if( wdg==widget )
        if( obj==NIL )
            obj:=wdg
        end
        return eval(blk,obj,data1,data2,data3)
    end

    ? "signal block: invalid widget"

*******************************************************************************
    