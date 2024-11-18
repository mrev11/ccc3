
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
function ReadMask(filnam)
local x:=memoread(filnam,.t.)
    if( empty(x) )
        ? "ERROR file not found:",filnam
        ?
        quit
    end
    return compat(x)


******************************************************************************************
static function compat(x) // regi msk-k konvertalasa
local n,ch,at,fg,bg

    n:=len(x)
    x::=left(n-(n%4)) // leszedi az esetleges EOF-ot

    ch:=screenchar(x)
    at:=screen_fg(x)  // eredeti fg-k  
    fg:=a""
    bg:=a""

    for n:=1 to len(at)
        if( asc(at[n])==7 )
            // normal
            fg+=bin(7) // w
            bg+=bin(0) // n
        else
            // inverse
            fg+=bin(0) // n
            bg+=bin(7) // w
        end
    next

    return screencompose(ch,fg,bg)


******************************************************************************************
