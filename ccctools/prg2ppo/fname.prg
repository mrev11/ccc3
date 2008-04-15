
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

*****************************************************************************   
function fpath(fspec) //d:\path\ v. d:
local spos:=rat("\",fspec)
local cpos:=rat(":",fspec)
    return left(fspec,max(spos,cpos))


*****************************************************************************   
function fname(fspec) //name.ext
local spos:=rat("\",fspec)
local cpos:=rat(":",fspec)
    return substr(fspec,max(spos,cpos)+1)


*****************************************************************************   
function fbase(fspec) //name
local spos:=rat("\",fspec)
local cpos:=rat(":",fspec)
local ppos:=rat(".",fspec)
    spos:=max(spos,cpos)
    return substr(fspec,spos+1,if(ppos>spos,ppos-spos-1,NIL))


*****************************************************************************   
function fext(fspec) //.ext v. ""
local spos:=rat("\",fspec)
local ppos:=rat(".",fspec)
    return if(ppos>spos,substr(fspec,ppos),"")


*****************************************************************************   
 