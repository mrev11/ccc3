
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

namespace json.lemon

******************************************************************************************
function json__object(lemon,o)
    return o


******************************************************************************************
function json__array(lemon,a)
    return a


******************************************************************************************
function object__memberlist(lemon,l)
local list:=lemon[l]
local object:=jsonobjectNew()
    object:array:=list
    lemon[l]:=object
    return l 


******************************************************************************************
function memberlist__(lemon)
    lemon::aadd({})
    return len(lemon)


******************************************************************************************
function memberlist__member(lemon,m)
local member:=lemon[m]
    lemon[m]:={lemon[m]}
    return m


******************************************************************************************
function memberlist__memberlist_member(lemon,l,m)
local list:=lemon[l]
local member:=lemon[m]
     list::aadd(member)
     lemon::asize(l)
     return l


******************************************************************************************
function member__string_value(lemon,s,v)
local name:=bin2str(s)
local value:=lemon[v]
local member:=jsonmemberNew(name,value)
    //? lemon,s,v,member
    lemon[v]:=member
    return v

******************************************************************************************
function array__valuelist(lemon,v)
    return v


******************************************************************************************
function valuelist__(lemon)
    lemon::aadd({})
    return len(lemon)

******************************************************************************************
function valuelist__value(lemon,v)
local value:=lemon[v]
    lemon[v]:={lemon[v]}
    return v


******************************************************************************************
function valuelist__valuelist_value(lemon,l,v)
local list:=lemon[l]
local value:=lemon[v]
     list::aadd(value)
     lemon::asize(l)
     return l


******************************************************************************************
function value__object(lemon,o)
    return o


******************************************************************************************
function value__array(lemon,a)
    return a


******************************************************************************************
function value__string(lemon,token)
    aadd(lemon,bin2str(token))
    return len(lemon)


******************************************************************************************
function value__number(lemon,token)
    aadd(lemon,val(token))
    return len(lemon)


******************************************************************************************
function value__true(lemon,token)
    aadd(lemon,.t.)
    return len(lemon)


******************************************************************************************
function value__false(lemon,token)
    aadd(lemon,.f.)
    return len(lemon)


******************************************************************************************
function value__null(lemon,token)
    aadd(lemon,NIL)
    return len(lemon)


******************************************************************************************
