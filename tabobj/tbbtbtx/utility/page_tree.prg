
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


******************************************************************************************
function page_tree(page)

local type:="TREE"
local lower,upper
local idx,offset
local pos,len,pgn,key,rec


    ? "type  ",  type

    ? "link  ", "0x"+page[ 5.. 8]::hex
    ? "prev  ", "0x"+page[ 9..12]::hex
    ? "next  ", "0x"+page[13..16]::hex
    ? "flags ", "0x"+page[17..20]::hex
    ? "lower ", "0x"+page[21..22]::hex
    ? "upper ", "0x"+page[23..24]::hex

    lower:=page::substr(21,2)::num                  // elso szabad pozicio
    upper:=page::substr(23,2)::num                  // elso nemszabad pozicio
    ? "items", (lower-24)/2                         // ennyi rekord van benne
    ? "space", upper-lower

    idx:=0
    offset:=24
    while( offset<lower )
        pos:=page::substr(offset+1,2)::num          // record offset on page
        len:=page::substr(pos+1,4)::num             // key length
        pgn:=page::substr(pos+5,4)::hex::padl(8)    // page number
        key:=page::substr(pos+9,len)                // key
        pos::=l2hex::padr(4)
        if( len==0  )
            len::=str::alltrim::padl(4)
            ? str(idx,3),"0x"+pos, len, pgn
        else
            len::=str::alltrim::padl(4)
            ? str(idx,3),"0x"+pos, len, pgn, key::key2str
        end
        idx++
        offset+=2
    end


******************************************************************************************
