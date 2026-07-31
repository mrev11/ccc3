//input: ppo/pge2wro.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_def_quit(int argno);
extern void _clp_empty(int argno);
extern void _clp_ferase(int argno);
extern void _clp_file(int argno);
extern void _clp_main(int argno);
extern void _clp_memoread(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_pluginenv_init(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);
extern void _clp_run(int argno);
extern void _clp_strtran(int argno);

//=======================================================================
void _clp_main(int argno)
{
VALUE *base=stack-argno;
while(stack<base+argno+6)PUSHNIL();
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
    line(12);
    string(L"!PGE2WRO.BAT");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    push_symbol(base+argno+0);//arg
    idxr0(2);
    _clp_qqout(3);
    pop();
    _clp_qout(0);
    pop();
    line(14);
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
    line(15);
    push_symbol(base+argno+2);//base
    string(L".pge");
    add();
    assign(base+argno+3);//pge
    pop();
    line(16);
    push_symbol(base+argno+2);//base
    string(L".sor");
    add();
    assign(base+argno+5);//sor
    pop();
    line(17);
    push_symbol(base+argno+2);//base
    string(L".wro");
    add();
    assign(base+argno+4);//wro
    pop();
    line(19);
    push_symbol(base+argno+1);//env
    string(L"SOURCE");
    push_symbol(base+argno+3);//pge
    _clp_pluginenv(3);
    pop();
    line(20);
    push_symbol(base+argno+1);//env
    string(L"TARGET");
    push_symbol(base+argno+4);//wro
    _clp_pluginenv(3);
    pop();
    line(21);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    string(L"out--pge2wro-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(22);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    string(L"error--pge2wro-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(24);
    push_symbol(base+argno+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(25);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(26);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(32);
    line(28);
    push_symbol(base+argno+5);//sor
    _clp_file(1);
    if(!flag()) goto if_1_1;
        line(29);
        string(L"pge2wro.exe -r ");
        push_symbol(base+argno+5);//sor
        add();
        string(L" ");
        add();
        push_symbol(base+argno+3);//pge
        add();
        string(L" 2>&1 >>");
        add();
        push_symbol(base+argno+1);//env
        string(L"OUT");
        _clp_pluginenv(2);
        add();
        _clp_run(1);
        pop();
    goto if_1_0;
    if_1_1:
    line(30);
        line(31);
        string(L"pge2wro.exe ");
        push_symbol(base+argno+3);//pge
        add();
        string(L" 2>&1 >>");
        add();
        push_symbol(base+argno+1);//env
        string(L"OUT");
        _clp_pluginenv(2);
        add();
        _clp_run(1);
        pop();
    if_1_2:
    if_1_0:;
    line(36);
    line(34);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_2_1;
        line(35);
        push_symbol(base+argno+0);//arg
        push_symbol(base+argno+1);//env
        push(&ONE);
        _clp_def_quit(3);
        pop();
    if_2_1:
    if_2_0:;
    line(38);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(39);
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

