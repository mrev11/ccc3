//input: build.ppo (5.0.21)

#include <cccdef.h>

static void _blk_adddep_0(int argno);
static void _blk_build_0(int argno);
static void _blk_build_1(int argno);
static void _blk_byrules_0(int argno);
static void _blk_s_rules_from_build_bat_0(int argno);
extern void _clp___quit(int argno);
extern void _clp_aadd(int argno);
extern void _clp_aclone(int argno);
static void _clp_adddep(int argno);
extern void _clp_ains(int argno);
extern void _clp_alltrim(int argno);
extern void _clp_argv(int argno);
extern void _clp_ascan(int argno);
extern void _clp_asize(int argno);
extern void _clp_asort(int argno);
extern void _clp_at(int argno);
static void _clp_build(int argno);
static void _clp_byhand(int argno);
static void _clp_byrules(int argno);
extern void _clp_chr(int argno);
static void _clp_cmp(int argno);
extern void _clp_directory(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_dtos(int argno);
extern void _clp_empty(int argno);
extern void _clp_errorlevel(int argno);
static void _clp_extension_types(int argno);
extern void _clp_ferase(int argno);
extern void _clp_fext(int argno);
extern void _clp_file(int argno);
extern void _clp_fname(int argno);
extern void _clp_fnameext(int argno);
extern void _clp_fpath(int argno);
extern void _clp_fpath0(int argno);
static void _clp_ftime(int argno);
extern void _clp_getenv(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_lower(int argno);
extern void _clp_main(int argno);
static void _clp_makeexe(int argno);
static void _clp_makeexe1(int argno);
static void _clp_makelib(int argno);
static void _clp_makeobj(int argno);
static void _clp_makeso(int argno);
extern void _clp_memoread(int argno);
static void _clp_normalize(int argno);
static void _clp_params(int argno);
static void _clp_procpar(int argno);
extern void _clp_psort(int argno);
extern void _clp_putenv(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);
static void _clp_readpar(int argno);
extern void _clp_right(int argno);
static void _clp_root(int argno);
static void _clp_ruleidx(int argno);
static void _clp_rulesort(int argno);
extern void _clp_run(int argno);
static void _clp_run1(int argno);
static void _clp_s_rules_from_build_bat(int argno);
static void _clp_search_file(int argno);
static void _clp_search_include(int argno);
static void _clp_search_library(int argno);
extern void _clp_simplehashnew(int argno);
extern void _clp_split(int argno);
extern void _clp_strtran(int argno);
extern void _clp_substr(int argno);
static void _clp_usage(int argno);
static void _clp_xsplit(int argno);
static void _ini__omitted_hash();
static void _ini__resource_hash();
static void _ini__s_rules();

static VALUE* _st_s_main_ptr()
{
    static stvar _st_s_main;
    return _st_s_main.ptr;
}
static VALUE* _st_s_libnam_ptr()
{
    static stvar _st_s_libnam;
    return _st_s_libnam.ptr;
}
static VALUE* _st_s_shared_ptr()
{
    static stvar _st_s_shared;
    return _st_s_shared.ptr;
}
static VALUE* _st_s_srcdir_ptr()
{
    static stvar _st_s_srcdir;
    return _st_s_srcdir.ptr;
}
static VALUE* _st_s_incdir_ptr()
{
    static stvar _st_s_incdir;
    return _st_s_incdir.ptr;
}
static VALUE* _st_s_libdir_ptr()
{
    static stvar _st_s_libdir;
    return _st_s_libdir.ptr;
}
static VALUE* _st_s_libfil_ptr()
{
    static stvar _st_s_libfil;
    return _st_s_libfil.ptr;
}
MUTEX_CREATE(_mutex_s_quiet);
static VALUE* _st_s_quiet_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_s_quiet);
    static stvar _st_s_quiet(&FALSE);
    MUTEX_UNLOCK(_mutex_s_quiet);
    SIGNAL_UNLOCK();
    return _st_s_quiet.ptr;
}
MUTEX_CREATE(_mutex_s_version);
static VALUE* _st_s_version_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_s_version);
    static stvar _st_s_version(&FALSE);
    MUTEX_UNLOCK(_mutex_s_version);
    SIGNAL_UNLOCK();
    return _st_s_version.ptr;
}
MUTEX_CREATE(_mutex_s_debug);
static VALUE* _st_s_debug_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_s_debug);
    static stvar _st_s_debug(&FALSE);
    MUTEX_UNLOCK(_mutex_s_debug);
    SIGNAL_UNLOCK();
    return _st_s_debug.ptr;
}
MUTEX_CREATE(_mutex_s_dry);
static VALUE* _st_s_dry_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_s_dry);
    static stvar _st_s_dry(&FALSE);
    MUTEX_UNLOCK(_mutex_s_dry);
    SIGNAL_UNLOCK();
    return _st_s_dry.ptr;
}
static VALUE* _st_s_primary_ptr()
{
    static stvar _st_s_primary;
    return _st_s_primary.ptr;
}
static VALUE* _st_s_resource_ptr()
{
    static stvar _st_s_resource;
    return _st_s_resource.ptr;
}
MUTEX_CREATE(_mutex_s_libabs);
static VALUE* _st_s_libabs_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_s_libabs);
    static stvar _st_s_libabs(&TRUE);
    MUTEX_UNLOCK(_mutex_s_libabs);
    SIGNAL_UNLOCK();
    return _st_s_libabs.ptr;
}
MUTEX_CREATE(_mutex_s_rules);
static VALUE* _st_s_rules_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_s_rules);
    static stvar _st_s_rules(_ini__s_rules);
    MUTEX_UNLOCK(_mutex_s_rules);
    SIGNAL_UNLOCK();
    return _st_s_rules.ptr;
}
MUTEX_CREATE(_mutex_resource_hash);
static VALUE* _st_resource_hash_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_resource_hash);
    static stvar _st_resource_hash(_ini__resource_hash);
    MUTEX_UNLOCK(_mutex_resource_hash);
    SIGNAL_UNLOCK();
    return _st_resource_hash.ptr;
}
MUTEX_CREATE(_mutex_omitted_hash);
static VALUE* _st_omitted_hash_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_omitted_hash);
    static stvar _st_omitted_hash(_ini__omitted_hash);
    MUTEX_UNLOCK(_mutex_omitted_hash);
    SIGNAL_UNLOCK();
    return _st_omitted_hash.ptr;
}

static void _ini__s_rules()
{
    string(L".msk");
    string(L".dlg");
    array(2);
    string(L".msk");
    string(L".pnl");
    array(2);
    string(L".mnt");
    string(L".gpi");
    array(2);
    string(L".cls");
    string(L".och");
    array(2);
    string(L".msk");
    string(L".say");
    array(2);
    string(L".htm");
    string(L".ctm");
    array(2);
    string(L".msk");
    string(L".wro");
    array(2);
    string(L".pge");
    string(L".out");
    array(2);
    string(L".pge");
    string(L".wro");
    array(2);
    string(L".tdc");
    string(L".ch");
    array(2);
    string(L".asm");
    string(L".obj");
    array(2);
    string(L".c");
    string(L".obj");
    array(2);
    string(L".cpp");
    string(L".obj");
    array(2);
    string(L".tds");
    string(L".obj");
    array(2);
    string(L".prg");
    string(L".obj");
    array(2);
    string(L".y");
    string(L".obj");
    array(2);
    string(L".lem");
    string(L".obj");
    array(2);
    string(L".lex");
    string(L".obj");
    array(2);
    string(L".tdc");
    string(L".obj");
    array(2);
    string(L".obj");
    string(L".lib");
    array(2);
    string(L".obj");
    string(L".exe");
    array(2);
    array(21);
}

static void _ini__resource_hash()
{
    _clp_simplehashnew(0);
}

