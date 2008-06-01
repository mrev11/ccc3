
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

//input: prg2ppo.ppo (5.0.06)

#include <cccdef.h>

extern void _clp___quit(int argno);
extern void _clp_aadd(int argno);
extern void _clp_aclone(int argno);
extern void _clp_alltrim(int argno);
extern void _clp_argv(int argno);
extern void _clp_chr(int argno);
extern void _clp_define(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_empty(int argno);
extern void _clp_endofline(int argno);
extern void _clp_errorlevel(int argno);
extern void _clp_fbase(int argno);
extern void _clp_ferase(int argno);
extern void _clp_fext(int argno);
extern void _clp_file(int argno);
extern void _clp_fpath(int argno);
extern void _clp_getenv(int argno);
extern void _clp_includepath(int argno);
static void _clp_inidefine(int argno);
static void _clp_iniinclude(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_linepragma(int argno);
static void _clp_logo(int argno);
extern void _clp_lower(int argno);
extern void _clp_main(int argno);
extern void _clp_memoread(int argno);
extern void _clp_memowrit(int argno);
extern void _clp_outstd(int argno);
extern void _clp_processing(int argno);
extern void _clp_qout(int argno);
static void _clp_readpar_a(int argno);
static void _clp_readpar_l(int argno);
extern void _clp_right(int argno);
extern void _clp_rule_df_get(int argno);
extern void _clp_rule_tr_get(int argno);
extern void _clp_searchinclude(int argno);
extern void _clp_set(int argno);
extern void _clp_sourcepath(int argno);
extern void _clp_split(int argno);
extern void _clp_str2bin(int argno);
extern void _clp_strtran(int argno);
extern void _clp_substr(int argno);

static VALUE* _st_s_input_ptr()
{
    static stvar _st_s_input;
    return _st_s_input.ptr;
}
static VALUE* _st_s_output_ptr()
{
    static stvar _st_s_output;
    return _st_s_output.ptr;
}
MUTEX_CREATE(_mutex_s_include);
static VALUE* _st_s_include_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_s_include);
    static stvar _st_s_include(L"");
    MUTEX_UNLOCK(_mutex_s_include);
    SIGNAL_UNLOCK();
    return _st_s_include.ptr;
}
MUTEX_CREATE(_mutex_s_define);
static VALUE* _st_s_define_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_s_define);
    static stvar _st_s_define(L"");
    MUTEX_UNLOCK(_mutex_s_define);
    SIGNAL_UNLOCK();
    return _st_s_define.ptr;
}
MUTEX_CREATE(_mutex_s_files);
static VALUE* _st_s_files_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_s_files);
    static stvar _st_s_files(L"");
    MUTEX_UNLOCK(_mutex_s_files);
    SIGNAL_UNLOCK();
    return _st_s_files.ptr;
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
MUTEX_CREATE(_mutex_s_line);
static VALUE* _st_s_line_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_s_line);
    static stvar _st_s_line(&TRUE);
    MUTEX_UNLOCK(_mutex_s_line);
    SIGNAL_UNLOCK();
    return _st_s_line.ptr;
}
//=======================================================================
void _clp_main(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+5)PUSHNIL();
argno=0;
push_call("main",base);
//
    line(39);
    _clp_argv(0);
    _clp_aclone(1);
    assign(base+0);//opt
    pop();
    line(40);
    line(85);
    {
    line(42);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_1_0:
    push_symbol(base+0);//opt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(44);
        push_symbol(base+0);//opt
        push_symbol(base+2);//n
        idxr();
        number(2);
        _clp_left(2);
        _clp_lower(1);
        assign(base+1);//o
        pop();
        line(84);
        line(46);
        push_symbol(base+1);//o
        push(&ONE);
        _clp_left(2);
        string(L"@");
        eqeq();
        if(!flag()) goto if_2_1;
            line(47);
            push_symbol(base+0);//opt
            push_symbol(base+2);//n
            idxr();
            number(2);
            _clp_substr(2);
            push_symbol(base+0);//opt
            _clp_readpar_a(2);
            pop();
        goto if_2_0;
        if_2_1:
        line(49);
        push_symbol(base+1);//o
        push(&ONE);
        _clp_left(2);
        string(L"!");
        eqeq();
        if(!flag()) goto if_2_2;
            line(50);
            push_symbol(base+0);//opt
            push_symbol(base+2);//n
            idxr();
            number(2);
            _clp_substr(2);
            push_symbol(base+0);//opt
            _clp_readpar_l(2);
            pop();
        goto if_2_0;
        if_2_2:
        line(52);
        push_symbol(base+1);//o
        push(&ONE);
        _clp_left(2);
        string(L"-");
        eqeq();
        topnot();
        if(!flag()) goto if_2_3;
            line(53);
            push_symbol(base+0);//opt
            push_symbol(base+2);//n
            idxr();
            assign(_st_s_input_ptr());//global
            pop();
        goto if_2_0;
        if_2_3:
        line(55);
        push_symbol(base+1);//o
        string(L"-o");
        eqeq();
        if(!flag()) goto if_2_4;
            line(56);
            push_symbol(base+0);//opt
            push_symbol(base+2);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_output_ptr());//global
            pop();
        goto if_2_0;
        if_2_4:
        line(58);
        push_symbol(base+1);//o
        string(L"-i");
        eqeq();
        if(!flag()) goto if_2_5;
            line(59);
            push_symbol(_st_s_include_ptr());//global
            push_symbol(base+0);//opt
            push_symbol(base+2);//n
            idxr();
            number(3);
            _clp_substr(2);
            string(L";");
            add();
            add();
            assign(_st_s_include_ptr());//global
            pop();
        goto if_2_0;
        if_2_5:
        line(61);
        push_symbol(base+1);//o
        string(L"-u");
        eqeq();
        if(!flag()) goto if_2_6;
            line(62);
            push_symbol(_st_s_files_ptr());//global
            push_symbol(base+0);//opt
            push_symbol(base+2);//n
            idxr();
            number(3);
            _clp_substr(2);
            string(L";");
            add();
            add();
            assign(_st_s_files_ptr());//global
            pop();
        goto if_2_0;
        if_2_6:
        line(64);
        push_symbol(base+1);//o
        string(L"-d");
        eqeq();
        if(!flag()) goto if_2_7;
            line(65);
            push_symbol(_st_s_define_ptr());//global
            push_symbol(base+0);//opt
            push_symbol(base+2);//n
            idxr();
            number(3);
            _clp_substr(2);
            string(L";");
            add();
            add();
            assign(_st_s_define_ptr());//global
            pop();
        goto if_2_0;
        if_2_7:
        line(67);
        push_symbol(base+1);//o
        string(L"-l");
        eqeq();
        if(!flag()) goto if_2_8;
            line(68);
            push_symbol(base+0);//opt
            push_symbol(base+2);//n
            idxr();
            number(3);
            _clp_substr(2);
            string(L"+");
            eqeq();
            assign(_st_s_line_ptr());//global
            pop();
        goto if_2_0;
        if_2_8:
        line(70);
        push_symbol(base+1);//o
        string(L"-v");
        eqeq();
        if(!flag()) goto if_2_9;
            line(71);
            push(&TRUE);
            assign(_st_s_version_ptr());//global
            pop();
        goto if_2_0;
        if_2_9:
        line(73);
        push_symbol(base+1);//o
        string(L"-q");
        eqeq();
        if(!flag()) goto if_2_10;
            line(74);
            push(&TRUE);
            assign(_st_s_quiet_ptr());//global
            pop();
        goto if_2_0;
        if_2_10:
        line(76);
        push_symbol(base+1);//o
        string(L"-x");
        eqeq();
        if(!flag()) goto if_2_11;
            line(77);
            push(&TRUE);
            assign(_st_s_version_ptr());//global
            pop();
            line(78);
            push(&TRUE);
            assign(_st_s_quiet_ptr());//global
            pop();
        goto if_2_0;
        if_2_11:
        line(80);
            line(81);
            string(L"Invalid switch: ");
            push_symbol(base+0);//opt
            push_symbol(base+2);//n
            idxr();
            _clp_qout(2);
            pop();
            line(82);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(83);
            _clp___quit(0);
            pop();
        if_2_12:
        if_2_0:;
    lab_1_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_1_0;
    lab_1_2:;
    }
    line(89);
    line(87);
    push_symbol(_st_s_quiet_ptr());//global
    topnot();
    if(!flag()) goto if_3_1;
        line(88);
        _clp_logo(0);
        pop();
    if_3_1:
    if_3_0:;
    line(93);
    line(91);
    push_symbol(_st_s_version_ptr());//global
    if(!flag()) goto if_4_1;
        line(92);
        _clp___quit(0);
        pop();
    if_4_1:
    if_4_0:;
    line(114);
    line(103);
    push_symbol(_st_s_input_ptr());//global
    push(&NIL);
    eqeq();
    if(!flag()) goto if_5_1;
        line(104);
        _clp_qout(0);
        pop();
        line(105);
        string(nls_text(L"Usage: prg2ppo <input>             //input file (.prg)"));
        _clp_qout(1);
        pop();
        line(106);
        string(nls_text(L"               [-o<output>]        //output file (.ppo)"));
        _clp_qout(1);
        pop();
        line(107);
        string(nls_text(L"               [-i<incdir>;]       //include directories"));
        _clp_qout(1);
        pop();
        line(108);
        string(nls_text(L"               [-u<incfil>;]       //use include file"));
        _clp_qout(1);
        pop();
        line(109);
        string(nls_text(L"               [-d<sym>[=<val>];]  //define symbol"));
        _clp_qout(1);
        pop();
        line(110);
        string(nls_text(L"               [@<parfile>]        //parameter file"));
        _clp_qout(1);
        pop();
        line(111);
        _clp_qout(0);
        pop();
        line(112);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(113);
        _clp___quit(0);
        pop();
    if_5_1:
    if_5_0:;
    line(118);
    line(116);
    push_symbol(_st_s_input_ptr());//global
    _clp_fext(1);
    _clp_empty(1);
    if(!flag()) goto if_6_1;
        line(117);
        push_symbol(_st_s_input_ptr());//global
        string(L".prg");
        add();
        assign(_st_s_input_ptr());//global
        pop();
    if_6_1:
    if_6_0:;
    line(124);
    line(120);
    push_symbol(_st_s_input_ptr());//global
    _clp_file(1);
    topnot();
    if(!flag()) goto if_7_1;
        line(121);
        push_symbol(_st_s_input_ptr());//global
        string(nls_text(L"not found"));
        _clp_qout(2);
        pop();
        line(122);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(123);
        _clp___quit(0);
        pop();
    if_7_1:
    if_7_0:;
    line(128);
    line(126);
    push_symbol(_st_s_output_ptr());//global
    _clp_empty(1);
    if(!flag()) goto if_8_1;
        line(127);
        push_symbol(_st_s_input_ptr());//global
        _clp_fpath(1);
        push_symbol(_st_s_input_ptr());//global
        _clp_fbase(1);
        add();
        string(L".ppo");
        add();
        assign(_st_s_output_ptr());//global
        pop();
    if_8_1:
    if_8_0:;
    line(130);
    number(17);
    string(L"off");
    _clp_set(2);
    pop();
    line(132);
    _clp_inidefine(0);
    pop();
    line(133);
    _clp_iniinclude(0);
    assign(base+3);//inctxt
    pop();
    line(140);
    number(22);
    push_symbol(_st_s_output_ptr());//global
    push(&FALSE);
    _clp_set(3);
    pop();
    line(141);
    number(21);
    string(L"on");
    _clp_set(2);
    pop();
    line(150);
    line(143);
    push_symbol(base+3);//inctxt
    push(&NIL);
    neeq();
    if(!flag()) goto if_9_1;
        line(144);
        push_symbol(_st_s_input_ptr());//global
        _clp_fpath(1);
        push_symbol(_st_s_input_ptr());//global
        _clp_fbase(1);
        add();
        string(L".tmp");
        add();
        assign(base+4);//inctmp
        pop();
        line(145);
        push_symbol(base+4);//inctmp
        push_symbol(base+3);//inctxt
        _clp_memowrit(2);
        pop();
        line(146);
        push_symbol(base+4);//inctmp
        _clp_processing(1);
        pop();
        line(147);
        push_symbol(base+4);//inctmp
        _clp_ferase(1);
        pop();
    goto if_9_0;
    if_9_1:
    line(148);
        line(149);
        push_symbol(_st_s_input_ptr());//global
        _clp_processing(1);
        pop();
    if_9_2:
    if_9_0:;
    line(152);
    number(22);
    string(L"");
    _clp_set(2);
    pop();
    line(153);
    number(21);
    string(L"off");
    _clp_set(2);
    pop();
    line(154);
    number(17);
    string(L"on");
    _clp_set(2);
    pop();
    line(156);
    string(nls_text(L"Number of define rules    :"));
    _clp_rule_df_get(0);
    _clp_len(1);
    _clp_qout(2);
    pop();
    line(157);
    string(nls_text(L"Number of translate rules :"));
    _clp_rule_tr_get(0);
    _clp_len(1);
    _clp_qout(2);
    pop();
    line(158);
    _clp_qout(0);
    pop();
    line(163);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_readpar_a(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+5)PUSHNIL();
