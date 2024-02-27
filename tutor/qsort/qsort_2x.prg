
// Legegyszerubb elvi implementacio + indexek.
// Rendezettseg elleni vedelem: veletlen pivot valasztassal.
// Egyenlo elemek eseten a rendezeskor figyelembe veszi az
// elem indexet, tehat valojaban nincsenek egyenlo elemek.
// Ez kivedi a stack overflow-val torteno elszallast.

#include "qsort.ch"


****************************************************************************
function qsort_2x(arr,p,r,blk)
    ?? "2x"
    qsort(arr,p,r,blk)


// a blk-t nem hasznalja
// a teszt program mindig
// novekvo sorrendben rendez

****************************************************************************
static function qsort(a,p:=1,r:=len(a),blk,index)

local q

    if( index==NIL )
        index:=array(r-p+1)
        for q:=p to r
            index[q]:=q
        next
    end

    if( p<r )
        q:=qsplit(a,p,r,index)
        if( r-q>q-p  )
            qsort(a,p,q-1,blk,index)
            qsort(a,q+1,r,blk,index)
        else
            qsort(a,q+1,r,blk,index)
            qsort(a,p,q-1,blk,index)
        end
    end


****************************************************************************
static function qsplit(a,p,r,index)

local x,pivot
local i,q,cmp

    pivot:=a[x:=pivot(a,p,r)]
    swap(a,x,r,index)

    q:=p-1
    for i:=p to r-1
        cmp:=stdcmp(a[i],pivot)
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
static function swap(a,x,y,index)
local tmp

    tmp:=a[x]
    a[x]:=a[y]
    a[y]:=tmp

    //tmp:=index[x]
    //index[x]:=index[y]
    //index[y]:=tmp
    
// Ha az index tombot is swapoljuk, akkor 
// az egyenlo elemek megtartjak a sorrendjuket.
// Ha nem swapoljuk, akkor az egyenlo elemek 
// keverednek,  de a stack overflow kivedesehez 
// ez is eleg (es nem is kell az index tomb).


****************************************************************************
static function pivot(a,p,r)
local q:=crypto_rand_bytes(3)::bin2hex::hex2l
    q:=p+q%(r-p+1)
    return q


****************************************************************************

