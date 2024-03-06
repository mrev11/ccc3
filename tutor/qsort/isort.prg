
// insertion sort

#include "qsort.ch"


******************************************************************************************
function swap(a,x,y)
local tmp:=a[x]
    a[x]:=a[y]
    a[y]:=tmp


******************************************************************************************
function compare(x,y,blk)
    if( blk==NIL )
        return stdcmp(x,y) //asc
    elseif( valtype(blk)=="L" )
        return if(blk,stdcmp(x,y),stdcmp(y,x)) //asc/desc
    end
    return eval(blk,x,y)


******************************************************************************************
static function comparex(a,x,y,blk)
    if( blk==NIL )
        return stdcmp(a[x],a[y]) // asc
    elseif( valtype(blk)=="L" )
        return if(blk,stdcmp(a[x],a[y]),stdcmp(a[y],a[x])) //asc/desc
    end
    return eval(blk,a[x],a[y])


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
static function guess_median(a,p,r,blk,m)

local index:=array(m)
local x,i,j

    index[1]:=p
    for i:=2 to m-1
        index[i]:=index[i-1]+int((r-p+1)/(m-1))
    next
    index[m]:=r

    i:=2
    while( i<=m )
        x:=index[i]
        j:=i
        while( j>1 .and. 0<comparex(a,index[j-1],x,blk) )
            index[j]:=index[j-1]
            j--
        end
        index[j]:=x
        i++
    end

    return index[(m+1)/2]


******************************************************************************************
#ifdef PIVOT_MIDDLE
function pivot_index(a,p,r)
    return p+int((r-p+1)/2)
#endif

#ifdef PIVOT_RANDOM
function pivot_index(a,p,r)
local q:=crypto_rand_bytes(4)::bin2hex::hex2l
    q:=p+q%(r-p+1)
    return q
#endif

#ifdef PIVOT_MEDIAN
function pivot_index(a,p,r,blk)
local len:=r-p+1
    if( blk==NIL )
        return p+int(len/2)
    elseif( len<200 )
        return guess_median(a,p,r,blk,3)
    elseif( len<1000 )
        return guess_median(a,p,r,blk,5)
    else
        return guess_median(a,p,r,blk,7)
    end
#endif


function pivot(a,p,r,blk)
local px:=pivot_index(a,p,r,blk)
    return a[px]

******************************************************************************************

