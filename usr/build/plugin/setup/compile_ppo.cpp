//input: ppo/compile_ppo.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_compile_ppo(int argno);
extern void _clp_def_quit(int argno);
extern void _clp_empty(int argno);
extern void _clp_ferase(int argno);
extern void _clp_memoread(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_run(int argno);

//=======================================================================
void _clp_compile_ppo(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("compile_ppo",base);
//
    line(7);
    line(9);
    push_symbol(base+1);//env
    string(L"SOURCE");
    string(L"ppo/");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    string(L".ppo");
    add();
    _clp_pluginenv(3);
    pop();
    line(10);
    push_symbol(base+1);//env
    string(L"TARGET");
    string(L"ppo/");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    string(L".cpp");
    add();
    _clp_pluginenv(3);
    pop();
    line(11);
    push_symbol(base+1);//env
    string(L"OUT");
    string(L"out--ppo2cpp-");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(12);
    push_symbol(base+1);//env
    string(L"ERR");
    string(L"error--ppo2cpp-");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(14);
    push_symbol(base+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(15);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(16);
    push_symbol(base+1);//env
    string(L"ERR");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(18);
    string(L"ppo2cpp.exe -q ");
    push_symbol(base+1);//env
    string(L"SOURCE");
    _clp_pluginenv(2);
    add();
    string(L" 2>");
    add();
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    add();
    assign(base+2);//cmd
    pop();
    line(19);
    push_symbol(base+2);//cmd
    _clp_run(1);
    pop();
    line(23);
    line(21);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_1_1;
        line(22);
        push_symbol(base+0);//arg
        push_symbol(base+1);//env
        push(&ONE);
        _clp_def_quit(3);
        pop();
    if_1_1:
    if_1_0:;
    line(25);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

