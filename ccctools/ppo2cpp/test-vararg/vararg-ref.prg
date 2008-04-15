
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

******************************************************************************
function main()

local a:="a"
local b:="b"
local c:="c"

    ? "vararg-ref"

    fun1(a,@b,c)
    ? a,b,c
    ?


******************************************************************************
function fun1(*)
local o:=xxNew()
local a:={*}
    ? {*},a
    o:test(*)
    ? {*},a

******************************************************************************
class xx(object)
    method test

static function xx.test(this,*)
    fun2(*)

static function fun2(this,a,b,c)
    varstack()
    ? this,a,b,c
    a:="A"
    b:="B"
    c:="C"

******************************************************************************

