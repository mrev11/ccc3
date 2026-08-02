//input: ppo/opt_cpp.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_channelnew(int argno);
extern void _clp_chr(int argno);
extern void _clp_dirmake(int argno);
extern void _clp_empty(int argno);
extern void _clp_file(int argno);
extern void _clp_len(int argno);
extern void _clp_memoread(int argno);
extern void _clp_opt_cpp(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_qqout(int argno);
extern void _clp_split(int argno);
extern void _clp_strtran(int argno);

class _method6_close: public _method6_{public: _method6_close():_method6_("close"){};}; static _method6_close _o_method_close;
class _method6_off: public _method6_{public: _method6_off():_method6_("off"){};}; static _method6_off _o_method_off;
class _method6_on: public _method6_{public: _method6_on():_method6_("on"){};}; static _method6_on _o_method_on;
class _method6_open: public _method6_{public: _method6_open():_method6_("open"){};}; static _method6_open _o_method_open;

//=======================================================================
void _clp_opt_cpp(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+8)PUSHNIL();
argno=2;
push_call("opt_cpp",base);
//
    line(8);
    line(9);
    number(10);
    _clp_chr(1);
    assign(base+3);//eol
    pop();
    line(10);
    line(11);
    line(12);
    line(14);
    push_symbol(base+1);//env
    string(L"BUILD_OBJ");
    _clp_pluginenv(2);
    _clp_dirmake(1);
    pop();
    line(16);
    push_symbol(base+1);//env
    string(L"CMPOPT");
    push_symbol(base+1);//env
    string(L"BUILD_OBJ");
    _clp_pluginenv(2);
    string(L"/");
    add();
    string(L"opt--cpp-");
    add();
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(18);
    push_symbol(base+1);//env
    string(L"CMPOPT");
    _clp_pluginenv(2);
    _clp_channelnew(1);
    assign(base+2);//options
    push(&FALSE);
    _o_method_open.eval(2);
    pop();
    line(19);
    push_symbol(base+2);//options
    _o_method_on.eval(1);
    pop();
    line(21);
    string(L"-Dcompile_");
    push_symbol(base+1);//env
    string(L"CCCVER");
    _clp_pluginenv(2);
    add();
    push_symbol(base+3);//eol
    add();
    _clp_qqout(1);
    pop();
    line(22);
    string(L"-Dcompile_");
    push_symbol(base+1);//env
    string(L"CCCUNAME");
    _clp_pluginenv(2);
    add();
    push_symbol(base+3);//eol
    add();
    _clp_qqout(1);
    pop();
    line(23);
    string(L"-Dcompile_");
    push_symbol(base+1);//env
    string(L"CCCBIN");
    _clp_pluginenv(2);
    add();
    push_symbol(base+3);//eol
    add();
    _clp_qqout(1);
    pop();
    line(24);
    string(L"-Dcompile_");
    push_symbol(base+1);//env
    string(L"MSYSTEM");
    _clp_pluginenv(2);
    add();
    push_symbol(base+3);//eol
    add();
    _clp_qqout(1);
    pop();
    line(26);
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
    string(L"/cppver.opt");
    add();
    assign(base+4);//cppopt
    pop();
    line(27);
    push_symbol(base+4);//cppopt
    _clp_memoread(1);
    _clp_qqout(1);
    pop();
    line(29);
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
    string(L"/");
    add();
    push_symbol(base+1);//env
    string(L"BUILD_OPT");
    _clp_pluginenv(2);
    add();
    assign(base+5);//bldopt
    pop();
    line(30);
    push_symbol(base+5);//bldopt
    _clp_memoread(1);
    _clp_qqout(1);
    pop();
    line(32);
    push_symbol(base+1);//env
    string(L"BUILD_INC");
    _clp_pluginenv(2);
    string(L" ");
    _clp_split(2);
    assign(base+6);//inc
    pop();
    line(37);
    {
    line(33);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+7);//n
    lab_1_0:
    push_symbol(base+6);//inc
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(36);
        line(34);
        push_symbol(base+6);//inc
        push_symbol(base+7);//n
        idxr();
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_2_1;
            line(35);
            string(L"-I");
            push_symbol(base+6);//inc
            push_symbol(base+7);//n
            idxr();
            string(L"\\");
            string(L"/");
            _clp_strtran(3);
            number(13);
            _clp_chr(1);
            string(L"");
            _clp_strtran(3);
            add();
            push_symbol(base+3);//eol
            add();
            _clp_qqout(1);
            pop();
        if_2_1:
        if_2_0:;
    lab_1_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+7);//n
    add();
    assign(base+7);//n
    goto lab_1_0;
    lab_1_2:;
    }
    line(41);
    line(39);
    push_symbol(base+1);//env
    string(L"BUILD_CFG");
    _clp_pluginenv(2);
    _clp_empty(1);
    topnot();
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+1);//env
    string(L"BUILD_CFG");
    _clp_pluginenv(2);
    _clp_file(1);
    }
    if(!flag()) goto if_3_1;
        line(40);
        push_symbol(base+1);//env
        string(L"BUILD_CFG");
        _clp_pluginenv(2);
        _clp_memoread(1);
        push_symbol(base+3);//eol
        add();
        _clp_qqout(1);
        pop();
    if_3_1:
    if_3_0:;
    line(43);
    push_symbol(base+2);//options
    _o_method_close.eval(1);
    pop();
    line(44);
    push_symbol(base+2);//options
    _o_method_off.eval(1);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