static void _ini__omitted_hash()
{
    _clp_simplehashnew(0);
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
    line(74);
    _clp_argv(0);
    _clp_aclone(1);
    assign(base+0);//opt
    pop();
    line(82);
    line(79);
    push_symbol(_st_s_quiet_ptr());//global
    topnot();
    if(!flag()) goto if_1_1;
        line(80);
        string(nls_text(L"CCC Program Builder "));
        string(L"1.3.9");
        add();
        string(L" Copyright (C) ComFirm Bt.");
        add();
        _clp_qqout(1);
        pop();
        line(81);
        _clp_qout(0);
        pop();
    if_1_1:
    if_1_0:;
    line(169);
    {
    line(85);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_2_0:
    push_symbol(base+0);//opt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_2_2;
        line(86);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        _clp_procpar(1);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        assign2(idxxl());
        pop();
        line(168);
        line(88);
        string(L"-l");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_1;
            line(89);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_libnam_ptr());//global
            pop();
            line(90);
            push(&FALSE);
            assign(_st_s_shared_ptr());//global
            pop();
        goto if_3_0;
        if_3_1:
        line(93);
        string(L"-s");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_2;
            line(94);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_libnam_ptr());//global
            pop();
            line(95);
            push(&TRUE);
            assign(_st_s_shared_ptr());//global
            pop();
        goto if_3_0;
        if_3_2:
        line(98);
        string(L"-d");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_3;
            line(103);
            line(99);
            push_symbol(_st_s_srcdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_4_1;
                line(100);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_srcdir_ptr());//global
                pop();
            goto if_4_0;
            if_4_1:
            line(101);
                line(102);
                push_symbol(_st_s_srcdir_ptr());//global
                string(L",");
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                add();
                add();
                assign(_st_s_srcdir_ptr());//global
                pop();
            if_4_2:
            if_4_0:;
        goto if_3_0;
        if_3_3:
        line(106);
        string(L"-i");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_4;
            line(111);
            line(107);
            push_symbol(_st_s_incdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_5_1;
                line(108);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_incdir_ptr());//global
                pop();
            goto if_5_0;
            if_5_1:
            line(109);
                line(110);
                push_symbol(_st_s_incdir_ptr());//global
                string(L",");
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                add();
                add();
                assign(_st_s_incdir_ptr());//global
                pop();
            if_5_2:
            if_5_0:;
        goto if_3_0;
        if_3_4:
        line(114);
        string(L"-p");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_5;
            line(119);
            line(115);
            push_symbol(_st_s_libdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_6_1;
                line(116);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_libdir_ptr());//global
                pop();
            goto if_6_0;
            if_6_1:
            line(117);
                line(118);
                push_symbol(_st_s_libdir_ptr());//global
                string(L",");
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                add();
                add();
                assign(_st_s_libdir_ptr());//global
                pop();
            if_6_2:
            if_6_0:;
        goto if_3_0;
        if_3_5:
        line(122);
        string(L"-b");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_6;
            line(127);
            line(123);
            push_symbol(_st_s_libfil_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_7_1;
                line(124);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_libfil_ptr());//global
                pop();
            goto if_7_0;
            if_7_1:
            line(125);
                line(126);
                push_symbol(_st_s_libfil_ptr());//global
                string(L",");
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                add();
                add();
                assign(_st_s_libfil_ptr());//global
                pop();
            if_7_2:
            if_7_0:;
        goto if_3_0;
        if_3_6:
        line(130);
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
        if(!flag()) goto if_3_7;
            line(135);
            line(131);
            push_symbol(_st_s_main_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_8_1;
                line(132);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_main_ptr());//global
                pop();
            goto if_8_0;
            if_8_1:
            line(133);
                line(134);
                push_symbol(_st_s_main_ptr());//global
                string(L",");
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                add();
                add();
                assign(_st_s_main_ptr());//global
                pop();
            if_8_2:
            if_8_0:;
        goto if_3_0;
        if_3_7:
        line(137);
        string(L"-o");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_8;
            line(138);
            push(&TRUE);
            push_symbol(_st_omitted_hash_ptr());//global
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
        goto if_3_0;
        if_3_8:
        line(140);
        string(L"-h");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_9;
            line(141);
            _clp_usage(0);
            pop();
            line(142);
            _clp___quit(0);
            pop();
        goto if_3_0;
        if_3_9:
        line(144);
        string(L"-q");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_10;
            line(145);
            push(&TRUE);
            assign(_st_s_quiet_ptr());//global
            pop();
        goto if_3_0;
        if_3_10:
        line(147);
        string(L"-v");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_11;
            line(148);
            push(&TRUE);
            assign(_st_s_version_ptr());//global
            pop();
        goto if_3_0;
        if_3_11:
        line(150);
        string(L"--debug");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        if(!flag()) goto if_3_12;
            line(151);
            push(&TRUE);
            assign(_st_s_debug_ptr());//global
            pop();
        goto if_3_0;
        if_3_12:
        line(153);
        string(L"--dry");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        if(!flag()) goto if_3_13;
            line(154);
            push(&TRUE);
            assign(_st_s_debug_ptr());//global
            pop();
            line(155);
            push(&TRUE);
            assign(_st_s_dry_ptr());//global
            pop();
        goto if_3_0;
        if_3_13:
        line(157);
        string(L"@");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        push(&ONE);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_14;
            line(158);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(2);
            _clp_substr(2);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            _clp_readpar(3);
            pop();
        goto if_3_0;
        if_3_14:
        line(160);
        string(L"=");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        ss();
        if(!flag()) goto if_3_15;
            line(161);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_putenv(1);
            pop();
        goto if_3_0;
        if_3_15:
        line(163);
            line(164);
            string(nls_text(L"Invalid switch: "));
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_qout(2);
            pop();
            line(165);
            _clp_usage(0);
            pop();
            line(166);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(167);
            _clp___quit(0);
            pop();
        if_3_16:
        if_3_0:;
    lab_2_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+1);//n
    add();
    assign(base+1);//n
    goto lab_2_0;
    lab_2_2:;
    }
    line(174);
    line(172);
    string(L"on");
    string(L"BUILD_DBG");
    _clp_getenv(1);
    _clp_lower(1);
    ss();
    if(!flag()) goto if_9_1;
        line(173);
        push(&TRUE);
        assign(_st_s_debug_ptr());//global
        pop();
    if_9_1:
    if_9_0:;
    line(177);
    line(175);
    string(L"debug");
    string(L"BUILD_DBG");
    _clp_getenv(1);
    _clp_lower(1);
    ss();
    if(!flag()) goto if_10_1;
        line(176);
        push(&TRUE);
        assign(_st_s_debug_ptr());//global
        pop();
    if_10_1:
    if_10_0:;
    line(181);
    line(178);
    string(L"dry");
    string(L"BUILD_DBG");
    _clp_getenv(1);
    _clp_lower(1);
    ss();
    if(!flag()) goto if_11_1;
        line(179);
        push(&TRUE);
        assign(_st_s_debug_ptr());//global
        pop();
        line(180);
        push(&TRUE);
        assign(_st_s_dry_ptr());//global
        pop();
    if_11_1:
    if_11_0:;
    line(185);
    line(183);
    push_symbol(_st_s_version_ptr());//global
    if(!flag()) goto if_12_1;
        line(184);
        _clp___quit(0);
        pop();
    if_12_1:
    if_12_0:;
    line(187);
    _clp_s_rules_from_build_bat(0);
    pop();
    line(188);
    _clp_extension_types(0);
    pop();
    line(190);
    _clp_root(0);
    pop();
    line(191);
    _clp_params(0);
    pop();
    line(192);
    _clp_build(0);
    pop();
    line(194);
    _clp_qout(0);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_s_rules_from_build_bat(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+3)PUSHNIL();
argno=0;
push_call("s_rules_from_build_bat",base);
//
    line(203);
    line(205);
    push_symbol(_st_s_rules_ptr());//global
    push(&ZERO);
    _clp_asize(2);
    pop();
    line(206);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"*.bat");
    add();
    _clp_directory(1);
    assign(base+0);//d
    pop();
    line(214);
    {
    line(207);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_13_0:
    push_symbol(base+0);//d
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_13_2;
        line(208);
        push_symbol(base+0);//d
        push_symbol(base+1);//n
        idxr();
        idxr0(1);
        string(L".bat");
        string(L"");
        _clp_strtran(3);
        string(L"2");
        _clp_split(2);
        assign(base+2);//rule
        pop();
        line(213);
        line(209);
        push_symbol(base+2);//rule
        _clp_len(1);
        number(2);
        eqeq();
        if(!flag()) goto if_14_1;
            line(210);
            string(L".");
            push_symbol(base+2);//rule
            idxr0(1);
            add();
            push_symbol(base+2);//rule
            assign2(idxxl0(1));
            pop();
            line(211);
            string(L".");
            push_symbol(base+2);//rule
            idxr0(2);
            add();
            push_symbol(base+2);//rule
            assign2(idxxl0(2));
            pop();
            line(212);
            push_symbol(_st_s_rules_ptr());//global
            push_symbol(base+2);//rule
            _clp_aadd(2);
            pop();
        if_14_1:
        if_14_0:;
    lab_13_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+1);//n
    add();
    assign(base+1);//n
    goto lab_13_0;
    lab_13_2:;
    }
    line(216);
    push_symbol(_st_s_rules_ptr());//global
    push(&NIL);
    push(&NIL);
    block(_blk_s_rules_from_build_bat_0,0);
    _clp_asort(4);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_s_rules_from_build_bat_0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_s_rules_from_build_bat_0",base);
