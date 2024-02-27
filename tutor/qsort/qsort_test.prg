

#include "qsort.ch"


****************************************************************************
function main()

local x:=array(ARRLEN),a,n,eq

    for n:=1 to len(x)
        x[n]:=crypto_rand_bytes(10)::bin2hex[1..STRLEN]
    next

    a:=aclone(x)
    tick(STRING(ASORT))
    //ASORT(a,,,{|x,y|stdcmp(x,y)}) //növekvő
    //ASORT(a,,,{|x,y|x<y})
    ASORT(a)
    tick()

    a:=aclone(x)
    tick(STRING(QSORT))
    //QSORT(a,,,{|x,y|stdcmp(x,y)}) //növekvő
    QSORT(a)
    tick()

    #ifdef DEBUG
    ? a
    #endif

    eq:=0
    for n:=2 to len(a)
        if( a[n-1]>a[n] )
            ? "HOPP",n
            ?
            quit
        elseif( a[n-1]==a[n] )
            eq++
        next
    next
    ? eq
    ?
    

****************************************************************************
static function tick(op)
static tick
    if( !empty(op) )
        tick:=gettickcount()
        ? op::padr(16)
    else
        ??  str((gettickcount()-tick)/1000,6,1)
    end

****************************************************************************












