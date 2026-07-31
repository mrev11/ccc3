//input: ppo/msk2html.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_asize(int argno);
extern void _clp_def_quit(int argno);
extern void _clp_empty(int argno);
extern void _clp_ferase(int argno);
extern void _clp_main(int argno);
extern void _clp_memoread(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_pluginenv_init(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);
extern void _clp_run(int argno);

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
    line(12);
    string(L"!MSK2HTML.BAT");
    push_symbol(base+argno+0);//arg
    _clp_qqout(2);
    pop();
    _clp_qout(0);
    pop();
    line(14);
    push_symbol(base+argno+0);//arg
    number(2);
    _clp_asize(2);
    pop();
    line(19);
    line(15);
    push_symbol(base+argno+0);//arg
    idxr0(2);
    push(&NIL);
    eqeq();
    cmp_127:;
    if(!flag()) goto if_1_1;
        line(16);
        push_symbol(base+argno+1);//env
        string(L"SOURCE");
        push_symbol(base+argno+0);//arg
        idxr0(1);
        _clp_pluginenv(3);
        pop();
    goto if_1_0;
    if_1_1:
    line(17);
        line(18);
        push_symbol(base+argno+1);//env
        string(L"SOURCE");
        push_symbol(base+argno+0);//arg
        idxr0(2);
        string(L"/");
        add();
        push_symbol(base+argno+0);//arg
        idxr0(1);
        add();
        _clp_pluginenv(3);
        pop();
    if_1_2:
    if_1_0:;
    line(22);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    string(L"out--msk2html-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(23);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    string(L"error--msk2html-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
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
    line(30);
    string(L"msk2html.exe ");
    push_symbol(base+argno+1);//env
    string(L"SOURCE");
    _clp_pluginenv(2);
    add();
    string(L" >");
    add();
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    add();
    _clp_run(1);
    pop();
    line(35);
    line(33);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_2_1;
        line(34);
        push_symbol(base+argno+0);//arg
        push_symbol(base+argno+1);//env
        push(&ONE);
        _clp_def_quit(3);
        pop();
    if_2_1:
    if_2_0:;
    line(37);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(38);
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

