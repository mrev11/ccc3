
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

#define S_ROW  10
#define S_COL  15

****************************************************************************
function _zedit_setpos(this,r,c)

local dsp:=.f.

    if( 1<=r .and. r<=len(this:atxt) .and. 1<=c )

        this:winrow:=r-this:sftrow-1
        this:wincol:=c-this:sftcol-1

        //függőleges korrekció

        if( this:winrow<0 )
            this:sftrow:=this:sftrow+this:winrow
            this:winrow:=0
            dsp:=.t.
        end
        while( this:sftrow>0 .and. this:winrow<S_ROW )
            this:winrow:=this:winrow+1
            this:sftrow:=this:sftrow-1
            dsp:=.t.
        end
        while( this:winrow>this:height-S_ROW )
            this:winrow:=this:winrow-1
            this:sftrow:=this:sftrow+1
            dsp:=.t.
        end

        //vízszintes korrekció

        if( this:wincol<0 )
            this:sftcol:=this:sftcol+this:wincol
            this:wincol:=0
            dsp:=.t.
        end
        while( this:sftcol>0 .and. this:wincol<this:width-S_COL )
            this:wincol:=this:wincol+1
            this:sftcol:=this:sftcol-1
            dsp:=.t.
        end
        while( this:wincol>this:width-S_COL )
            this:wincol:=this:wincol-1
            this:sftcol:=this:sftcol+1
            dsp:=.t.
        end

        
        if( dsp )
            this:display()
        end
    end

    return NIL

****************************************************************************

    