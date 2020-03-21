
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

********************************************************************************************
function textview.moveright(this)
    if( this:wincol<this:width-1 )
        this:wincol:=this:wincol+1
    else
        this:sftcol:=this:sftcol+1
        this:display()
    end


********************************************************************************************
function textview.moveleft(this)
    if( this:actcol>1 )
        if( this:wincol>0 )
            this:wincol:=this:wincol-1
        else
            this:sftcol:=this:sftcol-1
            this:display()
        end
    end
    

********************************************************************************************
function textview.home(this)

    this:wincol:=0
    if( this:sftcol!=0 )
        this:sftcol:=0
        this:display()
    end


********************************************************************************************
function textview.end(this)

local sftprv:=this:sftcol
local lenrow:=this:line(this:actrow)::len
            
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


            
********************************************************************************************
function textview.down(this)

    if( this:winrow<this:height-1 )
        if( this:eolpos(this:winrow+2)!=NIL )
            this:winrow:=this:winrow+1
        end

    elseif( shift_down(this) )
        this:scroll(1)
        this:displine(this:height)
    end


********************************************************************************************
function textview.up(this)

    if( this:winrow>0 )
        this:winrow:=this:winrow-1
    elseif( shift_up(this) )
        this:scroll(-1)
        this:displine(1)
    end


********************************************************************************************
function textview.pagedown(this)
local n

    if( this:winrow<this:height-1 )
        for n:=1 to this:height
            if( this:eolpos(n)==NIL )
                exit
            end
        next
        this:winrow:=n-2
    else
        for n:=1 to this:height
            if( !shift_down(this) )
                exit
            end
        next
        if( n>1 )
            this:display()
        end
    end


********************************************************************************************
function textview.pageup(this)
local n

    if( this:winrow>0 )
        this:winrow:=0
    else
        for n:=1 to this:height
            if( !shift_up(this) )
                exit
            end
        next
        if( n>1 )
            this:display()
        end
    end


********************************************************************************************
function textview.ctrlpgdn(this)
local n,pos:=len(this:text)

    this:atxt:=array(this:height)

    if( this:text::right(1)!=bin(10) )
        pos++
    end
    this:atxt[1]:=pos

    for n:=1 to this:height-1
        if( !shift_up(this) )
            exit
        end
    next

    this:winrow:=n-1
    this:wincol:=0
    this:sftcol:=0

    this:display()


********************************************************************************************
function textview.ctrlpgup(this)
    this:setpos(1)
    this:display()


********************************************************************************************
function textview.shift_down(this)
local pos1,pos2
    pos1:=this:eolpos(this:height)
    if( pos1==NIL )
        return .f.
    end
    pos2:=at(bin(10),this:text,pos1+1)
    if( pos2==0 .and. pos1<len(this:text) )
        pos2:=len(this:text)+1
    end
    if( pos2==0 )
        return .f.
    end
    adel(this:atxt,1)
    this:atxt[this:height]:=pos2
    return .t.


********************************************************************************************
function textview.shift_up(this)
local pos
    if( (pos:=this:bolpos(1))<=1 )
        return .f.
    end
    ains(this:atxt,1)
    this:atxt[1]:=pos-1
    return .t.


********************************************************************************************
