
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

function main()

local blk0:={|a,b,c|fun(a,b,c),{a,b}}
local blk1:={|*|fun(*)}   // optimaliz?lt
local blk2:={|*|fun(*),{*}} 
local blk3:={|a,b,*|fun(*),{a,b}}
local p

    ? "blk0";p:="2"
    ?? eval(blk0,"1")
    ?? eval(blk0,"1",@p,"3")
    ?? eval(blk0,"1",@p,"3","4","5")
    ? "p =",p
    ?
    ? "blk1";p:="2"
    ?? eval(blk1,"1")
    ?? eval(blk1,"1",@p,"3")
    ?? eval(blk1,"1",@p,"3","4","5")
    ? "p =",p
    ?
    ? "blk2";p:="2"
    ?? eval(blk2,"1")
    ?? eval(blk2,"1",@p,"3")
    ?? eval(blk2,"1",@p,"3","4","5")
    ? "p =",p
    ?
    ? "blk3";p:="2"
    ?? eval(blk3,"1")
    ?? eval(blk3,"1",@p,"3")
    ?? eval(blk3,"1",@p,"3","4","5")
    ? "p =",p
    ?

function fun(a,b,*)
    if( valtype(a)=="C" )
        a+="x"
    end
    if( valtype(b)=="C" )
        b+="x"
    end
    ? {*}
    return "fun"



