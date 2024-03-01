

#include "qsort.ch"


****************************************************************************
function main()

local x:=array(TEST_ARRLEN),n
local cmpblk//:={|a,b|stdcmp(a,b)}

    for n:=1 to len(x)
        x[n]:=crypto_rand_bytes(10)::bin2hex[1..TEST_STRLEN]
    next

    ? "length",x::len::str(7)
    #ifdef TEST_ASCEND
        ?? "  ASCEND "
        asort(x)
    #endif
    #ifdef TEST_DESCEND
        ?? "  DESCEND "
        asort(x,{|x,y|-stdcmp(x,y)})
    #endif
    ?? "  treshold", ISORT_TRESHOLD::str(2)

    #ifdef PIVOT_MEDIAN
        ?? "  pivot MEDIAN of 3"
    #else
        #ifdef PIVOT_RANDOM
            ?? "  pivot RANDOM"
        #else
            ?? "  pivot MIDDLE"
        #endif
    #endif

    ?

    test( (|a|  xasort      (a,1,len(a),cmpblk)), x  )

    test( (|a|  qsortc_3    (a,1,len(a),cmpblk)), x  )
    test( (|a|  qsortc_h    (a,1,len(a),cmpblk)), x  )
    test( (|a|  qsortc_hs   (a,1,len(a),cmpblk)), x  )


#ifdef EZEK_VANNAK

    test( (|a|  xasort      (a,1,len(a),cmpblk)), x  )
    test( (|a|  xisort      (a,1,len(a),cmpblk)), x  )

    test( (|a|  qsortc_3    (a,1,len(a),cmpblk)), x  )
    test( (|a|  qsortc_h    (a,1,len(a),cmpblk)), x  )
    test( (|a|  qsortc_hs   (a,1,len(a),cmpblk)), x  )

    test( (|a|  qsort_2     (a,1,len(a),cmpblk)), x  )
    test( (|a|  qsort_2x    (a,1,len(a),cmpblk)), x  )
    test( (|a|  qsort_3     (a,1,len(a),cmpblk)), x  )
    test( (|a|  qsort_h     (a,1,len(a),cmpblk)), x  )
    test( (|a|  qsort_hs    (a,1,len(a),cmpblk)), x  )
    test( (|a|  qsort_mt    (a,1,len(a),cmpblk)), x  )

#endif

 

    

****************************************************************************
static function test(sort,x)
local arr:=aclone(x) 
    tick(".") 
    eval(sort,arr) 
    tick()
    verify(arr)


****************************************************************************
static function tick(op)
static tick
    if( !empty(op) )
        tick:=gettickcount()
        ? op::padr(2)
    else
        ??  str((gettickcount()-tick)/1000,6,1)
    end


****************************************************************************
static function verify(a)
local eq,n

    begin
        eq:=0
        for n:=2 to len(a)
            if( a[n-1]==a[n] )
                eq++
            elseif( a[n-1]>a[n] )
                // error
                eq:=0
                exit
            next
        next
        if( n>len(a) )
            break(NIL) // ok ascend
        end
        
        eq:=0
        for n:=2 to len(a)
            if( a[n-1]==a[n] )
                eq++
            elseif( a[n-1]<a[n] )
                // error
                eq:=0
                exit
            next
        next
        if( n>len(a) )
            break(NIL) // ok descend
        end

        // WRONG
        ?? " WRONG"

    recover
        // RIGHT
        ?? eq
    end

    #ifdef DEBUG
    ?? " ",a
    #endif


****************************************************************************
static function xisort(*)
    ?? "isort"::padr(16)
    isort(*)

static function xasort(*)
    ?? "asort"::padr(16)
    asort(*)


****************************************************************************










