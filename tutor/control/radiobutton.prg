
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

#include "radiobutton.say"

function main()
    radiobutton({|*|load(*)},{|*|readmodal(*)},{|*|store(*)})



function load(getlist)
local group_r:={}
local group_s:={}

    g_r1:addto(group_r)
    g_r2:addto(group_r)
    g_r3:addto(group_r)

    g_s1:addto(group_s)
    g_s2:addto(group_s)
    g_s3:addto(group_s)
    g_s4:addto(group_s)

    getlist::aeval({|g|g:display})



function store(getlist)
    ? g_r1:name, g_r1:varget
    ? g_r2:name, g_r2:varget
    ? g_r3:name, g_r3:varget
    ?
    ? g_s1:name, g_s1:varget
    ? g_s2:name, g_s2:varget
    ? g_s3:name, g_s3:varget
    ? g_s4:name, g_s4:varget
    ?
    return .f. // nem lép ki
    