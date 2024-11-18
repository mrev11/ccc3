
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

// Legegyszerubb elvi implementacio + indexek.
// Rendezettseg elleni vedelem: veletlen pivot valasztassal.
// Egyenlo elemek eseten a rendezeskor figyelembe veszi az
// elem indexet, tehat valojaban nincsenek egyenlo elemek.

#include "qsort.ch"


****************************************************************************
function qsort_2x(*)
    ?? "qsort_2x"::padr(16)
    qsort(*)


****************************************************************************
static function qsort(a,p:=1,r:=len(a),blk,index)

// a    : array to sort
// p    : start index
// r    : final index
// blk  : compare block

local q

    if( index==NIL )
        index:=array(r-p+1)
        for q:=p to r
            index[q]:=q
        next
    end

    while( p+ISORT_TRESHOLD<r )
        q:=qsplit(a,p,r,blk,index)
        if( r-q>q-p  )
            qsort(a,p,q-1,blk,index)
            p:=q+1
        else
            qsort(a,q+1,r,blk,index)
            r:=q-1
        end
    end

    if( p<r )
        isort(a,p,r,blk)
    end


****************************************************************************
static function qsplit(a,p,r,blk,index)

local x,pivot
local i,q,cmp

    pivot:=a[x:=pivot_index(a,p,r,blk)]
    swap(a,x,r,index)

    q:=p-1
    for i:=p to r-1
        cmp:=compare(a[i],pivot,blk)
        if( cmp==0 )
            // egyenlo elemek eseten index szerint rendez
            // (tehat valojaban nincsenek egyenlo elemek)
            cmp:=i-x
        end
        if( cmp<0 )
            q++
            swap(a,i,q,index)
        end
    next
    q++

    swap(a,q,r,index)
    return q


****************************************************************************
static function swap(a,x,y,index) //specialis swap
local tmp

    tmp:=a[x]
    a[x]:=a[y]
    a[y]:=tmp

    tmp:=index[x]
    index[x]:=index[y]
    index[y]:=tmp
    
// Ha az index tombot is swapoljuk, akkor 
// az egyenlo elemek megtartjak a sorrendjuket.
// Ha nem swapoljuk, akkor az egyenlo elemek 
// keverednek,  de a stack overflow kivedesehez 
// ez is eleg (es nem is kell az index tomb).


****************************************************************************
