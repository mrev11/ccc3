//input: ppo/run1.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_alltrim(int argno);
extern void _clp_at(int argno);
static void _clp_bash(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_fclose(int argno);
extern void _clp_ferase(int argno);
extern void _clp_file(int argno);
extern void _clp_memoread(int argno);
extern void _clp_qqout(int argno);
extern void _clp_readlinenew(int argno);
extern void _clp_run(int argno);
extern void _clp_run1(int argno);
static void _clp_runch(int argno);
extern void _clp_runchild(int argno);
extern void _clp_s_batext(int argno);
extern void _clp_s_dry(int argno);
extern void _clp_s_runcnt(int argno);
extern void _clp_spawn(int argno);
extern void _clp_str(int argno);
extern void _clp_strtran(int argno);
extern void _clp_thread_mutex_init(int argno);
extern void _clp_thread_mutex_lock(int argno);
extern void _clp_thread_mutex_unlock(int argno);

class _method6_readline: public _method6_{public: _method6_readline():_method6_("readline"){};}; static _method6_readline _o_method_readline;

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
    line(69);
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
        line(53);
        line(39);
        _clp_dirsep(0);
        string(L"/");
        eqeq();
        cmp_183:;
        if(!flag()) goto if_2_1;
            line(41);
            push_symbol(base+0);//cmd
            _clp_runch(1);
            assign(base+2);//out
            pop();
        goto if_2_0;
        if_2_1:
        line(43);
        _clp_s_batext(0);
        string(L".bld");
        eqeq();
        cmp_222:;
        if(!flag()) goto if_2_2;
            line(45);
            push_symbol(base+0);//cmd
            string(L" >");
            add();
            push_symbol(base+1);//runtmp
            add();
            _clp_bash(1);
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
        goto if_2_0;
        if_2_2:
        line(49);
            line(51);
            push_symbol(base+0);//cmd
            string(L"/");
            string(L"\\");
            _clp_strtran(3);
            assign(base+0);//cmd
            pop();
            line(52);
            push_symbol(base+0);//cmd
            _clp_runch(1);
            assign(base+2);//out
            pop();
        if_2_3:
        if_2_0:;
        line(55);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_lock(1);
        pop();
        line(56);
        push_symbol(base+2);//out
        _clp_qqout(1);
        pop();
        line(57);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_unlock(1);
        pop();
        line(68);
        line(59);
        string(L"error");
        _clp_file(1);
        if(!flag()) goto if_3_1;
            line(63);
            string(L"type error");
            _clp_run(1);
            pop();
            line(67);
            push(&TRUE);
            _clp_s_dry(1);
            pop();
        if_3_1:
        if_3_0:;
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
    line(74);
    push_symbol(base+0);//cmd
    string(L"\\");
    string(L"/");
    _clp_strtran(3);
    assign(base+0);//cmd
    pop();
    line(77);
    line(75);
    string(L":/");
    push_symbol(base+0);//cmd
    _clp_at(2);
    number(2);
    eqeq();
    cmp_509:;
    if(!flag()) goto if_4_1;
        line(76);
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
    if_4_1:
    if_4_0:;
    line(78);
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
static void _clp_runch(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+6)PUSHNIL();
argno=1;
push_call("runch",base);
//
    line(84);
    line(85);
    binary("");
    assign(base+5);//result
    pop();
    line(87);
    push_symbol(base+0);//cmd
    _clp_runchild(1);
    dup();
    idxr0nil(2);
    assign(base+1);//pw
    pop();
    dup();
    idxr0nil(1);
    assign(base+2);//pr
    pop();
    pop();
    line(88);
    push_symbol(base+1);//pw
    _clp_fclose(1);
    pop();
    line(90);
    push_symbol(base+2);//pr
    _clp_readlinenew(1);
    assign(base+3);//rl
    pop();
    line(93);
    lab_5_1:
    line(91);
    push_symbol(base+3);//rl
    _o_method_readline.eval(1);
    assign(base+4);//line
    push(&NIL);
    neeq();
    cmp_727:;
    if(!flag()) goto lab_5_2;
        line(92);
        push_symbol(base+5);//result
        push_symbol(base+4);//line
        add();
        assign(base+5);//result
        pop();
    goto lab_5_1;
    lab_5_2:;
    line(94);
    push_symbol(base+2);//pr
    _clp_fclose(1);
    pop();
    line(100);
    push_symbol(base+5);//result
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

