
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
function atail(arr)
local x:=len(arr)
    return if(x<=0,NIL,arr[x])

****************************************************************************
function ascan(arr,blk,st,cn)
local at:=0, i 

    if( st==NIL )
        st:=1
    end

    if( cn==NIL )
        cn:=len(arr)
    end
   
    cn:=min(cn,len(arr)-st+1)
    
    if( valtype(blk)=="B" )

        for i:=st to st+cn-1
            if( eval(blk,arr[i]) )
                at:=i
                exit
            end
        next

    else

        for i:=st to st+cn-1

            //1999.05.11 
            //ascan defaultja az '=' operátorral történő összehasonlítás,
            //CCC-ben azonban '=' operátor nincs, helyette: !(...!=...)
            //FONTOS: blk van a jobb oldalon

            if( !(arr[i]!=blk) )  
                at:=i
                exit
            end
        next
    end

    return at


****************************************************************************
function aeval(arr,blk,st,cn)
local i 

    if( st==NIL )
        st:=1
    end

    if( cn==NIL )
        cn:=len(arr)
    end

    cn:=min(cn,len(arr)-st+1)
    
    for i:=st to st+cn-1
        eval(blk,arr[i]) 
    next

    return arr


****************************************************************************
function afill(arr,x,st,cn)
local i 

    if( st==NIL )
        st:=1
    end

    if( cn==NIL )
        cn:=len(arr)
    end

    cn:=min(cn,len(arr)-st+1)
   
    for i:=st to st+cn-1
        arr[i]:=x
    next

    return arr


****************************************************************************
function acopy(aSrc,aTrg,stSrc,cn,stTrg)
local i 

    if( stSrc==NIL )
        stSrc:=1
    end

    if( stTrg==NIL )
        stTrg:=1
    end

    if( cn==NIL )
        cn:=len(aSrc)
    end
    
    cn:=min(cn,len(aSrc)-stSrc+1)
    cn:=min(cn,len(aTrg)-stTrg+1)

    for i:=0 to cn-1
        aTrg[stTrg+i]:=aSrc[stSrc+i]
    next

    return aTrg


****************************************************************************
function _asort_ascendblock() // asort default blockja
    return {|x,y|x<y}


****************************************************************************

