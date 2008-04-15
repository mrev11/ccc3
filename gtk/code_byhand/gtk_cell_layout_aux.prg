
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

namespace gtk.cell_layout

static cell_codeblock:={}

*******************************************************************************
function cell_initialize_codeblock()
    cell_codeblock:={}

*******************************************************************************
function cell_unregister_codeblock(idx)
    cell_codeblock[idx]:=NIL

*******************************************************************************
function cell_register_codeblock(column,renderer,codeblock,objcol,objrnd,objmod)

local r:={column,renderer,codeblock,objcol,objrnd,objmod}
local x:=ascan(cell_codeblock,{|a|a==NIL})

    if( x>0 )
        cell_codeblock[x]:=r
        return x
    else
        aadd(cell_codeblock,r)
        return len(cell_codeblock)
    end

*******************************************************************************
function cell_execute_codeblock(idx,column,renderer,model,iter)

local col:=cell_codeblock[idx][1]
local rnd:=cell_codeblock[idx][2]
local blk:=cell_codeblock[idx][3]
local objcol:=cell_codeblock[idx][4]
local objrnd:=cell_codeblock[idx][5]
local objmod:=cell_codeblock[idx][6]

    if( col==column .and. rnd==renderer )
        if(objcol!=NIL)
            column:=objcol
        end
        if(objrnd!=NIL)
            renderer:=objrnd
        end
        if(objmod!=NIL)
            model:=objmod
        end
        return eval(blk,column,renderer,model,iter)
    end

    ? "cell block: invalid column/renderer"

*******************************************************************************
    