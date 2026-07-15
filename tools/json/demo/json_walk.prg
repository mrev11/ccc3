
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

// demó:  így lehet kiszedni az adatokat egy json objektumból

******************************************************************************************
function main(jsonfile:="credit_transfer_json")

local json:=json_parser(memoread(jsonfile))
local root:="cstmrCdtTrf"

local blkleaf:={|p,v|cbleaf(p,v)}
local blkelem:={|p,v|cbelem(p,v)}
local blkmemb//:={|p,v|cbmemb(p,v)}

    json_walk(json,root,blkleaf,blkelem,blkmemb)
    ?


******************************************************************************************
static function cbleaf(path,value)
    ? "VAL", path, "-->", value

static function cbelem(path,element)
    ? "e  ", path, "-->", element::oref

static function cbmemb(path,member)
    ? "m  ", path, "-->", member:name


******************************************************************************************
