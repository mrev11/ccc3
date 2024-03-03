
// Hoare-fele particionalas


#include "qsort.ch"


****************************************************************************
function qsort_h(*)
    ?? "qsort_h"::padr(16)
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
        if( q-p<r-q)
            qsort(a,p,q,blk)
            p:=q+1
        else
            qsort(a,q+1,r,blk)
            r:=q
        end
    end

    if( p<r )
        isort(a,p,r,blk)
    end


****************************************************************************
static function qsplit(a,p,r,blk) // Hoare-fele particionalas

local i:=p-1
local j:=r+1
local pivot:=pivot(a,p,r)

    while( .t. )
        while( 0>compare(a[++i],pivot,blk) ); end
        while( 0<compare(a[--j],pivot,blk) ); end
        if( i>=j )
            return j
        end
        swap(a,i,j)
    next


****************************************************************************
