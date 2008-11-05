
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

//input: build.ppo (5.0.11)

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
    line(73);
    line(70);
    push_symbol(_st_s_quiet_ptr());//global
    topnot();
    if(!flag()) goto if_1_1;
        line(71);
        string(nls_text(L"CCC Program Builder "));
        string(L"1.2.25");
        add();
        string(L" Copyright (C) ComFirm Bt.");
        add();
        _clp_qqout(1);
        pop();
        line(72);
        _clp_qout(0);
        pop();
    if_1_1:
    if_1_0:;
    line(159);
    {
    line(76);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_2_0:
    push_symbol(base+0);//opt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_2_2;
        line(77);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        _clp_procpar(1);
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        assign(idxl());
        pop();
        line(158);
        line(79);
        string(L"-l");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_1;
            line(80);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_libnam_ptr());//global
            pop();
            line(81);
            push(&FALSE);
            assign(_st_s_shared_ptr());//global
            pop();
        goto if_3_0;
        if_3_1:
        line(84);
        string(L"-s");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_2;
            line(85);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_libnam_ptr());//global
            pop();
            line(86);
            push(&TRUE);
            assign(_st_s_shared_ptr());//global
            pop();
        goto if_3_0;
        if_3_2:
        line(89);
        string(L"-d");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_3;
            line(94);
            line(90);
            push_symbol(_st_s_srcdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_4_1;
                line(91);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_srcdir_ptr());//global
                pop();
            goto if_4_0;
            if_4_1:
            line(92);
                line(93);
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
        line(97);
        string(L"-i");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_4;
            line(102);
            line(98);
            push_symbol(_st_s_incdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_5_1;
                line(99);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_incdir_ptr());//global
                pop();
            goto if_5_0;
            if_5_1:
            line(100);
                line(101);
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
        line(105);
        string(L"-p");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_5;
            line(110);
            line(106);
            push_symbol(_st_s_libdir_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_6_1;
                line(107);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_libdir_ptr());//global
                pop();
            goto if_6_0;
            if_6_1:
            line(108);
                line(109);
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
        line(113);
        string(L"-b");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_6;
            line(118);
            line(114);
            push_symbol(_st_s_libfil_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_7_1;
                line(115);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_libfil_ptr());//global
                pop();
            goto if_7_0;
            if_7_1:
            line(116);
                line(117);
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
        line(121);
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
            line(126);
            line(122);
            push_symbol(_st_s_main_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_8_1;
                line(123);
                push_symbol(base+0);//opt
                push_symbol(base+1);//n
                idxr();
                number(3);
                _clp_substr(2);
                assign(_st_s_main_ptr());//global
                pop();
            goto if_8_0;
            if_8_1:
            line(124);
                line(125);
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
        line(129);
        string(L"-h");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_8;
            line(130);
            _clp_usage(0);
            pop();
            line(131);
            _clp___quit(0);
            pop();
        goto if_3_0;
        if_3_8:
        line(133);
        string(L"-q");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_9;
            line(134);
            push(&TRUE);
            assign(_st_s_quiet_ptr());//global
            pop();
        goto if_3_0;
        if_3_9:
        line(136);
        string(L"-v");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        number(2);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_10;
            line(137);
            push(&TRUE);
            assign(_st_s_version_ptr());//global
            pop();
        goto if_3_0;
        if_3_10:
        line(139);
        string(L"--debug");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        eqeq();
        if(!flag()) goto if_3_11;
            line(140);
            push(&TRUE);
            assign(_st_s_debug_ptr());//global
            pop();
        goto if_3_0;
        if_3_11:
        line(142);
        string(L"@");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        push(&ONE);
        _clp_left(2);
        eqeq();
        if(!flag()) goto if_3_12;
            line(143);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            number(2);
            _clp_substr(2);
            push_symbol(base+0);//opt
            _clp_readpar(2);
            pop();
        goto if_3_0;
        if_3_12:
        line(145);
        string(L"=");
        push_symbol(base+0);//opt
        push_symbol(base+1);//n
        idxr();
        ss();
        if(!flag()) goto if_3_13;
            line(146);
            push_symbol(base+0);//opt
            push_symbol(base+1);//n
            idxr();
            _clp_putenv(1);
            pop();
            line(151);
            line(149);
            string(L"on");
            string(L"BUILD_DBG");
            _clp_getenv(1);
            _clp_lower(1);
            ss();
            if(!flag()) goto if_9_1;
                line(150);
                push(&TRUE);
                assign(_st_s_debug_ptr());//global
                pop();
            if_9_1:
            if_9_0:;
        goto if_3_0;
        if_3_13:
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
        if_3_14:
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
    push_symbol(_st_s_version_ptr());//global
    if(!flag()) goto if_10_1;
        line(163);
        _clp___quit(0);
        pop();
    if_10_1:
    if_10_0:;
    line(166);
    _clp_root(0);
    pop();
    line(167);
    _clp_params(0);
    pop();
    line(168);
    _clp_build(0);
    pop();
    line(170);
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
stack=base+min(argno,2);
while(stack<base+6)PUSHNIL();
argno=2;
push_call("readpar",base);
//
    line(175);
    push_symbol(base+0);//parfil
    _clp_memoread(1);
    assign(base+2);//par
    pop();
    line(182);
    line(177);
    push_symbol(base+2);//par
    _clp_empty(1);
    if(!flag()) goto if_11_1;
        line(181);
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
    line(190);
    line(184);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_12_1;
        line(189);
        line(185);
        push_symbol(base+2);//par
        _clp_empty(1);
        if(!flag()) goto if_13_1;
            line(186);
            string(L"Build parfile empty:");
            push_symbol(base+0);//parfil
            _clp_qqout(2);
            pop();
            _clp_qout(0);
            pop();
        goto if_13_0;
        if_13_1:
        line(187);
            line(188);
            string(L"Build parfile:");
            push_symbol(base+0);//parfil
            _clp_qqout(2);
            pop();
            _clp_qout(0);
            pop();
        if_13_2:
        if_13_0:;
    if_12_1:
    if_12_0:;
    line(192);
    push_symbol(base+2);//par
    number(13);
    _clp_chr(1);
    string(L"");
    _clp_strtran(3);
    assign(base+2);//par
    pop();
    line(193);
    push_symbol(base+2);//par
    number(10);
    _clp_chr(1);
    _clp_split(2);
    assign(base+2);//par
    pop();
    line(207);
    {
    line(195);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_14_0:
    push_symbol(base+2);//par
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_14_2;
        line(196);
        push_symbol(base+2);//par
        push_symbol(base+3);//n
        idxr();
        assign(base+4);//p
        pop();
        line(199);
        line(197);
        string(L"#");
        push_symbol(base+4);//p
        ss();
        if(!flag()) goto if_15_1;
            line(198);
            push_symbol(base+4);//p
            string(L"#");
            push_symbol(base+4);//p
            _clp_at(2);
            addnum(-1);
            _clp_left(2);
            assign(base+4);//p
            pop();
        if_15_1:
        if_15_0:;
        line(201);
        push_symbol(base+4);//p
        string(L" ");
        _clp_split(2);
        assign(base+4);//p
        pop();
        line(206);
        {
        line(202);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+5);//i
        lab_16_0:
        push_symbol(base+4);//p
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_16_2;
            line(205);
            line(203);
            push_symbol(base+4);//p
            push_symbol(base+5);//i
            idxr();
            _clp_empty(1);
            topnot();
            if(!flag()) goto if_17_1;
                line(204);
                push_symbol(base+1);//opt
                push_symbol(base+4);//p
                push_symbol(base+5);//i
                idxr();
                _clp_aadd(2);
                pop();
            if_17_1:
            if_17_0:;
        lab_16_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+5);//i
        add();
        assign(base+5);//i
        goto lab_16_0;
        lab_16_2:;
        }
    lab_14_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_14_0;
    lab_14_2:;
    }
    line(208);
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
    line(212);
    line(221);
    lab_18_1:
    line(214);
    push(&ZERO);
    string(L"$$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_18_2;
        line(215);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(216);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(3);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(217);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(218);
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
        line(219);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(220);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_18_1;
    lab_18_2:;
    line(230);
    lab_19_1:
    line(223);
    push(&ZERO);
    string(L"$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_19_2;
        line(224);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(225);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(2);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(226);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(227);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        _clp_getenv(1);
        add();
        assign(base+2);//p
        pop();
        line(228);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(229);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_19_1;
    lab_19_2:;
    line(232);
    push_symbol(base+0);//par
    string(L"\\");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(233);
    push_symbol(base+0);//par
    string(L"/");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(235);
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
    line(240);
    string(nls_text(L"BUILD -xExeNam|-lLibNam -dSrcDir -iIncDir -pLibDir -bLibFil -mMain"));
    _clp_qout(1);
    pop();
    line(241);
    _clp_qout(0);
    pop();
    line(242);
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
    line(248);
    line(285);
    line(250);
    string(L"BUILD_SRC");
    _clp_getenv(1);
    assign(base+0);//srcroot
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_20_1;
        line(254);
        line(252);
        push_symbol(base+0);//srcroot
        push(&ONE);
        _clp_right(2);
        string(L"/\\");
        ss();
        topnot();
        if(!flag()) goto if_21_1;
            line(253);
            push_symbol(base+0);//srcroot
            _clp_dirsep(0);
            add();
            assign(base+0);//srcroot
            pop();
        if_21_1:
        if_21_0:;
        line(258);
        line(256);
        push_symbol(_st_s_srcdir_ptr());//global
        push(&NIL);
        eqeq();
        if(!flag()) goto if_22_1;
            line(257);
            string(L".");
            assign(_st_s_srcdir_ptr());//global
            pop();
        if_22_1:
        if_22_0:;
        line(260);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+1);//d
        pop();
        line(262);
        string(L"");
        assign(_st_s_srcdir_ptr());//global
        pop();
        line(269);
        {
        line(263);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+2);//n
        lab_23_0:
        push_symbol(base+1);//d
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_23_2;
            line(268);
            line(264);
            push_symbol(base+1);//d
            push_symbol(base+2);//n
            idxr();
            push(&ONE);
            _clp_left(2);
            string(L"/\\");
            ss();
            if(!flag()) goto if_24_1;
                line(265);
                push_symbol(_st_s_srcdir_ptr());//global
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                string(L";");
                add();
                add();
                assign(_st_s_srcdir_ptr());//global
                pop();
            goto if_24_0;
            if_24_1:
            line(266);
                line(267);
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
            if_24_2:
            if_24_0:;
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
        line(284);
        line(272);
        push_symbol(_st_s_incdir_ptr());//global
        push(&NIL);
        neeq();
        if(!flag()) goto if_25_1;
            line(274);
            push_symbol(_st_s_incdir_ptr());//global
            string(L",;");
            _clp_xsplit(2);
            assign(base+1);//d
            pop();
            line(276);
            string(L"");
            assign(_st_s_incdir_ptr());//global
            pop();
            line(283);
            {
            line(277);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+2);//n
            lab_26_0:
            push_symbol(base+1);//d
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_26_2;
                line(282);
                line(278);
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                push(&ONE);
                _clp_left(2);
                string(L"/\\");
                ss();
                if(!flag()) goto if_27_1;
                    line(279);
                    push_symbol(_st_s_incdir_ptr());//global
                    push_symbol(base+1);//d
                    push_symbol(base+2);//n
                    idxr();
                    string(L";");
                    add();
                    add();
                    assign(_st_s_incdir_ptr());//global
                    pop();
                goto if_27_0;
                if_27_1:
                line(280);
                    line(281);
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
                if_27_2:
                if_27_0:;
            lab_26_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+2);//n
            add();
            assign(base+2);//n
            goto lab_26_0;
            lab_26_2:;
            }
        if_25_1:
        if_25_0:;
    if_20_1:
    if_20_0:;
    line(287);
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
    line(293);
    line(306);
    string(L"");
    assign(base+0);//txt
    pop();
    line(307);
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
    line(308);
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
    line(309);
    push_symbol(base+0);//txt
    string(L"BUILD_INC");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(310);
    push_symbol(base+0);//txt
    string(L"include");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(311);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(312);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(314);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(316);
    string(L"BUILD_INC=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(322);
    string(L"");
    assign(base+0);//txt
    pop();
    line(323);
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
    line(324);
    push_symbol(base+0);//txt
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(325);
    push_symbol(base+0);//txt
    string(L"lib");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(326);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(327);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(329);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(331);
    string(L"BUILD_LPT=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(337);
    string(L"");
    assign(base+0);//txt
    pop();
    line(338);
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
    line(339);
    push_symbol(base+0);//txt
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(340);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(341);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(342);
    string(L"BUILD_LIB=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(345);
    line(343);
    push_symbol(_st_s_libabs_ptr());//global
    if(!flag()) goto if_28_1;
        line(344);
        string(L"BUILD_LIB=");
        _clp_search_library(0);
        add();
        _clp_putenv(1);
        pop();
    if_28_1:
    if_28_0:;
    line(348);
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
    line(354);
    array(0);
    assign(base+0);//dir
    pop();
    line(355);
    array(0);
    assign(base+1);//obj
    pop();
    line(356);
    array(0);
    assign(base+2);//lib
    pop();
    line(357);
    array(0);
    assign(base+3);//mmd
    pop();
    line(358);
    array(0);
    assign(base+4);//todo
    pop();
    line(360);
    line(365);
    line(363);
    push_symbol(_st_s_main_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_29_1;
        line(364);
        push_symbol(_st_s_main_ptr());//global
        _clp_lower(1);
        string(L",;");
        _clp_xsplit(2);
        assign(base+3);//mmd
        pop();
    if_29_1:
    if_29_0:;
    line(372);
    line(368);
    push_symbol(_st_s_srcdir_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_30_1;
        line(369);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+0);//dir
        pop();
    goto if_30_0;
    if_30_1:
    line(370);
        line(371);
        string(L".");
        array(1);
        assign(base+0);//dir
        pop();
    if_30_2:
    if_30_0:;
    line(388);
    {
    line(374);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_31_0:
    push_symbol(base+0);//dir
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_31_2;
        line(376);
        string(L"");
        push_symbol(base+0);//dir
        push_symbol(base+8);//n
        idxr();
        _clp_qqout(2);
        pop();
        line(378);
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
        line(387);
        {
        line(380);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//i
        lab_32_0:
        push_symbol(base+5);//d1
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_32_2;
            line(382);
            push_symbol(base+5);//d1
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            _clp_lower(1);
            assign(base+6);//f
            pop();
            line(386);
            line(384);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            push_symbol(_st_s_primary_ptr());//global
            ss();
            if(!flag()) goto if_33_1;
                line(385);
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
            if_33_1:
            if_33_0:;
        lab_32_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//i
        add();
        assign(base+9);//i
        goto lab_32_0;
        lab_32_2:;
        }
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
    line(389);
    _clp_qout(0);
    pop();
    line(421);
    {
    line(394);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_34_0:
    push_symbol(base+1);//obj
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_34_2;
        line(396);
        push_symbol(base+1);//obj
        push_symbol(base+8);//n
        idxr();
        assign(base+6);//f
        pop();
        line(397);
        push_symbol(base+6);//f
        _clp_fname(1);
        assign(base+7);//o
        pop();
        line(399);
        push_symbol(base+7);//o
        string(L".obj");
        add();
        push_symbol(base+6);//f
        array(2);
        assign(base+11);//dep
        pop();
        line(418);
        line(401);
        push_symbol(base+6);//f
        _clp_fext(1);
        string(L".prg");
        eqeq();
        if(!flag()) goto if_35_1;
            line(402);
            push_symbol(base+6);//f
            _clp_memoread(1);
            assign(base+10);//txt
            pop();
            line(412);
            line(404);
            push(&ZERO);
            push_symbol(base+3);//mmd
            push_symbol_ref(base+7);//o
            block(_blk_build_0,1);
            _clp_ascan(2);
            neeq();
            if(!flag()) goto if_36_1;
            goto if_36_0;
            if_36_1:
            line(406);
            string(L"function main(");
            push_symbol(base+10);//txt
            ss();
            if(!flag()) goto if_36_2;
                line(409);
                line(407);
                push_symbol(_st_s_main_ptr());//global
                push(&NIL);
                eqeq();
                if(!flag()) goto if_37_1;
                    line(408);
                    push_symbol(base+3);//mmd
                    push_symbol(base+7);//o
                    _clp_aadd(2);
                    pop();
                if_37_1:
                if_37_0:;
            goto if_36_0;
            if_36_2:
            line(410);
                line(411);
                push_symbol(base+2);//lib
                push_symbol(base+7);//o
                _clp_aadd(2);
                pop();
            if_36_3:
            if_36_0:;
            line(414);
            push_symbol(base+10);//txt
            push_symbol(base+11);//dep
            push_symbol(base+0);//dir
            push_symbol(base+4);//todo
            _clp_search_include(4);
            pop();
        goto if_35_0;
        if_35_1:
        line(416);
        push(&ZERO);
        push_symbol(base+3);//mmd
        push_symbol_ref(base+7);//o
        block(_blk_build_1,1);
        _clp_ascan(2);
        eqeq();
        if(!flag()) goto if_35_2;
            line(417);
            push_symbol(base+2);//lib
            push_symbol(base+7);//o
            _clp_aadd(2);
            pop();
        if_35_2:
        if_35_0:;
        line(420);
        push_symbol(base+4);//todo
        push_symbol(base+11);//dep
        _clp_aadd(2);
        pop();
    lab_34_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_34_0;
    lab_34_2:;
    }
    line(423);
    push_symbol(base+4);//todo
    push(&NIL);
    push(&NIL);
    block(_blk_build_2,0);
    _clp_asort(4);
    pop();
    line(435);
    line(427);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_38_1;
        line(428);
        string(L"main:");
        push_symbol(base+3);//mmd
        _clp_qout(2);
        pop();
        line(429);
        string(L"lib :");
        push_symbol(base+2);//lib
        _clp_qout(2);
        pop();
        line(430);
        _clp_qout(0);
        pop();
        line(433);
        {
        line(431);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_39_0:
        push_symbol(base+4);//todo
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_39_2;
            line(432);
            push_symbol(base+4);//todo
            push_symbol(base+8);//n
            idxr();
            _clp_qout(1);
            pop();
        lab_39_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+8);//n
        add();
        assign(base+8);//n
        goto lab_39_0;
        lab_39_2:;
        }
        line(434);
        _clp_qout(0);
        pop();
    if_38_1:
    if_38_0:;
    line(439);
    {
    line(437);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_40_0:
    push_symbol(base+4);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_40_2;
        line(438);
        push_symbol(base+4);//todo
        push_symbol(base+8);//n
        idxr();
        _clp_makeobj(1);
        pop();
    lab_40_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_40_0;
    lab_40_2:;
    }
    line(458);
    line(443);
    push_symbol(_st_s_libnam_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_41_1;
        line(444);
        push_symbol(_st_s_libnam_ptr());//global
        push_symbol(base+2);//lib
        _clp_makelib(2);
        pop();
        line(448);
        line(446);
        push_symbol(_st_s_shared_ptr());//global
        push(&TRUE);
        eqeq();
        if(!flag()) goto if_42_1;
            line(447);
            push_symbol(_st_s_libnam_ptr());//global
            push_symbol(base+2);//lib
            _clp_makeso(2);
            pop();
        if_42_1:
        if_42_0:;
        line(452);
        {
        line(450);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_43_0:
        push_symbol(base+3);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_43_2;
            line(451);
            push_symbol(base+3);//mmd
            push_symbol(base+8);//n
            idxr();
            push_symbol(_st_s_libnam_ptr());//global
            _clp_makeexe1(2);
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
    goto if_41_0;
    if_41_1:
    line(454);
        line(457);
        {
        line(455);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_44_0:
        push_symbol(base+3);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_44_2;
            line(456);
            push_symbol(base+3);//mmd
            push_symbol(base+8);//n
            idxr();
            push_symbol(base+2);//lib
            _clp_makeexe(2);
            pop();
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
    if_41_2:
    if_41_0:;
    line(460);
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
    line(467);
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
    line(468);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(469);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2so.bat");
    add();
    assign(base+7);//torun
    pop();
    line(470);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(477);
    line(472);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_45_1;
        line(473);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(474);
        _clp_qout(0);
        pop();
        line(475);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(476);
        _clp___quit(0);
        pop();
    if_45_1:
    if_45_0:;
    line(479);
    push_symbol(base+7);//torun
    string(L" lib");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(481);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(484);
    line(482);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_46_1;
        line(483);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_46_1:
    if_46_0:;
    line(488);
    line(486);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_47_1;
        line(487);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_47_1:
    if_47_0:;
    line(511);
    {
    line(490);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_48_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_48_2;
        line(492);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(493);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+4);//depend
        add();
        add();
        assign(base+7);//torun
        pop();
        line(494);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(495);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(506);
        line(497);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_49_1;
            line(498);
            push_symbol(base+4);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(499);
            _clp_qout(0);
            pop();
            line(500);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(501);
            _clp___quit(0);
            pop();
        goto if_49_0;
        if_49_1:
        line(503);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_49_2;
            line(505);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_49_2:
        if_49_0:;
        line(510);
        line(508);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_50_1;
            line(509);
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
        if_50_1:
        if_50_0:;
    lab_48_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_48_0;
    lab_48_2:;
    }
    line(515);
    line(513);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_51_1;
        line(514);
        _clp_qout(0);
        pop();
    if_51_1:
    if_51_0:;
    line(519);
    line(517);
    push_symbol(base+6);//update
    if(!flag()) goto if_52_1;
        line(518);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_52_1:
    if_52_0:;
    line(521);
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
    line(527);
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
    line(528);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(529);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2lib.bat");
    add();
    assign(base+7);//torun
    pop();
    line(530);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+8);//objdir
    pop();
    line(531);
    line(538);
    line(533);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_53_1;
        line(534);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(535);
        _clp_qout(0);
        pop();
        line(536);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(537);
        _clp___quit(0);
        pop();
    if_53_1:
    if_53_0:;
    line(540);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(542);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(545);
    line(543);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_54_1;
        line(544);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_54_1:
    if_54_0:;
    line(549);
    line(547);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_55_1;
        line(548);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_55_1:
    if_55_0:;
    line(571);
    {
    line(551);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_56_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_56_2;
        line(553);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(554);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(555);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(566);
        line(557);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_57_1;
            line(558);
            push_symbol(base+4);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(559);
            _clp_qout(0);
            pop();
            line(560);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(561);
            _clp___quit(0);
            pop();
        goto if_57_0;
        if_57_1:
        line(563);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_57_2;
            line(565);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_57_2:
        if_57_0:;
        line(570);
        line(568);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_58_1;
            line(569);
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
        if_58_1:
        if_58_0:;
    lab_56_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_56_0;
    lab_56_2:;
    }
    line(575);
    line(573);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_59_1;
        line(574);
        _clp_qout(0);
        pop();
    if_59_1:
    if_59_0:;
    line(602);
    line(577);
    push_symbol(base+6);//update
    if(!flag()) goto if_60_1;
        line(582);
        {
        line(580);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_61_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_61_2;
            line(581);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
            pop();
        lab_61_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_61_0;
        lab_61_2:;
        }
        line(601);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_60_1:
    if_60_0:;
    line(604);
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
    line(610);
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
    line(611);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(612);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2exe.bat");
    add();
    assign(base+7);//torun
    pop();
    line(613);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+8);//objdir
    pop();
    line(614);
    line(621);
    line(616);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_62_1;
        line(617);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(618);
        _clp_qout(0);
        pop();
        line(619);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(620);
        _clp___quit(0);
        pop();
    if_62_1:
    if_62_0:;
    line(623);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(626);
    line(624);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_63_1;
        line(625);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_63_1:
    if_63_0:;
    line(630);
    line(628);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_64_1;
        line(629);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_64_1:
    if_64_0:;
    line(657);
    {
    line(632);
    push(&ONE);
    int sg=sign();
    push(&ZERO);
    assign(base+9);//n
    lab_65_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_65_2;
        line(638);
        line(634);
        push_symbol(base+9);//n
        push(&ZERO);
        eqeq();
        if(!flag()) goto if_66_1;
            line(635);
            push_symbol(base+0);//exenam
            assign(base+4);//depend
            pop();
        goto if_66_0;
        if_66_1:
        line(636);
            line(637);
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
        if_66_2:
        if_66_0:;
        line(640);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(641);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(652);
        line(643);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_67_1;
            line(644);
            push_symbol(base+4);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(645);
            _clp_qout(0);
            pop();
            line(646);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(647);
            _clp___quit(0);
            pop();
        goto if_67_0;
        if_67_1:
        line(649);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_67_2;
            line(651);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_67_2:
        if_67_0:;
        line(656);
        line(654);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_68_1;
            line(655);
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
        if_68_1:
        if_68_0:;
    lab_65_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_65_0;
    lab_65_2:;
    }
    line(661);
    line(659);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_69_1;
        line(660);
        _clp_qout(0);
        pop();
    if_69_1:
    if_69_0:;
    line(694);
    line(663);
    push_symbol(base+6);//update
    if(!flag()) goto if_70_1;
        line(664);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+0);//exenam
        add();
        add();
        assign(base+7);//torun
        pop();
        line(669);
        {
        line(667);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_71_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_71_2;
            line(668);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
            pop();
        lab_71_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_71_0;
        lab_71_2:;
        }
        line(693);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_70_1:
    if_70_0:;
    line(696);
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
    line(702);
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
    line(703);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(704);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"lib2exe.bat");
    add();
    assign(base+7);//torun
    pop();
    line(705);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(712);
    line(707);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_72_1;
        line(708);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(709);
        _clp_qout(0);
        pop();
        line(710);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(711);
        _clp___quit(0);
        pop();
    if_72_1:
    if_72_0:;
    line(714);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(717);
    line(715);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_73_1;
        line(716);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_73_1:
    if_73_0:;
    line(721);
    line(719);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_74_1;
        line(720);
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
    line(724);
    push_symbol(base+0);//mmod
    assign(base+4);//depend
    pop();
    line(725);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(726);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".obj");
    add();
    assign(base+4);//depend
    pop();
    line(727);
    push_symbol(base+4);//depend
    _clp_ftime(1);
    assign(base+5);//tdepend
    pop();
    line(736);
    line(729);
    push_symbol(base+5);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_75_1;
        line(730);
        push_symbol(base+4);//depend
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(731);
        _clp_qout(0);
        pop();
        line(732);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(733);
        _clp___quit(0);
        pop();
    goto if_75_0;
    if_75_1:
    line(734);
    push_symbol(base+3);//ttarget
    push_symbol(base+5);//tdepend
    lt();
    if(!flag()) goto if_75_2;
        line(735);
        push(&TRUE);
        assign(base+6);//update
        pop();
    if_75_2:
    if_75_0:;
    line(739);
    line(737);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_76_1;
        line(738);
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
    line(742);
    push_symbol(base+1);//libnam
    assign(base+4);//depend
    pop();
    line(743);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(744);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".lib");
    add();
    assign(base+4);//depend
    pop();
    line(745);
    push_symbol(base+4);//depend
    _clp_ftime(1);
    assign(base+5);//tdepend
    pop();
    line(754);
    line(747);
    push_symbol(base+5);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_77_1;
        line(748);
        push_symbol(base+4);//depend
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(749);
        _clp_qout(0);
        pop();
        line(750);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(751);
        _clp___quit(0);
        pop();
    goto if_77_0;
    if_77_1:
    line(752);
    push_symbol(base+3);//ttarget
    push_symbol(base+5);//tdepend
    lt();
    if(!flag()) goto if_77_2;
        line(753);
        push(&TRUE);
        assign(base+6);//update
        pop();
    if_77_2:
    if_77_0:;
    line(757);
    line(755);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_78_1;
        line(756);
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
    if_78_1:
    if_78_0:;
    line(762);
    line(760);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_79_1;
        line(761);
        _clp_qout(0);
        pop();
    if_79_1:
    if_79_0:;
    line(766);
    line(764);
    push_symbol(base+6);//update
    if(!flag()) goto if_80_1;
        line(765);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_80_1:
    if_80_0:;
    line(768);
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
    line(774);
    push_symbol(base+0);//deplist
    idxr0(1);
    assign(base+1);//target
    pop();
    line(775);
    push_symbol(base+0);//deplist
    idxr0(2);
    assign(base+2);//depend
    pop();
    line(776);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+3);//objdir
    pop();
    line(777);
    line(778);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(779);
    line(783);
    line(781);
    push_symbol(base+1);//target
    _clp_fext(1);
    string(L".obj");
    eqeq();
    if(!flag()) goto if_81_1;
        line(782);
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
    if_81_1:
    if_81_0:;
    line(785);
    push_symbol(base+1);//target
    _clp_ftime(1);
    assign(base+4);//ttarget
    pop();
    line(788);
    line(786);
    push_symbol(base+4);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_82_1;
        line(787);
        string(L"");
        assign(base+4);//ttarget
        pop();
    if_82_1:
    if_82_0:;
    line(792);
    line(790);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_83_1;
        line(791);
        push_symbol(base+1);//target
        string(L"[");
        push_symbol(base+4);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_83_1:
    if_83_0:;
    line(812);
    {
    line(794);
    push(&ONE);
    int sg=sign();
    number(2);
    assign(base+8);//n
    lab_84_0:
    push_symbol(base+0);//deplist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_84_2;
        line(795);
        push_symbol(base+0);//deplist
        push_symbol(base+8);//n
        idxr();
        assign(base+2);//depend
        pop();
        line(796);
        push_symbol(base+2);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(807);
        line(798);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_85_1;
            line(799);
            push_symbol(base+0);//deplist
            push_symbol(base+8);//n
            idxr();
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(800);
            _clp_qout(0);
            pop();
            line(801);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(802);
            _clp___quit(0);
            pop();
        goto if_85_0;
        if_85_1:
        line(804);
        push_symbol(base+4);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_85_2;
            line(806);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_85_2:
        if_85_0:;
        line(811);
        line(809);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_86_1;
            line(810);
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
        if_86_1:
        if_86_0:;
    lab_84_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_84_0;
    lab_84_2:;
    }
    line(817);
    line(815);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_87_1;
        line(816);
        _clp_qout(0);
        pop();
    if_87_1:
    if_87_0:;
    line(837);
    line(820);
    push_symbol(base+6);//update
    if(!flag()) goto if_88_1;
        line(822);
        string(L"BUILD_BAT");
        _clp_getenv(1);
        _clp_dirsep(0);
        add();
        assign(base+7);//torun
        pop();
        line(823);
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
        line(824);
        push_symbol(base+7);//torun
        string(L".bat");
        add();
        assign(base+7);//torun
        pop();
        line(831);
        line(826);
        push_symbol(base+7);//torun
        _clp_file(1);
        topnot();
        if(!flag()) goto if_89_1;
            line(827);
            string(L"[");
            push_symbol(base+7);//torun
            add();
            string(L"]");
            add();
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(828);
            _clp_qout(0);
            pop();
            line(829);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(830);
            _clp___quit(0);
            pop();
        if_89_1:
        if_89_0:;
        line(833);
        push_symbol(base+0);//deplist
        idxr0(1);
        _clp_fname(1);
        assign(base+9);//p1
        pop();
        line(834);
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
        line(836);
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
    if_88_1:
    if_88_0:;
    line(839);
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
    line(846);
    push_symbol(base+0);//cmd
    _clp_run(1);
    pop();
    line(856);
    line(848);
    string(L"error");
    _clp_file(1);
    if(!flag()) goto if_90_1;
        line(850);
        string(L"cat error");
        _clp_run(1);
        pop();
        line(854);
        _clp_qout(0);
        pop();
        line(855);
        _clp___quit(0);
        pop();
    if_90_1:
    if_90_0:;
    line(858);
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
    line(863);
    push_symbol(base+0);//fspec
    _clp_directory(1);
    assign(base+1);//d
    pop();
    line(866);
    line(864);
    push_symbol(base+1);//d
    _clp_len(1);
    push(&ONE);
    eqeq();
    if(!flag()) goto if_91_1;
        line(865);
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
    if_91_1:
    if_91_0:;
    line(867);
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
    line(873);
    number(10);
    _clp_chr(1);
    assign(base+4);//nl
    pop();
    line(874);
    push_symbol(base+4);//nl
    string(L"#include");
    add();
    assign(base+5);//include
    pop();
    line(875);
    push_symbol(base+5);//include
    _clp_len(1);
    assign(base+6);//lenincl
    pop();
    line(876);
    line(878);
    push_symbol(base+4);//nl
    push_symbol(base+0);//txt
    add();
    assign(base+0);//txt
    pop();
    line(901);
    lab_92_1:
    line(880);
    push_symbol(base+5);//include
    push_symbol(base+0);//txt
    _clp_at(2);
    assign(base+7);//n
    push(&ZERO);
    gt();
    if(!flag()) goto lab_92_2;
        line(882);
        string(L"\"");
        push_symbol(base+0);//txt
        push_symbol(base+7);//n
        push_symbol(base+6);//lenincl
        add();
        _clp_at(3);
        assign(base+8);//n1
        pop();
        line(883);
        string(L"\"");
        push_symbol(base+0);//txt
        push_symbol(base+8);//n1
        addnum(1);
        _clp_at(3);
        assign(base+9);//n2
        pop();
        line(884);
        push_symbol(base+4);//nl
        push_symbol(base+0);//txt
        push_symbol(base+7);//n
        push_symbol(base+6);//lenincl
        add();
        _clp_at(3);
        assign(base+10);//n3
        pop();
        line(898);
        line(886);
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
        if(!flag()) goto if_93_1;
            line(887);
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
            line(897);
            line(889);
            push_symbol(base+11);//f
            push_symbol(base+1);//dep
            push_symbol(base+2);//dir
            push_symbol(base+3);//todo
            _clp_byrules(4);
            if(!flag()) goto if_94_1;
            goto if_94_0;
            if_94_1:
            line(892);
            push_symbol(base+11);//f
            push_symbol(base+1);//dep
            push_symbol(base+2);//dir
            push_symbol(base+3);//todo
            _clp_byhand(4);
            if(!flag()) goto if_94_2;
            goto if_94_0;
            if_94_2:
            line(895);
            if_94_3:
            if_94_0:;
        if_93_1:
        if_93_0:;
        line(900);
        push_symbol(base+0);//txt
        push_symbol(base+10);//n3
        _clp_substr(2);
        assign(base+0);//txt
        pop();
    goto lab_92_1;
    lab_92_2:;
    line(902);
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
    line(910);
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+0);//dirlist
    pop();
    line(911);
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+1);//liblist
    pop();
    line(912);
    string(L"BUILD_SHR");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+2);//sharing
    pop();
    line(914);
    string(L"");
    assign(base+5);//txt
    pop();
    line(915);
    line(991);
    {
    line(918);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_95_0:
    push_symbol(base+1);//liblist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_95_2;
        line(922);
        line(920);
        push_symbol(base+1);//liblist
        push_symbol(base+3);//n
        idxr();
        assign(base+6);//f0
        _clp_empty(1);
        if(!flag()) goto if_96_1;
            line(921);
            goto lab_95_1;//loop
        if_96_1:
        if_96_0:;
        line(934);
        line(924);
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
        if(!flag()) goto if_97_1;
            line(925);
            push_symbol(base+6);//f0
            assign(base+7);//f1
            pop();
            line(926);
            push_symbol(base+6);//f0
            assign(base+8);//f2
            pop();
            line(927);
            push_symbol(base+6);//f0
            assign(base+9);//f3
            pop();
        goto if_97_0;
        if_97_1:
        line(928);
            line(929);
            push_symbol(base+6);//f0
            string(L".lib");
            add();
            assign(base+7);//f1
            pop();
            line(932);
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
            line(933);
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
        if_97_2:
        if_97_0:;
        line(986);
        {
        line(936);
        push(&ONE);
        int sg=sign();
        push(&ZERO);
        assign(base+4);//i
        lab_98_0:
        push_symbol(base+0);//dirlist
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_98_2;
            line(950);
            line(938);
            push_symbol(base+4);//i
            push(&ZERO);
            lteq();
            if(!flag()) goto if_99_1;
                line(939);
                push_symbol(base+7);//f1
                assign(base+10);//pf1
                pop();
                line(940);
                push_symbol(base+8);//f2
                assign(base+11);//pf2
                pop();
                line(941);
                push_symbol(base+9);//f3
                assign(base+12);//pf3
                pop();
            goto if_99_0;
            if_99_1:
            line(942);
                line(945);
                line(943);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_empty(1);
                if(!flag()) goto if_100_1;
                    line(944);
                    goto lab_98_1;//loop
                if_100_1:
                if_100_0:;
                line(947);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+7);//f1
                add();
                assign(base+10);//pf1
                pop();
                line(948);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+8);//f2
                add();
                assign(base+11);//pf2
                pop();
                line(949);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+9);//f3
                add();
                assign(base+12);//pf3
                pop();
            if_99_2:
            if_99_0:;
            line(985);
            line(956);
            string(L"static");
            push_symbol(base+2);//sharing
            ss();
            if(!flag()) goto if_101_1;
                line(969);
                line(960);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_102_1;
                    line(961);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(962);
                    goto lab_98_2;//exit
                goto if_102_0;
                if_102_1:
                line(963);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_102_2;
                    line(964);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(965);
                    goto lab_98_2;//exit
                goto if_102_0;
                if_102_2:
                line(966);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_102_3;
                    line(967);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(968);
                    goto lab_98_2;//exit
                if_102_3:
                if_102_0:;
            goto if_101_0;
            if_101_1:
            line(971);
                line(984);
                line(975);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_103_1;
                    line(976);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(977);
                    goto lab_98_2;//exit
                goto if_103_0;
                if_103_1:
                line(978);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_103_2;
                    line(979);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(980);
                    goto lab_98_2;//exit
                goto if_103_0;
                if_103_2:
                line(981);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_103_3;
                    line(982);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(983);
                    goto lab_98_2;//exit
                if_103_3:
                if_103_0:;
            if_101_2:
            if_101_0:;
        lab_98_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+4);//i
        add();
        assign(base+4);//i
        goto lab_98_0;
        lab_98_2:;
        }
        line(990);
        line(988);
        push_symbol(base+4);//i
        push_symbol(base+0);//dirlist
        _clp_len(1);
        gt();
        if(!flag()) goto if_104_1;
            line(989);
            push_symbol(base+5);//txt
            push_symbol(base+6);//f0
            string(L" ");
            add();
            add();
            assign(base+5);//txt
            pop();
        if_104_1:
        if_104_0:;
    lab_95_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_95_0;
    lab_95_2:;
    }
    line(993);
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
    line(998);
    line(1005);
    {
    line(1000);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_105_0:
    push_symbol(base+0);//dirlist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_105_2;
        line(1001);
        push_symbol(base+0);//dirlist
        push_symbol(base+2);//n
        idxr();
        _clp_dirsep(0);
        add();
        push_symbol(base+1);//fnamext
        add();
        assign(base+3);//pathname
        pop();
        line(1004);
        line(1002);
        push_symbol(base+3);//pathname
        _clp_file(1);
        if(!flag()) goto if_106_1;
            line(1003);
            push_symbol(base+3);//pathname
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_106_1:
        if_106_0:;
    lab_105_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_105_0;
    lab_105_2:;
    }
    line(1006);
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
    line(1017);
    push_symbol(base+0);//fil
    _clp_fname(1);
    assign(base+4);//f
    pop();
    line(1018);
    push_symbol(base+0);//fil
    _clp_fext(1);
    assign(base+5);//e
    pop();
    line(1019);
    line(1020);
    line(1021);
    line(1040);
    {
    line(1023);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//i
    lab_107_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_107_2;
        line(1039);
        line(1025);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+9);//i
        idxr();
        idxr0(2);
        push_symbol(base+5);//e
        eqeq();
        if(!flag()) goto if_108_1;
            line(1027);
            push_symbol(_st_s_rules_ptr());//global
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            assign(base+8);//e0
            pop();
            line(1038);
            line(1031);
            push(&NIL);
            push_symbol(base+2);//dir
            push_symbol(base+4);//f
            push_symbol(base+8);//e0
            add();
            _clp_search_file(2);
            assign(base+7);//r
            neeq();
            if(!flag()) goto if_109_1;
                line(1032);
                push_symbol(base+7);//r
                _clp_fpath(1);
                assign(base+6);//p
                pop();
                line(1033);
                push_symbol(base+1);//dep
                push_symbol(base+6);//p
                push_symbol(base+4);//f
                add();
                push_symbol(base+5);//e
                add();
                _clp_aadd(2);
                pop();
                line(1036);
                line(1034);
                push(&ZERO);
                push_symbol(base+3);//todo
                push_symbol_ref(base+6);//p
                push_symbol_ref(base+4);//f
                push_symbol_ref(base+5);//e
                block(_blk_byrules_0,3);
                _clp_ascan(2);
                eqeq();
                if(!flag()) goto if_110_1;
                    line(1035);
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
                if_110_1:
                if_110_0:;
                line(1037);
                push(&TRUE);
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            if_109_1:
            if_109_0:;
        if_108_1:
        if_108_0:;
    lab_107_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//i
    add();
    assign(base+9);//i
    goto lab_107_0;
    lab_107_2:;
    }
    line(1041);
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
    line(1052);
    push_symbol(base+2);//dir
    push_symbol(base+0);//f
    _clp_search_file(2);
    assign(base+4);//pn
    pop();
    line(1057);
    line(1054);
    push_symbol(base+4);//pn
    push(&NIL);
    neeq();
    if(!flag()) goto if_111_1;
        line(1055);
        push_symbol(base+1);//dep
        push_symbol(base+4);//pn
        _clp_aadd(2);
        pop();
        line(1056);
        push(&TRUE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_111_1:
    if_111_0:;
    line(1058);
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
    line(1063);
    push_symbol(base+0);//x
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+0);//x
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+2);//ix
    pop();
    line(1064);
    push_symbol(base+1);//y
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+1);//y
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+3);//iy
    pop();
    line(1065);
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
    line(1070);
    line(1075);
    {
    line(1071);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_112_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_112_2;
        line(1074);
        line(1072);
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
        if(!flag()) goto if_113_1;
            line(1073);
            push_symbol(base+2);//n
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_113_1:
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
    line(1076);
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
    line(1081);
    line(1091);
    {
    line(1082);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_114_0:
    push_symbol(base+1);//sep
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_114_2;
        line(1084);
        push_symbol(base+1);//sep
        push_symbol(base+2);//n
        push(&ONE);
        _clp_substr(3);
        assign(base+3);//s
        pop();
        line(1090);
        line(1086);
        push(&ZERO);
        push_symbol(base+3);//s
        push_symbol(base+0);//txt
        _clp_at(2);
        lt();
        if(!flag()) goto if_115_1;
            line(1087);
            goto lab_114_2;//exit
        goto if_115_0;
        if_115_1:
        line(1088);
            line(1089);
            push(&NIL);
            assign(base+3);//s
            pop();
        if_115_2:
        if_115_0:;
    lab_114_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_114_0;
    lab_114_2:;
    }
    line(1092);
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

