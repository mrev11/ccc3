//input: build.ppo (5.4.0)

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
extern void _clp_endofline(int argno);
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
extern void _clp_memowrit(int argno);
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
        string(L"1.5.1");
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
    push_symbol(base+1);//x
    push_symbol(base+2);//y
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
    line(358);
    lab_35_1:
    line(351);
    push(&ZERO);
    string(L"$${");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_35_2;
        line(352);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(353);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(3);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(354);
        string(L"}");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(355);
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
        line(356);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(357);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_35_1;
    lab_35_2:;
    line(367);
    lab_36_1:
    line(360);
    push(&ZERO);
    string(L"${");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_36_2;
        line(361);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(362);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(2);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(363);
        string(L"}");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(364);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        _clp_getenv(1);
        add();
        assign(base+2);//p
        pop();
        line(365);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(366);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_36_1;
    lab_36_2:;
    line(369);
    push_symbol(base+0);//par
    string(L"\\");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(370);
    push_symbol(base+0);//par
    string(L"/");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(372);
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
    line(377);
    string(nls_text(L"BUILD -xExeNam|-lLibNam -dSrcDir -iIncDir -pLibDir -bLibFil -mMain"));
    _clp_qout(1);
    pop();
    line(378);
    _clp_qout(0);
    pop();
    line(379);
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
    line(385);
    line(422);
    line(387);
    string(L"BUILD_SRC");
    _clp_getenv(1);
    assign(base+0);//srcroot
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_37_1;
        line(391);
        line(389);
        push_symbol(base+0);//srcroot
        push(&ONE);
        _clp_right(2);
        string(L"/\\");
        ss();
        topnot();
        if(!flag()) goto if_38_1;
            line(390);
            push_symbol(base+0);//srcroot
            _clp_dirsep(0);
            add();
            assign(base+0);//srcroot
            pop();
        if_38_1:
        if_38_0:;
        line(395);
        line(393);
        push_symbol(_st_s_srcdir_ptr());//global
        push(&NIL);
        eqeq();
        if(!flag()) goto if_39_1;
            line(394);
            string(L".");
            assign(_st_s_srcdir_ptr());//global
            pop();
        if_39_1:
        if_39_0:;
        line(397);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+1);//d
        pop();
        line(399);
        string(L"");
        assign(_st_s_srcdir_ptr());//global
        pop();
        line(406);
        {
        line(400);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+2);//n
        lab_40_0:
        push_symbol(base+1);//d
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_40_2;
            line(405);
            line(401);
            push_symbol(base+1);//d
            push_symbol(base+2);//n
            idxr();
            push(&ONE);
            _clp_left(2);
            string(L"/\\");
            ss();
            if(!flag()) goto if_41_1;
                line(402);
                push_symbol(_st_s_srcdir_ptr());//global
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                string(L";");
                add();
                add();
                assign(_st_s_srcdir_ptr());//global
                pop();
            goto if_41_0;
            if_41_1:
            line(403);
                line(404);
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
            if_41_2:
            if_41_0:;
        lab_40_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+2);//n
        add();
        assign(base+2);//n
        goto lab_40_0;
        lab_40_2:;
        }
        line(421);
        line(409);
        push_symbol(_st_s_incdir_ptr());//global
        push(&NIL);
        neeq();
        if(!flag()) goto if_42_1;
            line(411);
            push_symbol(_st_s_incdir_ptr());//global
            string(L",;");
            _clp_xsplit(2);
            assign(base+1);//d
            pop();
            line(413);
            string(L"");
            assign(_st_s_incdir_ptr());//global
            pop();
            line(420);
            {
            line(414);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+2);//n
            lab_43_0:
            push_symbol(base+1);//d
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_43_2;
                line(419);
                line(415);
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                push(&ONE);
                _clp_left(2);
                string(L"/\\");
                ss();
                if(!flag()) goto if_44_1;
                    line(416);
                    push_symbol(_st_s_incdir_ptr());//global
                    push_symbol(base+1);//d
                    push_symbol(base+2);//n
                    idxr();
                    string(L";");
                    add();
                    add();
                    assign(_st_s_incdir_ptr());//global
                    pop();
                goto if_44_0;
                if_44_1:
                line(417);
                    line(418);
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
                if_44_2:
                if_44_0:;
            lab_43_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+2);//n
            add();
            assign(base+2);//n
            goto lab_43_0;
            lab_43_2:;
            }
        if_42_1:
        if_42_0:;
    if_37_1:
    if_37_0:;
    line(424);
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
    line(430);
    line(443);
    string(L"");
    assign(base+0);//txt
    pop();
    line(444);
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
    line(445);
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
    line(446);
    push_symbol(base+0);//txt
    string(L"BUILD_INC");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(447);
    push_symbol(base+0);//txt
    string(L"include");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(448);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(449);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(453);
    string(L"BUILD_INC=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(459);
    string(L"");
    assign(base+0);//txt
    pop();
    line(460);
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
    line(461);
    push_symbol(base+0);//txt
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(462);
    push_symbol(base+0);//txt
    string(L"lib");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(463);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(464);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(468);
    string(L"BUILD_LPT=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(474);
    string(L"");
    assign(base+0);//txt
    pop();
    line(475);
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
    line(476);
    push_symbol(base+0);//txt
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(477);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(478);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(479);
    string(L"BUILD_LIB=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(480);
    _clp_search_library(0);
    assign(_st_s_libspec_ptr());//global
    pop();
    line(481);
    string(L"BUILD_LIB=");
    push_symbol(_st_s_libspec_ptr());//global
    add();
    _clp_putenv(1);
    pop();
    line(482);
    push_symbol(_st_s_libspec_ptr());//global
    string(L" ");
    _clp_split(2);
    assign(_st_s_libspec_ptr());//global
    pop();
    line(484);
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
    line(490);
    array(0);
    assign(base+0);//dir
    pop();
    line(491);
    array(0);
    assign(base+1);//obj
    pop();
    line(492);
    array(0);
    assign(base+2);//lib
    pop();
    line(493);
    array(0);
    assign(base+3);//mmd
    pop();
    line(494);
    array(0);
    assign(base+4);//todo
    pop();
    line(496);
    line(501);
    line(499);
    push_symbol(_st_s_main_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_45_1;
        line(500);
        push_symbol(_st_s_main_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+3);//mmd
        pop();
    if_45_1:
    if_45_0:;
    line(508);
    line(504);
    push_symbol(_st_s_srcdir_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_46_1;
        line(505);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+0);//dir
        pop();
    goto if_46_0;
    if_46_1:
    line(506);
        line(507);
        string(L".");
        array(1);
        assign(base+0);//dir
        pop();
    if_46_2:
    if_46_0:;
    line(532);
    {
    line(510);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_47_0:
    push_symbol(base+0);//dir
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_47_2;
        line(512);
        string(L"");
        push_symbol(base+0);//dir
        push_symbol(base+8);//n
        idxr();
        _clp_qqout(2);
        pop();
        line(514);
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
        line(531);
        {
        line(516);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//i
        lab_48_0:
        push_symbol(base+5);//d1
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_48_2;
            line(518);
            push_symbol(base+5);//d1
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            assign(base+6);//f
            pop();
            line(526);
            line(520);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            push_symbol(_st_s_primary_ptr());//global
            ss();
            if(!flag()) goto if_49_1;
                line(525);
                line(521);
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
                if(!flag()) goto if_50_1;
                goto if_50_0;
                if_50_1:
                line(523);
                    line(524);
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
                if_50_2:
                if_50_0:;
            if_49_1:
            if_49_0:;
            line(530);
            line(528);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            push_symbol(_st_s_resource_ptr());//global
            ss();
            if(!flag()) goto if_51_1;
                line(529);
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
            if_51_1:
            if_51_0:;
        lab_48_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//i
        add();
        assign(base+9);//i
        goto lab_48_0;
        lab_48_2:;
        }
    lab_47_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_47_0;
    lab_47_2:;
    }
    line(533);
    _clp_qout(0);
    pop();
    line(569);
    {
    line(538);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_52_0:
    push_symbol(base+1);//obj
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_52_2;
        line(540);
        push_symbol(base+1);//obj
        push_symbol(base+8);//n
        idxr();
        assign(base+6);//f
        pop();
        line(541);
        push_symbol(base+6);//f
        _clp_fname(1);
        assign(base+7);//o
        pop();
        line(542);
        push_symbol(base+6);//f
        _clp_memoread(1);
        assign(base+10);//txt
        pop();
        line(552);
        line(544);
        push(&ZERO);
        push_symbol(base+3);//mmd
        push_symbol_ref(base+7);//o
        block(_blk_build_0,1);
        _clp_ascan(2);
        neeq();
        if(!flag()) goto if_53_1;
        goto if_53_0;
        if_53_1:
        line(546);
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
        if(!flag()) goto if_53_2;
            line(549);
            line(547);
            push_symbol(_st_s_main_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_54_1;
                line(548);
                push_symbol(base+3);//mmd
                push_symbol(base+7);//o
                _clp_aadd(2);
                pop();
            if_54_1:
            if_54_0:;
        goto if_53_0;
        if_53_2:
        line(550);
            line(551);
            push_symbol(base+2);//lib
            push_symbol(base+7);//o
            _clp_aadd(2);
            pop();
        if_53_3:
        if_53_0:;
        line(554);
        push_symbol(base+7);//o
        string(L".obj");
        add();
        push_symbol(base+6);//f
        array(2);
        assign(base+11);//dep
        pop();
        line(566);
        {
        line(555);
        push(&ONE);
        int sg=sign();
        number(2);
        assign(base+9);//i
        lab_55_0:
        push_symbol(base+11);//dep
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_55_2;
            line(564);
            line(556);
            push_symbol(base+9);//i
            number(2);
            eqeq();
            if(!flag()) goto if_56_1;
            goto if_56_0;
            if_56_1:
            line(558);
            push_symbol(base+9);//i
            number(1024);
            gt();
            if(!flag()) goto if_56_2;
                line(559);
                string(L"recursive dependencies:");
                push_symbol(base+11);//dep
                _clp_qout(2);
                pop();
                line(560);
                _clp_qout(0);
                pop();
                line(561);
                _clp___quit(0);
                pop();
            goto if_56_0;
            if_56_2:
            line(562);
                line(563);
                push_symbol(base+11);//dep
                push_symbol(base+9);//i
                idxr();
                _clp_memoread(1);
                assign(base+10);//txt
                pop();
            if_56_3:
            if_56_0:;
            line(565);
            push_symbol(base+10);//txt
            push_symbol(base+11);//dep
            push_symbol(base+0);//dir
            push_symbol(base+4);//todo
            _clp_search_include(4);
            pop();
        lab_55_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//i
        add();
        assign(base+9);//i
        goto lab_55_0;
        lab_55_2:;
        }
        line(568);
        push_symbol(base+4);//todo
        push_symbol(base+11);//dep
        _clp_aadd(2);
        pop();
    lab_52_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_52_0;
    lab_52_2:;
    }
    line(571);
    push_symbol(base+4);//todo
    _clp_normalize(1);
    pop();
    line(573);
    push_symbol(base+4);//todo
    push(&NIL);
    push(&NIL);
    block(_blk_build_1,0);
    _clp_asort(4);
    pop();
    line(585);
    line(577);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_57_1;
        line(578);
        string(L"main:");
        push_symbol(base+3);//mmd
        _clp_qout(2);
        pop();
        line(579);
        string(L"lib :");
        push_symbol(base+2);//lib
        _clp_qout(2);
        pop();
        line(580);
        _clp_qout(0);
        pop();
        line(583);
        {
        line(581);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_58_0:
        push_symbol(base+4);//todo
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_58_2;
            line(582);
            push_symbol(base+4);//todo
            push_symbol(base+8);//n
            idxr();
            _clp_qout(1);
            pop();
        lab_58_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+8);//n
        add();
        assign(base+8);//n
        goto lab_58_0;
        lab_58_2:;
        }
        line(584);
        _clp_qout(0);
        pop();
    if_57_1:
    if_57_0:;
    line(587);
    string(L"error");
    _clp_ferase(1);
    pop();
    line(606);
    {
    line(588);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_59_0:
    push_symbol(base+4);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_59_2;
        line(589);
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_mutex_lock(1);
        pop();
        line(590);
        push_symbol(_st_thread_count_ptr());//global
        push(&ONE);
        add();
        assign(_st_thread_count_ptr());//global
        pop();
        line(593);
        lab_60_1:
        line(591);
        push_symbol(_st_thread_count_ptr());//global
        push_symbol(_st_maxthread_ptr());//global
        gt();
        if(!flag()) goto lab_60_2;
            line(592);
            push_symbol(_st_cond_count_ptr());//global
            push_symbol(_st_mutex_count_ptr());//global
            _clp_thread_cond_wait(2);
            pop();
        goto lab_60_1;
        lab_60_2:;
        line(594);
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_mutex_unlock(1);
        pop();
        line(596);
        push_symbol_ref(base+4);//todo
        block(_blk_build_2,1);
        push_symbol(base+8);//n
        _clp_thread_create_detach(2);
        pop();
        line(605);
        line(598);
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
        if(!flag()) goto if_61_1;
            line(600);
            push_symbol(_st_mutex_count_ptr());//global
            _clp_thread_mutex_lock(1);
            pop();
            line(603);
            lab_62_1:
            line(601);
            push_symbol(_st_thread_count_ptr());//global
            push(&ZERO);
            gt();
            if(!flag()) goto lab_62_2;
                line(602);
                push_symbol(_st_cond_count_ptr());//global
                push_symbol(_st_mutex_count_ptr());//global
                _clp_thread_cond_wait(2);
                pop();
            goto lab_62_1;
            lab_62_2:;
            line(604);
            push_symbol(_st_mutex_count_ptr());//global
            _clp_thread_mutex_unlock(1);
            pop();
        if_61_1:
        if_61_0:;
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
    line(608);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(611);
    lab_63_1:
    line(609);
    push_symbol(_st_thread_count_ptr());//global
    push(&ZERO);
    gt();
    if(!flag()) goto lab_63_2;
        line(610);
        push_symbol(_st_cond_count_ptr());//global
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_cond_wait(2);
        pop();
    goto lab_63_1;
    lab_63_2:;
    line(612);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    line(633);
    line(616);
    push_symbol(_st_s_libnam_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_64_1;
        line(617);
        push_symbol(_st_s_libnam_ptr());//global
        push_symbol(base+2);//lib
        _clp_makelib(2);
        pop();
        line(621);
        line(619);
        push_symbol(_st_s_shared_ptr());//global
        push(&TRUE);
        eqeq();
        if(!flag()) goto if_65_1;
            line(620);
            push_symbol(_st_s_libnam_ptr());//global
            push_symbol(base+2);//lib
            _clp_makeso(2);
            pop();
        if_65_1:
        if_65_0:;
        line(626);
        block(_blk_build_3,0);
        push_symbol(base+3);//mmd
        _clp_manage_threads(2);
        pop();
    goto if_64_0;
    if_64_1:
    line(628);
        line(632);
        push_symbol_ref(base+2);//lib
        block(_blk_build_4,1);
        push_symbol(base+3);//mmd
        _clp_manage_threads(2);
        pop();
    if_64_2:
    if_64_0:;
    line(635);
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
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_build_3",base);
//
    push_symbol(base+1);//x
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
    push_symbol(base+1);//x
    push_symbol(env+0);//lib
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
    line(641);
    array(0);
    assign(base+2);//thread
    pop();
    line(652);
    {
    line(642);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_66_0:
    push_symbol(base+1);//a
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_66_2;
        line(643);
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_mutex_lock(1);
        pop();
        line(644);
        push_symbol(_st_thread_count_ptr());//global
        push(&ONE);
        add();
        assign(_st_thread_count_ptr());//global
        pop();
        line(647);
        lab_67_1:
        line(645);
        push_symbol(_st_thread_count_ptr());//global
        push_symbol(_st_maxthread_ptr());//global
        gt();
        if(!flag()) goto lab_67_2;
            line(646);
            push_symbol(_st_cond_count_ptr());//global
            push_symbol(_st_mutex_count_ptr());//global
            _clp_thread_cond_wait(2);
            pop();
        goto lab_67_1;
        lab_67_2:;
        line(648);
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_mutex_unlock(1);
        pop();
        line(650);
        push_symbol_ref(base+0);//blk
        push_symbol_ref(base+1);//a
        block(_blk_manage_threads_0,2);
        push_symbol(base+4);//n
        _clp_thread_create(2);
        assign(base+3);//th
        pop();
        line(651);
        push_symbol(base+2);//thread
        push_symbol(base+3);//th
        _clp_aadd(2);
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
    line(655);
    {
    line(653);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_68_0:
    push_symbol(base+2);//thread
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_68_2;
        line(654);
        push_symbol(base+2);//thread
        push_symbol(base+4);//n
        idxr();
        _clp_thread_join(1);
        pop();
    lab_68_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_68_0;
    lab_68_2:;
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
    push_symbol(env+0);//blk
    push_symbol(env+1);//a
    push_symbol(base+1);//i
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
    line(661);
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
    line(662);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(663);
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
    line(664);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(671);
    line(666);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_69_1;
        line(667);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(668);
        _clp_qout(0);
        pop();
        line(669);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(670);
        _clp___quit(0);
        pop();
    if_69_1:
    if_69_0:;
    line(673);
    push_symbol(base+7);//torun
    string(L" lib");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(675);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(678);
    line(676);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_70_1;
        line(677);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_70_1:
    if_70_0:;
    line(682);
    line(680);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_71_1;
        line(681);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_71_1:
    if_71_0:;
    line(690);
    {
    line(684);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_72_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_72_2;
        line(686);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(687);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+4);//depend
        add();
        add();
        assign(base+7);//torun
        pop();
        line(688);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(689);
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
    lab_72_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_72_0;
    lab_72_2:;
    }
    line(694);
    line(692);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_73_1;
        line(693);
        _clp_qout(0);
        pop();
    if_73_1:
    if_73_0:;
    line(698);
    line(696);
    push_symbol(base+6);//update
    if(!flag()) goto if_74_1;
        line(697);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_74_1:
    if_74_0:;
    line(700);
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
    line(706);
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
    line(707);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(708);
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
    line(709);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(710);
    line(717);
    line(712);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_75_1;
        line(713);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(714);
        _clp_qout(0);
        pop();
        line(715);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(716);
        _clp___quit(0);
        pop();
    if_75_1:
    if_75_0:;
    line(719);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(721);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(724);
    line(722);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_76_1;
        line(723);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_76_1:
    if_76_0:;
    line(728);
    line(726);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_77_1;
        line(727);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_77_1:
    if_77_0:;
    line(735);
    {
    line(730);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_78_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_78_2;
        line(732);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(733);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(734);
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
    lab_78_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_78_0;
    lab_78_2:;
    }
    line(739);
    line(737);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_79_1;
        line(738);
        _clp_qout(0);
        pop();
    if_79_1:
    if_79_0:;
    line(767);
    line(741);
    push_symbol(base+6);//update
    if(!flag()) goto if_80_1;
        line(752);
        string(L"");
        assign(base+10);//objlist
        pop();
        line(761);
        {
        line(753);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_81_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_81_2;
            line(760);
            line(754);
            string(L"objmng");
            push_symbol(base+8);//objdir
            ss();
            if(!flag()) goto if_82_1;
                line(755);
                push_symbol(base+10);//objlist
                push_symbol(base+1);//object
                push_symbol(base+9);//n
                idxr();
                string(L".obj");
                add();
                _clp_endofline(0);
                add();
                add();
                assign(base+10);//objlist
                pop();
            goto if_82_0;
            if_82_1:
            line(756);
            string(L"objmsc");
            push_symbol(base+8);//objdir
            ss();
            if(!flag()) goto if_82_2;
                line(757);
                push_symbol(base+10);//objlist
                push_symbol(base+1);//object
                push_symbol(base+9);//n
                idxr();
                string(L".obj");
                add();
                _clp_endofline(0);
                add();
                add();
                assign(base+10);//objlist
                pop();
            goto if_82_0;
            if_82_2:
            line(758);
            string(L"objbor");
            push_symbol(base+8);//objdir
            ss();
            if(!flag()) goto if_82_3;
                line(759);
                push_symbol(base+10);//objlist
                string(L"+");
                push_symbol(base+1);//object
                push_symbol(base+9);//n
                idxr();
                add();
                string(L".obj &");
                add();
                _clp_endofline(0);
                add();
                add();
                assign(base+10);//objlist
                pop();
            if_82_3:
            if_82_0:;
        lab_81_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_81_0;
        lab_81_2:;
        }
        line(762);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        string(L"objects");
        add();
        push_symbol(base+10);//objlist
        _clp_memowrit(2);
        pop();
        line(763);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        string(L"objects-");
        add();
        push_symbol(base+0);//libnam
        add();
        push_symbol(base+10);//objlist
        _clp_memowrit(2);
        pop();
        line(766);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_80_1:
    if_80_0:;
    line(769);
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
    line(775);
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
    line(776);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(777);
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
    line(778);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(779);
    line(786);
    line(781);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_83_1;
        line(782);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(783);
        _clp_qout(0);
        pop();
        line(784);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(785);
        _clp___quit(0);
        pop();
    if_83_1:
    if_83_0:;
    line(788);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(791);
    line(789);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_84_1;
        line(790);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_84_1:
    if_84_0:;
    line(795);
    line(793);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_85_1;
        line(794);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_85_1:
    if_85_0:;
    line(807);
    {
    line(797);
    push(&ONE);
    int sg=sign();
    push(&ZERO);
    assign(base+9);//n
    lab_86_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_86_2;
        line(803);
        line(799);
        push_symbol(base+9);//n
        push(&ZERO);
        eqeq();
        if(!flag()) goto if_87_1;
            line(800);
            push_symbol(base+0);//exenam
            assign(base+4);//depend
            pop();
        goto if_87_0;
        if_87_1:
        line(801);
            line(802);
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
        if_87_2:
        if_87_0:;
        line(805);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(806);
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
    lab_86_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_86_0;
    lab_86_2:;
    }
    line(814);
    {
    line(809);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_88_0:
    push_symbol(_st_s_libspec_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_88_2;
        line(813);
        line(810);
        push_symbol(_st_s_libspec_ptr());//global
        push_symbol(base+9);//n
        idxr();
        number(4);
        _clp_right(2);
        string(L".lib");
        eqeq();
        if(!flag()) goto if_89_1;
            line(811);
            push_symbol(_st_s_libspec_ptr());//global
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
            line(812);
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
        if_89_1:
        if_89_0:;
    lab_88_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_88_0;
    lab_88_2:;
    }
    line(818);
    line(816);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_90_1;
        line(817);
        _clp_qout(0);
        pop();
    if_90_1:
    if_90_0:;
    line(852);
    line(820);
    push_symbol(base+6);//update
    if(!flag()) goto if_91_1;
        line(821);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+0);//exenam
        add();
        add();
        assign(base+7);//torun
        pop();
        line(832);
        string(L"");
        assign(base+10);//objlist
        pop();
        line(846);
        {
        line(833);
        push(&ONE);
        int sg=sign();
        push(&ZERO);
        assign(base+9);//n
        lab_92_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_92_2;
            line(835);
            push_symbol(base+8);//objdir
            _clp_dirsep(0);
            add();
            assign(base+11);//xobj
            pop();
            line(836);
            push_symbol(base+11);//xobj
            push_symbol(base+9);//n
            push(&ZERO);
            eqeq();
            if(flag()){
            push_symbol(base+0);//exenam
            }else{
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            }
            add();
            assign(base+11);//xobj
            pop();
            line(837);
            push_symbol(base+11);//xobj
            string(L".obj");
            add();
            assign(base+11);//xobj
            pop();
            line(845);
            line(839);
            string(L"objmng");
            push_symbol(base+8);//objdir
            ss();
            if(!flag()) goto if_93_1;
                line(840);
                push_symbol(base+10);//objlist
                push_symbol(base+11);//xobj
                _clp_endofline(0);
                add();
                add();
                assign(base+10);//objlist
                pop();
            goto if_93_0;
            if_93_1:
            line(841);
            string(L"objmsc");
            push_symbol(base+8);//objdir
            ss();
            if(!flag()) goto if_93_2;
                line(842);
                push_symbol(base+10);//objlist
                push_symbol(base+11);//xobj
                _clp_endofline(0);
                add();
                add();
                assign(base+10);//objlist
                pop();
            goto if_93_0;
            if_93_2:
            line(843);
            string(L"objbor");
            push_symbol(base+8);//objdir
            ss();
            if(!flag()) goto if_93_3;
                line(844);
                push_symbol(base+10);//objlist
                push_symbol(base+11);//xobj
                push_symbol(base+9);//n
                push_symbol(base+1);//object
                _clp_len(1);
                lt();
                if(flag()){
                string(L" + ");
                }else{
                string(L"");
                }
                add();
                _clp_endofline(0);
                add();
                add();
                assign(base+10);//objlist
                pop();
            if_93_3:
            if_93_0:;
        lab_92_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_92_0;
        lab_92_2:;
        }
        line(847);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        string(L"objects");
        add();
        push_symbol(base+10);//objlist
        _clp_memowrit(2);
        pop();
        line(848);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        string(L"objects-");
        add();
        push_symbol(base+0);//exenam
        add();
        push_symbol(base+10);//objlist
        _clp_memowrit(2);
        pop();
        line(851);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_91_1:
    if_91_0:;
    line(854);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(855);
    push_symbol(_st_thread_count_ptr());//global
    push(&ONE);
    sub();
    assign(_st_thread_count_ptr());//global
    pop();
    line(856);
    push_symbol(_st_cond_count_ptr());//global
    _clp_thread_cond_signal(1);
    pop();
    line(857);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    line(859);
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
    line(865);
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
    line(866);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(867);
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
    line(868);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(875);
    line(870);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_94_1;
        line(871);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(872);
        _clp_qout(0);
        pop();
        line(873);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(874);
        _clp___quit(0);
        pop();
    if_94_1:
    if_94_0:;
    line(877);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(880);
    line(878);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_95_1;
        line(879);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_95_1:
    if_95_0:;
    line(884);
    line(882);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_96_1;
        line(883);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_96_1:
    if_96_0:;
    line(887);
    push_symbol(base+0);//mmod
    assign(base+4);//depend
    pop();
    line(888);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(889);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".obj");
    add();
    assign(base+4);//depend
    pop();
    line(890);
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
    line(892);
    push_symbol(base+1);//libnam
    assign(base+4);//depend
    pop();
    line(893);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(894);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".lib");
    add();
    assign(base+4);//depend
    pop();
    line(895);
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
    line(902);
    {
    line(897);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_97_0:
    push_symbol(_st_s_libspec_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_97_2;
        line(901);
        line(898);
        push_symbol(_st_s_libspec_ptr());//global
        push_symbol(base+9);//n
        idxr();
        number(4);
        _clp_right(2);
        string(L".lib");
        eqeq();
        if(!flag()) goto if_98_1;
            line(899);
            push_symbol(_st_s_libspec_ptr());//global
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
            line(900);
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
        if_98_1:
        if_98_0:;
    lab_97_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_97_0;
    lab_97_2:;
    }
    line(906);
    line(904);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_99_1;
        line(905);
        _clp_qout(0);
        pop();
    if_99_1:
    if_99_0:;
    line(910);
    line(908);
    push_symbol(base+6);//update
    if(!flag()) goto if_100_1;
        line(909);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_100_1:
    if_100_0:;
    line(912);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(913);
    push_symbol(_st_thread_count_ptr());//global
    push(&ONE);
    sub();
    assign(_st_thread_count_ptr());//global
    pop();
    line(914);
    push_symbol(_st_cond_count_ptr());//global
    _clp_thread_cond_signal(1);
    pop();
    line(915);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    line(917);
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
    line(923);
    push_symbol(base+0);//deplist
    idxr0(1);
    assign(base+1);//target
    pop();
    line(924);
    push_symbol(base+0);//deplist
    idxr0(2);
    assign(base+2);//depend
    pop();
    line(925);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+3);//objdir
    pop();
    line(926);
    line(927);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(928);
    line(932);
    line(930);
    push_symbol(base+1);//target
    _clp_fext(1);
    string(L".obj");
    eqeq();
    if(!flag()) goto if_101_1;
        line(931);
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
    if_101_1:
    if_101_0:;
    line(934);
    push_symbol(base+1);//target
    _clp_ftime(1);
    assign(base+4);//ttarget
    pop();
    line(937);
    line(935);
    push_symbol(base+4);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_102_1;
        line(936);
        string(L"");
        assign(base+4);//ttarget
        pop();
    if_102_1:
    if_102_0:;
    line(941);
    line(939);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_103_1;
        line(940);
        push_symbol(base+1);//target
        string(L"[");
        push_symbol(base+4);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_103_1:
    if_103_0:;
    line(946);
    {
    line(943);
    push(&ONE);
    int sg=sign();
    number(2);
    assign(base+8);//n
    lab_104_0:
    push_symbol(base+0);//deplist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_104_2;
        line(944);
        push_symbol(base+0);//deplist
        push_symbol(base+8);//n
        idxr();
        assign(base+2);//depend
        pop();
        line(945);
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
    lab_104_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_104_0;
    lab_104_2:;
    }
    line(950);
    line(948);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_105_1;
        line(949);
        _clp_qout(0);
        pop();
    if_105_1:
    if_105_0:;
    line(969);
    line(952);
    push_symbol(base+6);//update
    if(!flag()) goto if_106_1;
        line(954);
        string(L"BUILD_BAT");
        _clp_getenv(1);
        _clp_dirsep(0);
        add();
        assign(base+7);//torun
        pop();
        line(955);
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
        line(956);
        push_symbol(base+7);//torun
        push_symbol(_st_s_batext_ptr());//global
        add();
        assign(base+7);//torun
        pop();
        line(963);
        line(958);
        push_symbol(base+7);//torun
        _clp_file(1);
        topnot();
        if(!flag()) goto if_107_1;
            line(959);
            string(L"[");
            push_symbol(base+7);//torun
            add();
            string(L"]");
            add();
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(960);
            _clp_qout(0);
            pop();
            line(961);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(962);
            _clp___quit(0);
            pop();
        if_107_1:
        if_107_0:;
        line(965);
        push_symbol(base+0);//deplist
        idxr0(1);
        _clp_fname(1);
        assign(base+9);//p1
        pop();
        line(966);
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
        line(968);
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
    if_106_1:
    if_106_0:;
    line(971);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(972);
    push_symbol(_st_thread_count_ptr());//global
    push(&ONE);
    sub();
    assign(_st_thread_count_ptr());//global
    pop();
    line(973);
    push_symbol(_st_cond_count_ptr());//global
    _clp_thread_cond_signal(1);
    pop();
    line(974);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    line(976);
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
    line(983);
    static stvarloc _st_mutex_out(_ini_run1_mutex_out,base);
    line(984);
    static stvar _st_count((double)0);
    line(985);
    line(1018);
    line(987);
    push_symbol(_st_s_dry_ptr());//global
    topnot();
    if(!flag()) goto if_108_1;
        line(989);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_lock(1);
        pop();
        line(990);
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
        line(991);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_unlock(1);
        pop();
        line(999);
        line(993);
        string(L"msys2");
        string(L"BUILD_BAT");
        _clp_getenv(1);
        ss();
        if(!flag()) goto if_109_1;
            line(995);
            push_symbol(base+0);//cmd
            string(L" >");
            add();
            push_symbol(base+1);//runtmp
            add();
            _clp_bash(1);
            pop();
        goto if_109_0;
        if_109_1:
        line(996);
            line(998);
            push_symbol(base+0);//cmd
            string(L" >");
            add();
            push_symbol(base+1);//runtmp
            add();
            _clp_run(1);
            pop();
        if_109_2:
        if_109_0:;
        line(1001);
        push_symbol(base+1);//runtmp
        _clp_memoread(1);
        assign(base+2);//out
        pop();
        line(1002);
        push_symbol(base+1);//runtmp
        _clp_ferase(1);
        pop();
        line(1004);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_lock(1);
        pop();
        line(1005);
        push_symbol(base+2);//out
        _clp_qqout(1);
        pop();
        line(1006);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_unlock(1);
        pop();
        line(1017);
        line(1008);
        string(L"error");
        _clp_file(1);
        if(!flag()) goto if_110_1;
            line(1012);
            string(L"type error");
            _clp_run(1);
            pop();
            line(1016);
            push(&TRUE);
            assign(_st_s_dry_ptr());//global
            pop();
        if_110_1:
        if_110_0:;
    if_108_1:
    if_108_0:;
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
    line(1023);
    push_symbol(base+0);//fspec
    string(L"H");
    _clp_directory(2);
    assign(base+1);//d
    pop();
    line(1026);
    line(1024);
    push_symbol(base+1);//d
    _clp_len(1);
    push(&ONE);
    eqeq();
    if(!flag()) goto if_111_1;
        line(1025);
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
    if_111_1:
    if_111_0:;
    line(1027);
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
    line(1033);
    number(10);
    _clp_chr(1);
    assign(base+4);//nl
    pop();
    line(1034);
    string(L"#include");
    assign(base+5);//include
    pop();
    line(1035);
    push_symbol(base+5);//include
    _clp_len(1);
    assign(base+6);//lenincl
    pop();
    line(1036);
    push(&ZERO);
    assign(base+8);//n2
    pop();
    line(1073);
    lab_112_1:
    line(1038);
    push_symbol(base+5);//include
    push_symbol(base+0);//txt
    push_symbol(base+8);//n2
    addnum(1);
    _clp_at(3);
    assign(base+7);//n1
    push(&ZERO);
    gt();
    if(!flag()) goto lab_112_2;
        line(1042);
        line(1040);
        push(&ZERO);
        push_symbol(base+4);//nl
        push_symbol(base+0);//txt
        push_symbol(base+7);//n1
        push_symbol(base+6);//lenincl
        add();
        _clp_at(3);
        assign(base+8);//n2
        eqeq();
        if(!flag()) goto if_113_1;
            line(1041);
            push_symbol(base+0);//txt
            _clp_len(1);
            addnum(1);
            assign(base+8);//n2
            pop();
        if_113_1:
        if_113_0:;
        line(1044);
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
        line(1045);
        push_symbol(base+9);//line
        number(9);
        _clp_chr(1);
        string(L"");
        _clp_strtran(3);
        assign(base+9);//line
        pop();
        line(1046);
        push_symbol(base+9);//line
        _clp_alltrim(1);
        assign(base+9);//line
        pop();
        line(1054);
        line(1048);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"\"");
        eqeq();
        if(!flag()) goto if_114_1;
            line(1049);
            string(L"\"");
            assign(base+10);//delim
            pop();
        goto if_114_0;
        if_114_1:
        line(1050);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"<");
        eqeq();
        if(!flag()) goto if_114_2;
            line(1051);
            string(L">");
            assign(base+10);//delim
            pop();
        goto if_114_0;
        if_114_2:
        line(1052);
            line(1053);
            goto lab_112_1;//loop
        if_114_3:
        if_114_0:;
        line(1058);
        line(1056);
        push(&ZERO);
        push_symbol(base+10);//delim
        push_symbol(base+9);//line
        number(2);
        _clp_at(3);
        assign(base+11);//dpos
        eqeq();
        if(!flag()) goto if_115_1;
            line(1057);
            goto lab_112_1;//loop
        if_115_1:
        if_115_0:;
        line(1060);
        push_symbol(base+9);//line
        number(2);
        push_symbol(base+11);//dpos
        addnum(-2);
        _clp_substr(3);
        assign(base+12);//f
        pop();
        line(1061);
        push_symbol(base+12);//f
        string(L"/");
        _clp_dirsep(0);
        _clp_strtran(3);
        assign(base+12);//f
        pop();
        line(1062);
        push_symbol(base+12);//f
        string(L"\\");
        _clp_dirsep(0);
        _clp_strtran(3);
        assign(base+12);//f
        pop();
        line(1072);
        line(1064);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byrules(4);
        if(!flag()) goto if_116_1;
        goto if_116_0;
        if_116_1:
        line(1067);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byhand(4);
        if(!flag()) goto if_116_2;
        goto if_116_0;
        if_116_2:
        line(1070);
        if_116_3:
        if_116_0:;
    goto lab_112_1;
    lab_112_2:;
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
    line(1082);
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+0);//dirlist
    pop();
    line(1083);
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+1);//liblist
    pop();
    line(1084);
    string(L"BUILD_SHR");
    _clp_getenv(1);
    assign(base+2);//sharing
    pop();
    line(1086);
    string(L"");
    assign(base+5);//txt
    pop();
    line(1087);
    line(1167);
    {
    line(1090);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_117_0:
    push_symbol(base+1);//liblist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_117_2;
        line(1094);
        line(1092);
        push_symbol(base+1);//liblist
        push_symbol(base+3);//n
        idxr();
        assign(base+6);//f0
        _clp_empty(1);
        if(!flag()) goto if_118_1;
            line(1093);
            goto lab_117_1;//loop
        if_118_1:
        if_118_0:;
        line(1106);
        line(1096);
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
        if(!flag()) goto if_119_1;
            line(1097);
            push_symbol(base+6);//f0
            assign(base+7);//f1
            pop();
            line(1098);
            push_symbol(base+6);//f0
            assign(base+8);//f2
            pop();
            line(1099);
            push_symbol(base+6);//f0
            assign(base+9);//f3
            pop();
        goto if_119_0;
        if_119_1:
        line(1100);
            line(1101);
            push_symbol(base+6);//f0
            string(L".lib");
            add();
            assign(base+7);//f1
            pop();
            line(1104);
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
            line(1105);
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
        if_119_2:
        if_119_0:;
        line(1158);
        {
        line(1108);
        push(&ONE);
        int sg=sign();
        push(&ZERO);
        assign(base+4);//i
        lab_120_0:
        push_symbol(base+0);//dirlist
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_120_2;
            line(1122);
            line(1110);
            push_symbol(base+4);//i
            push(&ZERO);
            lteq();
            if(!flag()) goto if_121_1;
                line(1111);
                push_symbol(base+7);//f1
                assign(base+10);//pf1
                pop();
                line(1112);
                push_symbol(base+8);//f2
                assign(base+11);//pf2
                pop();
                line(1113);
                push_symbol(base+9);//f3
                assign(base+12);//pf3
                pop();
            goto if_121_0;
            if_121_1:
            line(1114);
                line(1117);
                line(1115);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_empty(1);
                if(!flag()) goto if_122_1;
                    line(1116);
                    goto lab_120_1;//loop
                if_122_1:
                if_122_0:;
                line(1119);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+7);//f1
                add();
                assign(base+10);//pf1
                pop();
                line(1120);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+8);//f2
                add();
                assign(base+11);//pf2
                pop();
                line(1121);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+9);//f3
                add();
                assign(base+12);//pf3
                pop();
            if_121_2:
            if_121_0:;
            line(1157);
            line(1128);
            string(L"static");
            push_symbol(base+2);//sharing
            ss();
            if(!flag()) goto if_123_1;
                line(1141);
                line(1132);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_124_1;
                    line(1133);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1134);
                    goto lab_120_2;//exit
                goto if_124_0;
                if_124_1:
                line(1135);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_124_2;
                    line(1136);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1137);
                    goto lab_120_2;//exit
                goto if_124_0;
                if_124_2:
                line(1138);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_124_3;
                    line(1139);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1140);
                    goto lab_120_2;//exit
                if_124_3:
                if_124_0:;
            goto if_123_0;
            if_123_1:
            line(1143);
                line(1156);
                line(1147);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_125_1;
                    line(1148);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1149);
                    goto lab_120_2;//exit
                goto if_125_0;
                if_125_1:
                line(1150);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_125_2;
                    line(1151);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1152);
                    goto lab_120_2;//exit
                goto if_125_0;
                if_125_2:
                line(1153);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_125_3;
                    line(1154);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1155);
                    goto lab_120_2;//exit
                if_125_3:
                if_125_0:;
            if_123_2:
            if_123_0:;
        lab_120_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+4);//i
        add();
        assign(base+4);//i
        goto lab_120_0;
        lab_120_2:;
        }
        line(1166);
        line(1160);
        push_symbol(base+4);//i
        push_symbol(base+0);//dirlist
        _clp_len(1);
        gt();
        if(!flag()) goto if_126_1;
            line(1165);
            line(1161);
            push_symbol(base+6);//f0
            push(&ONE);
            number(2);
            slice();
            string(L"-l");
            eqeq();
            if(!flag()) goto if_127_1;
                line(1162);
                push_symbol(base+5);//txt
                push_symbol(base+6);//f0
                string(L" ");
                add();
                add();
                assign(base+5);//txt
                pop();
            goto if_127_0;
            if_127_1:
            line(1163);
                line(1164);
                push_symbol(base+5);//txt
                string(L"-l");
                push_symbol(base+6);//f0
                add();
                string(L" ");
                add();
                add();
                assign(base+5);//txt
                pop();
            if_127_2:
            if_127_0:;
        if_126_1:
        if_126_0:;
    lab_117_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_117_0;
    lab_117_2:;
    }
    line(1169);
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
    line(1174);
    line(1181);
    {
    line(1176);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_128_0:
    push_symbol(base+0);//dirlist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_128_2;
        line(1177);
        push_symbol(base+0);//dirlist
        push_symbol(base+2);//n
        idxr();
        _clp_dirsep(0);
        add();
        push_symbol(base+1);//fnamext
        add();
        assign(base+3);//pathname
        pop();
        line(1180);
        line(1178);
        push_symbol(base+3);//pathname
        _clp_file(1);
        if(!flag()) goto if_129_1;
            line(1179);
            push_symbol(base+3);//pathname
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_129_1:
        if_129_0:;
    lab_128_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_128_0;
    lab_128_2:;
    }
    line(1182);
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
    line(1193);
    push_symbol(base+0);//fil
    _clp_fname(1);
    assign(base+4);//f
    pop();
    line(1194);
    push_symbol(base+0);//fil
    _clp_fext(1);
    assign(base+5);//e
    pop();
    line(1195);
    line(1196);
    line(1197);
    line(1198);
    push(&FALSE);
    assign(base+11);//result
    pop();
    line(1204);
    line(1200);
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
    if(!flag()) goto if_130_1;
        line(1203);
        push(&FALSE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_130_1:
    if_130_0:;
    line(1231);
    {
    line(1206);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//i
    lab_131_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_131_2;
        line(1230);
        line(1208);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+9);//i
        idxr();
        idxr0(2);
        push_symbol(base+5);//e
        eqeq();
        if(!flag()) goto if_132_1;
            line(1210);
            push_symbol(_st_s_rules_ptr());//global
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            assign(base+8);//e0
            pop();
            line(1229);
            line(1215);
            push(&NIL);
            push_symbol(_st_resource_hash_ptr());//global
            push_symbol(base+4);//f
            push_symbol(base+8);//e0
            add();
            idxr();
            assign(base+7);//r
            neeq();
            if(!flag()) goto if_133_1;
                line(1216);
                push_symbol(base+7);//r
                _clp_fpath(1);
                assign(base+6);//p
                pop();
                line(1217);
                push_symbol(base+1);//dep
                push_symbol(base+6);//p
                push_symbol(base+4);//f
                add();
                push_symbol(base+5);//e
                add();
                _clp_adddep(2);
                pop();
                line(1227);
                line(1218);
                push(&ZERO);
                push_symbol(base+3);//todo
                push_symbol_ref(base+6);//p
                push_symbol_ref(base+4);//f
                push_symbol_ref(base+5);//e
                block(_blk_byrules_0,3);
                _clp_ascan(2);
                assign(base+10);//x
                eqeq();
                if(!flag()) goto if_134_1;
                    line(1219);
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
                goto if_134_0;
                if_134_1:
                line(1220);
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
                if(!flag()) goto if_134_2;
                    line(1221);
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
                if_134_2:
                if_134_0:;
                line(1228);
                push(&TRUE);
                assign(base+11);//result
                pop();
            if_133_1:
            if_133_0:;
        if_132_1:
        if_132_0:;
    lab_131_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//i
    add();
    assign(base+9);//i
    goto lab_131_0;
    lab_131_2:;
    }
    line(1232);
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
    push_symbol(base+1);//x
    idxr0(1);
    push_symbol(env+0);//p
    push_symbol(env+1);//f
    add();
    push_symbol(env+2);//e
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
    push_symbol(base+1);//x
    push_symbol(env+0);//p
    push_symbol(env+1);//f
    add();
    push_symbol(env+2);//e0
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
    line(1243);
    push_symbol(base+2);//dir
    push_symbol(base+0);//f
    _clp_search_file(2);
    assign(base+4);//pn
    pop();
    line(1248);
    line(1245);
    push_symbol(base+4);//pn
    push(&NIL);
    neeq();
    if(!flag()) goto if_135_1;
        line(1246);
        push_symbol(base+1);//dep
        push_symbol(base+4);//pn
        _clp_adddep(2);
        pop();
        line(1247);
        push(&TRUE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_135_1:
    if_135_0:;
    line(1249);
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
    line(1256);
    line(1254);
    push(&ZERO);
    push_symbol(base+0);//dep
    push_symbol_ref(base+1);//x
    block(_blk_adddep_0,1);
    _clp_ascan(2);
    eqeq();
    if(!flag()) goto if_136_1;
        line(1255);
        push_symbol(base+0);//dep
        push_symbol(base+1);//x
        _clp_aadd(2);
        pop();
    if_136_1:
    if_136_0:;
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
    push_symbol(base+1);//d
    push_symbol(env+0);//x
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
    line(1261);
    push_symbol(base+0);//x
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+0);//x
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+2);//ix
    pop();
    line(1262);
    push_symbol(base+1);//y
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+1);//y
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+3);//iy
    pop();
    line(1263);
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
    line(1268);
    line(1273);
    {
    line(1269);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_137_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_137_2;
        line(1272);
        line(1270);
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
        if(!flag()) goto if_138_1;
            line(1271);
            push_symbol(base+2);//n
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_138_1:
        if_138_0:;
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
    line(1274);
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
    line(1279);
    line(1289);
    {
    line(1280);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_139_0:
    push_symbol(base+1);//sep
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_139_2;
        line(1282);
        push_symbol(base+1);//sep
        push_symbol(base+2);//n
        push(&ONE);
        _clp_substr(3);
        assign(base+3);//s
        pop();
        line(1288);
        line(1284);
        push(&ZERO);
        push_symbol(base+3);//s
        push_symbol(base+0);//txt
        _clp_at(2);
        lt();
        if(!flag()) goto if_140_1;
            line(1285);
            goto lab_139_2;//exit
        goto if_140_0;
        if_140_1:
        line(1286);
            line(1287);
            push(&NIL);
            assign(base+3);//s
            pop();
        if_140_2:
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
    line(1290);
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
    line(1299);
    line(1310);
    {
    line(1301);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_141_0:
    push_symbol(base+0);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_141_2;
        line(1309);
        {
        line(1302);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+1);//i
        lab_142_0:
        push_symbol(base+0);//todo
        push_symbol(base+2);//n
        idxr();
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_142_2;
            line(1303);
            push_symbol(base+0);//todo
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+1);//i
            idxr();
            assign(base+3);//x
            pop();
            line(1304);
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
            line(1307);
            line(1305);
            push_symbol(base+3);//x
            number(2);
            _clp_left(2);
            string(L".");
            _clp_dirsep(0);
            add();
            eqeq();
            if(!flag()) goto if_143_1;
                line(1306);
                push_symbol(base+3);//x
                number(3);
                _clp_substr(2);
                assign(base+3);//x
                pop();
            if_143_1:
            if_143_0:;
            line(1308);
            push_symbol(base+3);//x
            push_symbol(base+0);//todo
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+1);//i
            assign2(idxxl());
            pop();
        lab_142_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+1);//i
        add();
        assign(base+1);//i
        goto lab_142_0;
        lab_142_2:;
        }
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
    line(1316);
    push(&FALSE);
    assign(base+2);//update
    pop();
    line(1317);
    push_symbol(base+1);//depend
    _clp_ftime(1);
    assign(base+3);//tdepend
    pop();
    line(1331);
    line(1319);
    push_symbol(base+3);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_144_1;
        line(1327);
        line(1320);
        push_symbol(_st_s_dry_ptr());//global
        if(!flag()) goto if_145_1;
            line(1321);
            string(L"");
            assign(base+3);//tdepend
            pop();
        goto if_145_0;
        if_145_1:
        line(1322);
            line(1323);
            push_symbol(base+1);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(1324);
            _clp_qout(0);
            pop();
            line(1325);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(1326);
            _clp___quit(0);
            pop();
        if_145_2:
        if_145_0:;
    goto if_144_0;
    if_144_1:
    line(1329);
    push_symbol(base+0);//ttarget
    push_symbol(base+3);//tdepend
    lt();
    if(!flag()) goto if_144_2;
        line(1330);
        push(&TRUE);
        assign(base+2);//update
        pop();
    if_144_2:
    if_144_0:;
    line(1335);
    line(1333);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_146_1;
        line(1334);
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
    if_146_1:
    if_146_0:;
    line(1337);
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
    line(1342);
    push_symbol(base+0);//cmd
    string(L"\\");
    string(L"/");
    _clp_strtran(3);
    assign(base+0);//cmd
    pop();
    line(1345);
    line(1343);
    string(L":/");
    push_symbol(base+0);//cmd
    _clp_at(2);
    number(2);
    eqeq();
    if(!flag()) goto if_147_1;
        line(1344);
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
    if_147_1:
    if_147_0:;
    line(1346);
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

