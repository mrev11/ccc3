
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

//optimalizált quicksort algoritmus
//tapasztalat szerint nem gyorsabb az elvi implementációnál,
//viszont mindenképpen előny, hogy nincs benne rekurzió

****************************************************************************
function main(arg)

local a:=array(5000),n

    set printer to qsort
    set printer on
    set console off

    for n:=1 to len(a)
        a[n]:=random()
    next

    if( arg=="q" )
        qsort(a,,,{|x,y|x>=y})  //csökkenő
    end
    
    if( arg=="x" )
        xqsort(a,,,{|x,y|x>=y})  //csökkenő
    end

    if( arg=="i" )
        isort(a,1,len(a),{|x,y|x>=y}) //csökkenő
    end

    for n:=1 to len(a)
        ? a[n]
    next
    ?

****************************************************************************
function qsort(a,p:=1,r:=len(a),blk:={|x,y|x<=y}) //elvi implementáció
local q
    if( p<r )
        q:=qsplit(a,p,r,blk)
        qsort(a,p,q-1,blk)
        qsort(a,q+1,r,blk)
    end
    
****************************************************************************
#define POP(x1,x2)        (--stkptr,x1:=stack1[stkptr],x2:=stack2[stkptr])
//#define PUSH(a,x1,x2,b) if(x1  <x2,(stack1[stkptr]:=x1,stack2[stkptr]:=x2,++stkptr),NIL)
#define PUSH(a,x1,x2,b)   if(x1+3<x2,(stack1[stkptr]:=x1,stack2[stkptr]:=x2,++stkptr),isort(a,x1,x2,b))

****************************************************************************
function xqsort(a,p:=1,r:=len(a),blk:={|x,y|x<=y}) //optimalizált implementáció

local pow2:=1,log2:=0
local stack1,stack2,stkptr:=1
local x1,x2,q,n

    while( pow2<r-p )  
        log2+=1
        pow2*=2
    end
    stack1:=array(log2+10)
    stack2:=array(log2+10)

    PUSH(a,p,r,blk)
    while( stkptr>1 )
        POP(x1,x2)

        q:=qsplit(a,x1,x2,blk)
        
        if( q-x1<x2-q )
            PUSH(a,q+1,x2,blk) //larger
            PUSH(a,x1,q-1,blk)
        else
            PUSH(a,x1,q-1,blk) //larger
            PUSH(a,q+1,x2,blk)
        end
    end

****************************************************************************
static function qsplit(a,p,r,blk)

local i:=p-1,j,k,x,tmp

//#define RANDOMIZE
#ifdef  RANDOMIZE
    k:=p+random()%(r-p+1)  //véletlenszám p..r között
    x:=a[k]
    a[k]:=a[r]
    a[r]:=x
#else
    x:=a[r]  //őrszem
#endif

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
static function isort(a,p,r,blk) //insertion sort
local i,j,v
    for i:=p+1 to r
        v:=a[i]
        j:=i-1
        while( j>=p .and. blk::eval(v,a[j]) )
            a[j+1]:=a[j]
            j:=j-1
        end
        a[j+1]:=v
    next

****************************************************************************
