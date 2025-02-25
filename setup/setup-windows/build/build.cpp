//input: ppo/build.ppo (5.7.0.1)

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
extern void _clp_argv(int argno);
extern void _clp_ascan(int argno);
extern void _clp_asort(int argno);
static void _clp_build(int argno);
extern void _clp_buildenv_bat(int argno);
extern void _clp_buildenv_dbg(int argno);
extern void _clp_buildenv_obj(int argno);
extern void _clp_buildenv_root(int argno);
extern void _clp_buildenv_thr(int argno);
extern void _clp_curdir(int argno);
extern void _clp_directory(int argno);
extern void _clp_direxist(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_empty(int argno);
extern void _clp_errorlevel(int argno);
extern void _clp_extension_types(int argno);
extern void _clp_ferase(int argno);
extern void _clp_fext(int argno);
extern void _clp_fname(int argno);
extern void _clp_fnameext(int argno);
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
extern void _clp_s_runcnt(int argno);
extern void _clp_s_shared(int argno);
extern void _clp_s_srcdir(int argno);
extern void _clp_s_version(int argno);
extern void _clp_search_include(int argno);
extern void _clp_srcroot(int argno);
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
while(stack<base+3)PUSHNIL();
argno=0;
push_call("main",base);
//
    line(33);
    _clp_argv(0);
    _clp_aclone(1);
    assign(base+0);//opt
    pop();
    line(34);
    _clp_dirsep(0);
    _clp_curdir(0);
    add();
    assign(base+2);//project
    pop();
    line(39);
    _clp_buildenv_obj(0);
    _clp_s_libdir(1);
    pop();
    line(125);
    {
    line(41);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_1_0:
    push_symbol(base+0);//opt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(42);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        _clp_procpar(1);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        assign2(idxxl());
        pop();
        line(124);
        line(44);
        string(L"-l");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_164:;
        if(!flag()) goto if_2_1;
            line(45);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            _clp_s_libnam(1);
            pop();
            line(46);
            push(&FALSE);
            _clp_s_shared(1);
            pop();
        goto if_2_0;
        if_2_1:
        line(49);
        string(L"-s");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_248:;
        if(!flag()) goto if_2_2;
            line(50);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            _clp_s_libnam(1);
            pop();
            line(51);
            push(&TRUE);
            _clp_s_shared(1);
            pop();
        goto if_2_0;
        if_2_2:
        line(54);
        string(L"-d");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_332:;
        if(!flag()) goto if_2_3;
            line(59);
            line(55);
            _clp_s_srcdir(0);
            push(&NIL);
            eqeq();
            cmp_371:;
            if(!flag()) goto if_3_1;
                line(56);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_srcdir(1);
                pop();
            goto if_3_0;
            if_3_1:
            line(57);
                line(58);
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
            if_3_2:
            if_3_0:;
        goto if_2_0;
        if_2_3:
        line(62);
        string(L"-i");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_481:;
        if(!flag()) goto if_2_4;
            line(67);
            line(63);
            _clp_s_incdir(0);
            push(&NIL);
            eqeq();
            cmp_520:;
            if(!flag()) goto if_4_1;
                line(64);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_incdir(1);
                pop();
            goto if_4_0;
            if_4_1:
            line(65);
                line(66);
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
            if_4_2:
            if_4_0:;
        goto if_2_0;
        if_2_4:
        line(70);
        string(L"-p");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_630:;
        if(!flag()) goto if_2_5;
            line(75);
            line(71);
            _clp_s_libdir(0);
            push(&NIL);
            eqeq();
            cmp_669:;
            if(!flag()) goto if_5_1;
                line(72);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_libdir(1);
                pop();
            goto if_5_0;
            if_5_1:
            line(73);
                line(74);
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
            if_5_2:
            if_5_0:;
        goto if_2_0;
        if_2_5:
        line(78);
        string(L"-b");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_779:;
        if(!flag()) goto if_2_6;
            line(83);
            line(79);
            _clp_s_libfil(0);
            push(&NIL);
            eqeq();
            cmp_818:;
            if(!flag()) goto if_6_1;
                line(80);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_libfil(1);
                pop();
            goto if_6_0;
            if_6_1:
            line(81);
                line(82);
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
            if_6_2:
            if_6_0:;
        goto if_2_0;
        if_2_6:
        line(86);
        string(L"-x");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_928:;
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
        cmp_955:;
        }
        if(!flag()) goto if_2_7;
            line(91);
            line(87);
            _clp_s_main(0);
            push(&NIL);
            eqeq();
            cmp_995:;
            if(!flag()) goto if_7_1;
                line(88);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_main(1);
                pop();
            goto if_7_0;
            if_7_1:
            line(89);
                line(90);
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
            if_7_2:
            if_7_0:;
        goto if_2_0;
        if_2_7:
        line(93);
        string(L"-o");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_1105:;
        if(!flag()) goto if_2_8;
            line(94);
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
        goto if_2_0;
        if_2_8:
        line(96);
        string(L"-h");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_1200:;
        if(!flag()) goto if_2_9;
            line(97);
            _clp_usage(0);
            pop();
            line(98);
            _clp___quit(0);
            pop();
        goto if_2_0;
        if_2_9:
        line(100);
        string(L"-q");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_1252:;
        if(!flag()) goto if_2_10;
            line(101);
            push(&TRUE);
            _clp_s_quiet(1);
            pop();
        goto if_2_0;
        if_2_10:
        line(103);
        string(L"-v");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_1302:;
        if(!flag()) goto if_2_11;
            line(104);
            push(&TRUE);
            _clp_s_version(1);
            pop();
        goto if_2_0;
        if_2_11:
        line(106);
        string(L"--debug");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        cmp_1352:;
        if(!flag()) goto if_2_12;
            line(107);
            push(&TRUE);
            _clp_s_debug(1);
            pop();
        goto if_2_0;
        if_2_12:
        line(109);
        string(L"--dry");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        cmp_1387:;
        if(!flag()) goto if_2_13;
            line(110);
            push(&TRUE);
            _clp_s_debug(1);
            pop();
            line(111);
            push(&TRUE);
            _clp_s_dry(1);
            pop();
        goto if_2_0;
        if_2_13:
        line(113);
        string(L"@");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        push(&ONE);
        _clp_left(2);
        eqeq();
        cmp_1436:;
        if(!flag()) goto if_2_14;
            line(114);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(2);
            _clp_substr(2);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            _clp_readpar(3);
            pop();
        goto if_2_0;
        if_2_14:
        line(116);
        string(L"=");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        ss();
        if(!flag()) goto if_2_15;
            line(117);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_putenv(1);
            pop();
        goto if_2_0;
        if_2_15:
        line(119);
            line(120);
            string(nls_text(L"Invalid switch: "));
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_qout(2);
            pop();
            line(121);
            _clp_usage(0);
            pop();
            line(122);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(123);
            _clp___quit(0);
            pop();
        if_2_16:
        if_2_0:;
    lab_1_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+1);//n
    add();
    assign(base+1);//n
    goto lab_1_0;
    lab_1_2:;
    }
    line(131);
    line(128);
    _clp_s_version(0);
    if(!flag()) goto if_8_1;
        line(129);
        string(nls_text(L"CCC Program Builder "));
        string(L"1.7.1");
        add();
        string(L" Copyright (C) ComFirm Bt.");
        add();
        _clp_qqout(1);
        pop();
        _clp_qout(0);
        pop();
        line(130);
        _clp___quit(0);
        pop();
    if_8_1:
    if_8_0:;
    line(135);
    line(132);
    _clp_buildenv_bat(0);
    _clp_empty(1);
    if(!flag()) goto if_9_1;
        line(133);
        string(L"BUILD_BAT environment not set");
        _clp_qqout(1);
        pop();
        _clp_qout(0);
        pop();
        line(134);
        _clp___quit(0);
        pop();
    if_9_1:
    if_9_0:;
    line(139);
    line(136);
    _clp_buildenv_bat(0);
    _clp_direxist(1);
    topnot();
    if(!flag()) goto if_10_1;
        line(137);
        string(L"BUILD_BAT directory does not exist [");
        _clp_buildenv_bat(0);
        add();
        string(L"]");
        add();
        _clp_qqout(1);
        pop();
        _clp_qout(0);
        pop();
        line(138);
        _clp___quit(0);
        pop();
    if_10_1:
    if_10_0:;
    line(143);
    line(140);
    _clp_buildenv_bat(0);
    _clp_dirsep(0);
    add();
    string(L"prg2obj.*");
    add();
    _clp_directory(1);
    _clp_empty(1);
    if(!flag()) goto if_11_1;
        line(141);
        string(L"BUILD_BAT directory does not contain script for prg2ppo [");
        _clp_buildenv_bat(0);
        add();
        string(L"]");
        add();
        _clp_qqout(1);
        pop();
        _clp_qout(0);
        pop();
        line(142);
        _clp___quit(0);
        pop();
    if_11_1:
    if_11_0:;
    line(145);
    push(&ONE);
    assign(_st_maxthread_ptr());//global
    pop();
    line(148);
    line(146);
    push(&ONE);
    _clp_buildenv_thr(0);
    _clp_val(1);
    lteq();
    cmp_1938:;
    if(!flag()) goto if_12_1;
        line(147);
        _clp_buildenv_thr(0);
        _clp_val(1);
        assign(_st_maxthread_ptr());//global
        pop();
    if_12_1:
    if_12_0:;
    line(171);
    line(151);
    _clp_s_quiet(0);
    topnot();
    if(!flag()) goto if_13_1;
        line(169);
        line(152);
        _clp_buildenv_root(0);
        _clp_empty(1);
        if(!flag()) goto if_14_1;
            line(156);
            push_symbol(base+2);//project
            _clp_fnameext(1);
            assign(base+2);//project
            pop();
        goto if_14_0;
        if_14_1:
        line(157);
            line(165);
            push_symbol(base+2);//project
            _clp_buildenv_root(0);
            string(L"");
            _clp_strtran(3);
            assign(base+2);//project
            pop();
            line(168);
            line(166);
            push_symbol(base+2);//project
            push(&ONE);
            _clp_left(2);
            _clp_dirsep(0);
            eqeq();
            cmp_2100:;
            if(!flag()) goto if_15_1;
                line(167);
                push_symbol(base+2);//project
                number(2);
                _clp_substr(2);
                assign(base+2);//project
                pop();
            if_15_1:
            if_15_0:;
        if_14_2:
        if_14_0:;
        line(170);
        string(L"BUILD => [");
        push_symbol(base+2);//project
        add();
        string(L"]");
        add();
        _clp_qqout(1);
        pop();
    if_13_1:
    if_13_0:;
    line(177);
    line(175);
    string(L"on");
    _clp_buildenv_dbg(0);
    ss();
    if(!flag()) goto if_16_1;
        line(176);
        push(&TRUE);
        _clp_s_debug(1);
        pop();
    if_16_1:
    if_16_0:;
    line(180);
    line(178);
    string(L"debug");
    _clp_buildenv_dbg(0);
    ss();
    if(!flag()) goto if_17_1;
        line(179);
        push(&TRUE);
        _clp_s_debug(1);
        pop();
    if_17_1:
    if_17_0:;
    line(184);
    line(181);
    string(L"dry");
    _clp_buildenv_dbg(0);
    ss();
    if(!flag()) goto if_18_1;
        line(182);
        push(&TRUE);
        _clp_s_debug(1);
        pop();
        line(183);
        push(&TRUE);
        _clp_s_dry(1);
        pop();
    if_18_1:
    if_18_0:;
    line(187);
    _clp_rules_from_build_bat(0);
    pop();
    line(188);
    _clp_extension_types(0);
    pop();
    line(190);
    _clp_srcroot(0);
    pop();
    line(191);
    _clp_params(0);
    pop();
    line(197);
    line(193);
    _clp_s_debug(0);
    if(!flag()) goto if_19_1;
        line(194);
        push(&ONE);
        assign(_st_maxthread_ptr());//global
        pop();
        line(195);
        string(L"1");
        _clp_buildenv_thr(1);
        pop();
        line(196);
        _clp_list_buildenv(0);
        pop();
    if_19_1:
    if_19_0:;
    line(199);
    push_symbol(_st_maxthread_ptr());//global
    _clp_threadpoolnew(1);
    assign(_st_pool_ptr());//global
    pop();
    line(201);
    _clp_build(0);
    pop();
    line(205);
    line(203);
    _clp_s_runcnt(0);
    push(&ZERO);
    gt();
    cmp_2473:;
    if(!flag()) goto if_20_1;
        line(204);
        _clp_qout(0);
        pop();
    if_20_1:
    if_20_0:;
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
    line(210);
    string(nls_text(L"BUILD -xExeNam|-lLibNam -dSrcDir -iIncDir -pLibDir -bLibFil -mMain"));
    _clp_qout(1);
    pop();
    line(211);
    _clp_qout(0);
    pop();
    line(212);
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
while(stack<base+13)PUSHNIL();
argno=0;
push_call("build",base);
//
    line(219);
    array(0);
    assign(base+0);//dir
    pop();
    line(220);
    array(0);
    assign(base+1);//inc
    pop();
    line(221);
    array(0);
    assign(base+2);//obj
    pop();
    line(222);
    array(0);
    assign(base+3);//lib
    pop();
    line(223);
    array(0);
    assign(base+4);//mmd
    pop();
    line(224);
    array(0);
    assign(base+5);//todo
    pop();
    line(226);
    line(231);
    line(229);
    _clp_s_main(0);
    push(&NIL);
    neeq();
    cmp_2682:;
    if(!flag()) goto if_21_1;
        line(230);
        _clp_s_main(0);
        string(L",;");
        _clp_xsplit(2);
        assign(base+4);//mmd
        pop();
    if_21_1:
    if_21_0:;
    line(238);
    line(234);
    _clp_s_srcdir(0);
    push(&NIL);
    neeq();
    cmp_2744:;
    if(!flag()) goto if_22_1;
        line(235);
        _clp_s_srcdir(0);
        string(L",;");
        _clp_xsplit(2);
        assign(base+0);//dir
        pop();
    goto if_22_0;
    if_22_1:
    line(236);
        line(237);
        string(L".");
        array(1);
        assign(base+0);//dir
        pop();
    if_22_2:
    if_22_0:;
    line(245);
    line(241);
    _clp_s_incdir(0);
    push(&NIL);
    neeq();
    cmp_2821:;
    if(!flag()) goto if_23_1;
        line(242);
        _clp_s_incdir(0);
        string(L",;");
        _clp_xsplit(2);
        assign(base+1);//inc
        pop();
    goto if_23_0;
    if_23_1:
    line(243);
        line(244);
        array(0);
        assign(base+1);//inc
        pop();
    if_23_2:
    if_23_0:;
    line(248);
    {
    line(246);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_24_0:
    push_symbol(base+0);//dir
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_24_2;
        line(247);
        push_symbol(base+1);//inc
        push_symbol(base+0);//dir
        push_symbol(base+9);//n
        idxr();
        _clp_aadd(2);
        pop();
    lab_24_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_24_0;
    lab_24_2:;
    }
    line(273);
    {
    line(251);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_25_0:
    push_symbol(base+0);//dir
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_25_2;
        line(253);
        string(L"");
        push_symbol(base+0);//dir
        push_symbol(base+9);//n
        idxr();
        _clp_qqout(2);
        pop();
        line(255);
        push_symbol(base+0);//dir
        push_symbol(base+9);//n
        idxr();
        _clp_dirsep(0);
        add();
        string(L"*.*");
        add();
        string(L"H");
        _clp_directory(2);
        assign(base+6);//d1
        pop();
        line(272);
        {
        line(257);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+10);//i
        lab_26_0:
        push_symbol(base+6);//d1
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_26_2;
            line(259);
            push_symbol(base+6);//d1
            push_symbol(base+10);//i
            idxr();
            idxr0(1);
            assign(base+7);//f
            pop();
            line(267);
            line(261);
            push_symbol(base+7);//f
            _clp_fext(1);
            string(L".");
            add();
            _clp_s_primary(0);
            ss();
            if(!flag()) goto if_27_1;
                line(266);
                line(262);
                _clp_omitted_hash(0);
                push_symbol(base+0);//dir
                push_symbol(base+9);//n
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+7);//f
                add();
                string(L"\\");
                string(L"/");
                _clp_strtran(3);
                idxr();
                push(&NIL);
                neeq();
                cmp_3151:;
                if(!flag()) goto if_28_1;
                goto if_28_0;
                if_28_1:
                line(264);
                    line(265);
                    push_symbol(base+2);//obj
                    push_symbol(base+0);//dir
                    push_symbol(base+9);//n
                    idxr();
                    _clp_dirsep(0);
                    add();
                    push_symbol(base+7);//f
                    add();
                    _clp_aadd(2);
                    pop();
                if_28_2:
                if_28_0:;
            if_27_1:
            if_27_0:;
            line(271);
            line(269);
            push_symbol(base+7);//f
            _clp_fext(1);
            string(L".");
            add();
            _clp_s_resource(0);
            ss();
            if(!flag()) goto if_29_1;
                line(270);
                push_symbol(base+0);//dir
                push_symbol(base+9);//n
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+7);//f
                add();
                _clp_resource_hash(0);
                push_symbol(base+7);//f
                assign2(idxxl());
                pop();
            if_29_1:
            if_29_0:;
        lab_26_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+10);//i
        add();
        assign(base+10);//i
        goto lab_26_0;
        lab_26_2:;
        }
    lab_25_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_25_0;
    lab_25_2:;
    }
    line(274);
    _clp_qout(0);
    pop();
    line(310);
    {
    line(279);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_30_0:
    push_symbol(base+2);//obj
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_30_2;
        line(281);
        push_symbol(base+2);//obj
        push_symbol(base+9);//n
        idxr();
        assign(base+7);//f
        pop();
        line(282);
        push_symbol(base+7);//f
        _clp_fname(1);
        assign(base+8);//o
        pop();
        line(283);
        push_symbol(base+7);//f
        _clp_memoread(1);
        assign(base+11);//txt
        pop();
        line(293);
        line(285);
        push(&ZERO);
        push_symbol(base+4);//mmd
        push_symbol_ref(base+8);//o
        block(_blk_build_0,1);
        _clp_ascan(2);
        neeq();
        cmp_3396:;
        if(!flag()) goto if_31_1;
        goto if_31_0;
        if_31_1:
        line(287);
        push_symbol(base+7);//f
        _clp_fext(1);
        string(L".prg");
        eqeq();
        cmp_3452:;
        if(!flag()){
        push(&FALSE);
        }else{
        string(L"function main(");
        push_symbol(base+11);//txt
        ss();
        }
        if(!flag()) goto if_31_2;
            line(290);
            line(288);
            _clp_s_main(0);
            push(&NIL);
            eqeq();
            cmp_3479:;
            if(!flag()) goto if_32_1;
                line(289);
                push_symbol(base+4);//mmd
                push_symbol(base+8);//o
                _clp_aadd(2);
                pop();
            if_32_1:
            if_32_0:;
        goto if_31_0;
        if_31_2:
        line(291);
            line(292);
            push_symbol(base+3);//lib
            push_symbol(base+8);//o
            _clp_aadd(2);
            pop();
        if_31_3:
        if_31_0:;
        line(295);
        push_symbol(base+8);//o
        string(L".obj");
        add();
        push_symbol(base+7);//f
        array(2);
        assign(base+12);//dep
        pop();
        line(307);
        {
        line(296);
        push(&ONE);
        int sg=sign();
        number(2);
        assign(base+10);//i
        lab_33_0:
        push_symbol(base+12);//dep
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_33_2;
            line(305);
            line(297);
            push_symbol(base+10);//i
            number(2);
            eqeq();
            cmp_3603:;
            if(!flag()) goto if_34_1;
            goto if_34_0;
            if_34_1:
            line(299);
            push_symbol(base+10);//i
            number(1024);
            gt();
            cmp_3619:;
            if(!flag()) goto if_34_2;
                line(300);
                string(L"recursive dependencies:");
                push_symbol(base+12);//dep
                _clp_qout(2);
                pop();
                line(301);
                _clp_qout(0);
                pop();
                line(302);
                _clp___quit(0);
                pop();
            goto if_34_0;
            if_34_2:
            line(303);
                line(304);
                push_symbol(base+12);//dep
                push_symbol(base+10);//i
                idxr();
                _clp_memoread(1);
                assign(base+11);//txt
                pop();
            if_34_3:
            if_34_0:;
            line(306);
            push_symbol(base+11);//txt
            push_symbol(base+12);//dep
            push_symbol(base+1);//inc
            push_symbol(base+5);//todo
            _clp_search_include(4);
            pop();
        lab_33_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+10);//i
        add();
        assign(base+10);//i
        goto lab_33_0;
        lab_33_2:;
        }
        line(309);
        push_symbol(base+5);//todo
        push_symbol(base+12);//dep
        _clp_aadd(2);
        pop();
    lab_30_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_30_0;
    lab_30_2:;
    }
    line(312);
    push_symbol(base+5);//todo
    _clp_normalize(1);
    pop();
    line(314);
    push_symbol(base+5);//todo
    push(&NIL);
    push(&NIL);
    block(_blk_build_1,0);
    _clp_asort(4);
    pop();
    line(328);
    line(320);
    _clp_s_debug(0);
    if(!flag()) goto if_35_1;
        line(321);
        string(L"main:");
        push_symbol(base+4);//mmd
        _clp_qout(2);
        pop();
        line(322);
        string(L"lib :");
        push_symbol(base+3);//lib
        _clp_qout(2);
        pop();
        line(323);
        _clp_qout(0);
        pop();
        line(326);
        {
        line(324);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_36_0:
        push_symbol(base+5);//todo
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_36_2;
            line(325);
            push_symbol(base+5);//todo
            push_symbol(base+9);//n
            idxr();
            _clp_qout(1);
            pop();
        lab_36_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_36_0;
        lab_36_2:;
        }
        line(327);
        _clp_qout(0);
        pop();
    if_35_1:
    if_35_0:;
    line(330);
    string(L"error");
    _clp_ferase(1);
    pop();
    line(335);
    {
    line(331);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_37_0:
    push_symbol(base+5);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_37_2;
        line(334);
        line(332);
        push_symbol(base+5);//todo
        push_symbol(base+9);//n
        idxr();
        idxr0(1);
        _clp_fext(1);
        string(L".obj");
        eqeq();
        cmp_4023:;
        topnot();
        if(!flag()) goto if_38_1;
            line(333);
            push_symbol(_st_pool_ptr());//global
            push_symbol_ref(base+5);//todo
            block(_blk_build_2,1);
            push_symbol(base+9);//n
            array(2);
            _o_method_addjob.eval(2);
            pop();
        if_38_1:
        if_38_0:;
    lab_37_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_37_0;
    lab_37_2:;
    }
    line(336);
    push_symbol(_st_pool_ptr());//global
    _o_method_wait.eval(1);
    pop();
    line(342);
    {
    line(338);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_39_0:
    push_symbol(base+5);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_39_2;
        line(341);
        line(339);
        push_symbol(base+5);//todo
        push_symbol(base+9);//n
        idxr();
        idxr0(1);
        _clp_fext(1);
        string(L".obj");
        eqeq();
        cmp_4150:;
        if(!flag()) goto if_40_1;
            line(340);
            push_symbol(_st_pool_ptr());//global
            push_symbol_ref(base+5);//todo
            block(_blk_build_3,1);
            push_symbol(base+9);//n
            array(2);
            _o_method_addjob.eval(2);
            pop();
        if_40_1:
        if_40_0:;
    lab_39_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_39_0;
    lab_39_2:;
    }
    line(343);
    push_symbol(_st_pool_ptr());//global
    _o_method_wait.eval(1);
    pop();
    line(361);
    line(347);
    _clp_s_libnam(0);
    push(&NIL);
    neeq();
    cmp_4243:;
    if(!flag()) goto if_41_1;
        line(348);
        _clp_s_libnam(0);
        push_symbol(base+3);//lib
        _clp_makelib(2);
        pop();
        line(352);
        line(350);
        _clp_s_shared(0);
        push(&TRUE);
        eqeq();
        cmp_4288:;
        if(!flag()){
        push(&FALSE);
        }else{
        _clp_dirsep(0);
        string(L"/");
        eqeq();
        cmp_4300:;
        }
        if(!flag()) goto if_42_1;
            line(351);
            _clp_s_libnam(0);
            push_symbol(base+3);//lib
            _clp_makeso(2);
            pop();
        if_42_1:
        if_42_0:;
        line(356);
        {
        line(354);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_43_0:
        push_symbol(base+4);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_43_2;
            line(355);
            push_symbol(_st_pool_ptr());//global
            block(_blk_build_4,0);
            push_symbol(base+4);//mmd
            push_symbol(base+9);//n
            idxr();
            _clp_s_libnam(0);
            array(3);
            _o_method_addjob.eval(2);
            pop();
        lab_43_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_43_0;
        lab_43_2:;
        }
    goto if_41_0;
    if_41_1:
    line(357);
        line(360);
        {
        line(358);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_44_0:
        push_symbol(base+4);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_44_2;
            line(359);
            push_symbol(_st_pool_ptr());//global
            block(_blk_build_5,0);
            push_symbol(base+4);//mmd
            push_symbol(base+9);//n
            idxr();
            push_symbol(base+3);//lib
            array(3);
            _o_method_addjob.eval(2);
            pop();
        lab_44_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_44_0;
        lab_44_2:;
        }
    if_41_2:
    if_41_0:;
    line(362);
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
    cmp_3415:;
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

