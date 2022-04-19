
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

static remark:=<<REMARK>>
    megszamlalja a kulonfele xml tagok elofordulasat

<<REMARK>>

static counter:={}


****************************************************************************
function main(fname:="example.xml")
local n,p

    ? remark

    p:=xmlparser2New(fname)
    p:contentblock:={|*|content(*)}
    p:parse  
   
    for n:=1 to len(counter)
        ? padr(counter[n][1],20), counter[n][2]
    next
    ? 

****************************************************************************
static function content(parser,node)
local n
    if( 0<(n:=ascan(counter,{|c|c[1]==node:type})) )
        counter[n][2]++
    else
        aadd(counter,{node:type,1})
    end
    return .f. //nem kell az objektumfa

****************************************************************************
 