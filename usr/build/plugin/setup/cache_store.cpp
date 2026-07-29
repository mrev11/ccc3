//input: ppo/cache_store.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_cache_store(int argno);
extern void _clp_def_quit(int argno);
extern void _clp_direxist(int argno);
extern void _clp_dirmake(int argno);
extern void _clp_empty(int argno);
extern void _clp_file(int argno);
extern void _clp_filecopy(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_qout(int argno);

//=======================================================================
void _clp_cache_store(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+5)PUSHNIL();
argno=2;
push_call("cache_store",base);
//
    line(6);
    line(11);
    line(8);
    push_symbol(base+1);//env
    string(L"BUILD_CACHE");
    _clp_pluginenv(2);
    _clp_empty(1);
    if(!flag()) goto if_1_1;
        line(9);
        push_symbol(base+1);//env
        string(L"BUILD_CACHE");
        push_symbol(base+1);//env
        string(L"HOME");
        _clp_pluginenv(2);
        string(L"/.cache/build");
        add();
        _clp_pluginenv(3);
        pop();
        line(10);
        push_symbol(base+1);//env
        string(L"BUILD_CACHE");
        _clp_pluginenv(2);
        _clp_dirmake(1);
        pop();
    if_1_1:
    if_1_0:;
    line(20);
    line(13);
    push_symbol(base+1);//env
    string(L"SHASUM");
    _clp_pluginenv(2);
    _clp_empty(1);
    topnot();
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_file(1);
    }
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+1);//env
    string(L"BUILD_CACHE");
    _clp_pluginenv(2);
    _clp_direxist(1);
    }
    if(!flag()) goto if_2_1;
        line(15);
        push_symbol(base+1);//env
        string(L"SHASUM");
        _clp_pluginenv(2);
        assign(base+2);//sum
        pop();
        line(16);
        push_symbol(base+1);//env
        string(L"BUILD_CACHE");
        _clp_pluginenv(2);
        string(L"/");
        add();
        push_symbol(base+2);//sum
        push(&ONE);
        number(2);
        slice();
        add();
        assign(base+3);//dir
        pop();
        line(17);
        push_symbol(base+3);//dir
        _clp_dirmake(1);
        pop();
        line(18);
        push_symbol(base+3);//dir
        string(L"/");
        add();
        push_symbol(base+2);//sum
        add();
        assign(base+4);//trg
        pop();
        line(19);
        push_symbol(base+1);//env
        string(L"TARGET");
        _clp_pluginenv(2);
        push_symbol(base+4);//trg
        _clp_filecopy(2);
        pop();
    if_2_1:
    if_2_0:;
    line(21);
    _clp_qout(0);
    pop();
    line(22);
    push_symbol(base+0);//arg
    push_symbol(base+1);//env
    push(&ZERO);
    _clp_def_quit(3);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

