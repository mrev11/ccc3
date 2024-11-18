
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

local i,j,k

    settermsize(40,130)

    //set alternate to log-draw
    //set alternate on

    for i:=0 to 5
        for j:=0 to 5
            for k:=0 to 5
                prn(i,j,k)
            next
        next
    next

    inkey(0)


******************************************************************************************
static function prn(r,g,b)

local clrstr
local fg,bg
local h:=3,w:=7
local x,y

    clrstr:=(r::str::alltrim+g::str::alltrim+b::str::alltrim) // color string

    x:=b*w
    y:=r*3

    x+=g*(6*w+1)%(18*w+3)   // egy sorban 3
    y+=if(g>2,19,0)         // osszesen 2 sor
    
    y+=2

    bg:=bg(r,g,b)           // ANSI color index
    fg:=fg(bg)              // "n" vagy "w"
    bg::=str(4)::alltrim    


    @ y  ,x say bg      ::padr(w) color fg+"/"+clrstr
    @ y+1,x say ""      ::padr(w) color fg+"/"+clrstr
    @ y+2,x say clrstr  ::padr(w) color fg+"/"+clrstr



******************************************************************************************
static function bg(r,g,b) // ANSI index
    return 36*r+6*g+b+16


******************************************************************************************
static function fg(bg)   // bg vilagossagatol fuggoen 0 vagy 7
local r,g,b
local intensity
    {r,g,b}:=ansi_colors(bg+1)
    intensity:=0
    intensity+=r**2
    intensity+=g**2
    intensity+=b**2
    intensity::=sqrt
    return if(intensity>220,"n","w")


******************************************************************************************
