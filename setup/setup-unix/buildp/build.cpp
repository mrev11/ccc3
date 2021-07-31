//input: build.ppo (5.3.0)

#include <cccdef.h>

static void _blk_adddep_0(int argno);
static void _blk_build_0(int argno);
static void _blk_build_1(int argno);
static void _blk_build_2(int argno);
static void _blk_build_3(int argno);
static void _blk_build_4(int argno);
static void _blk_byrules_0(int argno);
static void _blk_byrules_1(int argno);
static void _blk_manage_threads_0(int argno);
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
static void _clp_bash(int argno);
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
extern void _clp_eval(int argno);
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
extern void _clp_main(int argno);
static void _clp_makeexe(int argno);
static void _clp_makeexe1(int argno);
static void _clp_makelib(int argno);
static void _clp_makeobj(int argno);
static void _clp_makeso(int argno);
static void _clp_manage_threads(int argno);
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
extern void _clp_spawn(int argno);
extern void _clp_split(int argno);
extern void _clp_str(int argno);
extern void _clp_strtran(int argno);
extern void _clp_substr(int argno);
extern void _clp_thread_cond_init(int argno);
extern void _clp_thread_cond_signal(int argno);
extern void _clp_thread_cond_wait(int argno);
extern void _clp_thread_create(int argno);
extern void _clp_thread_create_detach(int argno);
extern void _clp_thread_join(int argno);
extern void _clp_thread_mutex_init(int argno);
extern void _clp_thread_mutex_lock(int argno);
extern void _clp_thread_mutex_unlock(int argno);
static void _clp_usage(int argno);
extern void _clp_val(int argno);
static void _clp_verifdep(int argno);
static void _clp_xsplit(int argno);
static void _ini__cond_count();
static void _ini__mutex_count();
static void _ini__omitted_hash();
static void _ini__resource_hash();
static void _ini__s_rules();
static void _ini_run1_mutex_out(VALUE*);

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
static VALUE* _st_s_libspec_ptr()
{
    static stvar _st_s_libspec;
    return _st_s_libspec.ptr;
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
static VALUE* _st_s_batext_ptr()
{
    static stvar _st_s_batext;
    return _st_s_batext.ptr;
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
MUTEX_CREATE(_mutex_mutex_count);
static VALUE* _st_mutex_count_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_mutex_count);
    static stvar _st_mutex_count(_ini__mutex_count);
    MUTEX_UNLOCK(_mutex_mutex_count);
    SIGNAL_UNLOCK();
    return _st_mutex_count.ptr;
}
MUTEX_CREATE(_mutex_cond_count);
static VALUE* _st_cond_count_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_cond_count);
    static stvar _st_cond_count(_ini__cond_count);
    MUTEX_UNLOCK(_mutex_cond_count);
    SIGNAL_UNLOCK();
    return _st_cond_count.ptr;
}
MUTEX_CREATE(_mutex_thread_count);
static VALUE* _st_thread_count_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_thread_count);
    static stvar _st_thread_count((double)0);
    MUTEX_UNLOCK(_mutex_thread_count);
    SIGNAL_UNLOCK();
    return _st_thread_count.ptr;
}
MUTEX_CREATE(_mutex_maxthread);
static VALUE* _st_maxthread_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_maxthread);
    static stvar _st_maxthread((double)4);
    MUTEX_UNLOCK(_mutex_maxthread);
    SIGNAL_UNLOCK();
    return _st_maxthread.ptr;
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

static void _ini__mutex_count()
{
    _clp_thread_mutex_init(0);
}

