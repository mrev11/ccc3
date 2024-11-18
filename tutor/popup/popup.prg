
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

#include "box.ch"

#define PRINT(x)    ? #x, x


function main()

local menu:={},n
local popup,popup1,popup2
local top,lef,bot,rig
local result

    scale()

    popup1:=popupmenuNew()
    popup1:title:="Submenu-A"
    popup1:menu::aadd( {"1 AA"                  , {|*|alert(*)}} )
    popup1:menu::aadd( {"2 AAAA"                , {|*|alert(*)}} )
    popup1:menu::aadd( {"3 AAAAAA"              , {|*|alert(*)}} )
    popup1:menu::aadd( {"4 AAAAAAAA"            , {|*|alert(*)}} )
    popup1:menu::aadd( {"5 AAAAAAAAAA"          , {|*|alert(*)}} )
    popup1:menu::aadd( {"6 AAAAAAAAAAAA"        , {|*|alert(*)}} )
    popup1:menu::aadd( {"7 AAAAAAAAAAAAAA"      , {|*|alert(*)}} )
    popup1:menu::aadd( {"8 AAAAAAAAAAAAAAAA"    , {|*|alert(*)}} )
    popup1:color:="n/454,w+/110"


    popup2:=popupmenuNew()
    popup2:title:="Submenu-B"
    popup2:menu::aadd("1 BB")
    popup2:menu::aadd("2 BBBB")
    popup2:menu::aadd("3 BBBBBB")
    popup2:menu::aadd("4 BBBBBBBB")
    popup2:menu::aadd("5 BBBBBBBBBB")
    popup2:menu::aadd("6 BBBBBBBBBBBB")
    popup2:menu::aadd("7 BBBBBBBBBBBBBB")
    popup2:menu::aadd("8 BBBBBBBBBBBBBBBB")
    popup2:menu[1]:=popup1
    popup2:menu[2]:=popup1
    popup2:menu[3]:=popup1
    popup2:color:="n/454,w+/020"

    top:=30
    lef:=50
    //bot:=40            
    //rig:=100           

    //PRINT(maxrow())
    //PRINT(maxcol())
    //PRINT(top)
    //PRINT(lef)
    //PRINT(bot)
    //PRINT(rig)

    for n:=1 to 20
        menu::aadd(n::str::alltrim+" "+replicate("X",2*n))
    next
    //menu::aadd(n::str::alltrim+" "+replicate("xxxxxxxxx!",10)+"*")

    menu[11]:=popup1
    menu[12]:=popup2

    setpos(0,0)
    
    popup:=popupmenuNew(menu,top,lef,bot,rig)

    popup:border:=B_SINGLE_DOUBLE
    popup:color:="n/454,w+/200"
    popup:upper:=7
    popup:choice:=10
    result:=popup:loop
    
    ? result, popup:choice, popup:upper, popup:text
    ?


    inkey(0)
