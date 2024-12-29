
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

static pattern:=""


***************************************************************************************
static function FFILE(bLoad,bRead,bStore)

local fspec:=space(26)
local msk:=mskCreate(5,2,5,40,bLoad,bRead,bStore)

    mskGet(msk,0,0,@fspec,"fspec")

    mskShow(msk)
    mskLoop(msk)
    mskHide(msk)

//Eredetileg mask-kal keszult dialog:
//az msk fajlok CCC2/CCC3-ban elternek,
//raadasul binarisak, nem jo bajlodni veluk,
//ezert az eredmeny say-t atirtam.
//Az eredeti msk fajl nincs megorizve.

#define g_fspec         getlist[ 1]



***************************************************************************************
function find_file(brw)
    FFILE({|gl|load(gl)},{|gl|readmodal(gl)},{|gl|store(gl,brw)} )


***************************************************************************************
static function load(getlist)

local wid:=g_fspec:varget::len //berajzolt meret
local fun:="@KS"+wid::str::alltrim
local pic:=fun+" "+replicate("X",256)

    g_fspec:picture:=pic
    g_fspec:varput(pattern)


***************************************************************************************
static function store(getlist,brw)

local arr:=brwArray(brw),n
local pos:=brwArrayPos(brw)

    pattern:=g_fspec:varget::alltrim
    
    for n:=pos+1 to len(arr)
        if( pattern $ arr[n][1] )
            //lehetne like
            //lehetne regex
            brwArrayPos(brw,n)
            brw:refreshall
            exit
        end
    next

    return .t.


***************************************************************************************
