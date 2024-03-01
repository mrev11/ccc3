
// Hoare-fele particionalas
// rekurzio atirva stackre

#include "qsort.ch"


****************************************************************************
function qsort_hs(*)
    ?? "qsort_hs"::padr(16)
    qsort(*)


****************************************************************************
static function qsort(a,p:=1,r:=len(a))

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

        while( p<r )
            q:=qsplit(a,p,r)

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
    end
    
    for p:=1 to len(sp)
        if( sp[p]==NIL )
            //?? " maxdepth",p
            exit
        end
    next


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

