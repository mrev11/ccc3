//input: ppo/runchild.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_fdup(int argno);
extern void _clp_pipe(int argno);
extern void _clp_runchild(int argno);
extern void _clp_spawn(int argno);
extern void _clp_split(int argno);
extern void _clp_strtran(int argno);
extern void _clp_thread_mutex_init(int argno);
extern void _clp_thread_mutex_lock(int argno);
extern void _clp_thread_mutex_unlock(int argno);
extern void _clp_valtype(int argno);

//=======================================================================
void _clp_runchild(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+9)PUSHNIL();
argno=2;
push_call("runchild",base);
//
    line(8);
    static stvar _st_mutex_fd;
    static int _ini_mutex_fd=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex_fd.ptr);
        pop();
        return 1;
    }();
    line(10);
    line(11);
    line(12);
    line(20);
    line(14);
    push_symbol(base+0);//cmd
    _clp_valtype(1);
    string(L"C");
    eqeq();
    cmp_96:;
    if(!flag()) goto if_1_1;
        line(18);
        lab_2_1:
        line(16);
        string(L"  ");
        push_symbol(base+0);//cmd
        ss();
        if(!flag()) goto lab_2_2;
            line(17);
            push_symbol(base+0);//cmd
            string(L"  ");
            string(L" ");
            _clp_strtran(3);
            assign(base+0);//cmd
            pop();
        goto lab_2_1;
        lab_2_2:;
        line(19);
        push_symbol(base+0);//cmd
        string(L" ");
        _clp_split(2);
        assign(base+0);//cmd
        pop();
    if_1_1:
    if_1_0:;
    line(22);
    push_symbol(_st_mutex_fd.ptr);//runchild
    _clp_thread_mutex_lock(1);
    pop();
    line(24);
    _clp_pipe(0);
    assign(base+2);//p1
    pop();
    line(25);
    _clp_pipe(0);
    assign(base+3);//p2
    pop();
    line(27);
    push_symbol(base+2);//p1
    idxr0(1);
    push(&FALSE);
    push(&TRUE);
    _clp_fdup(3);
    assign(base+7);//pr
    pop();
    line(28);
    push_symbol(base+3);//p2
    idxr0(2);
    push(&FALSE);
    push(&TRUE);
    _clp_fdup(3);
    assign(base+8);//pw
    pop();
    line(30);
    push(&ZERO);
    push(&FALSE);
    _clp_fdup(2);
    assign(base+4);//fd0
    pop();
    push_symbol(base+3);//p2
    idxr0(1);
    push(&ZERO);
    push(&TRUE);
    _clp_fdup(3);
    pop();
    line(31);
    push(&ONE);
    push(&FALSE);
    _clp_fdup(2);
    assign(base+5);//fd1
    pop();
    push_symbol(base+2);//p1
    idxr0(2);
    push(&ONE);
    push(&TRUE);
    _clp_fdup(3);
    pop();
    line(32);
    number(2);
    push(&FALSE);
    _clp_fdup(2);
    assign(base+6);//fd2
    pop();
    push(&ONE);
    number(2);
    _clp_fdup(2);
    pop();
    line(34);
    number(2);
    push_symbol(base+0);//cmd
    _clp_spawn(2);
    assign(base+1);//pid
    pop();
    line(36);
    push_symbol(base+4);//fd0
    push(&ZERO);
    push(&TRUE);
    _clp_fdup(3);
    pop();
    line(37);
    push_symbol(base+5);//fd1
    push(&ONE);
    push(&TRUE);
    _clp_fdup(3);
    pop();
    line(38);
    push_symbol(base+6);//fd2
    number(2);
    push(&TRUE);
    _clp_fdup(3);
    pop();
    line(40);
    push_symbol(_st_mutex_fd.ptr);//runchild
    _clp_thread_mutex_unlock(1);
    pop();
    line(42);
    push_symbol(base+7);//pr
    push_symbol(base+8);//pw
    array(2);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

