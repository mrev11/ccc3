//input: ppo/obj2so.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_ferase(int argno);
extern void _clp_link_so(int argno);
extern void _clp_main(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_pluginenv_init(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);

//=======================================================================
void _clp_main(int argno)
{
VALUE *base=stack-argno;
while(stack<base+argno+2)PUSHNIL();
push_call("main",base);
//
    line(7);
    {int argc=1-1;
    {int i;for(i=0;i<argno;i++){argc++;push_symbol(base+i);}}
    array(argc);
    };
    assign(base+argno+0);//arg
    pop();
    line(8);
    _clp_pluginenv_init(0);
    assign(base+argno+1);//env
    pop();
    line(10);
    string(L"!OBJ2SO.BAT");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    string(L".so");
    add();
    _clp_qqout(2);
    pop();
    _clp_qout(0);
    pop();
    line(12);
    push_symbol(base+argno+1);//env
    string(L"TARGET");
    push_symbol(base+argno+1);//env
    string(L"BUILD_OBJ");
    _clp_pluginenv(2);
    string(L"/");
    add();
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    string(L".so");
    add();
    _clp_pluginenv(3);
    pop();
    line(13);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    string(L"out--obj2so-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(14);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    string(L"error--obj2so-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(16);
    push_symbol(base+argno+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(17);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(18);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(20);
    push_symbol(base+argno+0);//arg
    push_symbol(base+argno+1);//env
    _clp_link_so(2);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

