//input: ppo/compile_cpp.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_chr(int argno);
extern void _clp_compile_cpp(int argno);
extern void _clp_def_quit(int argno);
extern void _clp_dirmake(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_empty(int argno);
extern void _clp_ferase(int argno);
extern void _clp_filecopy(int argno);
extern void _clp_memoread(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_run(int argno);
extern void _clp_strtran(int argno);

namespace _nsp_filespec{
extern void _clp_basename(int argno);
}//namespace filespec

//=======================================================================
void _clp_compile_cpp(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("compile_cpp",base);
//
    line(8);
    line(9);
    number(10);
    _clp_chr(1);
    assign(base+3);//eol
    pop();
    line(11);
    string(L"object");
    _clp_dirmake(1);
    pop();
    line(14);
    push_symbol(base+1);//env
    string(L"TARGET");
    push_symbol(base+1);//env
    string(L"BUILD_OBJ");
    _clp_pluginenv(2);
    string(L"/");
    add();
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    string(L".obj");
    add();
    _clp_pluginenv(3);
    pop();
    line(15);
    push_symbol(base+1);//env
    string(L"OUT");
    string(L"out--cpp2obj-");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(16);
    push_symbol(base+1);//env
    string(L"ERR");
    string(L"error--cpp2obj-");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(18);
    push_symbol(base+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(19);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(20);
    push_symbol(base+1);//env
    string(L"ERR");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(22);
    string(L"c++ ");
    push_symbol(base+1);//env
    string(L"CMPOPT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    push_symbol(base+3);//eol
    string(L" ");
    _clp_strtran(3);
    add();
    string(L" -o ");
    add();
    push_symbol(base+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    add();
    string(L" -c ");
    add();
    push_symbol(base+1);//env
    string(L"SOURCE");
    _clp_pluginenv(2);
    add();
    string(L" 2>");
    add();
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    add();
    assign(base+2);//cmd
    pop();
    line(23);
    push_symbol(base+2);//cmd
    _clp_run(1);
    pop();
    line(27);
    line(25);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_1_1;
        line(26);
        push_symbol(base+0);//arg
        push_symbol(base+1);//env
        push(&ONE);
        _clp_def_quit(3);
        pop();
    if_1_1:
    if_1_0:;
    line(29);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(34);
    line(31);
    push_symbol(base+1);//env
    string(L"BUILD_CPP");
    _clp_pluginenv(2);
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_2_1;
        line(32);
        push_symbol(base+1);//env
        string(L"BUILD_CPP");
        _clp_pluginenv(2);
        _clp_dirmake(1);
        pop();
        line(33);
        push_symbol(base+1);//env
        string(L"SOURCE");
        _clp_pluginenv(2);
        push_symbol(base+1);//env
        string(L"BUILD_CPP");
        _clp_pluginenv(2);
        _clp_dirsep(0);
        add();
        push_symbol(base+1);//env
        string(L"SOURCE");
        _clp_pluginenv(2);
        _nsp_filespec::_clp_basename(1);
        add();
        _clp_filecopy(2);
        pop();
    if_2_1:
    if_2_0:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

