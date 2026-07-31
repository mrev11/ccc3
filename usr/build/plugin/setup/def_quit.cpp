//input: ppo/def_quit.ppo (5.7.2)

#include <cccdef.h>

extern void _clp___quit(int argno);
extern void _clp_chr(int argno);
extern void _clp_def_quit(int argno);
extern void _clp_errorlevel(int argno);
extern void _clp_ferase(int argno);
extern void _clp_frename(int argno);
extern void _clp_memoread(int argno);
extern void _clp_memowrit(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);
extern void _clp_right(int argno);

//=======================================================================
void _clp_def_quit(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+4)PUSHNIL();
argno=3;
push_call("def_quit",base);
//
    line(9);
    line(18);
    line(11);
    push_symbol(base+2);//code
    push(&ZERO);
    gt();
    cmp_44:;
    if(!flag()) goto if_1_1;
        line(12);
        string(L"error");
        string(L"");
        _clp_memowrit(2);
        pop();
        line(13);
        push_symbol(base+1);//env
        string(L"OUT");
        _clp_pluginenv(2);
        push_symbol(base+1);//env
        string(L"ERR");
        _clp_pluginenv(2);
        _clp_frename(2);
        pop();
        line(14);
        push_symbol(base+1);//env
        string(L"ERR");
        _clp_pluginenv(2);
        _clp_memoread(1);
        assign(base+3);//memo
        _clp_qout(1);
        pop();
        line(17);
        line(15);
        push_symbol(base+3);//memo
        push(&ONE);
        _clp_right(2);
        number(10);
        _clp_chr(1);
        neeq();
        cmp_183:;
        if(!flag()) goto if_2_1;
            line(16);
            _clp_qout(0);
            pop();
        if_2_1:
        if_2_0:;
    if_1_1:
    if_1_0:;
    line(20);
    string(L"----------------------------------------------------------------");
    _clp_qqout(1);
    pop();
    _clp_qout(0);
    pop();
    line(22);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(24);
    push_symbol(base+2);//code
    _clp_errorlevel(1);
    pop();
    line(25);
    _clp___quit(0);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

