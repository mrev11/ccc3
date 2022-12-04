

static pool:=threadpoolNew(5)


******************************************************************************************
function main()

local cnt:=0
local job:={{|*|code(*)}}

    while( 27!=inkey(0) )
        aadd(job,(++cnt)::str::alltrim ) // hosszabbodik a param lista
        pool:addjob(job)
    end
    ? 


******************************************************************************************
static function code(*)
    ? ">>>",name(thread_self()),time(),"params:", {*}
    sleep(5000)       
    ? "<<<",name(thread_self()),time(),"params:", {*}


******************************************************************************************
static function name(tid)
local x:=ascan(pool:threads,tid)
    if( x>0 )
        tid:="ABCDEFGH"[(x-1)%8+1]
    end
    return tid


******************************************************************************************

   