//
    push_blkarg(base+1);//x
    push_blkarg(base+2);//y
    _clp_rulesort(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
static void _clp_rulesort(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("rulesort",base);
//
    line(223);
    line(224);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_15_1;
        string(L".exe");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_15_1:
    if_15_0:;
    line(225);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_16_1;
        string(L".so");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_16_1:
    if_16_0:;
    line(226);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_17_1;
        string(L".lib");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_17_1:
    if_17_0:;
    line(227);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_18_1;
        string(L".obj");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_18_1:
    if_18_0:;
    line(228);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_19_1;
        push_symbol(base+0);//x
        idxr0(1);
        push_symbol(base+1);//y
        idxr0(1);
        lt();
        assign(base+2);//result
        pop();
    if_19_1:
    if_19_0:;
    line(229);
    push_symbol(base+2);//result
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_cmp(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("cmp",base);
//
    line(236);
    line(232);
    push_symbol(base+1);//x
    idxr0(2);
    push_symbol(base+0);//ext
    eqeq();
    if(!flag()) goto if_20_1;
        line(233);
        push_symbol(base+2);//y
        idxr0(2);
        push_symbol(base+0);//ext
        eqeq();
        if(flag()){
        push_symbol(base+1);//x
        idxr0(1);
        push_symbol(base+2);//y
        idxr0(1);
        lt();
        }else{
        push(&FALSE);
        }
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_20_0;
    if_20_1:
    line(234);
    push_symbol(base+2);//y
    idxr0(2);
    push_symbol(base+0);//ext
    eqeq();
    if(!flag()) goto if_20_2;
        line(235);
        push_symbol(base+1);//x
        idxr0(2);
        push_symbol(base+0);//ext
        eqeq();
        if(flag()){
        push_symbol(base+1);//x
        idxr0(1);
        push_symbol(base+2);//y
        idxr0(1);
        lt();
        }else{
        push(&TRUE);
        }
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_20_2:
    if_20_0:;
    line(237);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_extension_types(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+3)PUSHNIL();
argno=0;
push_call("extension_types",base);
//
    line(241);
    line(243);
    string(L"");
    assign(_st_s_primary_ptr());//global
    pop();
    line(244);
    string(L"");
    assign(_st_s_resource_ptr());//global
    pop();
    line(258);
    {
    line(246);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_21_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_21_2;
        line(247);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+2);//n
        idxr();
        idxr0(1);
        assign(base+0);//r1
        pop();
        line(248);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+2);//n
        idxr();
        idxr0(2);
        assign(base+1);//r2
        pop();
        line(254);
        line(252);
        push_symbol(base+1);//r2
        string(L".obj");
        eqeq();
        if(!flag()) goto if_22_1;
            line(253);
            push_symbol(_st_s_primary_ptr());//global
            push_symbol(base+0);//r1
            add();
            assign(_st_s_primary_ptr());//global
            pop();
        if_22_1:
        if_22_0:;
        line(257);
        line(255);
        push_symbol(base+1);//r2
        string(L".");
        add();
        string(L".obj.lib.exe.");
        ss();
        topnot();
        if(!flag()) goto if_23_1;
            line(256);
            push_symbol(_st_s_resource_ptr());//global
            push_symbol(base+0);//r1
            add();
            assign(_st_s_resource_ptr());//global
            pop();
        if_23_1:
        if_23_0:;
    lab_21_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_21_0;
    lab_21_2:;
    }
    line(259);
    push_symbol(_st_s_primary_ptr());//global
    string(L".");
    add();
    assign(_st_s_primary_ptr());//global
    pop();
    line(260);
    push_symbol(_st_s_resource_ptr());//global
    string(L".");
    add();
    assign(_st_s_resource_ptr());//global
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_readpar(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+7)PUSHNIL();
argno=3;
push_call("readpar",base);
//
    line(267);
    push_symbol(base+0);//parfil
    _clp_memoread(1);
    assign(base+3);//par
    pop();
    line(274);
    line(269);
    push_symbol(base+3);//par
    _clp_empty(1);
    if(!flag()) goto if_24_1;
        line(273);
        string(L"BUILD_BAT");
        _clp_getenv(1);
        _clp_dirsep(0);
        add();
        push_symbol(base+0);//parfil
        add();
        _clp_memoread(1);
        assign(base+3);//par
        pop();
    if_24_1:
    if_24_0:;
    line(282);
    line(276);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_25_1;
        line(281);
        line(277);
        push_symbol(base+3);//par
        _clp_empty(1);
        if(!flag()) goto if_26_1;
            line(278);
            string(L"Build parfile empty:");
            push_symbol(base+0);//parfil
            _clp_qqout(2);
            pop();
            _clp_qout(0);
            pop();
        goto if_26_0;
        if_26_1:
        line(279);
            line(280);
            string(L"Build parfile:");
            push_symbol(base+0);//parfil
            _clp_qqout(2);
            pop();
            _clp_qout(0);
            pop();
        if_26_2:
        if_26_0:;
    if_25_1:
    if_25_0:;
    line(284);
    push_symbol(base+3);//par
    number(13);
    _clp_chr(1);
    string(L"");
    _clp_strtran(3);
    assign(base+3);//par
    pop();
    line(285);
    push_symbol(base+3);//par
    number(10);
    _clp_chr(1);
    _clp_split(2);
    assign(base+3);//par
    pop();
    line(301);
    {
    line(287);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_27_0:
    push_symbol(base+3);//par
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_27_2;
        line(288);
        push_symbol(base+3);//par
        push_symbol(base+4);//n
        idxr();
        assign(base+5);//p
        pop();
        line(291);
        line(289);
        string(L"#");
        push_symbol(base+5);//p
        ss();
        if(!flag()) goto if_28_1;
            line(290);
            push_symbol(base+5);//p
            string(L"#");
            push_symbol(base+5);//p
            _clp_at(2);
            addnum(-1);
            _clp_left(2);
            assign(base+5);//p
            pop();
        if_28_1:
        if_28_0:;
        line(293);
        push_symbol(base+5);//p
        string(L" ");
        _clp_split(2);
        assign(base+5);//p
        pop();
        line(300);
        {
        line(294);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+6);//i
        lab_29_0:
        push_symbol(base+5);//p
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_29_2;
            line(299);
            line(295);
            push_symbol(base+5);//p
            push_symbol(base+6);//i
            idxr();
            _clp_empty(1);
            topnot();
            if(!flag()) goto if_30_1;
                line(296);
                push_symbol(base+1);//opt
                push(&NIL);
                _clp_aadd(2);
                pop();
                line(297);
                push_symbol(base+1);//opt
                push_symbol(base+2);//optx
                push(&ONE);
                add();
                assign(base+2);//optx
                _clp_ains(2);
                pop();
                line(298);
                push_symbol(base+5);//p
                push_symbol(base+6);//i
                idxr();
                push_symbol(base+1);//opt
                push_symbol(base+2);//optx
                assign2(idxxl());
                pop();
            if_30_1:
            if_30_0:;
        lab_29_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+6);//i
        add();
        assign(base+6);//i
        goto lab_29_0;
        lab_29_2:;
        }
    lab_27_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_27_0;
    lab_27_2:;
    }
    line(302);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_procpar(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("procpar",base);
//
    line(306);
    line(315);
    lab_31_1:
    line(308);
    push(&ZERO);
    string(L"$$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_31_2;
        line(309);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(310);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(3);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(311);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(312);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        string(L"/$(BUILD_OBJ)/");
        add();
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        add();
        add();
        assign(base+2);//p
        pop();
        line(313);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(314);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_31_1;
    lab_31_2:;
    line(324);
    lab_32_1:
    line(317);
    push(&ZERO);
    string(L"$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_32_2;
        line(318);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(319);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(2);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(320);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(321);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        _clp_getenv(1);
        add();
        assign(base+2);//p
        pop();
        line(322);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(323);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_32_1;
    lab_32_2:;
    line(326);
    push_symbol(base+0);//par
    string(L"\\");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(327);
    push_symbol(base+0);//par
    string(L"/");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(329);
    push_symbol(base+0);//par
    push(&ONE);
    _clp_left(2);
    string(L"=");
    eqeq();
    if(flag()){
    push_symbol(base+0);//par
    _clp_lower(1);
    }else{
    push_symbol(base+0);//par
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
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
    line(334);
    string(nls_text(L"BUILD -xExeNam|-lLibNam -dSrcDir -iIncDir -pLibDir -bLibFil -mMain"));
    _clp_qout(1);
    pop();
    line(335);
    _clp_qout(0);
    pop();
    line(336);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_root(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+3)PUSHNIL();
argno=0;
push_call("root",base);
//
    line(342);
    line(379);
    line(344);
    string(L"BUILD_SRC");
    _clp_getenv(1);
    assign(base+0);//srcroot
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_33_1;
        line(348);
        line(346);
        push_symbol(base+0);//srcroot
        push(&ONE);
        _clp_right(2);
        string(L"/\\");
        ss();
        topnot();
        if(!flag()) goto if_34_1;
            line(347);
            push_symbol(base+0);//srcroot
            _clp_dirsep(0);
            add();
            assign(base+0);//srcroot
            pop();
        if_34_1:
        if_34_0:;
        line(352);
        line(350);
        push_symbol(_st_s_srcdir_ptr());//global
        push(&NIL);
        eqeq();
        if(!flag()) goto if_35_1;
            line(351);
            string(L".");
            assign(_st_s_srcdir_ptr());//global
            pop();
        if_35_1:
        if_35_0:;
        line(354);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+1);//d
        pop();
        line(356);
        string(L"");
        assign(_st_s_srcdir_ptr());//global
        pop();
        line(363);
        {
        line(357);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+2);//n
        lab_36_0:
        push_symbol(base+1);//d
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_36_2;
            line(362);
            line(358);
            push_symbol(base+1);//d
            push_symbol(base+2);//n
            idxr();
            push(&ONE);
            _clp_left(2);
            string(L"/\\");
            ss();
            if(!flag()) goto if_37_1;
                line(359);
                push_symbol(_st_s_srcdir_ptr());//global
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                string(L";");
                add();
                add();
                assign(_st_s_srcdir_ptr());//global
                pop();
            goto if_37_0;
            if_37_1:
            line(360);
                line(361);
                push_symbol(_st_s_srcdir_ptr());//global
                push_symbol(base+0);//srcroot
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                add();
                string(L";");
                add();
                add();
                assign(_st_s_srcdir_ptr());//global
                pop();
            if_37_2:
            if_37_0:;
        lab_36_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+2);//n
        add();
        assign(base+2);//n
        goto lab_36_0;
        lab_36_2:;
        }
        line(378);
        line(366);
        push_symbol(_st_s_incdir_ptr());//global
        push(&NIL);
        neeq();
        if(!flag()) goto if_38_1;
            line(368);
            push_symbol(_st_s_incdir_ptr());//global
            string(L",;");
            _clp_xsplit(2);
            assign(base+1);//d
            pop();
            line(370);
            string(L"");
            assign(_st_s_incdir_ptr());//global
            pop();
            line(377);
            {
            line(371);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+2);//n
            lab_39_0:
            push_symbol(base+1);//d
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_39_2;
                line(376);
                line(372);
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                push(&ONE);
                _clp_left(2);
                string(L"/\\");
                ss();
                if(!flag()) goto if_40_1;
                    line(373);
                    push_symbol(_st_s_incdir_ptr());//global
                    push_symbol(base+1);//d
                    push_symbol(base+2);//n
                    idxr();
                    string(L";");
                    add();
                    add();
                    assign(_st_s_incdir_ptr());//global
                    pop();
                goto if_40_0;
                if_40_1:
                line(374);
                    line(375);
                    push_symbol(_st_s_incdir_ptr());//global
                    push_symbol(base+0);//srcroot
                    push_symbol(base+1);//d
                    push_symbol(base+2);//n
                    idxr();
                    add();
                    string(L";");
                    add();
                    add();
                    assign(_st_s_incdir_ptr());//global
                    pop();
                if_40_2:
                if_40_0:;
            lab_39_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+2);//n
            add();
            assign(base+2);//n
            goto lab_39_0;
            lab_39_2:;
            }
        if_38_1:
        if_38_0:;
    if_33_1:
    if_33_0:;
    line(381);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_params(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+4)PUSHNIL();
