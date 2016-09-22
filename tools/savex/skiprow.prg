
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

#include "savex.ch"


******************************************************************************    
function skiprow(brw)
local arr:=brwArray(brw)
local pos:=brwArrayPos(brw)
local n,a,x,t
    if( len(arr)>1 )
        adel(arr,pos)
        asize(arr,len(arr)-1)
    else
        //utolso sor empty-re allitva
        a:=arr[1]
        for n:=1 to len(a)
            x:=a[n]
            t:=valtype(x)
            if( t=="C")
                x:=""
            elseif( t=="D" )
                x:=ctod("")
            elseif( t=="N" )
                x:=0
            end
            a[n]:=x
        next
    end
    brwArrayPos(brw,min(pos,len(arr)))
    brw:refreshAll()
    return .t.

******************************************************************************    
