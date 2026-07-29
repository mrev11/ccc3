//input: ppo/prg2obj.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_cache_search(int argno);
extern void _clp_cache_store(int argno);
extern void _clp_compile_cpp(int argno);
extern void _clp_compile_ppo(int argno);
extern void _clp_compile_prg(int argno);
extern void _clp_ferase(int argno);
extern void _clp_main(int argno);
extern void _clp_opt_cpp(int argno);
extern void _clp_opt_ppo(int argno);
extern void _clp_opt_prg(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_pluginenv_init(int argno);
extern void _clp_qqout(int argno);

//=======================================================================
void _clp_main(int argno)
{
VALUE *base=stack-argno;
while(stack<base+argno+2)PUSHNIL();
push_call("main",base);
//
    line(6);
    {int argc=1-1;
    {int i;for(i=0;i<argno;i++){argc++;push_symbol(base+i);}}
    array(argc);
    };
    assign(base+argno+0);//arg
    pop();
    line(7);
    _clp_pluginenv_init(0);
    assign(base+argno+1);//env
    pop();
    line(9);
    string(L"!PRG2OBJ.BAT");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    push_symbol(base+argno+0);//arg
    idxr0(2);
    _clp_qqout(3);
    pop();
    line(11);
    push_symbol(base+argno+1);//env
    string(L"SOURCE");
    push_symbol(base+argno+0);//arg
    idxr0(2);
    string(L"/");
    add();
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    string(L".prg");
    add();
    _clp_pluginenv(3);
    pop();
    line(12);
    push_symbol(base+argno+1);//env
    string(L"DEPEND");
    push_symbol(base+argno+0);//arg
    number(3);
    push(&NIL);
    slice();
    _clp_pluginenv(3);
    pop();
    line(13);
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
    string(L".obj");
    add();
    _clp_pluginenv(3);
    pop();
    line(14);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    string(L"out--prg2obj-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(15);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    string(L"error--prg2obj-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(19);
    push_symbol(base+argno+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(20);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(21);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(23);
    push_symbol(base+argno+0);//arg
    push_symbol(base+argno+1);//env
    _clp_opt_prg(2);
    pop();
    line(24);
    push_symbol(base+argno+0);//arg
    push_symbol(base+argno+1);//env
    _clp_cache_search(2);
    pop();
    line(25);
    push_symbol(base+argno+0);//arg
    push_symbol(base+argno+1);//env
    _clp_compile_prg(2);
    pop();
    line(26);
    push_symbol(base+argno+0);//arg
    push_symbol(base+argno+1);//env
    _clp_opt_ppo(2);
    pop();
    line(27);
    push_symbol(base+argno+0);//arg
    push_symbol(base+argno+1);//env
    _clp_compile_ppo(2);
    pop();
    line(29);
    push_symbol(base+argno+1);//env
    string(L"SOURCE");
    string(L"ppo/");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    string(L".cpp");
    add();
    _clp_pluginenv(3);
    pop();
    line(31);
    push_symbol(base+argno+0);//arg
    push_symbol(base+argno+1);//env
    _clp_opt_cpp(2);
    pop();
    line(32);
    push_symbol(base+argno+0);//arg
    push_symbol(base+argno+1);//env
    _clp_compile_cpp(2);
    pop();
    line(33);
    push_symbol(base+argno+0);//arg
    push_symbol(base+argno+1);//env
    _clp_cache_store(2);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

