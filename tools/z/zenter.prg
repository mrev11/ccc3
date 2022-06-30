
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
function _zedit_enter(this)

local line, n

    line:=substr(this:atxt[this:actrow],this:actcol)  //ez lesz az uj sor
    this:atxt[this:actrow]:=left(this:atxt[this:actrow],this:actcol-1) //ez marad a regi sor
    if( this:indent )
        n:=len(this:atxt[this:actrow])-len(ltrim(this:atxt[this:actrow])) //indentalashoz
    else
        n:=0
    end

    aadd(this:atxt,NIL)
    ains(this:atxt,this:actrow+1)
    this:atxt[this:actrow+1]:=space(n)+line
    this:sftcol:=0
    this:wincol:=n
    if( this:wincol>this:width-1 )
        this:sftcol:=this:wincol-this:width+1
        this:wincol:=this:width-1
    end

    if( this:winrow<this:height-1 )
        this:winrow:=this:winrow+1
    else
        this:sftrow:=this:sftrow+1
    end

    this:display()

    return NIL

*****************************************************************************
