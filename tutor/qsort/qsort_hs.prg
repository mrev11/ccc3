
// Hoare-fele particionalas
// rekurzio atirva stackre

#include "qsort.ch"


****************************************************************************
function qsort_hs(*)
    ?? "qsort_hs"::padr(16)
    qsort(*)


****************************************************************************
static function qsort(a,p:=1,r:=len(a),blk)

// a    : array to sort
// p    : start index
// r    : final index
// blk  : compare block

local q
local sp:=array(100)
local sr:=array(100)
local ss:=0

    ++ss
    sp[ss]:=p
    sr[ss]:=r
    
    while( ss>0 )
        
        p:=sp[ss]
        r:=sr[ss]
        --ss

        while( p+ISORT_TRESHOLD<r )
            q:=qsplit(a,p,r,blk)

            if( q-p>r-q)
                ++ss
                sp[ss]:=p
                sr[ss]:=q
                p:=q+1
            else
                ++ss
                sp[ss]:=q+1
                sr[ss]:=r
                r:=q
            end
        end

        if( p<r )
            isort(a,p,r,blk)
        end
    end
    
    for p:=1 to len(sp)
        if( sp[p]==NIL )
            //?? " maxdepth",p
            exit
        end
    next


****************************************************************************
static function qsplit(a,p,r,blk) // Hoare-fele particionalas

local i:=p-1
local j:=r+1
local pivot:=pivot(a,p,r-1,blk) // utolso kihagyva!

    while( .t. )
        while( 0>compare(a[++i],pivot,blk) ); end
        while( 0<compare(a[--j],pivot,blk) ); end
        if( i>=j )
            return j
        end
        swap(a,i,j)
    next


****************************************************************************
