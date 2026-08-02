//input: ppo/msk2wro.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_def_quit(int argno);
extern void _clp_empty(int argno);
extern void _clp_fclose(int argno);
extern void _clp_ferase(int argno);
extern void _clp_file(int argno);
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
while(stack<base+argno+7)PUSHNIL();
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
    line(12);
    line(14);
    string(L"!MSK2WRO.BAT");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    push_symbol(base+argno+0);//arg
    idxr0(2);
    _clp_qqout(3);
    pop();
    _clp_qout(0);
    pop();
    line(16);
    push_symbol(base+argno+0);//arg
    idxr0(2);
    string(L"/");
    add();
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    string(L".msk");
    string(L"");
    _clp_strtran(3);
    assign(base+argno+2);//base
    pop();
    line(18);
    push_symbol(base+argno+1);//env
    string(L"SOURCE");
    push_symbol(base+argno+2);//base
    string(L".msk");
    add();
    _clp_pluginenv(3);
    pop();
    line(19);
    push_symbol(base+argno+1);//env
    string(L"TARGET");
    push_symbol(base+argno+2);//base
    string(L".wro");
    add();
    _clp_pluginenv(3);
    pop();
    line(20);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    string(L"out--msk2wro-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(21);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    string(L"error--msk2wro-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(23);
    push_symbol(base+argno+2);//base
    string(L".temp");
    add();
    assign(base+argno+3);//pge
    pop();
    line(24);
    push_symbol(base+argno+2);//base
    string(L".sor");
    add();
    assign(base+argno+4);//sor
    pop();
    line(26);
    push_symbol(base+argno+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(27);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(28);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(29);
    push_symbol(base+argno+3);//pge
    _clp_ferase(1);
    pop();
    line(31);
    string(L"msk2pge.exe -ur ");
    push_symbol(base+argno+1);//env
    string(L"SOURCE");
    _clp_pluginenv(2);
    add();
    string(L" ");
    add();
    push_symbol(base+argno+3);//pge
    add();
    assign(base+argno+5);//cmd
    pop();
    line(33);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    number(1282);
    _clp_fopen(2);
    assign(base+argno+6);//fdout
    pop();
    line(34);
    push_symbol(base+argno+5);//cmd
    push_symbol(base+argno+6);//fdout
    push_symbol(base+argno+6);//fdout
    _clp_runredir(3);
    pop();
    line(35);
    push_symbol(base+argno+6);//fdout
    _clp_fclose(1);
    pop();
    line(41);
    line(37);
    push_symbol(base+argno+4);//sor
    _clp_file(1);
    if(!flag()) goto if_1_1;
        line(38);
        string(L"pge2wro.exe -r ");
        push_symbol(base+argno+4);//sor
        add();
        string(L" ");
        add();
        push_symbol(base+argno+3);//pge
        add();
        assign(base+argno+5);//cmd
        pop();
    goto if_1_0;
    if_1_1:
    line(39);
        line(40);
        string(L"pge2wro.exe            ");
        push_symbol(base+argno+3);//pge
        add();
        assign(base+argno+5);//cmd
        pop();
    if_1_2:
    if_1_0:;
    line(43);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    number(1282);
    _clp_fopen(2);
    assign(base+argno+6);//fdout
    pop();
    line(44);
    push_symbol(base+argno+5);//cmd
    push_symbol(base+argno+6);//fdout
    push_symbol(base+argno+6);//fdout
    _clp_runredir(3);
    pop();
    line(45);
    push_symbol(base+argno+6);//fdout
    _clp_fclose(1);
    pop();
    line(47);
    push_symbol(base+argno+3);//pge
    _clp_ferase(1);
    pop();
    line(51);
    line(49);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_2_1;
        line(50);
        push_symbol(base+argno+0);//arg
        push_symbol(base+argno+1);//env
        push(&ONE);
        _clp_def_quit(3);
        pop();
    if_2_1:
    if_2_0:;
    line(53);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(54);
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

