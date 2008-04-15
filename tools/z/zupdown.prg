
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
function _zedit_down(this)

    if( this:actrow<len(this:atxt) )
        if( this:winrow<this:height-1 )
            this:winrow:=this:winrow+1
        else
            this:sftrow:=this:sftrow+1
            this:scroll(1)
            this:displine()
        end
    end

    return NIL

****************************************************************************
function _zedit_up(this)

    if( this:actrow>1 )

        if( this:winrow>0 )
            this:winrow:=this:winrow-1
        else
            this:sftrow:=this:sftrow-1
            this:scroll(-1)
            this:displine()
        end
    end

    return NIL

****************************************************************************

