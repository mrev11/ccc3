
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
    if( len(col)>=cnum )
        return col[cnum]
    end
    if( len(col)==1 .and. cnum==2 )
        tmp:=col[1]::split("/")
        return tmp[2]+"/"+tmp[1]
    end
    return col[1]


************************************************************************
function revcolor()

// Megfordítja az aktuális color első két 
// színét, és visszaadja a régi beállítást.

local col:=setcolor()::split
local tmp,n
    if( len(col)==1 )
        col::aadd(setcolor()::logcolor(2))
    end
    tmp:=col[1]
    col[1]:=col[2]
    col[2]:=tmp
    tmp:=col[1]
    for n:=2 to len(col)
        tmp+=","+col[n]
    next
    return setcolor(tmp)


************************************************************************
 