argno=0;
push_call("params",base);
//
    line(387);
    line(400);
    string(L"");
    assign(base+0);//txt
    pop();
    line(401);
    push_symbol(base+0);//txt
    push_symbol(_st_s_srcdir_ptr());//global
    push(&NIL);
    eqeq();
    if(flag()){
    string(L".");
    }else{
    push_symbol(_st_s_srcdir_ptr());//global
    }
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(402);
    push_symbol(base+0);//txt
    push_symbol(_st_s_incdir_ptr());//global
    push(&NIL);
    eqeq();
    if(flag()){
    string(L"");
    }else{
    push_symbol(_st_s_incdir_ptr());//global
    }
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(403);
    push_symbol(base+0);//txt
    string(L"BUILD_INC");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(404);
    push_symbol(base+0);//txt
    string(L"include");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(405);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(406);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(408);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(410);
    string(L"BUILD_INC=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(416);
    string(L"");
    assign(base+0);//txt
    pop();
    line(417);
    push_symbol(base+0);//txt
    push_symbol(_st_s_libdir_ptr());//global
    push(&NIL);
    eqeq();
    if(flag()){
    string(L"");
    }else{
    push_symbol(_st_s_libdir_ptr());//global
    }
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(418);
    push_symbol(base+0);//txt
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(419);
    push_symbol(base+0);//txt
    string(L"lib");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(420);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(421);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(423);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(425);
    string(L"BUILD_LPT=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(431);
    string(L"");
    assign(base+0);//txt
    pop();
    line(432);
    push_symbol(base+0);//txt
    push_symbol(_st_s_libfil_ptr());//global
    push(&NIL);
    eqeq();
    if(flag()){
    string(L"");
    }else{
    push_symbol(_st_s_libfil_ptr());//global
    }
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(433);
    push_symbol(base+0);//txt
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(434);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(435);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(436);
    string(L"BUILD_LIB=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(439);
    line(437);
    push_symbol(_st_s_libabs_ptr());//global
    if(!flag()) goto if_41_1;
        line(438);
        string(L"BUILD_LIB=");
        _clp_search_library(0);
        add();
        _clp_putenv(1);
        pop();
    if_41_1:
    if_41_0:;
    line(442);
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
    line(448);
    array(0);
    assign(base+0);//dir
    pop();
    line(449);
    array(0);
    assign(base+1);//obj
    pop();
    line(450);
    array(0);
    assign(base+2);//lib
    pop();
    line(451);
    array(0);
    assign(base+3);//mmd
    pop();
    line(452);
    array(0);
    assign(base+4);//todo
    pop();
    line(454);
    line(459);
    line(457);
    push_symbol(_st_s_main_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_42_1;
        line(458);
        push_symbol(_st_s_main_ptr());//global
        _clp_lower(1);
        string(L",;");
        _clp_xsplit(2);
        assign(base+3);//mmd
        pop();
    if_42_1:
    if_42_0:;
    line(466);
    line(462);
    push_symbol(_st_s_srcdir_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_43_1;
        line(463);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+0);//dir
        pop();
    goto if_43_0;
    if_43_1:
    line(464);
        line(465);
        string(L".");
        array(1);
        assign(base+0);//dir
        pop();
    if_43_2:
    if_43_0:;
    line(490);
    {
    line(468);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_44_0:
    push_symbol(base+0);//dir
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_44_2;
        line(470);
        string(L"");
        push_symbol(base+0);//dir
        push_symbol(base+8);//n
        idxr();
        _clp_qqout(2);
        pop();
        line(472);
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
        line(489);
        {
        line(474);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//i
        lab_45_0:
        push_symbol(base+5);//d1
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_45_2;
            line(476);
            push_symbol(base+5);//d1
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            _clp_lower(1);
            assign(base+6);//f
            pop();
            line(484);
            line(478);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            push_symbol(_st_s_primary_ptr());//global
            ss();
            if(!flag()) goto if_46_1;
                line(483);
                line(479);
                push_symbol(_st_omitted_hash_ptr());//global
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
                if(!flag()) goto if_47_1;
                goto if_47_0;
                if_47_1:
                line(481);
                    line(482);
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
                if_47_2:
                if_47_0:;
            if_46_1:
            if_46_0:;
            line(488);
            line(486);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            push_symbol(_st_s_resource_ptr());//global
            ss();
            if(!flag()) goto if_48_1;
                line(487);
                push_symbol(base+0);//dir
                push_symbol(base+8);//n
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+6);//f
                add();
                push_symbol(_st_resource_hash_ptr());//global
                push_symbol(base+6);//f
                assign2(idxxl());
                pop();
            if_48_1:
            if_48_0:;
        lab_45_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//i
        add();
        assign(base+9);//i
        goto lab_45_0;
        lab_45_2:;
        }
    lab_44_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_44_0;
    lab_44_2:;
    }
    line(491);
    _clp_qout(0);
    pop();
    line(527);
    {
    line(496);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_49_0:
    push_symbol(base+1);//obj
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_49_2;
        line(498);
        push_symbol(base+1);//obj
        push_symbol(base+8);//n
        idxr();
        assign(base+6);//f
        pop();
        line(499);
        push_symbol(base+6);//f
        _clp_fname(1);
        assign(base+7);//o
        pop();
        line(500);
        push_symbol(base+6);//f
        _clp_memoread(1);
        assign(base+10);//txt
        pop();
        line(510);
        line(502);
        push(&ZERO);
        push_symbol(base+3);//mmd
        push_symbol_ref(base+7);//o
        block(_blk_build_0,1);
        _clp_ascan(2);
        neeq();
        if(!flag()) goto if_50_1;
        goto if_50_0;
        if_50_1:
        line(504);
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
        if(!flag()) goto if_50_2;
            line(507);
            line(505);
            push_symbol(_st_s_main_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_51_1;
                line(506);
                push_symbol(base+3);//mmd
                push_symbol(base+7);//o
                _clp_aadd(2);
                pop();
            if_51_1:
            if_51_0:;
        goto if_50_0;
        if_50_2:
        line(508);
            line(509);
            push_symbol(base+2);//lib
            push_symbol(base+7);//o
            _clp_aadd(2);
            pop();
        if_50_3:
        if_50_0:;
        line(512);
        push_symbol(base+7);//o
        string(L".obj");
        add();
        push_symbol(base+6);//f
        array(2);
        assign(base+11);//dep
        pop();
        line(524);
        {
        line(513);
        push(&ONE);
        int sg=sign();
        number(2);
        assign(base+9);//i
        lab_52_0:
        push_symbol(base+11);//dep
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_52_2;
            line(522);
            line(514);
            push_symbol(base+9);//i
            number(2);
            eqeq();
            if(!flag()) goto if_53_1;
            goto if_53_0;
            if_53_1:
            line(516);
            push_symbol(base+9);//i
            number(1024);
            gt();
            if(!flag()) goto if_53_2;
                line(517);
                string(L"recursive dependencies:");
                push_symbol(base+11);//dep
                _clp_qout(2);
                pop();
                line(518);
                _clp_qout(0);
                pop();
                line(519);
                _clp___quit(0);
                pop();
            goto if_53_0;
            if_53_2:
            line(520);
                line(521);
                push_symbol(base+11);//dep
                push_symbol(base+9);//i
                idxr();
                _clp_memoread(1);
                assign(base+10);//txt
                pop();
            if_53_3:
            if_53_0:;
            line(523);
            push_symbol(base+10);//txt
            push_symbol(base+11);//dep
            push_symbol(base+0);//dir
            push_symbol(base+4);//todo
            _clp_search_include(4);
            pop();
        lab_52_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//i
        add();
        assign(base+9);//i
        goto lab_52_0;
        lab_52_2:;
        }
        line(526);
        push_symbol(base+4);//todo
        push_symbol(base+11);//dep
        _clp_aadd(2);
        pop();
    lab_49_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_49_0;
    lab_49_2:;
    }
    line(529);
    push_symbol(base+4);//todo
    _clp_normalize(1);
    pop();
    line(531);
    push_symbol(base+4);//todo
    push(&NIL);
    push(&NIL);
    block(_blk_build_1,0);
    _clp_asort(4);
    pop();
    line(543);
    line(535);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_54_1;
        line(536);
        string(L"main:");
        push_symbol(base+3);//mmd
        _clp_qout(2);
        pop();
        line(537);
        string(L"lib :");
        push_symbol(base+2);//lib
        _clp_qout(2);
        pop();
        line(538);
        _clp_qout(0);
        pop();
        line(541);
        {
        line(539);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_55_0:
        push_symbol(base+4);//todo
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_55_2;
            line(540);
            push_symbol(base+4);//todo
            push_symbol(base+8);//n
            idxr();
            _clp_qout(1);
            pop();
        lab_55_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+8);//n
        add();
        assign(base+8);//n
        goto lab_55_0;
        lab_55_2:;
        }
        line(542);
        _clp_qout(0);
        pop();
    if_54_1:
    if_54_0:;
    line(545);
    string(L"error");
    _clp_ferase(1);
    pop();
    line(549);
    {
    line(547);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_56_0:
    push_symbol(base+4);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_56_2;
        line(548);
        push_symbol(base+4);//todo
        push_symbol(base+8);//n
        idxr();
        _clp_makeobj(1);
        pop();
    lab_56_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_56_0;
    lab_56_2:;
    }
    line(568);
    line(553);
    push_symbol(_st_s_libnam_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_57_1;
        line(554);
        push_symbol(_st_s_libnam_ptr());//global
        push_symbol(base+2);//lib
        _clp_makelib(2);
        pop();
        line(558);
        line(556);
        push_symbol(_st_s_shared_ptr());//global
        push(&TRUE);
        eqeq();
        if(!flag()) goto if_58_1;
            line(557);
            push_symbol(_st_s_libnam_ptr());//global
            push_symbol(base+2);//lib
            _clp_makeso(2);
            pop();
        if_58_1:
        if_58_0:;
        line(562);
        {
        line(560);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_59_0:
        push_symbol(base+3);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_59_2;
            line(561);
            push_symbol(base+3);//mmd
            push_symbol(base+8);//n
            idxr();
            push_symbol(_st_s_libnam_ptr());//global
            _clp_makeexe1(2);
            pop();
        lab_59_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+8);//n
        add();
        assign(base+8);//n
        goto lab_59_0;
        lab_59_2:;
        }
    goto if_57_0;
    if_57_1:
    line(564);
        line(567);
        {
        line(565);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_60_0:
        push_symbol(base+3);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_60_2;
            line(566);
            push_symbol(base+3);//mmd
            push_symbol(base+8);//n
            idxr();
            push_symbol(base+2);//lib
            _clp_makeexe(2);
            pop();
        lab_60_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+8);//n
        add();
        assign(base+8);//n
        goto lab_60_0;
        lab_60_2:;
        }
    if_57_2:
    if_57_0:;
    line(570);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
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
    push_blkarg(base+1);//m
    push_blkenv(env+0);//o
    _clp_lower(1);
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
    push_blkarg(base+1);//x
    push_blkarg(base+2);//y
    _clp_psort(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
static void _clp_makeso(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+10)PUSHNIL();
argno=2;
push_call("makeso",base);
//
    line(577);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"lib");
    add();
    push_symbol(base+0);//libnam
    add();
    string(L".so");
    add();
    assign(base+2);//target
    pop();
    line(578);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(579);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2so.bat");
    add();
    assign(base+7);//torun
    pop();
    line(580);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(587);
    line(582);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_61_1;
        line(583);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(584);
        _clp_qout(0);
        pop();
        line(585);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(586);
        _clp___quit(0);
        pop();
    if_61_1:
    if_61_0:;
    line(589);
    push_symbol(base+7);//torun
    string(L" lib");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(591);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(594);
    line(592);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_62_1;
        line(593);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_62_1:
    if_62_0:;
    line(598);
    line(596);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_63_1;
        line(597);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_63_1:
    if_63_0:;
    line(624);
    {
    line(600);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_64_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_64_2;
        line(602);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(603);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+4);//depend
        add();
        add();
        assign(base+7);//torun
        pop();
        line(604);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(605);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(619);
        line(607);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_65_1;
            line(615);
            line(608);
            push_symbol(_st_s_dry_ptr());//global
            if(!flag()) goto if_66_1;
                line(609);
                string(L"");
                assign(base+5);//tdepend
                pop();
            goto if_66_0;
            if_66_1:
            line(610);
                line(611);
                push_symbol(base+4);//depend
                string(nls_text(L"does not exist"));
                _clp_qout(2);
                pop();
                line(612);
                _clp_qout(0);
                pop();
                line(613);
                push(&ONE);
                _clp_errorlevel(1);
                pop();
                line(614);
                _clp___quit(0);
                pop();
            if_66_2:
            if_66_0:;
        goto if_65_0;
        if_65_1:
        line(617);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_65_2;
            line(618);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_65_2:
        if_65_0:;
        line(623);
        line(621);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_67_1;
            line(622);
            string(L"  ");
            push_symbol(base+4);//depend
            string(L"[");
            push_symbol(base+5);//tdepend
            add();
            string(L"]");
            add();
            push_symbol(base+3);//ttarget
            push_symbol(base+5);//tdepend
            lt();
            if(flag()){
            string(L"UPDATE");
            }else{
            string(L"");
            }
            _clp_qout(4);
            pop();
        if_67_1:
        if_67_0:;
    lab_64_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_64_0;
    lab_64_2:;
    }
    line(628);
    line(626);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_68_1;
        line(627);
        _clp_qout(0);
        pop();
    if_68_1:
    if_68_0:;
    line(632);
    line(630);
    push_symbol(base+6);//update
    if(!flag()) goto if_69_1;
        line(631);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_69_1:
    if_69_0:;
    line(634);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_makelib(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+11)PUSHNIL();
argno=2;
push_call("makelib",base);
//
    line(640);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    push_symbol(base+0);//libnam
    add();
    string(L".lib");
    add();
    assign(base+2);//target
    pop();
    line(641);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(642);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2lib.bat");
    add();
    assign(base+7);//torun
    pop();
    line(643);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+8);//objdir
    pop();
    line(644);
    line(651);
    line(646);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_70_1;
        line(647);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(648);
        _clp_qout(0);
        pop();
        line(649);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(650);
        _clp___quit(0);
        pop();
    if_70_1:
    if_70_0:;
    line(653);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(655);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(658);
    line(656);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_71_1;
        line(657);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_71_1:
    if_71_0:;
    line(662);
    line(660);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_72_1;
        line(661);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_72_1:
    if_72_0:;
    line(687);
    {
    line(664);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_73_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_73_2;
        line(666);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(667);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(668);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(682);
        line(670);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_74_1;
            line(678);
            line(671);
            push_symbol(_st_s_dry_ptr());//global
            if(!flag()) goto if_75_1;
                line(672);
                string(L"");
                assign(base+5);//tdepend
                pop();
            goto if_75_0;
            if_75_1:
            line(673);
                line(674);
                push_symbol(base+4);//depend
                string(nls_text(L"does not exist"));
                _clp_qout(2);
                pop();
                line(675);
                _clp_qout(0);
                pop();
                line(676);
                push(&ONE);
                _clp_errorlevel(1);
                pop();
                line(677);
                _clp___quit(0);
                pop();
            if_75_2:
            if_75_0:;
        goto if_74_0;
        if_74_1:
        line(680);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_74_2;
            line(681);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_74_2:
        if_74_0:;
        line(686);
        line(684);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_76_1;
            line(685);
            string(L"  ");
            push_symbol(base+4);//depend
            string(L"[");
            push_symbol(base+5);//tdepend
            add();
            string(L"]");
            add();
            push_symbol(base+3);//ttarget
            push_symbol(base+5);//tdepend
            lt();
            if(flag()){
            string(L"UPDATE");
            }else{
            string(L"");
            }
            _clp_qout(4);
            pop();
        if_76_1:
        if_76_0:;
    lab_73_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_73_0;
    lab_73_2:;
    }
    line(691);
    line(689);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_77_1;
        line(690);
        _clp_qout(0);
        pop();
    if_77_1:
    if_77_0:;
    line(719);
    line(693);
    push_symbol(base+6);//update
    if(!flag()) goto if_78_1;
        line(698);
        {
        line(696);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_79_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_79_2;
            line(697);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
            pop();
        lab_79_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_79_0;
        lab_79_2:;
        }
        line(718);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_78_1:
    if_78_0:;
    line(721);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_makeexe(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+12)PUSHNIL();
