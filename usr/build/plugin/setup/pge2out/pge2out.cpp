//input: ppo/pge2out.ppo (5.7.2)

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
extern void _clp_strtran(int argno);

//=======================================================================
void _clp_main(int argno)
{
VALUE *base=stack-argno;
while(stack<base+argno+5)PUSHNIL();
push_call("main",base);
//
    line(10);
    {int argc=1-1;
    {int i;for(i=0;i<argno;i++){argc++;push_symbol(base+i);}}
    array(argc);
    };
    assign(base+argno+0);//arg
    pop();
    line(11);
    _clp_pluginenv_init(0);
    assign(base+argno+1);//env
    pop();
    line(12);
    line(13);
    line(14);
    line(16);
    string(L"!PGE2OUT.BAT");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    push_symbol(base+argno+0);//arg
    idxr0(2);
    _clp_qqout(3);
    pop();
    _clp_qout(0);
    pop();
    line(18);
    push_symbol(base+argno+0);//arg
    idxr0(2);
    string(L"/");
    add();
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    string(L".pge");
    string(L"");
    _clp_strtran(3);
    assign(base+argno+2);//base
    pop();
    line(20);
    push_symbol(base+argno+1);//env
    string(L"SOURCE");
    push_symbol(base+argno+2);//base
    string(L".pge");
    add();
    _clp_pluginenv(3);
    pop();
    line(21);
    push_symbol(base+argno+1);//env
    string(L"TARGET");
    push_symbol(base+argno+2);//base
    string(L".out");
    add();
    _clp_pluginenv(3);
    pop();
    line(22);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    string(L"out--pge2out-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(23);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    string(L"error--pge2out-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(25);
    push_symbol(base+argno+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(26);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(27);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(29);
    string(L"pge2out.exe -f");
    push_symbol(base+argno+1);//env
    string(L"SOURCE");
    _clp_pluginenv(2);
    add();
    string(L" -gOUT");
    add();
    assign(base+argno+3);//cmd
    pop();
    line(31);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    number(1282);
    _clp_fopen(2);
    assign(base+argno+4);//fdout
    pop();
    line(32);
    push_symbol(base+argno+3);//cmd
    push_symbol(base+argno+4);//fdout
    push_symbol(base+argno+4);//fdout
    _clp_runredir(3);
    pop();
    line(33);
    push_symbol(base+argno+4);//fdout
    _clp_fclose(1);
    pop();
    line(38);
    line(36);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_1_1;
        line(37);
        push_symbol(base+argno+0);//arg
        push_symbol(base+argno+1);//env
        push(&ONE);
        _clp_def_quit(3);
        pop();
    if_1_1:
    if_1_0:;
    line(40);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(41);
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

