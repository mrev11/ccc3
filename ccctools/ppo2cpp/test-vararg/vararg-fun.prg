
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

function main(a,*)
    ? a,{*}  //az els? param?ter + az ?sszes egy arrayben.
    test(*)  //?tadja az ?sszes param?tert (a-t is).
    ?

function test(*)
    //varstack()

    test1(*)    // sok param?ter
    test1("X")  // kev?s param?ter
    test2(*)    // sok param?ter
    test2("X")  // kev?s param?ter
    test3(*)    // sok param?ter
    test3("X")  // kev?s param?ter
    ?
    test4(*)
    ?
    test4("X")  // kev?s param?ter
    ?
    test5(*)
    ?
    test5("X")  // kev?s param?ter
    ?
    test6(*)  
    test6("X")  // kev?s param?ter
    ?

******************************************************************************
function test1(a,b,c)
local x:="test1"
    ? x, len({*}),  '<mindig 3'

function test2(*)
local x:="test2"
    ? x, len({*}),  '<amennyit t?nylegesen megadtak'

function test3(a,b,*)
local x:="test3"
    ? x, len({*}),  '<amennyit t?nylegesen megadtak, de legal?bb 2'


******************************************************************************
function test4(a,b,*) //helyettes?t?sek

local x:="test4"
local o:=xxNew()
local e

    ? x,a,b, '<n?v szerint is ismert param?terek'

    begin
        ? {*}[1], '<egy elem el?v?tele'
        ? {*}[10], '<t?lny?lt, ez nem ?r?dik ki'
    recover e
        ? e, '<elsz?ll, ha t?lny?l'
    end

    ? {x,*,,*}, '<helyettes?t?s arrayben'
    ? getargs("1",*,"2",*), '<helyettes?t?s f?ggv?nyh?v?sban'
    ? o:initialize(*), '<helyettes?t?s met?dush?v?sban'


******************************************************************************
function test5(x,y,*) //helyettes?t?sek blokkban
local o
local a
local blk1:={|p1,p2,p3,p4|a:={*,*}} //itt * p1,p2,p3,p4-et jelenti
local blk2:={|p1,p2,p3,p4|getargs(*,,*)} //itt * p1,p2,p3,p4-et jelenti
local blk3:={|p1,p2,p3,p4|o:=xxNew(*)} //itt * p1,p2,p3,p4-et jelenti
local blk4:={|p1,p2,p3,p4|o:=xxNew(),o:initialize(*)} //itt * p1,p2,p3,p4-et jelenti

    ? eval(blk1,"test5/1",*), "<blokkargumentumok helyettes?tve arraybe"
    ? eval(blk2,"test5/2",*), "<blokkargumentumok helyettes?tve f?ggv?nyh?v?sba"
    ? eval(blk3,"test5/3",*), "<blokkargumentumok helyettes?tve f?ggv?nyh?v?sba"
    ? eval(blk4,"test5/4",*), "<blokkargumentumok helyettes?tve met?dush?v?sba"
    
    //varstack()

******************************************************************************
function test6(*)
local x:="test6"
    ? getargs(x,getargs(*),*), '<csillagok elt?r? szinten'
    ? {x,{*},*}, '<csillagok elt?r? szinten'

******************************************************************************
function getargs(*)
    return {*}

******************************************************************************
class xx(object)
    attrib a1
    attrib a2
    attrib a3
    attrib a4
    method initialize

static function xx.initialize(this,a1,a2,a3,a4)
    this:a1:=a1
    this:a2:=a2
    this:a3:=a3
    this:a4:=a4
    return this

******************************************************************************
