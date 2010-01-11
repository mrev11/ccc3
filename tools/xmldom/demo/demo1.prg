
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

//megszámlálja a különféle xml tagok előfordulását

static counter:={}

****************************************************************************
function main(fname)
local n, msg, p:=xmlparserNew(fname) 

    p:processblock:={|node|feldolgozo(node,msg)}
    msg:=message(msg,"Feldolgozás indul")
    p:parse  
    msg:=message(msg)
    
    for n:=1 to len(counter)
        ? padr(counter[n][1],20), counter[n][2]
    next

    ? //"maximális stack méret:", yaccmaxidx() 
    return NIL

****************************************************************************
static function feldolgozo(node,msg)

static k:=0
local n

    if( node:type=="kivonat" )
        message(msg,"Feldolgozva"+str(++k) )
    end
    
    if( 0<(n:=ascan(counter,{|c|c[1]==node:type})) )
        counter[n][2]++
    else
        aadd(counter,{node:type,1})
    end
    
    return .t. //nem kell az objektumfa

****************************************************************************
 