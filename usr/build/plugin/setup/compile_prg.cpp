//input: ppo/compile_prg.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_compile_prg(int argno);
extern void _clp_def_quit(int argno);
extern void _clp_dirmake(int argno);
extern void _clp_ferase(int argno);
extern void _clp_memoread(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_run(int argno);

//=======================================================================
void _clp_compile_prg(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("compile_prg",base);
//
    line(8);
    line(11);
    push_symbol(base+1);//env
    string(L"TARGET");
    string(L"ppo/");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    string(L".ppo");
    add();
    _clp_pluginenv(3);
    pop();
    line(12);
    push_symbol(base+1);//env
    string(L"OUT");
    string(L"out--prg2ppo-");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(13);
    push_symbol(base+1);//env
    string(L"ERR");
    string(L"error--prg2ppo-");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(15);
    push_symbol(base+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(16);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(17);
    push_symbol(base+1);//env
    string(L"ERR");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(19);
    string(L"ppo");
    _clp_dirmake(1);
    pop();
    line(21);
    string(L"prg2ppo.exe ");
    push_symbol(base+1);//env
    string(L"SOURCE");
    _clp_pluginenv(2);
    add();
    string(L" -o");
    add();
    push_symbol(base+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    add();
    string(L" @");
    add();
    push_symbol(base+1);//env
    string(L"CMPOPT");
    _clp_pluginenv(2);
    add();
    string(L" >");
    add();
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    add();
    assign(base+2);//cmd
    pop();
    line(22);
    push_symbol(base+2);//cmd
    _clp_run(1);
    pop();
    line(26);
    line(24);
    string(L"Number of translate rules");
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    ss();
    topnot();
    if(!flag()) goto if_1_1;
        line(25);
        push_symbol(base+0);//arg
        push_symbol(base+1);//env
        push(&ONE);
        _clp_def_quit(3);
        pop();
    if_1_1:
    if_1_0:;
    line(28);
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

