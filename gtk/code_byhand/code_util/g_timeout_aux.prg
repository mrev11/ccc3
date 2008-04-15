
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

static timeout_codeblock:={}

*******************************************************************************
function g_timeout_register_codeblock(blk)
local x:=ascan(timeout_codeblock,{|a|a==NIL})
    if( x>0 )
        timeout_codeblock[x]:=blk
    else
        aadd(timeout_codeblock,blk)
        x:=len(timeout_codeblock)
    end
    //? "timer block registered",x
    return x

*******************************************************************************
function g_timeout_execute_codeblock(x)
local result:=eval(timeout_codeblock[x])
    if( !result )
        timeout_codeblock[x]:=NIL
        //? "timer block removed",x
    end
    return result

*******************************************************************************
    