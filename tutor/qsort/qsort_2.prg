

// Legegyszerubb elvi implementacio.
// Rendezettseg elleni vedelem: veletlen pivot valasztassal.
// Sok egyenlo elem eseten stack overflow-val elszallhat.


#include "qsort.ch"

****************************************************************************
function qsort_2(*)
    ?? "2"
    qsort(*)


****************************************************************************
static function qsort(a,p:=1,r:=len(a))

local q

    while( p<r )
        q:=qsplit(a,p,r)

        if( r-q>q-p  )
            qsort(a,p,q-1)
            p:=q+1
        else
            qsort(a,q+1,r)
            r:=q-1
        end
    end

    // farok rekurzio megakadalyozza a callstack overflow-t
    // de egyenlo elemek eseten igy is o(n^2)-esre lassul


****************************************************************************
static function qsplit(a,p,r)

local x,pivot
local i,q

    pivot:=a[x:=pivot(a,p,r)]
    swap(a,x,r)

    q:=p-1
    for i:=p to r-1
        if( stdcmp(a[i],pivot)<0 )
            q++
            swap(a,i,q)
        end
    next
    q++
    swap(a,q,r)
    return q


****************************************************************************
static function swap(a,x,y)
local tmp:=a[x]
    a[x]:=a[y]
    a[y]:=tmp


****************************************************************************
static function pivot(a,p,r)
local q:=crypto_rand_bytes(3)::bin2hex::hex2l
    q:=p+q%(r-p+1)
    return q


****************************************************************************

