//input: ppo/def_quit.ppo (5.7.2)

#include <cccdef.h>

extern void _clp___quit(int argno);
extern void _clp_def_quit(int argno);
extern void _clp_errorlevel(int argno);
extern void _clp_ferase(int argno);
extern void _clp_frename(int argno);
extern void _clp_memoread(int argno);
extern void _clp_memowrit(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);

//=======================================================================
void _clp_def_quit(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("def_quit",base);
//
    line(14);
    line(10);
    push_symbol(base+2);//code
    push(&ZERO);
    gt();
    cmp_36:;
    if(!flag()) goto if_1_1;
        line(11);
        string(L"error");
        string(L"");
        _clp_memowrit(2);
        pop();
        line(12);
        push_symbol(base+1);//env
        string(L"OUT");
        _clp_pluginenv(2);
        push_symbol(base+1);//env
        string(L"ERR");
        _clp_pluginenv(2);
        _clp_frename(2);
        pop();
        line(13);
        push_symbol(base+1);//env
        string(L"ERR");
        _clp_pluginenv(2);
        _clp_memoread(1);
        _clp_qout(1);
        pop();
    if_1_1:
    if_1_0:;
    line(16);
    string(L"----------------------------------------------------------------");
    _clp_qqout(1);
    pop();
    _clp_qout(0);
    pop();
    line(18);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(20);
    push_symbol(base+2);//code
    _clp_errorlevel(1);
    pop();
    line(21);
    _clp___quit(0);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

