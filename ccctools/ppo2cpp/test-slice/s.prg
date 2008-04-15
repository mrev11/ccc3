
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

****************************************************************************
function main()
local x:="12345678901234567890"
local i:=2,j:=8
local p


    ? x
    ? x[..] 
    ? x[..i]+x[i+1..j-1]+x[j..]
    ?
    
    
    p:=probaNew()
    p:text:="Próba szerencse"

    ? p:whole
    ? p:substr(7,8)
    ? p:tail(7)
    ? p:start(7)
    ?
    
****************************************************************************
class proba(object)
    attrib text

    method whole    {|this| this:text[..]}
    method substr   {|this,x,y| this:text[x..y]}
    method tail     {|this,x| this:text[x..]}
    method start    {|this,x| this:text[..x]}
    
****************************************************************************
    