
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

//input: build.ppo (5.0.17)

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
        string(L"1.3.00");
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
        assign2(idxxl());
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
            push_symbol(base+1);//n
            _clp_readpar(3);
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
stack=base+min(argno,3);
while(stack<base+7)PUSHNIL();
argno=3;
push_call("readpar",base);
//
    line(175);
    push_symbol(base+0);//parfil
    _clp_memoread(1);
    assign(base+3);//par
    pop();
    line(182);
    line(177);
    push_symbol(base+3);//par
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
        assign(base+3);//par
        pop();
    if_11_1:
    if_11_0:;
    line(190);
    line(184);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_12_1;
        line(189);
        line(185);
        push_symbol(base+3);//par
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
    push_symbol(base+3);//par
    number(13);
    _clp_chr(1);
    string(L"");
    _clp_strtran(3);
    assign(base+3);//par
    pop();
    line(193);
    push_symbol(base+3);//par
    number(10);
    _clp_chr(1);
    _clp_split(2);
    assign(base+3);//par
    pop();
    line(209);
    {
    line(195);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_14_0:
    push_symbol(base+3);//par
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_14_2;
        line(196);
        push_symbol(base+3);//par
        push_symbol(base+4);//n
        idxr();
        assign(base+5);//p
        pop();
        line(199);
        line(197);
        string(L"#");
        push_symbol(base+5);//p
        ss();
        if(!flag()) goto if_15_1;
            line(198);
            push_symbol(base+5);//p
            string(L"#");
            push_symbol(base+5);//p
            _clp_at(2);
            addnum(-1);
            _clp_left(2);
            assign(base+5);//p
            pop();
        if_15_1:
        if_15_0:;
        line(201);
        push_symbol(base+5);//p
        string(L" ");
        _clp_split(2);
        assign(base+5);//p
        pop();
        line(208);
        {
        line(202);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+6);//i
        lab_16_0:
        push_symbol(base+5);//p
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_16_2;
            line(207);
            line(203);
            push_symbol(base+5);//p
            push_symbol(base+6);//i
            idxr();
            _clp_empty(1);
            topnot();
            if(!flag()) goto if_17_1;
                line(204);
                push_symbol(base+1);//opt
                push(&NIL);
                _clp_aadd(2);
                pop();
                line(205);
                push_symbol(base+1);//opt
                push_symbol(base+2);//optx
                push(&ONE);
                add();
                assign(base+2);//optx
                _clp_ains(2);
                pop();
                line(206);
                push_symbol(base+5);//p
                push_symbol(base+6);//i
                idxr();
                push_symbol(base+1);//opt
                push_symbol(base+2);//optx
                assign2(idxxl());
                pop();
            if_17_1:
            if_17_0:;
        lab_16_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+6);//i
        add();
        assign(base+6);//i
        goto lab_16_0;
        lab_16_2:;
        }
    lab_14_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_14_0;
    lab_14_2:;
    }
    line(210);
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
    line(214);
    line(223);
    lab_18_1:
    line(216);
    push(&ZERO);
    string(L"$$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_18_2;
        line(217);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(218);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(3);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(219);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(220);
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
        line(221);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(222);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_18_1;
    lab_18_2:;
    line(232);
    lab_19_1:
    line(225);
    push(&ZERO);
    string(L"$(");
    push_symbol(base+0);//par
    _clp_at(2);
    assign(base+1);//n
    lt();
    if(!flag()) goto lab_19_2;
        line(226);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        assign(base+2);//p
        pop();
        line(227);
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(2);
        _clp_substr(2);
        assign(base+0);//par
        pop();
        line(228);
        string(L")");
        push_symbol(base+0);//par
        _clp_at(2);
        assign(base+1);//n
        pop();
        line(229);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(-1);
        _clp_left(2);
        _clp_getenv(1);
        add();
        assign(base+2);//p
        pop();
        line(230);
        push_symbol(base+2);//p
        push_symbol(base+0);//par
        push_symbol(base+1);//n
        addnum(1);
        _clp_substr(2);
        add();
        assign(base+2);//p
        pop();
        line(231);
        push_symbol(base+2);//p
        assign(base+0);//par
        pop();
    goto lab_19_1;
    lab_19_2:;
    line(234);
    push_symbol(base+0);//par
    string(L"\\");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(235);
    push_symbol(base+0);//par
    string(L"/");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//par
    pop();
    line(237);
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
    line(242);
    string(nls_text(L"BUILD -xExeNam|-lLibNam -dSrcDir -iIncDir -pLibDir -bLibFil -mMain"));
    _clp_qout(1);
    pop();
    line(243);
    _clp_qout(0);
    pop();
    line(244);
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
    line(250);
    line(287);
    line(252);
    string(L"BUILD_SRC");
    _clp_getenv(1);
    assign(base+0);//srcroot
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_20_1;
        line(256);
        line(254);
        push_symbol(base+0);//srcroot
        push(&ONE);
        _clp_right(2);
        string(L"/\\");
        ss();
        topnot();
        if(!flag()) goto if_21_1;
            line(255);
            push_symbol(base+0);//srcroot
            _clp_dirsep(0);
            add();
            assign(base+0);//srcroot
            pop();
        if_21_1:
        if_21_0:;
        line(260);
        line(258);
        push_symbol(_st_s_srcdir_ptr());//global
        push(&NIL);
        eqeq();
        if(!flag()) goto if_22_1;
            line(259);
            string(L".");
            assign(_st_s_srcdir_ptr());//global
            pop();
        if_22_1:
        if_22_0:;
        line(262);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+1);//d
        pop();
        line(264);
        string(L"");
        assign(_st_s_srcdir_ptr());//global
        pop();
        line(271);
        {
        line(265);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+2);//n
        lab_23_0:
        push_symbol(base+1);//d
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_23_2;
            line(270);
            line(266);
            push_symbol(base+1);//d
            push_symbol(base+2);//n
            idxr();
            push(&ONE);
            _clp_left(2);
            string(L"/\\");
            ss();
            if(!flag()) goto if_24_1;
                line(267);
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
            line(268);
                line(269);
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
        line(286);
        line(274);
        push_symbol(_st_s_incdir_ptr());//global
        push(&NIL);
        neeq();
        if(!flag()) goto if_25_1;
            line(276);
            push_symbol(_st_s_incdir_ptr());//global
            string(L",;");
            _clp_xsplit(2);
            assign(base+1);//d
            pop();
            line(278);
            string(L"");
            assign(_st_s_incdir_ptr());//global
            pop();
            line(285);
            {
            line(279);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+2);//n
            lab_26_0:
            push_symbol(base+1);//d
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_26_2;
                line(284);
                line(280);
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                push(&ONE);
                _clp_left(2);
                string(L"/\\");
                ss();
                if(!flag()) goto if_27_1;
                    line(281);
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
                line(282);
                    line(283);
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
    line(289);
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
    line(295);
    line(308);
    string(L"");
    assign(base+0);//txt
    pop();
    line(309);
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
    line(310);
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
    line(311);
    push_symbol(base+0);//txt
    string(L"BUILD_INC");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(312);
    push_symbol(base+0);//txt
    string(L"include");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(313);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(314);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(316);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(318);
    string(L"BUILD_INC=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(324);
    string(L"");
    assign(base+0);//txt
    pop();
    line(325);
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
    line(326);
    push_symbol(base+0);//txt
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(327);
    push_symbol(base+0);//txt
    string(L"lib");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(328);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(329);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(331);
    push_symbol(base+0);//txt
    string(L":");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(333);
    string(L"BUILD_LPT=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(339);
    string(L"");
    assign(base+0);//txt
    pop();
    line(340);
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
    line(341);
    push_symbol(base+0);//txt
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L";");
    add();
    add();
    assign(base+0);//txt
    pop();
    line(342);
    push_symbol(base+0);//txt
    string(L",");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(343);
    push_symbol(base+0);//txt
    string(L";");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//txt
    pop();
    line(344);
    string(L"BUILD_LIB=");
    push_symbol(base+0);//txt
    add();
    _clp_putenv(1);
    pop();
    line(347);
    line(345);
    push_symbol(_st_s_libabs_ptr());//global
    if(!flag()) goto if_28_1;
        line(346);
        string(L"BUILD_LIB=");
        _clp_search_library(0);
        add();
        _clp_putenv(1);
        pop();
    if_28_1:
    if_28_0:;
    line(350);
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
    line(356);
    array(0);
    assign(base+0);//dir
    pop();
    line(357);
    array(0);
    assign(base+1);//obj
    pop();
    line(358);
    array(0);
    assign(base+2);//lib
    pop();
    line(359);
    array(0);
    assign(base+3);//mmd
    pop();
    line(360);
    array(0);
    assign(base+4);//todo
    pop();
    line(362);
    line(367);
    line(365);
    push_symbol(_st_s_main_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_29_1;
        line(366);
        push_symbol(_st_s_main_ptr());//global
        _clp_lower(1);
        string(L",;");
        _clp_xsplit(2);
        assign(base+3);//mmd
        pop();
    if_29_1:
    if_29_0:;
    line(374);
    line(370);
    push_symbol(_st_s_srcdir_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_30_1;
        line(371);
        push_symbol(_st_s_srcdir_ptr());//global
        string(L",;");
        _clp_xsplit(2);
        assign(base+0);//dir
        pop();
    goto if_30_0;
    if_30_1:
    line(372);
        line(373);
        string(L".");
        array(1);
        assign(base+0);//dir
        pop();
    if_30_2:
    if_30_0:;
    line(390);
    {
    line(376);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_31_0:
    push_symbol(base+0);//dir
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_31_2;
        line(378);
        string(L"");
        push_symbol(base+0);//dir
        push_symbol(base+8);//n
        idxr();
        _clp_qqout(2);
        pop();
        line(380);
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
        line(389);
        {
        line(382);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//i
        lab_32_0:
        push_symbol(base+5);//d1
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_32_2;
            line(384);
            push_symbol(base+5);//d1
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            _clp_lower(1);
            assign(base+6);//f
            pop();
            line(388);
            line(386);
            push_symbol(base+6);//f
            _clp_fext(1);
            string(L".");
            add();
            push_symbol(_st_s_primary_ptr());//global
            ss();
            if(!flag()) goto if_33_1;
                line(387);
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
    line(391);
    _clp_qout(0);
    pop();
    line(427);
    {
    line(396);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_34_0:
    push_symbol(base+1);//obj
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_34_2;
        line(398);
        push_symbol(base+1);//obj
        push_symbol(base+8);//n
        idxr();
        assign(base+6);//f
        pop();
        line(399);
        push_symbol(base+6);//f
        _clp_fname(1);
        assign(base+7);//o
        pop();
        line(400);
        push_symbol(base+6);//f
        _clp_memoread(1);
        assign(base+10);//txt
        pop();
        line(410);
        line(402);
        push(&ZERO);
        push_symbol(base+3);//mmd
        push_symbol_ref(base+7);//o
        block(_blk_build_0,1);
        _clp_ascan(2);
        neeq();
        if(!flag()) goto if_35_1;
        goto if_35_0;
        if_35_1:
        line(404);
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
        if(!flag()) goto if_35_2;
            line(407);
            line(405);
            push_symbol(_st_s_main_ptr());//global
            push(&NIL);
            eqeq();
            if(!flag()) goto if_36_1;
                line(406);
                push_symbol(base+3);//mmd
                push_symbol(base+7);//o
                _clp_aadd(2);
                pop();
            if_36_1:
            if_36_0:;
        goto if_35_0;
        if_35_2:
        line(408);
            line(409);
            push_symbol(base+2);//lib
            push_symbol(base+7);//o
            _clp_aadd(2);
            pop();
        if_35_3:
        if_35_0:;
        line(412);
        push_symbol(base+7);//o
        string(L".obj");
        add();
        push_symbol(base+6);//f
        array(2);
        assign(base+11);//dep
        pop();
        line(424);
        {
        line(413);
        push(&ONE);
        int sg=sign();
        number(2);
        assign(base+9);//i
        lab_37_0:
        push_symbol(base+11);//dep
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_37_2;
            line(422);
            line(414);
            push_symbol(base+9);//i
            number(2);
            eqeq();
            if(!flag()) goto if_38_1;
            goto if_38_0;
            if_38_1:
            line(416);
            push_symbol(base+9);//i
            number(128);
            gt();
            if(!flag()) goto if_38_2;
                line(417);
                string(L"recursive dependencies:");
                push_symbol(base+11);//dep
                _clp_qout(2);
                pop();
                line(418);
                _clp_qout(0);
                pop();
                line(419);
                _clp___quit(0);
                pop();
            goto if_38_0;
            if_38_2:
            line(420);
                line(421);
                push_symbol(base+11);//dep
                push_symbol(base+9);//i
                idxr();
                _clp_memoread(1);
                assign(base+10);//txt
                pop();
            if_38_3:
            if_38_0:;
            line(423);
            push_symbol(base+10);//txt
            push_symbol(base+11);//dep
            push_symbol(base+0);//dir
            push_symbol(base+4);//todo
            _clp_search_include(4);
            pop();
        lab_37_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//i
        add();
        assign(base+9);//i
        goto lab_37_0;
        lab_37_2:;
        }
        line(426);
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
    line(429);
    push_symbol(base+4);//todo
    push(&NIL);
    push(&NIL);
    block(_blk_build_1,0);
    _clp_asort(4);
    pop();
    line(441);
    line(433);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_39_1;
        line(434);
        string(L"main:");
        push_symbol(base+3);//mmd
        _clp_qout(2);
        pop();
        line(435);
        string(L"lib :");
        push_symbol(base+2);//lib
        _clp_qout(2);
        pop();
        line(436);
        _clp_qout(0);
        pop();
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
            _clp_qout(1);
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
        line(440);
        _clp_qout(0);
        pop();
    if_39_1:
    if_39_0:;
    line(445);
    {
    line(443);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+8);//n
    lab_41_0:
    push_symbol(base+4);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_41_2;
        line(444);
        push_symbol(base+4);//todo
        push_symbol(base+8);//n
        idxr();
        _clp_makeobj(1);
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
    line(464);
    line(449);
    push_symbol(_st_s_libnam_ptr());//global
    push(&NIL);
    neeq();
    if(!flag()) goto if_42_1;
        line(450);
        push_symbol(_st_s_libnam_ptr());//global
        push_symbol(base+2);//lib
        _clp_makelib(2);
        pop();
        line(454);
        line(452);
        push_symbol(_st_s_shared_ptr());//global
        push(&TRUE);
        eqeq();
        if(!flag()) goto if_43_1;
            line(453);
            push_symbol(_st_s_libnam_ptr());//global
            push_symbol(base+2);//lib
            _clp_makeso(2);
            pop();
        if_43_1:
        if_43_0:;
        line(458);
        {
        line(456);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_44_0:
        push_symbol(base+3);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_44_2;
            line(457);
            push_symbol(base+3);//mmd
            push_symbol(base+8);//n
            idxr();
            push_symbol(_st_s_libnam_ptr());//global
            _clp_makeexe1(2);
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
    goto if_42_0;
    if_42_1:
    line(460);
        line(463);
        {
        line(461);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+8);//n
        lab_45_0:
        push_symbol(base+3);//mmd
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_45_2;
            line(462);
            push_symbol(base+3);//mmd
            push_symbol(base+8);//n
            idxr();
            push_symbol(base+2);//lib
            _clp_makeexe(2);
            pop();
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
    if_42_2:
    if_42_0:;
    line(466);
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
    line(473);
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
    line(474);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(475);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2so.bat");
    add();
    assign(base+7);//torun
    pop();
    line(476);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(483);
    line(478);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_46_1;
        line(479);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(480);
        _clp_qout(0);
        pop();
        line(481);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(482);
        _clp___quit(0);
        pop();
    if_46_1:
    if_46_0:;
    line(485);
    push_symbol(base+7);//torun
    string(L" lib");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(487);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(490);
    line(488);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_47_1;
        line(489);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_47_1:
    if_47_0:;
    line(494);
    line(492);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_48_1;
        line(493);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_48_1:
    if_48_0:;
    line(517);
    {
    line(496);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_49_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_49_2;
        line(498);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(499);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+4);//depend
        add();
        add();
        assign(base+7);//torun
        pop();
        line(500);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(501);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(512);
        line(503);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_50_1;
            line(504);
            push_symbol(base+4);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(505);
            _clp_qout(0);
            pop();
            line(506);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(507);
            _clp___quit(0);
            pop();
        goto if_50_0;
        if_50_1:
        line(509);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_50_2;
            line(511);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_50_2:
        if_50_0:;
        line(516);
        line(514);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_51_1;
            line(515);
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
        if_51_1:
        if_51_0:;
    lab_49_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_49_0;
    lab_49_2:;
    }
    line(521);
    line(519);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_52_1;
        line(520);
        _clp_qout(0);
        pop();
    if_52_1:
    if_52_0:;
    line(525);
    line(523);
    push_symbol(base+6);//update
    if(!flag()) goto if_53_1;
        line(524);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_53_1:
    if_53_0:;
    line(527);
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
    line(533);
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
    line(534);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(535);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2lib.bat");
    add();
    assign(base+7);//torun
    pop();
    line(536);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+8);//objdir
    pop();
    line(537);
    line(544);
    line(539);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_54_1;
        line(540);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(541);
        _clp_qout(0);
        pop();
        line(542);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(543);
        _clp___quit(0);
        pop();
    if_54_1:
    if_54_0:;
    line(546);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(548);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(551);
    line(549);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_55_1;
        line(550);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_55_1:
    if_55_0:;
    line(555);
    line(553);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_56_1;
        line(554);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_56_1:
    if_56_0:;
    line(577);
    {
    line(557);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_57_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_57_2;
        line(559);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(560);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(561);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(572);
        line(563);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_58_1;
            line(564);
            push_symbol(base+4);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(565);
            _clp_qout(0);
            pop();
            line(566);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(567);
            _clp___quit(0);
            pop();
        goto if_58_0;
        if_58_1:
        line(569);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_58_2;
            line(571);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_58_2:
        if_58_0:;
        line(576);
        line(574);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_59_1;
            line(575);
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
        if_59_1:
        if_59_0:;
    lab_57_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_57_0;
    lab_57_2:;
    }
    line(581);
    line(579);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_60_1;
        line(580);
        _clp_qout(0);
        pop();
    if_60_1:
    if_60_0:;
    line(608);
    line(583);
    push_symbol(base+6);//update
    if(!flag()) goto if_61_1;
        line(588);
        {
        line(586);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_62_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_62_2;
            line(587);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
            pop();
        lab_62_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_62_0;
        lab_62_2:;
        }
        line(607);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_61_1:
    if_61_0:;
    line(610);
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
    line(616);
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
    line(617);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(618);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"obj2exe.bat");
    add();
    assign(base+7);//torun
    pop();
    line(619);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+8);//objdir
    pop();
    line(620);
    line(627);
    line(622);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_63_1;
        line(623);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(624);
        _clp_qout(0);
        pop();
        line(625);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(626);
        _clp___quit(0);
        pop();
    if_63_1:
    if_63_0:;
    line(629);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(632);
    line(630);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_64_1;
        line(631);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_64_1:
    if_64_0:;
    line(636);
    line(634);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_65_1;
        line(635);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_65_1:
    if_65_0:;
    line(663);
    {
    line(638);
    push(&ONE);
    int sg=sign();
    push(&ZERO);
    assign(base+9);//n
    lab_66_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_66_2;
        line(644);
        line(640);
        push_symbol(base+9);//n
        push(&ZERO);
        eqeq();
        if(!flag()) goto if_67_1;
            line(641);
            push_symbol(base+0);//exenam
            assign(base+4);//depend
            pop();
        goto if_67_0;
        if_67_1:
        line(642);
            line(643);
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            assign(base+4);//depend
            pop();
        if_67_2:
        if_67_0:;
        line(646);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(647);
        push_symbol(base+4);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(658);
        line(649);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_68_1;
            line(650);
            push_symbol(base+4);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(651);
            _clp_qout(0);
            pop();
            line(652);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(653);
            _clp___quit(0);
            pop();
        goto if_68_0;
        if_68_1:
        line(655);
        push_symbol(base+3);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_68_2;
            line(657);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_68_2:
        if_68_0:;
        line(662);
        line(660);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_69_1;
            line(661);
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
        if_69_1:
        if_69_0:;
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
    line(667);
    line(665);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_70_1;
        line(666);
        _clp_qout(0);
        pop();
    if_70_1:
    if_70_0:;
    line(700);
    line(669);
    push_symbol(base+6);//update
    if(!flag()) goto if_71_1;
        line(670);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+0);//exenam
        add();
        add();
        assign(base+7);//torun
        pop();
        line(675);
        {
        line(673);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_72_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_72_2;
            line(674);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
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
        line(699);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_71_1:
    if_71_0:;
    line(702);
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
    line(708);
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
    line(709);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(710);
    string(L"BUILD_BAT");
    _clp_getenv(1);
    _clp_dirsep(0);
    add();
    string(L"lib2exe.bat");
    add();
    assign(base+7);//torun
    pop();
    line(711);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+8);//objdir
    pop();
    line(718);
    line(713);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_73_1;
        line(714);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(715);
        _clp_qout(0);
        pop();
        line(716);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(717);
        _clp___quit(0);
        pop();
    if_73_1:
    if_73_0:;
    line(720);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(723);
    line(721);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_74_1;
        line(722);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_74_1:
    if_74_0:;
    line(727);
    line(725);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_75_1;
        line(726);
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
    line(730);
    push_symbol(base+0);//mmod
    assign(base+4);//depend
    pop();
    line(731);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(732);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".obj");
    add();
    assign(base+4);//depend
    pop();
    line(733);
    push_symbol(base+4);//depend
    _clp_ftime(1);
    assign(base+5);//tdepend
    pop();
    line(742);
    line(735);
    push_symbol(base+5);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_76_1;
        line(736);
        push_symbol(base+4);//depend
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(737);
        _clp_qout(0);
        pop();
        line(738);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(739);
        _clp___quit(0);
        pop();
    goto if_76_0;
    if_76_1:
    line(740);
    push_symbol(base+3);//ttarget
    push_symbol(base+5);//tdepend
    lt();
    if(!flag()) goto if_76_2;
        line(741);
        push(&TRUE);
        assign(base+6);//update
        pop();
    if_76_2:
    if_76_0:;
    line(745);
    line(743);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_77_1;
        line(744);
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
    if_77_1:
    if_77_0:;
    line(748);
    push_symbol(base+1);//libnam
    assign(base+4);//depend
    pop();
    line(749);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+4);//depend
    add();
    add();
    assign(base+7);//torun
    pop();
    line(750);
    push_symbol(base+8);//objdir
    _clp_dirsep(0);
    add();
    push_symbol(base+4);//depend
    add();
    string(L".lib");
    add();
    assign(base+4);//depend
    pop();
    line(751);
    push_symbol(base+4);//depend
    _clp_ftime(1);
    assign(base+5);//tdepend
    pop();
    line(760);
    line(753);
    push_symbol(base+5);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_78_1;
        line(754);
        push_symbol(base+4);//depend
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(755);
        _clp_qout(0);
        pop();
        line(756);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(757);
        _clp___quit(0);
        pop();
    goto if_78_0;
    if_78_1:
    line(758);
    push_symbol(base+3);//ttarget
    push_symbol(base+5);//tdepend
    lt();
    if(!flag()) goto if_78_2;
        line(759);
        push(&TRUE);
        assign(base+6);//update
        pop();
    if_78_2:
    if_78_0:;
    line(763);
    line(761);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_79_1;
        line(762);
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
    if_79_1:
    if_79_0:;
    line(768);
    line(766);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_80_1;
        line(767);
        _clp_qout(0);
        pop();
    if_80_1:
    if_80_0:;
    line(772);
    line(770);
    push_symbol(base+6);//update
    if(!flag()) goto if_81_1;
        line(771);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
    if_81_1:
    if_81_0:;
    line(774);
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
    line(780);
    push_symbol(base+0);//deplist
    idxr0(1);
    assign(base+1);//target
    pop();
    line(781);
    push_symbol(base+0);//deplist
    idxr0(2);
    assign(base+2);//depend
    pop();
    line(782);
    string(L"BUILD_OBJ");
    _clp_getenv(1);
    assign(base+3);//objdir
    pop();
    line(783);
    line(784);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(785);
    line(789);
    line(787);
    push_symbol(base+1);//target
    _clp_fext(1);
    string(L".obj");
    eqeq();
    if(!flag()) goto if_82_1;
        line(788);
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
    if_82_1:
    if_82_0:;
    line(791);
    push_symbol(base+1);//target
    _clp_ftime(1);
    assign(base+4);//ttarget
    pop();
    line(794);
    line(792);
    push_symbol(base+4);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_83_1;
        line(793);
        string(L"");
        assign(base+4);//ttarget
        pop();
    if_83_1:
    if_83_0:;
    line(798);
    line(796);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_84_1;
        line(797);
        push_symbol(base+1);//target
        string(L"[");
        push_symbol(base+4);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_84_1:
    if_84_0:;
    line(818);
    {
    line(800);
    push(&ONE);
    int sg=sign();
    number(2);
    assign(base+8);//n
    lab_85_0:
    push_symbol(base+0);//deplist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_85_2;
        line(801);
        push_symbol(base+0);//deplist
        push_symbol(base+8);//n
        idxr();
        assign(base+2);//depend
        pop();
        line(802);
        push_symbol(base+2);//depend
        _clp_ftime(1);
        assign(base+5);//tdepend
        pop();
        line(813);
        line(804);
        push_symbol(base+5);//tdepend
        push(&NIL);
        eqeq();
        if(!flag()) goto if_86_1;
            line(805);
            push_symbol(base+0);//deplist
            push_symbol(base+8);//n
            idxr();
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(806);
            _clp_qout(0);
            pop();
            line(807);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(808);
            _clp___quit(0);
            pop();
        goto if_86_0;
        if_86_1:
        line(810);
        push_symbol(base+4);//ttarget
        push_symbol(base+5);//tdepend
        lt();
        if(!flag()) goto if_86_2;
            line(812);
            push(&TRUE);
            assign(base+6);//update
            pop();
        if_86_2:
        if_86_0:;
        line(817);
        line(815);
        push_symbol(_st_s_debug_ptr());//global
        if(!flag()) goto if_87_1;
            line(816);
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
        if_87_1:
        if_87_0:;
    lab_85_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_85_0;
    lab_85_2:;
    }
    line(823);
    line(821);
    push_symbol(_st_s_debug_ptr());//global
    if(!flag()) goto if_88_1;
        line(822);
        _clp_qout(0);
        pop();
    if_88_1:
    if_88_0:;
    line(843);
    line(826);
    push_symbol(base+6);//update
    if(!flag()) goto if_89_1;
        line(828);
        string(L"BUILD_BAT");
        _clp_getenv(1);
        _clp_dirsep(0);
        add();
        assign(base+7);//torun
        pop();
        line(829);
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
        line(830);
        push_symbol(base+7);//torun
        string(L".bat");
        add();
        assign(base+7);//torun
        pop();
        line(837);
        line(832);
        push_symbol(base+7);//torun
        _clp_file(1);
        topnot();
        if(!flag()) goto if_90_1;
            line(833);
            string(L"[");
            push_symbol(base+7);//torun
            add();
            string(L"]");
            add();
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(834);
            _clp_qout(0);
            pop();
            line(835);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(836);
            _clp___quit(0);
            pop();
        if_90_1:
        if_90_0:;
        line(839);
        push_symbol(base+0);//deplist
        idxr0(1);
        _clp_fname(1);
        assign(base+9);//p1
        pop();
        line(840);
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
        line(842);
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
    if_89_1:
    if_89_0:;
    line(845);
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
    line(852);
    push_symbol(base+0);//cmd
    _clp_run(1);
    pop();
    line(862);
    line(854);
    string(L"error");
    _clp_file(1);
    if(!flag()) goto if_91_1;
        line(856);
        string(L"cat error");
        _clp_run(1);
        pop();
        line(860);
        _clp_qout(0);
        pop();
        line(861);
        _clp___quit(0);
        pop();
    if_91_1:
    if_91_0:;
    line(864);
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
    line(869);
    push_symbol(base+0);//fspec
    _clp_directory(1);
    assign(base+1);//d
    pop();
    line(872);
    line(870);
    push_symbol(base+1);//d
    _clp_len(1);
    push(&ONE);
    eqeq();
    if(!flag()) goto if_92_1;
        line(871);
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
    if_92_1:
    if_92_0:;
    line(873);
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
    line(879);
    number(10);
    _clp_chr(1);
    assign(base+4);//nl
    pop();
    line(880);
    string(L"#include");
    assign(base+5);//include
    pop();
    line(881);
    push_symbol(base+5);//include
    _clp_len(1);
    assign(base+6);//lenincl
    pop();
    line(882);
    push(&ZERO);
    assign(base+8);//n2
    pop();
    line(917);
    lab_93_1:
    line(884);
    push_symbol(base+5);//include
    push_symbol(base+0);//txt
    push_symbol(base+8);//n2
    addnum(1);
    _clp_at(3);
    assign(base+7);//n1
    push(&ZERO);
    gt();
    if(!flag()) goto lab_93_2;
        line(888);
        line(886);
        push(&ZERO);
        push_symbol(base+4);//nl
        push_symbol(base+0);//txt
        push_symbol(base+7);//n1
        push_symbol(base+6);//lenincl
        add();
        _clp_at(3);
        assign(base+8);//n2
        eqeq();
        if(!flag()) goto if_94_1;
            line(887);
            push_symbol(base+0);//txt
            _clp_len(1);
            addnum(1);
            assign(base+8);//n2
            pop();
        if_94_1:
        if_94_0:;
        line(890);
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
        line(891);
        push_symbol(base+9);//line
        number(9);
        _clp_chr(1);
        string(L"");
        _clp_strtran(3);
        assign(base+9);//line
        pop();
        line(892);
        push_symbol(base+9);//line
        _clp_alltrim(1);
        assign(base+9);//line
        pop();
        line(900);
        line(894);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"\"");
        eqeq();
        if(!flag()) goto if_95_1;
            line(895);
            string(L"\"");
            assign(base+10);//delim
            pop();
        goto if_95_0;
        if_95_1:
        line(896);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"<");
        eqeq();
        if(!flag()) goto if_95_2;
            line(897);
            string(L">");
            assign(base+10);//delim
            pop();
        goto if_95_0;
        if_95_2:
        line(898);
            line(899);
            goto lab_93_1;//loop
        if_95_3:
        if_95_0:;
        line(904);
        line(902);
        push(&ZERO);
        push_symbol(base+10);//delim
        push_symbol(base+9);//line
        number(2);
        _clp_at(3);
        assign(base+11);//dpos
        eqeq();
        if(!flag()) goto if_96_1;
            line(903);
            goto lab_93_1;//loop
        if_96_1:
        if_96_0:;
        line(906);
        push_symbol(base+9);//line
        number(2);
        push_symbol(base+11);//dpos
        addnum(-2);
        _clp_substr(3);
        assign(base+12);//f
        pop();
        line(916);
        line(908);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byrules(4);
        if(!flag()) goto if_97_1;
        goto if_97_0;
        if_97_1:
        line(911);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byhand(4);
        if(!flag()) goto if_97_2;
        goto if_97_0;
        if_97_2:
        line(914);
        if_97_3:
        if_97_0:;
    goto lab_93_1;
    lab_93_2:;
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
    line(926);
    string(L"BUILD_LPT");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+0);//dirlist
    pop();
    line(927);
    string(L"BUILD_LIB");
    _clp_getenv(1);
    string(L" ");
    _clp_split(2);
    assign(base+1);//liblist
    pop();
    line(928);
    string(L"BUILD_SHR");
    _clp_getenv(1);
    _clp_lower(1);
    assign(base+2);//sharing
    pop();
    line(930);
    string(L"");
    assign(base+5);//txt
    pop();
    line(931);
    line(1007);
    {
    line(934);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_98_0:
    push_symbol(base+1);//liblist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_98_2;
        line(938);
        line(936);
        push_symbol(base+1);//liblist
        push_symbol(base+3);//n
        idxr();
        assign(base+6);//f0
        _clp_empty(1);
        if(!flag()) goto if_99_1;
            line(937);
            goto lab_98_1;//loop
        if_99_1:
        if_99_0:;
        line(950);
        line(940);
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
        if(!flag()) goto if_100_1;
            line(941);
            push_symbol(base+6);//f0
            assign(base+7);//f1
            pop();
            line(942);
            push_symbol(base+6);//f0
            assign(base+8);//f2
            pop();
            line(943);
            push_symbol(base+6);//f0
            assign(base+9);//f3
            pop();
        goto if_100_0;
        if_100_1:
        line(944);
            line(945);
            push_symbol(base+6);//f0
            string(L".lib");
            add();
            assign(base+7);//f1
            pop();
            line(948);
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
            line(949);
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
        if_100_2:
        if_100_0:;
        line(1002);
        {
        line(952);
        push(&ONE);
        int sg=sign();
        push(&ZERO);
        assign(base+4);//i
        lab_101_0:
        push_symbol(base+0);//dirlist
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_101_2;
            line(966);
            line(954);
            push_symbol(base+4);//i
            push(&ZERO);
            lteq();
            if(!flag()) goto if_102_1;
                line(955);
                push_symbol(base+7);//f1
                assign(base+10);//pf1
                pop();
                line(956);
                push_symbol(base+8);//f2
                assign(base+11);//pf2
                pop();
                line(957);
                push_symbol(base+9);//f3
                assign(base+12);//pf3
                pop();
            goto if_102_0;
            if_102_1:
            line(958);
                line(961);
                line(959);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_empty(1);
                if(!flag()) goto if_103_1;
                    line(960);
                    goto lab_101_1;//loop
                if_103_1:
                if_103_0:;
                line(963);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+7);//f1
                add();
                assign(base+10);//pf1
                pop();
                line(964);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+8);//f2
                add();
                assign(base+11);//pf2
                pop();
                line(965);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+9);//f3
                add();
                assign(base+12);//pf3
                pop();
            if_102_2:
            if_102_0:;
            line(1001);
            line(972);
            string(L"static");
            push_symbol(base+2);//sharing
            ss();
            if(!flag()) goto if_104_1;
                line(985);
                line(976);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_105_1;
                    line(977);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(978);
                    goto lab_101_2;//exit
                goto if_105_0;
                if_105_1:
                line(979);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_105_2;
                    line(980);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(981);
                    goto lab_101_2;//exit
                goto if_105_0;
                if_105_2:
                line(982);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_105_3;
                    line(983);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(984);
                    goto lab_101_2;//exit
                if_105_3:
                if_105_0:;
            goto if_104_0;
            if_104_1:
            line(987);
                line(1000);
                line(991);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_106_1;
                    line(992);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(993);
                    goto lab_101_2;//exit
                goto if_106_0;
                if_106_1:
                line(994);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_106_2;
                    line(995);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(996);
                    goto lab_101_2;//exit
                goto if_106_0;
                if_106_2:
                line(997);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_106_3;
                    line(998);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(999);
                    goto lab_101_2;//exit
                if_106_3:
                if_106_0:;
            if_104_2:
            if_104_0:;
        lab_101_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+4);//i
        add();
        assign(base+4);//i
        goto lab_101_0;
        lab_101_2:;
        }
        line(1006);
        line(1004);
        push_symbol(base+4);//i
        push_symbol(base+0);//dirlist
        _clp_len(1);
        gt();
        if(!flag()) goto if_107_1;
            line(1005);
            push_symbol(base+5);//txt
            push_symbol(base+6);//f0
            string(L" ");
            add();
            add();
            assign(base+5);//txt
            pop();
        if_107_1:
        if_107_0:;
    lab_98_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_98_0;
    lab_98_2:;
    }
    line(1009);
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
    line(1014);
    line(1021);
    {
    line(1016);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_108_0:
    push_symbol(base+0);//dirlist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_108_2;
        line(1017);
        push_symbol(base+0);//dirlist
        push_symbol(base+2);//n
        idxr();
        _clp_dirsep(0);
        add();
        push_symbol(base+1);//fnamext
        add();
        assign(base+3);//pathname
        pop();
        line(1020);
        line(1018);
        push_symbol(base+3);//pathname
        _clp_file(1);
        if(!flag()) goto if_109_1;
            line(1019);
            push_symbol(base+3);//pathname
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_109_1:
        if_109_0:;
    lab_108_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_108_0;
    lab_108_2:;
    }
    line(1022);
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
    line(1033);
    push_symbol(base+0);//fil
    _clp_fname(1);
    assign(base+4);//f
    pop();
    line(1034);
    push_symbol(base+0);//fil
    _clp_fext(1);
    assign(base+5);//e
    pop();
    line(1035);
    line(1036);
    line(1037);
    line(1056);
    {
    line(1039);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//i
    lab_110_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_110_2;
        line(1055);
        line(1041);
        push_symbol(_st_s_rules_ptr());//global
        push_symbol(base+9);//i
        idxr();
        idxr0(2);
        push_symbol(base+5);//e
        eqeq();
        if(!flag()) goto if_111_1;
            line(1043);
            push_symbol(_st_s_rules_ptr());//global
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            assign(base+8);//e0
            pop();
            line(1054);
            line(1047);
            push(&NIL);
            push_symbol(base+2);//dir
            push_symbol(base+4);//f
            push_symbol(base+8);//e0
            add();
            _clp_search_file(2);
            assign(base+7);//r
            neeq();
            if(!flag()) goto if_112_1;
                line(1048);
                push_symbol(base+7);//r
                _clp_fpath(1);
                assign(base+6);//p
                pop();
                line(1049);
                push_symbol(base+1);//dep
                push_symbol(base+6);//p
                push_symbol(base+4);//f
                add();
                push_symbol(base+5);//e
                add();
                _clp_adddep(2);
                pop();
                line(1052);
                line(1050);
                push(&ZERO);
                push_symbol(base+3);//todo
                push_symbol_ref(base+6);//p
                push_symbol_ref(base+4);//f
                push_symbol_ref(base+5);//e
                block(_blk_byrules_0,3);
                _clp_ascan(2);
                eqeq();
                if(!flag()) goto if_113_1;
                    line(1051);
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
                if_113_1:
                if_113_0:;
                line(1053);
                push(&TRUE);
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            if_112_1:
            if_112_0:;
        if_111_1:
        if_111_0:;
    lab_110_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//i
    add();
    assign(base+9);//i
    goto lab_110_0;
    lab_110_2:;
    }
    line(1057);
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
    line(1068);
    push_symbol(base+2);//dir
    push_symbol(base+0);//f
    _clp_search_file(2);
    assign(base+4);//pn
    pop();
    line(1073);
    line(1070);
    push_symbol(base+4);//pn
    push(&NIL);
    neeq();
    if(!flag()) goto if_114_1;
        line(1071);
        push_symbol(base+1);//dep
        push_symbol(base+4);//pn
        _clp_adddep(2);
        pop();
        line(1072);
        push(&TRUE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_114_1:
    if_114_0:;
    line(1074);
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
    line(1081);
    line(1079);
    push(&ZERO);
    push_symbol(base+0);//dep
    push_symbol_ref(base+1);//x
    block(_blk_adddep_0,1);
    _clp_ascan(2);
    eqeq();
    if(!flag()) goto if_115_1;
        line(1080);
        push_symbol(base+0);//dep
        push_symbol(base+1);//x
        _clp_aadd(2);
        pop();
    if_115_1:
    if_115_0:;
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
    line(1086);
    push_symbol(base+0);//x
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+0);//x
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+2);//ix
    pop();
    line(1087);
    push_symbol(base+1);//y
    idxr0(2);
    _clp_fext(1);
    push_symbol(base+1);//y
    idxr0(1);
    _clp_fext(1);
    _clp_ruleidx(2);
    assign(base+3);//iy
    pop();
    line(1088);
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
    line(1093);
    line(1098);
    {
    line(1094);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_116_0:
    push_symbol(_st_s_rules_ptr());//global
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_116_2;
        line(1097);
        line(1095);
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
        if(!flag()) goto if_117_1;
            line(1096);
            push_symbol(base+2);//n
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_117_1:
        if_117_0:;
    lab_116_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_116_0;
    lab_116_2:;
    }
    line(1099);
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
    line(1104);
    line(1114);
    {
    line(1105);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_118_0:
    push_symbol(base+1);//sep
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_118_2;
        line(1107);
        push_symbol(base+1);//sep
        push_symbol(base+2);//n
        push(&ONE);
        _clp_substr(3);
        assign(base+3);//s
        pop();
        line(1113);
        line(1109);
        push(&ZERO);
        push_symbol(base+3);//s
        push_symbol(base+0);//txt
        _clp_at(2);
        lt();
        if(!flag()) goto if_119_1;
            line(1110);
            goto lab_118_2;//exit
        goto if_119_0;
        if_119_1:
        line(1111);
            line(1112);
            push(&NIL);
            assign(base+3);//s
            pop();
        if_119_2:
        if_119_0:;
    lab_118_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_118_0;
    lab_118_2:;
    }
    line(1115);
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