static void _ini__cond_count()
{
    _clp_thread_cond_init(0);
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
    line(82);
    _clp_argv(0);
    _clp_aclone(1);
    assign(base+0);//opt
    pop();
    line(91);
    line(87);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"multithread_support");
    add();
    _clp_file(1);
    topnot();
    if(!flag()) goto if_1_1;
        line(88);
        push(&ONE);
        assign(_st_maxthread_ptr());//global
        pop();
    goto if_1_0;
    if_1_1:
    line(89);
    push(&ONE);
    string(L"BUILD_THR");
    _clp_getenv(1);
    _clp_val(1);
    lteq();
    if(!flag()) goto if_1_2;
        line(90);
        string(L"BUILD_THR");
        _clp_getenv(1);
        _clp_val(1);
        assign(_st_maxthread_ptr());//global
        pop();
    if_1_2:
    if_1_0:;
    line(97);
    line(93);
    push_symbol(_st_s_quiet_ptr());//global
    topnot();
    if(!flag()) goto if_2_1;
        line(94);
        string(nls_text(L"CCC Program Builder "));
        string(L"1.5.0");
        add();
        string(L" Copyright (C) ComFirm Bt.");
        add();
        _clp_qqout(1);
        pop();
        line(95);
        string(L" (Thr");
        push_symbol(_st_maxthread_ptr());//global
        _clp_str(1);
        _clp_alltrim(1);
        add();
        string(L")");
        add();
        _clp_qqout(1);
        pop();
        line(96);
        _clp_qout(0);
        pop();
    if_2_1:
    if_2_0:;
    line(184);
    {
    line(100);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_3_0:
    push_symbol(base+0);//opt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_3_2;
        line(101);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        _clp_procpar(1);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        assign2(idxxl());
        pop();
        line(183);
        line(103);
        string(L"-l");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_1;
            line(104);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_libnam_ptr());//global
            pop();
            line(105);
            push(&FALSE);
            assign(_st_s_shared_ptr());//global
            pop();
        goto if_4_0;
        if_4_1:
        line(108);
        string(L"-s");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_2;
            line(109);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_libnam_ptr());//global
            pop();
            line(110);
            push(&TRUE);
            assign(_st_s_shared_ptr());//global
            pop();
        goto if_4_0;
        if_4_2:
        line(113);
        string(L"-d");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_3;
            line(118);
            line(114);
            push_symbol(_st_s_srcdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_5_1;
                line(115);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_srcdir_ptr());//global
                pop();
            goto if_5_0;
            if_5_1:
            line(116);
                line(117);
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
            if_5_2:
            if_5_0:;
        goto if_4_0;
        if_4_3:
        line(121);
        string(L"-i");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_4;
            line(126);
            line(122);
            push_symbol(_st_s_incdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_6_1;
                line(123);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_incdir_ptr());//global
                pop();
            goto if_6_0;
            if_6_1:
            line(124);
                line(125);
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
            if_6_2:
            if_6_0:;
        goto if_4_0;
        if_4_4:
        line(129);
        string(L"-p");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_5;
            line(134);
            line(130);
            push_symbol(_st_s_libdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_7_1;
                line(131);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_libdir_ptr());//global
                pop();
            goto if_7_0;
            if_7_1:
            line(132);
                line(133);
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
            if_7_2:
            if_7_0:;
        goto if_4_0;
        if_4_5:
        line(137);
        string(L"-b");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_6;
            line(142);
            line(138);
            push_symbol(_st_s_libfil_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_8_1;
                line(139);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_libfil_ptr());//global
                pop();
            goto if_8_0;
            if_8_1:
            line(140);
                line(141);
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
            if_8_2:
            if_8_0:;
        goto if_4_0;
        if_4_6:
        line(145);
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
            line(150);
            line(146);
            push_symbol(_st_s_main_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_9_1;
                line(147);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_main_ptr());//global
                pop();
            goto if_9_0;
            if_9_1:
            line(148);
                line(149);
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
            if_9_2:
            if_9_0:;
        goto if_4_0;
        if_4_7:
        line(152);
        string(L"-o");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_8;
            line(153);
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
        goto if_4_0;
        if_4_8:
        line(155);
        string(L"-h");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_9;
            line(156);
            _clp_usage(0);
            pop();
            line(157);
            _clp___quit(0);
            pop();
        goto if_4_0;
        if_4_9:
        line(159);
        string(L"-q");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_10;
            line(160);
            push(&TRUE);
            assign(_st_s_quiet_ptr());//global
            pop();
        goto if_4_0;
        if_4_10:
        line(162);
        string(L"-v");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_11;
            line(163);
            push(&TRUE);
            assign(_st_s_version_ptr());//global
            pop();
        goto if_4_0;
        if_4_11:
        line(165);
        string(L"--debug");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        if(!flag()) goto if_4_12;
            line(166);
            push(&TRUE);
            assign(_st_s_debug_ptr());//global
            pop();
        goto if_4_0;
        if_4_12:
        line(168);
        string(L"--dry");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        if(!flag()) goto if_4_13;
            line(169);
            push(&TRUE);
            assign(_st_s_debug_ptr());//global
            pop();
            line(170);
            push(&TRUE);
            assign(_st_s_dry_ptr());//global
            pop();
        goto if_4_0;
        if_4_13:
        line(172);
        string(L"@");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        push(&ONE);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_14;
            line(173);
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
        line(175);
        string(L"=");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        ss();
        if(!flag()) goto if_4_15;
            line(176);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_putenv(1);
            pop();
        goto if_4_0;
        if_4_15:
        line(178);
            line(179);
            string(nls_text(L"Invalid switch: "));
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_qout(2);
            pop();
            line(180);
            _clp_usage(0);
            pop();
            line(181);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(182);
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
    line(189);
    line(187);
    string(L"on");
    string(L"BUILD_DBG");
    _clp_getenv(1);
    ss();
    if(!flag()) goto if_10_1;
        line(188);
        push(&TRUE);
        assign(_st_s_debug_ptr());//global
        pop();
    if_10_1:
    if_10_0:;
    line(192);
    line(190);
    string(L"debug");
    string(L"BUILD_DBG");
    _clp_getenv(1);
    ss();
    if(!flag()) goto if_11_1;
        line(191);
        push(&TRUE);
        assign(_st_s_debug_ptr());//global
        pop();
    if_11_1:
    if_11_0:;
    line(196);
    line(193);
    string(L"dry");
    string(L"BUILD_DBG");
    _clp_getenv(1);
    ss();
    if(!flag()) goto if_12_1;
        line(194);
        push(&TRUE);
        assign(_st_s_debug_ptr());//global
        pop();
        line(195);
        push(&TRUE);
        assign(_st_s_dry_ptr());//global
        pop();
    if_12_1:
    if_12_0:;
    line(200);
    line(198);
    push_symbol(_st_s_version_ptr());//global
    if(!flag()) goto if_13_1;
        line(199);
        _clp___quit(0);
        pop();
    if_13_1:
    if_13_0:;
    line(202);
    _clp_s_rules_from_build_bat(0);
    pop();
    line(203);
    _clp_extension_types(0);
    pop();
    line(205);
    _clp_root(0);
    pop();
    line(206);
    _clp_params(0);
    pop();
    line(207);
    _clp_build(0);
    pop();
    line(209);
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
    line(217);
    line(227);
    line(219);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"prg2obj.bat");
    add();
    _clp_file(1);
    if(!flag()) goto if_14_1;
        line(220);
        string(L".bat");
        assign(_st_s_batext_ptr());//global
        pop();
    goto if_14_0;
    if_14_1:
    line(221);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"prg2obj.bash");
    add();
    _clp_file(1);
    if(!flag()) goto if_14_2;
        line(222);
        string(L".bash");
        assign(_st_s_batext_ptr());//global
        pop();
    goto if_14_0;
    if_14_2:
    line(223);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"prg2obj.sh");
    add();
    _clp_file(1);
    if(!flag()) goto if_14_3;
        line(224);
        string(L".sh");
        assign(_st_s_batext_ptr());//global
        pop();
    goto if_14_0;
    if_14_3:
    line(225);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"prg2obj.msys2");
    add();
    _clp_file(1);
    if(!flag()) goto if_14_4;
        line(226);
        string(L".msys2");
        assign(_st_s_batext_ptr());//global
        pop();
    if_14_4:
    if_14_0:;
    line(229);
    push_symbol(_st_s_rules_ptr());//global
    push(&ZERO);
    _clp_asize(2);
    pop();
    line(230);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"*");
    add();
    push_symbol(_st_s_batext_ptr());//global
    add();
    _clp_directory(1);
    assign(base+0);//d
    pop();
    line(238);
    {
    line(231);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_15_0:
    push_symbol(base+0);//d
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_15_2;
        line(232);
        push_symbol(base+0);//d
        push_symbol(base+1);//n
        idxr();
        idxr0(1);
        push_symbol(_st_s_batext_ptr());//global
        string(L"");
        _clp_strtran(3);
        string(L"2");
        _clp_split(2);
        assign(base+2);//rule
        pop();
        line(237);
        line(233);
        push_symbol(base+2);//rule
        _clp_len(1);
        number(2);
        eqeq();
        if(!flag()) goto if_16_1;
            line(234);
            string(L".");
            push_symbol(base+2);//rule
            idxr0(1);
            add();
            push_symbol(base+2);//rule
            assign2(idxxl0(1));
            pop();
            line(235);
            string(L".");
            push_symbol(base+2);//rule
            idxr0(2);
            add();
            push_symbol(base+2);//rule
            assign2(idxxl0(2));
            pop();
            line(236);
            push_symbol(_st_s_rules_ptr());//global
            push_symbol(base+2);//rule
            _clp_aadd(2);
            pop();
        if_16_1:
        if_16_0:;
    lab_15_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+1);//n
    add();
    assign(base+1);//n
    goto lab_15_0;
    lab_15_2:;
    }
    line(240);
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
    line(247);
    line(248);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_17_1;
        string(L".exe");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_17_1:
    if_17_0:;
    line(249);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_18_1;
        string(L".so");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_18_1:
    if_18_0:;
    line(250);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_19_1;
        string(L".lib");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_19_1:
    if_19_0:;
    line(251);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_20_1;
        string(L".obj");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_20_1:
    if_20_0:;
    line(252);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_21_1;
        push_symbol(base+0);//x
        idxr0(1);
        push_symbol(base+1);//y
        idxr0(1);
        lt();
        assign(base+2);//result
        pop();
    if_21_1:
    if_21_0:;
    line(253);
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
    line(260);
    line(256);
    push_symbol(base+1);//x
    idxr0(2);
    push_symbol(base+0);//ext
    eqeq();
    if(!flag()) goto if_22_1;
        line(257);
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
    goto if_22_0;
    if_22_1:
    line(258);
    push_symbol(base+2);//y
    idxr0(2);
    push_symbol(base+0);//ext
    eqeq();
    if(!flag()) goto if_22_2;
        line(259);
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
    if_22_2:
    if_22_0:;
    line(261);
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
    line(265);
    line(267);
    string(L"");
    assign(_st_s_primary_ptr());//global
    pop();
    line(268);
    string(L"");
    assign(_st_s_resource_ptr());//global
    pop();
    line(282);
    {
    line(270);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_23_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_23_2;
        line(271);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+2);//n
        idxr();
        idxr0(1);
        assign(base+0);//r1
        pop();
        line(272);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+2);//n
        idxr();
        idxr0(2);
        assign(base+1);//r2
        pop();
        line(278);
        line(276);
        push_symbol(base+1);//r2
        string(L".obj");
        eqeq();
        if(!flag()) goto if_24_1;
            line(277);
            push_symbol(_st_s_primary_ptr());//global
            push_symbol(base+0);//r1
            add();
            assign(_st_s_primary_ptr());//global
            pop();
        if_24_1:
        if_24_0:;
        line(281);
        line(279);
        push_symbol(base+1);//r2
        string(L".");
        add();
        string(L".obj.lib.exe.");
        ss();
        topnot();
        if(!flag()) goto if_25_1;
            line(280);
            push_symbol(_st_s_resource_ptr());//global
            push_symbol(base+0);//r1
            add();
            assign(_st_s_resource_ptr());//global
            pop();
        if_25_1:
        if_25_0:;
    lab_23_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_23_0;
    lab_23_2:;
    }
    line(283);
    push_symbol(_st_s_primary_ptr());//global
    string(L".");
    add();
    assign(_st_s_primary_ptr());//global
    pop();
    line(284);
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
    line(291);
    push_symbol(base+0);//parfil
    _clp_memoread(1);
    assign(base+3);//par
    pop();
    line(298);
    line(293);
    push_symbol(base+3);//par
    _clp_empty(1);
    if(!flag()) goto if_26_1;
        line(297);
        string(L"BUILD_BAT");
        _clp_getenv(1);
        _clp_dirsep(0);
        add();
        push_symbol(base+0);//parfil
        add();
        _clp_memoread(1);
        assign(base+3);//par
        pop();
    if_26_1:
    if_26_0:;
    line(306);
    line(300);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_27_1;
        line(305);
        line(301);
        push_symbol(base+3);//par
        _clp_empty(1);
        if(!flag()) goto if_28_1;
            line(302);
            string(L"Build parfile empty:");
            push_symbol(base+0);//parfil
            _clp_qqout(2);
            pop();
            _clp_qout(0);
            pop();
        goto if_28_0;
        if_28_1:
        line(303);
            line(304);
            string(L"Build parfile:");
            push_symbol(base+0);//parfil
            _clp_qqout(2);
            pop();
            _clp_qout(0);
            pop();
        if_28_2:
        if_28_0:;
    if_27_1:
    if_27_0:;
    line(308);
    push_symbol(base+3);//par
    number(13);
    _clp_chr(1);
    string(L"");
    _clp_strtran(3);
    assign(base+3);//par
    pop();
    line(309);
    push_symbol(base+3);//par
    number(10);
    _clp_chr(1);
    _clp_split(2);
    assign(base+3);//par
    pop();
    line(325);
    {
    line(311);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_29_0:
    push_symbol(base+3);//par
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_29_2;
        line(312);
        push_symbol(base+3);//par
        push_symbol(base+4);//n
        idxr();
        assign(base+5);//p
        pop();
        line(315);
        line(313);
        string(L"#");
        push_symbol(base+5);//p
        ss();
        if(!flag()) goto if_30_1;
            line(314);
            push_symbol(base+5);//p
            string(L"#");
            push_symbol(base+5);//p
            _clp_at(2);
            addnum(-1);
            _clp_left(2);
            assign(base+5);//p
            pop();
        if_30_1:
        if_30_0:;
        line(317);
        push_symbol(base+5);//p
        string(L" ");
        _clp_split(2);
        assign(base+5);//p
        pop();
        line(324);
        {
        line(318);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+6);//i
        lab_31_0:
        push_symbol(base+5);//p
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_31_2;
            line(323);
            line(319);
            push_symbol(base+5);//p
            push_symbol(base+6);//i
            idxr();
            _clp_empty(1);
            topnot();
            if(!flag()) goto if_32_1;
                line(320);
                push_symbol(base+1);//opt
                push(&NIL);
                _clp_aadd(2);
                pop();
                line(321);
                push_symbol(base+1);//opt
                push_symbol(base+2);//optx
                push(&ONE);
                add();
                assign(base+2);//optx
                _clp_ains(2);
                pop();
                line(322);
                push_symbol(base+5);//p
                push_symbol(base+6);//i
                idxr();
                push_symbol(base+1);//opt
                push_symbol(base+2);//optx
                assign2(idxxl());
                pop();
            if_32_1:
            if_32_0:;
        lab_31_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+6);//i
        add();
        assign(base+6);//i
        goto lab_31_0;
        lab_31_2:;
        }
    lab_29_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_29_0;
    lab_29_2:;
    }
    line(326);
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
    line(330);
    line(339);
    lab_33_1:
    line(332);
    push(&ZERO);
    string(L"$$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_33_2;
        line(333);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(334);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(3);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(335);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(336);
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
        line(337);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(338);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_33_1;
    lab_33_2:;
    line(348);
    lab_34_1:
    line(341);
    push(&ZERO);
    string(L"$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_34_2;
        line(342);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(343);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(2);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(344);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(345);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        _clp_getenv(1);
        add();
        assign(base+2);//p
        pop();
        line(346);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(347);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_34_1;
    lab_34_2:;
    line(350);
    push_symbol(base+0);//par
    string(L"\\");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(351);
    push_symbol(base+0);//par
    string(L"/");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(353);
    push_symbol(base+0);//par
    push(&ONE);
    _clp_left(2);
    string(L"=");
    eqeq();
    if(flag()){
    push_symbol(base+0);//par
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
    line(358);
    string(nls_text(L"BUILD -xExeNam|-lLibNam -dSrcDir -iIncDir -pLibDir -bLibFil -mMain"));
    _clp_qout(1);
    pop();
    line(359);
    _clp_qout(0);
    pop();
    line(360);
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
    line(366);
    line(403);
    line(368);
    string(L"BUILD_SRC");
    _clp_getenv(1);
    assign(base+0);//srcroot
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_35_1;
        line(372);
        line(370);
        push_symbol(base+0);//srcroot
        push(&ONE);
        _clp_right(2);
        string(L"/\\");
        ss();
        topnot();
        if(!flag()) goto if_36_1;
            line(371);
            push_symbol(base+0);//srcroot
            _clp_dirsep(0);
            add();
            assign(base+0);//srcroot
            pop();
        if_36_1:
        if_36_0:;
        line(376);
        line(374);
        push_symbol(_st_s_srcdir_ptr());//global
        push(&NIL);
        eqeq();
        if(!flag()) goto if_37_1;
            line(375);
            string(L".");
            assign(_st_s_srcdir_ptr());//global
            pop();
        if_37_1:
        if_37_0:;
        line(378);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+1);//d
        pop();
        line(380);
        string(L"");
        assign(_st_s_srcdir_ptr());//global
        pop();
        line(387);
        {
        line(381);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+2);//n
        lab_38_0:
        push_symbol(base+1);//d
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_38_2;
            line(386);
            line(382);
            push_symbol(base+1);//d
            push_symbol(base+2);//n
            idxr();
            push(&ONE);
            _clp_left(2);
            string(L"/\\");
            ss();
            if(!flag()) goto if_39_1;
                line(383);
                push_symbol(_st_s_srcdir_ptr());//global
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                string(L";");
                add();
                add();
                assign(_st_s_srcdir_ptr());//global
                pop();
            goto if_39_0;
            if_39_1:
            line(384);
                line(385);
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
            if_39_2:
            if_39_0:;
        lab_38_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+2);//n
        add();
        assign(base+2);//n
        goto lab_38_0;
        lab_38_2:;
        }
        line(402);
        line(390);
        push_symbol(_st_s_incdir_ptr());//global
        push(&NIL);
        neeq();
        if(!flag()) goto if_40_1;
            line(392);
            push_symbol(_st_s_incdir_ptr());//global
            string(L",;");
            _clp_xsplit(2);
            assign(base+1);//d
            pop();
            line(394);
            string(L"");
            assign(_st_s_incdir_ptr());//global
            pop();
            line(401);
            {
            line(395);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+2);//n
            lab_41_0:
            push_symbol(base+1);//d
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_41_2;
                line(400);
                line(396);
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                push(&ONE);
                _clp_left(2);
                string(L"/\\");
                ss();
                if(!flag()) goto if_42_1;
                    line(397);
                    push_symbol(_st_s_incdir_ptr());//global
                    push_symbol(base+1);//d
                    push_symbol(base+2);//n
                    idxr();
                    string(L";");
                    add();
                    add();
                    assign(_st_s_incdir_ptr());//global
                    pop();
                goto if_42_0;
                if_42_1:
                line(398);
                    line(399);
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
                if_42_2:
                if_42_0:;
            lab_41_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+2);//n
            add();
            assign(base+2);//n
            goto lab_41_0;
            lab_41_2:;
            }
        if_40_1:
        if_40_0:;
    if_35_1:
    if_35_0:;
    line(405);
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
    line(411);
    line(424);
    string(L"");
    assign(base+0);//txt
    pop();
    line(425);
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
    line(426);
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
    line(427);
    push_symbol(base+0);//txt
    string(L"BUILD_INC");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(428);
    push_symbol(base+0);//txt
    string(L"include");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(429);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(430);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(432);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(434);
    string(L"BUILD_INC=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(440);
    string(L"");
    assign(base+0);//txt
    pop();
    line(441);
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
    line(442);
    push_symbol(base+0);//txt
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(443);
    push_symbol(base+0);//txt
    string(L"lib");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(444);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(445);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(447);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(449);
    string(L"BUILD_LPT=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(455);
    string(L"");
    assign(base+0);//txt
    pop();
    line(456);
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
    line(457);
    push_symbol(base+0);//txt
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(458);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(459);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(460);
    string(L"BUILD_LIB=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(461);
    _clp_search_library(0);
    assign(_st_s_libspec_ptr());//global
    pop();
    line(462);
    string(L"BUILD_LIB=");
    push_symbol(_st_s_libspec_ptr());//global
    add();
    _clp_putenv(1);
    pop();
    line(463);
    push_symbol(_st_s_libspec_ptr());//global
    string(L" ");
    _clp_split(2);
    assign(_st_s_libspec_ptr());//global
    pop();
    line(465);
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
    line(471);
    array(0);
    assign(base+0);//dir
    pop();
    line(472);
    array(0);
    assign(base+1);//obj
    pop();
    line(473);
    array(0);
    assign(base+2);//lib
    pop();
    line(474);
    array(0);
    assign(base+3);//mmd
    pop();
    line(475);
    array(0);
    assign(base+4);//todo
    pop();
    line(477);
    line(482);
    line(480);
    push_symbol(_st_s_main_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_43_1;
        line(481);
        push_symbol(_st_s_main_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+3);//mmd
        pop();
    if_43_1:
    if_43_0:;
    line(489);
    line(485);
    push_symbol(_st_s_srcdir_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_44_1;
        line(486);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+0);//dir
        pop();
    goto if_44_0;
    if_44_1:
    line(487);
        line(488);
        string(L".");
        array(1);
        assign(base+0);//dir
        pop();
    if_44_2:
    if_44_0:;
    line(513);
    {
    line(491);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_45_0:
    push_symbol(base+0);//dir
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_45_2;
        line(493);
        string(L"");
        push_symbol(base+0);//dir
        push_symbol(base+8);//n
        idxr();
        _clp_qqout(2);
        pop();
        line(495);
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
        line(512);
        {
        line(497);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//i
        lab_46_0:
        push_symbol(base+5);//d1
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_46_2;
            line(499);
            push_symbol(base+5);//d1
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            assign(base+6);//f
            pop();
            line(507);
            line(501);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            push_symbol(_st_s_primary_ptr());//global
            ss();
            if(!flag()) goto if_47_1;
                line(506);
                line(502);
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
                if(!flag()) goto if_48_1;
                goto if_48_0;
                if_48_1:
                line(504);
                    line(505);
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
                if_48_2:
                if_48_0:;
            if_47_1:
            if_47_0:;
            line(511);
            line(509);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            push_symbol(_st_s_resource_ptr());//global
            ss();
            if(!flag()) goto if_49_1;
                line(510);
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
            if_49_1:
            if_49_0:;
        lab_46_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//i
        add();
        assign(base+9);//i
        goto lab_46_0;
        lab_46_2:;
        }
    lab_45_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_45_0;
    lab_45_2:;
    }
    line(514);
    _clp_qout(0);
    pop();
    line(550);
    {
    line(519);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_50_0:
    push_symbol(base+1);//obj
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_50_2;
        line(521);
        push_symbol(base+1);//obj
        push_symbol(base+8);//n
        idxr();
        assign(base+6);//f
        pop();
        line(522);
        push_symbol(base+6);//f
        _clp_fname(1);
        assign(base+7);//o
        pop();
        line(523);
        push_symbol(base+6);//f
        _clp_memoread(1);
        assign(base+10);//txt
        pop();
        line(533);
        line(525);
        push(&ZERO);
        push_symbol(base+3);//mmd
        push_symbol_ref(base+7);//o
        block(_blk_build_0,1);
        _clp_ascan(2);
        neeq();
        if(!flag()) goto if_51_1;
        goto if_51_0;
        if_51_1:
        line(527);
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
        if(!flag()) goto if_51_2;
            line(530);
            line(528);
            push_symbol(_st_s_main_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_52_1;
                line(529);
                push_symbol(base+3);//mmd
                push_symbol(base+7);//o
                _clp_aadd(2);
                pop();
            if_52_1:
            if_52_0:;
        goto if_51_0;
        if_51_2:
        line(531);
            line(532);
            push_symbol(base+2);//lib
            push_symbol(base+7);//o
            _clp_aadd(2);
            pop();
        if_51_3:
        if_51_0:;
        line(535);
        push_symbol(base+7);//o
        string(L".obj");
        add();
        push_symbol(base+6);//f
        array(2);
        assign(base+11);//dep
        pop();
        line(547);
        {
        line(536);
        push(&ONE);
        int sg=sign();
        number(2);
        assign(base+9);//i
        lab_53_0:
        push_symbol(base+11);//dep
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_53_2;
            line(545);
            line(537);
            push_symbol(base+9);//i
            number(2);
            eqeq();
            if(!flag()) goto if_54_1;
            goto if_54_0;
            if_54_1:
            line(539);
            push_symbol(base+9);//i
            number(1024);
            gt();
            if(!flag()) goto if_54_2;
                line(540);
                string(L"recursive dependencies:");
                push_symbol(base+11);//dep
                _clp_qout(2);
                pop();
                line(541);
                _clp_qout(0);
                pop();
                line(542);
                _clp___quit(0);
                pop();
            goto if_54_0;
            if_54_2:
            line(543);
                line(544);
                push_symbol(base+11);//dep
                push_symbol(base+9);//i
                idxr();
                _clp_memoread(1);
                assign(base+10);//txt
                pop();
            if_54_3:
            if_54_0:;
            line(546);
            push_symbol(base+10);//txt
            push_symbol(base+11);//dep
            push_symbol(base+0);//dir
            push_symbol(base+4);//todo
            _clp_search_include(4);
            pop();
        lab_53_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//i
        add();
        assign(base+9);//i
        goto lab_53_0;
        lab_53_2:;
        }
        line(549);
        push_symbol(base+4);//todo
        push_symbol(base+11);//dep
        _clp_aadd(2);
        pop();
    lab_50_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_50_0;
    lab_50_2:;
    }
    line(552);
    push_symbol(base+4);//todo
    _clp_normalize(1);
    pop();
    line(554);
    push_symbol(base+4);//todo
    push(&NIL);
    push(&NIL);
    block(_blk_build_1,0);
    _clp_asort(4);
    pop();
    line(566);
    line(558);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_55_1;
        line(559);
        string(L"main:");
        push_symbol(base+3);//mmd
        _clp_qout(2);
        pop();
        line(560);
        string(L"lib :");
        push_symbol(base+2);//lib
        _clp_qout(2);
        pop();
        line(561);
        _clp_qout(0);
        pop();
        line(564);
        {
        line(562);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_56_0:
        push_symbol(base+4);//todo
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_56_2;
            line(563);
            push_symbol(base+4);//todo
            push_symbol(base+8);//n
            idxr();
            _clp_qout(1);
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
        line(565);
        _clp_qout(0);
        pop();
    if_55_1:
    if_55_0:;
    line(568);
    string(L"error");
    _clp_ferase(1);
    pop();
    line(587);
    {
    line(569);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_57_0:
    push_symbol(base+4);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_57_2;
        line(570);
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_mutex_lock(1);
        pop();
        line(571);
        push_symbol(_st_thread_count_ptr());//global
        push(&ONE);
        add();
        assign(_st_thread_count_ptr());//global
        pop();
        line(574);
        lab_58_1:
        line(572);
        push_symbol(_st_thread_count_ptr());//global
        push_symbol(_st_maxthread_ptr());//global
        gt();
        if(!flag()) goto lab_58_2;
            line(573);
            push_symbol(_st_cond_count_ptr());//global
            push_symbol(_st_mutex_count_ptr());//global
            _clp_thread_cond_wait(2);
            pop();
        goto lab_58_1;
        lab_58_2:;
        line(575);
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_mutex_unlock(1);
        pop();
        line(577);
        push_symbol_ref(base+4);//todo
        block(_blk_build_2,1);
        push_symbol(base+8);//n
        _clp_thread_create_detach(2);
        pop();
        line(586);
        line(579);
        push_symbol(base+4);//todo
        push_symbol(base+8);//n
        idxr();
        idxr0(1);
        _clp_fext(1);
        string(L".obj");
        eqeq();
        topnot();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+8);//n
        push_symbol(base+4);//todo
        _clp_len(1);
        lt();
        }
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+4);//todo
        push_symbol(base+8);//n
        addnum(1);
        idxr();
        idxr0(1);
        _clp_fext(1);
        string(L".obj");
        eqeq();
        }
        if(!flag()) goto if_59_1;
            line(581);
            push_symbol(_st_mutex_count_ptr());//global
            _clp_thread_mutex_lock(1);
            pop();
            line(584);
            lab_60_1:
            line(582);
            push_symbol(_st_thread_count_ptr());//global
            push(&ZERO);
            gt();
            if(!flag()) goto lab_60_2;
                line(583);
                push_symbol(_st_cond_count_ptr());//global
                push_symbol(_st_mutex_count_ptr());//global
                _clp_thread_cond_wait(2);
                pop();
            goto lab_60_1;
            lab_60_2:;
            line(585);
            push_symbol(_st_mutex_count_ptr());//global
            _clp_thread_mutex_unlock(1);
            pop();
        if_59_1:
        if_59_0:;
    lab_57_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_57_0;
    lab_57_2:;
    }
    line(589);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(592);
    lab_61_1:
    line(590);
    push_symbol(_st_thread_count_ptr());//global
    push(&ZERO);
    gt();
    if(!flag()) goto lab_61_2;
        line(591);
        push_symbol(_st_cond_count_ptr());//global
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_cond_wait(2);
        pop();
    goto lab_61_1;
    lab_61_2:;
    line(593);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    line(614);
    line(597);
    push_symbol(_st_s_libnam_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_62_1;
        line(598);
        push_symbol(_st_s_libnam_ptr());//global
        push_symbol(base+2);//lib
        _clp_makelib(2);
        pop();
        line(602);
        line(600);
        push_symbol(_st_s_shared_ptr());//global
        push(&TRUE);
        eqeq();
        if(!flag()) goto if_63_1;
            line(601);
            push_symbol(_st_s_libnam_ptr());//global
            push_symbol(base+2);//lib
            _clp_makeso(2);
            pop();
        if_63_1:
        if_63_0:;
        line(607);
        block(_blk_build_3,0);
        push_symbol(base+3);//mmd
        _clp_manage_threads(2);
        pop();
    goto if_62_0;
    if_62_1:
    line(609);
        line(613);
        push_symbol_ref(base+2);//lib
        block(_blk_build_4,1);
        push_symbol(base+3);//mmd
        _clp_manage_threads(2);
        pop();
    if_62_2:
    if_62_0:;
    line(616);
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

static void _blk_build_2(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_build_2",base);
//
    push_blkenv(env+0);//todo
    push_blkarg(base+1);//i
    idxr();
    _clp_makeobj(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_build_3(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_build_3",base);
//
    push_blkarg(base+1);//x
    push_symbol(_st_s_libnam_ptr());//global
    _clp_makeexe1(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_build_4(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_build_4",base);
//
    push_blkarg(base+1);//x
    push_blkenv(env+0);//lib
    _clp_makeexe(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
static void _clp_manage_threads(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+5)PUSHNIL();
argno=2;
push_call("manage_threads",base);
//
    line(622);
    array(0);
    assign(base+2);//thread
    pop();
    line(633);
    {
    line(623);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_64_0:
    push_symbol(base+1);//a
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_64_2;
        line(624);
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_mutex_lock(1);
        pop();
        line(625);
        push_symbol(_st_thread_count_ptr());//global
        push(&ONE);
        add();
        assign(_st_thread_count_ptr());//global
        pop();
        line(628);
        lab_65_1:
        line(626);
        push_symbol(_st_thread_count_ptr());//global
        push_symbol(_st_maxthread_ptr());//global
        gt();
        if(!flag()) goto lab_65_2;
            line(627);
            push_symbol(_st_cond_count_ptr());//global
            push_symbol(_st_mutex_count_ptr());//global
            _clp_thread_cond_wait(2);
            pop();
        goto lab_65_1;
        lab_65_2:;
        line(629);
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_mutex_unlock(1);
        pop();
        line(631);
        push_symbol_ref(base+0);//blk
        push_symbol_ref(base+1);//a
        block(_blk_manage_threads_0,2);
        push_symbol(base+4);//n
        _clp_thread_create(2);
        assign(base+3);//th
        pop();
        line(632);
        push_symbol(base+2);//thread
        push_symbol(base+3);//th
        _clp_aadd(2);
        pop();
    lab_64_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_64_0;
    lab_64_2:;
    }
    line(636);
    {
    line(634);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_66_0:
    push_symbol(base+2);//thread
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_66_2;
        line(635);
        push_symbol(base+2);//thread
        push_symbol(base+4);//n
        idxr();
        _clp_thread_join(1);
        pop();
    lab_66_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_66_0;
    lab_66_2:;
    }
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_manage_threads_0(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_manage_threads_0",base);
//
    push_blkenv(env+0);//blk
    push_blkenv(env+1);//a
    push_blkarg(base+1);//i
    idxr();
    _clp_eval(2);
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
    line(642);
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
    line(643);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(644);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2so");
    add();
    push_symbol(_st_s_batext_ptr());//global
    add();
    assign(base+7);//torun
    pop();
    line(645);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(652);
    line(647);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_67_1;
        line(648);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(649);
        _clp_qout(0);
        pop();
        line(650);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(651);
        _clp___quit(0);
        pop();
    if_67_1:
    if_67_0:;
    line(654);
    push_symbol(base+7);//torun
    string(L" lib");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(656);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(659);
    line(657);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_68_1;
        line(658);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_68_1:
    if_68_0:;
    line(663);
    line(661);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_69_1;
        line(662);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_69_1:
    if_69_0:;
    line(671);
    {
    line(665);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_70_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_70_2;
        line(667);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(668);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+4);//depend
        add();
        add();
        assign(base+7);//torun
        pop();
        line(669);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(670);
        push_symbol(base+3);//ttarget
        push_symbol(base+4);//depend
        _clp_verifdep(2);
        if(flag()){
        push(&TRUE);
        }else{
        push_symbol(base+6);//update
        }
        assign(base+6);//update
        pop();
    lab_70_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_70_0;
    lab_70_2:;
    }
    line(675);
    line(673);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_71_1;
        line(674);
        _clp_qout(0);
        pop();
    if_71_1:
    if_71_0:;
    line(679);
    line(677);
    push_symbol(base+6);//update
    if(!flag()) goto if_72_1;
        line(678);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_72_1:
    if_72_0:;
    line(681);
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
    line(687);
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
    line(688);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(689);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2lib");
    add();
    push_symbol(_st_s_batext_ptr());//global
    add();
    assign(base+7);//torun
    pop();
    line(690);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(691);
    line(698);
    line(693);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_73_1;
        line(694);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(695);
        _clp_qout(0);
        pop();
        line(696);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(697);
        _clp___quit(0);
        pop();
    if_73_1:
    if_73_0:;
    line(700);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(702);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(705);
    line(703);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_74_1;
        line(704);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_74_1:
    if_74_0:;
    line(709);
    line(707);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_75_1;
        line(708);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_75_1:
    if_75_0:;
    line(716);
    {
    line(711);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_76_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_76_2;
        line(713);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(714);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(715);
        push_symbol(base+3);//ttarget
        push_symbol(base+4);//depend
        _clp_verifdep(2);
        if(flag()){
        push(&TRUE);
        }else{
        push_symbol(base+6);//update
        }
        assign(base+6);//update
        pop();
    lab_76_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_76_0;
    lab_76_2:;
    }
    line(720);
    line(718);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_77_1;
        line(719);
        _clp_qout(0);
        pop();
    if_77_1:
    if_77_0:;
    line(748);
    line(722);
    push_symbol(base+6);//update
    if(!flag()) goto if_78_1;
        line(727);
        {
        line(725);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_79_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_79_2;
            line(726);
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
        line(747);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_78_1:
    if_78_0:;
    line(750);
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
    line(756);
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
    line(757);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(758);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2exe");
    add();
    push_symbol(_st_s_batext_ptr());//global
    add();
    assign(base+7);//torun
    pop();
    line(759);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(760);
    line(767);
    line(762);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_80_1;
        line(763);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(764);
        _clp_qout(0);
        pop();
        line(765);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(766);
        _clp___quit(0);
        pop();
    if_80_1:
    if_80_0:;
    line(769);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(772);
    line(770);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_81_1;
        line(771);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_81_1:
    if_81_0:;
    line(776);
    line(774);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_82_1;
        line(775);
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
    line(788);
    {
    line(778);
    push(&ONE);
    int sg=sign();
    push(&ZERO);
    assign(base+9);//n
    lab_83_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_83_2;
        line(784);
        line(780);
        push_symbol(base+9);//n
        push(&ZERO);
        eqeq();
        if(!flag()) goto if_84_1;
            line(781);
            push_symbol(base+0);//exenam
            assign(base+4);//depend
            pop();
        goto if_84_0;
        if_84_1:
        line(782);
            line(783);
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
        if_84_2:
        if_84_0:;
        line(786);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(787);
        push_symbol(base+3);//ttarget
        push_symbol(base+4);//depend
        _clp_verifdep(2);
        if(flag()){
        push(&TRUE);
        }else{
        push_symbol(base+6);//update
        }
        assign(base+6);//update
        pop();
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
    line(795);
    {
    line(790);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_85_0:
    push_symbol(_st_s_libspec_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_85_2;
        line(794);
        line(791);
        push_symbol(_st_s_libspec_ptr());//global
        push_symbol(base+9);//n
        idxr();
        number(4);
        _clp_right(2);
        string(L".lib");
        eqeq();
        if(!flag()) goto if_86_1;
            line(792);
            push_symbol(_st_s_libspec_ptr());//global
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
            line(793);
            push_symbol(base+3);//ttarget
            push_symbol(base+4);//depend
            _clp_verifdep(2);
            if(flag()){
            push(&TRUE);
            }else{
            push_symbol(base+6);//update
            }
            assign(base+6);//update
            pop();
        if_86_1:
        if_86_0:;
    lab_85_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_85_0;
    lab_85_2:;
    }
    line(799);
    line(797);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_87_1;
        line(798);
        _clp_qout(0);
        pop();
    if_87_1:
    if_87_0:;
    line(833);
    line(801);
    push_symbol(base+6);//update
    if(!flag()) goto if_88_1;
        line(802);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+0);//exenam
        add();
        add();
        assign(base+7);//torun
        pop();
        line(807);
        {
        line(805);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_89_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_89_2;
            line(806);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
            pop();
        lab_89_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_89_0;
        lab_89_2:;
        }
        line(832);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_88_1:
    if_88_0:;
    line(835);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(836);
    push_symbol(_st_thread_count_ptr());//global
    push(&ONE);
    sub();
    assign(_st_thread_count_ptr());//global
    pop();
    line(837);
    push_symbol(_st_cond_count_ptr());//global
    _clp_thread_cond_signal(1);
    pop();
    line(838);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    line(840);
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
    line(846);
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
    line(847);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(848);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"lib2exe");
    add();
    push_symbol(_st_s_batext_ptr());//global
    add();
    assign(base+7);//torun
    pop();
    line(849);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(856);
    line(851);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_90_1;
        line(852);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(853);
        _clp_qout(0);
        pop();
        line(854);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(855);
        _clp___quit(0);
        pop();
    if_90_1:
    if_90_0:;
    line(858);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(861);
    line(859);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_91_1;
        line(860);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_91_1:
    if_91_0:;
    line(865);
    line(863);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_92_1;
        line(864);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_92_1:
    if_92_0:;
    line(868);
    push_symbol(base+0);//mmod
    assign(base+4);//depend
    pop();
    line(869);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(870);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".obj");
    add();
    assign(base+4);//depend
    pop();
    line(871);
    push_symbol(base+3);//ttarget
    push_symbol(base+4);//depend
    _clp_verifdep(2);
    if(flag()){
    push(&TRUE);
    }else{
    push_symbol(base+6);//update
    }
    assign(base+6);//update
    pop();
    line(873);
    push_symbol(base+1);//libnam
    assign(base+4);//depend
    pop();
    line(874);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(875);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".lib");
    add();
    assign(base+4);//depend
    pop();
    line(876);
    push_symbol(base+3);//ttarget
    push_symbol(base+4);//depend
    _clp_verifdep(2);
    if(flag()){
    push(&TRUE);
    }else{
    push_symbol(base+6);//update
    }
    assign(base+6);//update
    pop();
    line(883);
    {
    line(878);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_93_0:
    push_symbol(_st_s_libspec_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_93_2;
        line(882);
        line(879);
        push_symbol(_st_s_libspec_ptr());//global
        push_symbol(base+9);//n
        idxr();
        number(4);
        _clp_right(2);
        string(L".lib");
        eqeq();
        if(!flag()) goto if_94_1;
            line(880);
            push_symbol(_st_s_libspec_ptr());//global
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
            line(881);
            push_symbol(base+3);//ttarget
            push_symbol(base+4);//depend
            _clp_verifdep(2);
            if(flag()){
            push(&TRUE);
            }else{
            push_symbol(base+6);//update
            }
            assign(base+6);//update
            pop();
        if_94_1:
        if_94_0:;
    lab_93_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_93_0;
    lab_93_2:;
    }
    line(887);
    line(885);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_95_1;
        line(886);
        _clp_qout(0);
        pop();
    if_95_1:
    if_95_0:;
    line(891);
    line(889);
    push_symbol(base+6);//update
    if(!flag()) goto if_96_1;
        line(890);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_96_1:
    if_96_0:;
    line(893);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(894);
    push_symbol(_st_thread_count_ptr());//global
    push(&ONE);
    sub();
    assign(_st_thread_count_ptr());//global
    pop();
    line(895);
    push_symbol(_st_cond_count_ptr());//global
    _clp_thread_cond_signal(1);
    pop();
    line(896);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
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
    if(!flag()) goto if_97_1;
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
    if_97_1:
    if_97_0:;
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
    if(!flag()) goto if_98_1;
        line(917);
        string(L"");
        assign(base+4);//ttarget
        pop();
    if_98_1:
    if_98_0:;
    line(922);
    line(920);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_99_1;
        line(921);
        push_symbol(base+1);//target
        string(L"[");
        push_symbol(base+4);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_99_1:
    if_99_0:;
    line(927);
    {
    line(924);
    push(&ONE);
    int sg=sign();
    number(2);
    assign(base+8);//n
    lab_100_0:
    push_symbol(base+0);//deplist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_100_2;
        line(925);
        push_symbol(base+0);//deplist
        push_symbol(base+8);//n
        idxr();
        assign(base+2);//depend
        pop();
        line(926);
        push_symbol(base+4);//ttarget
        push_symbol(base+2);//depend
        _clp_verifdep(2);
        if(flag()){
        push(&TRUE);
        }else{
        push_symbol(base+6);//update
        }
        assign(base+6);//update
        pop();
    lab_100_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_100_0;
    lab_100_2:;
    }
    line(931);
    line(929);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_101_1;
        line(930);
        _clp_qout(0);
        pop();
    if_101_1:
    if_101_0:;
    line(950);
    line(933);
    push_symbol(base+6);//update
    if(!flag()) goto if_102_1;
        line(935);
        string(L"BUILD_BAT");
        _clp_getenv(1);
        _clp_dirsep(0);
        add();
        assign(base+7);//torun
        pop();
        line(936);
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
        line(937);
        push_symbol(base+7);//torun
        push_symbol(_st_s_batext_ptr());//global
        add();
        assign(base+7);//torun
        pop();
        line(944);
        line(939);
        push_symbol(base+7);//torun
        _clp_file(1);
        topnot();
        if(!flag()) goto if_103_1;
            line(940);
            string(L"[");
            push_symbol(base+7);//torun
            add();
            string(L"]");
            add();
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(941);
            _clp_qout(0);
            pop();
            line(942);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(943);
            _clp___quit(0);
            pop();
        if_103_1:
        if_103_0:;
        line(946);
        push_symbol(base+0);//deplist
        idxr0(1);
        _clp_fname(1);
        assign(base+9);//p1
        pop();
        line(947);
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
        line(949);
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
    if_102_1:
    if_102_0:;
    line(952);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(953);
    push_symbol(_st_thread_count_ptr());//global
    push(&ONE);
    sub();
    assign(_st_thread_count_ptr());//global
    pop();
    line(954);
    push_symbol(_st_cond_count_ptr());//global
    _clp_thread_cond_signal(1);
    pop();
    line(955);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    line(957);
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
while(stack<base+3)PUSHNIL();
argno=1;
push_call("run1",base);
//
    line(964);
    static stvarloc _st_mutex_out(_ini_run1_mutex_out,base);
    line(965);
    static stvar _st_count((double)0);
    line(966);
    line(999);
    line(968);
    push_symbol(_st_s_dry_ptr());//global
    topnot();
    if(!flag()) goto if_104_1;
        line(970);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_lock(1);
        pop();
        line(971);
        string(L"log-runtmp");
        push_symbol(_st_count.ptr);//run1
        push(&ONE);
        add();
        assign(_st_count.ptr);//run1
        _clp_str(1);
        _clp_alltrim(1);
        add();
        assign(base+1);//runtmp
        pop();
        line(972);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_unlock(1);
        pop();
        line(980);
        line(974);
        string(L"msys2");
        string(L"BUILD_BAT");
        _clp_getenv(1);
        ss();
        if(!flag()) goto if_105_1;
            line(976);
            push_symbol(base+0);//cmd
            string(L" >");
            add();
            push_symbol(base+1);//runtmp
            add();
            _clp_bash(1);
            pop();
        goto if_105_0;
        if_105_1:
        line(977);
            line(979);
            push_symbol(base+0);//cmd
            string(L" >");
            add();
            push_symbol(base+1);//runtmp
            add();
            _clp_run(1);
            pop();
        if_105_2:
        if_105_0:;
        line(982);
        push_symbol(base+1);//runtmp
        _clp_memoread(1);
        assign(base+2);//out
        pop();
        line(983);
        push_symbol(base+1);//runtmp
        _clp_ferase(1);
        pop();
        line(985);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_lock(1);
        pop();
        line(986);
        push_symbol(base+2);//out
        _clp_qqout(1);
        pop();
        line(987);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_unlock(1);
        pop();
        line(998);
        line(989);
        string(L"error");
        _clp_file(1);
        if(!flag()) goto if_106_1;
            line(991);
            string(L"cat error");
            _clp_run(1);
            pop();
            line(997);
            push(&TRUE);
            assign(_st_s_dry_ptr());//global
            pop();
        if_106_1:
        if_106_0:;
    if_104_1:
    if_104_0:;
//
stack=base;
push(&NIL);
pop_call();
}

static void _ini_run1_mutex_out(VALUE* base)
{
    _clp_thread_mutex_init(0);
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
    line(1004);
    push_symbol(base+0);//fspec
    string(L"H");
    _clp_directory(2);
    assign(base+1);//d
    pop();
    line(1007);
    line(1005);
    push_symbol(base+1);//d
    _clp_len(1);
    push(&ONE);
    eqeq();
    if(!flag()) goto if_107_1;
        line(1006);
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
    if_107_1:
    if_107_0:;
    line(1008);
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
    line(1014);
    number(10);
    _clp_chr(1);
    assign(base+4);//nl
    pop();
    line(1015);
    string(L"#include");
    assign(base+5);//include
    pop();
    line(1016);
    push_symbol(base+5);//include
    _clp_len(1);
    assign(base+6);//lenincl
    pop();
    line(1017);
    push(&ZERO);
    assign(base+8);//n2
    pop();
    line(1054);
    lab_108_1:
    line(1019);
    push_symbol(base+5);//include
    push_symbol(base+0);//txt
    push_symbol(base+8);//n2
    addnum(1);
    _clp_at(3);
    assign(base+7);//n1
    push(&ZERO);
    gt();
    if(!flag()) goto lab_108_2;
        line(1023);
        line(1021);
        push(&ZERO);
        push_symbol(base+4);//nl
        push_symbol(base+0);//txt
        push_symbol(base+7);//n1
        push_symbol(base+6);//lenincl
        add();
        _clp_at(3);
        assign(base+8);//n2
        eqeq();
        if(!flag()) goto if_109_1;
            line(1022);
            push_symbol(base+0);//txt
            _clp_len(1);
            addnum(1);
            assign(base+8);//n2
            pop();
        if_109_1:
        if_109_0:;
        line(1025);
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
        line(1026);
        push_symbol(base+9);//line
        number(9);
        _clp_chr(1);
        string(L"");
        _clp_strtran(3);
        assign(base+9);//line
        pop();
        line(1027);
        push_symbol(base+9);//line
        _clp_alltrim(1);
        assign(base+9);//line
        pop();
        line(1035);
        line(1029);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"\"");
        eqeq();
        if(!flag()) goto if_110_1;
            line(1030);
            string(L"\"");
            assign(base+10);//delim
            pop();
        goto if_110_0;
        if_110_1:
        line(1031);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"<");
        eqeq();
        if(!flag()) goto if_110_2;
            line(1032);
            string(L">");
            assign(base+10);//delim
            pop();
        goto if_110_0;
        if_110_2:
        line(1033);
            line(1034);
            goto lab_108_1;//loop
        if_110_3:
        if_110_0:;
        line(1039);
        line(1037);
        push(&ZERO);
        push_symbol(base+10);//delim
        push_symbol(base+9);//line
        number(2);
        _clp_at(3);
        assign(base+11);//dpos
        eqeq();
        if(!flag()) goto if_111_1;
            line(1038);
            goto lab_108_1;//loop
        if_111_1:
        if_111_0:;
        line(1041);
        push_symbol(base+9);//line
        number(2);
        push_symbol(base+11);//dpos
        addnum(-2);
        _clp_substr(3);
        assign(base+12);//f
        pop();
        line(1042);
        push_symbol(base+12);//f
        string(L"/");
        _clp_dirsep(0);
        _clp_strtran(3);
        assign(base+12);//f
        pop();
        line(1043);
        push_symbol(base+12);//f
        string(L"\\");
        _clp_dirsep(0);
        _clp_strtran(3);
        assign(base+12);//f
        pop();
        line(1053);
        line(1045);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byrules(4);
        if(!flag()) goto if_112_1;
        goto if_112_0;
        if_112_1:
        line(1048);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byhand(4);
        if(!flag()) goto if_112_2;
        goto if_112_0;
        if_112_2:
        line(1051);
        if_112_3:
        if_112_0:;
    goto lab_108_1;
    lab_108_2:;
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
    line(1063);
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+0);//dirlist
    pop();
    line(1064);
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+1);//liblist
    pop();
    line(1065);
    string(L"BUILD_SHR");
    _clp_getenv(1);
    assign(base+2);//sharing
    pop();
    line(1067);
    string(L"");
    assign(base+5);//txt
    pop();
    line(1068);
    line(1148);
    {
    line(1071);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_113_0:
    push_symbol(base+1);//liblist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_113_2;
        line(1075);
        line(1073);
        push_symbol(base+1);//liblist
        push_symbol(base+3);//n
        idxr();
        assign(base+6);//f0
        _clp_empty(1);
        if(!flag()) goto if_114_1;
            line(1074);
            goto lab_113_1;//loop
        if_114_1:
        if_114_0:;
        line(1087);
        line(1077);
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
        if(!flag()) goto if_115_1;
            line(1078);
            push_symbol(base+6);//f0
            assign(base+7);//f1
            pop();
            line(1079);
            push_symbol(base+6);//f0
            assign(base+8);//f2
            pop();
            line(1080);
            push_symbol(base+6);//f0
            assign(base+9);//f3
            pop();
        goto if_115_0;
        if_115_1:
        line(1081);
            line(1082);
            push_symbol(base+6);//f0
            string(L".lib");
            add();
            assign(base+7);//f1
            pop();
            line(1085);
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
            line(1086);
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
        if_115_2:
        if_115_0:;
        line(1139);
        {
        line(1089);
        push(&ONE);
        int sg=sign();
        push(&ZERO);
        assign(base+4);//i
        lab_116_0:
        push_symbol(base+0);//dirlist
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_116_2;
            line(1103);
            line(1091);
            push_symbol(base+4);//i
            push(&ZERO);
            lteq();
            if(!flag()) goto if_117_1;
                line(1092);
                push_symbol(base+7);//f1
                assign(base+10);//pf1
                pop();
                line(1093);
                push_symbol(base+8);//f2
                assign(base+11);//pf2
                pop();
                line(1094);
                push_symbol(base+9);//f3
                assign(base+12);//pf3
                pop();
            goto if_117_0;
            if_117_1:
            line(1095);
                line(1098);
                line(1096);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_empty(1);
                if(!flag()) goto if_118_1;
                    line(1097);
                    goto lab_116_1;//loop
                if_118_1:
                if_118_0:;
                line(1100);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+7);//f1
                add();
                assign(base+10);//pf1
                pop();
                line(1101);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+8);//f2
                add();
                assign(base+11);//pf2
                pop();
                line(1102);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+9);//f3
                add();
                assign(base+12);//pf3
                pop();
            if_117_2:
            if_117_0:;
            line(1138);
            line(1109);
            string(L"static");
            push_symbol(base+2);//sharing
            ss();
            if(!flag()) goto if_119_1;
                line(1122);
                line(1113);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_120_1;
                    line(1114);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1115);
                    goto lab_116_2;//exit
                goto if_120_0;
                if_120_1:
                line(1116);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_120_2;
                    line(1117);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1118);
                    goto lab_116_2;//exit
                goto if_120_0;
                if_120_2:
                line(1119);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_120_3;
                    line(1120);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1121);
                    goto lab_116_2;//exit
                if_120_3:
                if_120_0:;
            goto if_119_0;
            if_119_1:
            line(1124);
                line(1137);
                line(1128);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_121_1;
                    line(1129);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1130);
                    goto lab_116_2;//exit
                goto if_121_0;
                if_121_1:
                line(1131);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_121_2;
                    line(1132);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1133);
                    goto lab_116_2;//exit
                goto if_121_0;
                if_121_2:
                line(1134);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_121_3;
                    line(1135);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1136);
                    goto lab_116_2;//exit
                if_121_3:
                if_121_0:;
            if_119_2:
            if_119_0:;
        lab_116_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+4);//i
        add();
        assign(base+4);//i
        goto lab_116_0;
        lab_116_2:;
        }
        line(1147);
        line(1141);
        push_symbol(base+4);//i
        push_symbol(base+0);//dirlist
        _clp_len(1);
        gt();
        if(!flag()) goto if_122_1;
            line(1146);
            line(1142);
            push_symbol(base+6);//f0
            push(&ONE);
            number(2);
            slice();
            string(L"-l");
            eqeq();
            if(!flag()) goto if_123_1;
                line(1143);
                push_symbol(base+5);//txt
                push_symbol(base+6);//f0
                string(L" ");
                add();
                add();
                assign(base+5);//txt
                pop();
            goto if_123_0;
            if_123_1:
            line(1144);
                line(1145);
                push_symbol(base+5);//txt
                string(L"-l");
                push_symbol(base+6);//f0
                add();
                string(L" ");
                add();
                add();
                assign(base+5);//txt
                pop();
            if_123_2:
            if_123_0:;
        if_122_1:
        if_122_0:;
    lab_113_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_113_0;
    lab_113_2:;
    }
    line(1150);
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
    line(1155);
    line(1162);
    {
    line(1157);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_124_0:
    push_symbol(base+0);//dirlist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_124_2;
        line(1158);
        push_symbol(base+0);//dirlist
        push_symbol(base+2);//n
        idxr();
        _clp_dirsep(0);
        add();
        push_symbol(base+1);//fnamext
        add();
        assign(base+3);//pathname
        pop();
        line(1161);
        line(1159);
        push_symbol(base+3);//pathname
        _clp_file(1);
        if(!flag()) goto if_125_1;
            line(1160);
            push_symbol(base+3);//pathname
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_125_1:
        if_125_0:;
    lab_124_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_124_0;
    lab_124_2:;
    }
    line(1163);
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
while(stack<base+12)PUSHNIL();
argno=4;
push_call("byrules",base);
//
    line(1174);
    push_symbol(base+0);//fil
    _clp_fname(1);
    assign(base+4);//f
    pop();
    line(1175);
    push_symbol(base+0);//fil
    _clp_fext(1);
    assign(base+5);//e
    pop();
    line(1176);
    line(1177);
    line(1178);
    line(1179);
    push(&FALSE);
    assign(base+11);//result
    pop();
    line(1185);
    line(1181);
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
    if(!flag()) goto if_126_1;
        line(1184);
        push(&FALSE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_126_1:
    if_126_0:;
    line(1212);
    {
    line(1187);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//i
    lab_127_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_127_2;
        line(1211);
        line(1189);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+9);//i
        idxr();
        idxr0(2);
        push_symbol(base+5);//e
        eqeq();
        if(!flag()) goto if_128_1;
            line(1191);
            push_symbol(_st_s_rules_ptr());//global
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            assign(base+8);//e0
            pop();
            line(1210);
            line(1196);
            push(&NIL);
            push_symbol(_st_resource_hash_ptr());//global
            push_symbol(base+4);//f
            push_symbol(base+8);//e0
            add();
            idxr();
            assign(base+7);//r
            neeq();
            if(!flag()) goto if_129_1;
                line(1197);
                push_symbol(base+7);//r
                _clp_fpath(1);
                assign(base+6);//p
                pop();
                line(1198);
                push_symbol(base+1);//dep
                push_symbol(base+6);//p
                push_symbol(base+4);//f
                add();
                push_symbol(base+5);//e
                add();
                _clp_adddep(2);
                pop();
                line(1208);
                line(1199);
                push(&ZERO);
                push_symbol(base+3);//todo
                push_symbol_ref(base+6);//p
                push_symbol_ref(base+4);//f
                push_symbol_ref(base+5);//e
                block(_blk_byrules_0,3);
                _clp_ascan(2);
                assign(base+10);//x
                eqeq();
                if(!flag()) goto if_130_1;
                    line(1200);
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
                goto if_130_0;
                if_130_1:
                line(1201);
                push(&ZERO);
                push_symbol(base+3);//todo
                push_symbol(base+10);//x
                idxr();
                push_symbol_ref(base+6);//p
                push_symbol_ref(base+4);//f
                push_symbol_ref(base+8);//e0
                block(_blk_byrules_1,3);
                _clp_ascan(2);
                eqeq();
                if(!flag()) goto if_130_2;
                    line(1202);
                    push_symbol(base+3);//todo
                    push_symbol(base+10);//x
                    idxr();
                    push_symbol(base+6);//p
                    push_symbol(base+4);//f
                    add();
                    push_symbol(base+8);//e0
                    add();
                    _clp_aadd(2);
                    pop();
                if_130_2:
                if_130_0:;
                line(1209);
                push(&TRUE);
                assign(base+11);//result
                pop();
            if_129_1:
            if_129_0:;
        if_128_1:
        if_128_0:;
    lab_127_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//i
    add();
    assign(base+9);//i
    goto lab_127_0;
    lab_127_2:;
    }
    line(1213);
    push_symbol(base+11);//result
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

