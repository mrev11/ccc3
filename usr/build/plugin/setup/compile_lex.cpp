//input: ppo/compile_lex.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_compile_lex(int argno);
extern void _clp_def_quit(int argno);
extern void _clp_dirmake(int argno);
extern void _clp_empty(int argno);
extern void _clp_ferase(int argno);
extern void _clp_memoread(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_run(int argno);

//=======================================================================
void _clp_compile_lex(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("compile_lex",base);
//
    line(7);
    line(9);
    push_symbol(base+1);//env
    string(L"SOURCE");
    push_symbol(base+0);//arg
    idxr0(2);
    string(L"/");
    add();
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    string(L".lex");
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
    string(L"out--lex2cpp-");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(12);
    push_symbol(base+1);//env
    string(L"ERR");
    string(L"error--lex2cpp-");
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
    string(L"ppo");
    _clp_dirmake(1);
    pop();
    line(20);
    string(L"flex.exe ");
    push_symbol(base+1);//env
    string(L"BUILD_LEX");
    _clp_pluginenv(2);
    add();
    string(L" -oppo/");
    add();
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    string(L".cpp ");
    add();
    push_symbol(base+1);//env
    string(L"SOURCE");
    _clp_pluginenv(2);
    add();
    string(L" >");
    add();
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    add();
    string(L" 2>&1");
    add();
    assign(base+2);//cmd
    pop();
    line(21);
    push_symbol(base+2);//cmd
    _clp_run(1);
    pop();
    line(25);
    line(23);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_1_1;
        line(24);
        push_symbol(base+0);//arg
        push_symbol(base+1);//env
        push(&ONE);
        _clp_def_quit(3);
        pop();
    if_1_1:
    if_1_0:;
    line(27);
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

