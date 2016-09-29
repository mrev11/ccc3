
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

#define REPEAT 10000


*****************************************************************************    
function main()
local d,n,hash:=tutor.hashtableNew()

    d:=directory(getenv("CCCDIR")+dirsep()+fullmask(),"HD")
    for n:=1 to len(d)
        hash:add(d[n])
    next
    
    test1(d,d)
    test2(hash,d)
    
    return NIL

*****************************************************************************    
function test1(data,k) //lineáris keresés

local n,key,x,r,s0:=seconds()

    for r:=1 to REPEAT
        for n:=1 to len(k)
            key:=k[n][1]
            x:=ascan(data,{|i|i[1]==key})
            if( r==1 )
                ? if(x==0,NIL,data[x])
            end
        next
    next
    
    ? "test1",seconds()-s0
    ?
    return NIL


*****************************************************************************    
function test2(hash,k) //hash keresés

local n,key,x,r,s0:=seconds()

    for r:=1 to REPEAT
        for n:=1 to len(k)
            key:=k[n][1]
            x:=hash:get(key)
            if( r==1 )
                ? x
            end
        next
    next
    
    ? "test2",seconds()-s0
    ?
    return NIL

*****************************************************************************    
