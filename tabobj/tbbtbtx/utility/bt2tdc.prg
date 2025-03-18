
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

#include "table.ch"


function main(btfile)

local tab
local path,name
local index,column,col
local i,n
local keep

    if( btfile::right(3)!=".bt" )
        btfile+=".bt"
    end
    tab:=tabResource(btfile)
    path:=tabPath(tab)
    name:=tabFile(tab)
    index:=tabIndex(tab)
    column:=tabColumn(tab)
    keep:=tabKeepDeleted(tab)

    set printer to "_"+name::lower+".tdc"
    set printer on
    set console off

    ?? "!table "+name
    if( !empty(path) )
        ? "!path ",path::left(len(path)-1)
    end

    for i:=1 to len(index)
        ? "!index",index[i][1]::upper,index[i][2]
        for n:=1 to len(index[i][3])
            col:=column[index[i][3][n]]
            ?? "",col[1]
        next
    next

    for n:=1 to len(column)
        ? "!field", column[n][1]::padr(12),  ; // name
                    column[n][2],            ; // type
                    column[n][3]::str(3),    ; // width
                    column[n][4]::str(2)       // decimal
    next

    if( keep!=NIL )
        // tabResource csak annyit tud
        // hogy letezik a deleted index
        // keep ertekenek 1-et allit be
        ? "!keepdeleted",str(keep,3)
    end

    ?


