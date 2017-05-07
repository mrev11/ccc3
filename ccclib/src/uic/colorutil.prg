
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

************************************************************************
function LogColor(color,cnum) // color-ból a cnum-edik logikai szín    
local col:=split(color)
    return if(len(col)>=cnum,col[cnum],NIL)


************************************************************************
function revcolor()
// Megfordítja az aktuális color első két 
// színét, és visszaadja a régi beállítást.
local color:=setcolor()
local clist:=split(color)
local fgbg
    if( len(clist)<1 )
        aadd(clist,"w/n")
    end
    if( len(clist)<2 )
        fgbg:=clist[1]::split("/")
        aadd(clist,fgbg[2]+"/"+fgbg[1])
    end
    setcolor(clist[2]+","+clist[1])
    return color


************************************************************************
 