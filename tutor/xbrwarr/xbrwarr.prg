
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

#include "directry.ch"

function main()

local dir:=directory("*.*","D")
local brw:=brwCreate(10,10,maxrow()-2,maxcol()-10)
local smenu:={}


    setcursor(0)
    set date format to "yyyy.mm.dd"

    brwArray(brw,dir)

    brwColumn(brw,"Name",brwABlock(brw,F_NAME),"XXXXXXXXXXXXX")
    brwColumn(brw,"Size",brwABlock(brw,F_SIZE),"99999999")
    brwColumn(brw,"Date",brwABlock(brw,F_DATE))
    brwColumn(brw,"Time",brwABlock(brw,F_TIME))
    brwColumn(brw,"Attr",brwABlock(brw,F_ATTR),1)

    aadd(smenu,{"By name",{|b|sortbyname(b)}})
    aadd(smenu,{"By time",{|b|sortbytime(b)}})
    aadd(smenu,{"By size",{|b|sortbysize(b)}})
    aadd(smenu,{MENUSEP})
    aadd(smenu,{"Hopp",{||alert("öt szép szűzlány őrült írót nyúz")}})
    
    brwMenu(brw,"Sort","Sort by name/time/size",smenu)
    brwMenu(brw,"Alert","Make an alert",;
                 {||2!=alert("Are you sure?",{"Continue","Quit"})})
    
    brwMenuName(brw,"[Directory]")
    
    brwCaption(brw,"Array Browse Example")

    brwShow(brw)
    brwLoop(brw)
    brwHide(brw)
    return NIL

static function sortbyname(b)    
local a:=brwArray(b)
    asort(a,,,{|x,y| x[F_NAME]<=y[F_NAME]})
    b:refreshall()
    return NIL
    
static function sortbytime(b)    
local a:=brwArray(b)
    asort(a,,,{|x,y| dtos(x[F_DATE])+x[F_TIME]<=dtos(y[F_DATE])+y[F_TIME]})
    b:refreshall()
    return NIL

static function sortbysize(b)    
local a:=brwArray(b)
    asort(a,,,{|x,y| x[F_SIZE]<=y[F_SIZE]})
    b:refreshall()
    return NIL



