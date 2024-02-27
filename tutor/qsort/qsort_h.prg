

#include "qsort.ch"


****************************************************************************
function qsort_h(*)
    ?? "h"
    qsort(*)


****************************************************************************
static function qsort(a,p:=1,r:=len(a))
local q
    while( 0<=p<r )
        q:=qsplit(a,p,r)
        if( q-p<r-q)
            qsort(a,p,q)
            p:=q+1
        else
            qsort(a,q+1,r)
            r:=q
        end
    end


****************************************************************************
static function qsplit(a,p,r) // Hoare-fele particionalas

local i:=p-1
local j:=r+1
local pivot:=pivot(a,p,r) 

    while( .t. )
        while( 0>stdcmp(a[++i],pivot) ); end 
        while( 0<stdcmp(a[--j],pivot) ); end
        if( i>=j )
            return j
        end
        swap(a,i,j)
    next


****************************************************************************
static function swap(a,x,y)
local tmp:=a[x]
    a[x]:=a[y]
    a[y]:=tmp


****************************************************************************
static function pivot(a,p,r)
local q:=crypto_rand_bytes(3)::bin2hex::hex2l
    q:=p+q%(r-p+1)
    return a[q]


****************************************************************************

