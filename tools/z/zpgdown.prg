
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
function _zedit_pagedown(this)

local sftprv:=this:sftrow

    if( this:winrow<this:height-1 )
        this:winrow:=this:height-1
    else
        this:sftrow:=this:sftrow+this:height
    end

    if( this:actrow>len(this:atxt) )
        this:sftrow:=this:sftrow+len(this:atxt)-this:actrow
        if( this:sftrow<0 )
            this:winrow:=this:winrow+this:sftrow
            this:sftrow:=0
        end
    end

    if( sftprv!=this:sftrow )
        this:display()
    end
    
    return NIL

****************************************************************************
function _zedit_ctrlpgdn(this)

    this:winrow:=min(this:height,len(this:atxt))-1
    this:sftrow:=len(this:atxt)-this:winrow-1
    this:wincol:=0
    this:display()
    return NIL

****************************************************************************
