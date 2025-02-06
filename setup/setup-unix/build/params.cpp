//input: ppo/params.ppo (5.7.0.1)

#include <cccdef.h>

extern void _clp_buildenv_inc(int argno);
extern void _clp_buildenv_lib(int argno);
extern void _clp_buildenv_lpt(int argno);
extern void _clp_getenv(int argno);
extern void _clp_params(int argno);
extern void _clp_s_incdir(int argno);
extern void _clp_s_libdir(int argno);
extern void _clp_s_libfil(int argno);
extern void _clp_s_libspec(int argno);
extern void _clp_s_srcdir(int argno);
extern void _clp_search_library(int argno);
extern void _clp_split(int argno);
extern void _clp_strtran(int argno);

//=======================================================================
void _clp_params(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+4)PUSHNIL();
argno=0;
push_call("params",base);
//
    line(25);
    line(38);
    string(L"");
    assign(base+0);//txt
    pop();
    line(39);
    push_symbol(base+0);//txt
    _clp_s_srcdir(0);
    push(&NIL);
    eqeq();
    cmp_63:;
    if(flag()){
    string(L".");
    }else{
    _clp_s_srcdir(0);
    }
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(40);
    push_symbol(base+0);//txt
    _clp_s_incdir(0);
    push(&NIL);
    eqeq();
    cmp_101:;
    if(flag()){
    string(L"");
    }else{
    _clp_s_incdir(0);
    }
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(41);
    push_symbol(base+0);//txt
    _clp_buildenv_inc(0);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(42);
    push_symbol(base+0);//txt
    string(L"include");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(43);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(44);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(46);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(48);
    push_symbol(base+0);//txt
    _clp_buildenv_inc(1);
    pop();
    line(54);
    string(L"");
    assign(base+0);//txt
    pop();
    line(55);
    push_symbol(base+0);//txt
    _clp_s_libdir(0);
    push(&NIL);
    eqeq();
    cmp_297:;
    if(flag()){
    string(L"");
    }else{
    _clp_s_libdir(0);
    }
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(56);
    push_symbol(base+0);//txt
    _clp_buildenv_lpt(0);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(57);
    push_symbol(base+0);//txt
    string(L"lib");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(58);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(59);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(61);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(63);
    push_symbol(base+0);//txt
    _clp_buildenv_lpt(1);
    pop();
    line(69);
    string(L"");
    assign(base+0);//txt
    pop();
    line(70);
    push_symbol(base+0);//txt
    _clp_s_libfil(0);
    push(&NIL);
    eqeq();
    cmp_493:;
    if(flag()){
    string(L"");
    }else{
    _clp_s_libfil(0);
    }
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(71);
    push_symbol(base+0);//txt
    _clp_buildenv_lib(0);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(72);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(73);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(74);
    push_symbol(base+0);//txt
    _clp_buildenv_lib(1);
    pop();
    line(75);
    _clp_search_library(0);
    _clp_s_libspec(1);
    pop();
    line(76);
    _clp_s_libspec(0);
    _clp_buildenv_lib(1);
    pop();
    line(77);
    _clp_s_libspec(0);
    string(L" ");
    _clp_split(2);
    _clp_s_libspec(1);
    pop();
    line(79);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

