
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
function _zedit_backspace(this)

local line, lenrow

    if( this:actcol>1 )

        if( len(this:atxt[this:actrow])>=this:actcol-1 )
            this:atxt[this:actrow]:=stuff(this:atxt[this:actrow],this:actcol-1,1,"")
        end
        
        if( this:wincol>0 )
            this:wincol:=this:wincol-1
            this:displine()
        else
            this:sftcol:=this:sftcol-1
            this:display()
        end

    elseif( this:actrow>1 )  //this:actcol==1 this:sftcol==0 this:wincol==0

        line:=this:atxt[this:actrow]
        adel(this:atxt,this:actrow)
        asize(this:atxt,len(this:atxt)-1)
        
        if( this:winrow>0 )
            this:winrow:=this:winrow-1
        else
            this:sftrow:=this:sftrow-1
        end
   
        lenrow:=len(this:atxt[this:actrow])
        this:wincol:=lenrow

        if( this:wincol>this:width-1 )
            this:wincol:=this:width-1
        elseif( this:wincol<0 )
            this:wincol:=0
        end

        this:sftcol:=lenrow-this:wincol
        this:atxt[this:actrow]+=line

        this:display()
    end
    
    return NIL


*****************************************************************************
