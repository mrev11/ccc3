

// Legegyszerubb elvi implementacio.
// Rendezettseg elleni vedelem: veletlen pivot valasztassal.
// Sok egyenlo elem eseten stack overflow-val elszallhat.


#include "qsort.ch"

****************************************************************************
function qsort_2(*)
    ?? "qsort_2"::padr(16)
    qsort(*)


****************************************************************************
static function qsort(a,p:=1,r:=len(a),blk)

// a    : array to sort
// p    : start index
// r    : final index
// blk  : compare block

local q

    while( p+ISORT_TRESHOLD<r )
        q:=qsplit(a,p,r,blk)

        if( r-q>q-p  )
            qsort(a,p,q-1,blk)
            p:=q+1
        else
            qsort(a,q+1,r,blk)
            r:=q-1
        end
    end

    if( p<r )
        isort(a,p,r,blk)
    end

    // farok rekurzio megakadalyozza a callstack overflow-t
    // de egyenlo elemek eseten igy is O(n^2)-esre lassul


****************************************************************************
static function qsplit(a,p,r,blk)

local x,pivot
local i,q

    pivot:=a[x:=pivot_index(a,p,r)]
    swap(a,x,r)

    q:=p-1
    for i:=p to r-1
        if( compare(a[i],pivot,blk)<0 )
            q++
            swap(a,i,q)
        end
    next
    q++
    swap(a,q,r)
    return q


****************************************************************************
