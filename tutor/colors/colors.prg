
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
function main()

local n,color
local r0,r1,r,c

    setcursor(0)
    cls

    // base colors

    for n:=0 to 15
        @ 1,4*n say "    " color color(n)
        @ 2,4*n say "    " color color(n)
    next

    // 6x6x6 color cube

    r0:=4
    r1:=0
    r:=0
    c:=0
    for n:=16 to 231
        @ r0+r1+r+0, 4*c say "    " color color(n)
        @ r0+r1+r+1, 4*c say "    " color color(n)
        c++
        if( c==18 )
            c:=0
            r++
            r1:=12*(r%2)
        end
    next

    // grey scale

    r0:=30
    r:=0
    c:=0
    for n:=232 to 255
        @ r0+r+0, 4*c say "    " color color(n)
        @ r0+r+1, 4*c say "    " color color(n)
        c++
        if( c==6 )
            c:=0
            r+=2
        end
    next

    inkey(0)



******************************************************************************************
static function color(n)
    return "w/#"+n::str::alltrim

******************************************************************************************

