
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
//
//1) rekurzió helyett stack
//   a stackre először a nagyobbik, utána a kisebbik rész kerül,
//   így mindig először a kisebbik rész lesz rendezve,
//   ami biztosítja, hogy a stack nem nő log(n)-nél nagyobbra
//
//2) a rövid részhalmazokat isort rendezi
//
//3) az őrszem 
//      egy 3 elemű részhalmaz mediánja
//      véletlenszerűen választott elem
//
//4) az összehasonlitás váltakozó irányban történik
//   az egyező elemek okozta lassulás elkerülésére


//megjegyzések:
//
// a könyvtári asort a libc-beli qsort-on alapul
//  mindig oda-vissza kiértékeli az összehasonlító blokkot
//  ennek ellenére gyorsabb az itteni implementációknál 
//  különösen gyorsabb eleve rendezett halmazokon
//
// a könyvtári asort-tal nem működik a libgc
//  mert az objektum-referenciák swapját byteonként végzi(!)
//  mert a referenciákat a kollektor által nem kezelt memóriába teszi
//  viszont az itteni xqsort gc friendly

****************************************************************************
function main(arg)

local a:=array(5000),n
local cmpcnt:=0
local blk:={|x,y|++cmpcnt,y<x}

    for n:=1 to len(a)
        a[n]:=random()%20 //-> sok egyenlő elem
    next

    if( arg=="q" )
        qsort(a,,,blk) //simple qsort
    end 
    
    if( arg=="x" )
        xqsort(a,,,blk) //optimized qsort
    end

    if( arg=="i" )
        isort(a,1,len(a),blk) //insertion
    end

    if( arg=="a" )
        asort(a,1,len(a),blk) // könyvtári
    end

    ? arg, cmpcnt
    ?

    set printer to log-sorted
    set printer on
    set console off

    for n:=1 to len(a)
        ? a[n]
    next
    ?

****************************************************************************
//function asort(a,sta:=1,cnt:=len(a)-sta+1,blk) //Clipper asort
//    xqsort(a,sta,sta+cnt-1,blk)
//    return a

//ez lehet a könyvtári asort függvény helyettesítése

****************************************************************************
static function qsort(a,p:=1,r:=len(a),blk:={|x,y|x<y}) //elvi implementáció

local q

    if( p<r )
        q:=qsplit(a,p,r,blk)
        qsort(a,p,q-1,blk)
        qsort(a,q+1,r,blk)
    end
    
    //itt szerencsétlen esetben stack overflow lehet
    //pl. sok egyenlő elem esetén, ha nem alkalmazunk
    //váltakozó irányt az összehasonlításban
    
****************************************************************************
#define POP(x1,x2)        (--stkptr,x1:=stack1[stkptr],x2:=stack2[stkptr])
//#define PUSH(a,x1,x2,b) if(x1  <x2,(stack1[stkptr]:=x1,stack2[stkptr]:=x2,++stkptr),NIL)
#define PUSH(a,x1,x2,b)   if(x1+3<x2,(stack1[stkptr]:=x1,stack2[stkptr]:=x2,++stkptr),isort(a,x1,x2,b))

****************************************************************************
static function xqsort(a,p:=1,r:=len(a),blk:={|x,y|x<y}) //optimalizált implementáció

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

    //itt nem lehet stack overflow

****************************************************************************
static function qsplit(a,p,r,blk)

local i:=p-1,j,x,tmp,flg:=.t.

//#define RANDOMIZE
#define MEDIAN


#ifdef RANDOMIZE
local k:=p+random()%(r-p+1)  //véletlenszám p..r között
    x:=a[k]
    a[k]:=a[r]
    a[r]:=x //őrszem
#endif //RANDOMIZE 


#ifdef MEDIAN
local q,xp,xq,xr

#define SWAP(k)  x:=a[k];a[k]:=a[r];a[r]:=x //őrszem

    q:=int((p+r)/2)
    xp:=a[p]
    xq:=a[q]
    xr:=a[r]
    if( eval(blk,xp,xr) )
        if( eval(blk,xq,xp) )
            SWAP(p)
        elseif( eval(blk,xr,xq) )
            //SWAP(r)
            x:=a[r]  //őrszem
        else
            SWAP(q)
        end
    else
        if( eval(blk,xq,xr) )
            //SWAP(r)
            x:=a[r]  //őrszem
        elseif( eval(blk,xp,xq) )
            SWAP(p)
        else
            SWAP(q)
        end
    end
#endif //MEDIAN


#ifndef RANDOMIZE
#ifndef MEDIAN
    x:=a[r]  //őrszem (alapeset)
#endif 
#endif 

    for j:=p to r-1

        if(flg)
            //váltakozó irányú összehasonlítás
            //az egyenlő elemek okozta lassulás ellen
        
            if( blk::eval(a[j],x) )
                i++
                tmp:=a[i]
                a[i]:=a[j]
                a[j]:=tmp
            end
            flg:=.f.
        else
            if( !blk::eval(x,a[j]) )
                i++
                tmp:=a[i]
                a[i]:=a[j]
                a[j]:=tmp
            end
            flg:=.t.
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
