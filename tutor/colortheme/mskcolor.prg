
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

#include "color.say"



********************************************************************************
function editmask()
local bload:={|*|load(*)}
local bread:={|*|readmodal(*)}
local bstore:={||.t.}
local msk:=mskCOLORcreate(bLoad,bRead,bStore)
    mskReplace(msk,col()+1,row()+1)
    mskLoop(msk)
    return lastkey()


********************************************************************************
static function load(getlist)
    g_push:varput("<EztNyomdMeg>")
    g_push:execblock:= {||editmask(),.t.}
    // ha az execblock empty-t ad vissza, akkor a maszk kilép


    g_get1:varput("Holnap lesz fácán.")
    g_get2:varput("Vanaki forrón szereti.") ;g_get2:bright:=.t.
    g_get3:varput("Meggyvágó.")             ;g_get3::get.behave_as_label
    g_get4:varput("Fenyőpinty.")            ;g_get4:bright:=.t.; g_get4::get.behave_as_label

    g_lab1:varput("Rozsdafarkú")
    g_lab2:varput("Próba szerencse")        ;g_lab2:bright:=.t.

    getlist::aeval({|g|g:display})


********************************************************************************