argno=2;
push_call("makeexe",base);
//
    line(727);
    string(L"BUILD_EXE");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    push_symbol(base+0);//exenam
    add();
    string(L".exe");
    add();
    assign(base+2);//target
    pop();
    line(728);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(729);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2exe.bat");
    add();
    assign(base+7);//torun
    pop();
    line(730);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+8);//objdir
    pop();
    line(731);
    line(738);
    line(733);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_80_1;
        line(734);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(735);
        _clp_qout(0);
        pop();
        line(736);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(737);
        _clp___quit(0);
        pop();
    if_80_1:
    if_80_0:;
    line(740);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(743);
    line(741);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_81_1;
        line(742);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_81_1:
    if_81_0:;
    line(747);
    line(745);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_82_1;
        line(746);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_82_1:
    if_82_0:;
    line(776);
    {
    line(749);
    push(&ONE);
    int sg=sign();
    push(&ZERO);
    assign(base+9);//n
    lab_83_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_83_2;
        line(755);
        line(751);
        push_symbol(base+9);//n
        push(&ZERO);
        eqeq();
        if(!flag()) goto if_84_1;
            line(752);
            push_symbol(base+0);//exenam
            assign(base+4);//depend
            pop();
        goto if_84_0;
        if_84_1:
        line(753);
            line(754);
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
        if_84_2:
        if_84_0:;
        line(757);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(758);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(771);
        line(760);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_85_1;
            line(768);
            line(761);
            push_symbol(_st_s_dry_ptr());//global
            if(!flag()) goto if_86_1;
                line(762);
                string(L"");
                assign(base+5);//tdepend
                pop();
            goto if_86_0;
            if_86_1:
            line(763);
                line(764);
                push_symbol(base+4);//depend
                string(nls_text(L"does not exist"));
                _clp_qout(2);
                pop();
                line(765);
                _clp_qout(0);
                pop();
                line(766);
                push(&ONE);
                _clp_errorlevel(1);
                pop();
                line(767);
                _clp___quit(0);
                pop();
            if_86_2:
            if_86_0:;
        goto if_85_0;
        if_85_1:
        line(769);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_85_2;
            line(770);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_85_2:
        if_85_0:;
        line(775);
        line(773);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_87_1;
            line(774);
            string(L"  ");
            push_symbol(base+4);//depend
            string(L"[");
            push_symbol(base+5);//tdepend
            add();
            string(L"]");
            add();
            push_symbol(base+3);//ttarget
            push_symbol(base+5);//tdepend
            lt();
            if(flag()){
            string(L"UPDATE");
            }else{
            string(L"");
            }
            _clp_qout(4);
            pop();
        if_87_1:
        if_87_0:;
    lab_83_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_83_0;
    lab_83_2:;
    }
    line(780);
    line(778);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_88_1;
        line(779);
        _clp_qout(0);
        pop();
    if_88_1:
    if_88_0:;
    line(814);
    line(782);
    push_symbol(base+6);//update
    if(!flag()) goto if_89_1;
        line(783);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+0);//exenam
        add();
        add();
        assign(base+7);//torun
        pop();
        line(788);
        {
        line(786);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_90_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_90_2;
            line(787);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
            pop();
        lab_90_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_90_0;
        lab_90_2:;
        }
        line(813);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_89_1:
    if_89_0:;
    line(816);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_makeexe1(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+10)PUSHNIL();
