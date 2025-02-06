//input: ppo/prg2ppo.ppo (5.7.0.1)

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
static VALUE* _st_s_include_ptr()
{
    static stvar _st_s_include(L"");
    return _st_s_include.ptr;
}
static VALUE* _st_s_define_ptr()
{
    static stvar _st_s_define(L"");
    return _st_s_define.ptr;
}
static VALUE* _st_s_files_ptr()
{
    static stvar _st_s_files(L"");
    return _st_s_files.ptr;
}
static VALUE* _st_s_quiet_ptr()
{
    static stvar _st_s_quiet(&FALSE);
    return _st_s_quiet.ptr;
}
static VALUE* _st_s_version_ptr()
{
    static stvar _st_s_version(&FALSE);
    return _st_s_version.ptr;
}
static VALUE* _st_s_line_ptr()
{
    static stvar _st_s_line(&TRUE);
    return _st_s_line.ptr;
}
//=======================================================================
void _clp_main(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+3)PUSHNIL();
argno=0;
push_call("main",base);
//
    line(39);
    _clp_argv(0);
    _clp_aclone(1);
    assign(base+0);//opt
    pop();
    line(84);
    {
    line(41);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_1_0:
    push_symbol(base+0);//opt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(43);
        push_symbol(base+0);//opt
        push_symbol(base+2);//n
        idxr();
        number(2);
        _clp_left(2);
        _clp_lower(1);
        assign(base+1);//o
        pop();
        line(83);
        line(45);
        push_symbol(base+1);//o
        push(&ONE);
        _clp_left(2);
        string(L"@");
        eqeq();
        cmp_212:;
        if(!flag()) goto if_2_1;
            line(46);
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
        line(48);
        push_symbol(base+1);//o
        push(&ONE);
        _clp_left(2);
        string(L"!");
        eqeq();
        cmp_284:;
        if(!flag()) goto if_2_2;
            line(49);
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
        line(51);
        push_symbol(base+1);//o
        push(&ONE);
        _clp_left(2);
        string(L"-");
        eqeq();
        cmp_357:;
        topnot();
        if(!flag()) goto if_2_3;
            line(52);
            push_symbol(base+0);//opt
            push_symbol(base+2);//n
            idxr();
            assign(_st_s_input_ptr());//global
            pop();
        goto if_2_0;
        if_2_3:
        line(54);
        push_symbol(base+1);//o
        string(L"-o");
        eqeq();
        cmp_389:;
        if(!flag()) goto if_2_4;
            line(55);
            push_symbol(base+0);//opt
            push_symbol(base+2);//n
            idxr();
            number(3);
            _clp_substr(2);
            assign(_st_s_output_ptr());//global
            pop();
        goto if_2_0;
        if_2_4:
        line(57);
        push_symbol(base+1);//o
        string(L"-i");
        eqeq();
        cmp_435:;
        if(!flag()) goto if_2_5;
            line(58);
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
        line(60);
        push_symbol(base+1);//o
        string(L"-u");
        eqeq();
        cmp_485:;
        if(!flag()) goto if_2_6;
            line(61);
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
        line(63);
        push_symbol(base+1);//o
        string(L"-d");
        eqeq();
        cmp_535:;
        if(!flag()) goto if_2_7;
            line(64);
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
        line(66);
        push_symbol(base+1);//o
        string(L"-l");
        eqeq();
        cmp_585:;
        if(!flag()) goto if_2_8;
            line(67);
            push_symbol(base+0);//opt
            push_symbol(base+2);//n
            idxr();
            number(3);
            _clp_substr(2);
            string(L"+");
            eqeq();
            cmp_620:;
            assign(_st_s_line_ptr());//global
            pop();
        goto if_2_0;
        if_2_8:
        line(69);
        push_symbol(base+1);//o
        string(L"-v");
        eqeq();
        cmp_635:;
        if(!flag()) goto if_2_9;
            line(70);
            push(&TRUE);
            assign(_st_s_version_ptr());//global
            pop();
        goto if_2_0;
        if_2_9:
        line(72);
        push_symbol(base+1);//o
        string(L"-q");
        eqeq();
        cmp_661:;
        if(!flag()) goto if_2_10;
            line(73);
            push(&TRUE);
            assign(_st_s_quiet_ptr());//global
            pop();
        goto if_2_0;
        if_2_10:
        line(75);
        push_symbol(base+1);//o
        string(L"-x");
        eqeq();
        cmp_687:;
        if(!flag()) goto if_2_11;
            line(76);
            push(&TRUE);
            assign(_st_s_version_ptr());//global
            pop();
            line(77);
            push(&TRUE);
            assign(_st_s_quiet_ptr());//global
            pop();
        goto if_2_0;
        if_2_11:
        line(79);
            line(80);
            string(L"Invalid switch: ");
            push_symbol(base+0);//opt
            push_symbol(base+2);//n
            idxr();
            _clp_qout(2);
            pop();
            line(81);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(82);
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
    line(88);
    line(86);
    push_symbol(_st_s_quiet_ptr());//global
    topnot();
    if(!flag()) goto if_3_1;
        line(87);
        _clp_logo(0);
        pop();
    if_3_1:
    if_3_0:;
    line(92);
    line(90);
    push_symbol(_st_s_version_ptr());//global
    if(!flag()) goto if_4_1;
        line(91);
        _clp___quit(0);
        pop();
    if_4_1:
    if_4_0:;
    line(113);
    line(102);
    push_symbol(_st_s_input_ptr());//global
    push(&NIL);
    eqeq();
    cmp_840:;
    if(!flag()) goto if_5_1;
        line(103);
        _clp_qout(0);
        pop();
        line(104);
        string(nls_text(L"Usage: prg2ppo <input>             //input file (.prg)"));
        _clp_qout(1);
        pop();
        line(105);
        string(nls_text(L"               [-o<output>]        //output file (.ppo)"));
        _clp_qout(1);
        pop();
        line(106);
        string(nls_text(L"               [-i<incdir>;]       //include directories"));
        _clp_qout(1);
        pop();
        line(107);
        string(nls_text(L"               [-u<incfil>;]       //use include file"));
        _clp_qout(1);
        pop();
        line(108);
        string(nls_text(L"               [-d<sym>[=<val>];]  //define symbol"));
        _clp_qout(1);
        pop();
        line(109);
        string(nls_text(L"               [@<parfile>]        //parameter file"));
        _clp_qout(1);
        pop();
        line(110);
        _clp_qout(0);
        pop();
        line(111);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(112);
        _clp___quit(0);
        pop();
    if_5_1:
    if_5_0:;
    line(117);
    line(115);
    push_symbol(_st_s_input_ptr());//global
    _clp_fext(1);
    _clp_empty(1);
    if(!flag()) goto if_6_1;
        line(116);
        push_symbol(_st_s_input_ptr());//global
        string(L".prg");
        add();
        assign(_st_s_input_ptr());//global
        pop();
    if_6_1:
    if_6_0:;
    line(123);
    line(119);
    push_symbol(_st_s_input_ptr());//global
    _clp_file(1);
    topnot();
    if(!flag()) goto if_7_1;
        line(120);
        push_symbol(_st_s_input_ptr());//global
        string(nls_text(L"not found"));
        _clp_qout(2);
        pop();
        line(121);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(122);
        _clp___quit(0);
        pop();
    if_7_1:
    if_7_0:;
    line(127);
    line(125);
    push_symbol(_st_s_output_ptr());//global
    _clp_empty(1);
    if(!flag()) goto if_8_1;
        line(126);
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
    line(129);
    number(17);
    string(L"off");
    _clp_set(2);
    pop();
    line(131);
    _clp_inidefine(0);
    pop();
    line(132);
    _clp_iniinclude(0);
    pop();
    line(142);
    number(22);
    push_symbol(_st_s_output_ptr());//global
    push(&FALSE);
    _clp_set(3);
    pop();
    line(144);
    number(21);
    string(L"on");
    _clp_set(2);
    pop();
    line(146);
    push_symbol(_st_s_input_ptr());//global
    _clp_processing(1);
    pop();
    line(148);
    number(22);
    string(L"");
    _clp_set(2);
    pop();
    line(149);
    number(21);
    string(L"off");
    _clp_set(2);
    pop();
    line(150);
    number(17);
    string(L"on");
    _clp_set(2);
    pop();
    line(152);
    string(nls_text(L"Number of define rules    :"));
    _clp_rule_df_get(0);
    _clp_len(1);
    _clp_qout(2);
    pop();
    line(153);
    string(nls_text(L"Number of translate rules :"));
    _clp_rule_tr_get(0);
    _clp_len(1);
    _clp_qout(2);
    pop();
    line(154);
    _clp_qout(0);
    pop();
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
    line(165);
    push_symbol(base+0);//parfil
    _clp_memoread(1);
    assign(base+2);//par
    pop();
    line(169);
    line(167);
    push_symbol(base+2);//par
    _clp_empty(1);
    if(!flag()) goto if_9_1;
        line(168);
        push(&NIL);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_9_1:
    if_9_0:;
    line(171);
    push_symbol(base+2);//par
    number(13);
    _clp_chr(1);
    string(L"");
    _clp_strtran(3);
    assign(base+2);//par
    pop();
    line(172);
    push_symbol(base+2);//par
    number(10);
    _clp_chr(1);
    string(L" ");
    _clp_strtran(3);
    assign(base+2);//par
    pop();
    line(173);
    push_symbol(base+2);//par
    string(L" ");
    _clp_split(2);
    assign(base+2);//par
    pop();
    line(180);
    {
    line(175);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_10_0:
    push_symbol(base+2);//par
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_10_2;
        line(176);
        push_symbol(base+2);//par
        push_symbol(base+3);//n
        idxr();
        _clp_alltrim(1);
        assign(base+4);//p
        pop();
        line(179);
        line(177);
        push_symbol(base+4);//p
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_11_1;
            line(178);
            push_symbol(base+1);//opt
            push_symbol(base+4);//p
            _clp_aadd(2);
            pop();
        if_11_1:
        if_11_0:;
    lab_10_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_10_0;
    lab_10_2:;
    }
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
    line(184);
    push_symbol(base+0);//parfil
    _clp_memoread(1);
    assign(base+2);//par
    pop();
    line(188);
    line(186);
    push_symbol(base+2);//par
    _clp_empty(1);
    if(!flag()) goto if_12_1;
        line(187);
        push(&NIL);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_12_1:
    if_12_0:;
    line(190);
    push_symbol(base+2);//par
    number(13);
    _clp_chr(1);
    string(L"");
    _clp_strtran(3);
    assign(base+2);//par
    pop();
    line(191);
    push_symbol(base+2);//par
    number(10);
    _clp_chr(1);
    _clp_split(2);
    assign(base+2);//par
    pop();
    line(198);
    {
    line(193);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_13_0:
    push_symbol(base+2);//par
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_13_2;
        line(194);
        push_symbol(base+2);//par
        push_symbol(base+3);//n
        idxr();
        _clp_alltrim(1);
        assign(base+4);//p
        pop();
        line(197);
        line(195);
        push_symbol(base+4);//p
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_14_1;
            line(196);
            push_symbol(base+1);//opt
            push_symbol(base+4);//p
            _clp_aadd(2);
            pop();
        if_14_1:
        if_14_0:;
    lab_13_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_13_0;
    lab_13_2:;
    }
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
    line(202);
    string(nls_text(L"CCC Preprocessor "));
    string(L"1.6.1");
    add();
    string(L" Copyright (C) ComFirm Bt.");
    add();
    assign(base+0);//x
    pop();
    line(203);
    push_symbol(base+0);//x
    _clp_endofline(0);
    add();
    _clp_outstd(1);
    pop();
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
    line(208);
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
    line(212);
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
    line(216);
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
    line(220);
    line(222);
    push_symbol(_st_s_define_ptr());//global
    string(L" ");
    string(L"");
    _clp_strtran(3);
    assign(base+0);//deflist
    pop();
    line(223);
    push_symbol(base+0);//deflist
    string(L";");
    _clp_split(2);
    assign(base+0);//deflist
    pop();
    line(227);
    {
    line(225);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_15_0:
    push_symbol(base+0);//deflist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_15_2;
        line(226);
        push_symbol(base+0);//deflist
        push_symbol(base+1);//n
        idxr();
        string(L"=");
        string(L" ");
        _clp_strtran(3);
        _clp_str2bin(1);
        _clp_define(1);
        pop();
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
    line(239);
    push_symbol(_st_s_files_ptr());//global
    string(L";");
    _clp_split(2);
    assign(base+1);//includes
    pop();
    line(244);
    {
    line(241);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_16_0:
    push_symbol(base+1);//includes
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_16_2;
        line(242);
        push_symbol(base+1);//includes
        push_symbol(base+2);//n
        idxr();
        _clp_searchinclude(1);
        assign(base+3);//incfil
        pop();
        line(243);
        push_symbol(base+3);//incfil
        _clp_processing(1);
        pop();
    lab_16_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_16_0;
    lab_16_2:;
    }
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
    line(249);
    _clp_includepath(0);
    string(L"INCLUDE");
    _clp_getenv(1);
    add();
    string(L";");
    _clp_split(2);
    assign(base+1);//incdir
    pop();
    line(251);
    push_symbol(base+0);//incfil
    string(L"/");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//incfil
    pop();
    line(252);
    push_symbol(base+0);//incfil
    string(L"\\");
    _clp_dirsep(0);
    _clp_strtran(3);
    assign(base+0);//incfil
    pop();
    line(269);
    line(254);
    push_symbol(base+0);//incfil
    _clp_file(1);
    if(!flag()) goto if_17_1;
        line(255);
        push_symbol(base+0);//incfil
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_17_0;
    if_17_1:
    line(257);
    _clp_sourcepath(0);
    push_symbol(base+0);//incfil
    add();
    _clp_file(1);
    if(!flag()) goto if_17_2;
        line(258);
        _clp_sourcepath(0);
        push_symbol(base+0);//incfil
        add();
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_17_0;
    if_17_2:
    line(260);
        line(268);
        {
        line(261);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+2);//n
        lab_18_0:
        push_symbol(base+1);//incdir
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_18_2;
            line(264);
            line(262);
            push_symbol(base+1);//incdir
            push_symbol(base+2);//n
            idxr();
            push(&ONE);
            _clp_right(2);
            _clp_dirsep(0);
            neeq();
            cmp_2596:;
            if(!flag()) goto if_19_1;
                line(263);
                push_symbol(base+1);//incdir
                push_symbol(base+2);//n
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+1);//incdir
                push_symbol(base+2);//n
                assign2(idxxl());
                pop();
            if_19_1:
            if_19_0:;
            line(267);
            line(265);
            push_symbol(base+1);//incdir
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+0);//incfil
            add();
            _clp_file(1);
            if(!flag()) goto if_20_1;
                line(266);
                push_symbol(base+1);//incdir
                push_symbol(base+2);//n
                idxr();
                push_symbol(base+0);//incfil
                add();
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            if_20_1:
            if_20_0:;
        lab_18_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+2);//n
        add();
        assign(base+2);//n
        goto lab_18_0;
        lab_18_2:;
        }
    if_17_3:
    if_17_0:;
    line(270);
    push_symbol(base+0);//incfil
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

