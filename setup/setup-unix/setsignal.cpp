//input: ppo/setsignal.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_setsignal(int argno);
extern void _clp_signal_getpend(int argno);
extern void _clp_signal_lock(int argno);
extern void _clp_signal_raise(int argno);
extern void _clp_signal_unlock(int argno);

//=======================================================================
void _clp_setsignal(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("setsignal",base);
//
    line(26);
    line(38);
    line(28);
    push_symbol(base+0);//onoff
    push(&FALSE);
    eqeq();
    cmp_36:;
    if(!flag()) goto if_1_1;
        line(30);
        _clp_signal_lock(0);
        assign(base+1);//level
        pop();
    goto if_1_0;
    if_1_1:
    line(32);
    push_symbol(base+0);//onoff
    push(&TRUE);
    eqeq();
    cmp_67:;
    if(!flag()) goto if_1_2;
        line(34);
        _clp_signal_unlock(0);
        assign(base+1);//level
        pop();
        line(37);
        line(35);
        push(&ZERO);
        push_symbol(base+1);//level
        eqeq();
        cmp_96:;
        if(!flag()) goto if_2_1;
            line(36);
            _clp_signal_getpend(0);
            _clp_signal_raise(1);
            pop();
        if_2_1:
        if_2_0:;
    if_1_2:
    if_1_0:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

