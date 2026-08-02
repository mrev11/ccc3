//input: ppo/compile_tdc.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_compile_tdc(int argno);
extern void _clp_def_quit(int argno);
extern void _clp_dirchange(int argno);
extern void _clp_dirmake(int argno);
extern void _clp_empty(int argno);
extern void _clp_fclose(int argno);
extern void _clp_ferase(int argno);
extern void _clp_filecopy(int argno);
extern void _clp_fopen(int argno);
extern void _clp_memoread(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_runredir(int argno);

//=======================================================================
void _clp_compile_tdc(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("compile_tdc",base);
//
    line(8);
    line(9);
    line(11);
    push_symbol(base+1);//env
    string(L"SOURCE");
    push_symbol(base+0);//arg
    idxr0(2);
    string(L"/");
    add();
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    string(L".tdc");
    add();
    _clp_pluginenv(3);
    pop();
    line(12);
    push_symbol(base+1);//env
    string(L"TARGET");
    string(L"ppo/");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    string(L".prg");
    add();
    _clp_pluginenv(3);
    pop();
    line(13);
    push_symbol(base+1);//env
    string(L"OUT");
    string(L"out--tdc2prg-");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(14);
    push_symbol(base+1);//env
    string(L"ERR");
    string(L"error--tdc2prg-");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(16);
    push_symbol(base+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(17);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(18);
    push_symbol(base+1);//env
    string(L"ERR");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(20);
    string(L"ppo");
    _clp_dirmake(1);
    pop();
    line(21);
    push_symbol(base+1);//env
    string(L"SOURCE");
    _clp_pluginenv(2);
    string(L"ppo/");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    string(L".tdc");
    add();
    _clp_filecopy(2);
    pop();
    line(22);
    string(L"ppo");
    _clp_dirchange(1);
    pop();
    line(23);
    string(L"tdc2prg.exe ");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    string(L".tdc");
    add();
    assign(base+2);//cmd
    pop();
    line(25);
    string(L"../");
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    add();
    number(770);
    _clp_fopen(2);
    assign(base+3);//fdout
    pop();
    line(26);
    push_symbol(base+2);//cmd
    push_symbol(base+3);//fdout
    push_symbol(base+3);//fdout
    _clp_runredir(3);
    pop();
    line(27);
    push_symbol(base+3);//fdout
    _clp_fclose(1);
    pop();
    line(28);
    string(L"..");
    _clp_dirchange(1);
    pop();
    line(32);
    line(30);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_1_1;
        line(31);
        push_symbol(base+0);//arg
        push_symbol(base+1);//env
        push(&ONE);
        _clp_def_quit(3);
        pop();
    if_1_1:
    if_1_0:;
    line(34);
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

