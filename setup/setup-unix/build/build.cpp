
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

//input: build.ppo (5.0.18)

#include <cccdef.h>

static void _blk_adddep_0(int argno);
static void _blk_build_0(int argno);
static void _blk_build_1(int argno);
static void _blk_byrules_0(int argno);
extern void _clp___quit(int argno);
extern void _clp_aadd(int argno);
extern void _clp_aclone(int argno);
static void _clp_adddep(int argno);
extern void _clp_ains(int argno);
extern void _clp_alltrim(int argno);
extern void _clp_argv(int argno);
extern void _clp_ascan(int argno);
extern void _clp_asort(int argno);
extern void _clp_at(int argno);
static void _clp_build(int argno);
static void _clp_byhand(int argno);
static void _clp_byrules(int argno);
extern void _clp_chr(int argno);
extern void _clp_directory(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_dtos(int argno);
extern void _clp_empty(int argno);
extern void _clp_errorlevel(int argno);
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
extern void _clp_run(int argno);
static void _clp_run1(int argno);
static void _clp_search_file(int argno);
static void _clp_search_include(int argno);
static void _clp_search_library(int argno);
extern void _clp_split(int argno);
extern void _clp_strtran(int argno);
extern void _clp_substr(int argno);
static void _clp_usage(int argno);
static void _clp_xsplit(int argno);
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
MUTEX_CREATE(_mutex_s_primary);
static VALUE* _st_s_primary_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_s_primary);
    static stvar _st_s_primary(L".y.lem.lex.prg.cpp.c.asm.");
    MUTEX_UNLOCK(_mutex_s_primary);
    SIGNAL_UNLOCK();
    return _st_s_primary.ptr;
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
    string(L".asm");
    string(L".obj");
    array(2);
    string(L".c");
    string(L".obj");
    array(2);
    string(L".cpp");
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
    string(L".obj");
    string(L".lib");
    array(2);
    string(L".obj");
    string(L".exe");
    array(2);
    array(18);
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
    line(66);
    _clp_argv(0);
    _clp_aclone(1);
    assign(base+0);//opt
    pop();
    line(74);
    line(71);
    push_symbol(_st_s_quiet_ptr());//global
    topnot();
    if(!flag()) goto if_1_1;
        line(72);
        string(nls_text(L"CCC Program Builder "));
        string(L"1.3.03");
        add();
        string(L" Copyright (C) ComFirm Bt.");
        add();
        _clp_qqout(1);
        pop();
        line(73);
        _clp_qout(0);
        pop();
    if_1_1:
    if_1_0:;
    line(159);
    {
    line(77);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_2_0:
    push_symbol(base+0);//opt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_2_2;
        line(78);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        _clp_procpar(1);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        assign2(idxxl());
        pop();
        line(158);
        line(80);
        string(L"-l");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_1;
            line(81);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_libnam_ptr());//global
            pop();
            line(82);
            push(&FALSE);
            assign(_st_s_shared_ptr());//global
            pop();
        goto if_3_0;
        if_3_1:
        line(85);
        string(L"-s");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_2;
            line(86);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_libnam_ptr());//global
            pop();
            line(87);
            push(&TRUE);
            assign(_st_s_shared_ptr());//global
            pop();
        goto if_3_0;
        if_3_2:
        line(90);
        string(L"-d");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_3;
            line(95);
            line(91);
            push_symbol(_st_s_srcdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_4_1;
                line(92);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_srcdir_ptr());//global
                pop();
            goto if_4_0;
            if_4_1:
            line(93);
                line(94);
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
        line(98);
        string(L"-i");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_4;
            line(103);
            line(99);
            push_symbol(_st_s_incdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_5_1;
                line(100);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_incdir_ptr());//global
                pop();
            goto if_5_0;
            if_5_1:
            line(101);
                line(102);
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
        line(106);
        string(L"-p");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_5;
            line(111);
            line(107);
            push_symbol(_st_s_libdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_6_1;
                line(108);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_libdir_ptr());//global
                pop();
            goto if_6_0;
            if_6_1:
            line(109);
                line(110);
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
        line(114);
        string(L"-b");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_6;
            line(119);
            line(115);
            push_symbol(_st_s_libfil_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_7_1;
                line(116);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_libfil_ptr());//global
                pop();
            goto if_7_0;
            if_7_1:
            line(117);
                line(118);
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
        line(122);
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
            line(127);
            line(123);
            push_symbol(_st_s_main_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_8_1;
                line(124);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_main_ptr());//global
                pop();
            goto if_8_0;
            if_8_1:
            line(125);
                line(126);
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
        line(130);
        string(L"-h");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_8;
            line(131);
            _clp_usage(0);
            pop();
            line(132);
            _clp___quit(0);
            pop();
        goto if_3_0;
        if_3_8:
        line(134);
        string(L"-q");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_9;
            line(135);
            push(&TRUE);
            assign(_st_s_quiet_ptr());//global
            pop();
        goto if_3_0;
        if_3_9:
        line(137);
        string(L"-v");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_10;
            line(138);
            push(&TRUE);
            assign(_st_s_version_ptr());//global
            pop();
        goto if_3_0;
        if_3_10:
        line(140);
        string(L"--debug");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        if(!flag()) goto if_3_11;
            line(141);
            push(&TRUE);
            assign(_st_s_debug_ptr());//global
            pop();
        goto if_3_0;
        if_3_11:
        line(143);
        string(L"--dry");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        if(!flag()) goto if_3_12;
            line(144);
            push(&TRUE);
            assign(_st_s_debug_ptr());//global
            pop();
            line(145);
            push(&TRUE);
            assign(_st_s_dry_ptr());//global
            pop();
        goto if_3_0;
        if_3_12:
        line(147);
        string(L"@");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        push(&ONE);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_13;
            line(148);
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
        if_3_13:
        line(150);
        string(L"=");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        ss();
        if(!flag()) goto if_3_14;
            line(151);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_putenv(1);
            pop();
        goto if_3_0;
        if_3_14:
        line(153);
            line(154);
            string(nls_text(L"Invalid switch: "));
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_qout(2);
            pop();
            line(155);
            _clp_usage(0);
            pop();
            line(156);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(157);
            _clp___quit(0);
            pop();
        if_3_15:
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
    line(164);
    line(162);
    string(L"on");
    string(L"BUILD_DBG");
    _clp_getenv(1);
    _clp_lower(1);
    ss();
    if(!flag()) goto if_9_1;
        line(163);
        push(&TRUE);
        assign(_st_s_debug_ptr());//global
        pop();
    if_9_1:
    if_9_0:;
    line(167);
    line(165);
    string(L"debug");
    string(L"BUILD_DBG");
    _clp_getenv(1);
    _clp_lower(1);
    ss();
    if(!flag()) goto if_10_1;
        line(166);
        push(&TRUE);
        assign(_st_s_debug_ptr());//global
        pop();
    if_10_1:
    if_10_0:;
    line(171);
    line(168);
    string(L"dry");
    string(L"BUILD_DBG");
    _clp_getenv(1);
    _clp_lower(1);
    ss();
    if(!flag()) goto if_11_1;
        line(169);
        push(&TRUE);
        assign(_st_s_debug_ptr());//global
        pop();
        line(170);
        push(&TRUE);
        assign(_st_s_dry_ptr());//global
        pop();
    if_11_1:
    if_11_0:;
    line(175);
    line(173);
    push_symbol(_st_s_version_ptr());//global
    if(!flag()) goto if_12_1;
        line(174);
        _clp___quit(0);
        pop();
    if_12_1:
    if_12_0:;
    line(177);
    _clp_root(0);
    pop();
    line(178);
    _clp_params(0);
    pop();
    line(179);
    _clp_build(0);
    pop();
    line(181);
    _clp_qout(0);
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
    line(186);
    push_symbol(base+0);//parfil
    _clp_memoread(1);
    assign(base+3);//par
    pop();
    line(193);
    line(188);
    push_symbol(base+3);//par
    _clp_empty(1);
    if(!flag()) goto if_13_1;
        line(192);
        string(L"BUILD_BAT");
        _clp_getenv(1);
        _clp_dirsep(0);
        add();
        push_symbol(base+0);//parfil
        add();
        _clp_memoread(1);
        assign(base+3);//par
        pop();
    if_13_1:
    if_13_0:;
    line(201);
    line(195);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_14_1;
        line(200);
        line(196);
        push_symbol(base+3);//par
        _clp_empty(1);
        if(!flag()) goto if_15_1;
            line(197);
            string(L"Build parfile empty:");
            push_symbol(base+0);//parfil
            _clp_qqout(2);
            pop();
            _clp_qout(0);
            pop();
        goto if_15_0;
        if_15_1:
        line(198);
            line(199);
            string(L"Build parfile:");
            push_symbol(base+0);//parfil
            _clp_qqout(2);
            pop();
            _clp_qout(0);
            pop();
        if_15_2:
        if_15_0:;
    if_14_1:
    if_14_0:;
    line(203);
    push_symbol(base+3);//par
    number(13);
    _clp_chr(1);
    string(L"");
    _clp_strtran(3);
    assign(base+3);//par
    pop();
    line(204);
    push_symbol(base+3);//par
    number(10);
    _clp_chr(1);
    _clp_split(2);
    assign(base+3);//par
    pop();
    line(220);
    {
    line(206);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_16_0:
    push_symbol(base+3);//par
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_16_2;
        line(207);
        push_symbol(base+3);//par
        push_symbol(base+4);//n
        idxr();
        assign(base+5);//p
        pop();
        line(210);
        line(208);
        string(L"#");
        push_symbol(base+5);//p
        ss();
        if(!flag()) goto if_17_1;
            line(209);
            push_symbol(base+5);//p
            string(L"#");
            push_symbol(base+5);//p
            _clp_at(2);
            addnum(-1);
            _clp_left(2);
            assign(base+5);//p
            pop();
        if_17_1:
        if_17_0:;
        line(212);
        push_symbol(base+5);//p
        string(L" ");
        _clp_split(2);
        assign(base+5);//p
        pop();
        line(219);
        {
        line(213);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+6);//i
        lab_18_0:
        push_symbol(base+5);//p
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_18_2;
            line(218);
            line(214);
            push_symbol(base+5);//p
            push_symbol(base+6);//i
            idxr();
            _clp_empty(1);
            topnot();
            if(!flag()) goto if_19_1;
                line(215);
                push_symbol(base+1);//opt
                push(&NIL);
                _clp_aadd(2);
                pop();
                line(216);
                push_symbol(base+1);//opt
                push_symbol(base+2);//optx
                push(&ONE);
                add();
                assign(base+2);//optx
                _clp_ains(2);
                pop();
                line(217);
                push_symbol(base+5);//p
                push_symbol(base+6);//i
                idxr();
                push_symbol(base+1);//opt
                push_symbol(base+2);//optx
                assign2(idxxl());
                pop();
            if_19_1:
            if_19_0:;
        lab_18_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+6);//i
        add();
        assign(base+6);//i
        goto lab_18_0;
        lab_18_2:;
        }
    lab_16_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_16_0;
    lab_16_2:;
    }
    line(221);
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
    line(225);
    line(234);
    lab_20_1:
    line(227);
    push(&ZERO);
    string(L"$$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_20_2;
        line(228);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(229);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(3);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(230);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(231);
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
        line(232);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(233);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_20_1;
    lab_20_2:;
    line(243);
    lab_21_1:
    line(236);
    push(&ZERO);
    string(L"$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_21_2;
        line(237);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(238);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(2);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(239);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(240);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        _clp_getenv(1);
        add();
        assign(base+2);//p
        pop();
        line(241);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(242);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_21_1;
    lab_21_2:;
    line(245);
    push_symbol(base+0);//par
    string(L"\\");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(246);
    push_symbol(base+0);//par
    string(L"/");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(248);
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
    line(253);
    string(nls_text(L"BUILD -xExeNam|-lLibNam -dSrcDir -iIncDir -pLibDir -bLibFil -mMain"));
    _clp_qout(1);
    pop();
    line(254);
    _clp_qout(0);
    pop();
    line(255);
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
    line(261);
    line(298);
    line(263);
    string(L"BUILD_SRC");
    _clp_getenv(1);
    assign(base+0);//srcroot
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_22_1;
        line(267);
        line(265);
        push_symbol(base+0);//srcroot
        push(&ONE);
        _clp_right(2);
        string(L"/\\");
        ss();
        topnot();
        if(!flag()) goto if_23_1;
            line(266);
            push_symbol(base+0);//srcroot
            _clp_dirsep(0);
            add();
            assign(base+0);//srcroot
            pop();
        if_23_1:
        if_23_0:;
        line(271);
        line(269);
        push_symbol(_st_s_srcdir_ptr());//global
        push(&NIL);
        eqeq();
        if(!flag()) goto if_24_1;
            line(270);
            string(L".");
            assign(_st_s_srcdir_ptr());//global
            pop();
        if_24_1:
        if_24_0:;
        line(273);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+1);//d
        pop();
        line(275);
        string(L"");
        assign(_st_s_srcdir_ptr());//global
        pop();
        line(282);
        {
        line(276);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+2);//n
        lab_25_0:
        push_symbol(base+1);//d
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_25_2;
            line(281);
            line(277);
            push_symbol(base+1);//d
            push_symbol(base+2);//n
            idxr();
            push(&ONE);
            _clp_left(2);
            string(L"/\\");
            ss();
            if(!flag()) goto if_26_1;
                line(278);
                push_symbol(_st_s_srcdir_ptr());//global
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                string(L";");
                add();
                add();
                assign(_st_s_srcdir_ptr());//global
                pop();
            goto if_26_0;
            if_26_1:
            line(279);
                line(280);
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
            if_26_2:
            if_26_0:;
        lab_25_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+2);//n
        add();
        assign(base+2);//n
        goto lab_25_0;
        lab_25_2:;
        }
        line(297);
        line(285);
        push_symbol(_st_s_incdir_ptr());//global
        push(&NIL);
        neeq();
        if(!flag()) goto if_27_1;
            line(287);
            push_symbol(_st_s_incdir_ptr());//global
            string(L",;");
            _clp_xsplit(2);
            assign(base+1);//d
            pop();
            line(289);
            string(L"");
            assign(_st_s_incdir_ptr());//global
            pop();
            line(296);
            {
            line(290);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+2);//n
            lab_28_0:
            push_symbol(base+1);//d
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_28_2;
                line(295);
                line(291);
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                push(&ONE);
                _clp_left(2);
                string(L"/\\");
                ss();
                if(!flag()) goto if_29_1;
                    line(292);
                    push_symbol(_st_s_incdir_ptr());//global
                    push_symbol(base+1);//d
                    push_symbol(base+2);//n
                    idxr();
                    string(L";");
                    add();
                    add();
                    assign(_st_s_incdir_ptr());//global
                    pop();
                goto if_29_0;
                if_29_1:
                line(293);
                    line(294);
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
                if_29_2:
                if_29_0:;
            lab_28_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+2);//n
            add();
            assign(base+2);//n
            goto lab_28_0;
            lab_28_2:;
            }
        if_27_1:
        if_27_0:;
    if_22_1:
    if_22_0:;
    line(300);
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
    line(306);
    line(319);
    string(L"");
    assign(base+0);//txt
    pop();
    line(320);
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
    line(321);
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
    line(322);
    push_symbol(base+0);//txt
    string(L"BUILD_INC");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(323);
    push_symbol(base+0);//txt
    string(L"include");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(324);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(325);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(327);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(329);
    string(L"BUILD_INC=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(335);
    string(L"");
    assign(base+0);//txt
    pop();
    line(336);
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
    line(337);
    push_symbol(base+0);//txt
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(338);
    push_symbol(base+0);//txt
    string(L"lib");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(339);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(340);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(342);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(344);
    string(L"BUILD_LPT=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(350);
    string(L"");
    assign(base+0);//txt
    pop();
    line(351);
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
    line(352);
    push_symbol(base+0);//txt
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(353);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(354);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(355);
    string(L"BUILD_LIB=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(358);
    line(356);
    push_symbol(_st_s_libabs_ptr());//global
    if(!flag()) goto if_30_1;
        line(357);
        string(L"BUILD_LIB=");
        _clp_search_library(0);
        add();
        _clp_putenv(1);
        pop();
    if_30_1:
    if_30_0:;
    line(361);
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
    line(367);
    array(0);
    assign(base+0);//dir
    pop();
    line(368);
    array(0);
    assign(base+1);//obj
    pop();
    line(369);
    array(0);
    assign(base+2);//lib
    pop();
    line(370);
    array(0);
    assign(base+3);//mmd
    pop();
    line(371);
    array(0);
    assign(base+4);//todo
    pop();
    line(373);
    line(378);
    line(376);
    push_symbol(_st_s_main_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_31_1;
        line(377);
        push_symbol(_st_s_main_ptr());//global
        _clp_lower(1);
        string(L",;");
        _clp_xsplit(2);
        assign(base+3);//mmd
        pop();
    if_31_1:
    if_31_0:;
    line(385);
    line(381);
    push_symbol(_st_s_srcdir_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_32_1;
        line(382);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+0);//dir
        pop();
    goto if_32_0;
    if_32_1:
    line(383);
        line(384);
        string(L".");
        array(1);
        assign(base+0);//dir
        pop();
    if_32_2:
    if_32_0:;
    line(401);
    {
    line(387);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_33_0:
    push_symbol(base+0);//dir
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_33_2;
        line(389);
        string(L"");
        push_symbol(base+0);//dir
        push_symbol(base+8);//n
        idxr();
        _clp_qqout(2);
        pop();
        line(391);
        push_symbol(base+0);//dir
        push_symbol(base+8);//n
        idxr();
        _clp_dirsep(0);
        add();
        string(L"*.*");
        add();
        _clp_directory(1);
        assign(base+5);//d1
        pop();
        line(400);
        {
        line(393);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//i
        lab_34_0:
        push_symbol(base+5);//d1
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_34_2;
            line(395);
            push_symbol(base+5);//d1
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            _clp_lower(1);
            assign(base+6);//f
            pop();
            line(399);
            line(397);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            push_symbol(_st_s_primary_ptr());//global
            ss();
            if(!flag()) goto if_35_1;
                line(398);
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
            if_35_1:
            if_35_0:;
        lab_34_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//i
        add();
        assign(base+9);//i
        goto lab_34_0;
        lab_34_2:;
        }
    lab_33_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_33_0;
    lab_33_2:;
    }
    line(402);
    _clp_qout(0);
    pop();
    line(438);
    {
    line(407);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_36_0:
    push_symbol(base+1);//obj
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_36_2;
        line(409);
        push_symbol(base+1);//obj
        push_symbol(base+8);//n
        idxr();
        assign(base+6);//f
        pop();
        line(410);
        push_symbol(base+6);//f
        _clp_fname(1);
        assign(base+7);//o
        pop();
        line(411);
        push_symbol(base+6);//f
        _clp_memoread(1);
        assign(base+10);//txt
        pop();
        line(421);
        line(413);
        push(&ZERO);
        push_symbol(base+3);//mmd
        push_symbol_ref(base+7);//o
        block(_blk_build_0,1);
        _clp_ascan(2);
        neeq();
        if(!flag()) goto if_37_1;
        goto if_37_0;
        if_37_1:
        line(415);
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
        if(!flag()) goto if_37_2;
            line(418);
            line(416);
            push_symbol(_st_s_main_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_38_1;
                line(417);
                push_symbol(base+3);//mmd
                push_symbol(base+7);//o
                _clp_aadd(2);
                pop();
            if_38_1:
            if_38_0:;
        goto if_37_0;
        if_37_2:
        line(419);
            line(420);
            push_symbol(base+2);//lib
            push_symbol(base+7);//o
            _clp_aadd(2);
            pop();
        if_37_3:
        if_37_0:;
        line(423);
        push_symbol(base+7);//o
        string(L".obj");
        add();
        push_symbol(base+6);//f
        array(2);
        assign(base+11);//dep
        pop();
        line(435);
        {
        line(424);
        push(&ONE);
        int sg=sign();
        number(2);
        assign(base+9);//i
        lab_39_0:
        push_symbol(base+11);//dep
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_39_2;
            line(433);
            line(425);
            push_symbol(base+9);//i
            number(2);
            eqeq();
            if(!flag()) goto if_40_1;
            goto if_40_0;
            if_40_1:
            line(427);
            push_symbol(base+9);//i
            number(128);
            gt();
            if(!flag()) goto if_40_2;
                line(428);
                string(L"recursive dependencies:");
                push_symbol(base+11);//dep
                _clp_qout(2);
                pop();
                line(429);
                _clp_qout(0);
                pop();
                line(430);
                _clp___quit(0);
                pop();
            goto if_40_0;
            if_40_2:
            line(431);
                line(432);
                push_symbol(base+11);//dep
                push_symbol(base+9);//i
                idxr();
                _clp_memoread(1);
                assign(base+10);//txt
                pop();
            if_40_3:
            if_40_0:;
            line(434);
            push_symbol(base+10);//txt
            push_symbol(base+11);//dep
            push_symbol(base+0);//dir
            push_symbol(base+4);//todo
            _clp_search_include(4);
            pop();
        lab_39_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//i
        add();
        assign(base+9);//i
        goto lab_39_0;
        lab_39_2:;
        }
        line(437);
        push_symbol(base+4);//todo
        push_symbol(base+11);//dep
        _clp_aadd(2);
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
    line(440);
    push_symbol(base+4);//todo
    _clp_normalize(1);
    pop();
    line(442);
    push_symbol(base+4);//todo
    push(&NIL);
    push(&NIL);
    block(_blk_build_1,0);
    _clp_asort(4);
    pop();
    line(454);
    line(446);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_41_1;
        line(447);
        string(L"main:");
        push_symbol(base+3);//mmd
        _clp_qout(2);
        pop();
        line(448);
        string(L"lib :");
        push_symbol(base+2);//lib
        _clp_qout(2);
        pop();
        line(449);
        _clp_qout(0);
        pop();
        line(452);
        {
        line(450);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_42_0:
        push_symbol(base+4);//todo
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_42_2;
            line(451);
            push_symbol(base+4);//todo
            push_symbol(base+8);//n
            idxr();
            _clp_qout(1);
            pop();
        lab_42_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+8);//n
        add();
        assign(base+8);//n
        goto lab_42_0;
        lab_42_2:;
        }
        line(453);
        _clp_qout(0);
        pop();
    if_41_1:
    if_41_0:;
    line(458);
    {
    line(456);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_43_0:
    push_symbol(base+4);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_43_2;
        line(457);
        push_symbol(base+4);//todo
        push_symbol(base+8);//n
        idxr();
        _clp_makeobj(1);
        pop();
    lab_43_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_43_0;
    lab_43_2:;
    }
    line(477);
    line(462);
    push_symbol(_st_s_libnam_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_44_1;
        line(463);
        push_symbol(_st_s_libnam_ptr());//global
        push_symbol(base+2);//lib
        _clp_makelib(2);
        pop();
        line(467);
        line(465);
        push_symbol(_st_s_shared_ptr());//global
        push(&TRUE);
        eqeq();
        if(!flag()) goto if_45_1;
            line(466);
            push_symbol(_st_s_libnam_ptr());//global
            push_symbol(base+2);//lib
            _clp_makeso(2);
            pop();
        if_45_1:
        if_45_0:;
        line(471);
        {
        line(469);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_46_0:
        push_symbol(base+3);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_46_2;
            line(470);
            push_symbol(base+3);//mmd
            push_symbol(base+8);//n
            idxr();
            push_symbol(_st_s_libnam_ptr());//global
            _clp_makeexe1(2);
            pop();
        lab_46_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+8);//n
        add();
        assign(base+8);//n
        goto lab_46_0;
        lab_46_2:;
        }
    goto if_44_0;
    if_44_1:
    line(473);
        line(476);
        {
        line(474);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_47_0:
        push_symbol(base+3);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_47_2;
            line(475);
            push_symbol(base+3);//mmd
            push_symbol(base+8);//n
            idxr();
            push_symbol(base+2);//lib
            _clp_makeexe(2);
            pop();
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
    if_44_2:
    if_44_0:;
    line(479);
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
    line(486);
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
    line(487);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(488);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2so.bat");
    add();
    assign(base+7);//torun
    pop();
    line(489);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(496);
    line(491);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_48_1;
        line(492);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(493);
        _clp_qout(0);
        pop();
        line(494);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(495);
        _clp___quit(0);
        pop();
    if_48_1:
    if_48_0:;
    line(498);
    push_symbol(base+7);//torun
    string(L" lib");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(500);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(503);
    line(501);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_49_1;
        line(502);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_49_1:
    if_49_0:;
    line(507);
    line(505);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_50_1;
        line(506);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_50_1:
    if_50_0:;
    line(533);
    {
    line(509);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_51_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_51_2;
        line(511);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(512);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+4);//depend
        add();
        add();
        assign(base+7);//torun
        pop();
        line(513);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(514);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(528);
        line(516);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_52_1;
            line(524);
            line(517);
            push_symbol(_st_s_dry_ptr());//global
            if(!flag()) goto if_53_1;
                line(518);
                string(L"");
                assign(base+5);//tdepend
                pop();
            goto if_53_0;
            if_53_1:
            line(519);
                line(520);
                push_symbol(base+4);//depend
                string(nls_text(L"does not exist"));
                _clp_qout(2);
                pop();
                line(521);
                _clp_qout(0);
                pop();
                line(522);
                push(&ONE);
                _clp_errorlevel(1);
                pop();
                line(523);
                _clp___quit(0);
                pop();
            if_53_2:
            if_53_0:;
        goto if_52_0;
        if_52_1:
        line(526);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_52_2;
            line(527);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_52_2:
        if_52_0:;
        line(532);
        line(530);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_54_1;
            line(531);
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
        if_54_1:
        if_54_0:;
    lab_51_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_51_0;
    lab_51_2:;
    }
    line(537);
    line(535);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_55_1;
        line(536);
        _clp_qout(0);
        pop();
    if_55_1:
    if_55_0:;
    line(541);
    line(539);
    push_symbol(base+6);//update
    if(!flag()) goto if_56_1;
        line(540);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_56_1:
    if_56_0:;
    line(543);
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
    line(549);
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
    line(550);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(551);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2lib.bat");
    add();
    assign(base+7);//torun
    pop();
    line(552);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+8);//objdir
    pop();
    line(553);
    line(560);
    line(555);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_57_1;
        line(556);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(557);
        _clp_qout(0);
        pop();
        line(558);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(559);
        _clp___quit(0);
        pop();
    if_57_1:
    if_57_0:;
    line(562);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(564);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(567);
    line(565);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_58_1;
        line(566);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_58_1:
    if_58_0:;
    line(571);
    line(569);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_59_1;
        line(570);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_59_1:
    if_59_0:;
    line(596);
    {
    line(573);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_60_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_60_2;
        line(575);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(576);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(577);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(591);
        line(579);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_61_1;
            line(587);
            line(580);
            push_symbol(_st_s_dry_ptr());//global
            if(!flag()) goto if_62_1;
                line(581);
                string(L"");
                assign(base+5);//tdepend
                pop();
            goto if_62_0;
            if_62_1:
            line(582);
                line(583);
                push_symbol(base+4);//depend
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
            if_62_2:
            if_62_0:;
        goto if_61_0;
        if_61_1:
        line(589);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_61_2;
            line(590);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_61_2:
        if_61_0:;
        line(595);
        line(593);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_63_1;
            line(594);
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
        if_63_1:
        if_63_0:;
    lab_60_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_60_0;
    lab_60_2:;
    }
    line(600);
    line(598);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_64_1;
        line(599);
        _clp_qout(0);
        pop();
    if_64_1:
    if_64_0:;
    line(627);
    line(602);
    push_symbol(base+6);//update
    if(!flag()) goto if_65_1;
        line(607);
        {
        line(605);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_66_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_66_2;
            line(606);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
            pop();
        lab_66_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_66_0;
        lab_66_2:;
        }
        line(626);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_65_1:
    if_65_0:;
    line(629);
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
    line(635);
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
    line(636);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(637);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2exe.bat");
    add();
    assign(base+7);//torun
    pop();
    line(638);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+8);//objdir
    pop();
    line(639);
    line(646);
    line(641);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_67_1;
        line(642);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(643);
        _clp_qout(0);
        pop();
        line(644);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(645);
        _clp___quit(0);
        pop();
    if_67_1:
    if_67_0:;
    line(648);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(651);
    line(649);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_68_1;
        line(650);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_68_1:
    if_68_0:;
    line(655);
    line(653);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_69_1;
        line(654);
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
    line(684);
    {
    line(657);
    push(&ONE);
    int sg=sign();
    push(&ZERO);
    assign(base+9);//n
    lab_70_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_70_2;
        line(663);
        line(659);
        push_symbol(base+9);//n
        push(&ZERO);
        eqeq();
        if(!flag()) goto if_71_1;
            line(660);
            push_symbol(base+0);//exenam
            assign(base+4);//depend
            pop();
        goto if_71_0;
        if_71_1:
        line(661);
            line(662);
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
        if_71_2:
        if_71_0:;
        line(665);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(666);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(679);
        line(668);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_72_1;
            line(676);
            line(669);
            push_symbol(_st_s_dry_ptr());//global
            if(!flag()) goto if_73_1;
                line(670);
                string(L"");
                assign(base+5);//tdepend
                pop();
            goto if_73_0;
            if_73_1:
            line(671);
                line(672);
                push_symbol(base+4);//depend
                string(nls_text(L"does not exist"));
                _clp_qout(2);
                pop();
                line(673);
                _clp_qout(0);
                pop();
                line(674);
                push(&ONE);
                _clp_errorlevel(1);
                pop();
                line(675);
                _clp___quit(0);
                pop();
            if_73_2:
            if_73_0:;
        goto if_72_0;
        if_72_1:
        line(677);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_72_2;
            line(678);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_72_2:
        if_72_0:;
        line(683);
        line(681);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_74_1;
            line(682);
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
        if_74_1:
        if_74_0:;
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
    line(688);
    line(686);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_75_1;
        line(687);
        _clp_qout(0);
        pop();
    if_75_1:
    if_75_0:;
    line(721);
    line(690);
    push_symbol(base+6);//update
    if(!flag()) goto if_76_1;
        line(691);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+0);//exenam
        add();
        add();
        assign(base+7);//torun
        pop();
        line(696);
        {
        line(694);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_77_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_77_2;
            line(695);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
            pop();
        lab_77_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_77_0;
        lab_77_2:;
        }
        line(720);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_76_1:
    if_76_0:;
    line(723);
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
    line(729);
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
    line(730);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(731);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"lib2exe.bat");
    add();
    assign(base+7);//torun
    pop();
    line(732);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(739);
    line(734);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_78_1;
        line(735);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(736);
        _clp_qout(0);
        pop();
        line(737);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(738);
        _clp___quit(0);
        pop();
    if_78_1:
    if_78_0:;
    line(741);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(744);
    line(742);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_79_1;
        line(743);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_79_1:
    if_79_0:;
    line(748);
    line(746);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_80_1;
        line(747);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_80_1:
    if_80_0:;
    line(751);
    push_symbol(base+0);//mmod
    assign(base+4);//depend
    pop();
    line(752);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(753);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".obj");
    add();
    assign(base+4);//depend
    pop();
    line(754);
    push_symbol(base+4);//depend
    _clp_ftime(1);
    assign(base+5);//tdepend
    pop();
    line(767);
    line(756);
    push_symbol(base+5);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_81_1;
        line(764);
        line(757);
        push_symbol(_st_s_dry_ptr());//global
        if(!flag()) goto if_82_1;
            line(758);
            string(L"");
            assign(base+5);//tdepend
            pop();
        goto if_82_0;
        if_82_1:
        line(759);
            line(760);
            push_symbol(base+4);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(761);
            _clp_qout(0);
            pop();
            line(762);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(763);
            _clp___quit(0);
            pop();
        if_82_2:
        if_82_0:;
    goto if_81_0;
    if_81_1:
    line(765);
    push_symbol(base+3);//ttarget
    push_symbol(base+5);//tdepend
    lt();
    if(!flag()) goto if_81_2;
        line(766);
        push(&TRUE);
        assign(base+6);//update
        pop();
    if_81_2:
    if_81_0:;
    line(771);
    line(769);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_83_1;
        line(770);
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
    if_83_1:
    if_83_0:;
    line(774);
    push_symbol(base+1);//libnam
    assign(base+4);//depend
    pop();
    line(775);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(776);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".lib");
    add();
    assign(base+4);//depend
    pop();
    line(777);
    push_symbol(base+4);//depend
    _clp_ftime(1);
    assign(base+5);//tdepend
    pop();
    line(790);
    line(779);
    push_symbol(base+5);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_84_1;
        line(787);
        line(780);
        push_symbol(_st_s_dry_ptr());//global
        if(!flag()) goto if_85_1;
            line(781);
            string(L"");
            assign(base+5);//tdepend
            pop();
        goto if_85_0;
        if_85_1:
        line(782);
            line(783);
            push_symbol(base+4);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(784);
            _clp_qout(0);
            pop();
            line(785);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(786);
            _clp___quit(0);
            pop();
        if_85_2:
        if_85_0:;
    goto if_84_0;
    if_84_1:
    line(788);
    push_symbol(base+3);//ttarget
    push_symbol(base+5);//tdepend
    lt();
    if(!flag()) goto if_84_2;
        line(789);
        push(&TRUE);
        assign(base+6);//update
        pop();
    if_84_2:
    if_84_0:;
    line(794);
    line(792);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_86_1;
        line(793);
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
    if_86_1:
    if_86_0:;
    line(799);
    line(797);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_87_1;
        line(798);
        _clp_qout(0);
        pop();
    if_87_1:
    if_87_0:;
    line(803);
    line(801);
    push_symbol(base+6);//update
    if(!flag()) goto if_88_1;
        line(802);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_88_1:
    if_88_0:;
    line(805);
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
    line(811);
    push_symbol(base+0);//deplist
    idxr0(1);
    assign(base+1);//target
    pop();
    line(812);
    push_symbol(base+0);//deplist
    idxr0(2);
    assign(base+2);//depend
    pop();
    line(813);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+3);//objdir
    pop();
    line(814);
    line(815);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(816);
    line(820);
    line(818);
    push_symbol(base+1);//target
    _clp_fext(1);
    string(L".obj");
    eqeq();
    if(!flag()) goto if_89_1;
        line(819);
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
    if_89_1:
    if_89_0:;
    line(822);
    push_symbol(base+1);//target
    _clp_ftime(1);
    assign(base+4);//ttarget
    pop();
    line(825);
    line(823);
    push_symbol(base+4);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_90_1;
        line(824);
        string(L"");
        assign(base+4);//ttarget
        pop();
    if_90_1:
    if_90_0:;
    line(829);
    line(827);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_91_1;
        line(828);
        push_symbol(base+1);//target
        string(L"[");
        push_symbol(base+4);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_91_1:
    if_91_0:;
    line(852);
    {
    line(831);
    push(&ONE);
    int sg=sign();
    number(2);
    assign(base+8);//n
    lab_92_0:
    push_symbol(base+0);//deplist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_92_2;
        line(832);
        push_symbol(base+0);//deplist
        push_symbol(base+8);//n
        idxr();
        assign(base+2);//depend
        pop();
        line(833);
        push_symbol(base+2);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(847);
        line(835);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_93_1;
            line(843);
            line(836);
            push_symbol(_st_s_dry_ptr());//global
            if(!flag()) goto if_94_1;
                line(837);
                string(L"");
                assign(base+5);//tdepend
                pop();
            goto if_94_0;
            if_94_1:
            line(838);
                line(839);
                push_symbol(base+0);//deplist
                push_symbol(base+8);//n
                idxr();
                string(nls_text(L"does not exist"));
                _clp_qout(2);
                pop();
                line(840);
                _clp_qout(0);
                pop();
                line(841);
                push(&ONE);
                _clp_errorlevel(1);
                pop();
                line(842);
                _clp___quit(0);
                pop();
            if_94_2:
            if_94_0:;
        goto if_93_0;
        if_93_1:
        line(845);
        push_symbol(base+4);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_93_2;
            line(846);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_93_2:
        if_93_0:;
        line(851);
        line(849);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_95_1;
            line(850);
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
        if_95_1:
        if_95_0:;
    lab_92_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_92_0;
    lab_92_2:;
    }
    line(856);
    line(854);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_96_1;
        line(855);
        _clp_qout(0);
        pop();
    if_96_1:
    if_96_0:;
    line(875);
    line(858);
    push_symbol(base+6);//update
    if(!flag()) goto if_97_1;
        line(860);
        string(L"BUILD_BAT");
        _clp_getenv(1);
        _clp_dirsep(0);
        add();
        assign(base+7);//torun
        pop();
        line(861);
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
        line(862);
        push_symbol(base+7);//torun
        string(L".bat");
        add();
        assign(base+7);//torun
        pop();
        line(869);
        line(864);
        push_symbol(base+7);//torun
        _clp_file(1);
        topnot();
        if(!flag()) goto if_98_1;
            line(865);
            string(L"[");
            push_symbol(base+7);//torun
            add();
            string(L"]");
            add();
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(866);
            _clp_qout(0);
            pop();
            line(867);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(868);
            _clp___quit(0);
            pop();
        if_98_1:
        if_98_0:;
        line(871);
        push_symbol(base+0);//deplist
        idxr0(1);
        _clp_fname(1);
        assign(base+9);//p1
        pop();
        line(872);
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
        line(874);
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
    if_97_1:
    if_97_0:;
    line(877);
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
    line(897);
    line(884);
    push_symbol(_st_s_dry_ptr());//global
    topnot();
    if(!flag()) goto if_99_1;
        line(886);
        push_symbol(base+0);//cmd
        _clp_run(1);
        pop();
        line(896);
        line(888);
        string(L"error");
        _clp_file(1);
        if(!flag()) goto if_100_1;
            line(890);
            string(L"cat error");
            _clp_run(1);
            pop();
            line(894);
            _clp_qout(0);
            pop();
            line(895);
            _clp___quit(0);
            pop();
        if_100_1:
        if_100_0:;
    if_99_1:
    if_99_0:;
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
    line(902);
    push_symbol(base+0);//fspec
    _clp_directory(1);
    assign(base+1);//d
    pop();
    line(905);
    line(903);
    push_symbol(base+1);//d
    _clp_len(1);
    push(&ONE);
    eqeq();
    if(!flag()) goto if_101_1;
        line(904);
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
    if_101_1:
    if_101_0:;
    line(906);
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
    line(912);
    number(10);
    _clp_chr(1);
    assign(base+4);//nl
    pop();
    line(913);
    string(L"#include");
    assign(base+5);//include
    pop();
    line(914);
    push_symbol(base+5);//include
    _clp_len(1);
    assign(base+6);//lenincl
    pop();
    line(915);
    push(&ZERO);
    assign(base+8);//n2
    pop();
    line(952);
    lab_102_1:
    line(917);
    push_symbol(base+5);//include
    push_symbol(base+0);//txt
    push_symbol(base+8);//n2
    addnum(1);
    _clp_at(3);
    assign(base+7);//n1
    push(&ZERO);
    gt();
    if(!flag()) goto lab_102_2;
        line(921);
        line(919);
        push(&ZERO);
        push_symbol(base+4);//nl
        push_symbol(base+0);//txt
        push_symbol(base+7);//n1
        push_symbol(base+6);//lenincl
        add();
        _clp_at(3);
        assign(base+8);//n2
        eqeq();
        if(!flag()) goto if_103_1;
            line(920);
            push_symbol(base+0);//txt
            _clp_len(1);
            addnum(1);
            assign(base+8);//n2
            pop();
        if_103_1:
        if_103_0:;
        line(923);
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
        line(924);
        push_symbol(base+9);//line
        number(9);
        _clp_chr(1);
        string(L"");
        _clp_strtran(3);
        assign(base+9);//line
        pop();
        line(925);
        push_symbol(base+9);//line
        _clp_alltrim(1);
        assign(base+9);//line
        pop();
        line(933);
        line(927);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"\"");
        eqeq();
        if(!flag()) goto if_104_1;
            line(928);
            string(L"\"");
            assign(base+10);//delim
            pop();
        goto if_104_0;
        if_104_1:
        line(929);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"<");
        eqeq();
        if(!flag()) goto if_104_2;
            line(930);
            string(L">");
            assign(base+10);//delim
            pop();
        goto if_104_0;
        if_104_2:
        line(931);
            line(932);
            goto lab_102_1;//loop
        if_104_3:
        if_104_0:;
        line(937);
        line(935);
        push(&ZERO);
        push_symbol(base+10);//delim
        push_symbol(base+9);//line
        number(2);
        _clp_at(3);
        assign(base+11);//dpos
        eqeq();
        if(!flag()) goto if_105_1;
            line(936);
            goto lab_102_1;//loop
        if_105_1:
        if_105_0:;
        line(939);
        push_symbol(base+9);//line
        number(2);
        push_symbol(base+11);//dpos
        addnum(-2);
        _clp_substr(3);
        assign(base+12);//f
        pop();
        line(940);
        push_symbol(base+12);//f
        string(L"/");
        _clp_dirsep(0);
        _clp_strtran(3);
        assign(base+12);//f
        pop();
        line(941);
        push_symbol(base+12);//f
        string(L"\\");
        _clp_dirsep(0);
        _clp_strtran(3);
        assign(base+12);//f
        pop();
        line(951);
        line(943);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byrules(4);
        if(!flag()) goto if_106_1;
        goto if_106_0;
        if_106_1:
        line(946);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byhand(4);
        if(!flag()) goto if_106_2;
        goto if_106_0;
        if_106_2:
        line(949);
        if_106_3:
        if_106_0:;
    goto lab_102_1;
    lab_102_2:;
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
    line(961);
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+0);//dirlist
    pop();
    line(962);
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+1);//liblist
    pop();
    line(963);
    string(L"BUILD_SHR");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+2);//sharing
    pop();
    line(965);
    string(L"");
    assign(base+5);//txt
    pop();
    line(966);
    line(1042);
    {
    line(969);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_107_0:
    push_symbol(base+1);//liblist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_107_2;
        line(973);
        line(971);
        push_symbol(base+1);//liblist
        push_symbol(base+3);//n
        idxr();
        assign(base+6);//f0
        _clp_empty(1);
        if(!flag()) goto if_108_1;
            line(972);
            goto lab_107_1;//loop
        if_108_1:
        if_108_0:;
        line(985);
        line(975);
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
        if(!flag()) goto if_109_1;
            line(976);
            push_symbol(base+6);//f0
            assign(base+7);//f1
            pop();
            line(977);
            push_symbol(base+6);//f0
            assign(base+8);//f2
            pop();
            line(978);
            push_symbol(base+6);//f0
            assign(base+9);//f3
            pop();
        goto if_109_0;
        if_109_1:
        line(979);
            line(980);
            push_symbol(base+6);//f0
            string(L".lib");
            add();
            assign(base+7);//f1
            pop();
            line(983);
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
            line(984);
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
        if_109_2:
        if_109_0:;
        line(1037);
        {
        line(987);
        push(&ONE);
        int sg=sign();
        push(&ZERO);
        assign(base+4);//i
        lab_110_0:
        push_symbol(base+0);//dirlist
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_110_2;
            line(1001);
            line(989);
            push_symbol(base+4);//i
            push(&ZERO);
            lteq();
            if(!flag()) goto if_111_1;
                line(990);
                push_symbol(base+7);//f1
                assign(base+10);//pf1
                pop();
                line(991);
                push_symbol(base+8);//f2
                assign(base+11);//pf2
                pop();
                line(992);
                push_symbol(base+9);//f3
                assign(base+12);//pf3
                pop();
            goto if_111_0;
            if_111_1:
            line(993);
                line(996);
                line(994);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_empty(1);
                if(!flag()) goto if_112_1;
                    line(995);
                    goto lab_110_1;//loop
                if_112_1:
                if_112_0:;
                line(998);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+7);//f1
                add();
                assign(base+10);//pf1
                pop();
                line(999);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+8);//f2
                add();
                assign(base+11);//pf2
                pop();
                line(1000);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+9);//f3
                add();
                assign(base+12);//pf3
                pop();
            if_111_2:
            if_111_0:;
            line(1036);
            line(1007);
            string(L"static");
            push_symbol(base+2);//sharing
            ss();
            if(!flag()) goto if_113_1;
                line(1020);
                line(1011);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_114_1;
                    line(1012);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1013);
                    goto lab_110_2;//exit
                goto if_114_0;
                if_114_1:
                line(1014);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_114_2;
                    line(1015);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1016);
                    goto lab_110_2;//exit
                goto if_114_0;
                if_114_2:
                line(1017);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_114_3;
                    line(1018);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1019);
                    goto lab_110_2;//exit
                if_114_3:
                if_114_0:;
            goto if_113_0;
            if_113_1:
            line(1022);
                line(1035);
                line(1026);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_115_1;
                    line(1027);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1028);
                    goto lab_110_2;//exit
                goto if_115_0;
                if_115_1:
                line(1029);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_115_2;
                    line(1030);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1031);
                    goto lab_110_2;//exit
                goto if_115_0;
                if_115_2:
                line(1032);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_115_3;
                    line(1033);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(1034);
                    goto lab_110_2;//exit
                if_115_3:
                if_115_0:;
            if_113_2:
            if_113_0:;
        lab_110_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+4);//i
        add();
        assign(base+4);//i
        goto lab_110_0;
        lab_110_2:;
        }
        line(1041);
        line(1039);
        push_symbol(base+4);//i
        push_symbol(base+0);//dirlist
        _clp_len(1);
        gt();
        if(!flag()) goto if_116_1;
            line(1040);
            push_symbol(base+5);//txt
            push_symbol(base+6);//f0
            string(L" ");
            add();
            add();
            assign(base+5);//txt
            pop();
        if_116_1:
        if_116_0:;
    lab_107_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_107_0;
    lab_107_2:;
    }
    line(1044);
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
    line(1049);
    line(1056);
    {
    line(1051);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_117_0:
    push_symbol(base+0);//dirlist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_117_2;
        line(1052);
        push_symbol(base+0);//dirlist
        push_symbol(base+2);//n
        idxr();
        _clp_dirsep(0);
        add();
        push_symbol(base+1);//fnamext
        add();
        assign(base+3);//pathname
        pop();
        line(1055);
        line(1053);
        push_symbol(base+3);//pathname
        _clp_file(1);
        if(!flag()) goto if_118_1;
            line(1054);
            push_symbol(base+3);//pathname
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_118_1:
        if_118_0:;
    lab_117_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_117_0;
    lab_117_2:;
    }
    line(1057);
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
    line(1068);
    push_symbol(base+0);//fil
    _clp_fname(1);
    assign(base+4);//f
    pop();
    line(1069);
    push_symbol(base+0);//fil
    _clp_fext(1);
    assign(base+5);//e
    pop();
    line(1070);
    line(1071);
    line(1072);
    line(1091);
    {
    line(1074);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//i
    lab_119_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_119_2;
        line(1090);
        line(1076);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+9);//i
        idxr();
        idxr0(2);
        push_symbol(base+5);//e
        eqeq();
        if(!flag()) goto if_120_1;
            line(1078);
            push_symbol(_st_s_rules_ptr());//global
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            assign(base+8);//e0
            pop();
            line(1089);
            line(1082);
            push(&NIL);
            push_symbol(base+2);//dir
            push_symbol(base+4);//f
            push_symbol(base+8);//e0
            add();
            _clp_search_file(2);
            assign(base+7);//r
            neeq();
            if(!flag()) goto if_121_1;
                line(1083);
                push_symbol(base+7);//r
                _clp_fpath(1);
                assign(base+6);//p
                pop();
                line(1084);
                push_symbol(base+1);//dep
                push_symbol(base+6);//p
                push_symbol(base+4);//f
                add();
                push_symbol(base+5);//e
                add();
                _clp_adddep(2);
                pop();
                line(1087);
                line(1085);
                push(&ZERO);
                push_symbol(base+3);//todo
                push_symbol_ref(base+6);//p
                push_symbol_ref(base+4);//f
                push_symbol_ref(base+5);//e
                block(_blk_byrules_0,3);
                _clp_ascan(2);
                eqeq();
                if(!flag()) goto if_122_1;
                    line(1086);
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
                if_122_1:
                if_122_0:;
                line(1088);
                push(&TRUE);
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            if_121_1:
            if_121_0:;
        if_120_1:
        if_120_0:;
    lab_119_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//i
    add();
    assign(base+9);//i
    goto lab_119_0;
    lab_119_2:;
    }
    line(1092);
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
    line(1103);
    push_symbol(base+2);//dir
    push_symbol(base+0);//f
    _clp_search_file(2);
    assign(base+4);//pn
    pop();
    line(1108);
    line(1105);
    push_symbol(base+4);//pn
    push(&NIL);
    neeq();
    if(!flag()) goto if_123_1;
        line(1106);
        push_symbol(base+1);//dep
        push_symbol(base+4);//pn
        _clp_adddep(2);
        pop();
        line(1107);
        push(&TRUE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_123_1:
    if_123_0:;
    line(1109);
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
    line(1116);
    line(1114);
    push(&ZERO);
    push_symbol(base+0);//dep
    push_symbol_ref(base+1);//x
    block(_blk_adddep_0,1);
    _clp_ascan(2);
    eqeq();
    if(!flag()) goto if_124_1;
        line(1115);
        push_symbol(base+0);//dep
        push_symbol(base+1);//x
        _clp_aadd(2);
        pop();
    if_124_1:
    if_124_0:;
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
    line(1121);
    push_symbol(base+0);//x
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+0);//x
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+2);//ix
    pop();
    line(1122);
    push_symbol(base+1);//y
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+1);//y
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+3);//iy
    pop();
    line(1123);
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
    line(1128);
    line(1133);
    {
    line(1129);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_125_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_125_2;
        line(1132);
        line(1130);
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
        if(!flag()) goto if_126_1;
            line(1131);
            push_symbol(base+2);//n
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_126_1:
        if_126_0:;
    lab_125_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_125_0;
    lab_125_2:;
    }
    line(1134);
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
    line(1139);
    line(1149);
    {
    line(1140);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_127_0:
    push_symbol(base+1);//sep
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_127_2;
        line(1142);
        push_symbol(base+1);//sep
        push_symbol(base+2);//n
        push(&ONE);
        _clp_substr(3);
        assign(base+3);//s
        pop();
        line(1148);
        line(1144);
        push(&ZERO);
        push_symbol(base+3);//s
        push_symbol(base+0);//txt
        _clp_at(2);
        lt();
        if(!flag()) goto if_128_1;
            line(1145);
            goto lab_127_2;//exit
        goto if_128_0;
        if_128_1:
        line(1146);
            line(1147);
            push(&NIL);
            assign(base+3);//s
            pop();
        if_128_2:
        if_128_0:;
    lab_127_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_127_0;
    lab_127_2:;
    }
    line(1150);
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
    line(1159);
    line(1170);
    {
    line(1161);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_129_0:
    push_symbol(base+0);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_129_2;
        line(1169);
        {
        line(1162);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+1);//i
        lab_130_0:
        push_symbol(base+0);//todo
        push_symbol(base+2);//n
        idxr();
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_130_2;
            line(1163);
            push_symbol(base+0);//todo
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+1);//i
            idxr();
            assign(base+3);//x
            pop();
            line(1164);
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
            line(1167);
            line(1165);
            push_symbol(base+3);//x
            number(2);
            _clp_left(2);
            string(L".");
            _clp_dirsep(0);
            add();
            eqeq();
            if(!flag()) goto if_131_1;
                line(1166);
                push_symbol(base+3);//x
                number(3);
                _clp_substr(2);
                assign(base+3);//x
                pop();
            if_131_1:
            if_131_0:;
            line(1168);
            push_symbol(base+3);//x
            push_symbol(base+0);//todo
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+1);//i
            assign2(idxxl());
            pop();
        lab_130_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+1);//i
        add();
        assign(base+1);//i
        goto lab_130_0;
        lab_130_2:;
        }
    lab_129_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_129_0;
    lab_129_2:;
    }
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

