
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
function page_memo(page)

local type:="MEMO"
local lower,upper,offset
local recmix,recno,memix
local poslen,pos,len
local pgnext,ixnext
local memseg

    ? "type  ",  type

    ? "link  ", "0x"+page[ 5.. 8]::hex
    ? "lower ", "0x"+page[ 9..12]::hex
    ? "upper ", "0x"+page[13..16]::hex

    lower:=page::substr(9,4)::num    // elso szabad pozicio
    upper:=page::substr(13,4)::num   // elso nemszabad pozicio
    ? "items", (lower-16)/16         // ennyi rekord van benne
    ? "space", upper-lower

    offset:=16
    while( offset<lower )
        recmix :=page::substr(offset+ 1,4)::num // MEMO_ID
        poslen :=page::substr(offset+ 5,4)::num // MEMO_DESC
        pgnext :=page::substr(offset+ 9,4)::num // MEMO_PGNEXT
        ixnext :=page::substr(offset+13,4)::num // MEMO_IXNEXT

        {recno,memix}:=parse_recmix(recmix)
        {pos,len}:=parse_poslen(poslen)
        memseg:=page::substr(pos+1,len)

        ? (offset/16-1)::str(3),;
          form_recmix(recno,memix,15),;
          len::transform(" 99999"),;
          form_memseg(memseg,64)

        if( pgnext!=0 )
            ?? " -> "+form_mempos(pgnext,ixnext)
        end

        offset+=16
    end


******************************************************************************************
