
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

//input: build.ppo (5.0.03x)

#include <cccdef.h>

static void _blk_build_0(int argno);
static void _blk_build_1(int argno);
static void _blk_build_2(int argno);
static void _blk_byrules_0(int argno);
extern void _clp___quit(int argno);
extern void _clp_aadd(int argno);
extern void _clp_aclone(int argno);
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
extern void _clp_set(int argno);
extern void _clp_setdosconv(int argno);
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
    line(65);
    _clp_argv(0);
    _clp_aclone(1);
    assign(base+0);//opt
    pop();
    line(70);
    string(L"off");
    _clp_setdosconv(1);
    pop();
    line(151);
    {
    line(73);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_1_0:
    push_symbol(base+0);//opt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(74);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        _clp_procpar(1);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        assign(idxl());
        pop();
        line(150);
        line(76);
        string(L"-l");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_2_1;
            line(77);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_libnam_ptr());//global
            pop();
            line(78);
            push(&FALSE);
            assign(_st_s_shared_ptr());//global
            pop();
        goto if_2_0;
        if_2_1:
        line(81);
        string(L"-s");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_2_2;
            line(82);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_libnam_ptr());//global
            pop();
            line(83);
            push(&TRUE);
            assign(_st_s_shared_ptr());//global
            pop();
        goto if_2_0;
        if_2_2:
        line(86);
        string(L"-d");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_2_3;
            line(91);
            line(87);
            push_symbol(_st_s_srcdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_3_1;
                line(88);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_srcdir_ptr());//global
                pop();
            goto if_3_0;
            if_3_1:
            line(89);
                line(90);
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
            if_3_2:
            if_3_0:;
        goto if_2_0;
        if_2_3:
        line(94);
        string(L"-i");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_2_4;
            line(99);
            line(95);
            push_symbol(_st_s_incdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_4_1;
                line(96);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_incdir_ptr());//global
                pop();
            goto if_4_0;
            if_4_1:
            line(97);
                line(98);
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
            if_4_2:
            if_4_0:;
        goto if_2_0;
        if_2_4:
        line(102);
        string(L"-p");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_2_5;
            line(107);
            line(103);
            push_symbol(_st_s_libdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_5_1;
                line(104);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_libdir_ptr());//global
                pop();
            goto if_5_0;
            if_5_1:
            line(105);
                line(106);
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
            if_5_2:
            if_5_0:;
        goto if_2_0;
        if_2_5:
        line(110);
        string(L"-b");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_2_6;
            line(115);
            line(111);
            push_symbol(_st_s_libfil_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_6_1;
                line(112);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_libfil_ptr());//global
                pop();
            goto if_6_0;
            if_6_1:
            line(113);
                line(114);
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
            if_6_2:
            if_6_0:;
        goto if_2_0;
        if_2_6:
        line(118);
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
        if(!flag()) goto if_2_7;
            line(123);
            line(119);
            push_symbol(_st_s_main_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_7_1;
                line(120);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_main_ptr());//global
                pop();
            goto if_7_0;
            if_7_1:
            line(121);
                line(122);
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
            if_7_2:
            if_7_0:;
        goto if_2_0;
        if_2_7:
        line(126);
        string(L"-h");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_2_8;
            line(127);
            _clp_usage(0);
            pop();
            line(128);
            _clp___quit(0);
            pop();
        goto if_2_0;
        if_2_8:
        line(130);
        string(L"-q");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_2_9;
            line(131);
            push(&TRUE);
            assign(_st_s_quiet_ptr());//global
            pop();
        goto if_2_0;
        if_2_9:
        line(133);
        string(L"-v");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_2_10;
            line(134);
            push(&TRUE);
            assign(_st_s_version_ptr());//global
            pop();
        goto if_2_0;
        if_2_10:
        line(137);
        string(L"@");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        push(&ONE);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_2_11;
            line(138);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(2);
            _clp_substr(2);
            push_symbol(base+0);//opt
            _clp_readpar(2);
            pop();
        goto if_2_0;
        if_2_11:
        line(141);
        string(L"=");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        ss();
        if(!flag()) goto if_2_12;
            line(142);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_putenv(1);
            pop();
        goto if_2_0;
        if_2_12:
        line(145);
            line(146);
            string(nls_text(L"Invalid switch: "));
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_qout(2);
            pop();
            line(147);
            _clp_usage(0);
            pop();
            line(148);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(149);
            _clp___quit(0);
            pop();
        if_2_13:
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
    line(156);
    line(153);
    push_symbol(_st_s_quiet_ptr());//global
    topnot();
    if(!flag()) goto if_8_1;
        line(154);
        string(nls_text(L"CCC Program Builder "));
        string(L"1.2.24");
        add();
        string(L" Copyright (C) ComFirm Bt.");
        add();
        _clp_qqout(1);
        pop();
        line(155);
        _clp_qout(0);
        pop();
    if_8_1:
    if_8_0:;
    line(160);
    line(158);
    push_symbol(_st_s_version_ptr());//global
    if(!flag()) goto if_9_1;
        line(159);
        _clp___quit(0);
        pop();
    if_9_1:
    if_9_0:;
    line(167);
    line(163);
    string(L"on");
    string(L"BUILD_DBG");
    _clp_getenv(1);
    _clp_lower(1);
    ss();
    if(!flag()) goto if_10_1;
        line(164);
        push(&TRUE);
        assign(_st_s_debug_ptr());//global
        pop();
        line(165);
        number(19);
        string(L"debug");
        push(&FALSE);
        _clp_set(3);
        pop();
        line(166);
        number(18);
        string(L"on");
        _clp_set(2);
        pop();
    if_10_1:
    if_10_0:;
    line(169);
    _clp_root(0);
    pop();
    line(170);
    _clp_params(0);
    pop();
    line(171);
    _clp_build(0);
    pop();
    line(173);
    _clp_qout(0);
    pop();
    line(175);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_readpar(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+6)PUSHNIL();
