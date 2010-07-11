
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

#define PARLST  *[1..3]
//#define PARLST  *[x..x+x]
//#define PARLST  *[3..]
//#define PARLST  *[..4]
//#define PARLST  *[..40]
//#define PARLST  *[5..4]
//#define PARLST  *[..]
//#define PARLST  a,*[2..1],b,*,c

//#define PARLST  *
//#define PARLST  a,b,c
//#define PARLST


*****************************************************************************
class base(object)
    method  proba

function base.proba(*)
    ? "base.proba    ",  .proba(*[2..])


*****************************************************************************
class derived(base)
    method  proba
    method  forw        :proba                         //rövidített írásmód
    method  forw1       {|this,*|this:proba(*[2..])}   //teljesen kiírva

function derived.proba(*)
    ? "derived.proba ", .proba(*[2..])


*****************************************************************************
function main(*)

local x:=2
local a:="a"
local b:="b"
local c:="c"
local d:=derivedNew()
local e:="env"

local blk0:={|*| {PARLST}}
local blk1:={|*| proba(PARLST)}
local blk2:={|*| d:proba(PARLST)}
local blk3:={|*| d:(derived)proba(PARLST)}
local blk4:={|*| d:(base)proba(PARLST)}
local blk5:={|*| d:(base@derived)proba(PARLST)}
local blk6:={|*| d:(super@derived)proba(PARLST)}
local blk7:={|*| d:forw(PARLST)}


    ? "array         ", {PARLST}
    ? "funcall       ", proba(PARLST)
    d:proba(PARLST)
    d:(derived)proba(PARLST)
    d:(base)proba(PARLST)
    d:(base@derived)proba(PARLST)
    d:(super@derived)proba(PARLST)
    d:forw(PARLST)
    ?

    ? "array         ", eval(blk0,*)
    ? "funcall       ", eval(blk1,*)
    eval(blk2,*)
    eval(blk3,*)
    eval(blk4,*)
    eval(blk5,*)
    eval(blk6,*)
    eval(blk7,*)
    ?
    ?


*****************************************************************************
function proba(*)
    return {*}

*****************************************************************************
