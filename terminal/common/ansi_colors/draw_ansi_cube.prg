
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

local i,j,k,x

    ?? chr(27)+"[8;56;130t"  // resize term window to 56x130

    for x:=1 to 3
        for i:=0 to 15
            prnx(i,x)
            if( i==7 )
                ?? chr(27)+"[m "
            end
        next
        ?? chr(27)+"[m";?
    next


    for i:=0 to 5
        for x:=1 to 3
            ?
            for j:=0 to 2
                for k:=0 to 5
                    prn(i,j,k,x)
                next
                ?? chr(27)+"[m "
            next
        next
    next
    ?? chr(27)+"[m";?


    for i:=0 to 5
        for x:=1 to 3
            ?
            for j:=3 to 5
                for k:=0 to 5
                    prn(i,j,k,x)
                next
                ?? chr(27)+"[m "
            next
        next
    next
    ?? chr(27)+"[m";?
    ?


    for x:=1 to 3
        for i:=232 to 237
            prnx(i,x)
        next
        ?? chr(27)+"[m"
        ?
    next

    for x:=1 to 3
        for i:=238 to 243
            prnx(i,x)
        next
        ?? chr(27)+"[m"
        ?
    next
        
    for x:=1 to 3
        for i:=244 to 249
            prnx(i,x)
        next
        ?? chr(27)+"[m"
        ?
    next
        
    for x:=1 to 3
        for i:=250 to 255
            prnx(i,x)
        next
        ?? chr(27)+"[m"
        ?
    next

    inkey(0)


******************************************************************************************
static function prnx(bg,x)
local fg
    fg:=fg(bg)
    bg::=str(4)::alltrim
    fg::=str(4)::alltrim
    if( x==1 )
        x:=bg
    elseif( x==3 )
        x:=rgb(bg)
    else
        x:=""
    end
    ?? chr(27)+"[38;5;"+fg+"m"+chr(27)+"[48;5;"+bg+"m"+x::padr(7)


******************************************************************************************
static function prn(i,j,k,x)
local fg,bg,gr
    bg:=bg(i,j,k)
    fg:=fg(bg)
    gr:=gr(bg)
    bg::=str(4)::alltrim
    fg::=str(4)::alltrim
    if( x==1 )
        x:=bg+if(gr,"*","")
    elseif( x==3 )
        x:=rgb(bg)
    else
        x:=""
    end
    ?? chr(27)+"[38;5;"+fg+"m"+chr(27)+"[48;5;"+bg+"m"+x::padr(7)


******************************************************************************************
static function bg(i,j,k)
    return 36*i+6*j+k+16


******************************************************************************************
static function fg(bg)
local r,g,b,intensity
    bg:=if(bg::valtype=="N",bg,val(bg))
    {r,g,b}:=ansi_colors(bg+1)
    intensity:=0
    intensity+=r**2
    intensity+=g**2
    intensity+=b**2
    intensity::=sqrt
    return if(intensity>255,0,7)


******************************************************************************************
static function gr(bg)
local rgb
    bg:=if(bg::valtype=="N",bg,val(bg))
    rgb:=ansi_colors(bg+1)
    return rgb[1]==rgb[2] .and. rgb[1]==rgb[3]


******************************************************************************************
static function rgb(x)
local r,g,b
    x:=if(x::valtype=="N",x,val(x))+1
    r:=ansi_colors(x)[1]
    g:=ansi_colors(x)[2]
    b:=ansi_colors(x)[3]
    return r::l2hex::padl(2,"0")+g::l2hex::padl(2,"0")+b::l2hex::padl(2,"0")


******************************************************************************************
