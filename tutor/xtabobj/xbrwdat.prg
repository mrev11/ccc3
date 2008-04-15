
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

#include "table.ch"
#include "_tesztdb.ch"

function main()

local brw, smenu:={}

    setcursor(0)
    set date format to "yyyy.mm.dd"
    
    
    TESZTDB:open
    TESZTDB:control:="name"
    
    brw:=TESZTDB:browse(10,10,maxrow()-2,maxcol()-10)

    brwColumn(brw,"Name",{||TESZTDB_NAME},"XXXXXXXXXXXXX")
    brwColumn(brw,"Size",{||TESZTDB_SIZE},"99999999")
    brwColumn(brw,"Date",{||TESZTDB_DATE})
    brwColumn(brw,"Time",{||TESZTDB_TIME})
    brwColumn(brw,"Attr",{||TESZTDB_ATTR},1)

    aadd(smenu,{"By name",{|b|sortbyname(b)}})
    aadd(smenu,{"By time",{|b|sortbytime(b)}})
    aadd(smenu,{"By size",{|b|sortbysize(b)}})
    
    brwMenu(brw,"Sort","Sort by name/time/size",smenu)
    brwMenu(brw,"Alert","Make an alert",;
                 {||2!=alert("Are you sure?",{"Continue","Quit"})})
    
    brwMenuName(brw,"[Directory]")
    
    brwCaption(brw,"Database Browse Example")
    brwSetFocus(brw)

    brwShow(brw)
    brwLoop(brw)
    brwHide(brw)
    return NIL

static function sortbyname(b)    
    TESZTDB:control:="name"
    b:refreshall()
    return NIL
    
static function sortbytime(b)    
    TESZTDB:control:="time"
    b:refreshall()
    return NIL

static function sortbysize(b)    
    TESZTDB:control:="size"
    b:refreshall()
    return NIL



