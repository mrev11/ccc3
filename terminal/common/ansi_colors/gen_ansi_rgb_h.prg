
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

    set alternate to "log-ansi_rgb_h"
    set alternate on
    set console off

    ? "static char ANSI_RGB[257][3]={"

    for n:=1 to 256
        color:=ansi_colors(n)
        ? "{", color[1]::hex, ",", color[2]::hex, ",", color[3]::hex, "}, //"+str(n-1,4)
    next

    ? "{0,0,0}};"
    ? <<XXX>>

void ansi_rgb(int x, int *r, int *g, int *b)
{
    *r=ANSI_RGB[x][0];
    *g=ANSI_RGB[x][1];
    *b=ANSI_RGB[x][2];
}
<<XXX>>

******************************************************************************************
static function hex(x)
    x::=l2hex::padl(2,"0")
    return "0x"+x


******************************************************************************************
