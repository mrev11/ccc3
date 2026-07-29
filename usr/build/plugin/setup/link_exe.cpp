//input: ppo/link_exe.ppo (5.7.2)

#include <cccdef.h>

static void _clp_cat(int argno);
extern void _clp_channelnew(int argno);
extern void _clp_chr(int argno);
extern void _clp_def_quit(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_empty(int argno);
extern void _clp_ferase(int argno);
extern void _clp_file(int argno);
extern void _clp_len(int argno);
extern void _clp_link_exe(int argno);
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
void _clp_link_exe(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+11)PUSHNIL();
argno=2;
push_call("link_exe",base);
//
    line(8);
    line(9);
    line(10);
    number(10);
    _clp_chr(1);
    assign(base+6);//eol
    pop();
    line(11);
    line(12);
    _clp_dirsep(0);
    string(L"/");
    eqeq();
    cmp_98:;
    if(flag()){
    string(L"/dev/null");
    }else{
    string(L"NUL");
    }
    assign(base+10);//null
    pop();
    line(14);
    push_symbol(base+1);//env
    string(L"TARGET");
    push_symbol(base+1);//env
    string(L"BUILD_EXE");
    _clp_pluginenv(2);
    string(L"/");
    add();
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    string(L".exe");
    add();
    _clp_pluginenv(3);
    pop();
    line(15);
    push_symbol(base+1);//env
    string(L"RSPLNK");
    push_symbol(base+1);//env
    string(L"BUILD_OBJ");
    _clp_pluginenv(2);
    string(L"/rsp--exe-");
    add();
    push_symbol(base+0);//arg
    idxr0(1);
    add();
    _clp_pluginenv(3);
    pop();
    line(17);
    push_symbol(base+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(18);
    push_symbol(base+1);//env
    string(L"RSPLNK");
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
    push_symbol(base+1);//env
    string(L"RSPLNK");
    _clp_pluginenv(2);
    _clp_channelnew(1);
    assign(base+2);//rsp
    push(&FALSE);
    _o_method_open.eval(2);
    pop();
    line(23);
    push_symbol(base+2);//rsp
    _o_method_on.eval(1);
    pop();
    line(25);
    string(L"-o ");
    push_symbol(base+1);//env
    string(L"TARGET");
    _clp_pluginenv(2);
    add();
    push_symbol(base+6);//eol
    add();
    _clp_qqout(1);
    pop();
    line(27);
    push_symbol(base+1);//env
    string(L"BUILD_LPT");
    _clp_pluginenv(2);
    string(L" ");
    _clp_split(2);
    assign(base+3);//lpt
    pop();
    line(32);
    {
    line(28);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+5);//n
    lab_1_0:
    push_symbol(base+3);//lpt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(31);
        line(29);
        push_symbol(base+3);//lpt
        push_symbol(base+5);//n
        idxr();
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_2_1;
            line(30);
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
    string(L"-Wl,--start-group");
    push_symbol(base+6);//eol
    add();
    _clp_qqout(1);
    pop();
    line(49);
    line(36);
    push_symbol(base+1);//env
    string(L"LIBNAME");
    _clp_pluginenv(2);
    _clp_empty(1);
    if(!flag()) goto if_3_1;
        line(44);
        line(38);
        push_symbol(base+1);//env
        string(L"BUILD_OBJ");
        _clp_pluginenv(2);
        string(L"/objects-");
        add();
        push_symbol(base+1);//env
        string(L"EXENAME");
        _clp_pluginenv(2);
        add();
        _clp_file(1);
        if(!flag()) goto if_4_1;
            line(39);
            push_symbol(base+1);//env
            string(L"BUILD_OBJ");
            _clp_pluginenv(2);
            string(L"/objects-");
            add();
            push_symbol(base+1);//env
            string(L"EXENAME");
            _clp_pluginenv(2);
            add();
            _clp_memoread(1);
            push_symbol(base+6);//eol
            add();
            _clp_qqout(1);
            pop();
        goto if_4_0;
        if_4_1:
        line(40);
            line(43);
            {
            line(41);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+5);//n
            lab_5_0:
            push_symbol(base+0);//arg
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_5_2;
                line(42);
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
            lab_5_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+5);//n
            add();
            assign(base+5);//n
            goto lab_5_0;
            lab_5_2:;
            }
        if_4_2:
        if_4_0:;
    goto if_3_0;
    if_3_1:
    line(45);
        line(47);
        push_symbol(base+1);//env
        string(L"BUILD_OBJ");
        _clp_pluginenv(2);
        string(L"/");
        add();
        push_symbol(base+1);//env
        string(L"EXENAME");
        _clp_pluginenv(2);
        add();
        string(L".obj");
        add();
        push_symbol(base+6);//eol
        add();
        _clp_qqout(1);
        pop();
        line(48);
        push_symbol(base+1);//env
        string(L"BUILD_OBJ");
        _clp_pluginenv(2);
        string(L"/");
        add();
        push_symbol(base+1);//env
        string(L"LIBNAME");
        _clp_pluginenv(2);
        add();
        string(L".lib");
        add();
        push_symbol(base+6);//eol
        add();
        _clp_qqout(1);
        pop();
    if_3_2:
    if_3_0:;
    line(51);
    push_symbol(base+1);//env
    string(L"BUILD_LIB");
    _clp_pluginenv(2);
    string(L" ");
    _clp_split(2);
    assign(base+4);//lib
    pop();
    line(56);
    {
    line(52);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+5);//n
    lab_6_0:
    push_symbol(base+4);//lib
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_6_2;
        line(55);
        line(53);
        push_symbol(base+4);//lib
        push_symbol(base+5);//n
        idxr();
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_7_1;
            line(54);
            push_symbol(base+4);//lib
            push_symbol(base+5);//n
            idxr();
            push_symbol(base+6);//eol
            add();
            _clp_qqout(1);
            pop();
        if_7_1:
        if_7_0:;
    lab_6_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+5);//n
    add();
    assign(base+5);//n
    goto lab_6_0;
    lab_6_2:;
    }
    line(60);
    line(58);
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
    if(!flag()) goto if_8_1;
        line(59);
        push_symbol(base+1);//env
        string(L"BUILD_LIBX");
        _clp_pluginenv(2);
        _clp_memoread(1);
        push_symbol(base+6);//eol
        add();
        _clp_qqout(1);
        pop();
    if_8_1:
    if_8_0:;
    line(62);
    string(L"-Wl,--end-group");
    push_symbol(base+6);//eol
    add();
    _clp_qqout(1);
    pop();
    line(64);
    push_symbol(base+1);//env
    string(L"OPT");
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
    _clp_pluginenv(3);
    pop();
    line(69);
    line(65);
    push_symbol(base+1);//env
    string(L"BUILD_SHR");
    _clp_pluginenv(2);
    string(L"fullstatic");
    eqeq();
    cmp_1320:;
    if(!flag()) goto if_9_1;
        line(66);
        push_symbol(base+1);//env
        string(L"OPT");
        _clp_pluginenv(2);
        _clp_memoread(1);
        string(L"-rdynamic");
        string(L"_static");
        _clp_strtran(3);
        push_symbol(base+6);//eol
        add();
        _clp_qqout(1);
        pop();
    goto if_9_0;
    if_9_1:
    line(67);
        line(68);
        push_symbol(base+1);//env
        string(L"OPT");
        _clp_pluginenv(2);
        _clp_memoread(1);
        push_symbol(base+6);//eol
        add();
        _clp_qqout(1);
        pop();
    if_9_2:
    if_9_0:;
    line(70);
    push_symbol(base+2);//rsp
    _o_method_off.eval(1);
    pop();
    line(71);
    push_symbol(base+2);//rsp
    _o_method_close.eval(1);
    pop();
    line(73);
    push_symbol(base+1);//env
    string(L"RSPLNK");
    _clp_pluginenv(2);
    _clp_memoread(1);
    assign(base+2);//rsp
    pop();
    line(74);
    string(L"c++ ");
    push_symbol(base+2);//rsp
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
    line(75);
    push_symbol(base+7);//cmd
    _clp_run(1);
    pop();
    line(79);
    line(77);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_memoread(1);
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_10_1;
        line(78);
        push_symbol(base+0);//arg
        push_symbol(base+1);//env
        push(&ONE);
        _clp_def_quit(3);
        pop();
    if_10_1:
    if_10_0:;
    line(80);
    push_symbol(base+1);//env
    string(L"OUT");
    _clp_pluginenv(2);
    _clp_ferase(1);
    pop();
    line(101);
    line(82);
    _clp_dirsep(0);
    string(L"/");
    eqeq();
    cmp_1684:;
    if(!flag()) goto if_11_1;
        line(87);
        push_symbol(base+1);//env
        string(L"BUILD_OBJ");
        _clp_pluginenv(2);
        string(L"/log-comid-");
        add();
        push_symbol(base+0);//arg
        idxr0(1);
        add();
        assign(base+8);//tmp
        pop();
        line(88);
        string(L"git log --pretty=format:\"%h %ai\" -1  2>");
        push_symbol(base+10);//null
        add();
        string(L" 1>");
        add();
        push_symbol(base+8);//tmp
        add();
        _clp_run(1);
        pop();
        line(92);
        line(89);
        push_symbol(base+8);//tmp
        _clp_memoread(1);
        assign(base+9);//x
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_12_1;
            line(90);
            string(L"COMMITID[");
            push_symbol(base+9);//x
            add();
            string(L"] ");
            add();
            assign(base+9);//x
            pop();
            line(91);
            push_symbol(base+1);//env
            string(L"TARGET");
            _clp_pluginenv(2);
            push_symbol(base+9);//x
            _clp_cat(2);
            pop();
        if_12_1:
        if_12_0:;
        line(93);
        push_symbol(base+8);//tmp
        _clp_ferase(1);
        pop();
        line(95);
        push_symbol(base+1);//env
        string(L"BUILD_OBJ");
        _clp_pluginenv(2);
        string(L"/log-cccbn-");
        add();
        push_symbol(base+0);//arg
        idxr0(1);
        add();
        assign(base+8);//tmp
        pop();
        line(96);
        string(L"cccbn.exe -n 2>");
        push_symbol(base+10);//null
        add();
        string(L" 1>");
        add();
        push_symbol(base+8);//tmp
        add();
        _clp_run(1);
        pop();
        line(99);
        line(97);
        push_symbol(base+8);//tmp
        _clp_memoread(1);
        assign(base+9);//x
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_13_1;
            line(98);
            push_symbol(base+1);//env
            string(L"TARGET");
            _clp_pluginenv(2);
            push_symbol(base+9);//x
            _clp_cat(2);
            pop();
        if_13_1:
        if_13_0:;
        line(100);
        push_symbol(base+8);//tmp
        _clp_ferase(1);
        pop();
    if_11_1:
    if_11_0:;
    line(103);
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
static void _clp_cat(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("cat",base);
//
    line(108);
    line(109);
    push_symbol(base+0);//fspec
    _clp_channelnew(1);
    assign(base+2);//ch
    push(&TRUE);
    _o_method_open.eval(2);
    pop();
    line(110);
    push_symbol(base+2);//ch
    _o_method_on.eval(1);
    pop();
    line(111);
    push_symbol(base+1);//x
    _clp_qqout(1);
    pop();
    line(112);
    push_symbol(base+2);//ch
    _o_method_close.eval(1);
    pop();
    line(113);
    push_symbol(base+2);//ch
    _o_method_off.eval(1);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

