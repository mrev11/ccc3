//input: ppo/obj2lib.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_channelnew(int argno);
extern void _clp_chr(int argno);
extern void _clp_def_quit(int argno);
extern void _clp_empty(int argno);
extern void _clp_fclose(int argno);
extern void _clp_ferase(int argno);
extern void _clp_file(int argno);
extern void _clp_fopen(int argno);
extern void _clp_len(int argno);
extern void _clp_main(int argno);
extern void _clp_memoread(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_pluginenv_init(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);
extern void _clp_runredir(int argno);
extern void _clp_split(int argno);
extern void _clp_strtran(int argno);

class _method6_close: public _method6_{public: _method6_close():_method6_("close"){};}; static _method6_close _o_method_close;
class _method6_off: public _method6_{public: _method6_off():_method6_("off"){};}; static _method6_off _o_method_off;
class _method6_on: public _method6_{public: _method6_on():_method6_("on"){};}; static _method6_on _o_method_on;
class _method6_open: public _method6_{public: _method6_open():_method6_("open"){};}; static _method6_open _o_method_open;

//=======================================================================
void _clp_main(int argno)
{
VALUE *base=stack-argno;
while(stack<base+argno+8)PUSHNIL();
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
    line(11);
    number(10);
    _clp_chr(1);
    assign(base+argno+3);//eol
    pop();
    line(12);
    line(13);
    line(14);
    line(16);
    string(L"!OBJ2LIB.BAT");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    string(L".lib");
    add();
    push_symbol(base+argno+1);//env
    string(L"BUILD_EXE");
    _clp_pluginenv(2);
    _clp_qqout(3);
    pop();
    _clp_qout(0);
    pop();
    line(18);
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
    string(L".lib");
    add();
    _clp_pluginenv(3);
    pop();
    line(19);
    push_symbol(base+argno+1);//env
    string(L"RSPLIB");
    push_symbol(base+argno+1);//env
    string(L"BUILD_OBJ");
    _clp_pluginenv(2);
    string(L"/rsp--lib-");
    add();
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(20);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    string(L"out--obj2lib-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(21);
    push_symbol(base+argno+1);//env
    string(L"ERR");
    string(L"out--obj2lib-");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(23);
    push_symbol(base+argno+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(24);
    push_symbol(base+argno+1);//env
    string(L"RSPLIB");
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
    line(28);
    push_symbol(base+argno+1);//env
    string(L"LIBNAME");
    push_symbol(base+argno+0);//arg
    idxr0(1);
    _clp_pluginenv(3);
    pop();
    line(30);
    push_symbol(base+argno+1);//env
    string(L"RSPLIB");
    _clp_pluginenv(2);
    _clp_channelnew(1);
    assign(base+argno+2);//rsp
    push(&FALSE);
    _o_method_open.eval(2);
    pop();
    line(31);
    push_symbol(base+argno+2);//rsp
    _o_method_on.eval(1);
    pop();
    line(45);
    line(34);
    push_symbol(base+argno+1);//env
    string(L"BUILD_OBJ");
    _clp_pluginenv(2);
    string(L"/objects-");
    add();
    push_symbol(base+argno+1);//env
    string(L"LIBNAME");
    _clp_pluginenv(2);
    add();
    _clp_file(1);
    if(!flag()) goto if_1_1;
        line(36);
        push_symbol(base+argno+1);//env
        string(L"BUILD_OBJ");
        _clp_pluginenv(2);
        string(L"/objects-");
        add();
        push_symbol(base+argno+1);//env
        string(L"LIBNAME");
        _clp_pluginenv(2);
        add();
        _clp_memoread(1);
        push_symbol(base+argno+3);//eol
        _clp_split(2);
        assign(base+argno+4);//obj
        pop();
        line(39);
        {
        line(37);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+argno+5);//n
        lab_2_0:
        push_symbol(base+argno+4);//obj
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_2_2;
            line(38);
            push_symbol(base+argno+1);//env
            string(L"BUILD_OBJ");
            _clp_pluginenv(2);
            string(L"/");
            add();
            push_symbol(base+argno+4);//obj
            push_symbol(base+argno+5);//n
            idxr();
            number(13);
            _clp_chr(1);
            string(L"");
            _clp_strtran(3);
            add();
            push_symbol(base+argno+3);//eol
            add();
            _clp_qqout(1);
            pop();
        lab_2_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+argno+5);//n
        add();
        assign(base+argno+5);//n
        goto lab_2_0;
        lab_2_2:;
        }
    goto if_1_0;
    if_1_1:
    line(40);
        line(44);
        {
        line(42);
        push(&ONE);
        int sg=sign();
        number(2);
        assign(base+argno+5);//n
        lab_3_0:
        push_symbol(base+argno+0);//arg
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_3_2;
            line(43);
            push_symbol(base+argno+1);//env
            string(L"BUILD_OBJ");
            _clp_pluginenv(2);
            string(L"/");
            add();
            push_symbol(base+argno+0);//arg
            push_symbol(base+argno+5);//n
            idxr();
            add();
            string(L".obj");
            add();
            push_symbol(base+argno+3);//eol
            add();
            _clp_qqout(1);
            pop();
        lab_3_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+argno+5);//n
        add();
        assign(base+argno+5);//n
        goto lab_3_0;
        lab_3_2:;
        }
    if_1_2:
    if_1_0:;
    line(47);
    push_symbol(base+argno+2);//rsp
    _o_method_close.eval(1);
    pop();
    line(48);
    push_symbol(base+argno+2);//rsp
    _o_method_off.eval(1);
    pop();
    line(50);
    string(L"ar -c -q ");
    push_symbol(base+argno+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    add();
    string(L" ");
    add();
    push_symbol(base+argno+1);//env
    string(L"RSPLIB");
    _clp_pluginenv(2);
    _clp_memoread(1);
    push_symbol(base+argno+3);//eol
    string(L" ");
    _clp_strtran(3);
    add();
    assign(base+argno+6);//cmd
    pop();
    line(52);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    number(770);
    _clp_fopen(2);
    assign(base+argno+7);//fdout
    pop();
    line(53);
    push_symbol(base+argno+6);//cmd
    push_symbol(base+argno+7);//fdout
    push_symbol(base+argno+7);//fdout
    _clp_runredir(3);
    pop();
    line(54);
    push_symbol(base+argno+7);//fdout
    _clp_fclose(1);
    pop();
    line(58);
    line(56);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_4_1;
        line(57);
        push_symbol(base+argno+0);//arg
        push_symbol(base+argno+1);//env
        push(&ONE);
        _clp_def_quit(3);
        pop();
    if_4_1:
    if_4_0:;
    line(60);
    push_symbol(base+argno+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(61);
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