argno=2;
push_call("readpar_a",base);
//
    line(168);
    push_symbol(base+0);//parfil
    _clp_memoread(1);
    assign(base+2);//par
    pop();
    line(172);
    line(170);
    push_symbol(base+2);//par
    _clp_empty(1);
    if(!flag()) goto if_10_1;
        line(171);
        push(&NIL);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_10_1:
    if_10_0:;
    line(174);
    push_symbol(base+2);//par
    number(13);
    _clp_chr(1);
    string(L"");
    _clp_strtran(3);
    assign(base+2);//par
    pop();
    line(175);
    push_symbol(base+2);//par
    number(10);
    _clp_chr(1);
    string(L" ");
    _clp_strtran(3);
    assign(base+2);//par
    pop();
    line(176);
    push_symbol(base+2);//par
    string(L" ");
    _clp_split(2);
    assign(base+2);//par
    pop();
    line(183);
    {
    line(178);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_11_0:
    push_symbol(base+2);//par
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_11_2;
        line(179);
        push_symbol(base+2);//par
        push_symbol(base+3);//n
        idxr();
        _clp_alltrim(1);
        assign(base+4);//p
        pop();
        line(182);
        line(180);
        push_symbol(base+4);//p
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_12_1;
            line(181);
            push_symbol(base+1);//opt
            push_symbol(base+4);//p
            _clp_aadd(2);
            pop();
        if_12_1:
        if_12_0:;
    lab_11_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_11_0;
    lab_11_2:;
    }
    line(184);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_readpar_l(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+5)PUSHNIL();
