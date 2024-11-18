
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

    setcursor(0)

    color( 0, 0,"000,111,222,333,444,555")

    color( 0,10,"000,100,200,300,400,500")
    color( 0,20,"000,010,020,030,040,050")
    color( 0,30,"000,001,002,003,004,005")

    color( 0,40,"000,110,220,330,440,550")
    color( 0,50,"000,101,202,303,404,505")
    color( 0,60,"000,011,022,033,044,055")



    color( 14, 0,"w,w+")      // 7
    color( 14,10,"r,r+")      // 1
    color( 14,20,"g,g+")      // 2
    color( 14,30,"b,b+")      // 4
    color( 14,40,"rg,rg+")    // 3
    color( 14,50,"rb,rb+")    // 5
    color( 14,60,"gb,gb+")    // 6
    color( 14,70,"n,n+")      // 0


    inkey(0)

******************************************************************************************
static function color(r,c,bg, fg:="n", br:="")
local i,color
    bg::=split(",")
    for i:=1 to len(bg)
        color:=fg+"/"+bg[i]+br
        @ r+2*i  ,c say color::padr(10) color (color)
        @ r+2*i+1,c say ""   ::padr(10) color (color)
    next


******************************************************************************************

