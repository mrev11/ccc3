
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

*****************************************************************************
function _zedit_tab(this)

local rlen:=len(this:atxt[this:actrow])
local ts:=this:actcol%this:tabsiz
    if( ts==0 )
        ts:=this:tabsiz
    end
    ts:=this:tabsiz-ts+1

    if( this:actcol<=rlen  )
        this:atxt[this:actrow]:=stuff(this:atxt[this:actrow],this:actcol,0,space(ts))
    end

    this:wincol:=this:wincol+ts

    if( this:wincol>this:width-1 )
        this:wincol:=this:width-1
        this:sftcol:=rlen-this:wincol
        this:display()
    else
        this:displine()
    end

    return NIL

*****************************************************************************

