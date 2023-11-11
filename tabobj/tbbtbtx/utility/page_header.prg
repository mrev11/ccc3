
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
function page_header(page)

local version
local nords
local offset
local n

    ?
    ? "magic    :", page[ 1.. 4]::bin2hex 
    ? "diskord  :", dskord()
    ? "swap     :", if(swap(),"TRUE","FALSE")
    ? "version  :", page[ 5.. 8]::hex
    ?
    ? "pagesize :", page[ 9..12]::num , page[ 9..12]::hex
    ? "nrecords :", page[13..16]::num , page[13..16]::hex
    ? "freelist :", page[17..20]::num , page[17..20]::hex
    ? "lastdata :", page[21..24]::num , page[21..24]::hex
    ? "freememo :", page[25..28]::num , page[25..28]::hex
    ? "norders  :", page[29..32]::num , page[29..32]::hex
    ?

    version:=page[ 5.. 8]::num
    nords:=page[29..32]::num

    for n:=1 to nords
        if( version<=2 )
            offset:=32*n
        else
            offset:=16+32*n
        end
        ? page[offset+17..offset+32]::strtran(bin(0),bin(32)),;
         "root="+page[offset+1..offset+4]::hex,;
         "last="+page[offset+5..offset+8]::hex,;
         "free="+page[offset+9..offset+12]::hex
    next


******************************************************************************************
