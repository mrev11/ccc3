//input: build.ppo (5.6.0)

#include <cccdef.h>

static void _blk_build_0(int argno);
static void _blk_build_1(int argno);
static void _blk_build_2(int argno);
static void _blk_build_3(int argno);
static void _blk_build_4(int argno);
static void _blk_build_5(int argno);
extern void _clp___quit(int argno);
extern void _clp_aadd(int argno);
extern void _clp_aclone(int argno);
extern void _clp_alltrim(int argno);
extern void _clp_argv(int argno);
extern void _clp_ascan(int argno);
extern void _clp_asort(int argno);
static void _clp_build(int argno);
extern void _clp_buildenv_bat(int argno);
extern void _clp_buildenv_dbg(int argno);
extern void _clp_buildenv_thr(int argno);
extern void _clp_directory(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_errorlevel(int argno);
extern void _clp_extension_types(int argno);
extern void _clp_ferase(int argno);
extern void _clp_fext(int argno);
extern void _clp_file(int argno);
extern void _clp_fname(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_list_buildenv(int argno);
extern void _clp_main(int argno);
extern void _clp_makeexe(int argno);
extern void _clp_makeexe1(int argno);
extern void _clp_makelib(int argno);
extern void _clp_makeobj(int argno);
extern void _clp_makeso(int argno);
extern void _clp_memoread(int argno);
extern void _clp_normalize(int argno);
extern void _clp_omitted_hash(int argno);
extern void _clp_params(int argno);
extern void _clp_procpar(int argno);
extern void _clp_psort(int argno);
extern void _clp_putenv(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);
extern void _clp_readpar(int argno);
extern void _clp_resource_hash(int argno);
extern void _clp_rules_from_build_bat(int argno);
extern void _clp_s_debug(int argno);
extern void _clp_s_dry(int argno);
extern void _clp_s_incdir(int argno);
extern void _clp_s_libdir(int argno);
extern void _clp_s_libfil(int argno);
extern void _clp_s_libnam(int argno);
extern void _clp_s_main(int argno);
extern void _clp_s_primary(int argno);
extern void _clp_s_quiet(int argno);
extern void _clp_s_resource(int argno);
extern void _clp_s_shared(int argno);
extern void _clp_s_srcdir(int argno);
extern void _clp_s_version(int argno);
extern void _clp_search_include(int argno);
extern void _clp_srcroot(int argno);
extern void _clp_str(int argno);
extern void _clp_strtran(int argno);
extern void _clp_substr(int argno);
extern void _clp_threadpoolnew(int argno);
static void _clp_usage(int argno);
extern void _clp_val(int argno);
extern void _clp_xsplit(int argno);

class _method6_addjob: public _method6_{public: _method6_addjob():_method6_("addjob"){};}; static _method6_addjob _o_method_addjob;
class _method6_wait: public _method6_{public: _method6_wait():_method6_("wait"){};}; static _method6_wait _o_method_wait;

static VALUE* _st_maxthread_ptr()
{
    static stvar _st_maxthread((double)4);
    return _st_maxthread.ptr;
}
static VALUE* _st_pool_ptr()
{
    static stvar _st_pool;
    return _st_pool.ptr;
}
//=======================================================================
void _clp_main(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+2)PUSHNIL();
argno=0;
push_call("main",base);
//
    line(33);
    _clp_argv(0);
    _clp_aclone(1);
    assign(base+0);//opt
    pop();
    line(42);
    line(38);
    _clp_buildenv_bat(0);
    _clp_dirsep(0);
    add();
    string(L"multithread_support");
    add();
    _clp_file(1);
    topnot();
    if(!flag()) goto if_1_1;
        line(39);
        push(&ONE);
        assign(_st_maxthread_ptr());//global
        pop();
    goto if_1_0;
    if_1_1:
    line(40);
    push(&ONE);
    _clp_buildenv_thr(0);
    _clp_val(1);
    lteq();
    if(!flag()) goto if_1_2;
        line(41);
        _clp_buildenv_thr(0);
        _clp_val(1);
        assign(_st_maxthread_ptr());//global
        pop();
    if_1_2:
    if_1_0:;
    line(48);
    line(44);
    _clp_s_quiet(0);
    topnot();
    if(!flag()) goto if_2_1;
        line(45);
        string(nls_text(L"CCC Program Builder "));
        string(L"1.6.2");
        add();
        string(L" Copyright (C) ComFirm Bt.");
        add();
        _clp_qqout(1);
        pop();
        line(46);
        string(L" (Thr");
        push_symbol(_st_maxthread_ptr());//global
        _clp_str(1);
        _clp_alltrim(1);
        add();
        string(L")");
        add();
        _clp_qqout(1);
        pop();
        line(47);
        _clp_qout(0);
        pop();
    if_2_1:
    if_2_0:;
    line(135);
    {
    line(51);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_3_0:
    push_symbol(base+0);//opt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_3_2;
        line(52);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        _clp_procpar(1);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        assign2(idxxl());
        pop();
        line(134);
        line(54);
        string(L"-l");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_1;
            line(55);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            _clp_s_libnam(1);
            pop();
            line(56);
            push(&FALSE);
            _clp_s_shared(1);
            pop();
        goto if_4_0;
        if_4_1:
        line(59);
        string(L"-s");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_2;
            line(60);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            _clp_s_libnam(1);
            pop();
            line(61);
            push(&TRUE);
            _clp_s_shared(1);
            pop();
        goto if_4_0;
        if_4_2:
        line(64);
        string(L"-d");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_3;
            line(69);
            line(65);
            _clp_s_srcdir(0);
            push(&NIL);
            eqeq();
            if(!flag()) goto if_5_1;
                line(66);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_srcdir(1);
                pop();
            goto if_5_0;
            if_5_1:
            line(67);
                line(68);
                _clp_s_srcdir(0);
                string(L",");
                add();
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                add();
                _clp_s_srcdir(1);
                pop();
            if_5_2:
            if_5_0:;
        goto if_4_0;
        if_4_3:
        line(72);
        string(L"-i");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_4;
            line(77);
            line(73);
            _clp_s_incdir(0);
            push(&NIL);
            eqeq();
            if(!flag()) goto if_6_1;
                line(74);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_incdir(1);
                pop();
            goto if_6_0;
            if_6_1:
            line(75);
                line(76);
                _clp_s_incdir(0);
                string(L",");
                add();
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                add();
                _clp_s_incdir(1);
                pop();
            if_6_2:
            if_6_0:;
        goto if_4_0;
        if_4_4:
        line(80);
        string(L"-p");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_5;
            line(85);
            line(81);
            _clp_s_libdir(0);
            push(&NIL);
            eqeq();
            if(!flag()) goto if_7_1;
                line(82);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_libdir(1);
                pop();
            goto if_7_0;
            if_7_1:
            line(83);
                line(84);
                _clp_s_libdir(0);
                string(L",");
                add();
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                add();
                _clp_s_libdir(1);
                pop();
            if_7_2:
            if_7_0:;
        goto if_4_0;
        if_4_5:
        line(88);
        string(L"-b");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_6;
            line(93);
            line(89);
            _clp_s_libfil(0);
            push(&NIL);
            eqeq();
            if(!flag()) goto if_8_1;
                line(90);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_libfil(1);
                pop();
            goto if_8_0;
            if_8_1:
            line(91);
                line(92);
                _clp_s_libfil(0);
                string(L",");
                add();
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                add();
                _clp_s_libfil(1);
                pop();
            if_8_2:
            if_8_0:;
        goto if_4_0;
        if_4_6:
        line(96);
        string(L"-x");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(flag()){
        push(&TRUE);
        }else{
        string(L"-m");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        }
        if(!flag()) goto if_4_7;
            line(101);
            line(97);
            _clp_s_main(0);
            push(&NIL);
            eqeq();
            if(!flag()) goto if_9_1;
                line(98);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_main(1);
                pop();
            goto if_9_0;
            if_9_1:
            line(99);
                line(100);
                _clp_s_main(0);
                string(L",");
                add();
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                add();
                _clp_s_main(1);
                pop();
            if_9_2:
            if_9_0:;
        goto if_4_0;
        if_4_7:
        line(103);
        string(L"-o");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_8;
            line(104);
            push(&TRUE);
            _clp_omitted_hash(0);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            string(L"\\");
            string(L"/");
            _clp_strtran(3);
            assign2(idxxl());
            pop();
        goto if_4_0;
        if_4_8:
        line(106);
        string(L"-h");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_9;
            line(107);
            _clp_usage(0);
            pop();
            line(108);
            _clp___quit(0);
            pop();
        goto if_4_0;
        if_4_9:
        line(110);
        string(L"-q");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_10;
            line(111);
            push(&TRUE);
            _clp_s_quiet(1);
            pop();
        goto if_4_0;
        if_4_10:
        line(113);
        string(L"-v");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_11;
            line(114);
            push(&TRUE);
            _clp_s_version(1);
            pop();
        goto if_4_0;
        if_4_11:
        line(116);
        string(L"--debug");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        if(!flag()) goto if_4_12;
            line(117);
            push(&TRUE);
            _clp_s_debug(1);
            pop();
        goto if_4_0;
        if_4_12:
        line(119);
        string(L"--dry");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        if(!flag()) goto if_4_13;
            line(120);
            push(&TRUE);
            _clp_s_debug(1);
            pop();
            line(121);
            push(&TRUE);
            _clp_s_dry(1);
            pop();
        goto if_4_0;
        if_4_13:
        line(123);
        string(L"@");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        push(&ONE);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_14;
            line(124);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(2);
            _clp_substr(2);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            _clp_readpar(3);
            pop();
        goto if_4_0;
        if_4_14:
        line(126);
        string(L"=");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        ss();
        if(!flag()) goto if_4_15;
            line(127);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_putenv(1);
            pop();
        goto if_4_0;
        if_4_15:
        line(129);
            line(130);
            string(nls_text(L"Invalid switch: "));
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_qout(2);
            pop();
            line(131);
            _clp_usage(0);
            pop();
            line(132);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(133);
            _clp___quit(0);
            pop();
        if_4_16:
        if_4_0:;
    lab_3_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+1);//n
    add();
    assign(base+1);//n
    goto lab_3_0;
    lab_3_2:;
    }
    line(140);
    line(138);
    string(L"on");
    _clp_buildenv_dbg(0);
    ss();
    if(!flag()) goto if_10_1;
        line(139);
        push(&TRUE);
        _clp_s_debug(1);
        pop();
    if_10_1:
    if_10_0:;
    line(143);
    line(141);
    string(L"debug");
    _clp_buildenv_dbg(0);
    ss();
    if(!flag()) goto if_11_1;
        line(142);
        push(&TRUE);
        _clp_s_debug(1);
        pop();
    if_11_1:
    if_11_0:;
    line(147);
    line(144);
    string(L"dry");
    _clp_buildenv_dbg(0);
    ss();
    if(!flag()) goto if_12_1;
        line(145);
        push(&TRUE);
        _clp_s_debug(1);
        pop();
        line(146);
        push(&TRUE);
        _clp_s_dry(1);
        pop();
    if_12_1:
    if_12_0:;
    line(151);
    line(149);
    _clp_s_version(0);
    if(!flag()) goto if_13_1;
        line(150);
        _clp___quit(0);
        pop();
    if_13_1:
    if_13_0:;
    line(153);
    _clp_rules_from_build_bat(0);
    pop();
    line(154);
    _clp_extension_types(0);
    pop();
    line(156);
    _clp_srcroot(0);
    pop();
    line(157);
    _clp_params(0);
    pop();
    line(163);
    line(159);
    _clp_s_debug(0);
    if(!flag()) goto if_14_1;
        line(160);
        push(&ONE);
        assign(_st_maxthread_ptr());//global
        pop();
        line(161);
        string(L"1");
        _clp_buildenv_thr(1);
        pop();
        line(162);
        _clp_list_buildenv(0);
        pop();
    if_14_1:
    if_14_0:;
    line(165);
    push_symbol(_st_maxthread_ptr());//global
    _clp_threadpoolnew(1);
    assign(_st_pool_ptr());//global
    pop();
    line(167);
    _clp_build(0);
    pop();
    line(169);
    _clp_qout(0);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_usage(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("usage",base);
//
    line(174);
    string(nls_text(L"BUILD -xExeNam|-lLibNam -dSrcDir -iIncDir -pLibDir -bLibFil -mMain"));
    _clp_qout(1);
    pop();
    line(175);
    _clp_qout(0);
    pop();
    line(176);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_build(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+12)PUSHNIL();
argno=0;
push_call("build",base);
//
    line(183);
    array(0);
    assign(base+0);//dir
    pop();
    line(184);
    array(0);
    assign(base+1);//obj
    pop();
    line(185);
    array(0);
    assign(base+2);//lib
    pop();
    line(186);
    array(0);
    assign(base+3);//mmd
    pop();
    line(187);
    array(0);
    assign(base+4);//todo
    pop();
    line(189);
    line(194);
    line(192);
    _clp_s_main(0);
    push(&NIL);
    neeq();
    if(!flag()) goto if_15_1;
        line(193);
        _clp_s_main(0);
        string(L",;");
        _clp_xsplit(2);
        assign(base+3);//mmd
        pop();
    if_15_1:
    if_15_0:;
    line(201);
    line(197);
    _clp_s_srcdir(0);
    push(&NIL);
    neeq();
    if(!flag()) goto if_16_1;
        line(198);
        _clp_s_srcdir(0);
        string(L",;");
        _clp_xsplit(2);
        assign(base+0);//dir
        pop();
    goto if_16_0;
    if_16_1:
    line(199);
        line(200);
        string(L".");
        array(1);
        assign(base+0);//dir
        pop();
    if_16_2:
    if_16_0:;
    line(225);
    {
    line(203);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_17_0:
    push_symbol(base+0);//dir
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_17_2;
        line(205);
        string(L"");
        push_symbol(base+0);//dir
        push_symbol(base+8);//n
        idxr();
        _clp_qqout(2);
        pop();
        line(207);
        push_symbol(base+0);//dir
        push_symbol(base+8);//n
        idxr();
        _clp_dirsep(0);
        add();
        string(L"*.*");
        add();
        string(L"H");
        _clp_directory(2);
        assign(base+5);//d1
        pop();
        line(224);
        {
        line(209);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//i
        lab_18_0:
        push_symbol(base+5);//d1
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_18_2;
            line(211);
            push_symbol(base+5);//d1
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            assign(base+6);//f
            pop();
            line(219);
            line(213);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            _clp_s_primary(0);
            ss();
            if(!flag()) goto if_19_1;
                line(218);
                line(214);
                _clp_omitted_hash(0);
                push_symbol(base+0);//dir
                push_symbol(base+8);//n
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+6);//f
                add();
                string(L"\\");
                string(L"/");
                _clp_strtran(3);
                idxr();
                push(&NIL);
                neeq();
                if(!flag()) goto if_20_1;
                goto if_20_0;
                if_20_1:
                line(216);
                    line(217);
                    push_symbol(base+1);//obj
                    push_symbol(base+0);//dir
                    push_symbol(base+8);//n
                    idxr();
                    _clp_dirsep(0);
                    add();
                    push_symbol(base+6);//f
                    add();
                    _clp_aadd(2);
                    pop();
                if_20_2:
                if_20_0:;
            if_19_1:
            if_19_0:;
            line(223);
            line(221);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            _clp_s_resource(0);
            ss();
            if(!flag()) goto if_21_1;
                line(222);
                push_symbol(base+0);//dir
                push_symbol(base+8);//n
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+6);//f
                add();
                _clp_resource_hash(0);
                push_symbol(base+6);//f
                assign2(idxxl());
                pop();
            if_21_1:
            if_21_0:;
        lab_18_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//i
        add();
        assign(base+9);//i
        goto lab_18_0;
        lab_18_2:;
        }
    lab_17_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_17_0;
    lab_17_2:;
    }
    line(226);
    _clp_qout(0);
    pop();
    line(262);
    {
    line(231);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_22_0:
    push_symbol(base+1);//obj
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_22_2;
        line(233);
        push_symbol(base+1);//obj
        push_symbol(base+8);//n
        idxr();
        assign(base+6);//f
        pop();
        line(234);
        push_symbol(base+6);//f
        _clp_fname(1);
        assign(base+7);//o
        pop();
        line(235);
        push_symbol(base+6);//f
        _clp_memoread(1);
        assign(base+10);//txt
        pop();
        line(245);
        line(237);
        push(&ZERO);
        push_symbol(base+3);//mmd
        push_symbol_ref(base+7);//o
        block(_blk_build_0,1);
        _clp_ascan(2);
        neeq();
        if(!flag()) goto if_23_1;
        goto if_23_0;
        if_23_1:
        line(239);
        push_symbol(base+6);//f
        _clp_fext(1);
        string(L".prg");
        eqeq();
        if(!flag()){
        push(&FALSE);
        }else{
        string(L"function main(");
        push_symbol(base+10);//txt
        ss();
        }
        if(!flag()) goto if_23_2;
            line(242);
            line(240);
            _clp_s_main(0);
            push(&NIL);
            eqeq();
            if(!flag()) goto if_24_1;
                line(241);
                push_symbol(base+3);//mmd
                push_symbol(base+7);//o
                _clp_aadd(2);
                pop();
            if_24_1:
            if_24_0:;
        goto if_23_0;
        if_23_2:
        line(243);
            line(244);
            push_symbol(base+2);//lib
            push_symbol(base+7);//o
            _clp_aadd(2);
            pop();
        if_23_3:
        if_23_0:;
        line(247);
        push_symbol(base+7);//o
        string(L".obj");
        add();
        push_symbol(base+6);//f
        array(2);
        assign(base+11);//dep
        pop();
        line(259);
        {
        line(248);
        push(&ONE);
        int sg=sign();
        number(2);
        assign(base+9);//i
        lab_25_0:
        push_symbol(base+11);//dep
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_25_2;
            line(257);
            line(249);
            push_symbol(base+9);//i
            number(2);
            eqeq();
            if(!flag()) goto if_26_1;
            goto if_26_0;
            if_26_1:
            line(251);
            push_symbol(base+9);//i
            number(1024);
            gt();
            if(!flag()) goto if_26_2;
                line(252);
                string(L"recursive dependencies:");
                push_symbol(base+11);//dep
                _clp_qout(2);
                pop();
                line(253);
                _clp_qout(0);
                pop();
                line(254);
                _clp___quit(0);
                pop();
            goto if_26_0;
            if_26_2:
            line(255);
                line(256);
                push_symbol(base+11);//dep
                push_symbol(base+9);//i
                idxr();
                _clp_memoread(1);
                assign(base+10);//txt
                pop();
            if_26_3:
            if_26_0:;
            line(258);
            push_symbol(base+10);//txt
            push_symbol(base+11);//dep
            push_symbol(base+0);//dir
            push_symbol(base+4);//todo
            _clp_search_include(4);
            pop();
        lab_25_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//i
        add();
        assign(base+9);//i
        goto lab_25_0;
        lab_25_2:;
        }
        line(261);
        push_symbol(base+4);//todo
        push_symbol(base+11);//dep
        _clp_aadd(2);
        pop();
    lab_22_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_22_0;
    lab_22_2:;
    }
    line(264);
    push_symbol(base+4);//todo
    _clp_normalize(1);
    pop();
    line(266);
    push_symbol(base+4);//todo
    push(&NIL);
    push(&NIL);
    block(_blk_build_1,0);
    _clp_asort(4);
    pop();
    line(278);
    line(270);
    _clp_s_debug(0);
    if(!flag()) goto if_27_1;
        line(271);
        string(L"main:");
        push_symbol(base+3);//mmd
        _clp_qout(2);
        pop();
        line(272);
        string(L"lib :");
        push_symbol(base+2);//lib
        _clp_qout(2);
        pop();
        line(273);
        _clp_qout(0);
        pop();
        line(276);
        {
        line(274);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_28_0:
        push_symbol(base+4);//todo
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_28_2;
            line(275);
            push_symbol(base+4);//todo
            push_symbol(base+8);//n
            idxr();
            _clp_qout(1);
            pop();
        lab_28_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+8);//n
        add();
        assign(base+8);//n
        goto lab_28_0;
        lab_28_2:;
        }
        line(277);
        _clp_qout(0);
        pop();
    if_27_1:
    if_27_0:;
    line(280);
    string(L"error");
    _clp_ferase(1);
    pop();
    line(285);
    {
    line(281);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_29_0:
    push_symbol(base+4);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_29_2;
        line(284);
        line(282);
        push_symbol(base+4);//todo
        push_symbol(base+8);//n
        idxr();
        idxr0(1);
        _clp_fext(1);
        string(L".obj");
        eqeq();
        topnot();
        if(!flag()) goto if_30_1;
            line(283);
            push_symbol(_st_pool_ptr());//global
            push_symbol_ref(base+4);//todo
            block(_blk_build_2,1);
            push_symbol(base+8);//n
            array(2);
            _o_method_addjob.eval(2);
            pop();
        if_30_1:
        if_30_0:;
    lab_29_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_29_0;
    lab_29_2:;
    }
    line(286);
    push_symbol(_st_pool_ptr());//global
    _o_method_wait.eval(1);
    pop();
    line(292);
    {
    line(288);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_31_0:
    push_symbol(base+4);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_31_2;
        line(291);
        line(289);
        push_symbol(base+4);//todo
        push_symbol(base+8);//n
        idxr();
        idxr0(1);
        _clp_fext(1);
        string(L".obj");
        eqeq();
        if(!flag()) goto if_32_1;
            line(290);
            push_symbol(_st_pool_ptr());//global
            push_symbol_ref(base+4);//todo
            block(_blk_build_3,1);
            push_symbol(base+8);//n
            array(2);
            _o_method_addjob.eval(2);
            pop();
        if_32_1:
        if_32_0:;
    lab_31_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_31_0;
    lab_31_2:;
    }
    line(293);
    push_symbol(_st_pool_ptr());//global
    _o_method_wait.eval(1);
    pop();
    line(311);
    line(297);
    _clp_s_libnam(0);
    push(&NIL);
    neeq();
    if(!flag()) goto if_33_1;
        line(298);
        _clp_s_libnam(0);
        push_symbol(base+2);//lib
        _clp_makelib(2);
        pop();
        line(302);
        line(300);
        _clp_s_shared(0);
        push(&TRUE);
        eqeq();
        if(!flag()){
        push(&FALSE);
        }else{
        _clp_dirsep(0);
        string(L"/");
        eqeq();
        }
        if(!flag()) goto if_34_1;
            line(301);
            _clp_s_libnam(0);
            push_symbol(base+2);//lib
            _clp_makeso(2);
            pop();
        if_34_1:
        if_34_0:;
        line(306);
        {
        line(304);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_35_0:
        push_symbol(base+3);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_35_2;
            line(305);
            push_symbol(_st_pool_ptr());//global
            block(_blk_build_4,0);
            push_symbol(base+3);//mmd
            push_symbol(base+8);//n
            idxr();
            _clp_s_libnam(0);
            array(3);
            _o_method_addjob.eval(2);
            pop();
        lab_35_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+8);//n
        add();
        assign(base+8);//n
        goto lab_35_0;
        lab_35_2:;
        }
    goto if_33_0;
    if_33_1:
    line(307);
        line(310);
        {
        line(308);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_36_0:
        push_symbol(base+3);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_36_2;
            line(309);
            push_symbol(_st_pool_ptr());//global
            block(_blk_build_5,0);
            push_symbol(base+3);//mmd
            push_symbol(base+8);//n
            idxr();
            push_symbol(base+2);//lib
            array(3);
            _o_method_addjob.eval(2);
            pop();
        lab_36_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+8);//n
        add();
        assign(base+8);//n
        goto lab_36_0;
        lab_36_2:;
        }
    if_33_2:
    if_33_0:;
    line(312);
    push_symbol(_st_pool_ptr());//global
    _o_method_wait.eval(1);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_build_0(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_build_0",base);
//
    push_symbol(base+1);//m
    push_symbol(env+0);//o
    eqeq();
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_build_1(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_build_1",base);
//
    push_symbol(base+1);//x
    push_symbol(base+2);//y
    _clp_psort(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_build_2(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_build_2",base);
//
    push_symbol(env+0);//todo
    push_symbol(base+1);//i
    idxr();
    _clp_makeobj(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_build_3(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_build_3",base);
//
    push_symbol(env+0);//todo
    push_symbol(base+1);//i
    idxr();
    _clp_makeobj(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_build_4(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_build_4",base);
//
    push_symbol(base+1);//m
    push_symbol(base+2);//l
    _clp_makeexe1(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_build_5(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_build_5",base);
//
    push_symbol(base+1);//m
    push_symbol(base+2);//l
    _clp_makeexe(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================

