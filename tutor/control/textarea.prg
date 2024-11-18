
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

#include "textarea.say"

*************************************************************************************************
function main()
    textarea({|g|load(g)}, {|g|readmodal(g)}, {|g|store(g)},50,50)
    ?

*************************************************************************************************
static function load(getlist)

    g_get1:varput:="Egyszer hopp"
    g_get2:varput:="Máskor kopp"

    g_area:varput:=memoread("textarea.prg")
    //g_area:modflag:=.f.

    g_mehet:execblock:={||NIL}  // GE_ESCAPE -> store()

    getlist::aeval({|g|g:display})


*************************************************************************************************
static function store(getlist)
local n
    for n:=1 to len(getlist)
        ? getlist[n]:name, getlist[n]:varget
    next
    return .t.


*************************************************************************************************