static void _blk_byrules_1(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_byrules_1",base);
//
    push_blkarg(base+1);//x
    push_blkenv(env+0);//p
    push_blkenv(env+1);//f
    add();
    push_blkenv(env+2);//e0
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
    line(1224);
    push_symbol(base+2);//dir
    push_symbol(base+0);//f
    _clp_search_file(2);
    assign(base+4);//pn
    pop();
    line(1229);
    line(1226);
    push_symbol(base+4);//pn
    push(&NIL);
    neeq();
    if(!flag()) goto if_131_1;
        line(1227);
        push_symbol(base+1);//dep
        push_symbol(base+4);//pn
        _clp_adddep(2);
        pop();
        line(1228);
        push(&TRUE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_131_1:
    if_131_0:;
    line(1230);
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
    line(1237);
    line(1235);
    push(&ZERO);
    push_symbol(base+0);//dep
    push_symbol_ref(base+1);//x
    block(_blk_adddep_0,1);
    _clp_ascan(2);
    eqeq();
    if(!flag()) goto if_132_1;
        line(1236);
        push_symbol(base+0);//dep
        push_symbol(base+1);//x
        _clp_aadd(2);
        pop();
    if_132_1:
    if_132_0:;
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
    line(1242);
    push_symbol(base+0);//x
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+0);//x
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+2);//ix
    pop();
    line(1243);
    push_symbol(base+1);//y
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+1);//y
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+3);//iy
    pop();
    line(1244);
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
    line(1249);
    line(1254);
    {
    line(1250);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_133_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_133_2;
        line(1253);
        line(1251);
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
        if(!flag()) goto if_134_1;
            line(1252);
            push_symbol(base+2);//n
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_134_1:
        if_134_0:;
    lab_133_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_133_0;
    lab_133_2:;
    }
    line(1255);
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
    line(1260);
    line(1270);
    {
    line(1261);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_135_0:
    push_symbol(base+1);//sep
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_135_2;
        line(1263);
        push_symbol(base+1);//sep
        push_symbol(base+2);//n
        push(&ONE);
        _clp_substr(3);
        assign(base+3);//s
        pop();
        line(1269);
        line(1265);
        push(&ZERO);
        push_symbol(base+3);//s
        push_symbol(base+0);//txt
        _clp_at(2);
        lt();
        if(!flag()) goto if_136_1;
            line(1266);
            goto lab_135_2;//exit
        goto if_136_0;
        if_136_1:
        line(1267);
            line(1268);
            push(&NIL);
            assign(base+3);//s
            pop();
        if_136_2:
        if_136_0:;
    lab_135_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_135_0;
    lab_135_2:;
    }
    line(1271);
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
    line(1280);
    line(1291);
    {
    line(1282);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_137_0:
    push_symbol(base+0);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_137_2;
        line(1290);
        {
        line(1283);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+1);//i
        lab_138_0:
        push_symbol(base+0);//todo
        push_symbol(base+2);//n
        idxr();
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_138_2;
            line(1284);
            push_symbol(base+0);//todo
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+1);//i
            idxr();
            assign(base+3);//x
            pop();
            line(1285);
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
            line(1288);
            line(1286);
            push_symbol(base+3);//x
            number(2);
            _clp_left(2);
            string(L".");
            _clp_dirsep(0);
            add();
            eqeq();
            if(!flag()) goto if_139_1;
                line(1287);
                push_symbol(base+3);//x
                number(3);
                _clp_substr(2);
                assign(base+3);//x
                pop();
            if_139_1:
            if_139_0:;
            line(1289);
            push_symbol(base+3);//x
            push_symbol(base+0);//todo
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+1);//i
            assign2(idxxl());
            pop();
        lab_138_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+1);//i
        add();
        assign(base+1);//i
        goto lab_138_0;
        lab_138_2:;
        }
    lab_137_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_137_0;
    lab_137_2:;
    }
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_verifdep(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("verifdep",base);
//
    line(1297);
    push(&FALSE);
    assign(base+2);//update
    pop();
    line(1298);
    push_symbol(base+1);//depend
    _clp_ftime(1);
    assign(base+3);//tdepend
    pop();
    line(1312);
    line(1300);
    push_symbol(base+3);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_140_1;
        line(1308);
        line(1301);
        push_symbol(_st_s_dry_ptr());//global
        if(!flag()) goto if_141_1;
            line(1302);
            string(L"");
            assign(base+3);//tdepend
            pop();
        goto if_141_0;
        if_141_1:
        line(1303);
            line(1304);
            push_symbol(base+1);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(1305);
            _clp_qout(0);
            pop();
            line(1306);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(1307);
            _clp___quit(0);
            pop();
        if_141_2:
        if_141_0:;
    goto if_140_0;
    if_140_1:
    line(1310);
    push_symbol(base+0);//ttarget
    push_symbol(base+3);//tdepend
    lt();
    if(!flag()) goto if_140_2;
        line(1311);
        push(&TRUE);
        assign(base+2);//update
        pop();
    if_140_2:
    if_140_0:;
    line(1316);
    line(1314);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_142_1;
        line(1315);
        string(L"  ");
        push_symbol(base+1);//depend
        string(L"[");
        push_symbol(base+3);//tdepend
        add();
        string(L"]");
        add();
        push_symbol(base+0);//ttarget
        push_symbol(base+3);//tdepend
        lt();
        if(flag()){
        string(L"UPDATE");
        }else{
        string(L"");
        }
        _clp_qout(4);
        pop();
    if_142_1:
    if_142_0:;
    line(1318);
    push_symbol(base+2);//update
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_bash(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("bash",base);
//
    line(1323);
    push_symbol(base+0);//cmd
    string(L"\\");
    string(L"/");
    _clp_strtran(3);
    assign(base+0);//cmd
    pop();
    line(1326);
    line(1324);
    string(L":/");
    push_symbol(base+0);//cmd
    _clp_at(2);
    number(2);
    eqeq();
    if(!flag()) goto if_143_1;
        line(1325);
        string(L"/");
        push_symbol(base+0);//cmd
        idxr0(1);
        add();
        push_symbol(base+0);//cmd
        number(3);
        push(&NIL);
        slice();
        add();
        assign(base+0);//cmd
        pop();
    if_143_1:
    if_143_0:;
    line(1327);
    number(3);
    string(L"bash.exe");
    string(L"-c");
    string(L"\"");
    push_symbol(base+0);//cmd
    add();
    string(L"\"");
    add();
    _clp_spawn(4);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