argno=2;
push_call("makeexe1",base);
//
    line(822);
    string(L"BUILD_EXE");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    push_symbol(base+0);//mmod
    add();
    string(L".exe");
    add();
    assign(base+2);//target
    pop();
    line(823);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(824);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"lib2exe.bat");
    add();
    assign(base+7);//torun
    pop();
    line(825);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(832);
    line(827);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_91_1;
        line(828);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(829);
        _clp_qout(0);
        pop();
        line(830);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(831);
        _clp___quit(0);
        pop();
    if_91_1:
    if_91_0:;
    line(834);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(837);
    line(835);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_92_1;
        line(836);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_92_1:
    if_92_0:;
    line(841);
    line(839);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_93_1;
        line(840);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_93_1:
    if_93_0:;
    line(844);
    push_symbol(base+0);//mmod
    assign(base+4);//depend
    pop();
    line(845);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(846);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".obj");
    add();
    assign(base+4);//depend
    pop();
    line(847);
    push_symbol(base+4);//depend
    _clp_ftime(1);
    assign(base+5);//tdepend
    pop();
    line(860);
    line(849);
    push_symbol(base+5);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_94_1;
        line(857);
        line(850);
        push_symbol(_st_s_dry_ptr());//global
        if(!flag()) goto if_95_1;
            line(851);
            string(L"");
            assign(base+5);//tdepend
            pop();
        goto if_95_0;
        if_95_1:
        line(852);
            line(853);
            push_symbol(base+4);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(854);
            _clp_qout(0);
            pop();
            line(855);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(856);
            _clp___quit(0);
            pop();
        if_95_2:
        if_95_0:;
    goto if_94_0;
    if_94_1:
    line(858);
    push_symbol(base+3);//ttarget
    push_symbol(base+5);//tdepend
    lt();
    if(!flag()) goto if_94_2;
        line(859);
        push(&TRUE);
        assign(base+6);//update
        pop();
    if_94_2:
    if_94_0:;
    line(864);
    line(862);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_96_1;
        line(863);
        string(L"  ");
        push_symbol(base+4);//depend
        string(L"[");
        push_symbol(base+5);//tdepend
        add();
        string(L"]");
        add();
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(flag()){
        string(L"UPDATE");
        }else{
        string(L"");
        }
        _clp_qout(4);
        pop();
    if_96_1:
    if_96_0:;
    line(867);
    push_symbol(base+1);//libnam
    assign(base+4);//depend
    pop();
    line(868);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(869);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".lib");
    add();
    assign(base+4);//depend
    pop();
    line(870);
    push_symbol(base+4);//depend
    _clp_ftime(1);
    assign(base+5);//tdepend
    pop();
    line(883);
    line(872);
    push_symbol(base+5);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_97_1;
        line(880);
        line(873);
        push_symbol(_st_s_dry_ptr());//global
        if(!flag()) goto if_98_1;
            line(874);
            string(L"");
            assign(base+5);//tdepend
            pop();
        goto if_98_0;
        if_98_1:
        line(875);
            line(876);
            push_symbol(base+4);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(877);
            _clp_qout(0);
            pop();
            line(878);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(879);
            _clp___quit(0);
            pop();
        if_98_2:
        if_98_0:;
    goto if_97_0;
    if_97_1:
    line(881);
    push_symbol(base+3);//ttarget
    push_symbol(base+5);//tdepend
    lt();
    if(!flag()) goto if_97_2;
        line(882);
        push(&TRUE);
        assign(base+6);//update
        pop();
    if_97_2:
    if_97_0:;
    line(887);
    line(885);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_99_1;
        line(886);
        string(L"  ");
        push_symbol(base+4);//depend
        string(L"[");
        push_symbol(base+5);//tdepend
        add();
        string(L"]");
        add();
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(flag()){
        string(L"UPDATE");
        }else{
        string(L"");
        }
        _clp_qout(4);
        pop();
    if_99_1:
    if_99_0:;
    line(892);
    line(890);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_100_1;
        line(891);
        _clp_qout(0);
        pop();
    if_100_1:
    if_100_0:;
    line(896);
    line(894);
    push_symbol(base+6);//update
    if(!flag()) goto if_101_1;
        line(895);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_101_1:
    if_101_0:;
    line(898);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_makeobj(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+11)PUSHNIL();
