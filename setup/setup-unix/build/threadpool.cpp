//input: ppo/threadpool.ppo (5.7.0.1)

#include <cccdef.h>

static void _blk_threadpoolregister_0(int argno);
static void _blk_threadpoolregister_1(int argno);
static void _blk_threadpoolregister_2(int argno);
static void _blk_threadpoolregister_3(int argno);
static void _blk_threadpoolregister_4(int argno);
static void _blk_threadpoolregister_5(int argno);
static void _blk_threadpoolregister_6(int argno);
static void _blk_threadpoolregister_7(int argno);
static void _blk_threadpoolregister_8(int argno);
static void _blk_threadpoolregister_9(int argno);
extern void _clp_aadd(int argno);
extern void _clp_adel(int argno);
extern void _clp_ascan(int argno);
extern void _clp_asize(int argno);
extern void _clp_classattrib(int argno);
extern void _clp_classmethod(int argno);
extern void _clp_classregister(int argno);
extern void _clp_evalarray(int argno);
extern void _clp_len(int argno);
extern void _clp_objectclass(int argno);
extern void _clp_objectnew(int argno);
static void _clp_thread(int argno);
extern void _clp_thread_cond_init(int argno);
extern void _clp_thread_cond_signal(int argno);
extern void _clp_thread_cond_wait(int argno);
extern void _clp_thread_create(int argno);
extern void _clp_thread_mutex_init(int argno);
extern void _clp_thread_mutex_lock(int argno);
extern void _clp_thread_mutex_trylock(int argno);
extern void _clp_thread_mutex_unlock(int argno);
extern void _clp_thread_self(int argno);
extern void _clp_threadpoolclass(int argno);
extern void _clp_threadpoolnew(int argno);
static void _clp_threadpoolregister(int argno);

namespace _nsp_threadpool{
static void _blk_addthread_0(int argno);
static void _clp_actjobs(int argno);
static void _clp_addjob(int argno);
static void _clp_addthread(int argno);
static void _clp_exit(int argno);
static void _clp_initialize(int argno);
static void _clp_lenjobs(int argno);
static void _clp_numthreads(int argno);
static void _clp_wait(int argno);
static void _clp_wait_act(int argno);
static void _clp_wait_job(int argno);
}//namespace threadpool

class _method6_actcond: public _method6_{public: _method6_actcond():_method6_("actcond"){};}; static _method6_actcond _o_method_actcond;
class _method6_active: public _method6_{public: _method6_active():_method6_("active"){};}; static _method6_active _o_method_active;
class _method6_actmutx: public _method6_{public: _method6_actmutx():_method6_("actmutx"){};}; static _method6_actmutx _o_method_actmutx;
class _method6_addjob: public _method6_{public: _method6_addjob():_method6_("addjob"){};}; static _method6_addjob _o_method_addjob;
class _method6_addthread: public _method6_{public: _method6_addthread():_method6_("addthread"){};}; static _method6_addthread _o_method_addthread;
class _method6_initialize: public _method6_{public: _method6_initialize():_method6_("initialize"){};}; static _method6_initialize _o_method_initialize;
class _method6_jobcond: public _method6_{public: _method6_jobcond():_method6_("jobcond"){};}; static _method6_jobcond _o_method_jobcond;
class _method6_jobmutx: public _method6_{public: _method6_jobmutx():_method6_("jobmutx"){};}; static _method6_jobmutx _o_method_jobmutx;
class _method6_jobs: public _method6_{public: _method6_jobs():_method6_("jobs"){};}; static _method6_jobs _o_method_jobs;
class _method6_slpmutx: public _method6_{public: _method6_slpmutx():_method6_("slpmutx"){};}; static _method6_slpmutx _o_method_slpmutx;
class _method6_thrcond: public _method6_{public: _method6_thrcond():_method6_("thrcond"){};}; static _method6_thrcond _o_method_thrcond;
class _method6_threads: public _method6_{public: _method6_threads():_method6_("threads"){};}; static _method6_threads _o_method_threads;
class _method6_thrmutx: public _method6_{public: _method6_thrmutx():_method6_("thrmutx"){};}; static _method6_thrmutx _o_method_thrmutx;

//=======================================================================

