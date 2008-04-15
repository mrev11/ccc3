
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

//Browse compatibilty test

#define TBROWSE  
 
// Ha TBROWSE definiált, önálló tbrowse objektum, 
//   fut: Clipper, CCC konzol
//
// Ha TBROWSE nem definiált, brwShow által megjelenített browse,
//   fut: Clipper, CCC konzol, Windows GUI, Linux GUI


#include "box.ch"
#include "inkey.ch"
#include "directry.ch"

***************************************************************************** 
function main()

local dir:=directory(getenv("CCCDIR")+"/ccclib/src/*.*","D")
local pos:=1
local b,c,k

    set printer to out
    set printer on


    #ifdef TBROWSE
        b:=tbrowseNew(6,20,20,maxcol()-20)
    #else
        b:=brwCreate(6,20,20,maxcol()-20)
    #endif

    c:=tbcolumnNew("FileName",{||dir[pos][1]})
    c:picture:="XXXXXXXXXXXX"
    c:width:=len(c:picture) //Clipper hiba!
    c:footing:="FILENAME" 
    c:colorblock:={|x|if(".prg"$x,{3,4},{1,2})}
    b:addcolumn(c)

    c:=tbcolumnNew("Size",{||dir[pos][2]})
    c:picture:="999,999"
    c:footing:="SIZE" 
    b:addcolumn(c)

    c:=tbcolumnNew("Date",{||dir[pos][3]})
    c:picture:="D"
    c:footing:="DATE" 
    b:addcolumn(c)

    c:=tbcolumnNew("Time",{||dir[pos][4]})
    c:picture:="XXXXXXXX"
    c:footing:="TIME" 
    b:addcolumn(c)

    c:=tbcolumnNew("Attr",{||dir[pos][5]})
    c:picture:="XXX"
    c:footing:="ATTR" 
    b:addcolumn(c)
 
    b:gotopblock    := {||pos:=1}
    b:gobottomblock := {||pos:=len(dir)}
    b:skipblock     := {|n,p0| p0:=pos,;
                               pos+=n,;
                               pos:=min(pos,len(dir)),;
                               pos:=max(pos,1),;
                               pos-p0}

    b:headsep       := B_HD+B_DS8+B_HD 
    b:footsep       := B_HS+B_SS2+B_HS 
    b:colsep        := " "+B_VS+" " 
    b:colorspec     := "w+/bg,w+/b,rg+/bg,rg+/r"
    
    b:freeze        := 1
  //brwFooting(b,{"Balra","Középre","Jobbra"})
    
    cls
    
    #ifndef TBROWSE
        brwShow(b)
    #endif

    while( .t. )
        
        while !b:stabilize(); end 

        k:=inkey(0) 
      
        if( k==K_ESC )
            exit
        elseif( k==K_DOWN ) 
            b:down()
        elseif( k==K_UP )
            b:up()
        elseif( k==K_PGDN )
            b:pageDown()
        elseif( k==K_PGUP )
            b:pageUp()
        elseif( k==K_CTRL_PGUP )
            b:goTop()
        elseif( k==K_CTRL_PGDN )
            b:goBottom()
        elseif( k==K_RIGHT )
            b:right()
        elseif( k==K_LEFT )
            b:left()
        elseif( k==K_HOME )
            b:home()
        elseif( k==K_END )
            b:end()
        elseif( k==K_CTRL_LEFT )
            b:panLeft()
        elseif( k==K_CTRL_RIGHT )
            b:panRight()
        elseif( k==K_CTRL_HOME )
            b:panHome()
        elseif( k==K_CTRL_END )
            b:panEnd()
        end
    end


    #ifndef TBROWSE
        brwHide(b)
    #endif
 
    return NIL
 

***************************************************************************** 








 