
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

#include "qsort.ch"


****************************************************************************
function main( cmpblk )

local x:=array(TEST_ARRLEN),n

    if( cmpblk=="n" ) 
        cmpblk:=NIL                             // default ascend
    elseif( cmpblk=="t" ) 
        cmpblk:=.t.                             // ascend
    elseif( cmpblk=="f" ) 
        cmpblk:=.f.                             // descend
    else
        cmpblk:={|a,b|counter(),stdcmp(a,b)}    // block ascend
    end


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
        ?? "  pivot MEDIAN"
    #endif
    #ifdef PIVOT_RANDOM
        ?? "  pivot RANDOM"
    #endif
    #ifdef PIVOT_MIDDLE
        ?? "  pivot MIDDLE"
    #endif

    ?


#ifdef   TEST_ASORT    
    test( (|a|  xasort      (a,1,len(a),cmpblk)), x  )
#endif
#ifdef   TEST_ISORT    
    test( (|a|  xisort      (a,1,len(a),cmpblk)), x  )
#endif

    ?

#ifdef   TEST_HSORTC    
    test( (|a|  hsortc      (a,1,len(a),cmpblk)), x  )
#endif
#ifdef   TEST_QSORTC_3  
    test( (|a|  qsortc_3    (a,1,len(a),cmpblk)), x  )
#endif
#ifdef   TEST_QSORTC_H  
    test( (|a|  qsortc_h    (a,1,len(a),cmpblk)), x  )
#endif
#ifdef   TEST_QSORTC_HS 
    test( (|a|  qsortc_hs   (a,1,len(a),cmpblk)), x  )
#endif

    ?

#ifdef   TEST_HSORT     
    test( (|a|  hsort       (a,1,len(a),cmpblk)), x  )
#endif
#ifdef   TEST_HSORT_B   
    test( (|a|  hsort_b     (a,1,len(a),cmpblk)), x  )
#endif
#ifdef   TEST_QSORT_2   
    test( (|a|  qsort_2     (a,1,len(a),cmpblk)), x  )
#endif
#ifdef   TEST_QSORT_2X  
    test( (|a|  qsort_2x    (a,1,len(a),cmpblk)), x  )
#endif
#ifdef   TEST_QSORT_3   
    test( (|a|  qsort_3     (a,1,len(a),cmpblk)), x  )
#endif
#ifdef   TEST_QSORT_H   
    test( (|a|  qsort_h     (a,1,len(a),cmpblk)), x  )
#endif
#ifdef   TEST_QSORT_HS  
    test( (|a|  qsort_hs    (a,1,len(a),cmpblk)), x  )
#endif
#ifdef   TEST_QSORT_MT  
    test( (|a|  qsort_mt    (a,1,len(a),cmpblk)), x  )
#endif



****************************************************************************
static function test(sort,x)
local arr:=aclone(x)
    counter(0)
    tick(".")
    eval(sort,arr)
    tick()
    verify(arr)
    ?? counter()::transform("999,999,999,999")


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
static function counter(x)
static mutex:=thread_mutex_init()
static cnt:=0
    thread_mutex_lock(mutex)
    if( x!=NIL )
        cnt:=x
    else
        ++cnt
    end
    thread_mutex_unlock(mutex)
    return cnt


****************************************************************************
static function xisort(*)
    ?? "ISORT"::padr(16)
    isort(*)

static function xasort(*)
    ?? "ASORT"::padr(16)
    asort(*)


****************************************************************************
