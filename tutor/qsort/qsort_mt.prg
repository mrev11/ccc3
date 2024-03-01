

#include "qsort.ch"


static pool:=threadpoolNew(8)
static sort:=(|*|qsort(*))


****************************************************************************
function qsort_mt(*)
     ?? "qsort_mt"::padr(16)
   qsort1(*)


static function qsort1(*)
    pool:addjob({sort,*})
    //pool:wait
    poolwait(pool)  // mint pool:wait,  csak listazza a queue hosszat


// ez mukodik, aminek orulni kell, de sokkal lassabb, mint az egyszalu
// a pool:wait alabbi modositasa mutatja, milyen hosszu a sor (tobb 10 ezer)


static function poolwait(this)
local wait:=.t.
local maxlen:=0

    while(wait)
        this:actmutx::thread_mutex_lock
        while( this:active>0 )
            this:actcond::thread_cond_wait(this:actmutx)
        end
        if( this:jobmutx::thread_mutex_trylock==0 )
            if( this:jobs::len==0 )
                wait:=.f.
            end
            
            if( maxlen<this:jobs::len )
                maxlen:=this:jobs::len
                ? "max number of waiting jobs:",maxlen
            end    
                
            this:jobmutx::thread_mutex_unlock
        end
        this:actmutx::thread_mutex_unlock
    end


****************************************************************************
static function qsort(a,p:=1,r:=len(a))
local q
    while( p<r )
        q:=qsplit(a,p,r)

        if( q-p>r-q)
            pool:addjob( {sort,a,p,q} )
            p:=q+1
        else
            pool:addjob( {sort,a,q+1,r} )
            r:=q
        end
    end


****************************************************************************
static function qsplit(a,p,r)

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