argno=2;
push_call("readpar_l",base);
//
    line(189);
    push_symbol(base+0);//parfil
    _clp_memoread(1);
    assign(base+2);//par
    pop();
    line(193);
    line(191);
    push_symbol(base+2);//par
    _clp_empty(1);
    if(!flag()) goto if_13_1;
        line(192);
        push(&NIL);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_13_1:
    if_13_0:;
    line(195);
    push_symbol(base+2);//par
    number(13);
    _clp_chr(1);
    string(L"");
    _clp_strtran(3);
    assign(base+2);//par
    pop();
    line(196);
    push_symbol(base+2);//par
    number(10);
    _clp_chr(1);
    _clp_split(2);
    assign(base+2);//par
    pop();
    line(203);
    {
    line(198);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_14_0:
    push_symbol(base+2);//par
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_14_2;
        line(199);
        push_symbol(base+2);//par
        push_symbol(base+3);//n
        idxr();
        _clp_alltrim(1);
        assign(base+4);//p
        pop();
        line(202);
        line(200);
        push_symbol(base+4);//p
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_15_1;
            line(201);
            push_symbol(base+1);//opt
            push_symbol(base+4);//p
            _clp_aadd(2);
            pop();
        if_15_1:
        if_15_0:;
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
    line(204);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_logo(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+1)PUSHNIL();
argno=0;
push_call("logo",base);
//
    line(209);
    string(nls_text(L"CCC Preprocessor "));
    string(L"1.3.05");
    add();
    string(L" Copyright (C) ComFirm Bt.");
    add();
    assign(base+0);//x
    pop();
    line(210);
    push_symbol(base+0);//x
    _clp_endofline(0);
    add();
    _clp_outstd(1);
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
void _clp_linepragma(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("linepragma",base);
//
    line(217);
    push_symbol(_st_s_line_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_includepath(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("includepath",base);
//
    line(221);
    push_symbol(_st_s_include_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_sourcepath(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("sourcepath",base);
//
    line(225);
    push_symbol(_st_s_input_ptr());//global
    _clp_fpath(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_inidefine(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+2)PUSHNIL();
argno=0;
push_call("inidefine",base);
//
    line(230);
    line(232);
    push_symbol(_st_s_define_ptr());//global
    string(L" ");
    string(L"");
    _clp_strtran(3);
    assign(base+0);//deflist
    pop();
    line(233);
    push_symbol(base+0);//deflist
    string(L";");
    _clp_split(2);
    assign(base+0);//deflist
    pop();
    line(237);
    {
    line(235);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_16_0:
    push_symbol(base+0);//deflist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_16_2;
        line(236);
        push_symbol(base+0);//deflist
        push_symbol(base+1);//n
        idxr();
        string(L"=");
        string(L" ");
        _clp_strtran(3);
        _clp_str2bin(1);
        _clp_define(1);
        pop();
    lab_16_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+1);//n
    add();
    assign(base+1);//n
    goto lab_16_0;
    lab_16_2:;
    }
    line(238);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_iniinclude(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+4)PUSHNIL();
argno=1;
push_call("iniinclude",base);
//
    line(274);
    push_symbol(_st_s_files_ptr());//global
    string(L";");
    _clp_split(2);
    assign(base+1);//includes
    pop();
    line(279);
    {
    line(276);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_17_0:
    push_symbol(base+1);//includes
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_17_2;
        line(277);
        push_symbol(base+1);//includes
        push_symbol(base+2);//n
        idxr();
        _clp_searchinclude(1);
        assign(base+3);//incfil
        pop();
        line(278);
        push_symbol(base+3);//incfil
        _clp_processing(1);
        pop();
    lab_17_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_17_0;
    lab_17_2:;
    }
    line(280);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_searchinclude(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("searchinclude",base);
//
    line(288);
    _clp_includepath(0);
    string(L"INCLUDE");
    _clp_getenv(1);
    add();
    string(L";");
    _clp_split(2);
    assign(base+1);//incdir
    pop();
    line(305);
    line(290);
    push_symbol(base+0);//incfil
    _clp_file(1);
    if(!flag()) goto if_18_1;
        line(291);
        push_symbol(base+0);//incfil
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_18_0;
    if_18_1:
    line(293);
    _clp_sourcepath(0);
    push_symbol(base+0);//incfil
    add();
    _clp_file(1);
    if(!flag()) goto if_18_2;
        line(294);
        _clp_sourcepath(0);
        push_symbol(base+0);//incfil
        add();
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_18_0;
    if_18_2:
    line(296);
        line(304);
        {
        line(297);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+2);//n
        lab_19_0:
        push_symbol(base+1);//incdir
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_19_2;
            line(300);
            line(298);
            push_symbol(base+1);//incdir
            push_symbol(base+2);//n
            idxr();
            push(&ONE);
            _clp_right(2);
            _clp_dirsep(0);
            neeq();
            if(!flag()) goto if_20_1;
                line(299);
                push_symbol(base+1);//incdir
                push_symbol(base+2);//n
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+1);//incdir
                push_symbol(base+2);//n
                assign(idxl());
                pop();
            if_20_1:
            if_20_0:;
            line(303);
            line(301);
            push_symbol(base+1);//incdir
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+0);//incfil
            add();
            _clp_file(1);
            if(!flag()) goto if_21_1;
                line(302);
                push_symbol(base+1);//incdir
                push_symbol(base+2);//n
                idxr();
                push_symbol(base+0);//incfil
                add();
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            if_21_1:
            if_21_0:;
        lab_19_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+2);//n
        add();
        assign(base+2);//n
        goto lab_19_0;
        lab_19_2:;
        }
    if_18_3:
    if_18_0:;
    line(306);
    push_symbol(base+0);//incfil
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

