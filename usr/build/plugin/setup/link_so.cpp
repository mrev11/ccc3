//input: ppo/link_so.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_channelnew(int argno);
extern void _clp_chr(int argno);
extern void _clp_def_quit(int argno);
extern void _clp_empty(int argno);
extern void _clp_ferase(int argno);
extern void _clp_file(int argno);
extern void _clp_len(int argno);
extern void _clp_link_so(int argno);
extern void _clp_memoread(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_qqout(int argno);
extern void _clp_run(int argno);
extern void _clp_split(int argno);
extern void _clp_strtran(int argno);

class _method6_close: public _method6_{public: _method6_close():_method6_("close"){};}; static _method6_close _o_method_close;
class _method6_off: public _method6_{public: _method6_off():_method6_("off"){};}; static _method6_off _o_method_off;
class _method6_on: public _method6_{public: _method6_on():_method6_("on"){};}; static _method6_on _o_method_on;
class _method6_open: public _method6_{public: _method6_open():_method6_("open"){};}; static _method6_open _o_method_open;

//=======================================================================
void _clp_link_so(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+10)PUSHNIL();
argno=2;
push_call("link_so",base);
//
    line(7);
    line(8);
    line(9);
    number(10);
    _clp_chr(1);
    assign(base+6);//eol
    pop();
    line(10);
    line(12);
    push_symbol(base+1);//env
    string(L"RSPLNK");
    push_symbol(base+1);//env
    string(L"BUILD_OBJ");
    _clp_pluginenv(2);
    string(L"/rsp--so-");
    add();
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(14);
    push_symbol(base+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(15);
    push_symbol(base+1);//env
    string(L"RSPLNK");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(16);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(17);
    push_symbol(base+1);//env
    string(L"ERR");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(19);
    push_symbol(base+1);//env
    string(L"RSPLNK");
    _clp_pluginenv(2);
    _clp_channelnew(1);
    assign(base+2);//rsp
    push(&FALSE);
    _o_method_open.eval(2);
    pop();
    line(20);
    push_symbol(base+2);//rsp
    _o_method_on.eval(1);
    pop();
    line(22);
    string(L"-shared");
    push_symbol(base+6);//eol
    add();
    _clp_qqout(1);
    pop();
    line(23);
    string(L"-o ");
    push_symbol(base+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    add();
    push_symbol(base+6);//eol
    add();
    _clp_qqout(1);
    pop();
    line(25);
    push_symbol(base+1);//env
    string(L"BUILD_LPT");
    _clp_pluginenv(2);
    string(L" ");
    _clp_split(2);
    assign(base+3);//lpt
    pop();
    line(30);
    {
    line(26);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+5);//n
    lab_1_0:
    push_symbol(base+3);//lpt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(29);
        line(27);
        push_symbol(base+3);//lpt
        push_symbol(base+5);//n
        idxr();
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_2_1;
            line(28);
            string(L"-L");
            push_symbol(base+3);//lpt
            push_symbol(base+5);//n
            idxr();
            add();
            push_symbol(base+6);//eol
            add();
            _clp_qqout(1);
            pop();
        if_2_1:
        if_2_0:;
    lab_1_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+5);//n
    add();
    assign(base+5);//n
    goto lab_1_0;
    lab_1_2:;
    }
    line(34);
    {
    line(32);
    push(&ONE);
    int sg=sign();
    number(2);
    assign(base+5);//n
    lab_3_0:
    push_symbol(base+0);//arg
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_3_2;
        line(33);
        push_symbol(base+1);//env
        string(L"BUILD_OBJ");
        _clp_pluginenv(2);
        string(L"/");
        add();
        push_symbol(base+0);//arg
        push_symbol(base+5);//n
        idxr();
        add();
        string(L".obj");
        add();
        push_symbol(base+6);//eol
        add();
        _clp_qqout(1);
        pop();
    lab_3_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+5);//n
    add();
    assign(base+5);//n
    goto lab_3_0;
    lab_3_2:;
    }
    line(36);
    push_symbol(base+1);//env
    string(L"BUILD_LIB");
    _clp_pluginenv(2);
    string(L" ");
    _clp_split(2);
    assign(base+4);//lib
    pop();
    line(41);
    {
    line(37);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+5);//n
    lab_4_0:
    push_symbol(base+4);//lib
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
        line(40);
        line(38);
        push_symbol(base+4);//lib
        push_symbol(base+5);//n
        idxr();
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_5_1;
            line(39);
            push_symbol(base+4);//lib
            push_symbol(base+5);//n
            idxr();
            push_symbol(base+6);//eol
            add();
            _clp_qqout(1);
            pop();
        if_5_1:
        if_5_0:;
    lab_4_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+5);//n
    add();
    assign(base+5);//n
    goto lab_4_0;
    lab_4_2:;
    }
    line(45);
    line(43);
    push_symbol(base+1);//env
    string(L"BUILD_LIBX");
    _clp_pluginenv(2);
    _clp_empty(1);
    topnot();
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+1);//env
    string(L"BUILD_LIBX");
    _clp_pluginenv(2);
    _clp_file(1);
    }
    if(!flag()) goto if_6_1;
        line(44);
        push_symbol(base+1);//env
        string(L"BUILD_LIBX");
        _clp_pluginenv(2);
        _clp_memoread(1);
        push_symbol(base+6);//eol
        add();
        _clp_qqout(1);
        pop();
    if_6_1:
    if_6_0:;
    line(47);
    string(L"-Wl,-soname=");
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    string(L".so");
    add();
    push_symbol(base+6);//eol
    add();
    _clp_qqout(1);
    pop();
    line(49);
    push_symbol(base+1);//env
    string(L"CCCDIR");
    _clp_pluginenv(2);
    string(L"/usr/options/");
    add();
    push_symbol(base+1);//env
    string(L"CCCUNAME");
    _clp_pluginenv(2);
    add();
    string(L"/");
    add();
    push_symbol(base+1);//env
    string(L"CCCBIN");
    _clp_pluginenv(2);
    add();
    string(L"/link.opt");
    add();
    _clp_memoread(1);
    push_symbol(base+6);//eol
    add();
    _clp_qqout(1);
    pop();
    line(51);
    push_symbol(base+2);//rsp
    _o_method_close.eval(1);
    pop();
    line(52);
    push_symbol(base+2);//rsp
    _o_method_off.eval(1);
    pop();
    line(54);
    string(L"c++ ");
    push_symbol(base+1);//env
    string(L"RSPLNK");
    _clp_pluginenv(2);
    _clp_memoread(1);
    push_symbol(base+6);//eol
    string(L" ");
    _clp_strtran(3);
    add();
    string(L" 2>");
    add();
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    add();
    assign(base+7);//cmd
    pop();
    line(55);
    push_symbol(base+7);//cmd
    _clp_run(1);
    pop();
    line(59);
    line(57);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_7_1;
        line(58);
        push_symbol(base+0);//arg
        push_symbol(base+1);//env
        push(&ONE);
        _clp_def_quit(3);
        pop();
    if_7_1:
    if_7_0:;
    line(61);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(62);
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

