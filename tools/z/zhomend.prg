
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

****************************************************************************
function _zedit_home(this)

    this:wincol:=0
    if( this:sftcol!=0 )
        this:sftcol:=0
        this:display()
    end
    return NIL

****************************************************************************
function _zedit_end(this)

local sftprv:=this:sftcol
local lenrow:=len(this:atxt[this:actrow])
            
    this:wincol:=lenrow

    if( this:wincol>this:width-1 )
        this:wincol:=this:width-1
    elseif( this:wincol<0 )
        this:wincol:=0
    end
    this:sftcol:=lenrow-this:wincol

    if( sftprv!=this:sftcol )
        this:display()
    end
    return NIL

****************************************************************************
