
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
local col:=color::split
local tmp
    if( empty(col) )
        col:={"w/n"}
    end

    if( len(col)>=cnum .and. !empty(col[cnum]) )
        // ha meg van adva
        tmp:=col[cnum]
 
    elseif( cnum==2 )
        // ha col[2] nincs megadva,
        // akkor veszi col[1] inverzet
        tmp:=col[1]::split("/")
        tmp:=tmp[2]+"/"+tmp[1]

    else
        tmp:=col[1]
    end

    return tmp

************************************************************************
function revcolor()

// Megfordítja az aktuális color első két 
// színét, és visszaadja a régi beállítást.

local col:=setcolor()::split
local tmp,n
    if( len(col)<2 )
        asize(col,2)
    end

    col[1]:=setcolor()::logcolor(2)
    col[2]:=setcolor()::logcolor(1)
    tmp:=col[1]
    for n:=2 to len(col)
        tmp+=","+col[n]
    next
    return setcolor(tmp)


************************************************************************
 