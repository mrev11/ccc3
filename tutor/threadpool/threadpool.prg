

******************************************************************************************
class threadpool(object)

    attrib  threads             // list of thread_self() values
    attrib  jobs                // queue of jobs
    attrib  active              // number of active threads

    attrib  slpmutx             // sleeping threads wait for this mutex
    attrib  jobmutx             // locked while job queue is changing
    attrib  jobcond             // used along with jobmutx
    attrib  actmutx             // locked while this:active is changing
    attrib  actcond             // used along with actmutx
    attrib  thrmutx             // locked while this:threads is changing
    attrib  thrcond             // used along with thrmutx

    method  addthread
    method  numthreads          // number of threads
    method  addjob
    method  lenjobs             // length of queue of jobs
    method  actjobs             // number of jobs under processing (active)

    method  wait
    method  exit

    method  initialize


******************************************************************************************
static function threadpool.initialize(this, number_of_threads)
local n

    this:threads:={}
    this:jobs:={}
    this:active:=0

    this:slpmutx:=thread_mutex_init()
    this:jobmutx:=thread_mutex_init()
    this:jobcond:=thread_cond_init()
    this:actmutx:=thread_mutex_init()
    this:actcond:=thread_cond_init()
    this:thrmutx:=thread_mutex_init()
    this:thrcond:=thread_cond_init()

    for n:=1 to number_of_threads
        this:addthread
    next

    return this

******************************************************************************************
static function threadpool.addthread(this)
    thread_create({|t|thread(t)},this)

******************************************************************************************
static function threadpool.numthreads(this)
local num
    this:thrmutx::thread_mutex_lock
    num:=this:threads::len
    this:thrmutx::thread_mutex_unlock
    return num

******************************************************************************************
static function threadpool.addjob(this,job)
    this:jobmutx::thread_mutex_lock
    this:jobs::aadd(job)
    this:jobmutx::thread_mutex_unlock
    this:jobcond::thread_cond_signal    // jelzi a queue valtozasat

******************************************************************************************
static function threadpool.lenjobs(this)
local len
    this:jobmutx::thread_mutex_lock
    len:=this:jobs::len
    this:jobmutx::thread_mutex_unlock
    return len

******************************************************************************************
static function threadpool.actjobs(this)
local act
    this:actmutx::thread_mutex_lock
    act:=this:active
    this:actmutx::thread_mutex_unlock
    return act

******************************************************************************************
static function threadpool.wait(this,lwm:=0)

    //var, mig elfogynak a jobok a sorbol
    this:jobmutx::thread_mutex_lock
    while( len(this:jobs)>lwm )
        this:jobcond::thread_cond_wait(this:jobmutx)
    end
    this:jobmutx::thread_mutex_unlock
    
    if( lwm==0 )
        //var, mig befejezodnek a futo jobok
        this:actmutx::thread_mutex_lock
        while( this:active>0  )
            this:actcond::thread_cond_wait(this:actmutx)
        end
        this:actmutx::thread_mutex_unlock
    end

******************************************************************************************
static function threadpool.exit(this)
    this:thrmutx::thread_mutex_lock
    while( len(this:threads)>0 )
        this:addjob(NIL)
        this:thrcond::thread_cond_wait(this:thrmutx)
    end
    this:thrmutx::thread_mutex_unlock

******************************************************************************************
static function thread(this) // ezzel indul minden thread
local job,x

    this:thrmutx::thread_mutex_lock
    this:threads::aadd(thread_self())
    this:thrmutx::thread_mutex_unlock

    // VIGYAZAT
    // Linuxon (tid:=thread_create()) == (self:=thread_self())
    // Windows (tid:=thread_create()) != (self:=thread_self())
    // ezert threads-ba nem tid-eket, hanem self-eket teszunk

    while(.t.)
        this:slpmutx::thread_mutex_lock()      // LOCKED-thr

        // var, mig a queue-ba bekerul egy job
        this:jobmutx::thread_mutex_lock()      // LOCKED-job
        while( 1>len(this:jobs) )
            this:jobcond::thread_cond_wait(this:jobmutx)
        end
        this:actmutx::thread_mutex_lock()
        this:active++
        this:actmutx::thread_mutex_unlock()
        job:=this:jobs[1]
        this:jobs::adel(1)
        this:jobs::asize(len(this:jobs)-1)
        this:jobmutx::thread_mutex_unlock()    // UNLOCKED-job (kivette a job-ot)
        this:jobcond::thread_cond_signal       // jelzi a queue valtozasat

        this:slpmutx::thread_mutex_unlock()    // UNLOCKED-thr (engedi a tobbi thread-et)

        if( job==NIL )
            // end of thread
            this:thrmutx::thread_mutex_lock
            x:=ascan(this:threads,thread_self())
            this:threads::adel(x)
            this:threads::asize(len(this:threads)-1)
            this:thrmutx::thread_mutex_unlock
            this:thrcond::thread_cond_signal
        else
            // dolgozik
            // job={codeblock,arg1,arg2,...}
            evalarray( job[1], job[2..] )
        end

        this:actmutx::thread_mutex_lock()
        this:active--
        this:actmutx::thread_mutex_unlock()
        this:actcond::thread_cond_signal

        if( job==NIL )
            exit
        else
            job:=NIL // gc
        end
    end

******************************************************************************************

// thread_create
// thread_self
// thread_detach
// thread_exit
// thread_join
// thread_mutex_init
// thread_mutex_lock
// thread_mutex_trylock
// thread_mutex_unlock
// thread_mutex_destroy
// thread_cond_init
// thread_cond_signal
// thread_cond_wait
// thread_cond_destroy
// thread_create_detach

