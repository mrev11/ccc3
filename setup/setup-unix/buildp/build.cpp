//input: build.ppo (5.0.21)

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
extern void _clp_lower(int argno);
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
    line(78);
    _clp_argv(0);
    _clp_aclone(1);
    assign(base+0);//opt
    pop();
    line(87);
    line(83);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"multithread_support");
    add();
    _clp_file(1);
    topnot();
    if(!flag()) goto if_1_1;
        line(84);
        push(&ONE);
        assign(_st_maxthread_ptr());//global
        pop();
    goto if_1_0;
    if_1_1:
    line(85);
    push(&ONE);
    string(L"BUILD_THR");
    _clp_getenv(1);
    _clp_val(1);
    lteq();
    if(!flag()) goto if_1_2;
        line(86);
        string(L"BUILD_THR");
        _clp_getenv(1);
        _clp_val(1);
        assign(_st_maxthread_ptr());//global
        pop();
    if_1_2:
    if_1_0:;
    line(93);
    line(89);
    push_symbol(_st_s_quiet_ptr());//global
    topnot();
    if(!flag()) goto if_2_1;
        line(90);
        string(nls_text(L"CCC Program Builder "));
        string(L"1.4.10");
        add();
        string(L" Copyright (C) ComFirm Bt.");
        add();
        _clp_qqout(1);
        pop();
        line(91);
        string(L" (Thr");
        push_symbol(_st_maxthread_ptr());//global
        _clp_str(1);
        _clp_alltrim(1);
        add();
        string(L")");
        add();
        _clp_qqout(1);
        pop();
        line(92);
        _clp_qout(0);
        pop();
    if_2_1:
    if_2_0:;
    line(180);
    {
    line(96);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_3_0:
    push_symbol(base+0);//opt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_3_2;
        line(97);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        _clp_procpar(1);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        assign2(idxxl());
        pop();
        line(179);
        line(99);
        string(L"-l");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_1;
            line(100);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_libnam_ptr());//global
            pop();
            line(101);
            push(&FALSE);
            assign(_st_s_shared_ptr());//global
            pop();
        goto if_4_0;
        if_4_1:
        line(104);
        string(L"-s");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_2;
            line(105);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_libnam_ptr());//global
            pop();
            line(106);
            push(&TRUE);
            assign(_st_s_shared_ptr());//global
            pop();
        goto if_4_0;
        if_4_2:
        line(109);
        string(L"-d");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_3;
            line(114);
            line(110);
            push_symbol(_st_s_srcdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_5_1;
                line(111);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_srcdir_ptr());//global
                pop();
            goto if_5_0;
            if_5_1:
            line(112);
                line(113);
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
        line(117);
        string(L"-i");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_4;
            line(122);
            line(118);
            push_symbol(_st_s_incdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_6_1;
                line(119);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_incdir_ptr());//global
                pop();
            goto if_6_0;
            if_6_1:
            line(120);
                line(121);
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
        line(125);
        string(L"-p");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_5;
            line(130);
            line(126);
            push_symbol(_st_s_libdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_7_1;
                line(127);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_libdir_ptr());//global
                pop();
            goto if_7_0;
            if_7_1:
            line(128);
                line(129);
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
        line(133);
        string(L"-b");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_6;
            line(138);
            line(134);
            push_symbol(_st_s_libfil_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_8_1;
                line(135);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_libfil_ptr());//global
                pop();
            goto if_8_0;
            if_8_1:
            line(136);
                line(137);
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
        line(141);
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
            line(146);
            line(142);
            push_symbol(_st_s_main_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_9_1;
                line(143);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_main_ptr());//global
                pop();
            goto if_9_0;
            if_9_1:
            line(144);
                line(145);
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
        line(148);
        string(L"-o");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_8;
            line(149);
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
        line(151);
        string(L"-h");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_9;
            line(152);
            _clp_usage(0);
            pop();
            line(153);
            _clp___quit(0);
            pop();
        goto if_4_0;
        if_4_9:
        line(155);
        string(L"-q");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_10;
            line(156);
            push(&TRUE);
            assign(_st_s_quiet_ptr());//global
            pop();
        goto if_4_0;
        if_4_10:
        line(158);
        string(L"-v");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_11;
            line(159);
            push(&TRUE);
            assign(_st_s_version_ptr());//global
            pop();
        goto if_4_0;
        if_4_11:
        line(161);
        string(L"--debug");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        if(!flag()) goto if_4_12;
            line(162);
            push(&TRUE);
            assign(_st_s_debug_ptr());//global
            pop();
        goto if_4_0;
        if_4_12:
        line(164);
        string(L"--dry");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        if(!flag()) goto if_4_13;
            line(165);
            push(&TRUE);
            assign(_st_s_debug_ptr());//global
            pop();
            line(166);
            push(&TRUE);
            assign(_st_s_dry_ptr());//global
            pop();
        goto if_4_0;
        if_4_13:
        line(168);
        string(L"@");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        push(&ONE);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_4_14;
            line(169);
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
        line(171);
        string(L"=");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        ss();
        if(!flag()) goto if_4_15;
            line(172);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_putenv(1);
            pop();
        goto if_4_0;
        if_4_15:
        line(174);
            line(175);
            string(nls_text(L"Invalid switch: "));
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_qout(2);
            pop();
            line(176);
            _clp_usage(0);
            pop();
            line(177);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(178);
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
    line(185);
    line(183);
    string(L"on");
    string(L"BUILD_DBG");
    _clp_getenv(1);
    _clp_lower(1);
    ss();
    if(!flag()) goto if_10_1;
        line(184);
        push(&TRUE);
        assign(_st_s_debug_ptr());//global
        pop();
    if_10_1:
    if_10_0:;
    line(188);
    line(186);
    string(L"debug");
    string(L"BUILD_DBG");
    _clp_getenv(1);
    _clp_lower(1);
    ss();
    if(!flag()) goto if_11_1;
        line(187);
        push(&TRUE);
        assign(_st_s_debug_ptr());//global
        pop();
    if_11_1:
    if_11_0:;
    line(192);
    line(189);
    string(L"dry");
    string(L"BUILD_DBG");
    _clp_getenv(1);
    _clp_lower(1);
    ss();
    if(!flag()) goto if_12_1;
        line(190);
        push(&TRUE);
        assign(_st_s_debug_ptr());//global
        pop();
        line(191);
        push(&TRUE);
        assign(_st_s_dry_ptr());//global
        pop();
    if_12_1:
    if_12_0:;
    line(196);
    line(194);
    push_symbol(_st_s_version_ptr());//global
    if(!flag()) goto if_13_1;
        line(195);
        _clp___quit(0);
        pop();
    if_13_1:
    if_13_0:;
    line(198);
    _clp_s_rules_from_build_bat(0);
    pop();
    line(199);
    _clp_extension_types(0);
    pop();
    line(201);
    _clp_root(0);
    pop();
    line(202);
    _clp_params(0);
    pop();
    line(203);
    _clp_build(0);
    pop();
    line(205);
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
    line(213);
    line(215);
    push_symbol(_st_s_rules_ptr());//global
    push(&ZERO);
    _clp_asize(2);
    pop();
    line(216);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"*.bat");
    add();
    _clp_directory(1);
    assign(base+0);//d
    pop();
    line(224);
    {
    line(217);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_14_0:
    push_symbol(base+0);//d
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_14_2;
        line(218);
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
        line(223);
        line(219);
        push_symbol(base+2);//rule
        _clp_len(1);
        number(2);
        eqeq();
        if(!flag()) goto if_15_1;
            line(220);
            string(L".");
            push_symbol(base+2);//rule
            idxr0(1);
            add();
            push_symbol(base+2);//rule
            assign2(idxxl0(1));
            pop();
            line(221);
            string(L".");
            push_symbol(base+2);//rule
            idxr0(2);
            add();
            push_symbol(base+2);//rule
            assign2(idxxl0(2));
            pop();
            line(222);
            push_symbol(_st_s_rules_ptr());//global
            push_symbol(base+2);//rule
            _clp_aadd(2);
            pop();
        if_15_1:
        if_15_0:;
    lab_14_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+1);//n
    add();
    assign(base+1);//n
    goto lab_14_0;
    lab_14_2:;
    }
    line(226);
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
    line(233);
    line(234);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_16_1;
        string(L".exe");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_16_1:
    if_16_0:;
    line(235);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_17_1;
        string(L".so");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_17_1:
    if_17_0:;
    line(236);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_18_1;
        string(L".lib");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_18_1:
    if_18_0:;
    line(237);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_19_1;
        string(L".obj");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_19_1:
    if_19_0:;
    line(238);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    if(!flag()) goto if_20_1;
        push_symbol(base+0);//x
        idxr0(1);
        push_symbol(base+1);//y
        idxr0(1);
        lt();
        assign(base+2);//result
        pop();
    if_20_1:
    if_20_0:;
    line(239);
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
    line(246);
    line(242);
    push_symbol(base+1);//x
    idxr0(2);
    push_symbol(base+0);//ext
    eqeq();
    if(!flag()) goto if_21_1;
        line(243);
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
    goto if_21_0;
    if_21_1:
    line(244);
    push_symbol(base+2);//y
    idxr0(2);
    push_symbol(base+0);//ext
    eqeq();
    if(!flag()) goto if_21_2;
        line(245);
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
    if_21_2:
    if_21_0:;
    line(247);
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
    line(251);
    line(253);
    string(L"");
    assign(_st_s_primary_ptr());//global
    pop();
    line(254);
    string(L"");
    assign(_st_s_resource_ptr());//global
    pop();
    line(268);
    {
    line(256);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_22_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_22_2;
        line(257);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+2);//n
        idxr();
        idxr0(1);
        assign(base+0);//r1
        pop();
        line(258);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+2);//n
        idxr();
        idxr0(2);
        assign(base+1);//r2
        pop();
        line(264);
        line(262);
        push_symbol(base+1);//r2
        string(L".obj");
        eqeq();
        if(!flag()) goto if_23_1;
            line(263);
            push_symbol(_st_s_primary_ptr());//global
            push_symbol(base+0);//r1
            add();
            assign(_st_s_primary_ptr());//global
            pop();
        if_23_1:
        if_23_0:;
        line(267);
        line(265);
        push_symbol(base+1);//r2
        string(L".");
        add();
        string(L".obj.lib.exe.");
        ss();
        topnot();
        if(!flag()) goto if_24_1;
            line(266);
            push_symbol(_st_s_resource_ptr());//global
            push_symbol(base+0);//r1
            add();
            assign(_st_s_resource_ptr());//global
            pop();
        if_24_1:
        if_24_0:;
    lab_22_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_22_0;
    lab_22_2:;
    }
    line(269);
    push_symbol(_st_s_primary_ptr());//global
    string(L".");
    add();
    assign(_st_s_primary_ptr());//global
    pop();
    line(270);
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
    line(277);
    push_symbol(base+0);//parfil
    _clp_memoread(1);
    assign(base+3);//par
    pop();
    line(284);
    line(279);
    push_symbol(base+3);//par
    _clp_empty(1);
    if(!flag()) goto if_25_1;
        line(283);
        string(L"BUILD_BAT");
        _clp_getenv(1);
        _clp_dirsep(0);
        add();
        push_symbol(base+0);//parfil
        add();
        _clp_memoread(1);
        assign(base+3);//par
        pop();
    if_25_1:
    if_25_0:;
    line(292);
    line(286);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_26_1;
        line(291);
        line(287);
        push_symbol(base+3);//par
        _clp_empty(1);
        if(!flag()) goto if_27_1;
            line(288);
            string(L"Build parfile empty:");
            push_symbol(base+0);//parfil
            _clp_qqout(2);
            pop();
            _clp_qout(0);
            pop();
        goto if_27_0;
        if_27_1:
        line(289);
            line(290);
            string(L"Build parfile:");
            push_symbol(base+0);//parfil
            _clp_qqout(2);
            pop();
            _clp_qout(0);
            pop();
        if_27_2:
        if_27_0:;
    if_26_1:
    if_26_0:;
    line(294);
    push_symbol(base+3);//par
    number(13);
    _clp_chr(1);
    string(L"");
    _clp_strtran(3);
    assign(base+3);//par
    pop();
    line(295);
    push_symbol(base+3);//par
    number(10);
    _clp_chr(1);
    _clp_split(2);
    assign(base+3);//par
    pop();
    line(311);
    {
    line(297);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_28_0:
    push_symbol(base+3);//par
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_28_2;
        line(298);
        push_symbol(base+3);//par
        push_symbol(base+4);//n
        idxr();
        assign(base+5);//p
        pop();
        line(301);
        line(299);
        string(L"#");
        push_symbol(base+5);//p
        ss();
        if(!flag()) goto if_29_1;
            line(300);
            push_symbol(base+5);//p
            string(L"#");
            push_symbol(base+5);//p
            _clp_at(2);
            addnum(-1);
            _clp_left(2);
            assign(base+5);//p
            pop();
        if_29_1:
        if_29_0:;
        line(303);
        push_symbol(base+5);//p
        string(L" ");
        _clp_split(2);
        assign(base+5);//p
        pop();
        line(310);
        {
        line(304);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+6);//i
        lab_30_0:
        push_symbol(base+5);//p
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_30_2;
            line(309);
            line(305);
            push_symbol(base+5);//p
            push_symbol(base+6);//i
            idxr();
            _clp_empty(1);
            topnot();
            if(!flag()) goto if_31_1;
                line(306);
                push_symbol(base+1);//opt
                push(&NIL);
                _clp_aadd(2);
                pop();
                line(307);
                push_symbol(base+1);//opt
                push_symbol(base+2);//optx
                push(&ONE);
                add();
                assign(base+2);//optx
                _clp_ains(2);
                pop();
                line(308);
                push_symbol(base+5);//p
                push_symbol(base+6);//i
                idxr();
                push_symbol(base+1);//opt
                push_symbol(base+2);//optx
                assign2(idxxl());
                pop();
            if_31_1:
            if_31_0:;
        lab_30_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+6);//i
        add();
        assign(base+6);//i
        goto lab_30_0;
        lab_30_2:;
        }
    lab_28_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_28_0;
    lab_28_2:;
    }
    line(312);
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
    line(316);
    line(325);
    lab_32_1:
    line(318);
    push(&ZERO);
    string(L"$$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_32_2;
        line(319);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(320);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(3);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(321);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(322);
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
        line(323);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(324);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_32_1;
    lab_32_2:;
    line(334);
    lab_33_1:
    line(327);
    push(&ZERO);
    string(L"$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_33_2;
        line(328);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(329);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(2);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(330);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(331);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        _clp_getenv(1);
        add();
        assign(base+2);//p
        pop();
        line(332);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(333);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_33_1;
    lab_33_2:;
    line(336);
    push_symbol(base+0);//par
    string(L"\\");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(337);
    push_symbol(base+0);//par
    string(L"/");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(339);
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
    line(344);
    string(nls_text(L"BUILD -xExeNam|-lLibNam -dSrcDir -iIncDir -pLibDir -bLibFil -mMain"));
    _clp_qout(1);
    pop();
    line(345);
    _clp_qout(0);
    pop();
    line(346);
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
    line(352);
    line(389);
    line(354);
    string(L"BUILD_SRC");
    _clp_getenv(1);
    assign(base+0);//srcroot
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_34_1;
        line(358);
        line(356);
        push_symbol(base+0);//srcroot
        push(&ONE);
        _clp_right(2);
        string(L"/\\");
        ss();
        topnot();
        if(!flag()) goto if_35_1;
            line(357);
            push_symbol(base+0);//srcroot
            _clp_dirsep(0);
            add();
            assign(base+0);//srcroot
            pop();
        if_35_1:
        if_35_0:;
        line(362);
        line(360);
        push_symbol(_st_s_srcdir_ptr());//global
        push(&NIL);
        eqeq();
        if(!flag()) goto if_36_1;
            line(361);
            string(L".");
            assign(_st_s_srcdir_ptr());//global
            pop();
        if_36_1:
        if_36_0:;
        line(364);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+1);//d
        pop();
        line(366);
        string(L"");
        assign(_st_s_srcdir_ptr());//global
        pop();
        line(373);
        {
        line(367);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+2);//n
        lab_37_0:
        push_symbol(base+1);//d
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_37_2;
            line(372);
            line(368);
            push_symbol(base+1);//d
            push_symbol(base+2);//n
            idxr();
            push(&ONE);
            _clp_left(2);
            string(L"/\\");
            ss();
            if(!flag()) goto if_38_1;
                line(369);
                push_symbol(_st_s_srcdir_ptr());//global
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                string(L";");
                add();
                add();
                assign(_st_s_srcdir_ptr());//global
                pop();
            goto if_38_0;
            if_38_1:
            line(370);
                line(371);
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
            if_38_2:
            if_38_0:;
        lab_37_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+2);//n
        add();
        assign(base+2);//n
        goto lab_37_0;
        lab_37_2:;
        }
        line(388);
        line(376);
        push_symbol(_st_s_incdir_ptr());//global
        push(&NIL);
        neeq();
        if(!flag()) goto if_39_1;
            line(378);
            push_symbol(_st_s_incdir_ptr());//global
            string(L",;");
            _clp_xsplit(2);
            assign(base+1);//d
            pop();
            line(380);
            string(L"");
            assign(_st_s_incdir_ptr());//global
            pop();
            line(387);
            {
            line(381);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+2);//n
            lab_40_0:
            push_symbol(base+1);//d
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_40_2;
                line(386);
                line(382);
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                push(&ONE);
                _clp_left(2);
                string(L"/\\");
                ss();
                if(!flag()) goto if_41_1;
                    line(383);
                    push_symbol(_st_s_incdir_ptr());//global
                    push_symbol(base+1);//d
                    push_symbol(base+2);//n
                    idxr();
                    string(L";");
                    add();
                    add();
                    assign(_st_s_incdir_ptr());//global
                    pop();
                goto if_41_0;
                if_41_1:
                line(384);
                    line(385);
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
        if_39_1:
        if_39_0:;
    if_34_1:
    if_34_0:;
    line(391);
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
    line(397);
    line(410);
    string(L"");
    assign(base+0);//txt
    pop();
    line(411);
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
    line(412);
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
    line(413);
    push_symbol(base+0);//txt
    string(L"BUILD_INC");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(414);
    push_symbol(base+0);//txt
    string(L"include");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(415);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(416);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(418);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(420);
    string(L"BUILD_INC=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(426);
    string(L"");
    assign(base+0);//txt
    pop();
    line(427);
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
    line(428);
    push_symbol(base+0);//txt
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(429);
    push_symbol(base+0);//txt
    string(L"lib");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(430);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(431);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(433);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(435);
    string(L"BUILD_LPT=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(441);
    string(L"");
    assign(base+0);//txt
    pop();
    line(442);
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
    line(443);
    push_symbol(base+0);//txt
    string(L"BUILD_LIB");
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
    line(446);
    string(L"BUILD_LIB=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(447);
    _clp_search_library(0);
    assign(_st_s_libspec_ptr());//global
    pop();
    line(448);
    string(L"BUILD_LIB=");
    push_symbol(_st_s_libspec_ptr());//global
    add();
    _clp_putenv(1);
    pop();
    line(449);
    push_symbol(_st_s_libspec_ptr());//global
    string(L" ");
    _clp_split(2);
    assign(_st_s_libspec_ptr());//global
    pop();
    line(451);
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
    line(457);
    array(0);
    assign(base+0);//dir
    pop();
    line(458);
    array(0);
    assign(base+1);//obj
    pop();
    line(459);
    array(0);
    assign(base+2);//lib
    pop();
    line(460);
    array(0);
    assign(base+3);//mmd
    pop();
    line(461);
    array(0);
    assign(base+4);//todo
    pop();
    line(463);
    line(468);
    line(466);
    push_symbol(_st_s_main_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_42_1;
        line(467);
        push_symbol(_st_s_main_ptr());//global
        _clp_lower(1);
        string(L",;");
        _clp_xsplit(2);
        assign(base+3);//mmd
        pop();
    if_42_1:
    if_42_0:;
    line(475);
    line(471);
    push_symbol(_st_s_srcdir_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_43_1;
        line(472);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+0);//dir
        pop();
    goto if_43_0;
    if_43_1:
    line(473);
        line(474);
        string(L".");
        array(1);
        assign(base+0);//dir
        pop();
    if_43_2:
    if_43_0:;
    line(499);
    {
    line(477);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_44_0:
    push_symbol(base+0);//dir
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_44_2;
        line(479);
        string(L"");
        push_symbol(base+0);//dir
        push_symbol(base+8);//n
        idxr();
        _clp_qqout(2);
        pop();
        line(481);
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
        line(498);
        {
        line(483);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//i
        lab_45_0:
        push_symbol(base+5);//d1
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_45_2;
            line(485);
            push_symbol(base+5);//d1
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            _clp_lower(1);
            assign(base+6);//f
            pop();
            line(493);
            line(487);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            push_symbol(_st_s_primary_ptr());//global
            ss();
            if(!flag()) goto if_46_1;
                line(492);
                line(488);
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
                line(490);
                    line(491);
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
            line(497);
            line(495);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            push_symbol(_st_s_resource_ptr());//global
            ss();
            if(!flag()) goto if_48_1;
                line(496);
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
    line(500);
    _clp_qout(0);
    pop();
    line(536);
    {
    line(505);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_49_0:
    push_symbol(base+1);//obj
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_49_2;
        line(507);
        push_symbol(base+1);//obj
        push_symbol(base+8);//n
        idxr();
        assign(base+6);//f
        pop();
        line(508);
        push_symbol(base+6);//f
        _clp_fname(1);
        assign(base+7);//o
        pop();
        line(509);
        push_symbol(base+6);//f
        _clp_memoread(1);
        assign(base+10);//txt
        pop();
        line(519);
        line(511);
        push(&ZERO);
        push_symbol(base+3);//mmd
        push_symbol_ref(base+7);//o
        block(_blk_build_0,1);
        _clp_ascan(2);
        neeq();
        if(!flag()) goto if_50_1;
        goto if_50_0;
        if_50_1:
        line(513);
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
            line(516);
            line(514);
            push_symbol(_st_s_main_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_51_1;
                line(515);
                push_symbol(base+3);//mmd
                push_symbol(base+7);//o
                _clp_aadd(2);
                pop();
            if_51_1:
            if_51_0:;
        goto if_50_0;
        if_50_2:
        line(517);
            line(518);
            push_symbol(base+2);//lib
            push_symbol(base+7);//o
            _clp_aadd(2);
            pop();
        if_50_3:
        if_50_0:;
        line(521);
        push_symbol(base+7);//o
        string(L".obj");
        add();
        push_symbol(base+6);//f
        array(2);
        assign(base+11);//dep
        pop();
        line(533);
        {
        line(522);
        push(&ONE);
        int sg=sign();
        number(2);
        assign(base+9);//i
        lab_52_0:
        push_symbol(base+11);//dep
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_52_2;
            line(531);
            line(523);
            push_symbol(base+9);//i
            number(2);
            eqeq();
            if(!flag()) goto if_53_1;
            goto if_53_0;
            if_53_1:
            line(525);
            push_symbol(base+9);//i
            number(1024);
            gt();
            if(!flag()) goto if_53_2;
                line(526);
                string(L"recursive dependencies:");
                push_symbol(base+11);//dep
                _clp_qout(2);
                pop();
                line(527);
                _clp_qout(0);
                pop();
                line(528);
                _clp___quit(0);
                pop();
            goto if_53_0;
            if_53_2:
            line(529);
                line(530);
                push_symbol(base+11);//dep
                push_symbol(base+9);//i
                idxr();
                _clp_memoread(1);
                assign(base+10);//txt
                pop();
            if_53_3:
            if_53_0:;
            line(532);
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
        line(535);
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
    line(538);
    push_symbol(base+4);//todo
    _clp_normalize(1);
    pop();
    line(540);
    push_symbol(base+4);//todo
    push(&NIL);
    push(&NIL);
    block(_blk_build_1,0);
    _clp_asort(4);
    pop();
    line(552);
    line(544);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_54_1;
        line(545);
        string(L"main:");
        push_symbol(base+3);//mmd
        _clp_qout(2);
        pop();
        line(546);
        string(L"lib :");
        push_symbol(base+2);//lib
        _clp_qout(2);
        pop();
        line(547);
        _clp_qout(0);
        pop();
        line(550);
        {
        line(548);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_55_0:
        push_symbol(base+4);//todo
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_55_2;
            line(549);
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
        line(551);
        _clp_qout(0);
        pop();
    if_54_1:
    if_54_0:;
    line(554);
    string(L"error");
    _clp_ferase(1);
    pop();
    line(573);
    {
    line(555);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_56_0:
    push_symbol(base+4);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_56_2;
        line(556);
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_mutex_lock(1);
        pop();
        line(557);
        push_symbol(_st_thread_count_ptr());//global
        push(&ONE);
        add();
        assign(_st_thread_count_ptr());//global
        pop();
        line(560);
        lab_57_1:
        line(558);
        push_symbol(_st_thread_count_ptr());//global
        push_symbol(_st_maxthread_ptr());//global
        gt();
        if(!flag()) goto lab_57_2;
            line(559);
            push_symbol(_st_cond_count_ptr());//global
            push_symbol(_st_mutex_count_ptr());//global
            _clp_thread_cond_wait(2);
            pop();
        goto lab_57_1;
        lab_57_2:;
        line(561);
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_mutex_unlock(1);
        pop();
        line(563);
        push_symbol_ref(base+4);//todo
        block(_blk_build_2,1);
        push_symbol(base+8);//n
        _clp_thread_create_detach(2);
        pop();
        line(572);
        line(565);
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
        if(!flag()) goto if_58_1;
            line(567);
            push_symbol(_st_mutex_count_ptr());//global
            _clp_thread_mutex_lock(1);
            pop();
            line(570);
            lab_59_1:
            line(568);
            push_symbol(_st_thread_count_ptr());//global
            push(&ZERO);
            gt();
            if(!flag()) goto lab_59_2;
                line(569);
                push_symbol(_st_cond_count_ptr());//global
                push_symbol(_st_mutex_count_ptr());//global
                _clp_thread_cond_wait(2);
                pop();
            goto lab_59_1;
            lab_59_2:;
            line(571);
            push_symbol(_st_mutex_count_ptr());//global
            _clp_thread_mutex_unlock(1);
            pop();
        if_58_1:
        if_58_0:;
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
    line(575);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(578);
    lab_60_1:
    line(576);
    push_symbol(_st_thread_count_ptr());//global
    push(&ZERO);
    gt();
    if(!flag()) goto lab_60_2;
        line(577);
        push_symbol(_st_cond_count_ptr());//global
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_cond_wait(2);
        pop();
    goto lab_60_1;
    lab_60_2:;
    line(579);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    line(600);
    line(583);
    push_symbol(_st_s_libnam_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_61_1;
        line(584);
        push_symbol(_st_s_libnam_ptr());//global
        push_symbol(base+2);//lib
        _clp_makelib(2);
        pop();
        line(588);
        line(586);
        push_symbol(_st_s_shared_ptr());//global
        push(&TRUE);
        eqeq();
        if(!flag()) goto if_62_1;
            line(587);
            push_symbol(_st_s_libnam_ptr());//global
            push_symbol(base+2);//lib
            _clp_makeso(2);
            pop();
        if_62_1:
        if_62_0:;
        line(593);
        block(_blk_build_3,0);
        push_symbol(base+3);//mmd
        _clp_manage_threads(2);
        pop();
    goto if_61_0;
    if_61_1:
    line(595);
        line(599);
        push_symbol_ref(base+2);//lib
        block(_blk_build_4,1);
        push_symbol(base+3);//mmd
        _clp_manage_threads(2);
        pop();
    if_61_2:
    if_61_0:;
    line(602);
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
    line(608);
    array(0);
    assign(base+2);//thread
    pop();
    line(619);
    {
    line(609);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_63_0:
    push_symbol(base+1);//a
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_63_2;
        line(610);
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_mutex_lock(1);
        pop();
        line(611);
        push_symbol(_st_thread_count_ptr());//global
        push(&ONE);
        add();
        assign(_st_thread_count_ptr());//global
        pop();
        line(614);
        lab_64_1:
        line(612);
        push_symbol(_st_thread_count_ptr());//global
        push_symbol(_st_maxthread_ptr());//global
        gt();
        if(!flag()) goto lab_64_2;
            line(613);
            push_symbol(_st_cond_count_ptr());//global
            push_symbol(_st_mutex_count_ptr());//global
            _clp_thread_cond_wait(2);
            pop();
        goto lab_64_1;
        lab_64_2:;
        line(615);
        push_symbol(_st_mutex_count_ptr());//global
        _clp_thread_mutex_unlock(1);
        pop();
        line(617);
        push_symbol_ref(base+0);//blk
        push_symbol_ref(base+1);//a
        block(_blk_manage_threads_0,2);
        push_symbol(base+4);//n
        _clp_thread_create(2);
        assign(base+3);//th
        pop();
        line(618);
        push_symbol(base+2);//thread
        push_symbol(base+3);//th
        _clp_aadd(2);
        pop();
    lab_63_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_63_0;
    lab_63_2:;
    }
    line(622);
    {
    line(620);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_65_0:
    push_symbol(base+2);//thread
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_65_2;
        line(621);
        push_symbol(base+2);//thread
        push_symbol(base+4);//n
        idxr();
        _clp_thread_join(1);
        pop();
    lab_65_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_65_0;
    lab_65_2:;
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
    line(628);
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
    line(629);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(630);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2so.bat");
    add();
    assign(base+7);//torun
    pop();
    line(631);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(638);
    line(633);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_66_1;
        line(634);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(635);
        _clp_qout(0);
        pop();
        line(636);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(637);
        _clp___quit(0);
        pop();
    if_66_1:
    if_66_0:;
    line(640);
    push_symbol(base+7);//torun
    string(L" lib");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(642);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(645);
    line(643);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_67_1;
        line(644);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_67_1:
    if_67_0:;
    line(649);
    line(647);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_68_1;
        line(648);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_68_1:
    if_68_0:;
    line(657);
    {
    line(651);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_69_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_69_2;
        line(653);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(654);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+4);//depend
        add();
        add();
        assign(base+7);//torun
        pop();
        line(655);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(656);
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
    lab_69_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_69_0;
    lab_69_2:;
    }
    line(661);
    line(659);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_70_1;
        line(660);
        _clp_qout(0);
        pop();
    if_70_1:
    if_70_0:;
    line(665);
    line(663);
    push_symbol(base+6);//update
    if(!flag()) goto if_71_1;
        line(664);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_71_1:
    if_71_0:;
    line(667);
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
    line(673);
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
    line(674);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(675);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2lib.bat");
    add();
    assign(base+7);//torun
    pop();
    line(676);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+8);//objdir
    pop();
    line(677);
    line(684);
    line(679);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_72_1;
        line(680);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(681);
        _clp_qout(0);
        pop();
        line(682);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(683);
        _clp___quit(0);
        pop();
    if_72_1:
    if_72_0:;
    line(686);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(688);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(691);
    line(689);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_73_1;
        line(690);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_73_1:
    if_73_0:;
    line(695);
    line(693);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_74_1;
        line(694);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_74_1:
    if_74_0:;
    line(702);
    {
    line(697);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_75_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_75_2;
        line(699);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(700);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(701);
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
    lab_75_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_75_0;
    lab_75_2:;
    }
    line(706);
    line(704);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_76_1;
        line(705);
        _clp_qout(0);
        pop();
    if_76_1:
    if_76_0:;
    line(734);
    line(708);
    push_symbol(base+6);//update
    if(!flag()) goto if_77_1;
        line(713);
        {
        line(711);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_78_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_78_2;
            line(712);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
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
        line(733);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_77_1:
    if_77_0:;
    line(736);
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
    line(742);
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
    line(743);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(744);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2exe.bat");
    add();
    assign(base+7);//torun
    pop();
    line(745);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+8);//objdir
    pop();
    line(746);
    line(753);
    line(748);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_79_1;
        line(749);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(750);
        _clp_qout(0);
        pop();
        line(751);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(752);
        _clp___quit(0);
        pop();
    if_79_1:
    if_79_0:;
    line(755);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(758);
    line(756);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_80_1;
        line(757);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_80_1:
    if_80_0:;
    line(762);
    line(760);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_81_1;
        line(761);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_81_1:
    if_81_0:;
    line(774);
    {
    line(764);
    push(&ONE);
    int sg=sign();
    push(&ZERO);
    assign(base+9);//n
    lab_82_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_82_2;
        line(770);
        line(766);
        push_symbol(base+9);//n
        push(&ZERO);
        eqeq();
        if(!flag()) goto if_83_1;
            line(767);
            push_symbol(base+0);//exenam
            assign(base+4);//depend
            pop();
        goto if_83_0;
        if_83_1:
        line(768);
            line(769);
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
        if_83_2:
        if_83_0:;
        line(772);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(773);
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
    lab_82_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_82_0;
    lab_82_2:;
    }
    line(781);
    {
    line(776);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_84_0:
    push_symbol(_st_s_libspec_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_84_2;
        line(780);
        line(777);
        push_symbol(_st_s_libspec_ptr());//global
        push_symbol(base+9);//n
        idxr();
        number(4);
        _clp_right(2);
        string(L".lib");
        eqeq();
        if(!flag()) goto if_85_1;
            line(778);
            push_symbol(_st_s_libspec_ptr());//global
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
            line(779);
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
        if_85_1:
        if_85_0:;
    lab_84_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_84_0;
    lab_84_2:;
    }
    line(785);
    line(783);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_86_1;
        line(784);
        _clp_qout(0);
        pop();
    if_86_1:
    if_86_0:;
    line(819);
    line(787);
    push_symbol(base+6);//update
    if(!flag()) goto if_87_1;
        line(788);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+0);//exenam
        add();
        add();
        assign(base+7);//torun
        pop();
        line(793);
        {
        line(791);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_88_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_88_2;
            line(792);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
            pop();
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
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_87_1:
    if_87_0:;
    line(821);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(822);
    push_symbol(_st_thread_count_ptr());//global
    push(&ONE);
    sub();
    assign(_st_thread_count_ptr());//global
    pop();
    line(823);
    push_symbol(_st_cond_count_ptr());//global
    _clp_thread_cond_signal(1);
    pop();
    line(824);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    line(826);
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
    line(832);
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
    line(833);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(834);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"lib2exe.bat");
    add();
    assign(base+7);//torun
    pop();
    line(835);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(842);
    line(837);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_89_1;
        line(838);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(839);
        _clp_qout(0);
        pop();
        line(840);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(841);
        _clp___quit(0);
        pop();
    if_89_1:
    if_89_0:;
    line(844);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(847);
    line(845);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_90_1;
        line(846);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_90_1:
    if_90_0:;
    line(851);
    line(849);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_91_1;
        line(850);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_91_1:
    if_91_0:;
    line(854);
    push_symbol(base+0);//mmod
    assign(base+4);//depend
    pop();
    line(855);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(856);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".obj");
    add();
    assign(base+4);//depend
    pop();
    line(857);
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
    line(859);
    push_symbol(base+1);//libnam
    assign(base+4);//depend
    pop();
    line(860);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(861);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".lib");
    add();
    assign(base+4);//depend
    pop();
    line(862);
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
    line(869);
    {
    line(864);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_92_0:
    push_symbol(_st_s_libspec_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_92_2;
        line(868);
        line(865);
        push_symbol(_st_s_libspec_ptr());//global
        push_symbol(base+9);//n
        idxr();
        number(4);
        _clp_right(2);
        string(L".lib");
        eqeq();
        if(!flag()) goto if_93_1;
            line(866);
            push_symbol(_st_s_libspec_ptr());//global
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
            line(867);
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
        if_93_1:
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
    line(873);
    line(871);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_94_1;
        line(872);
        _clp_qout(0);
        pop();
    if_94_1:
    if_94_0:;
    line(877);
    line(875);
    push_symbol(base+6);//update
    if(!flag()) goto if_95_1;
        line(876);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_95_1:
    if_95_0:;
    line(879);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(880);
    push_symbol(_st_thread_count_ptr());//global
    push(&ONE);
    sub();
    assign(_st_thread_count_ptr());//global
    pop();
    line(881);
    push_symbol(_st_cond_count_ptr());//global
    _clp_thread_cond_signal(1);
    pop();
    line(882);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    line(884);
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
    line(890);
    push_symbol(base+0);//deplist
    idxr0(1);
    assign(base+1);//target
    pop();
    line(891);
    push_symbol(base+0);//deplist
    idxr0(2);
    assign(base+2);//depend
    pop();
    line(892);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+3);//objdir
    pop();
    line(893);
    line(894);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(895);
    line(899);
    line(897);
    push_symbol(base+1);//target
    _clp_fext(1);
    string(L".obj");
    eqeq();
    if(!flag()) goto if_96_1;
        line(898);
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
    if_96_1:
    if_96_0:;
    line(901);
    push_symbol(base+1);//target
    _clp_ftime(1);
    assign(base+4);//ttarget
    pop();
    line(904);
    line(902);
    push_symbol(base+4);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_97_1;
        line(903);
        string(L"");
        assign(base+4);//ttarget
        pop();
    if_97_1:
    if_97_0:;
    line(908);
    line(906);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_98_1;
        line(907);
        push_symbol(base+1);//target
        string(L"[");
        push_symbol(base+4);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_98_1:
    if_98_0:;
    line(913);
    {
    line(910);
    push(&ONE);
    int sg=sign();
    number(2);
    assign(base+8);//n
    lab_99_0:
    push_symbol(base+0);//deplist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_99_2;
        line(911);
        push_symbol(base+0);//deplist
        push_symbol(base+8);//n
        idxr();
        assign(base+2);//depend
        pop();
        line(912);
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
    lab_99_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_99_0;
    lab_99_2:;
    }
    line(917);
    line(915);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_100_1;
        line(916);
        _clp_qout(0);
        pop();
    if_100_1:
    if_100_0:;
    line(936);
    line(919);
    push_symbol(base+6);//update
    if(!flag()) goto if_101_1;
        line(921);
        string(L"BUILD_BAT");
        _clp_getenv(1);
        _clp_dirsep(0);
        add();
        assign(base+7);//torun
        pop();
        line(922);
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
        line(923);
        push_symbol(base+7);//torun
        string(L".bat");
        add();
        assign(base+7);//torun
        pop();
        line(930);
        line(925);
        push_symbol(base+7);//torun
        _clp_file(1);
        topnot();
        if(!flag()) goto if_102_1;
            line(926);
            string(L"[");
            push_symbol(base+7);//torun
            add();
            string(L"]");
            add();
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(927);
            _clp_qout(0);
            pop();
            line(928);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(929);
            _clp___quit(0);
            pop();
        if_102_1:
        if_102_0:;
        line(932);
        push_symbol(base+0);//deplist
        idxr0(1);
        _clp_fname(1);
        assign(base+9);//p1
        pop();
        line(933);
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
        line(935);
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
    if_101_1:
    if_101_0:;
    line(938);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(939);
    push_symbol(_st_thread_count_ptr());//global
    push(&ONE);
    sub();
    assign(_st_thread_count_ptr());//global
    pop();
    line(940);
    push_symbol(_st_cond_count_ptr());//global
    _clp_thread_cond_signal(1);
    pop();
    line(941);
    push_symbol(_st_mutex_count_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    line(943);
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
    line(950);
    static stvarloc _st_mutex_out(_ini_run1_mutex_out,base);
    line(951);
    static stvar _st_count((double)0);
    line(952);
    line(978);
    line(954);
    push_symbol(_st_s_dry_ptr());//global
    topnot();
    if(!flag()) goto if_103_1;
        line(956);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_lock(1);
        pop();
        line(957);
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
        line(958);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_unlock(1);
        pop();
        line(960);
        push_symbol(base+0);//cmd
        string(L" >");
        add();
        push_symbol(base+1);//runtmp
        add();
        _clp_run(1);
        pop();
        line(961);
        push_symbol(base+1);//runtmp
        _clp_memoread(1);
        assign(base+2);//out
        pop();
        line(962);
        push_symbol(base+1);//runtmp
        _clp_ferase(1);
        pop();
        line(964);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_lock(1);
        pop();
        line(965);
        push_symbol(base+2);//out
        _clp_qqout(1);
        pop();
        line(966);
        push_symbol(_st_mutex_out.ptr);//run1
        _clp_thread_mutex_unlock(1);
        pop();
        line(977);
        line(968);
        string(L"error");
        _clp_file(1);
        if(!flag()) goto if_104_1;
            line(970);
            string(L"cat error");
            _clp_run(1);
            pop();
            line(976);
            push(&TRUE);
            assign(_st_s_dry_ptr());//global
            pop();
        if_104_1:
        if_104_0:;
    if_103_1:
    if_103_0:;
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
    line(983);
    push_symbol(base+0);//fspec
    string(L"H");
    _clp_directory(2);
    assign(base+1);//d
    pop();
    line(986);
    line(984);
    push_symbol(base+1);//d
    _clp_len(1);
    push(&ONE);
    eqeq();
    if(!flag()) goto if_105_1;
        line(985);
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
    if_105_1:
    if_105_0:;
    line(987);
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
    line(993);
    number(10);
    _clp_chr(1);
    assign(base+4);//nl
    pop();
    line(994);
    string(L"#include");
    assign(base+5);//include
    pop();
    line(995);
    push_symbol(base+5);//include
    _clp_len(1);
    assign(base+6);//lenincl
    pop();
    line(996);
    push(&ZERO);
    assign(base+8);//n2
    pop();
    line(1033);
    lab_106_1:
    line(998);
    push_symbol(base+5);//include
    push_symbol(base+0);//txt
    push_symbol(base+8);//n2
    addnum(1);
    _clp_at(3);
    assign(base+7);//n1
    push(&ZERO);
    gt();
    if(!flag()) goto lab_106_2;
        line(1002);
        line(1000);
        push(&ZERO);
        push_symbol(base+4);//nl
        push_symbol(base+0);//txt
        push_symbol(base+7);//n1
        push_symbol(base+6);//lenincl
        add();
        _clp_at(3);
        assign(base+8);//n2
        eqeq();
        if(!flag()) goto if_107_1;
            line(1001);
            push_symbol(base+0);//txt
            _clp_len(1);
            addnum(1);
            assign(base+8);//n2
            pop();
        if_107_1:
        if_107_0:;
        line(1004);
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
        line(1005);
        push_symbol(base+9);//line
        number(9);
        _clp_chr(1);
        string(L"");
        _clp_strtran(3);
        assign(base+9);//line
        pop();
        line(1006);
        push_symbol(base+9);//line
        _clp_alltrim(1);
        assign(base+9);//line
        pop();
        line(1014);
        line(1008);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"\"");
        eqeq();
        if(!flag()) goto if_108_1;
            line(1009);
            string(L"\"");
            assign(base+10);//delim
            pop();
        goto if_108_0;
        if_108_1:
        line(1010);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"<");
        eqeq();
        if(!flag()) goto if_108_2;
            line(1011);
            string(L">");
            assign(base+10);//delim
            pop();
        goto if_108_0;
        if_108_2:
        line(1012);
            line(1013);
            goto lab_106_1;//loop
        if_108_3:
        if_108_0:;
        line(1018);
        line(1016);
        push(&ZERO);
        push_symbol(base+10);//delim
        push_symbol(base+9);//line
        number(2);
        _clp_at(3);
        assign(base+11);//dpos
        eqeq();
        if(!flag()) goto if_109_1;
            line(1017);
            goto lab_106_1;//loop
        if_109_1:
        if_109_0:;
        line(1020);
        push_symbol(base+9);//line
        number(2);
        push_symbol(base+11);//dpos
        addnum(-2);
        _clp_substr(3);
        assign(base+12);//f
        pop();
        line(1021);
        push_symbol(base+12);//f
        string(L"/");
        _clp_dirsep(0);
        _clp_strtran(3);
        assign(base+12);//f
        pop();
        line(1022);
        push_symbol(base+12);//f
        string(L"\\");
        _clp_dirsep(0);
        _clp_strtran(3);
        assign(base+12);//f
        pop();
        line(1032);
        line(1024);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byrules(4);
        if(!flag()) goto if_110_1;
        goto if_110_0;
        if_110_1:
        line(1027);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byhand(4);
        if(!flag()) goto if_110_2;
        goto if_110_0;
        if_110_2:
        line(1030);
        if_110_3:
        if_110_0:;
    goto lab_106_1;
    lab_106_2:;
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
    line(1042);
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+0);//dirlist
    pop();
    line(1043);
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+1);//liblist
    pop();
    line(1044);
    string(L"BUILD_SHR");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+2);//sharing
    pop();
    line(1046);
    string(L"");
    assign(base+5);//txt
    pop();
    line(1047);
    line(1127);
    {
    line(1050);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_111_0:
    push_symbol(base+1);//liblist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_111_2;
        line(1054);
        line(1052);
        push_symbol(base+1);//liblist
        push_symbol(base+3);//n
        idxr();
        assign(base+6);//f0
        _clp_empty(1);
        if(!flag()) goto if_112_1;
            line(1053);
            goto lab_111_1;//loop
        if_112_1:
        if_112_0:;
        line(1066);
        line(1056);
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
        if(!flag()) goto if_113_1;
            line(1057);
            push_symbol(base+6);//f0
            assign(base+7);//f1
            pop();
            line(1058);
            push_symbol(base+6);//f0
            assign(base+8);//f2
            pop();
            line(1059);
            push_symbol(base+6);//f0
            assign(base+9);//f3
            pop();
        goto if_113_0;
        if_113_1:
        line(1060);
            line(1061);
            push_symbol(base+6);//f0
            string(L".lib");
            add();
            assign(base+7);//f1
            pop();
            line(1064);
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
            line(1065);
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
        if_113_2:
        if_113_0:;
        line(1118);
        {
        line(1068);
        push(&ONE);
        int sg=sign();
        push(&ZERO);
        assign(base+4);//i
        lab_114_0:
        push_symbol(base+0);//dirlist
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_114_2;
            line(1082);
            line(1070);
            push_symbol(base+4);//i
            push(&ZERO);
            lteq();
            if(!flag()) goto if_115_1;
                line(1071);
                push_symbol(base+7);//f1
                assign(base+10);//pf1
                pop();
                line(1072);
                push_symbol(base+8);//f2
                assign(base+11);//pf2
                pop();
                line(1073);
                push_symbol(base+9);//f3
                assign(base+12);//pf3
                pop();
            goto if_115_0;
            if_115_1:
            line(1074);
                line(1077);
                line(1075);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_empty(1);
                if(!flag()) goto if_116_1;
                    line(1076);
                    goto lab_114_1;//loop
                if_116_1:
                if_116_0:;
                line(1079);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+7);//f1
                add();
                assign(base+10);//pf1
                pop();
                line(1080);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+8);//f2
                add();
                assign(base+11);//pf2
                pop();
                line(1081);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+9);//f3
                add();
                assign(base+12);//pf3
                pop();
            if_115_2:
            if_115_0:;
            line(1117);
            line(1088);
            string(L"static");
            push_symbol(base+2);//sharing
            ss();
            if(!flag()) goto if_117_1;
                line(1101);
                line(1092);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_118_1;
                    line(1093);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1094);
                    goto lab_114_2;//exit
                goto if_118_0;
                if_118_1:
                line(1095);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_118_2;
                    line(1096);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1097);
                    goto lab_114_2;//exit
                goto if_118_0;
                if_118_2:
                line(1098);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_118_3;
                    line(1099);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1100);
                    goto lab_114_2;//exit
                if_118_3:
                if_118_0:;
            goto if_117_0;
            if_117_1:
            line(1103);
                line(1116);
                line(1107);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_119_1;
                    line(1108);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1109);
                    goto lab_114_2;//exit
                goto if_119_0;
                if_119_1:
                line(1110);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_119_2;
                    line(1111);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1112);
                    goto lab_114_2;//exit
                goto if_119_0;
                if_119_2:
                line(1113);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_119_3;
                    line(1114);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1115);
                    goto lab_114_2;//exit
                if_119_3:
                if_119_0:;
            if_117_2:
            if_117_0:;
        lab_114_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+4);//i
        add();
        assign(base+4);//i
        goto lab_114_0;
        lab_114_2:;
        }
        line(1126);
        line(1120);
        push_symbol(base+4);//i
        push_symbol(base+0);//dirlist
        _clp_len(1);
        gt();
        if(!flag()) goto if_120_1;
            line(1125);
            line(1121);
            push_symbol(base+6);//f0
            push(&ONE);
            number(2);
            slice();
            string(L"-l");
            eqeq();
            if(!flag()) goto if_121_1;
                line(1122);
                push_symbol(base+5);//txt
                push_symbol(base+6);//f0
                string(L" ");
                add();
                add();
                assign(base+5);//txt
                pop();
            goto if_121_0;
            if_121_1:
            line(1123);
                line(1124);
                push_symbol(base+5);//txt
                string(L"-l");
                push_symbol(base+6);//f0
                add();
                string(L" ");
                add();
                add();
                assign(base+5);//txt
                pop();
            if_121_2:
            if_121_0:;
        if_120_1:
        if_120_0:;
    lab_111_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_111_0;
    lab_111_2:;
    }
    line(1129);
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
    line(1134);
    line(1141);
    {
    line(1136);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_122_0:
    push_symbol(base+0);//dirlist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_122_2;
        line(1137);
        push_symbol(base+0);//dirlist
        push_symbol(base+2);//n
        idxr();
        _clp_dirsep(0);
        add();
        push_symbol(base+1);//fnamext
        add();
        assign(base+3);//pathname
        pop();
        line(1140);
        line(1138);
        push_symbol(base+3);//pathname
        _clp_file(1);
        if(!flag()) goto if_123_1;
            line(1139);
            push_symbol(base+3);//pathname
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_123_1:
        if_123_0:;
    lab_122_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_122_0;
    lab_122_2:;
    }
    line(1142);
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
    line(1153);
    push_symbol(base+0);//fil
    _clp_fname(1);
    assign(base+4);//f
    pop();
    line(1154);
    push_symbol(base+0);//fil
    _clp_fext(1);
    assign(base+5);//e
    pop();
    line(1155);
    line(1156);
    line(1157);
    line(1158);
    push(&FALSE);
    assign(base+11);//result
    pop();
    line(1164);
    line(1160);
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
    if(!flag()) goto if_124_1;
        line(1163);
        push(&FALSE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_124_1:
    if_124_0:;
    line(1191);
    {
    line(1166);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//i
    lab_125_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_125_2;
        line(1190);
        line(1168);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+9);//i
        idxr();
        idxr0(2);
        push_symbol(base+5);//e
        eqeq();
        if(!flag()) goto if_126_1;
            line(1170);
            push_symbol(_st_s_rules_ptr());//global
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            assign(base+8);//e0
            pop();
            line(1189);
            line(1175);
            push(&NIL);
            push_symbol(_st_resource_hash_ptr());//global
            push_symbol(base+4);//f
            push_symbol(base+8);//e0
            add();
            idxr();
            assign(base+7);//r
            neeq();
            if(!flag()) goto if_127_1;
                line(1176);
                push_symbol(base+7);//r
                _clp_fpath(1);
                assign(base+6);//p
                pop();
                line(1177);
                push_symbol(base+1);//dep
                push_symbol(base+6);//p
                push_symbol(base+4);//f
                add();
                push_symbol(base+5);//e
                add();
                _clp_adddep(2);
                pop();
                line(1187);
                line(1178);
                push(&ZERO);
                push_symbol(base+3);//todo
                push_symbol_ref(base+6);//p
                push_symbol_ref(base+4);//f
                push_symbol_ref(base+5);//e
                block(_blk_byrules_0,3);
                _clp_ascan(2);
                assign(base+10);//x
                eqeq();
                if(!flag()) goto if_128_1;
                    line(1179);
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
                goto if_128_0;
                if_128_1:
                line(1180);
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
                if(!flag()) goto if_128_2;
                    line(1181);
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
                if_128_2:
                if_128_0:;
                line(1188);
                push(&TRUE);
                assign(base+11);//result
                pop();
            if_127_1:
            if_127_0:;
        if_126_1:
        if_126_0:;
    lab_125_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//i
    add();
    assign(base+9);//i
    goto lab_125_0;
    lab_125_2:;
    }
    line(1192);
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
    if(!flag()) goto if_129_1;
        line(1206);
        push_symbol(base+1);//dep
        push_symbol(base+4);//pn
        _clp_adddep(2);
        pop();
        line(1207);
        push(&TRUE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_129_1:
    if_129_0:;
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
    if(!flag()) goto if_130_1;
        line(1215);
        push_symbol(base+0);//dep
        push_symbol(base+1);//x
        _clp_aadd(2);
        pop();
    if_130_1:
    if_130_0:;
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
    lab_131_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_131_2;
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
        if(!flag()) goto if_132_1;
            line(1231);
            push_symbol(base+2);//n
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_132_1:
        if_132_0:;
    lab_131_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_131_0;
    lab_131_2:;
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
    lab_133_0:
    push_symbol(base+1);//sep
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_133_2;
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
        if(!flag()) goto if_134_1;
            line(1245);
            goto lab_133_2;//exit
        goto if_134_0;
        if_134_1:
        line(1246);
            line(1247);
            push(&NIL);
            assign(base+3);//s
            pop();
        if_134_2:
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
    lab_135_0:
    push_symbol(base+0);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_135_2;
        line(1269);
        {
        line(1262);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+1);//i
        lab_136_0:
        push_symbol(base+0);//todo
        push_symbol(base+2);//n
        idxr();
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_136_2;
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
            if(!flag()) goto if_137_1;
                line(1266);
                push_symbol(base+3);//x
                number(3);
                _clp_substr(2);
                assign(base+3);//x
                pop();
            if_137_1:
            if_137_0:;
            line(1268);
            push_symbol(base+3);//x
            push_symbol(base+0);//todo
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+1);//i
            assign2(idxxl());
            pop();
        lab_136_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+1);//i
        add();
        assign(base+1);//i
        goto lab_136_0;
        lab_136_2:;
        }
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
    line(1276);
    push(&FALSE);
    assign(base+2);//update
    pop();
    line(1277);
    push_symbol(base+1);//depend
    _clp_ftime(1);
    assign(base+3);//tdepend
    pop();
    line(1291);
    line(1279);
    push_symbol(base+3);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_138_1;
        line(1287);
        line(1280);
        push_symbol(_st_s_dry_ptr());//global
        if(!flag()) goto if_139_1;
            line(1281);
            string(L"");
            assign(base+3);//tdepend
            pop();
        goto if_139_0;
        if_139_1:
        line(1282);
            line(1283);
            push_symbol(base+1);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(1284);
            _clp_qout(0);
            pop();
            line(1285);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(1286);
            _clp___quit(0);
            pop();
        if_139_2:
        if_139_0:;
    goto if_138_0;
    if_138_1:
    line(1289);
    push_symbol(base+0);//ttarget
    push_symbol(base+3);//tdepend
    lt();
    if(!flag()) goto if_138_2;
        line(1290);
        push(&TRUE);
        assign(base+2);//update
        pop();
    if_138_2:
    if_138_0:;
    line(1295);
    line(1293);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_140_1;
        line(1294);
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
    if_140_1:
    if_140_0:;
    line(1297);
    push_symbol(base+2);//update
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

