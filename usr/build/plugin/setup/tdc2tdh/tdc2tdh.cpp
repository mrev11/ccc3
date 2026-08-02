//input: ppo/tdc2tdh.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_def_quit(int argno);
extern void _clp_empty(int argno);
extern void _clp_fclose(int argno);
extern void _clp_ferase(int argno);
extern void _clp_fopen(int argno);
extern void _clp_main(int argno);
extern void _clp_memoread(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_pluginenv_init(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);
extern void _clp_runredir(int argno);

//=======================================================================
void _clp_main(int argno)
{
VALUE *base=stack-argno;
while(stack<base+argno+4)PUSHNIL();
push_call("main",base);
//
    line(8);
    {int argc=1-1;
    {int i;for(i=0;i<argno;i++){argc++;push_symbol(base+i);}}
    array(argc);
    };
    assign(base+argno+0);//arg
    pop();
    line(9);
    _clp_pluginenv_init(0);
    assign(base+argno+1);//env
    pop();
    line(10);
    line(11);
    line(13);
    string(L"!TDC2TDH.BAT");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    push_symbol(base+argno+0);//arg
    idxr0(2);
    _clp_qqout(3);
    pop();
    _clp_qout(0);
    pop();
    line(15);
    push_symbol(base+argno+1);//env
    string(L"SOURCE");
    push_symbol(base+argno+0);//arg
    idxr0(2);
    string(L"/");
    add();
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    string(L".tdc");
    add();
    _clp_pluginenv(3);
    pop();
    line(16);
    push_symbol(base+argno+1);//env
    string(L"DEPEND");
    push_symbol(base+argno+0);//arg
    number(3);
    push(&NIL);
    slice();
    _clp_pluginenv(3);
    pop();
    line(17);
    push_symbol(base+argno+1);//env
    string(L"TARGET");
    string(L"table.");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    string(L".tdh");
    add();
    _clp_pluginenv(3);
    pop();
    line(18);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    string(L"out--tdc2tdh-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(19);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    string(L"error--tdc2tdh    -");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(21);
    push_symbol(base+argno+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(22);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(23);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(25);
    string(L"tdc2tdh.exe ");
    push_symbol(base+argno+1);//env
    string(L"SOURCE");
    _clp_pluginenv(2);
    add();
    assign(base+argno+2);//cmd
    pop();
    line(27);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    number(770);
    _clp_fopen(2);
    assign(base+argno+3);//fdout
    pop();
    line(28);
    push_symbol(base+argno+2);//cmd
    push_symbol(base+argno+3);//fdout
    push_symbol(base+argno+3);//fdout
    _clp_runredir(3);
    pop();
    line(29);
    push_symbol(base+argno+3);//fdout
    _clp_fclose(1);
    pop();
    line(33);
    line(31);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_1_1;
        line(32);
        push_symbol(base+argno+0);//arg
        push_symbol(base+argno+1);//env
        push(&ONE);
        _clp_def_quit(3);
        pop();
    if_1_1:
    if_1_0:;
    line(35);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(36);
    push_symbol(base+argno+0);//arg
    push_symbol(base+argno+1);//env
    push(&ZERO);
    _clp_def_quit(3);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

