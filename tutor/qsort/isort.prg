
// insertion sort

#include "qsort.ch"

******************************************************************************************
function isort(a,p,r,blk)

// a    : array to sort
// p    : start index
// r    : final index
// blk  : compare block

local x,i,j

    i:=p+1
    while( i<=r )
        x:=a[i]
        j:=i
        while( j>p .and. 0<compare(a[j-1],x,blk) )
            a[j]:=a[j-1]
            j--
        end
        a[j]:=x
        i++
    end


******************************************************************************************
function compare(x,y,blk)
    if( blk!=NIL )
        return eval(blk,x,y)
    end
    return stdcmp(x,y)


******************************************************************************************
function swap(a,x,y)
local tmp:=a[x]
    a[x]:=a[y]
    a[y]:=tmp


******************************************************************************************
#ifdef PIVOT_MIDDLE
function pivot_index(a,p,r)
    return p+int((r-p)/2)
#endif

#ifdef PIVOT_RANDOM
function pivot_index(a,p,r) //ugyanaz
local q:=crypto_rand_bytes(4)::bin2hex::hex2l
    q:=p+q%(r-p+1)
    return q
#endif

#ifdef PIVOT_MEDIAN
function pivot_index(a,p,r) //ugyanaz
local q:=crypto_rand_bytes(4)::bin2hex::hex2l
    q:=p+q%(r-p+1)
    return q
#endif


function pivot(a,p,r)
    return a[pivot_index(a,p,r)]

******************************************************************************************



#ifdef KIHAGY
******************************************************************************************
function isort_swap(a)
local i,j
    i:=2
    while( i<=len(a) )
        j:=i
        while( j>1 .and. a[j-1]>a[j] ) 
            swap(a,j-1,j)
            j--
        end         
        i++
    end


******************************************************************************************
function isort_recur(a,len)
local x,j
    if( len>1 )
        isort(a,len-1)
        x:=a[len]
        j:=len-1
        while( j>=1 .and. a[j]>x  ) 
            a[j+1]:=a[j]
            j--
        end         
        a[j+1]:=x
    end


******************************************************************************************
#endif