argno=1;
push_call("makeobj",base);
//
    line(904);
    push_symbol(base+0);//deplist
    idxr0(1);
    assign(base+1);//target
    pop();
    line(905);
    push_symbol(base+0);//deplist
    idxr0(2);
    assign(base+2);//depend
    pop();
    line(906);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+3);//objdir
    pop();
    line(907);
    line(908);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(909);
    line(913);
    line(911);
    push_symbol(base+1);//target
    _clp_fext(1);
    string(L".obj");
    eqeq();
    if(!flag()) goto if_102_1;
        line(912);
        push_symbol(base+3);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+1);//target
        _clp_fname(1);
        add();
        push_symbol(base+1);//target
        _clp_fext(1);
        add();
        assign(base+1);//target
        pop();
    if_102_1:
    if_102_0:;
    line(915);
    push_symbol(base+1);//target
    _clp_ftime(1);
    assign(base+4);//ttarget
    pop();
    line(918);
    line(916);
    push_symbol(base+4);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_103_1;
        line(917);
        string(L"");
        assign(base+4);//ttarget
        pop();
    if_103_1:
    if_103_0:;
    line(922);
    line(920);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_104_1;
        line(921);
        push_symbol(base+1);//target
        string(L"[");
        push_symbol(base+4);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_104_1:
    if_104_0:;
    line(945);
    {
    line(924);
    push(&ONE);
    int sg=sign();
    number(2);
    assign(base+8);//n
    lab_105_0:
    push_symbol(base+0);//deplist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_105_2;
        line(925);
        push_symbol(base+0);//deplist
        push_symbol(base+8);//n
        idxr();
        assign(base+2);//depend
        pop();
        line(926);
        push_symbol(base+2);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(940);
        line(928);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_106_1;
            line(936);
            line(929);
            push_symbol(_st_s_dry_ptr());//global
            if(!flag()) goto if_107_1;
                line(930);
                string(L"");
                assign(base+5);//tdepend
                pop();
            goto if_107_0;
            if_107_1:
            line(931);
                line(932);
                push_symbol(base+0);//deplist
                push_symbol(base+8);//n
                idxr();
                string(nls_text(L"does not exist"));
                _clp_qout(2);
                pop();
                line(933);
                _clp_qout(0);
                pop();
                line(934);
                push(&ONE);
                _clp_errorlevel(1);
                pop();
                line(935);
                _clp___quit(0);
                pop();
            if_107_2:
            if_107_0:;
        goto if_106_0;
        if_106_1:
        line(938);
        push_symbol(base+4);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_106_2;
            line(939);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_106_2:
        if_106_0:;
        line(944);
        line(942);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_108_1;
            line(943);
            string(L"  ");
            push_symbol(base+2);//depend
            string(L"[");
            push_symbol(base+5);//tdepend
            add();
            string(L"]");
            add();
            push_symbol(base+4);//ttarget
            push_symbol(base+5);//tdepend
            lt();
            if(flag()){
            string(L"UPDATE");
            }else{
            string(L"");
            }
            _clp_qout(4);
            pop();
        if_108_1:
        if_108_0:;
    lab_105_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_105_0;
    lab_105_2:;
    }
    line(949);
    line(947);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_109_1;
        line(948);
        _clp_qout(0);
        pop();
    if_109_1:
    if_109_0:;
    line(968);
    line(951);
    push_symbol(base+6);//update
    if(!flag()) goto if_110_1;
        line(953);
        string(L"BUILD_BAT");
        _clp_getenv(1);
        _clp_dirsep(0);
        add();
        assign(base+7);//torun
        pop();
        line(954);
        push_symbol(base+7);//torun
        push_symbol(base+0);//deplist
        idxr0(2);
        _clp_fext(1);
        string(L"2");
        add();
        push_symbol(base+0);//deplist
        idxr0(1);
        _clp_fext(1);
        add();
        string(L".");
        string(L"");
        _clp_strtran(3);
        add();
        assign(base+7);//torun
        pop();
        line(955);
        push_symbol(base+7);//torun
        string(L".bat");
        add();
        assign(base+7);//torun
        pop();
        line(962);
        line(957);
        push_symbol(base+7);//torun
        _clp_file(1);
        topnot();
        if(!flag()) goto if_111_1;
            line(958);
            string(L"[");
            push_symbol(base+7);//torun
            add();
            string(L"]");
            add();
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(959);
            _clp_qout(0);
            pop();
            line(960);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(961);
            _clp___quit(0);
            pop();
        if_111_1:
        if_111_0:;
        line(964);
        push_symbol(base+0);//deplist
        idxr0(1);
        _clp_fname(1);
        assign(base+9);//p1
        pop();
        line(965);
        push_symbol(base+0);//deplist
        idxr0(2);
        _clp_fpath0(1);
        assign(base+10);//p2
        pop();
        push_symbol(base+10);//p2
        _clp_empty(1);
        if(flag()){
        string(L".");
        }else{
        push_symbol(base+10);//p2
        }
        assign(base+10);//p2
        pop();
        line(967);
        push_symbol(base+7);//torun
        string(L" ");
        add();
        push_symbol(base+9);//p1
        add();
        string(L" ");
        add();
        push_symbol(base+10);//p2
        add();
        _clp_run1(1);
        pop();
    if_110_1:
    if_110_0:;
    line(970);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_run1(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("run1",base);
//
    line(990);
    line(977);
    push_symbol(_st_s_dry_ptr());//global
    topnot();
    if(!flag()) goto if_112_1;
        line(979);
        push_symbol(base+0);//cmd
        _clp_run(1);
        pop();
        line(989);
        line(981);
        string(L"error");
        _clp_file(1);
        if(!flag()) goto if_113_1;
            line(983);
            string(L"cat error");
            _clp_run(1);
            pop();
            line(987);
            _clp_qout(0);
            pop();
            line(988);
            _clp___quit(0);
            pop();
        if_113_1:
        if_113_0:;
    if_112_1:
    if_112_0:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_ftime(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("ftime",base);
//
    line(995);
    push_symbol(base+0);//fspec
    string(L"H");
    _clp_directory(2);
    assign(base+1);//d
    pop();
    line(998);
    line(996);
    push_symbol(base+1);//d
    _clp_len(1);
    push(&ONE);
    eqeq();
    if(!flag()) goto if_114_1;
        line(997);
        push_symbol(base+1);//d
        idxr0(1);
        idxr0(3);
        _clp_dtos(1);
        string(L"-");
        add();
        push_symbol(base+1);//d
        idxr0(1);
        idxr0(4);
        add();
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_114_1:
    if_114_0:;
    line(999);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_search_include(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+13)PUSHNIL();
argno=4;
push_call("search_include",base);
//
    line(1005);
    number(10);
    _clp_chr(1);
    assign(base+4);//nl
    pop();
    line(1006);
    string(L"#include");
    assign(base+5);//include
    pop();
    line(1007);
    push_symbol(base+5);//include
    _clp_len(1);
    assign(base+6);//lenincl
    pop();
    line(1008);
    push(&ZERO);
    assign(base+8);//n2
    pop();
    line(1045);
    lab_115_1:
    line(1010);
    push_symbol(base+5);//include
    push_symbol(base+0);//txt
    push_symbol(base+8);//n2
    addnum(1);
    _clp_at(3);
    assign(base+7);//n1
    push(&ZERO);
    gt();
    if(!flag()) goto lab_115_2;
        line(1014);
        line(1012);
        push(&ZERO);
        push_symbol(base+4);//nl
        push_symbol(base+0);//txt
        push_symbol(base+7);//n1
        push_symbol(base+6);//lenincl
        add();
        _clp_at(3);
        assign(base+8);//n2
        eqeq();
        if(!flag()) goto if_116_1;
            line(1013);
            push_symbol(base+0);//txt
            _clp_len(1);
            addnum(1);
            assign(base+8);//n2
            pop();
        if_116_1:
        if_116_0:;
        line(1016);
        push_symbol(base+0);//txt
        push_symbol(base+7);//n1
        push_symbol(base+6);//lenincl
        add();
        push_symbol(base+8);//n2
        push_symbol(base+7);//n1
        sub();
        push_symbol(base+6);//lenincl
        sub();
        _clp_substr(3);
        assign(base+9);//line
        pop();
        line(1017);
        push_symbol(base+9);//line
        number(9);
        _clp_chr(1);
        string(L"");
        _clp_strtran(3);
        assign(base+9);//line
        pop();
        line(1018);
        push_symbol(base+9);//line
        _clp_alltrim(1);
        assign(base+9);//line
        pop();
        line(1026);
        line(1020);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"\"");
        eqeq();
        if(!flag()) goto if_117_1;
            line(1021);
            string(L"\"");
            assign(base+10);//delim
            pop();
        goto if_117_0;
        if_117_1:
        line(1022);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"<");
        eqeq();
        if(!flag()) goto if_117_2;
            line(1023);
            string(L">");
            assign(base+10);//delim
            pop();
        goto if_117_0;
        if_117_2:
        line(1024);
            line(1025);
            goto lab_115_1;//loop
        if_117_3:
        if_117_0:;
        line(1030);
        line(1028);
        push(&ZERO);
        push_symbol(base+10);//delim
        push_symbol(base+9);//line
        number(2);
        _clp_at(3);
        assign(base+11);//dpos
        eqeq();
        if(!flag()) goto if_118_1;
            line(1029);
            goto lab_115_1;//loop
        if_118_1:
        if_118_0:;
        line(1032);
        push_symbol(base+9);//line
        number(2);
        push_symbol(base+11);//dpos
        addnum(-2);
        _clp_substr(3);
        assign(base+12);//f
        pop();
        line(1033);
        push_symbol(base+12);//f
        string(L"/");
        _clp_dirsep(0);
        _clp_strtran(3);
        assign(base+12);//f
        pop();
        line(1034);
        push_symbol(base+12);//f
        string(L"\\");
        _clp_dirsep(0);
        _clp_strtran(3);
        assign(base+12);//f
        pop();
        line(1044);
        line(1036);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byrules(4);
        if(!flag()) goto if_119_1;
        goto if_119_0;
        if_119_1:
        line(1039);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byhand(4);
        if(!flag()) goto if_119_2;
        goto if_119_0;
        if_119_2:
        line(1042);
        if_119_3:
        if_119_0:;
    goto lab_115_1;
    lab_115_2:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_search_library(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+13)PUSHNIL();
