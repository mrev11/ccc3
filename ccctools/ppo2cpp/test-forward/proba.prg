
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

*******************************************************************************
class proba(object)
    attrib x

    method a
    method b
    method c

static function proba.a(this,p:="a")
    this:x+=p
    return this

static function proba.b(this,p:="b")
    this:x+=p
    return this

static function proba.c(this,p:="c",*)
    this:x+=p
    varstack()
    return this


*******************************************************************************
function main()

local p:=probaNew()
local blk:={|o,*|o:a:b:c(*[2..])}
local blx:={|o,x,y,z|o:a:b:c(x,y,z)}
local bl0:={|o,*|o:c(*[2..])}

    p:x:=""
    ? "blk"
    ? eval(blk,p,"X","Y","Z")

    p:x:=""
    ? "blx"
    ? eval(blx,p,"X","Y","Z")

    p:x:=""
    ? "bl0"
    ? eval(bl0,p,"X","Y","Z")

    ?

*******************************************************************************
    