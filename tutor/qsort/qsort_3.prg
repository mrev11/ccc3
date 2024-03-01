
// Rendezettseg elleni vedelem: veletlen pivot valasztas
// Egyenlo elemek elleni vedelem: harom reszre osztas (lt,eq,gt)


#include "qsort.ch"

static depth:=0
static maxdepth:=0

****************************************************************************
function qsort_3(*)
    ?? "qsort_3"::padr(16)
    qsort(*)
    //?? " maxdepth",maxdepth

****************************************************************************
static function qsort(a,p:=1,r:=len(a))

local lt,gt

    if( ++depth>maxdepth )
        maxdepth:=depth
    end

    while( p<r )
        qsplit(a,p,r,@lt,@gt)

        if( lt-p<r-gt )
            qsort(a,p,lt)
            p:=gt
        else
            qsort(a,gt,r)
            r:=lt
        end
    end
    
    --depth


****************************************************************************
static function qsplit(a,p,r,q1,q2)

local lt:=p
local eq:=p
local gt:=r
local pivot 
local cmp

    pivot:=pivot(a,p,r)

    while( eq<=gt)
        cmp:=stdcmp(a[eq],pivot)
        if( cmp<0 )
            swap(a,eq,lt)
            lt++
            eq++
        elseif( cmp>0 )
            swap(a,eq,gt)
            gt--
        else
            eq++
        end
    next

#ifdef XDEBUG
    ? pivot,;
      "lt="+lt::str::alltrim,;
      "eq="+eq::str::alltrim,;
      "gt="+gt::str::alltrim,;
      a[p..lt-1],a[lt..eq-1],a[eq..r]
#endif

    q1:=lt-1   // utolso kisebb
    q2:=eq     // elso nagyobb


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

