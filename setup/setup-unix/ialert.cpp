
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

//input: ialert.ppo (5.0.06)

#include <cccdef.h>

static void _blk_interactive_alert_0(int argno);
extern void _clp___keyboard(int argno);
extern void _clp_aadd(int argno);
extern void _clp_aeval(int argno);
extern void _clp_alltrim(int argno);
extern void _clp_asize(int argno);
extern void _clp_at(int argno);
static void _clp_chdraw(int argno);
extern void _clp_chr(int argno);
extern void _clp_devout(int argno);
extern void _clp_devpos(int argno);
extern void _clp_drawbox(int argno);
extern void _clp_empty(int argno);
extern void _clp_inkey(int argno);
extern void _clp_interactive_alert(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_ltrim(int argno);
extern void _clp_max(int argno);
extern void _clp_maxcol(int argno);
extern void _clp_maxrow(int argno);
extern void _clp_min(int argno);
extern void _clp_restscreen(int argno);
extern void _clp_round(int argno);
extern void _clp_setcolor(int argno);
extern void _clp_setcursor(int argno);
extern void _clp_split(int argno);
extern void _clp_substr(int argno);
extern void _clp_upper(int argno);
extern void _clp_valtype(int argno);
static void _clp_wrap1text(int argno);
static void _clp_wraptextarray(int argno);

//=======================================================================
void _clp_interactive_alert(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+23)PUSHNIL();
argno=2;
push_call("interactive_alert",base);
//
    line(80);
    line(81);
    line(83);
    push(&ZERO);
    assign(base+5);//choice
    pop();
    line(84);
    line(86);
    line(87);
    line(88);
    line(89);
    line(90);
    line(92);
    string(L"");
    _clp___keyboard(1);
    pop();
    line(96);
    line(94);
    push_symbol(base+0);//txt
    _clp_empty(1);
    if(flag()){
    push(&TRUE);
    }else{
    push_symbol(base+0);//txt
    _clp_valtype(1);
    string(L"C");
    eqeq();
    topnot();
    }
    if(!flag()) goto if_1_1;
        line(95);
        push(&ZERO);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_1_1:
    if_1_0:;
    line(100);
    line(98);
    push_symbol(base+1);//alts
    _clp_empty(1);
    if(flag()){
    push(&TRUE);
    }else{
    push_symbol(base+1);//alts
    _clp_valtype(1);
    string(L"A");
    neeq();
    }
    if(!flag()) goto if_2_1;
        line(99);
        string(nls_text(L"OK"));
        array(1);
        assign(base+1);//alts
        pop();
    if_2_1:
    if_2_0:;
    line(102);
    string(L"W+/R");
    _clp_setcolor(1);
    assign(base+3);//color
    pop();
    line(103);
    push(&ZERO);
    _clp_setcursor(1);
    assign(base+4);//crs
    pop();
    line(105);
    array(0);
    assign(base+6);//alternatives
    pop();
    line(106);
    string(L"");
    assign(base+7);//shortcuts
    pop();
    line(110);
    {
    line(107);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_3_0:
    push_symbol(base+1);//alts
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_3_2;
        line(108);
        push_symbol(base+6);//alternatives
        string(L" ");
        push_symbol(base+1);//alts
        push_symbol(base+9);//n
        idxr();
        add();
        string(L" ");
        add();
        _clp_aadd(2);
        pop();
        line(109);
        push_symbol(base+7);//shortcuts
        push_symbol(base+1);//alts
        push_symbol(base+9);//n
        idxr();
        push(&ONE);
        _clp_left(2);
        _clp_upper(1);
        add();
        assign(base+7);//shortcuts
        pop();
    lab_3_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_3_0;
    lab_3_2:;
    }
    line(112);
    push_symbol(base+0);//txt
    string(L";");
    _clp_split(2);
    assign(base+8);//atxt
    pop();
    line(115);
    array(0);
    assign(base+13);//ttxt
    pop();
    line(119);
    {
    line(116);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_4_0:
    push_symbol(base+8);//atxt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
        line(117);
        push_symbol(base+8);//atxt
        push_symbol(base+9);//n
        idxr();
        array(1);
        _clp_maxcol(0);
        addnum(-5);
        push(&TRUE);
        push(&TRUE);
        _clp_wraptextarray(4);
        assign(base+15);//wt
        pop();
        line(118);
        push_symbol(base+15);//wt
        push_symbol_ref(base+13);//ttxt
        block(_blk_interactive_alert_0,1);
        _clp_aeval(2);
        pop();
    lab_4_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_4_0;
    lab_4_2:;
    }
    line(122);
    push_symbol(base+6);//alternatives
    _clp_maxcol(0);
    addnum(-5);
    push(&FALSE);
    push(&FALSE);
    _clp_wraptextarray(4);
    assign(base+14);//talt
    pop();
    line(124);
    push(&ZERO);
    assign(base+11);//width
    pop();
    line(125);
    push(&ZERO);
    assign(base+12);//height
    pop();
    line(137);
    {
    line(129);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_5_0:
    push_symbol(base+14);//talt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_5_2;
        line(130);
        push_symbol(base+14);//talt
        push_symbol(base+9);//n
        idxr();
        idxr0(1);
        _clp_len(1);
        push_symbol(base+14);//talt
        push_symbol(base+9);//n
        idxr();
        idxr0(2);
        add();
        assign(base+16);//wx
        pop();
        line(133);
        line(131);
        push_symbol(base+11);//width
        push_symbol(base+16);//wx
        lt();
        if(!flag()) goto if_6_1;
            line(132);
            push_symbol(base+16);//wx
            assign(base+11);//width
            pop();
        if_6_1:
        if_6_0:;
        line(136);
        line(134);
        push_symbol(base+12);//height
        push_symbol(base+14);//talt
        push_symbol(base+9);//n
        idxr();
        idxr0(3);
        addnum(1);
        lt();
        if(!flag()) goto if_7_1;
            line(135);
            push_symbol(base+14);//talt
            push_symbol(base+9);//n
            idxr();
            idxr0(3);
            addnum(1);
            assign(base+12);//height
            pop();
        if_7_1:
        if_7_0:;
    lab_5_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_5_0;
    lab_5_2:;
    }
    line(139);
    push_symbol(base+11);//width
    assign(base+17);//walt
    pop();
    line(140);
    push_symbol(base+12);//height
    assign(base+18);//halt
    pop();
    line(146);
    line(144);
    push_symbol(base+13);//ttxt
    _clp_len(1);
    _clp_maxrow(0);
    push_symbol(base+12);//height
    sub();
    addnum(-1);
    gteq();
    if(!flag()) goto if_8_1;
        line(145);
        push_symbol(base+13);//ttxt
        _clp_maxrow(0);
        push_symbol(base+12);//height
        sub();
        addnum(-1);
        _clp_asize(2);
        pop();
    if_8_1:
    if_8_0:;
    line(154);
    {
    line(150);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_9_0:
    push_symbol(base+13);//ttxt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_9_2;
        line(153);
        line(151);
        push_symbol(base+13);//ttxt
        push_symbol(base+9);//n
        idxr();
        idxr0(1);
        _clp_len(1);
        push_symbol(base+11);//width
        gt();
        if(!flag()) goto if_10_1;
            line(152);
            push_symbol(base+13);//ttxt
            push_symbol(base+9);//n
            idxr();
            idxr0(1);
            _clp_len(1);
            assign(base+11);//width
            pop();
        if_10_1:
        if_10_0:;
    lab_9_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_9_0;
    lab_9_2:;
    }
    line(156);
    push_symbol(base+12);//height
    push_symbol(base+13);//ttxt
    _clp_len(1);
    push_symbol(base+13);//ttxt
    _clp_len(1);
    number(2);
    gteq();
    if(flag()){
    push(&ONE);
    }else{
    push(&ZERO);
    }
    add();
    addnum(3);
    add();
    assign(base+12);//height
    pop();
    line(157);
    push_symbol(base+11);//width
    number(6);
    add();
    assign(base+11);//width
    pop();
    line(160);
    _clp_maxrow(0);
    push_symbol(base+12);//height
    sub();
    number(2);
    div();
    push(&ZERO);
    _clp_round(2);
    assign(base+21);//top
    pop();
    line(161);
    _clp_maxcol(0);
    push_symbol(base+11);//width
    sub();
    number(2);
    div();
    push(&ZERO);
    _clp_round(2);
    assign(base+22);//left
    pop();
    line(163);
    push_symbol(base+21);//top
    push(&ZERO);
    _clp_max(2);
    assign(base+21);//top
    pop();
    line(164);
    push_symbol(base+22);//left
    push(&ZERO);
    _clp_max(2);
    assign(base+22);//left
    pop();
    line(165);
    push_symbol(base+12);//height
    _clp_maxrow(0);
    push_symbol(base+21);//top
    sub();
    addnum(1);
    _clp_min(2);
    assign(base+12);//height
    pop();
    line(166);
    push_symbol(base+11);//width
    _clp_maxcol(0);
    push_symbol(base+22);//left
    sub();
    addnum(1);
    _clp_min(2);
    assign(base+11);//width
    pop();
    line(175);
    {
    line(173);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_11_0:
    push_symbol(base+14);//talt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_11_2;
        line(174);
        push_symbol(base+14);//talt
        push_symbol(base+9);//n
        idxr();
        idxr0(2);
        push_symbol(base+11);//width
        push_symbol(base+17);//walt
        sub();
        addnum(-3);
        number(2);
        div();
        push(&ZERO);
        _clp_round(2);
        add();
        push_symbol(base+14);//talt
        push_symbol(base+9);//n
        idxr();
        assign(idxl0(2));
        pop();
    lab_11_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_11_0;
    lab_11_2:;
    }
    line(177);
    push_symbol(base+21);//top
    push_symbol(base+22);//left
    push_symbol(base+21);//top
    push_symbol(base+12);//height
    add();
    addnum(-1);
    push_symbol(base+22);//left
    push_symbol(base+11);//width
    add();
    addnum(-1);
    number(9484);
    _clp_chr(1);
    number(9472);
    _clp_chr(1);
    add();
    number(9488);
    _clp_chr(1);
    add();
    number(9474);
    _clp_chr(1);
    add();
    number(9496);
    _clp_chr(1);
    add();
    number(9472);
    _clp_chr(1);
    add();
    number(9492);
    _clp_chr(1);
    add();
    number(9474);
    _clp_chr(1);
    add();
    _clp_drawbox(5);
    assign(base+2);//savscr
    pop();
    line(182);
    {
    line(179);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_12_0:
    push_symbol(base+13);//ttxt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_12_2;
        line(181);
        push_symbol(base+21);//top
        push_symbol(base+9);//n
        add();
        push_symbol(base+22);//left
        push_symbol(base+11);//width
        push_symbol(base+13);//ttxt
        push_symbol(base+9);//n
        idxr();
        idxr0(1);
        _clp_len(1);
        sub();
        number(2);
        div();
        add();
        _clp_devpos(2);
        pop();
        push_symbol(base+13);//ttxt
        push_symbol(base+9);//n
        idxr();
        idxr0(1);
        _clp_devout(1);
        pop();
    lab_12_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_12_0;
    lab_12_2:;
    }
    line(184);
    push(&ONE);
    assign(base+5);//choice
    pop();
    line(185);
    push(&TRUE);
    assign(base+19);//mehet
    pop();
    line(217);
    lab_13_1:
    line(186);
    push_symbol(base+19);//mehet
    if(!flag()) goto lab_13_2;
        line(187);
        push_symbol(base+14);//talt
        push_symbol(base+5);//choice
        push_symbol(base+21);//top
        push_symbol(base+12);//height
        add();
        push_symbol(base+18);//halt
        sub();
        addnum(-1);
        push_symbol(base+22);//left
        addnum(1);
        _clp_chdraw(4);
        pop();
        line(188);
        push(&ZERO);
        _clp_inkey(1);
        assign(base+20);//key
        pop();
        line(216);
        line(190);
        push_symbol(base+20);//key
        number(27);
        eqeq();
        if(!flag()) goto if_14_1;
            line(191);
            push(&ZERO);
            assign(base+5);//choice
            pop();
            line(192);
            push(&FALSE);
            assign(base+19);//mehet
            pop();
        goto if_14_0;
        if_14_1:
        line(194);
        push_symbol(base+20);//key
        number(19);
        eqeq();
        if(!flag()) goto if_14_2;
            line(197);
            line(195);
            push_symbol(base+5);//choice
            push(&ONE);
            gt();
            if(!flag()) goto if_15_1;
                line(196);
                push_symbol(base+5);//choice
                dup();
                push(&ONE);
                sub();
                assign(base+5);//choice
                pop();
                pop();
            if_15_1:
            if_15_0:;
        goto if_14_0;
        if_14_2:
        line(199);
        push_symbol(base+20);//key
        number(4);
        eqeq();
        if(!flag()) goto if_14_3;
            line(202);
            line(200);
            push_symbol(base+5);//choice
            push_symbol(base+14);//talt
            _clp_len(1);
            lt();
            if(!flag()) goto if_16_1;
                line(201);
                push_symbol(base+5);//choice
                dup();
                push(&ONE);
                add();
                assign(base+5);//choice
                pop();
                pop();
            if_16_1:
            if_16_0:;
        goto if_14_0;
        if_14_3:
        line(204);
        push_symbol(base+20);//key
        number(13);
        eqeq();
        if(!flag()) goto if_14_4;
            line(205);
            push(&FALSE);
            assign(base+19);//mehet
            pop();
        goto if_14_0;
        if_14_4:
        line(207);
        push_symbol(base+20);//key
        number(32);
        eqeq();
        if(!flag()) goto if_14_5;
            line(208);
            push(&FALSE);
            assign(base+19);//mehet
            pop();
        goto if_14_0;
        if_14_5:
        line(210);
        number(32);
        push_symbol(base+20);//key
        lt();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+20);//key
        number(256);
        lt();
        }
        if(!flag()) goto if_14_6;
            line(215);
            line(211);
            push(&ZERO);
            push_symbol(base+20);//key
            _clp_chr(1);
            _clp_upper(1);
            push_symbol(base+7);//shortcuts
            _clp_at(2);
            assign(base+9);//n
            lt();
            if(!flag()) goto if_17_1;
                line(212);
                push_symbol(base+9);//n
                assign(base+5);//choice
                pop();
                line(213);
                push(&FALSE);
                assign(base+19);//mehet
                pop();
                line(214);
                goto lab_13_2;//exit
            if_17_1:
            if_17_0:;
        if_14_6:
        if_14_0:;
    goto lab_13_1;
    lab_13_2:;
    line(219);
    push_symbol(base+3);//color
    _clp_setcolor(1);
    pop();
    line(221);
    push_symbol(base+4);//crs
    _clp_setcursor(1);
    pop();
    line(222);
    push_symbol(base+21);//top
    push_symbol(base+22);//left
    push_symbol(base+21);//top
    push_symbol(base+12);//height
    add();
    addnum(-1);
    push_symbol(base+22);//left
    push_symbol(base+11);//width
    add();
    addnum(-1);
    push_symbol(base+2);//savscr
    _clp_restscreen(5);
    pop();
    line(224);
    push_symbol(base+5);//choice
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_interactive_alert_0(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_interactive_alert_0",base);
//
    push_blkenv(env+0);//ttxt
    push_blkarg(base+1);//x
    _clp_aadd(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
static void _clp_chdraw(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+7)PUSHNIL();
argno=4;
push_call("chdraw",base);
//
    line(229);
    string(L"W+/R");
    assign(base+4);//stcolor
    pop();
    line(230);
    string(L"W+/B");
    assign(base+5);//hicolor
    pop();
    line(231);
    line(236);
    {
    line(233);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+6);//i
    lab_18_0:
    push_symbol(base+0);//talt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_18_2;
        line(234);
        push_symbol(base+0);//talt
        push_symbol(base+6);//i
        idxr();
        idxr0(3);
        push_symbol(base+2);//row
        add();
        push_symbol(base+0);//talt
        push_symbol(base+6);//i
        idxr();
        idxr0(2);
        push_symbol(base+3);//col
        add();
        _clp_devpos(2);
        pop();
        push_symbol(base+0);//talt
        push_symbol(base+6);//i
        idxr();
        idxr0(1);
        push_symbol(base+6);//i
        push_symbol(base+1);//choice
        eqeq();
        if(flag()){
        push_symbol(base+5);//hicolor
        }else{
        push_symbol(base+4);//stcolor
        }
        _clp_devout(2);
        pop();
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
    line(237);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_wrap1text(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+8)PUSHNIL();
argno=3;
push_call("wrap1text",base);
//
    line(256);
    line(257);
    push(&TRUE);
    assign(base+7);//szohatar
    pop();
    line(261);
    line(259);
    push_symbol(base+2);//dotrim
    push(&TRUE);
    eqeq();
    if(!flag()) goto if_19_1;
        line(260);
        push_symbol(base+0);//str
        _clp_ltrim(1);
        assign(base+0);//str
        pop();
    if_19_1:
    if_19_0:;
    line(285);
    line(262);
    push_symbol(base+0);//str
    _clp_len(1);
    push_symbol(base+1);//width
    lteq();
    if(!flag()) goto if_20_1;
        line(263);
        push_symbol(base+0);//str
        assign(base+5);//str1
        pop();
        line(264);
        string(L"");
        assign(base+6);//str2
        pop();
    goto if_20_0;
    if_20_1:
    line(265);
        line(267);
        push_symbol(base+0);//str
        push(&ONE);
        push_symbol(base+1);//width
        _clp_substr(3);
        assign(base+4);//w
        pop();
        line(268);
        push_symbol(base+4);//w
        _clp_len(1);
        assign(base+3);//i
        pop();
        line(271);
        lab_21_1:
        line(269);
        push_symbol(base+3);//i
        push(&ZERO);
        gt();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+4);//w
        push_symbol(base+3);//i
        push(&ONE);
        _clp_substr(3);
        string(L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
        ss();
        }
        if(!flag()) goto lab_21_2;
            line(270);
            push_symbol(base+3);//i
            dup();
            push(&ONE);
            sub();
            assign(base+3);//i
            pop();
            pop();
        goto lab_21_1;
        lab_21_2:;
        line(284);
        line(275);
        push_symbol(base+3);//i
        push(&ZERO);
        eqeq();
        if(!flag()) goto if_22_1;
            line(277);
            push_symbol(base+4);//w
            assign(base+5);//str1
            pop();
            line(278);
            push_symbol(base+0);//str
            push_symbol(base+5);//str1
            _clp_len(1);
            addnum(1);
            _clp_substr(2);
            assign(base+6);//str2
            pop();
            line(279);
            push(&FALSE);
            assign(base+7);//szohatar
            pop();
        goto if_22_0;
        if_22_1:
        line(280);
            line(282);
            push_symbol(base+0);//str
            push(&ONE);
            push_symbol(base+3);//i
            _clp_substr(3);
            assign(base+5);//str1
            pop();
            line(283);
            push_symbol(base+0);//str
            push_symbol(base+3);//i
            addnum(1);
            _clp_substr(2);
            assign(base+6);//str2
            pop();
        if_22_2:
        if_22_0:;
    if_20_2:
    if_20_0:;
    line(288);
    line(286);
    push_symbol(base+2);//dotrim
    push(&TRUE);
    eqeq();
    if(!flag()) goto if_23_1;
        line(287);
        push_symbol(base+5);//str1
        _clp_alltrim(1);
        assign(base+5);//str1
        pop();
    if_23_1:
    if_23_0:;
    line(289);
    push_symbol(base+5);//str1
    push_symbol(base+6);//str2
    push_symbol(base+7);//szohatar
    array(3);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_wraptextarray(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+10)PUSHNIL();
argno=4;
push_call("wraptextarray",base);
//
    line(303);
    array(0);
    assign(base+4);//t
    pop();
    line(304);
    line(305);
    line(307);
    push(&ZERO);
    assign(base+5);//x
    pop();
    line(308);
    push(&ZERO);
    assign(base+6);//y
    pop();
    line(309);
    push(&ONE);
    assign(base+7);//i
    pop();
    line(353);
    {
    line(310);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+7);//i
    lab_24_0:
    push_symbol(base+0);//strarray
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_24_2;
        line(311);
        push_symbol(base+0);//strarray
        push_symbol(base+7);//i
        idxr();
        assign(base+9);//w
        pop();
        line(314);
        line(312);
        push_symbol(base+3);//trim
        push(&TRUE);
        eqeq();
        if(!flag()) goto if_25_1;
            line(313);
            push_symbol(base+9);//w
            _clp_alltrim(1);
            assign(base+9);//w
            pop();
        if_25_1:
        if_25_0:;
        line(352);
        line(315);
        push_symbol(base+5);//x
        push_symbol(base+9);//w
        _clp_len(1);
        add();
        push_symbol(base+1);//width
        lteq();
        if(!flag()) goto if_26_1;
            line(318);
            line(316);
            push_symbol(base+5);//x
            push(&ZERO);
            neeq();
            if(!flag()) goto if_27_1;
                line(317);
                push_symbol(base+5);//x
                dup();
                push(&ONE);
                add();
                assign(base+5);//x
                pop();
                pop();
            if_27_1:
            if_27_0:;
            line(319);
            push_symbol(base+4);//t
            push_symbol(base+9);//w
            push_symbol(base+5);//x
            push_symbol(base+6);//y
            array(3);
            _clp_aadd(2);
            pop();
            line(320);
            push_symbol(base+5);//x
            push_symbol(base+9);//w
            _clp_len(1);
            add();
            assign(base+5);//x
            pop();
        goto if_26_0;
        if_26_1:
        line(321);
            line(344);
            lab_28_1:
            line(322);
            push_symbol(base+9);//w
            string(L"");
            eqeq();
            topnot();
            if(!flag()){
            push(&FALSE);
            }else{
            push_symbol(base+5);//x
            push_symbol(base+9);//w
            _clp_len(1);
            add();
            push_symbol(base+1);//width
            gt();
            }
            if(!flag()) goto lab_28_2;
                line(323);
                push_symbol(base+9);//w
                push_symbol(base+1);//width
                push_symbol(base+5);//x
                sub();
                push_symbol(base+3);//trim
                _clp_wrap1text(3);
                assign(base+8);//t1
                pop();
                line(343);
                line(324);
                push_symbol(base+2);//wrap
                push(&TRUE);
                eqeq();
                if(!flag()){
                push(&FALSE);
                }else{
                push_symbol(base+8);//t1
                idxr0(3);
                }
                if(!flag()) goto if_29_1;
                    line(328);
                    line(326);
                    push_symbol(base+5);//x
                    push(&ZERO);
                    neeq();
                    if(!flag()) goto if_30_1;
                        line(327);
                        push_symbol(base+5);//x
                        dup();
                        push(&ONE);
                        add();
                        assign(base+5);//x
                        pop();
                        pop();
                    if_30_1:
                    if_30_0:;
                    line(329);
                    push_symbol(base+4);//t
                    push_symbol(base+8);//t1
                    idxr0(1);
                    push_symbol(base+5);//x
                    push_symbol(base+6);//y
                    array(3);
                    _clp_aadd(2);
                    pop();
                    line(330);
                    push_symbol(base+8);//t1
                    idxr0(2);
                    assign(base+9);//w
                    pop();
                    line(331);
                    push_symbol(base+5);//x
                    push_symbol(base+8);//t1
                    idxr0(1);
                    _clp_len(1);
                    add();
                    assign(base+5);//x
                    pop();
                goto if_29_0;
                if_29_1:
                line(332);
                    line(338);
                    line(335);
                    push_symbol(base+5);//x
                    push(&ZERO);
                    neeq();
                    if(!flag()) goto if_31_1;
                        line(336);
                        push_symbol(base+6);//y
                        dup();
                        push(&ONE);
                        add();
                        assign(base+6);//y
                        pop();
                        pop();
                        line(337);
                        push(&ZERO);
                        assign(base+5);//x
                        pop();
                    if_31_1:
                    if_31_0:;
                    line(339);
                    push_symbol(base+9);//w
                    push_symbol(base+1);//width
                    push_symbol(base+5);//x
                    sub();
                    push_symbol(base+3);//trim
                    _clp_wrap1text(3);
                    assign(base+8);//t1
                    pop();
                    line(340);
                    push_symbol(base+4);//t
                    push_symbol(base+8);//t1
                    idxr0(1);
                    push_symbol(base+5);//x
                    push_symbol(base+6);//y
                    array(3);
                    _clp_aadd(2);
                    pop();
                    line(341);
                    push_symbol(base+8);//t1
                    idxr0(2);
                    assign(base+9);//w
                    pop();
                    line(342);
                    push_symbol(base+5);//x
                    push_symbol(base+8);//t1
                    idxr0(1);
                    _clp_len(1);
                    add();
                    assign(base+5);//x
                    pop();
                if_29_2:
                if_29_0:;
            goto lab_28_1;
            lab_28_2:;
            line(351);
            line(345);
            push_symbol(base+9);//w
            string(L"");
            eqeq();
            topnot();
            if(!flag()) goto if_32_1;
                line(348);
                line(346);
                push_symbol(base+5);//x
                push(&ZERO);
                neeq();
                if(!flag()) goto if_33_1;
                    line(347);
                    push_symbol(base+5);//x
                    dup();
                    push(&ONE);
                    add();
                    assign(base+5);//x
                    pop();
                    pop();
                if_33_1:
                if_33_0:;
                line(349);
                push_symbol(base+4);//t
                push_symbol(base+9);//w
                push_symbol(base+5);//x
                push_symbol(base+6);//y
                array(3);
                _clp_aadd(2);
                pop();
                line(350);
                push_symbol(base+5);//x
                push_symbol(base+9);//w
                _clp_len(1);
                add();
                assign(base+5);//x
                pop();
            if_32_1:
            if_32_0:;
        if_26_2:
        if_26_0:;
    lab_24_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+7);//i
    add();
    assign(base+7);//i
    goto lab_24_0;
    lab_24_2:;
    }
    line(354);
    push_symbol(base+4);//t
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

