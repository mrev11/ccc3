
//demonstrálja,
//hogy a szálak egyidőben futnak
//hogy a szálak közös static változókkal, de külön local stackkel rendelkeznek
//a localstack függvény használatát

static s1:="s1"
static s2:="s2"
static s3:="s3"

static mutex:=thread_mutex_init()

*********************************************************************************
function main()

local a:="a",b:="b",c:="c"
local blk:={|*|other_thread(*)}
local th

    s1 //hivatkozás nélkül nem jön létre
    s2
    s3
    
    rand(seconds())
    
    th:=thread_create(blk,1,2,3)
    //th:=eval(blk,1,2,3)

    work("MAIN")

    if(th!=NIL)
        thread_join(th)
    end
    

*********************************************************************************
function other_thread(*)
local hopp:="HOPP"
    work("THREAD")
    
*********************************************************************************
function work(text)
local n
    for n:=1 to 100
        sleep(rand())
        thread_mutex_lock(mutex)
        ? text,n
        thread_mutex_unlock(mutex)
    next

    thread_mutex_lock(mutex)
    varstack()
    ? localstack(1), localstack(2), localstack(3), localstack(4), localstack(5)
    ?
    thread_mutex_unlock(mutex)


*********************************************************************************
    