static VALUE* _st_clid_threadpool_ptr()
{
    static stvar _st_clid_threadpool;
    static int _ini_clid_threadpool=[=](){
        _clp_threadpoolregister(0);
        assign(_st_clid_threadpool.ptr);
        pop();
        return 1;
    }();
    return _st_clid_threadpool.ptr;
}
//=======================================================================
void _clp_threadpoolclass(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("threadpoolclass",base);
//
    line(4);
    push_symbol(_st_clid_threadpool_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_threadpoolregister(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+1)PUSHNIL();
argno=0;
push_call("threadpoolregister",base);
//
    line(7);
    string(L"threadpool");
    ::_clp_objectclass(0);
    array(1);
    _clp_classregister(2);
    assign(base+0);//clid
    pop();
    line(8);
    push_symbol(base+0);//clid
    string(L"threads");
    _clp_classattrib(2);
    pop();
    line(9);
    push_symbol(base+0);//clid
    string(L"jobs");
    _clp_classattrib(2);
    pop();
    line(10);
    push_symbol(base+0);//clid
    string(L"active");
    _clp_classattrib(2);
    pop();
    line(11);
    push_symbol(base+0);//clid
    string(L"slpmutx");
    _clp_classattrib(2);
    pop();
    line(12);
    push_symbol(base+0);//clid
    string(L"jobmutx");
    _clp_classattrib(2);
    pop();
    line(13);
    push_symbol(base+0);//clid
    string(L"jobcond");
    _clp_classattrib(2);
    pop();
    line(14);
    push_symbol(base+0);//clid
    string(L"actmutx");
    _clp_classattrib(2);
    pop();
    line(15);
    push_symbol(base+0);//clid
    string(L"actcond");
    _clp_classattrib(2);
    pop();
    line(16);
    push_symbol(base+0);//clid
    string(L"thrmutx");
    _clp_classattrib(2);
    pop();
    line(17);
    push_symbol(base+0);//clid
    string(L"thrcond");
    _clp_classattrib(2);
    pop();
    line(18);
    push_symbol(base+0);//clid
    string(L"addthread");
    block(_blk_threadpoolregister_0,0);
    _clp_classmethod(3);
    pop();
    line(19);
    push_symbol(base+0);//clid
    string(L"numthreads");
    block(_blk_threadpoolregister_1,0);
    _clp_classmethod(3);
    pop();
    line(20);
    push_symbol(base+0);//clid
    string(L"addjob");
    block(_blk_threadpoolregister_2,0);
    _clp_classmethod(3);
    pop();
    line(21);
    push_symbol(base+0);//clid
    string(L"lenjobs");
    block(_blk_threadpoolregister_3,0);
    _clp_classmethod(3);
    pop();
    line(22);
    push_symbol(base+0);//clid
    string(L"actjobs");
    block(_blk_threadpoolregister_4,0);
    _clp_classmethod(3);
    pop();
    line(23);
    push_symbol(base+0);//clid
    string(L"wait");
    block(_blk_threadpoolregister_5,0);
    _clp_classmethod(3);
    pop();
    line(24);
    push_symbol(base+0);//clid
    string(L"wait_job");
    block(_blk_threadpoolregister_6,0);
    _clp_classmethod(3);
    pop();
    line(25);
    push_symbol(base+0);//clid
    string(L"wait_act");
    block(_blk_threadpoolregister_7,0);
    _clp_classmethod(3);
    pop();
    line(26);
    push_symbol(base+0);//clid
    string(L"exit");
    block(_blk_threadpoolregister_8,0);
    _clp_classmethod(3);
    pop();
    line(27);
    push_symbol(base+0);//clid
    string(L"initialize");
    block(_blk_threadpoolregister_9,0);
    _clp_classmethod(3);
    pop();
    line(28);
    push_symbol(base+0);//clid
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_threadpoolregister_0(int argno)
{
//
    _nsp_threadpool::_clp_addthread(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_threadpoolregister_1(int argno)
{
//
    _nsp_threadpool::_clp_numthreads(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_threadpoolregister_2(int argno)
{
//
    _nsp_threadpool::_clp_addjob(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_threadpoolregister_3(int argno)
{
//
    _nsp_threadpool::_clp_lenjobs(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_threadpoolregister_4(int argno)
{
//
    _nsp_threadpool::_clp_actjobs(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_threadpoolregister_5(int argno)
{
//
    _nsp_threadpool::_clp_wait(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_threadpoolregister_6(int argno)
{
//
    _nsp_threadpool::_clp_wait_job(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_threadpoolregister_7(int argno)
{
//
    _nsp_threadpool::_clp_wait_act(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_threadpoolregister_8(int argno)
{
//
    _nsp_threadpool::_clp_exit(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_threadpoolregister_9(int argno)
{
//
    _nsp_threadpool::_clp_initialize(argno-1);
//
*(stack-2)=*(stack-1);pop();
}
//=======================================================================
void _clp_threadpoolnew(int argno)
{
    push(_st_clid_threadpool_ptr());
    _clp_objectnew(1);
    dup();
    int i;
    for(i=0; i<argno; i++)
    {
        *(stack-2-i)=*(stack-3-i);
    }
    *(stack-2-argno)=*(stack-1);
    pop();
    _o_method_initialize.eval(1+argno);
}
//=======================================================================
namespace _nsp_threadpool{
static void _clp_initialize(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("threadpool.initialize",base);
//
    line(53);
    line(55);
    push_symbol(base+0);//this
    array(0);
    _o_method_threads.eval(2);
    pop();
    line(56);
    push_symbol(base+0);//this
    array(0);
    _o_method_jobs.eval(2);
    pop();
    line(57);
    push_symbol(base+0);//this
    push(&ZERO);
    _o_method_active.eval(2);
    pop();
    line(59);
    push_symbol(base+0);//this
    _clp_thread_mutex_init(0);
    _o_method_slpmutx.eval(2);
    pop();
    line(60);
    push_symbol(base+0);//this
    _clp_thread_mutex_init(0);
    _o_method_jobmutx.eval(2);
    pop();
    line(61);
    push_symbol(base+0);//this
    _clp_thread_cond_init(0);
    _o_method_jobcond.eval(2);
    pop();
    line(62);
    push_symbol(base+0);//this
    _clp_thread_mutex_init(0);
    _o_method_actmutx.eval(2);
    pop();
    line(63);
    push_symbol(base+0);//this
    _clp_thread_cond_init(0);
    _o_method_actcond.eval(2);
    pop();
    line(64);
    push_symbol(base+0);//this
    _clp_thread_mutex_init(0);
    _o_method_thrmutx.eval(2);
    pop();
    line(65);
    push_symbol(base+0);//this
    _clp_thread_cond_init(0);
    _o_method_thrcond.eval(2);
    pop();
    line(69);
    {
    line(67);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_1_0:
    push_symbol(base+1);//number_of_threads
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(68);
        push_symbol(base+0);//this
        _o_method_addthread.eval(1);
        pop();
    lab_1_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_1_0;
    lab_1_2:;
    }
    line(71);
    push_symbol(base+0);//this
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace threadpool
//=======================================================================
namespace _nsp_threadpool{
static void _clp_addthread(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("threadpool.addthread",base);
//
    line(76);
    block(_blk_addthread_0,0);
    push_symbol(base+0);//this
    _clp_thread_create(2);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_addthread_0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("threadpool._blk_addthread_0",base);
//
    push_symbol(base+1);//t
    _clp_thread(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
}//namespace threadpool
//=======================================================================
namespace _nsp_threadpool{
static void _clp_numthreads(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("threadpool.numthreads",base);
//
    line(81);
    line(82);
    push_symbol(base+0);//this
    _o_method_thrmutx.eval(1);
    _clp_thread_mutex_lock(1);
    pop();
    line(83);
    push_symbol(base+0);//this
    _o_method_threads.eval(1);
    _clp_len(1);
    assign(base+1);//num
    pop();
    line(84);
    push_symbol(base+0);//this
    _o_method_thrmutx.eval(1);
    _clp_thread_mutex_unlock(1);
    pop();
    line(85);
    push_symbol(base+1);//num
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace threadpool
//=======================================================================
namespace _nsp_threadpool{
static void _clp_addjob(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("threadpool.addjob",base);
//
    line(90);
    push_symbol(base+0);//this
    _o_method_jobmutx.eval(1);
    _clp_thread_mutex_lock(1);
    pop();
    line(91);
    push_symbol(base+0);//this
    _o_method_jobs.eval(1);
    push_symbol(base+1);//job
    _clp_aadd(2);
    pop();
    line(92);
    push_symbol(base+0);//this
    _o_method_jobmutx.eval(1);
    _clp_thread_mutex_unlock(1);
    pop();
    line(93);
    push_symbol(base+0);//this
    _o_method_jobcond.eval(1);
    _clp_thread_cond_signal(1);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace threadpool
//=======================================================================
namespace _nsp_threadpool{
static void _clp_lenjobs(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("threadpool.lenjobs",base);
//
    line(98);
    line(99);
    push_symbol(base+0);//this
    _o_method_jobmutx.eval(1);
    _clp_thread_mutex_lock(1);
    pop();
    line(100);
    push_symbol(base+0);//this
    _o_method_jobs.eval(1);
    _clp_len(1);
    assign(base+1);//len
    pop();
    line(101);
    push_symbol(base+0);//this
    _o_method_jobmutx.eval(1);
    _clp_thread_mutex_unlock(1);
    pop();
    line(102);
    push_symbol(base+1);//len
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace threadpool
//=======================================================================
namespace _nsp_threadpool{
static void _clp_actjobs(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("threadpool.actjobs",base);
//
    line(107);
    line(108);
    push_symbol(base+0);//this
    _o_method_actmutx.eval(1);
    _clp_thread_mutex_lock(1);
    pop();
    line(109);
    push_symbol(base+0);//this
    _o_method_active.eval(1);
    assign(base+1);//act
    pop();
    line(110);
    push_symbol(base+0);//this
    _o_method_actmutx.eval(1);
    _clp_thread_mutex_unlock(1);
    pop();
    line(111);
    push_symbol(base+1);//act
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace threadpool
//=======================================================================
namespace _nsp_threadpool{
static void _clp_wait(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("threadpool.wait",base);
//
    line(124);
    push(&TRUE);
    assign(base+1);//wait
    pop();
    line(143);
    lab_2_1:
    line(127);
    push_symbol(base+1);//wait
    if(!flag()) goto lab_2_2;
        line(129);
        push_symbol(base+0);//this
        _o_method_actmutx.eval(1);
        _clp_thread_mutex_lock(1);
        pop();
        line(133);
        lab_3_1:
        line(130);
        push_symbol(base+0);//this
        _o_method_active.eval(1);
        push(&ZERO);
        gt();
        cmp_1677:;
        if(!flag()) goto lab_3_2;
            line(132);
            push_symbol(base+0);//this
            _o_method_actcond.eval(1);
            push_symbol(base+0);//this
            _o_method_actmutx.eval(1);
            _clp_thread_cond_wait(2);
            pop();
        goto lab_3_1;
        lab_3_2:;
        line(141);
        line(134);
        push_symbol(base+0);//this
        _o_method_jobmutx.eval(1);
        _clp_thread_mutex_trylock(1);
        push(&ZERO);
        eqeq();
        cmp_1735:;
        if(!flag()) goto if_4_1;
            line(139);
            line(136);
            push_symbol(base+0);//this
            _o_method_jobs.eval(1);
            _clp_len(1);
            push(&ZERO);
            eqeq();
            cmp_1762:;
            if(!flag()) goto if_5_1;
                line(138);
                push(&FALSE);
                assign(base+1);//wait
                pop();
            if_5_1:
            if_5_0:;
            line(140);
            push_symbol(base+0);//this
            _o_method_jobmutx.eval(1);
            _clp_thread_mutex_unlock(1);
            pop();
        if_4_1:
        if_4_0:;
        line(142);
        push_symbol(base+0);//this
        _o_method_actmutx.eval(1);
        _clp_thread_mutex_unlock(1);
        pop();
    goto lab_2_1;
    lab_2_2:;
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace threadpool
//=======================================================================
namespace _nsp_threadpool{
static void _clp_wait_job(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("threadpool.wait_job",base);
//
    if( ((base+1)->type==TYPE_NIL)||
       (((base+1)->type==TYPE_REF)&&
        ((base+1)->data.vref->value.type==TYPE_NIL))){
    line(147);
    push(&ZERO);
    assign(base+1);//lwm
    pop();
    }
    line(152);
    push_symbol(base+0);//this
    _o_method_jobmutx.eval(1);
    _clp_thread_mutex_lock(1);
    pop();
    line(155);
    lab_6_1:
    line(153);
    push_symbol(base+0);//this
    _o_method_jobs.eval(1);
    _clp_len(1);
    push_symbol(base+1);//lwm
    gt();
    cmp_1905:;
    if(!flag()) goto lab_6_2;
        line(154);
        push_symbol(base+0);//this
        _o_method_jobcond.eval(1);
        push_symbol(base+0);//this
        _o_method_jobmutx.eval(1);
        _clp_thread_cond_wait(2);
        pop();
    goto lab_6_1;
    lab_6_2:;
    line(156);
    push_symbol(base+0);//this
    _o_method_jobmutx.eval(1);
    _clp_thread_mutex_unlock(1);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace threadpool
//=======================================================================
namespace _nsp_threadpool{
static void _clp_wait_act(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("threadpool.wait_act",base);
//
    if( ((base+1)->type==TYPE_NIL)||
       (((base+1)->type==TYPE_REF)&&
        ((base+1)->data.vref->value.type==TYPE_NIL))){
    line(160);
    push(&ZERO);
    assign(base+1);//lwm
    pop();
    }
    line(165);
    push_symbol(base+0);//this
    _o_method_actmutx.eval(1);
    _clp_thread_mutex_lock(1);
    pop();
    line(168);
    lab_7_1:
    line(166);
    push_symbol(base+0);//this
    _o_method_active.eval(1);
    push_symbol(base+1);//lwm
    gt();
    cmp_2019:;
    if(!flag()) goto lab_7_2;
        line(167);
        push_symbol(base+0);//this
        _o_method_actcond.eval(1);
        push_symbol(base+0);//this
        _o_method_actmutx.eval(1);
        _clp_thread_cond_wait(2);
        pop();
    goto lab_7_1;
    lab_7_2:;
    line(169);
    push_symbol(base+0);//this
    _o_method_actmutx.eval(1);
    _clp_thread_mutex_unlock(1);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace threadpool
//=======================================================================
namespace _nsp_threadpool{
static void _clp_exit(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("threadpool.exit",base);
//
    if( ((base+1)->type==TYPE_NIL)||
       (((base+1)->type==TYPE_REF)&&
        ((base+1)->data.vref->value.type==TYPE_NIL))){
    line(173);
    push(&ZERO);
    assign(base+1);//lwm
    pop();
    }
    line(179);
    push_symbol(base+0);//this
    _o_method_thrmutx.eval(1);
    _clp_thread_mutex_lock(1);
    pop();
    line(183);
    lab_8_1:
    line(180);
    push_symbol(base+0);//this
    _o_method_threads.eval(1);
    _clp_len(1);
    push_symbol(base+1);//lwm
    gt();
    cmp_2141:;
    if(!flag()) goto lab_8_2;
        line(181);
        push_symbol(base+0);//this
        push(&NIL);
        _o_method_addjob.eval(2);
        pop();
        line(182);
        push_symbol(base+0);//this
        _o_method_thrcond.eval(1);
        push_symbol(base+0);//this
        _o_method_thrmutx.eval(1);
        _clp_thread_cond_wait(2);
        pop();
    goto lab_8_1;
    lab_8_2:;
    line(184);
    push_symbol(base+0);//this
    _o_method_thrmutx.eval(1);
    _clp_thread_mutex_unlock(1);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace threadpool
//=======================================================================
static void _clp_thread(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("thread",base);
//
    line(189);
    line(191);
    push_symbol(base+0);//this
    _o_method_thrmutx.eval(1);
    _clp_thread_mutex_lock(1);
    pop();
    line(192);
    push_symbol(base+0);//this
    _o_method_threads.eval(1);
    _clp_thread_self(0);
    _clp_aadd(2);
    pop();
    line(193);
    push_symbol(base+0);//this
    _o_method_thrmutx.eval(1);
    _clp_thread_mutex_unlock(1);
    pop();
    line(243);
    lab_9_1:
    line(200);
    push(&TRUE);
    if(!flag()) goto lab_9_2;
        line(201);
        push_symbol(base+0);//this
        _o_method_slpmutx.eval(1);
        _clp_thread_mutex_lock(1);
        pop();
        line(204);
        push_symbol(base+0);//this
        _o_method_jobmutx.eval(1);
        _clp_thread_mutex_lock(1);
        pop();
        line(207);
        lab_10_1:
        line(205);
        push(&ONE);
        push_symbol(base+0);//this
        _o_method_jobs.eval(1);
        _clp_len(1);
        gt();
        cmp_2363:;
        if(!flag()) goto lab_10_2;
            line(206);
            push_symbol(base+0);//this
            _o_method_jobcond.eval(1);
            push_symbol(base+0);//this
            _o_method_jobmutx.eval(1);
            _clp_thread_cond_wait(2);
            pop();
        goto lab_10_1;
        lab_10_2:;
        line(208);
        push_symbol(base+0);//this
        _o_method_actmutx.eval(1);
        _clp_thread_mutex_lock(1);
        pop();
        line(209);
        push_symbol(base+0);//this
        _o_method_active.eval(1);
        dup();
        push(&ONE);
        add();
        push_symbol(base+0);//this
        swap();
        _o_method_active.eval(2);
        pop();
        pop();
        line(210);
        push_symbol(base+0);//this
        _o_method_actmutx.eval(1);
        _clp_thread_mutex_unlock(1);
        pop();
        line(211);
        push_symbol(base+0);//this
        _o_method_jobs.eval(1);
        idxr0(1);
        assign(base+1);//job
        pop();
        line(212);
        push_symbol(base+0);//this
        _o_method_jobs.eval(1);
        push(&ONE);
        _clp_adel(2);
        pop();
        line(213);
        push_symbol(base+0);//this
        _o_method_jobs.eval(1);
        push_symbol(base+0);//this
        _o_method_jobs.eval(1);
        _clp_len(1);
        addnum(-1);
        _clp_asize(2);
        pop();
        line(214);
        push_symbol(base+0);//this
        _o_method_jobmutx.eval(1);
        _clp_thread_mutex_unlock(1);
        pop();
        line(215);
        push_symbol(base+0);//this
        _o_method_jobcond.eval(1);
        _clp_thread_cond_signal(1);
        pop();
        line(217);
        push_symbol(base+0);//this
        _o_method_slpmutx.eval(1);
        _clp_thread_mutex_unlock(1);
        pop();
        line(231);
        line(219);
        push_symbol(base+1);//job
        push(&NIL);
        eqeq();
        cmp_2606:;
        if(!flag()) goto if_11_1;
            line(221);
            push_symbol(base+0);//this
            _o_method_thrmutx.eval(1);
            _clp_thread_mutex_lock(1);
            pop();
            line(222);
            push_symbol(base+0);//this
            _o_method_threads.eval(1);
            _clp_thread_self(0);
            _clp_ascan(2);
            assign(base+2);//x
            pop();
            line(223);
            push_symbol(base+0);//this
            _o_method_threads.eval(1);
            push_symbol(base+2);//x
            _clp_adel(2);
            pop();
            line(224);
            push_symbol(base+0);//this
            _o_method_threads.eval(1);
            push_symbol(base+0);//this
            _o_method_threads.eval(1);
            _clp_len(1);
            addnum(-1);
            _clp_asize(2);
            pop();
            line(225);
            push_symbol(base+0);//this
            _o_method_thrmutx.eval(1);
            _clp_thread_mutex_unlock(1);
            pop();
            line(226);
            push_symbol(base+0);//this
            _o_method_thrcond.eval(1);
            _clp_thread_cond_signal(1);
            pop();
        goto if_11_0;
        if_11_1:
        line(227);
            line(230);
            push_symbol(base+1);//job
            idxr0(1);
            push_symbol(base+1);//job
            number(2);
            push(&NIL);
            slice();
            _clp_evalarray(2);
            pop();
        if_11_2:
        if_11_0:;
        line(233);
        push_symbol(base+0);//this
        _o_method_actmutx.eval(1);
        _clp_thread_mutex_lock(1);
        pop();
        line(234);
        push_symbol(base+0);//this
        _o_method_active.eval(1);
        dup();
        push(&ONE);
        sub();
        push_symbol(base+0);//this
        swap();
        _o_method_active.eval(2);
        pop();
        pop();
        line(235);
        push_symbol(base+0);//this
        _o_method_actmutx.eval(1);
        _clp_thread_mutex_unlock(1);
        pop();
        line(236);
        push_symbol(base+0);//this
        _o_method_actcond.eval(1);
        _clp_thread_cond_signal(1);
        pop();
        line(242);
        line(238);
        push_symbol(base+1);//job
        push(&NIL);
        eqeq();
        cmp_2888:;
        if(!flag()) goto if_12_1;
            line(239);
            goto lab_9_2;//exit
        goto if_12_0;
        if_12_1:
        line(240);
            line(241);
            push(&NIL);
            assign(base+1);//job
            pop();
        if_12_2:
        if_12_0:;
    goto lab_9_1;
    lab_9_2:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