argno=0;
push_call("search_library",base);
//
    line(1054);
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+0);//dirlist
    pop();
    line(1055);
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+1);//liblist
    pop();
    line(1056);
    string(L"BUILD_SHR");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+2);//sharing
    pop();
    line(1058);
    string(L"");
    assign(base+5);//txt
    pop();
    line(1059);
    line(1135);
    {
    line(1062);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_120_0:
    push_symbol(base+1);//liblist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_120_2;
        line(1066);
        line(1064);
        push_symbol(base+1);//liblist
        push_symbol(base+3);//n
        idxr();
        assign(base+6);//f0
        _clp_empty(1);
        if(!flag()) goto if_121_1;
            line(1065);
            goto lab_120_1;//loop
        if_121_1:
        if_121_0:;
        line(1078);
        line(1068);
        string(L".lib");
        push_symbol(base+6);//f0
        ss();
        if(flag()){
        push(&TRUE);
        }else{
        string(L".a");
        push_symbol(base+6);//f0
        ss();
        }
        if(flag()){
        push(&TRUE);
        }else{
        string(L".so");
        push_symbol(base+6);//f0
        ss();
        }
        if(!flag()) goto if_122_1;
            line(1069);
            push_symbol(base+6);//f0
            assign(base+7);//f1
            pop();
            line(1070);
            push_symbol(base+6);//f0
            assign(base+8);//f2
            pop();
            line(1071);
            push_symbol(base+6);//f0
            assign(base+9);//f3
            pop();
        goto if_122_0;
        if_122_1:
        line(1072);
            line(1073);
            push_symbol(base+6);//f0
            string(L".lib");
            add();
            assign(base+7);//f1
            pop();
            line(1076);
            push_symbol(base+6);//f0
            _clp_fpath(1);
            string(L"lib");
            add();
            push_symbol(base+6);//f0
            _clp_fnameext(1);
            add();
            string(L".a");
            add();
            assign(base+8);//f2
            pop();
            line(1077);
            push_symbol(base+6);//f0
            _clp_fpath(1);
            string(L"lib");
            add();
            push_symbol(base+6);//f0
            _clp_fnameext(1);
            add();
            string(L".so");
            add();
            assign(base+9);//f3
            pop();
        if_122_2:
        if_122_0:;
        line(1130);
        {
        line(1080);
        push(&ONE);
        int sg=sign();
        push(&ZERO);
        assign(base+4);//i
        lab_123_0:
        push_symbol(base+0);//dirlist
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_123_2;
            line(1094);
            line(1082);
            push_symbol(base+4);//i
            push(&ZERO);
            lteq();
            if(!flag()) goto if_124_1;
                line(1083);
                push_symbol(base+7);//f1
                assign(base+10);//pf1
                pop();
                line(1084);
                push_symbol(base+8);//f2
                assign(base+11);//pf2
                pop();
                line(1085);
                push_symbol(base+9);//f3
                assign(base+12);//pf3
                pop();
            goto if_124_0;
            if_124_1:
            line(1086);
                line(1089);
                line(1087);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_empty(1);
                if(!flag()) goto if_125_1;
                    line(1088);
                    goto lab_123_1;//loop
                if_125_1:
                if_125_0:;
                line(1091);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+7);//f1
                add();
                assign(base+10);//pf1
                pop();
                line(1092);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+8);//f2
                add();
                assign(base+11);//pf2
                pop();
                line(1093);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+9);//f3
                add();
                assign(base+12);//pf3
                pop();
            if_124_2:
            if_124_0:;
            line(1129);
            line(1100);
            string(L"static");
            push_symbol(base+2);//sharing
            ss();
            if(!flag()) goto if_126_1;
                line(1113);
                line(1104);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_127_1;
                    line(1105);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1106);
                    goto lab_123_2;//exit
                goto if_127_0;
                if_127_1:
                line(1107);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_127_2;
                    line(1108);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1109);
                    goto lab_123_2;//exit
                goto if_127_0;
                if_127_2:
                line(1110);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_127_3;
                    line(1111);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1112);
                    goto lab_123_2;//exit
                if_127_3:
                if_127_0:;
            goto if_126_0;
            if_126_1:
            line(1115);
                line(1128);
                line(1119);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_128_1;
                    line(1120);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1121);
                    goto lab_123_2;//exit
                goto if_128_0;
                if_128_1:
                line(1122);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_128_2;
                    line(1123);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1124);
                    goto lab_123_2;//exit
                goto if_128_0;
                if_128_2:
                line(1125);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_128_3;
                    line(1126);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1127);
                    goto lab_123_2;//exit
                if_128_3:
                if_128_0:;
            if_126_2:
            if_126_0:;
        lab_123_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+4);//i
        add();
        assign(base+4);//i
        goto lab_123_0;
        lab_123_2:;
        }
        line(1134);
        line(1132);
        push_symbol(base+4);//i
        push_symbol(base+0);//dirlist
        _clp_len(1);
        gt();
        if(!flag()) goto if_129_1;
            line(1133);
            push_symbol(base+5);//txt
            push_symbol(base+6);//f0
            string(L" ");
            add();
            add();
            assign(base+5);//txt
            pop();
        if_129_1:
        if_129_0:;
    lab_120_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_120_0;
    lab_120_2:;
    }
    line(1137);
    push_symbol(base+5);//txt
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_search_file(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("search_file",base);
//
    line(1142);
    line(1149);
    {
    line(1144);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_130_0:
    push_symbol(base+0);//dirlist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_130_2;
        line(1145);
        push_symbol(base+0);//dirlist
        push_symbol(base+2);//n
        idxr();
        _clp_dirsep(0);
        add();
        push_symbol(base+1);//fnamext
        add();
        assign(base+3);//pathname
        pop();
        line(1148);
        line(1146);
        push_symbol(base+3);//pathname
        _clp_file(1);
        if(!flag()) goto if_131_1;
            line(1147);
            push_symbol(base+3);//pathname
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_131_1:
        if_131_0:;
    lab_130_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_130_0;
    lab_130_2:;
    }
    line(1150);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_byrules(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+10)PUSHNIL();
argno=4;
push_call("byrules",base);
//
    line(1161);
    push_symbol(base+0);//fil
    _clp_fname(1);
    assign(base+4);//f
    pop();
    line(1162);
    push_symbol(base+0);//fil
    _clp_fext(1);
    assign(base+5);//e
    pop();
    line(1163);
    line(1164);
    line(1165);
    line(1171);
    line(1167);
    push_symbol(base+5);//e
    string(L".ch");
    eqeq();
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+4);//f
    idxr0(1);
    string(L"_");
    eqeq();
    topnot();
    }
    if(!flag()) goto if_132_1;
        line(1170);
        push(&FALSE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_132_1:
    if_132_0:;
    line(1191);
    {
    line(1173);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//i
    lab_133_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_133_2;
        line(1190);
        line(1175);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+9);//i
        idxr();
        idxr0(2);
        push_symbol(base+5);//e
        eqeq();
        if(!flag()) goto if_134_1;
            line(1177);
            push_symbol(_st_s_rules_ptr());//global
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            assign(base+8);//e0
            pop();
            line(1189);
            line(1182);
            push(&NIL);
            push_symbol(_st_resource_hash_ptr());//global
            push_symbol(base+4);//f
            push_symbol(base+8);//e0
            add();
            idxr();
            assign(base+7);//r
            neeq();
            if(!flag()) goto if_135_1;
                line(1183);
                push_symbol(base+7);//r
                _clp_fpath(1);
                assign(base+6);//p
                pop();
                line(1184);
                push_symbol(base+1);//dep
                push_symbol(base+6);//p
                push_symbol(base+4);//f
                add();
                push_symbol(base+5);//e
                add();
                _clp_adddep(2);
                pop();
                line(1187);
                line(1185);
                push(&ZERO);
                push_symbol(base+3);//todo
                push_symbol_ref(base+6);//p
                push_symbol_ref(base+4);//f
                push_symbol_ref(base+5);//e
                block(_blk_byrules_0,3);
                _clp_ascan(2);
                eqeq();
                if(!flag()) goto if_136_1;
                    line(1186);
                    push_symbol(base+3);//todo
                    push_symbol(base+6);//p
                    push_symbol(base+4);//f
                    add();
                    push_symbol(base+5);//e
                    add();
                    push_symbol(base+6);//p
                    push_symbol(base+4);//f
                    add();
                    push_symbol(base+8);//e0
                    add();
                    array(2);
                    _clp_aadd(2);
                    pop();
                if_136_1:
                if_136_0:;
                line(1188);
                push(&TRUE);
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            if_135_1:
            if_135_0:;
        if_134_1:
        if_134_0:;
    lab_133_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//i
    add();
    assign(base+9);//i
    goto lab_133_0;
    lab_133_2:;
    }
    line(1192);
    push(&FALSE);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_byrules_0(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_byrules_0",base);
//
    push_blkarg(base+1);//x
    idxr0(1);
    push_blkenv(env+0);//p
    push_blkenv(env+1);//f
    add();
    push_blkenv(env+2);//e
    add();
    eqeq();
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
static void _clp_byhand(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+5)PUSHNIL();
argno=4;
push_call("byhand",base);
//
    line(1203);
    push_symbol(base+2);//dir
    push_symbol(base+0);//f
    _clp_search_file(2);
    assign(base+4);//pn
    pop();
    line(1208);
    line(1205);
    push_symbol(base+4);//pn
    push(&NIL);
    neeq();
    if(!flag()) goto if_137_1;
        line(1206);
        push_symbol(base+1);//dep
        push_symbol(base+4);//pn
        _clp_adddep(2);
        pop();
        line(1207);
        push(&TRUE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_137_1:
    if_137_0:;
    line(1209);
    push(&FALSE);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_adddep(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("adddep",base);
//
    line(1216);
    line(1214);
    push(&ZERO);
    push_symbol(base+0);//dep
    push_symbol_ref(base+1);//x
    block(_blk_adddep_0,1);
    _clp_ascan(2);
    eqeq();
    if(!flag()) goto if_138_1;
        line(1215);
        push_symbol(base+0);//dep
        push_symbol(base+1);//x
        _clp_aadd(2);
        pop();
    if_138_1:
    if_138_0:;
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_adddep_0(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_adddep_0",base);
//
    push_blkarg(base+1);//d
    push_blkenv(env+0);//x
    eqeq();
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
void _clp_psort(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("psort",base);
//
    line(1221);
    push_symbol(base+0);//x
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+0);//x
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+2);//ix
    pop();
    line(1222);
    push_symbol(base+1);//y
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+1);//y
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+3);//iy
    pop();
    line(1223);
    push_symbol(base+2);//ix
    push_symbol(base+3);//iy
    eqeq();
    if(flag()){
    push_symbol(base+0);//x
    idxr0(1);
    push_symbol(base+1);//y
    idxr0(1);
    lt();
    }else{
    push_symbol(base+2);//ix
    push_symbol(base+3);//iy
    lt();
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_ruleidx(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("ruleidx",base);
//
    line(1228);
    line(1233);
    {
    line(1229);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_139_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_139_2;
        line(1232);
        line(1230);
        push_symbol(base+0);//e1
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+2);//n
        idxr();
        idxr0(1);
        eqeq();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+1);//e2
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+2);//n
        idxr();
        idxr0(2);
        eqeq();
        }
        if(!flag()) goto if_140_1;
            line(1231);
            push_symbol(base+2);//n
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_140_1:
        if_140_0:;
    lab_139_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_139_0;
    lab_139_2:;
    }
    line(1234);
    push(&ZERO);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_xsplit(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("xsplit",base);
//
    line(1239);
    line(1249);
    {
    line(1240);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_141_0:
    push_symbol(base+1);//sep
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_141_2;
        line(1242);
        push_symbol(base+1);//sep
        push_symbol(base+2);//n
        push(&ONE);
        _clp_substr(3);
        assign(base+3);//s
        pop();
        line(1248);
        line(1244);
        push(&ZERO);
        push_symbol(base+3);//s
        push_symbol(base+0);//txt
        _clp_at(2);
        lt();
        if(!flag()) goto if_142_1;
            line(1245);
            goto lab_141_2;//exit
        goto if_142_0;
        if_142_1:
        line(1246);
            line(1247);
            push(&NIL);
            assign(base+3);//s
            pop();
        if_142_2:
        if_142_0:;
    lab_141_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_141_0;
    lab_141_2:;
    }
    line(1250);
    push_symbol(base+0);//txt
    push_symbol(base+3);//s
    _clp_split(2);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_normalize(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+4)PUSHNIL();
argno=1;
push_call("normalize",base);
//
    line(1259);
    line(1270);
    {
    line(1261);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_143_0:
    push_symbol(base+0);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_143_2;
        line(1269);
        {
        line(1262);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+1);//i
        lab_144_0:
        push_symbol(base+0);//todo
        push_symbol(base+2);//n
        idxr();
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_144_2;
            line(1263);
            push_symbol(base+0);//todo
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+1);//i
            idxr();
            assign(base+3);//x
            pop();
            line(1264);
            push_symbol(base+3);//x
            _clp_dirsep(0);
            string(L".");
            add();
            _clp_dirsep(0);
            add();
            _clp_dirsep(0);
            _clp_strtran(3);
            assign(base+3);//x
            pop();
            line(1267);
            line(1265);
            push_symbol(base+3);//x
            number(2);
            _clp_left(2);
            string(L".");
            _clp_dirsep(0);
            add();
            eqeq();
            if(!flag()) goto if_145_1;
                line(1266);
                push_symbol(base+3);//x
                number(3);
                _clp_substr(2);
                assign(base+3);//x
                pop();
            if_145_1:
            if_145_0:;
            line(1268);
            push_symbol(base+3);//x
            push_symbol(base+0);//todo
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+1);//i
            assign2(idxxl());
            pop();
        lab_144_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+1);//i
        add();
        assign(base+1);//i
        goto lab_144_0;
        lab_144_2:;
        }
    lab_143_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_143_0;
    lab_143_2:;
    }
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

