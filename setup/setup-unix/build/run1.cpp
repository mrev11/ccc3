//input: ppo/run1.ppo (5.7.0.1)

#include <cccdef.h>

extern void _clp_alltrim(int argno);
extern void _clp_at(int argno);
static void _clp_bash(int argno);
extern void _clp_ferase(int argno);
extern void _clp_file(int argno);
extern void _clp_memoread(int argno);
extern void _clp_qqout(int argno);
extern void _clp_run(int argno);
extern void _clp_run1(int argno);
extern void _clp_s_dry(int argno);
extern void _clp_s_runcnt(int argno);
extern void _clp_spawn(int argno);
extern void _clp_str(int argno);
extern void _clp_strtran(int argno);
extern void _clp_thread_mutex_init(int argno);
extern void _clp_thread_mutex_lock(int argno);
extern void _clp_thread_mutex_unlock(int argno);

//=======================================================================
void _clp_run1(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+4)PUSHNIL();
argno=1;
push_call("run1",base);
//
    line(26);
    static stvar _st_mutex_out;
    static int _ini_mutex_out=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex_out.ptr);
        pop();
        return 1;
    }();
    line(27);
    static stvar _st_count((double)0);
    line(28);
    line(29);
    _clp_s_runcnt(0);
    assign(base+3);//runcnt
    pop();
    line(31);
    push_symbol(base+3);//runcnt
    addnum(1);
    _clp_s_runcnt(1);
    pop();
    line(63);
    line(33);
    _clp_s_dry(0);
    topnot();
    if(!flag()) goto if_1_1;
        line(35);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_lock(1);
        pop();
        line(36);
        string(L"log-runtmp");
        push_symbol(_st_count.ptr);//run1
        push(&ONE);
        add();
        assign(_st_count.ptr);//run1
        _clp_str(1);
        _clp_alltrim(1);
        add();
        assign(base+1);//runtmp
        pop();
        line(37);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_unlock(1);
        pop();
        line(40);
        push_symbol(base+0);//cmd
        string(L" >");
        add();
        push_symbol(base+1);//runtmp
        add();
        _clp_run(1);
        pop();
        line(46);
        push_symbol(base+1);//runtmp
        _clp_memoread(1);
        assign(base+2);//out
        pop();
        line(47);
        push_symbol(base+1);//runtmp
        _clp_ferase(1);
        pop();
        line(49);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_lock(1);
        pop();
        line(50);
        push_symbol(base+2);//out
        _clp_qqout(1);
        pop();
        line(51);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_unlock(1);
        pop();
        line(62);
        line(53);
        string(L"error");
        _clp_file(1);
        if(!flag()) goto if_2_1;
            line(55);
            string(L"cat error");
            _clp_run(1);
            pop();
            line(61);
            push(&TRUE);
            _clp_s_dry(1);
            pop();
        if_2_1:
        if_2_0:;
    if_1_1:
    if_1_0:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_bash(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("bash",base);
//
    line(68);
    push_symbol(base+0);//cmd
    string(L"\\");
    string(L"/");
    _clp_strtran(3);
    assign(base+0);//cmd
    pop();
    line(71);
    line(69);
    string(L":/");
    push_symbol(base+0);//cmd
    _clp_at(2);
    number(2);
    eqeq();
    cmp_395:;
    if(!flag()) goto if_3_1;
        line(70);
        string(L"/");
        push_symbol(base+0);//cmd
        idxr0(1);
        add();
        push_symbol(base+0);//cmd
        number(3);
        push(&NIL);
        slice();
        add();
        assign(base+0);//cmd
        pop();
    if_3_1:
    if_3_0:;
    line(72);
    number(3);
    string(L"bash.exe");
    string(L"-c");
    string(L"\"");
    push_symbol(base+0);//cmd
    add();
    string(L"\"");
    add();
    _clp_spawn(4);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

