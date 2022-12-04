

#command ?  [ <list,...> ] => print( <list> )


static pool:=threadpoolNew(6)

******************************************************************************************
function main()
local n

    rand(seconds()) // init

    for n:=1 to 20
        pool:addjob( { {|*|code(*)}, n } )
    next

    //#define DEBUG
    #ifdef DEBUG
        // kilepteti az osszes szalat
        while( pool:numthreads>0 )
            pool:addjob( NIL ) 
            ? "###", "num", pool:numthreads, "len", pool:lenjobs
            sleep(1000)
        end
        ? "### END"
    #else
        // kilepteti az osszes szalat
        pool:exit 
        ? "###", "numthreads", pool:numthreads
    #endif
    ? 

******************************************************************************************
static function code(param)
    ? " >", name(), time(), "par", param::str(3)
    sleep( rand()*5000 )       
    ? "< ", name(), time(), "par", param::str(3)


******************************************************************************************
static function name() // thread name: A,B,C...
local tid:=thread_self()
local x:=ascan(pool:threads,tid)
    if( x>0 )
        tid:="ABCDEFGH"[(x-1)%8+1]
    end
    return tid


******************************************************************************************
static function print(*)   // ne keveredjenek a kiirasok
static print:=thread_mutex_init()  
    print::thread_mutex_lock 
    qout(*)
    print::thread_mutex_unlock 


******************************************************************************************
   