argno=2;
push_call("readpar",base);
//
    line(180);
    push_symbol(base+0);//parfil
    _clp_memoread(1);
    assign(base+2);//par
    pop();
    line(187);
    line(182);
    push_symbol(base+2);//par
    _clp_empty(1);
    if(!flag()) goto if_11_1;
        line(186);
        string(L"BUILD_BAT");
        _clp_getenv(1);
        _clp_dirsep(0);
        add();
        push_symbol(base+0);//parfil
        add();
        _clp_memoread(1);
        assign(base+2);//par
        pop();
    if_11_1:
    if_11_0:;
    line(189);
    push_symbol(base+2);//par
    number(13);
    _clp_chr(1);
    string(L"");
    _clp_strtran(3);
    assign(base+2);//par
    pop();
    line(190);
    push_symbol(base+2);//par
    number(10);
    _clp_chr(1);
    _clp_split(2);
    assign(base+2);//par
    pop();
    line(204);
    {
    line(192);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_12_0:
    push_symbol(base+2);//par
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_12_2;
        line(193);
        push_symbol(base+2);//par
        push_symbol(base+3);//n
        idxr();
        assign(base+4);//p
        pop();
        line(196);
        line(194);
        string(L"#");
        push_symbol(base+4);//p
        ss();
        if(!flag()) goto if_13_1;
            line(195);
            push_symbol(base+4);//p
            string(L"#");
            push_symbol(base+4);//p
            _clp_at(2);
            addnum(-1);
            _clp_left(2);
            assign(base+4);//p
            pop();
        if_13_1:
        if_13_0:;
        line(198);
        push_symbol(base+4);//p
        string(L" ");
        _clp_split(2);
        assign(base+4);//p
        pop();
        line(203);
        {
        line(199);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+5);//i
        lab_14_0:
        push_symbol(base+4);//p
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_14_2;
            line(202);
            line(200);
            push_symbol(base+4);//p
            push_symbol(base+5);//i
            idxr();
            _clp_empty(1);
            topnot();
            if(!flag()) goto if_15_1;
                line(201);
                push_symbol(base+1);//opt
                push_symbol(base+4);//p
                push_symbol(base+5);//i
                idxr();
                _clp_aadd(2);
                pop();
            if_15_1:
            if_15_0:;
        lab_14_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+5);//i
        add();
        assign(base+5);//i
        goto lab_14_0;
        lab_14_2:;
        }
    lab_12_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_12_0;
    lab_12_2:;
    }
    line(205);
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
    line(209);
    line(218);
    lab_16_1:
    line(211);
    push(&ZERO);
    string(L"$$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_16_2;
        line(212);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(213);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(3);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(214);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(215);
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
        line(216);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(217);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_16_1;
    lab_16_2:;
    line(227);
    lab_17_1:
    line(220);
    push(&ZERO);
    string(L"$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_17_2;
        line(221);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(222);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(2);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(223);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(224);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        _clp_getenv(1);
        add();
        assign(base+2);//p
        pop();
        line(225);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(226);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_17_1;
    lab_17_2:;
    line(229);
    push_symbol(base+0);//par
    string(L"\\");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(230);
    push_symbol(base+0);//par
    string(L"/");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(232);
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
    line(237);
    string(nls_text(L"BUILD -xExeNam|-lLibNam -dSrcDir -iIncDir -pLibDir -bLibFil -mMain"));
    _clp_qout(1);
    pop();
    line(238);
    _clp_qout(0);
    pop();
    line(239);
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
    line(245);
    line(282);
    line(247);
    string(L"BUILD_SRC");
    _clp_getenv(1);
    assign(base+0);//srcroot
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_18_1;
        line(251);
        line(249);
        push_symbol(base+0);//srcroot
        push(&ONE);
        _clp_right(2);
        string(L"/\\");
        ss();
        topnot();
        if(!flag()) goto if_19_1;
            line(250);
            push_symbol(base+0);//srcroot
            _clp_dirsep(0);
            add();
            assign(base+0);//srcroot
            pop();
        if_19_1:
        if_19_0:;
        line(255);
        line(253);
        push_symbol(_st_s_srcdir_ptr());//global
        push(&NIL);
        eqeq();
        if(!flag()) goto if_20_1;
            line(254);
            string(L".");
            assign(_st_s_srcdir_ptr());//global
            pop();
        if_20_1:
        if_20_0:;
        line(257);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+1);//d
        pop();
        line(259);
        string(L"");
        assign(_st_s_srcdir_ptr());//global
        pop();
        line(266);
        {
        line(260);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+2);//n
        lab_21_0:
        push_symbol(base+1);//d
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_21_2;
            line(265);
            line(261);
            push_symbol(base+1);//d
            push_symbol(base+2);//n
            idxr();
            push(&ONE);
            _clp_left(2);
            string(L"/\\");
            ss();
            if(!flag()) goto if_22_1;
                line(262);
                push_symbol(_st_s_srcdir_ptr());//global
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                string(L";");
                add();
                add();
                assign(_st_s_srcdir_ptr());//global
                pop();
            goto if_22_0;
            if_22_1:
            line(263);
                line(264);
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
            if_22_2:
            if_22_0:;
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
        line(281);
        line(269);
        push_symbol(_st_s_incdir_ptr());//global
        push(&NIL);
        neeq();
        if(!flag()) goto if_23_1;
            line(271);
            push_symbol(_st_s_incdir_ptr());//global
            string(L",;");
            _clp_xsplit(2);
            assign(base+1);//d
            pop();
            line(273);
            string(L"");
            assign(_st_s_incdir_ptr());//global
            pop();
            line(280);
            {
            line(274);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+2);//n
            lab_24_0:
            push_symbol(base+1);//d
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_24_2;
                line(279);
                line(275);
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                push(&ONE);
                _clp_left(2);
                string(L"/\\");
                ss();
                if(!flag()) goto if_25_1;
                    line(276);
                    push_symbol(_st_s_incdir_ptr());//global
                    push_symbol(base+1);//d
                    push_symbol(base+2);//n
                    idxr();
                    string(L";");
                    add();
                    add();
                    assign(_st_s_incdir_ptr());//global
                    pop();
                goto if_25_0;
                if_25_1:
                line(277);
                    line(278);
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
                if_25_2:
                if_25_0:;
            lab_24_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+2);//n
            add();
            assign(base+2);//n
            goto lab_24_0;
            lab_24_2:;
            }
        if_23_1:
        if_23_0:;
    if_18_1:
    if_18_0:;
    line(284);
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
    line(290);
    line(303);
    string(L"");
    assign(base+0);//txt
    pop();
    line(304);
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
    line(305);
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
    line(306);
    push_symbol(base+0);//txt
    string(L"BUILD_INC");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(307);
    push_symbol(base+0);//txt
    string(L"include");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(308);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(309);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(311);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(313);
    string(L"BUILD_INC=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(319);
    string(L"");
    assign(base+0);//txt
    pop();
    line(320);
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
    line(321);
    push_symbol(base+0);//txt
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(322);
    push_symbol(base+0);//txt
    string(L"lib");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(323);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(324);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(326);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(328);
    string(L"BUILD_LPT=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(334);
    string(L"");
    assign(base+0);//txt
    pop();
    line(335);
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
    line(336);
    push_symbol(base+0);//txt
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(337);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(338);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(339);
    string(L"BUILD_LIB=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(342);
    line(340);
    push_symbol(_st_s_libabs_ptr());//global
    if(!flag()) goto if_26_1;
        line(341);
        string(L"BUILD_LIB=");
        _clp_search_library(0);
        add();
        _clp_putenv(1);
        pop();
    if_26_1:
    if_26_0:;
    line(345);
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
    line(351);
    array(0);
    assign(base+0);//dir
    pop();
    line(352);
    array(0);
    assign(base+1);//obj
    pop();
    line(353);
    array(0);
    assign(base+2);//lib
    pop();
    line(354);
    array(0);
    assign(base+3);//mmd
    pop();
    line(355);
    array(0);
    assign(base+4);//todo
    pop();
    line(357);
    line(362);
    line(360);
    push_symbol(_st_s_main_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_27_1;
        line(361);
        push_symbol(_st_s_main_ptr());//global
        _clp_lower(1);
        string(L",;");
        _clp_xsplit(2);
        assign(base+3);//mmd
        pop();
    if_27_1:
    if_27_0:;
    line(369);
    line(365);
    push_symbol(_st_s_srcdir_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_28_1;
        line(366);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+0);//dir
        pop();
    goto if_28_0;
    if_28_1:
    line(367);
        line(368);
        string(L".");
        array(1);
        assign(base+0);//dir
        pop();
    if_28_2:
    if_28_0:;
    line(385);
    {
    line(371);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_29_0:
    push_symbol(base+0);//dir
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_29_2;
        line(373);
        string(L"");
        push_symbol(base+0);//dir
        push_symbol(base+8);//n
        idxr();
        _clp_qqout(2);
        pop();
        line(375);
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
        line(384);
        {
        line(377);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//i
        lab_30_0:
        push_symbol(base+5);//d1
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_30_2;
            line(379);
            push_symbol(base+5);//d1
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            _clp_lower(1);
            assign(base+6);//f
            pop();
            line(383);
            line(381);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            push_symbol(_st_s_primary_ptr());//global
            ss();
            if(!flag()) goto if_31_1;
                line(382);
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
            if_31_1:
            if_31_0:;
        lab_30_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//i
        add();
        assign(base+9);//i
        goto lab_30_0;
        lab_30_2:;
        }
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
    line(386);
    _clp_qout(0);
    pop();
    line(418);
    {
    line(391);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_32_0:
    push_symbol(base+1);//obj
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_32_2;
        line(393);
        push_symbol(base+1);//obj
        push_symbol(base+8);//n
        idxr();
        assign(base+6);//f
        pop();
        line(394);
        push_symbol(base+6);//f
        _clp_fname(1);
        assign(base+7);//o
        pop();
        line(396);
        push_symbol(base+7);//o
        string(L".obj");
        add();
        push_symbol(base+6);//f
        array(2);
        assign(base+11);//dep
        pop();
        line(415);
        line(398);
        push_symbol(base+6);//f
        _clp_fext(1);
        string(L".prg");
        eqeq();
        if(!flag()) goto if_33_1;
            line(399);
            push_symbol(base+6);//f
            _clp_memoread(1);
            assign(base+10);//txt
            pop();
            line(409);
            line(401);
            push(&ZERO);
            push_symbol(base+3);//mmd
            push_symbol_ref(base+7);//o
            block(_blk_build_0,1);
            _clp_ascan(2);
            neeq();
            if(!flag()) goto if_34_1;
            goto if_34_0;
            if_34_1:
            line(403);
            string(L"function main(");
            push_symbol(base+10);//txt
            ss();
            if(!flag()) goto if_34_2;
                line(406);
                line(404);
                push_symbol(_st_s_main_ptr());//global
                push(&NIL);
                eqeq();
                if(!flag()) goto if_35_1;
                    line(405);
                    push_symbol(base+3);//mmd
                    push_symbol(base+7);//o
                    _clp_aadd(2);
                    pop();
                if_35_1:
                if_35_0:;
            goto if_34_0;
            if_34_2:
            line(407);
                line(408);
                push_symbol(base+2);//lib
                push_symbol(base+7);//o
                _clp_aadd(2);
                pop();
            if_34_3:
            if_34_0:;
            line(411);
            push_symbol(base+10);//txt
            push_symbol(base+11);//dep
            push_symbol(base+0);//dir
            push_symbol(base+4);//todo
            _clp_search_include(4);
            pop();
        goto if_33_0;
        if_33_1:
        line(413);
        push(&ZERO);
        push_symbol(base+3);//mmd
        push_symbol_ref(base+7);//o
        block(_blk_build_1,1);
        _clp_ascan(2);
        eqeq();
        if(!flag()) goto if_33_2;
            line(414);
            push_symbol(base+2);//lib
            push_symbol(base+7);//o
            _clp_aadd(2);
            pop();
        if_33_2:
        if_33_0:;
        line(417);
        push_symbol(base+4);//todo
        push_symbol(base+11);//dep
        _clp_aadd(2);
        pop();
    lab_32_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_32_0;
    lab_32_2:;
    }
    line(420);
    push_symbol(base+4);//todo
    push(&NIL);
    push(&NIL);
    block(_blk_build_2,0);
    _clp_asort(4);
    pop();
    line(432);
    line(424);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_36_1;
        line(425);
        string(L"main:");
        push_symbol(base+3);//mmd
        _clp_qout(2);
        pop();
        line(426);
        string(L"lib :");
        push_symbol(base+2);//lib
        _clp_qout(2);
        pop();
        line(427);
        _clp_qout(0);
        pop();
        line(430);
        {
        line(428);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_37_0:
        push_symbol(base+4);//todo
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_37_2;
            line(429);
            push_symbol(base+4);//todo
            push_symbol(base+8);//n
            idxr();
            _clp_qout(1);
            pop();
        lab_37_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+8);//n
        add();
        assign(base+8);//n
        goto lab_37_0;
        lab_37_2:;
        }
        line(431);
        _clp_qout(0);
        pop();
    if_36_1:
    if_36_0:;
    line(436);
    {
    line(434);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_38_0:
    push_symbol(base+4);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_38_2;
        line(435);
        push_symbol(base+4);//todo
        push_symbol(base+8);//n
        idxr();
        _clp_makeobj(1);
        pop();
    lab_38_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_38_0;
    lab_38_2:;
    }
    line(455);
    line(440);
    push_symbol(_st_s_libnam_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_39_1;
        line(441);
        push_symbol(_st_s_libnam_ptr());//global
        push_symbol(base+2);//lib
        _clp_makelib(2);
        pop();
        line(445);
        line(443);
        push_symbol(_st_s_shared_ptr());//global
        push(&TRUE);
        eqeq();
        if(!flag()) goto if_40_1;
            line(444);
            push_symbol(_st_s_libnam_ptr());//global
            push_symbol(base+2);//lib
            _clp_makeso(2);
            pop();
        if_40_1:
        if_40_0:;
        line(449);
        {
        line(447);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_41_0:
        push_symbol(base+3);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_41_2;
            line(448);
            push_symbol(base+3);//mmd
            push_symbol(base+8);//n
            idxr();
            push_symbol(_st_s_libnam_ptr());//global
            _clp_makeexe1(2);
            pop();
        lab_41_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+8);//n
        add();
        assign(base+8);//n
        goto lab_41_0;
        lab_41_2:;
        }
    goto if_39_0;
    if_39_1:
    line(451);
        line(454);
        {
        line(452);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_42_0:
        push_symbol(base+3);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_42_2;
            line(453);
            push_symbol(base+3);//mmd
            push_symbol(base+8);//n
            idxr();
            push_symbol(base+2);//lib
            _clp_makeexe(2);
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
    if_39_2:
    if_39_0:;
    line(457);
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
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_build_1",base);
//
    push_blkarg(base+1);//m
    push_blkenv(env+0);//o
    _clp_lower(1);
    eqeq();
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_build_2(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_build_2",base);
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
    line(464);
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
    line(465);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(466);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2so.bat");
    add();
    assign(base+7);//torun
    pop();
    line(467);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(474);
    line(469);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_43_1;
        line(470);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(471);
        _clp_qout(0);
        pop();
        line(472);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(473);
        _clp___quit(0);
        pop();
    if_43_1:
    if_43_0:;
    line(476);
    push_symbol(base+7);//torun
    string(L" lib");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(478);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(481);
    line(479);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_44_1;
        line(480);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_44_1:
    if_44_0:;
    line(485);
    line(483);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_45_1;
        line(484);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_45_1:
    if_45_0:;
    line(508);
    {
    line(487);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_46_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_46_2;
        line(489);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(490);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+4);//depend
        add();
        add();
        assign(base+7);//torun
        pop();
        line(491);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(492);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(503);
        line(494);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_47_1;
            line(495);
            push_symbol(base+4);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(496);
            _clp_qout(0);
            pop();
            line(497);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(498);
            _clp___quit(0);
            pop();
        goto if_47_0;
        if_47_1:
        line(500);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_47_2;
            line(502);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_47_2:
        if_47_0:;
        line(507);
        line(505);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_48_1;
            line(506);
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
        if_48_1:
        if_48_0:;
    lab_46_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_46_0;
    lab_46_2:;
    }
    line(512);
    line(510);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_49_1;
        line(511);
        _clp_qout(0);
        pop();
    if_49_1:
    if_49_0:;
    line(516);
    line(514);
    push_symbol(base+6);//update
    if(!flag()) goto if_50_1;
        line(515);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_50_1:
    if_50_0:;
    line(518);
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
    line(524);
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
    line(525);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(526);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2lib.bat");
    add();
    assign(base+7);//torun
    pop();
    line(527);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+8);//objdir
    pop();
    line(528);
    line(535);
    line(530);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_51_1;
        line(531);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(532);
        _clp_qout(0);
        pop();
        line(533);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(534);
        _clp___quit(0);
        pop();
    if_51_1:
    if_51_0:;
    line(537);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(539);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(542);
    line(540);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_52_1;
        line(541);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_52_1:
    if_52_0:;
    line(546);
    line(544);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_53_1;
        line(545);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_53_1:
    if_53_0:;
    line(568);
    {
    line(548);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_54_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_54_2;
        line(550);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(551);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(552);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(563);
        line(554);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_55_1;
            line(555);
            push_symbol(base+4);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(556);
            _clp_qout(0);
            pop();
            line(557);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(558);
            _clp___quit(0);
            pop();
        goto if_55_0;
        if_55_1:
        line(560);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_55_2;
            line(562);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_55_2:
        if_55_0:;
        line(567);
        line(565);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_56_1;
            line(566);
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
        if_56_1:
        if_56_0:;
    lab_54_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_54_0;
    lab_54_2:;
    }
    line(572);
    line(570);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_57_1;
        line(571);
        _clp_qout(0);
        pop();
    if_57_1:
    if_57_0:;
    line(599);
    line(574);
    push_symbol(base+6);//update
    if(!flag()) goto if_58_1;
        line(579);
        {
        line(577);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_59_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_59_2;
            line(578);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
            pop();
        lab_59_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_59_0;
        lab_59_2:;
        }
        line(598);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_58_1:
    if_58_0:;
    line(601);
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
    line(607);
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
    line(608);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(609);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2exe.bat");
    add();
    assign(base+7);//torun
    pop();
    line(610);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+8);//objdir
    pop();
    line(611);
    line(618);
    line(613);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_60_1;
        line(614);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(615);
        _clp_qout(0);
        pop();
        line(616);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(617);
        _clp___quit(0);
        pop();
    if_60_1:
    if_60_0:;
    line(620);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(623);
    line(621);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_61_1;
        line(622);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_61_1:
    if_61_0:;
    line(627);
    line(625);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_62_1;
        line(626);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_62_1:
    if_62_0:;
    line(654);
    {
    line(629);
    push(&ONE);
    int sg=sign();
    push(&ZERO);
    assign(base+9);//n
    lab_63_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_63_2;
        line(635);
        line(631);
        push_symbol(base+9);//n
        push(&ZERO);
        eqeq();
        if(!flag()) goto if_64_1;
            line(632);
            push_symbol(base+0);//exenam
            assign(base+4);//depend
            pop();
        goto if_64_0;
        if_64_1:
        line(633);
            line(634);
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
        if_64_2:
        if_64_0:;
        line(637);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(638);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(649);
        line(640);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_65_1;
            line(641);
            push_symbol(base+4);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(642);
            _clp_qout(0);
            pop();
            line(643);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(644);
            _clp___quit(0);
            pop();
        goto if_65_0;
        if_65_1:
        line(646);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_65_2;
            line(648);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_65_2:
        if_65_0:;
        line(653);
        line(651);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_66_1;
            line(652);
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
        if_66_1:
        if_66_0:;
    lab_63_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_63_0;
    lab_63_2:;
    }
    line(658);
    line(656);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_67_1;
        line(657);
        _clp_qout(0);
        pop();
    if_67_1:
    if_67_0:;
    line(691);
    line(660);
    push_symbol(base+6);//update
    if(!flag()) goto if_68_1;
        line(661);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+0);//exenam
        add();
        add();
        assign(base+7);//torun
        pop();
        line(666);
        {
        line(664);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_69_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_69_2;
            line(665);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
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
        line(690);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_68_1:
    if_68_0:;
    line(693);
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
    line(699);
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
    line(700);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(701);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"lib2exe.bat");
    add();
    assign(base+7);//torun
    pop();
    line(702);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(709);
    line(704);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_70_1;
        line(705);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(706);
        _clp_qout(0);
        pop();
        line(707);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(708);
        _clp___quit(0);
        pop();
    if_70_1:
    if_70_0:;
    line(711);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(714);
    line(712);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_71_1;
        line(713);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_71_1:
    if_71_0:;
    line(718);
    line(716);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_72_1;
        line(717);
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
    line(721);
    push_symbol(base+0);//mmod
    assign(base+4);//depend
    pop();
    line(722);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(723);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".obj");
    add();
    assign(base+4);//depend
    pop();
    line(724);
    push_symbol(base+4);//depend
    _clp_ftime(1);
    assign(base+5);//tdepend
    pop();
    line(733);
    line(726);
    push_symbol(base+5);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_73_1;
        line(727);
        push_symbol(base+4);//depend
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(728);
        _clp_qout(0);
        pop();
        line(729);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(730);
        _clp___quit(0);
        pop();
    goto if_73_0;
    if_73_1:
    line(731);
    push_symbol(base+3);//ttarget
    push_symbol(base+5);//tdepend
    lt();
    if(!flag()) goto if_73_2;
        line(732);
        push(&TRUE);
        assign(base+6);//update
        pop();
    if_73_2:
    if_73_0:;
    line(736);
    line(734);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_74_1;
        line(735);
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
    line(739);
    push_symbol(base+1);//libnam
    assign(base+4);//depend
    pop();
    line(740);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(741);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".lib");
    add();
    assign(base+4);//depend
    pop();
    line(742);
    push_symbol(base+4);//depend
    _clp_ftime(1);
    assign(base+5);//tdepend
    pop();
    line(751);
    line(744);
    push_symbol(base+5);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_75_1;
        line(745);
        push_symbol(base+4);//depend
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(746);
        _clp_qout(0);
        pop();
        line(747);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(748);
        _clp___quit(0);
        pop();
    goto if_75_0;
    if_75_1:
    line(749);
    push_symbol(base+3);//ttarget
    push_symbol(base+5);//tdepend
    lt();
    if(!flag()) goto if_75_2;
        line(750);
        push(&TRUE);
        assign(base+6);//update
        pop();
    if_75_2:
    if_75_0:;
    line(754);
    line(752);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_76_1;
        line(753);
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
    line(759);
    line(757);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_77_1;
        line(758);
        _clp_qout(0);
        pop();
    if_77_1:
    if_77_0:;
    line(763);
    line(761);
    push_symbol(base+6);//update
    if(!flag()) goto if_78_1;
        line(762);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_78_1:
    if_78_0:;
    line(765);
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
    line(771);
    push_symbol(base+0);//deplist
    idxr0(1);
    assign(base+1);//target
    pop();
    line(772);
    push_symbol(base+0);//deplist
    idxr0(2);
    assign(base+2);//depend
    pop();
    line(773);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+3);//objdir
    pop();
    line(774);
    line(775);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(776);
    line(780);
    line(778);
    push_symbol(base+1);//target
    _clp_fext(1);
    string(L".obj");
    eqeq();
    if(!flag()) goto if_79_1;
        line(779);
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
    if_79_1:
    if_79_0:;
    line(782);
    push_symbol(base+1);//target
    _clp_ftime(1);
    assign(base+4);//ttarget
    pop();
    line(785);
    line(783);
    push_symbol(base+4);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_80_1;
        line(784);
        string(L"");
        assign(base+4);//ttarget
        pop();
    if_80_1:
    if_80_0:;
    line(789);
    line(787);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_81_1;
        line(788);
        push_symbol(base+1);//target
        string(L"[");
        push_symbol(base+4);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_81_1:
    if_81_0:;
    line(809);
    {
    line(791);
    push(&ONE);
    int sg=sign();
    number(2);
    assign(base+8);//n
    lab_82_0:
    push_symbol(base+0);//deplist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_82_2;
        line(792);
        push_symbol(base+0);//deplist
        push_symbol(base+8);//n
        idxr();
        assign(base+2);//depend
        pop();
        line(793);
        push_symbol(base+2);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(804);
        line(795);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_83_1;
            line(796);
            push_symbol(base+0);//deplist
            push_symbol(base+8);//n
            idxr();
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(797);
            _clp_qout(0);
            pop();
            line(798);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(799);
            _clp___quit(0);
            pop();
        goto if_83_0;
        if_83_1:
        line(801);
        push_symbol(base+4);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_83_2;
            line(803);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_83_2:
        if_83_0:;
        line(808);
        line(806);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_84_1;
            line(807);
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
        if_84_1:
        if_84_0:;
    lab_82_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_82_0;
    lab_82_2:;
    }
    line(814);
    line(812);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_85_1;
        line(813);
        _clp_qout(0);
        pop();
    if_85_1:
    if_85_0:;
    line(834);
    line(817);
    push_symbol(base+6);//update
    if(!flag()) goto if_86_1;
        line(819);
        string(L"BUILD_BAT");
        _clp_getenv(1);
        _clp_dirsep(0);
        add();
        assign(base+7);//torun
        pop();
        line(820);
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
        line(821);
        push_symbol(base+7);//torun
        string(L".bat");
        add();
        assign(base+7);//torun
        pop();
        line(828);
        line(823);
        push_symbol(base+7);//torun
        _clp_file(1);
        topnot();
        if(!flag()) goto if_87_1;
            line(824);
            string(L"[");
            push_symbol(base+7);//torun
            add();
            string(L"]");
            add();
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(825);
            _clp_qout(0);
            pop();
            line(826);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(827);
            _clp___quit(0);
            pop();
        if_87_1:
        if_87_0:;
        line(830);
        push_symbol(base+0);//deplist
        idxr0(1);
        _clp_fname(1);
        assign(base+9);//p1
        pop();
        line(831);
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
        line(833);
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
    if_86_1:
    if_86_0:;
    line(836);
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
    line(843);
    push_symbol(base+0);//cmd
    _clp_run(1);
    pop();
    line(853);
    line(845);
    string(L"error");
    _clp_file(1);
    if(!flag()) goto if_88_1;
        line(847);
        string(L"cat error");
        _clp_run(1);
        pop();
        line(851);
        _clp_qout(0);
        pop();
        line(852);
        _clp___quit(0);
        pop();
    if_88_1:
    if_88_0:;
    line(855);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
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
    line(860);
    push_symbol(base+0);//fspec
    _clp_directory(1);
    assign(base+1);//d
    pop();
    line(863);
    line(861);
    push_symbol(base+1);//d
    _clp_len(1);
    push(&ONE);
    eqeq();
    if(!flag()) goto if_89_1;
        line(862);
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
    if_89_1:
    if_89_0:;
    line(864);
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
while(stack<base+12)PUSHNIL();
argno=4;
push_call("search_include",base);
//
    line(870);
    number(10);
    _clp_chr(1);
    assign(base+4);//nl
    pop();
    line(871);
    push_symbol(base+4);//nl
    string(L"#include");
    add();
    assign(base+5);//include
    pop();
    line(872);
    push_symbol(base+5);//include
    _clp_len(1);
    assign(base+6);//lenincl
    pop();
    line(873);
    line(875);
    push_symbol(base+4);//nl
    push_symbol(base+0);//txt
    add();
    assign(base+0);//txt
    pop();
    line(898);
    lab_90_1:
    line(877);
    push_symbol(base+5);//include
    push_symbol(base+0);//txt
    _clp_at(2);
    assign(base+7);//n
    push(&ZERO);
    gt();
    if(!flag()) goto lab_90_2;
        line(879);
        string(L"\"");
        push_symbol(base+0);//txt
        push_symbol(base+7);//n
        push_symbol(base+6);//lenincl
        add();
        _clp_at(3);
        assign(base+8);//n1
        pop();
        line(880);
        string(L"\"");
        push_symbol(base+0);//txt
        push_symbol(base+8);//n1
        addnum(1);
        _clp_at(3);
        assign(base+9);//n2
        pop();
        line(881);
        push_symbol(base+4);//nl
        push_symbol(base+0);//txt
        push_symbol(base+7);//n
        push_symbol(base+6);//lenincl
        add();
        _clp_at(3);
        assign(base+10);//n3
        pop();
        line(895);
        line(883);
        push_symbol(base+8);//n1
        push_symbol(base+9);//n2
        lt();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+9);//n2
        push_symbol(base+10);//n3
        lt();
        }
        if(!flag()) goto if_91_1;
            line(884);
            push_symbol(base+0);//txt
            push_symbol(base+8);//n1
            addnum(1);
            push_symbol(base+9);//n2
            push_symbol(base+8);//n1
            sub();
            addnum(-1);
            _clp_substr(3);
            assign(base+11);//f
            pop();
            line(894);
            line(886);
            push_symbol(base+11);//f
            push_symbol(base+1);//dep
            push_symbol(base+2);//dir
            push_symbol(base+3);//todo
            _clp_byrules(4);
            if(!flag()) goto if_92_1;
            goto if_92_0;
            if_92_1:
            line(889);
            push_symbol(base+11);//f
            push_symbol(base+1);//dep
            push_symbol(base+2);//dir
            push_symbol(base+3);//todo
            _clp_byhand(4);
            if(!flag()) goto if_92_2;
            goto if_92_0;
            if_92_2:
            line(892);
            if_92_3:
            if_92_0:;
        if_91_1:
        if_91_0:;
        line(897);
        push_symbol(base+0);//txt
        push_symbol(base+10);//n3
        _clp_substr(2);
        assign(base+0);//txt
        pop();
    goto lab_90_1;
    lab_90_2:;
    line(899);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
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
    line(907);
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+0);//dirlist
    pop();
    line(908);
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+1);//liblist
    pop();
    line(909);
    string(L"BUILD_SHR");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+2);//sharing
    pop();
    line(911);
    string(L"");
    assign(base+5);//txt
    pop();
    line(912);
    line(988);
    {
    line(915);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_93_0:
    push_symbol(base+1);//liblist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_93_2;
        line(919);
        line(917);
        push_symbol(base+1);//liblist
        push_symbol(base+3);//n
        idxr();
        assign(base+6);//f0
        _clp_empty(1);
        if(!flag()) goto if_94_1;
            line(918);
            goto lab_93_1;//loop
        if_94_1:
        if_94_0:;
        line(931);
        line(921);
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
        if(!flag()) goto if_95_1;
            line(922);
            push_symbol(base+6);//f0
            assign(base+7);//f1
            pop();
            line(923);
            push_symbol(base+6);//f0
            assign(base+8);//f2
            pop();
            line(924);
            push_symbol(base+6);//f0
            assign(base+9);//f3
            pop();
        goto if_95_0;
        if_95_1:
        line(925);
            line(926);
            push_symbol(base+6);//f0
            string(L".lib");
            add();
            assign(base+7);//f1
            pop();
            line(929);
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
            line(930);
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
        if_95_2:
        if_95_0:;
        line(983);
        {
        line(933);
        push(&ONE);
        int sg=sign();
        push(&ZERO);
        assign(base+4);//i
        lab_96_0:
        push_symbol(base+0);//dirlist
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_96_2;
            line(947);
            line(935);
            push_symbol(base+4);//i
            push(&ZERO);
            lteq();
            if(!flag()) goto if_97_1;
                line(936);
                push_symbol(base+7);//f1
                assign(base+10);//pf1
                pop();
                line(937);
                push_symbol(base+8);//f2
                assign(base+11);//pf2
                pop();
                line(938);
                push_symbol(base+9);//f3
                assign(base+12);//pf3
                pop();
            goto if_97_0;
            if_97_1:
            line(939);
                line(942);
                line(940);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_empty(1);
                if(!flag()) goto if_98_1;
                    line(941);
                    goto lab_96_1;//loop
                if_98_1:
                if_98_0:;
                line(944);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+7);//f1
                add();
                assign(base+10);//pf1
                pop();
                line(945);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+8);//f2
                add();
                assign(base+11);//pf2
                pop();
                line(946);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+9);//f3
                add();
                assign(base+12);//pf3
                pop();
            if_97_2:
            if_97_0:;
            line(982);
            line(953);
            string(L"static");
            push_symbol(base+2);//sharing
            ss();
            if(!flag()) goto if_99_1;
                line(966);
                line(957);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_100_1;
                    line(958);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(959);
                    goto lab_96_2;//exit
                goto if_100_0;
                if_100_1:
                line(960);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_100_2;
                    line(961);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(962);
                    goto lab_96_2;//exit
                goto if_100_0;
                if_100_2:
                line(963);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_100_3;
                    line(964);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(965);
                    goto lab_96_2;//exit
                if_100_3:
                if_100_0:;
            goto if_99_0;
            if_99_1:
            line(968);
                line(981);
                line(972);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_101_1;
                    line(973);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(974);
                    goto lab_96_2;//exit
                goto if_101_0;
                if_101_1:
                line(975);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_101_2;
                    line(976);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(977);
                    goto lab_96_2;//exit
                goto if_101_0;
                if_101_2:
                line(978);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_101_3;
                    line(979);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(980);
                    goto lab_96_2;//exit
                if_101_3:
                if_101_0:;
            if_99_2:
            if_99_0:;
        lab_96_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+4);//i
        add();
        assign(base+4);//i
        goto lab_96_0;
        lab_96_2:;
        }
        line(987);
        line(985);
        push_symbol(base+4);//i
        push_symbol(base+0);//dirlist
        _clp_len(1);
        gt();
        if(!flag()) goto if_102_1;
            line(986);
            push_symbol(base+5);//txt
            push_symbol(base+6);//f0
            string(L" ");
            add();
            add();
            assign(base+5);//txt
            pop();
        if_102_1:
        if_102_0:;
    lab_93_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_93_0;
    lab_93_2:;
    }
    line(990);
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
    line(995);
    line(1002);
    {
    line(997);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_103_0:
    push_symbol(base+0);//dirlist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_103_2;
        line(998);
        push_symbol(base+0);//dirlist
        push_symbol(base+2);//n
        idxr();
        _clp_dirsep(0);
        add();
        push_symbol(base+1);//fnamext
        add();
        assign(base+3);//pathname
        pop();
        line(1001);
        line(999);
        push_symbol(base+3);//pathname
        _clp_file(1);
        if(!flag()) goto if_104_1;
            line(1000);
            push_symbol(base+3);//pathname
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_104_1:
        if_104_0:;
    lab_103_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_103_0;
    lab_103_2:;
    }
    line(1003);
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
    line(1014);
    push_symbol(base+0);//fil
    _clp_fname(1);
    assign(base+4);//f
    pop();
    line(1015);
    push_symbol(base+0);//fil
    _clp_fext(1);
    assign(base+5);//e
    pop();
    line(1016);
    line(1017);
    line(1018);
    line(1037);
    {
    line(1020);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//i
    lab_105_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_105_2;
        line(1036);
        line(1022);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+9);//i
        idxr();
        idxr0(2);
        push_symbol(base+5);//e
        eqeq();
        if(!flag()) goto if_106_1;
            line(1024);
            push_symbol(_st_s_rules_ptr());//global
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            assign(base+8);//e0
            pop();
            line(1035);
            line(1028);
            push(&NIL);
            push_symbol(base+2);//dir
            push_symbol(base+4);//f
            push_symbol(base+8);//e0
            add();
            _clp_search_file(2);
            assign(base+7);//r
            neeq();
            if(!flag()) goto if_107_1;
                line(1029);
                push_symbol(base+7);//r
                _clp_fpath(1);
                assign(base+6);//p
                pop();
                line(1030);
                push_symbol(base+1);//dep
                push_symbol(base+6);//p
                push_symbol(base+4);//f
                add();
                push_symbol(base+5);//e
                add();
                _clp_aadd(2);
                pop();
                line(1033);
                line(1031);
                push(&ZERO);
                push_symbol(base+3);//todo
                push_symbol_ref(base+6);//p
                push_symbol_ref(base+4);//f
                push_symbol_ref(base+5);//e
                block(_blk_byrules_0,3);
                _clp_ascan(2);
                eqeq();
                if(!flag()) goto if_108_1;
                    line(1032);
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
                if_108_1:
                if_108_0:;
                line(1034);
                push(&TRUE);
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            if_107_1:
            if_107_0:;
        if_106_1:
        if_106_0:;
    lab_105_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//i
    add();
    assign(base+9);//i
    goto lab_105_0;
    lab_105_2:;
    }
    line(1038);
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
    line(1049);
    push_symbol(base+2);//dir
    push_symbol(base+0);//f
    _clp_search_file(2);
    assign(base+4);//pn
    pop();
    line(1054);
    line(1051);
    push_symbol(base+4);//pn
    push(&NIL);
    neeq();
    if(!flag()) goto if_109_1;
        line(1052);
        push_symbol(base+1);//dep
        push_symbol(base+4);//pn
        _clp_aadd(2);
        pop();
        line(1053);
        push(&TRUE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_109_1:
    if_109_0:;
    line(1055);
    push(&FALSE);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
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
    line(1060);
    push_symbol(base+0);//x
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+0);//x
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+2);//ix
    pop();
    line(1061);
    push_symbol(base+1);//y
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+1);//y
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+3);//iy
    pop();
    line(1062);
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
    line(1067);
    line(1072);
    {
    line(1068);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_110_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_110_2;
        line(1071);
        line(1069);
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
        if(!flag()) goto if_111_1;
            line(1070);
            push_symbol(base+2);//n
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_111_1:
        if_111_0:;
    lab_110_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_110_0;
    lab_110_2:;
    }
    line(1073);
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
    line(1078);
    line(1088);
    {
    line(1079);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_112_0:
    push_symbol(base+1);//sep
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_112_2;
        line(1081);
        push_symbol(base+1);//sep
        push_symbol(base+2);//n
        push(&ONE);
        _clp_substr(3);
        assign(base+3);//s
        pop();
        line(1087);
        line(1083);
        push(&ZERO);
        push_symbol(base+3);//s
        push_symbol(base+0);//txt
        _clp_at(2);
        lt();
        if(!flag()) goto if_113_1;
            line(1084);
            goto lab_112_2;//exit
        goto if_113_0;
        if_113_1:
        line(1085);
            line(1086);
            push(&NIL);
            assign(base+3);//s
            pop();
        if_113_2:
        if_113_0:;
    lab_112_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_112_0;
    lab_112_2:;
    }
    line(1089);
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

