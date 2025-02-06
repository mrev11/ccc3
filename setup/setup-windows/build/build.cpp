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
extern void _clp_alltrim(int argno);
extern void _clp_argv(int argno);
extern void _clp_ascan(int argno);
extern void _clp_asort(int argno);
static void _clp_build(int argno);
extern void _clp_buildenv_bat(int argno);
extern void _clp_buildenv_dbg(int argno);
extern void _clp_buildenv_obj(int argno);
extern void _clp_buildenv_thr(int argno);
extern void _clp_directory(int argno);
extern void _clp_direxist(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_empty(int argno);
extern void _clp_errorlevel(int argno);
extern void _clp_extension_types(int argno);
extern void _clp_ferase(int argno);
extern void _clp_fext(int argno);
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
    line(38);
    _clp_buildenv_obj(0);
    _clp_s_libdir(1);
    pop();
    line(124);
    {
    line(40);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_1_0:
    push_symbol(base+0);//opt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(41);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        _clp_procpar(1);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        assign2(idxxl());
        pop();
        line(123);
        line(43);
        string(L"-l");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_139:;
        if(!flag()) goto if_2_1;
            line(44);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            _clp_s_libnam(1);
            pop();
            line(45);
            push(&FALSE);
            _clp_s_shared(1);
            pop();
        goto if_2_0;
        if_2_1:
        line(48);
        string(L"-s");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_223:;
        if(!flag()) goto if_2_2;
            line(49);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            _clp_s_libnam(1);
            pop();
            line(50);
            push(&TRUE);
            _clp_s_shared(1);
            pop();
        goto if_2_0;
        if_2_2:
        line(53);
        string(L"-d");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_307:;
        if(!flag()) goto if_2_3;
            line(58);
            line(54);
            _clp_s_srcdir(0);
            push(&NIL);
            eqeq();
            cmp_346:;
            if(!flag()) goto if_3_1;
                line(55);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_srcdir(1);
                pop();
            goto if_3_0;
            if_3_1:
            line(56);
                line(57);
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
        line(61);
        string(L"-i");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_456:;
        if(!flag()) goto if_2_4;
            line(66);
            line(62);
            _clp_s_incdir(0);
            push(&NIL);
            eqeq();
            cmp_495:;
            if(!flag()) goto if_4_1;
                line(63);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_incdir(1);
                pop();
            goto if_4_0;
            if_4_1:
            line(64);
                line(65);
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
        line(69);
        string(L"-p");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_605:;
        if(!flag()) goto if_2_5;
            line(74);
            line(70);
            _clp_s_libdir(0);
            push(&NIL);
            eqeq();
            cmp_644:;
            if(!flag()) goto if_5_1;
                line(71);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_libdir(1);
                pop();
            goto if_5_0;
            if_5_1:
            line(72);
                line(73);
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
        line(77);
        string(L"-b");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_754:;
        if(!flag()) goto if_2_6;
            line(82);
            line(78);
            _clp_s_libfil(0);
            push(&NIL);
            eqeq();
            cmp_793:;
            if(!flag()) goto if_6_1;
                line(79);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_libfil(1);
                pop();
            goto if_6_0;
            if_6_1:
            line(80);
                line(81);
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
        line(85);
        string(L"-x");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_903:;
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
        cmp_930:;
        }
        if(!flag()) goto if_2_7;
            line(90);
            line(86);
            _clp_s_main(0);
            push(&NIL);
            eqeq();
            cmp_970:;
            if(!flag()) goto if_7_1;
                line(87);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                _clp_s_main(1);
                pop();
            goto if_7_0;
            if_7_1:
            line(88);
                line(89);
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
        line(92);
        string(L"-o");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_1080:;
        if(!flag()) goto if_2_8;
            line(93);
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
        line(95);
        string(L"-h");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_1175:;
        if(!flag()) goto if_2_9;
            line(96);
            _clp_usage(0);
            pop();
            line(97);
            _clp___quit(0);
            pop();
        goto if_2_0;
        if_2_9:
        line(99);
        string(L"-q");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_1227:;
        if(!flag()) goto if_2_10;
            line(100);
            push(&TRUE);
            _clp_s_quiet(1);
            pop();
        goto if_2_0;
        if_2_10:
        line(102);
        string(L"-v");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        cmp_1277:;
        if(!flag()) goto if_2_11;
            line(103);
            push(&TRUE);
            _clp_s_version(1);
            pop();
        goto if_2_0;
        if_2_11:
        line(105);
        string(L"--debug");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        cmp_1327:;
        if(!flag()) goto if_2_12;
            line(106);
            push(&TRUE);
            _clp_s_debug(1);
            pop();
        goto if_2_0;
        if_2_12:
        line(108);
        string(L"--dry");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        cmp_1362:;
        if(!flag()) goto if_2_13;
            line(109);
            push(&TRUE);
            _clp_s_debug(1);
            pop();
            line(110);
            push(&TRUE);
            _clp_s_dry(1);
            pop();
        goto if_2_0;
        if_2_13:
        line(112);
        string(L"@");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        push(&ONE);
        _clp_left(2);
        eqeq();
        cmp_1411:;
        if(!flag()) goto if_2_14;
            line(113);
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
        line(115);
        string(L"=");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        ss();
        if(!flag()) goto if_2_15;
            line(116);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_putenv(1);
            pop();
        goto if_2_0;
        if_2_15:
        line(118);
            line(119);
            string(nls_text(L"Invalid switch: "));
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_qout(2);
            pop();
            line(120);
            _clp_usage(0);
            pop();
            line(121);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(122);
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
    line(130);
    line(127);
    _clp_s_version(0);
    if(!flag()) goto if_8_1;
        line(128);
        string(nls_text(L"CCC Program Builder "));
        string(L"1.7.0");
        add();
        string(L" Copyright (C) ComFirm Bt.");
        add();
        _clp_qqout(1);
        pop();
        _clp_qout(0);
        pop();
        line(129);
        _clp___quit(0);
        pop();
    if_8_1:
    if_8_0:;
    line(134);
    line(131);
    _clp_buildenv_bat(0);
    _clp_empty(1);
    if(!flag()) goto if_9_1;
        line(132);
        string(L"BUILD_BAT environment not set");
        _clp_qqout(1);
        pop();
        _clp_qout(0);
        pop();
        line(133);
        _clp___quit(0);
        pop();
    if_9_1:
    if_9_0:;
    line(138);
    line(135);
    _clp_buildenv_bat(0);
    _clp_direxist(1);
    topnot();
    if(!flag()) goto if_10_1;
        line(136);
        string(L"BUILD_BAT directory does not exist [");
        _clp_buildenv_bat(0);
        add();
        string(L"]");
        add();
        _clp_qqout(1);
        pop();
        _clp_qout(0);
        pop();
        line(137);
        _clp___quit(0);
        pop();
    if_10_1:
    if_10_0:;
    line(142);
    line(139);
    _clp_buildenv_bat(0);
    _clp_dirsep(0);
    add();
    string(L"prg2obj.*");
    add();
    _clp_directory(1);
    _clp_empty(1);
    if(!flag()) goto if_11_1;
        line(140);
        string(L"BUILD_BAT directory does not contain script for prg2ppo [");
        _clp_buildenv_bat(0);
        add();
        string(L"]");
        add();
        _clp_qqout(1);
        pop();
        _clp_qout(0);
        pop();
        line(141);
        _clp___quit(0);
        pop();
    if_11_1:
    if_11_0:;
    line(144);
    push(&ONE);
    assign(_st_maxthread_ptr());//global
    pop();
    line(147);
    line(145);
    push(&ONE);
    _clp_buildenv_thr(0);
    _clp_val(1);
    lteq();
    cmp_1913:;
    if(!flag()) goto if_12_1;
        line(146);
        _clp_buildenv_thr(0);
        _clp_val(1);
        assign(_st_maxthread_ptr());//global
        pop();
    if_12_1:
    if_12_0:;
    line(154);
    line(150);
    _clp_s_quiet(0);
    topnot();
    if(!flag()) goto if_13_1;
        line(151);
        string(nls_text(L"CCC Program Builder "));
        string(L"1.7.0");
        add();
        string(L" Copyright (C) ComFirm Bt.");
        add();
        _clp_qqout(1);
        pop();
        line(152);
        string(L" (Thr");
        push_symbol(_st_maxthread_ptr());//global
        _clp_str(1);
        _clp_alltrim(1);
        add();
        string(L")");
        add();
        _clp_qqout(1);
        pop();
        line(153);
        _clp_qout(0);
        pop();
    if_13_1:
    if_13_0:;
    line(160);
    line(158);
    string(L"on");
    _clp_buildenv_dbg(0);
    ss();
    if(!flag()) goto if_14_1;
        line(159);
        push(&TRUE);
        _clp_s_debug(1);
        pop();
    if_14_1:
    if_14_0:;
    line(163);
    line(161);
    string(L"debug");
    _clp_buildenv_dbg(0);
    ss();
    if(!flag()) goto if_15_1;
        line(162);
        push(&TRUE);
        _clp_s_debug(1);
        pop();
    if_15_1:
    if_15_0:;
    line(167);
    line(164);
    string(L"dry");
    _clp_buildenv_dbg(0);
    ss();
    if(!flag()) goto if_16_1;
        line(165);
        push(&TRUE);
        _clp_s_debug(1);
        pop();
        line(166);
        push(&TRUE);
        _clp_s_dry(1);
        pop();
    if_16_1:
    if_16_0:;
    line(170);
    _clp_rules_from_build_bat(0);
    pop();
    line(171);
    _clp_extension_types(0);
    pop();
    line(173);
    _clp_srcroot(0);
    pop();
    line(174);
    _clp_params(0);
    pop();
    line(180);
    line(176);
    _clp_s_debug(0);
    if(!flag()) goto if_17_1;
        line(177);
        push(&ONE);
        assign(_st_maxthread_ptr());//global
        pop();
        line(178);
        string(L"1");
        _clp_buildenv_thr(1);
        pop();
        line(179);
        _clp_list_buildenv(0);
        pop();
    if_17_1:
    if_17_0:;
    line(182);
    push_symbol(_st_maxthread_ptr());//global
    _clp_threadpoolnew(1);
    assign(_st_pool_ptr());//global
    pop();
    line(184);
    _clp_build(0);
    pop();
    line(186);
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
    line(191);
    string(nls_text(L"BUILD -xExeNam|-lLibNam -dSrcDir -iIncDir -pLibDir -bLibFil -mMain"));
    _clp_qout(1);
    pop();
    line(192);
    _clp_qout(0);
    pop();
    line(193);
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
    line(200);
    array(0);
    assign(base+0);//dir
    pop();
    line(201);
    array(0);
    assign(base+1);//inc
    pop();
    line(202);
    array(0);
    assign(base+2);//obj
    pop();
    line(203);
    array(0);
    assign(base+3);//lib
    pop();
    line(204);
    array(0);
    assign(base+4);//mmd
    pop();
    line(205);
    array(0);
    assign(base+5);//todo
    pop();
    line(207);
    line(212);
    line(210);
    _clp_s_main(0);
    push(&NIL);
    neeq();
    cmp_2539:;
    if(!flag()) goto if_18_1;
        line(211);
        _clp_s_main(0);
        string(L",;");
        _clp_xsplit(2);
        assign(base+4);//mmd
        pop();
    if_18_1:
    if_18_0:;
    line(219);
    line(215);
    _clp_s_srcdir(0);
    push(&NIL);
    neeq();
    cmp_2601:;
    if(!flag()) goto if_19_1;
        line(216);
        _clp_s_srcdir(0);
        string(L",;");
        _clp_xsplit(2);
        assign(base+0);//dir
        pop();
    goto if_19_0;
    if_19_1:
    line(217);
        line(218);
        string(L".");
        array(1);
        assign(base+0);//dir
        pop();
    if_19_2:
    if_19_0:;
    line(226);
    line(222);
    _clp_s_incdir(0);
    push(&NIL);
    neeq();
    cmp_2678:;
    if(!flag()) goto if_20_1;
        line(223);
        _clp_s_incdir(0);
        string(L",;");
        _clp_xsplit(2);
        assign(base+1);//inc
        pop();
    goto if_20_0;
    if_20_1:
    line(224);
        line(225);
        array(0);
        assign(base+1);//inc
        pop();
    if_20_2:
    if_20_0:;
    line(229);
    {
    line(227);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_21_0:
    push_symbol(base+0);//dir
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_21_2;
        line(228);
        push_symbol(base+1);//inc
        push_symbol(base+0);//dir
        push_symbol(base+9);//n
        idxr();
        _clp_aadd(2);
        pop();
    lab_21_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_21_0;
    lab_21_2:;
    }
    line(254);
    {
    line(232);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_22_0:
    push_symbol(base+0);//dir
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_22_2;
        line(234);
        string(L"");
        push_symbol(base+0);//dir
        push_symbol(base+9);//n
        idxr();
        _clp_qqout(2);
        pop();
        line(236);
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
        line(253);
        {
        line(238);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+10);//i
        lab_23_0:
        push_symbol(base+6);//d1
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_23_2;
            line(240);
            push_symbol(base+6);//d1
            push_symbol(base+10);//i
            idxr();
            idxr0(1);
            assign(base+7);//f
            pop();
            line(248);
            line(242);
            push_symbol(base+7);//f
            _clp_fext(1);
            string(L".");
            add();
            _clp_s_primary(0);
            ss();
            if(!flag()) goto if_24_1;
                line(247);
                line(243);
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
                cmp_3008:;
                if(!flag()) goto if_25_1;
                goto if_25_0;
                if_25_1:
                line(245);
                    line(246);
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
                if_25_2:
                if_25_0:;
            if_24_1:
            if_24_0:;
            line(252);
            line(250);
            push_symbol(base+7);//f
            _clp_fext(1);
            string(L".");
            add();
            _clp_s_resource(0);
            ss();
            if(!flag()) goto if_26_1;
                line(251);
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
            if_26_1:
            if_26_0:;
        lab_23_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+10);//i
        add();
        assign(base+10);//i
        goto lab_23_0;
        lab_23_2:;
        }
    lab_22_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_22_0;
    lab_22_2:;
    }
    line(255);
    _clp_qout(0);
    pop();
    line(291);
    {
    line(260);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_27_0:
    push_symbol(base+2);//obj
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_27_2;
        line(262);
        push_symbol(base+2);//obj
        push_symbol(base+9);//n
        idxr();
        assign(base+7);//f
        pop();
        line(263);
        push_symbol(base+7);//f
        _clp_fname(1);
        assign(base+8);//o
        pop();
        line(264);
        push_symbol(base+7);//f
        _clp_memoread(1);
        assign(base+11);//txt
        pop();
        line(274);
        line(266);
        push(&ZERO);
        push_symbol(base+4);//mmd
        push_symbol_ref(base+8);//o
        block(_blk_build_0,1);
        _clp_ascan(2);
        neeq();
        cmp_3253:;
        if(!flag()) goto if_28_1;
        goto if_28_0;
        if_28_1:
        line(268);
        push_symbol(base+7);//f
        _clp_fext(1);
        string(L".prg");
        eqeq();
        cmp_3309:;
        if(!flag()){
        push(&FALSE);
        }else{
        string(L"function main(");
        push_symbol(base+11);//txt
        ss();
        }
        if(!flag()) goto if_28_2;
            line(271);
            line(269);
            _clp_s_main(0);
            push(&NIL);
            eqeq();
            cmp_3336:;
            if(!flag()) goto if_29_1;
                line(270);
                push_symbol(base+4);//mmd
                push_symbol(base+8);//o
                _clp_aadd(2);
                pop();
            if_29_1:
            if_29_0:;
        goto if_28_0;
        if_28_2:
        line(272);
            line(273);
            push_symbol(base+3);//lib
            push_symbol(base+8);//o
            _clp_aadd(2);
            pop();
        if_28_3:
        if_28_0:;
        line(276);
        push_symbol(base+8);//o
        string(L".obj");
        add();
        push_symbol(base+7);//f
        array(2);
        assign(base+12);//dep
        pop();
        line(288);
        {
        line(277);
        push(&ONE);
        int sg=sign();
        number(2);
        assign(base+10);//i
        lab_30_0:
        push_symbol(base+12);//dep
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_30_2;
            line(286);
            line(278);
            push_symbol(base+10);//i
            number(2);
            eqeq();
            cmp_3460:;
            if(!flag()) goto if_31_1;
            goto if_31_0;
            if_31_1:
            line(280);
            push_symbol(base+10);//i
            number(1024);
            gt();
            cmp_3476:;
            if(!flag()) goto if_31_2;
                line(281);
                string(L"recursive dependencies:");
                push_symbol(base+12);//dep
                _clp_qout(2);
                pop();
                line(282);
                _clp_qout(0);
                pop();
                line(283);
                _clp___quit(0);
                pop();
            goto if_31_0;
            if_31_2:
            line(284);
                line(285);
                push_symbol(base+12);//dep
                push_symbol(base+10);//i
                idxr();
                _clp_memoread(1);
                assign(base+11);//txt
                pop();
            if_31_3:
            if_31_0:;
            line(287);
            push_symbol(base+11);//txt
            push_symbol(base+12);//dep
            push_symbol(base+1);//inc
            push_symbol(base+5);//todo
            _clp_search_include(4);
            pop();
        lab_30_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+10);//i
        add();
        assign(base+10);//i
        goto lab_30_0;
        lab_30_2:;
        }
        line(290);
        push_symbol(base+5);//todo
        push_symbol(base+12);//dep
        _clp_aadd(2);
        pop();
    lab_27_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_27_0;
    lab_27_2:;
    }
    line(293);
    push_symbol(base+5);//todo
    _clp_normalize(1);
    pop();
    line(295);
    push_symbol(base+5);//todo
    push(&NIL);
    push(&NIL);
    block(_blk_build_1,0);
    _clp_asort(4);
    pop();
    line(309);
    line(301);
    _clp_s_debug(0);
    if(!flag()) goto if_32_1;
        line(302);
        string(L"main:");
        push_symbol(base+4);//mmd
        _clp_qout(2);
        pop();
        line(303);
        string(L"lib :");
        push_symbol(base+3);//lib
        _clp_qout(2);
        pop();
        line(304);
        _clp_qout(0);
        pop();
        line(307);
        {
        line(305);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_33_0:
        push_symbol(base+5);//todo
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_33_2;
            line(306);
            push_symbol(base+5);//todo
            push_symbol(base+9);//n
            idxr();
            _clp_qout(1);
            pop();
        lab_33_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_33_0;
        lab_33_2:;
        }
        line(308);
        _clp_qout(0);
        pop();
    if_32_1:
    if_32_0:;
    line(311);
    string(L"error");
    _clp_ferase(1);
    pop();
    line(316);
    {
    line(312);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_34_0:
    push_symbol(base+5);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_34_2;
        line(315);
        line(313);
        push_symbol(base+5);//todo
        push_symbol(base+9);//n
        idxr();
        idxr0(1);
        _clp_fext(1);
        string(L".obj");
        eqeq();
        cmp_3880:;
        topnot();
        if(!flag()) goto if_35_1;
            line(314);
            push_symbol(_st_pool_ptr());//global
            push_symbol_ref(base+5);//todo
            block(_blk_build_2,1);
            push_symbol(base+9);//n
            array(2);
            _o_method_addjob.eval(2);
            pop();
        if_35_1:
        if_35_0:;
    lab_34_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_34_0;
    lab_34_2:;
    }
    line(317);
    push_symbol(_st_pool_ptr());//global
    _o_method_wait.eval(1);
    pop();
    line(323);
    {
    line(319);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_36_0:
    push_symbol(base+5);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_36_2;
        line(322);
        line(320);
        push_symbol(base+5);//todo
        push_symbol(base+9);//n
        idxr();
        idxr0(1);
        _clp_fext(1);
        string(L".obj");
        eqeq();
        cmp_4007:;
        if(!flag()) goto if_37_1;
            line(321);
            push_symbol(_st_pool_ptr());//global
            push_symbol_ref(base+5);//todo
            block(_blk_build_3,1);
            push_symbol(base+9);//n
            array(2);
            _o_method_addjob.eval(2);
            pop();
        if_37_1:
        if_37_0:;
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
    line(324);
    push_symbol(_st_pool_ptr());//global
    _o_method_wait.eval(1);
    pop();
    line(342);
    line(328);
    _clp_s_libnam(0);
    push(&NIL);
    neeq();
    cmp_4100:;
    if(!flag()) goto if_38_1;
        line(329);
        _clp_s_libnam(0);
        push_symbol(base+3);//lib
        _clp_makelib(2);
        pop();
        line(333);
        line(331);
        _clp_s_shared(0);
        push(&TRUE);
        eqeq();
        cmp_4145:;
        if(!flag()){
        push(&FALSE);
        }else{
        _clp_dirsep(0);
        string(L"/");
        eqeq();
        cmp_4157:;
        }
        if(!flag()) goto if_39_1;
            line(332);
            _clp_s_libnam(0);
            push_symbol(base+3);//lib
            _clp_makeso(2);
            pop();
        if_39_1:
        if_39_0:;
        line(337);
        {
        line(335);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_40_0:
        push_symbol(base+4);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_40_2;
            line(336);
            push_symbol(_st_pool_ptr());//global
            block(_blk_build_4,0);
            push_symbol(base+4);//mmd
            push_symbol(base+9);//n
            idxr();
            _clp_s_libnam(0);
            array(3);
            _o_method_addjob.eval(2);
            pop();
        lab_40_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_40_0;
        lab_40_2:;
        }
    goto if_38_0;
    if_38_1:
    line(338);
        line(341);
        {
        line(339);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_41_0:
        push_symbol(base+4);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_41_2;
            line(340);
            push_symbol(_st_pool_ptr());//global
            block(_blk_build_5,0);
            push_symbol(base+4);//mmd
            push_symbol(base+9);//n
            idxr();
            push_symbol(base+3);//lib
            array(3);
            _o_method_addjob.eval(2);
            pop();
        lab_41_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_41_0;
        lab_41_2:;
        }
    if_38_2:
    if_38_0:;
    line(343);
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
    cmp_3272:;
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

