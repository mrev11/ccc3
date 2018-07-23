
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

//quicksort algoritmus

****************************************************************************
function main()

local a:=array(1000),n

    for n:=1 to len(a)
        a[n]:=random()
    next

    qsort(a) //növekvő

    set printer to log-sorted
    set printer on
    set console off

    for n:=1 to len(a)
        ? a[n]
    next
    ?
    
****************************************************************************
function qsort(a,p:=1,r:=len(a),blk:={|x,y|x<y})
local q
    if( p<r )
        q:=qsplit(a,p,r,blk)
        qsort(a,p,q-1,blk)
        qsort(a,q+1,r,blk)
    end

****************************************************************************
static function qsplit(a,p,r,blk)

local i:=p-1,j,k,x,tmp

    x:=a[r]  //őrszem

    for j:=p to r-1
        if( blk::eval(a[j],x) )
            i++
            tmp:=a[i]
            a[i]:=a[j]
            a[j]:=tmp
        end

        // tfh <=-re rendezünk, akkor        
        // p<=n<=i esetén a[n]<=x (esetleg üres halmaz)
        // i< n<=j esetén a[n]> x (esetleg üres halmaz)
    next

    i++
    tmp:=a[i]
    a[i]:=a[r]
    a[r]:=tmp
    
    // p<=i<=r
    // n<i esetén  a[n]<=a[i]
    // n>i esetén  a[n]> a[i]

    return i

****************************************************************************
