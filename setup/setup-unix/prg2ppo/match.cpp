
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

//input: match.ppo (5.0.11)

#include <cccdef.h>

extern void _clp_aadd(int argno);
extern void _clp_adel(int argno);
extern void _clp_array(int argno);
extern void _clp_asize(int argno);
extern void _clp_cx_df_get(int argno);
extern void _clp_cx_tr_get(int argno);
extern void _clp_error(int argno);
static void _clp_glue(int argno);
extern void _clp_inputnew(int argno);
extern void _clp_int(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_ltrim(int argno);
extern void _clp_markerinfo(int argno);
extern void _clp_markertype(int argno);
extern void _clp_markervalue(int argno);
extern void _clp_match(int argno);
static void _clp_match1(int argno);
extern void _clp_match_extended(int argno);
extern void _clp_match_list(int argno);
extern void _clp_match_regular(int argno);
extern void _clp_match_restricted(int argno);
extern void _clp_match_wild(int argno);
extern void _clp_max(int argno);
static void _clp_nexttoken(int argno);
extern void _clp_outline(int argno);
extern void _clp_outputnew(int argno);
extern void _clp_qout(int argno);
static void _clp_replacelist(int argno);
extern void _clp_result_dumbstr(int argno);
extern void _clp_result_logify(int argno);
extern void _clp_result_regular(int argno);
extern void _clp_result_stringify(int argno);
extern void _clp_right(int argno);
extern void _clp_rtrim(int argno);
extern void _clp_rule_df_get(int argno);
extern void _clp_rule_if_get(int argno);
extern void _clp_rule_search(int argno);
extern void _clp_rule_tr_get(int argno);
extern void _clp_upper(int argno);
extern void _clp_valtype(int argno);
extern void _clp_xtxlegal(int argno);

class _method_add: public _method2_{public: _method_add():_method2_("add"){};}; static _method_add _o_method_add;
class _method_buffer: public _method2_{public: _method_buffer():_method2_("buffer"){};}; static _method_buffer _o_method_buffer;
class _method_bufidx: public _method2_{public: _method_bufidx():_method2_("bufidx"){};}; static _method_bufidx _o_method_bufidx;
class _method_clear: public _method2_{public: _method_clear():_method2_("clear"){};}; static _method_clear _o_method_clear;
class _method_get: public _method2_{public: _method_get():_method2_("get"){};}; static _method_get _o_method_get;
class _method_index: public _method2_{public: _method_index():_method2_("index"){};}; static _method_index _o_method_index;
class _method_len: public _method2_{public: _method_len():_method2_("len"){};}; static _method_len _o_method_len;
class _method_next: public _method2_{public: _method_next():_method2_("next"){};}; static _method_next _o_method_next;
class _method_unget: public _method2_{public: _method_unget():_method2_("unget"){};}; static _method_unget _o_method_unget;

//=======================================================================
void _clp_match(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+14)PUSHNIL();
argno=1;
push_call("match",base);
//
    line(34);
    number(1024);
    push_symbol(base+0);//tlist
    _clp_inputnew(2);
    assign(base+1);//inp
    pop();
    line(35);
    number(256);
    _clp_outputnew(1);
    assign(base+2);//out
    pop();
    line(37);
    _clp_rule_df_get(0);
    assign(base+3);//rdef
    pop();
    line(38);
    _clp_rule_tr_get(0);
    assign(base+4);//rtrn
    pop();
    line(39);
    _clp_cx_df_get(0);
    assign(base+5);//cxdef
    pop();
    line(40);
    _clp_cx_tr_get(0);
    assign(base+6);//cxtrn
    pop();
    line(41);
    push_symbol(base+3);//rdef
    _clp_len(1);
    assign(base+7);//lendef
    pop();
    line(42);
    push_symbol(base+4);//rtrn
    _clp_len(1);
    assign(base+9);//lentrn
    pop();
    line(43);
    push(&TRUE);
    assign(base+13);//reprocess
    pop();
    line(124);
    lab_1_1:
    line(49);
    push_symbol(base+13);//reprocess
    if(!flag()) goto lab_1_2;
        line(51);
        push(&FALSE);
        assign(base+13);//reprocess
        pop();
        line(78);
        lab_2_1:
        line(55);
        push_symbol(base+1);//inp
        _o_method_next.eval(1);
        assign(base+11);//token
        push(&NIL);
        neeq();
        if(!flag()) goto lab_2_2;
            line(57);
            push(&FALSE);
            assign(base+8);//repdef
            pop();
            line(69);
            line(59);
            push(&ZERO);
            push_symbol(base+3);//rdef
            push_symbol(base+11);//token
            push_symbol(base+5);//cxdef
            _clp_rule_search(3);
            assign(base+12);//n
            lt();
            if(!flag()) goto if_3_1;
                line(68);
                lab_4_1:
                line(61);
                push_symbol(base+12);//n
                push_symbol(base+7);//lendef
                lteq();
                if(!flag()){
                push(&FALSE);
                }else{
                push_symbol(base+11);//token
                push_symbol(base+3);//rdef
                push_symbol(base+12);//n
                idxr();
                idxr0(1);
                idxr0(1);
                eqeq();
                }
                if(!flag()) goto lab_4_2;
                    line(66);
                    line(62);
                    push_symbol(base+3);//rdef
                    push_symbol(base+12);//n
                    idxr();
                    push_symbol(base+1);//inp
                    push(&TRUE);
                    _clp_match1(3);
                    if(!flag()) goto if_5_1;
                        line(63);
                        push(&TRUE);
                        assign(base+8);//repdef
                        pop();
                        line(64);
                        push(&TRUE);
                        assign(base+13);//reprocess
                        pop();
                        line(65);
                        goto lab_4_2;//exit
                    if_5_1:
                    if_5_0:;
                    line(67);
                    push_symbol(base+12);//n
                    dup();
                    push(&ONE);
                    add();
                    assign(base+12);//n
                    pop();
                    pop();
                goto lab_4_1;
                lab_4_2:;
            if_3_1:
            if_3_0:;
            line(77);
            line(75);
            push_symbol(base+8);//repdef
            topnot();
            if(!flag()) goto if_6_1;
                line(76);
                push_symbol(base+2);//out
                push_symbol(base+1);//inp
                _o_method_get.eval(1);
                _o_method_add.eval(2);
                pop();
            if_6_1:
            if_6_0:;
        goto lab_2_1;
        lab_2_2:;
        line(82);
        push_symbol(base+1);//inp
        _o_method_clear.eval(1);
        pop();
        line(83);
        push_symbol(base+1);//inp
        push_symbol(base+2);//out
        _o_method_buffer.eval(1);
        push_symbol(base+2);//out
        _o_method_len.eval(1);
        _o_method_unget.eval(3);
        pop();
        line(84);
        push_symbol(base+2);//out
        _o_method_clear.eval(1);
        pop();
        line(88);
        line(86);
        push_symbol(base+13);//reprocess
        if(!flag()) goto if_7_1;
            line(87);
            goto lab_1_1;//loop
        if_7_1:
        if_7_0:;
        line(117);
        lab_8_1:
        line(93);
        push_symbol(base+1);//inp
        _o_method_next.eval(1);
        assign(base+11);//token
        push(&NIL);
        neeq();
        if(!flag()) goto lab_8_2;
            line(95);
            push_symbol(base+11);//token
            _clp_upper(1);
            assign(base+11);//token
            pop();
            line(97);
            push(&FALSE);
            assign(base+10);//reptrn
            pop();
            line(108);
            line(99);
            push(&ZERO);
            push_symbol(base+4);//rtrn
            push_symbol(base+11);//token
            push_symbol(base+6);//cxtrn
            _clp_rule_search(3);
            assign(base+12);//n
            lt();
            if(!flag()) goto if_9_1;
                line(107);
                lab_10_1:
                line(100);
                push_symbol(base+12);//n
                push_symbol(base+9);//lentrn
                lteq();
                if(!flag()){
                push(&FALSE);
                }else{
                push_symbol(base+11);//token
                push_symbol(base+4);//rtrn
                push_symbol(base+12);//n
                idxr();
                idxr0(1);
                idxr0(1);
                eqeq();
                }
                if(!flag()) goto lab_10_2;
                    line(105);
                    line(101);
                    push_symbol(base+4);//rtrn
                    push_symbol(base+12);//n
                    idxr();
                    push_symbol(base+1);//inp
                    push(&FALSE);
                    _clp_match1(3);
                    if(!flag()) goto if_11_1;
                        line(102);
                        push(&TRUE);
                        assign(base+10);//reptrn
                        pop();
                        line(103);
                        push(&TRUE);
                        assign(base+13);//reprocess
                        pop();
                        line(104);
                        goto lab_10_2;//exit
                    if_11_1:
                    if_11_0:;
                    line(106);
                    push_symbol(base+12);//n
                    dup();
                    push(&ONE);
                    add();
                    assign(base+12);//n
                    pop();
                    pop();
                goto lab_10_1;
                lab_10_2:;
            if_9_1:
            if_9_0:;
            line(116);
            line(114);
            push_symbol(base+10);//reptrn
            topnot();
            if(!flag()) goto if_12_1;
                line(115);
                push_symbol(base+2);//out
                push_symbol(base+1);//inp
                _o_method_get.eval(1);
                _o_method_add.eval(2);
                pop();
            if_12_1:
            if_12_0:;
        goto lab_8_1;
        lab_8_2:;
        line(123);
        line(119);
        push_symbol(base+13);//reprocess
        if(!flag()) goto if_13_1;
            line(120);
            push_symbol(base+1);//inp
            _o_method_clear.eval(1);
            pop();
            line(121);
            push_symbol(base+1);//inp
            push_symbol(base+2);//out
            _o_method_buffer.eval(1);
            push_symbol(base+2);//out
            _o_method_len.eval(1);
            _o_method_unget.eval(3);
            pop();
            line(122);
            push_symbol(base+2);//out
            _o_method_clear.eval(1);
            pop();
        if_13_1:
        if_13_0:;
    goto lab_1_1;
    lab_1_2:;
    line(126);
    push_symbol(base+2);//out
    _o_method_buffer.eval(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_match1(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+22)PUSHNIL();
argno=3;
push_call("match1",base);
//
    line(140);
    push(&ZERO);
    assign(base+3);//match_level
    pop();
    line(152);
    number(32);
    _clp_array(1);
    assign(base+4);//match_count
    pop();
    line(153);
    number(32);
    _clp_array(1);
    assign(base+5);//match_state
    pop();
    line(154);
    number(32);
    _clp_array(1);
    assign(base+6);//match_leftb
    pop();
    line(158);
    push(&ZERO);
    assign(base+8);//mcount
    pop();
    line(159);
    push_symbol(base+0);//rule
    idxr0(1);
    assign(base+9);//leftside
    pop();
    line(160);
    push_symbol(base+0);//rule
    idxr0(2);
    assign(base+10);//rightside
    pop();
    line(161);
    push_symbol(base+9);//leftside
    _clp_len(1);
    _clp_array(1);
    assign(base+11);//matchlist
    pop();
    line(162);
    line(163);
    line(164);
    line(165);
    line(167);
    push_symbol(base+3);//match_level
    dup();
    push(&ONE);
    add();
    assign(base+3);//match_level
    pop();
    pop();
    push_symbol(base+8);//mcount
    push_symbol(base+4);//match_count
    push_symbol(base+3);//match_level
    assign(idxl());
    pop();
    push_symbol(base+7);//n
    push_symbol(base+6);//match_leftb
    push_symbol(base+3);//match_level
    assign(idxl());
    pop();
    push(&TRUE);
    push_symbol(base+5);//match_state
    push_symbol(base+3);//match_level
    assign(idxl());
    pop();
    line(278);
    {
    line(169);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+7);//n
    lab_14_0:
    push_symbol(base+9);//leftside
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_14_2;
        line(171);
        push_symbol(base+9);//leftside
        push_symbol(base+7);//n
        idxr();
        assign(base+13);//token_rule
        pop();
        line(172);
        push_symbol(base+1);//inp
        push_symbol(base+8);//mcount
        addnum(1);
        _o_method_next.eval(2);
        assign(base+12);//token_input
        pop();
        line(177);
        lab_15_1:
        line(174);
        push_symbol(base+12);//token_input
        binary(" ");
        eqeq();
        if(!flag()) goto lab_15_2;
            line(175);
            push_symbol(base+8);//mcount
            dup();
            push(&ONE);
            add();
            assign(base+8);//mcount
            pop();
            pop();
            line(176);
            push_symbol(base+1);//inp
            push_symbol(base+8);//mcount
            addnum(1);
            _o_method_next.eval(2);
            assign(base+12);//token_input
            pop();
        goto lab_15_1;
        lab_15_2:;
        line(180);
        push_symbol(base+13);//token_rule
        _clp_valtype(1);
        assign(base+14);//type
        pop();
        line(208);
        line(183);
        push_symbol(base+14);//type
        string(L"L");
        eqeq();
        if(!flag()) goto if_16_1;
            line(206);
            line(185);
            push_symbol(base+13);//token_rule
            if(!flag()) goto if_17_1;
                line(186);
                push_symbol(base+5);//match_state
                push_symbol(base+3);//match_level
                idxr();
                assign(base+18);//x
                pop();
                line(187);
                push_symbol(base+3);//match_level
                dup();
                push(&ONE);
                add();
                assign(base+3);//match_level
                pop();
                pop();
                push_symbol(base+8);//mcount
                push_symbol(base+4);//match_count
                push_symbol(base+3);//match_level
                assign(idxl());
                pop();
                push_symbol(base+7);//n
                push_symbol(base+6);//match_leftb
                push_symbol(base+3);//match_level
                assign(idxl());
                pop();
                push(&TRUE);
                push_symbol(base+5);//match_state
                push_symbol(base+3);//match_level
                assign(idxl());
                pop();
                line(188);
                push_symbol(base+18);//x
                push_symbol(base+5);//match_state
                push_symbol(base+3);//match_level
                assign(idxl());
                pop();
            goto if_17_0;
            if_17_1:
            line(190);
                line(200);
                line(192);
                push_symbol(base+5);//match_state
                push_symbol(base+3);//match_level
                idxr();
                topnot();
                if(!flag()) goto if_18_1;
                    line(199);
                    {
                    line(197);
                    push(&ONE);
                    int sg=sign();
                    push_symbol(base+6);//match_leftb
                    push_symbol(base+3);//match_level
                    idxr();
                    assign(base+17);//i
                    lab_19_0:
                    push_symbol(base+7);//n
                    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_19_2;
                        line(198);
                        push(&NIL);
                        push_symbol(base+11);//matchlist
                        push_symbol(base+17);//i
                        assign(idxl());
                        pop();
                    lab_19_1:
                    push(&ONE);
                    dup();
                    sg=sign();
                    push_symbol(base+17);//i
                    add();
                    assign(base+17);//i
                    goto lab_19_0;
                    lab_19_2:;
                    }
                if_18_1:
                if_18_0:;
                line(205);
                line(202);
                push_symbol(base+3);//match_level
                push(&ONE);
                sub();
                assign(base+3);//match_level
                push(&ONE);
                lt();
                if(!flag()) goto if_20_1;
                    line(203);
                    push_symbol(base+9);//leftside
                    _clp_qout(1);
                    pop();
                    line(204);
                    string(nls_text(L"Unexpected ]"));
                    _clp_error(1);
                    pop();
                if_20_1:
                if_20_0:;
            if_17_2:
            if_17_0:;
            line(207);
            goto lab_14_1;//loop
        if_16_1:
        if_16_0:;
        line(213);
        line(211);
        push_symbol(base+5);//match_state
        push_symbol(base+3);//match_level
        idxr();
        topnot();
        if(!flag()) goto if_21_1;
            line(212);
            goto lab_14_1;//loop
        if_21_1:
        if_21_0:;
        line(273);
        line(216);
        push_symbol(base+14);//type
        string(L"X");
        eqeq();
        if(!flag()) goto if_22_1;
            line(233);
            line(222);
            push_symbol(base+12);//token_input
            push(&NIL);
            eqeq();
            if(!flag()) goto if_23_1;
                line(223);
                push_symbol(base+4);//match_count
                push_symbol(base+3);//match_level
                idxr();
                assign(base+8);//mcount
                pop();
                push(&FALSE);
                push_symbol(base+5);//match_state
                push_symbol(base+3);//match_level
                assign(idxl());
                pop();
            goto if_23_0;
            if_23_1:
            line(225);
            push_symbol(base+2);//casesensitive
            if(!flag()){
            push(&FALSE);
            }else{
            push_symbol(base+12);//token_input
            push_symbol(base+13);//token_rule
            eqeq();
            topnot();
            }
            if(!flag()) goto if_23_2;
                line(226);
                push_symbol(base+4);//match_count
                push_symbol(base+3);//match_level
                idxr();
                assign(base+8);//mcount
                pop();
                push(&FALSE);
                push_symbol(base+5);//match_state
                push_symbol(base+3);//match_level
                assign(idxl());
                pop();
            goto if_23_0;
            if_23_2:
            line(228);
            push_symbol(base+2);//casesensitive
            topnot();
            if(!flag()){
            push(&FALSE);
            }else{
            push_symbol(base+12);//token_input
            _clp_upper(1);
            push_symbol(base+13);//token_rule
            eqeq();
            topnot();
            }
            if(!flag()) goto if_23_3;
                line(229);
                push_symbol(base+4);//match_count
                push_symbol(base+3);//match_level
                idxr();
                assign(base+8);//mcount
                pop();
                push(&FALSE);
                push_symbol(base+5);//match_state
                push_symbol(base+3);//match_level
                assign(idxl());
                pop();
            goto if_23_0;
            if_23_3:
            line(231);
                line(232);
                push_symbol(base+8);//mcount
                dup();
                push(&ONE);
                add();
                assign(base+8);//mcount
                pop();
                pop();
            if_23_4:
            if_23_0:;
        goto if_22_0;
        if_22_1:
        line(236);
        push_symbol(base+14);//type
        string(L"N");
        eqeq();
        if(!flag()) goto if_22_2;
            line(238);
            push_symbol(base+13);//token_rule
            _clp_markertype(1);
            assign(base+14);//type
            pop();
            line(239);
            push_symbol(base+13);//token_rule
            _clp_markerinfo(1);
            assign(base+15);//info
            pop();
            line(241);
            push_symbol(base+9);//leftside
            push_symbol(base+7);//n
            _clp_nexttoken(2);
            assign(base+19);//ntok
            pop();
            line(259);
            line(243);
            push_symbol(base+14);//type
            push(&ONE);
            eqeq();
            if(!flag()) goto if_24_1;
                line(244);
                push_symbol(base+1);//inp
                _o_method_buffer.eval(1);
                push_symbol(base+1);//inp
                push_symbol(base+8);//mcount
                addnum(1);
                _o_method_index.eval(2);
                push_symbol(base+19);//ntok
                _clp_match_regular(3);
                assign(base+16);//k
                pop();
            goto if_24_0;
            if_24_1:
            line(246);
            push_symbol(base+14);//type
            number(2);
            eqeq();
            if(!flag()) goto if_24_2;
                line(247);
                push_symbol(base+1);//inp
                _o_method_buffer.eval(1);
                push_symbol(base+1);//inp
                push_symbol(base+8);//mcount
                addnum(1);
                _o_method_index.eval(2);
                push_symbol(base+19);//ntok
                _clp_match_list(3);
                assign(base+16);//k
                pop();
            goto if_24_0;
            if_24_2:
            line(249);
            push_symbol(base+14);//type
            number(3);
            eqeq();
            if(!flag()) goto if_24_3;
                line(250);
                push_symbol(base+12);//token_input
                push_symbol(base+13);//token_rule
                _clp_match_restricted(2);
                assign(base+16);//k
                pop();
            goto if_24_0;
            if_24_3:
            line(252);
            push_symbol(base+14);//type
            number(4);
            eqeq();
            if(!flag()) goto if_24_4;
                line(253);
                push_symbol(base+1);//inp
                _o_method_buffer.eval(1);
                push_symbol(base+1);//inp
                push_symbol(base+8);//mcount
                addnum(1);
                _o_method_index.eval(2);
                push_symbol(base+19);//ntok
                _clp_match_extended(3);
                assign(base+16);//k
                pop();
            goto if_24_0;
            if_24_4:
            line(255);
            push_symbol(base+14);//type
            number(5);
            eqeq();
            if(!flag()) goto if_24_5;
                line(256);
                push_symbol(base+1);//inp
                _o_method_buffer.eval(1);
                push_symbol(base+1);//inp
                push_symbol(base+8);//mcount
                addnum(1);
                _o_method_index.eval(2);
                _clp_match_wild(2);
                assign(base+16);//k
                pop();
            goto if_24_0;
            if_24_5:
            line(257);
                line(258);
                push(&ZERO);
                assign(base+16);//k
                pop();
            if_24_6:
            if_24_0:;
            line(272);
            line(263);
            push_symbol(base+16);//k
            push(&ZERO);
            lteq();
            if(!flag()) goto if_25_1;
                line(264);
                push_symbol(base+4);//match_count
                push_symbol(base+3);//match_level
                idxr();
                assign(base+8);//mcount
                pop();
                push(&FALSE);
                push_symbol(base+5);//match_state
                push_symbol(base+3);//match_level
                assign(idxl());
                pop();
            goto if_25_0;
            if_25_1:
            line(265);
                line(266);
                push_symbol(base+16);//k
                _clp_array(1);
                assign(base+18);//x
                pop();
                line(269);
                {
                line(267);
                push(&ONE);
                int sg=sign();
                push(&ONE);
                assign(base+17);//i
                lab_26_0:
                push_symbol(base+16);//k
                if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_26_2;
                    line(268);
                    push_symbol(base+1);//inp
                    push_symbol(base+8);//mcount
                    push_symbol(base+17);//i
                    add();
                    _o_method_next.eval(2);
                    push_symbol(base+18);//x
                    push_symbol(base+17);//i
                    assign(idxl());
                    pop();
                lab_26_1:
                push(&ONE);
                dup();
                sg=sign();
                push_symbol(base+17);//i
                add();
                assign(base+17);//i
                goto lab_26_0;
                lab_26_2:;
                }
                line(270);
                push_symbol(base+8);//mcount
                push_symbol(base+16);//k
                add();
                assign(base+8);//mcount
                pop();
                line(271);
                push_symbol(base+18);//x
                push_symbol(base+11);//matchlist
                push_symbol(base+7);//n
                assign(idxl());
                pop();
            if_25_2:
            if_25_0:;
        if_22_2:
        if_22_0:;
        line(277);
        line(275);
        push_symbol(base+3);//match_level
        push(&ONE);
        eqeq();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+5);//match_state
        push_symbol(base+3);//match_level
        idxr();
        topnot();
        }
        if(!flag()) goto if_27_1;
            line(276);
            goto lab_14_2;//exit
        if_27_1:
        if_27_0:;
    lab_14_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+7);//n
    add();
    assign(base+7);//n
    goto lab_14_0;
    lab_14_2:;
    }
    line(283);
    line(280);
    push_symbol(base+3);//match_level
    push(&ONE);
    neeq();
    if(!flag()) goto if_28_1;
        line(281);
        push_symbol(base+9);//leftside
        _clp_qout(1);
        pop();
        line(282);
        string(nls_text(L"Unbalanced ["));
        _clp_error(1);
        pop();
    if_28_1:
    if_28_0:;
    line(285);
    push_symbol(base+7);//n
    push_symbol(base+9);//leftside
    _clp_len(1);
    gt();
    assign(base+20);//result
    pop();
    line(296);
    line(287);
    push_symbol(base+20);//result
    if(!flag()) goto if_29_1;
        line(288);
        push_symbol(base+10);//rightside
        push_symbol(base+11);//matchlist
        _clp_replacelist(2);
        assign(base+21);//rlist
        pop();
        line(289);
        push_symbol(base+1);//inp
        _o_method_bufidx.eval(1);
        push_symbol(base+8);//mcount
        add();
        push_symbol(base+1);//inp
        swap();
        _o_method_bufidx.eval(2);
        pop();
        line(290);
        push_symbol(base+1);//inp
        push_symbol(base+21);//rlist
        _o_method_unget.eval(2);
        pop();
    if_29_1:
    if_29_0:;
    line(298);
    push_symbol(base+20);//result
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_replacelist(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+13)PUSHNIL();
argno=2;
push_call("replacelist",base);
//
    line(311);
    array(0);
    assign(base+2);//rlist
    pop();
    line(312);
    line(313);
    push(&FALSE);
    assign(base+9);//optional
    pop();
    line(314);
    push(&FALSE);
    assign(base+12);//glue
    pop();
    line(374);
    {
    line(316);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_30_0:
    push_symbol(base+0);//rightside
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_30_2;
        line(317);
        push_symbol(base+0);//rightside
        push_symbol(base+4);//n
        idxr();
        assign(base+3);//x
        pop();
        line(335);
        line(319);
        push_symbol(base+3);//x
        _clp_valtype(1);
        string(L"L");
        eqeq();
        if(!flag()) goto if_31_1;
            line(333);
            line(320);
            push_symbol(base+3);//x
            if(!flag()) goto if_32_1;
                line(321);
                push(&TRUE);
                assign(base+9);//optional
                pop();
                line(322);
                push(&FALSE);
                assign(base+10);//optstat
                pop();
                line(323);
                push_symbol(base+2);//rlist
                _clp_len(1);
                assign(base+11);//optlen
                pop();
            goto if_32_0;
            if_32_1:
            line(324);
                line(325);
                push(&FALSE);
                assign(base+9);//optional
                pop();
                line(332);
                line(326);
                push_symbol(base+10);//optstat
                topnot();
                if(!flag()) goto if_33_1;
                    line(331);
                    push_symbol(base+2);//rlist
                    push_symbol(base+11);//optlen
                    _clp_asize(2);
                    pop();
                if_33_1:
                if_33_0:;
            if_32_2:
            if_32_0:;
            line(334);
            goto lab_30_1;//loop
        if_31_1:
        if_31_0:;
        line(373);
        line(337);
        push_symbol(base+3);//x
        _clp_valtype(1);
        string(L"X");
        eqeq();
        if(!flag()) goto if_34_1;
            line(338);
            push_symbol(base+2);//rlist
            push_symbol(base+3);//x
            _clp_aadd(2);
            pop();
            line(342);
            line(340);
            push_symbol(base+3);//x
            binary("##");
            eqeq();
            if(!flag()) goto if_35_1;
                line(341);
                push(&TRUE);
                assign(base+12);//glue
                pop();
            if_35_1:
            if_35_0:;
        goto if_34_0;
        if_34_1:
        line(344);
        push_symbol(base+3);//x
        _clp_valtype(1);
        string(L"N");
        eqeq();
        if(!flag()) goto if_34_2;
            line(346);
            push_symbol(base+3);//x
            _clp_markertype(1);
            assign(base+6);//type
            pop();
            line(347);
            push_symbol(base+3);//x
            _clp_markerinfo(1);
            assign(base+7);//info
            pop();
            line(348);
            push_symbol(base+1);//matchlist
            push_symbol(base+7);//info
            idxr();
            assign(base+8);//match
            pop();
            line(352);
            line(350);
            push_symbol(base+8);//match
            push(&NIL);
            neeq();
            if(!flag()) goto if_36_1;
                line(351);
                push(&TRUE);
                assign(base+10);//optstat
                pop();
            if_36_1:
            if_36_0:;
            line(372);
            line(354);
            push_symbol(base+6);//type
            push(&ONE);
            eqeq();
            if(!flag()) goto if_37_1;
                line(355);
                push_symbol(base+2);//rlist
                push_symbol(base+8);//match
                _clp_result_regular(2);
                pop();
            goto if_37_0;
            if_37_1:
            line(357);
            push_symbol(base+6);//type
            number(2);
            eqeq();
            if(!flag()) goto if_37_2;
                line(358);
                push_symbol(base+2);//rlist
                push_symbol(base+8);//match
                _clp_result_dumbstr(2);
                pop();
            goto if_37_0;
            if_37_2:
            line(360);
            push_symbol(base+6);//type
            number(3);
            eqeq();
            if(!flag()) goto if_37_3;
                line(361);
                push_symbol(base+2);//rlist
                push_symbol(base+8);//match
                push(&FALSE);
                binary("\"");
                binary("\"");
                _clp_result_stringify(5);
                pop();
            goto if_37_0;
            if_37_3:
            line(363);
            push_symbol(base+6);//type
            number(4);
            eqeq();
            if(!flag()) goto if_37_4;
                line(364);
                push_symbol(base+2);//rlist
                push_symbol(base+8);//match
                push(&TRUE);
                binary("\"");
                binary("\"");
                _clp_result_stringify(5);
                pop();
            goto if_37_0;
            if_37_4:
            line(366);
            push_symbol(base+6);//type
            number(5);
            eqeq();
            if(!flag()) goto if_37_5;
                line(367);
                push_symbol(base+2);//rlist
                push_symbol(base+8);//match
                push(&FALSE);
                binary("{||");
                binary("}");
                _clp_result_stringify(5);
                pop();
            goto if_37_0;
            if_37_5:
            line(369);
            push_symbol(base+6);//type
            number(6);
            eqeq();
            if(!flag()) goto if_37_6;
                line(370);
                push_symbol(base+2);//rlist
                push_symbol(base+8);//match
                _clp_result_logify(2);
                pop();
            if_37_6:
            if_37_0:;
        if_34_2:
        if_34_0:;
    lab_30_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_30_0;
    lab_30_2:;
    }
    line(378);
    line(376);
    push_symbol(base+12);//glue
    if(!flag()) goto if_38_1;
        line(377);
        push_symbol(base+2);//rlist
        _clp_glue(1);
        pop();
    if_38_1:
    if_38_0:;
    line(380);
    push_symbol(base+2);//rlist
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_glue(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+4)PUSHNIL();
argno=1;
push_call("glue",base);
//
    line(389);
    binary("##");
    assign(base+2);//gl
    pop();
    binary("\"");
    binary("'");
    add();
    assign(base+3);//qq
    pop();
    line(402);
    {
    line(391);
    push(&ONE);
    int sg=sign();
    number(2);
    assign(base+1);//n
    lab_39_0:
    push_symbol(base+0);//rlist
    _clp_len(1);
    addnum(-1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_39_2;
        line(401);
        line(392);
        push_symbol(base+0);//rlist
        push_symbol(base+1);//n
        idxr();
        push_symbol(base+2);//gl
        eqeq();
        if(!flag()) goto if_40_1;
            line(397);
            line(393);
            push_symbol(base+0);//rlist
            push_symbol(base+1);//n
            addnum(-1);
            idxr();
            push(&ONE);
            _clp_right(2);
            push_symbol(base+3);//qq
            ss();
            if(flag()){
            push(&TRUE);
            }else{
            push_symbol(base+0);//rlist
            push_symbol(base+1);//n
            addnum(1);
            idxr();
            push(&ONE);
            _clp_right(2);
            push_symbol(base+3);//qq
            ss();
            }
            if(!flag()) goto if_41_1;
                line(394);
                push_symbol(base+0);//rlist
                push_symbol(base+1);//n
                addnum(-1);
                idxr();
                binary("+");
                push_symbol(base+0);//rlist
                push_symbol(base+1);//n
                addnum(1);
                idxr();
                add();
                add();
                push_symbol(base+0);//rlist
                push_symbol(base+1);//n
                addnum(-1);
                assign(idxl());
                pop();
            goto if_41_0;
            if_41_1:
            line(395);
                line(396);
                push_symbol(base+0);//rlist
                push_symbol(base+1);//n
                addnum(-1);
                idxr();
                push_symbol(base+0);//rlist
                push_symbol(base+1);//n
                addnum(1);
                idxr();
                add();
                push_symbol(base+0);//rlist
                push_symbol(base+1);//n
                addnum(-1);
                assign(idxl());
                pop();
            if_41_2:
            if_41_0:;
            line(398);
            push_symbol(base+0);//rlist
            push_symbol(base+1);//n
            _clp_adel(2);
            pop();
            line(399);
            push_symbol(base+0);//rlist
            push_symbol(base+1);//n
            _clp_adel(2);
            pop();
            line(400);
            push_symbol(base+0);//rlist
            push_symbol(base+0);//rlist
            _clp_len(1);
            addnum(-2);
            _clp_asize(2);
            pop();
        if_40_1:
        if_40_0:;
    lab_39_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+1);//n
    add();
    assign(base+1);//n
    goto lab_39_0;
    lab_39_2:;
    }
    line(404);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_match_regular(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("match_regular",base);
//
    line(408);
    push_symbol(base+0);//toklist
    push_symbol(base+1);//n
    push_symbol(base+2);//nexttok
    _clp_xtxlegal(3);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_match_list(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("match_list",base);
//
    line(414);
    push(&ZERO);
    assign(base+2);//k
    pop();
    push_symbol(base+0);//toklist
    _clp_len(1);
    assign(base+3);//lentok
    pop();
    line(425);
    lab_42_1:
    line(416);
    push_symbol(base+1);//n
    push_symbol(base+2);//k
    add();
    push_symbol(base+3);//lentok
    lteq();
    if(!flag()) goto lab_42_2;
        line(418);
        push_symbol(base+2);//k
        push_symbol(base+0);//toklist
        push_symbol(base+1);//n
        push_symbol(base+2);//k
        add();
        _clp_xtxlegal(2);
        add();
        assign(base+2);//k
        pop();
        line(424);
        line(420);
        push_symbol(base+1);//n
        push_symbol(base+2);//k
        add();
        push_symbol(base+3);//lentok
        gt();
        if(flag()){
        push(&TRUE);
        }else{
        push_symbol(base+0);//toklist
        push_symbol(base+1);//n
        push_symbol(base+2);//k
        add();
        idxr();
        binary(",");
        eqeq();
        topnot();
        }
        if(!flag()) goto if_43_1;
            line(421);
            goto lab_42_2;//exit
        goto if_43_0;
        if_43_1:
        line(422);
            line(423);
            push_symbol(base+2);//k
            dup();
            push(&ONE);
            add();
            assign(base+2);//k
            pop();
            pop();
        if_43_2:
        if_43_0:;
    goto lab_42_1;
    lab_42_2:;
    line(426);
    push_symbol(base+2);//k
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_match_restricted(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("match_restricted",base);
//
    line(432);
    push(&ZERO);
    assign(base+3);//k
    pop();
    line(440);
    line(434);
    push_symbol(base+0);//tokinp
    push(&NIL);
    neeq();
    if(!flag()) goto if_44_1;
        line(436);
        push_symbol(base+1);//tokrul
        _clp_markerinfo(1);
        _clp_rule_if_get(1);
        assign(base+2);//info
        pop();
        line(439);
        line(437);
        binary(",");
        push_symbol(base+0);//tokinp
        _clp_upper(1);
        add();
        binary(",");
        add();
        binary(",");
        push_symbol(base+2);//info
        add();
        binary(",");
        add();
        ss();
        if(!flag()) goto if_45_1;
            line(438);
            push(&ONE);
            assign(base+3);//k
            pop();
        if_45_1:
        if_45_0:;
    if_44_1:
    if_44_0:;
    line(442);
    push_symbol(base+3);//k
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_match_extended(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+4)PUSHNIL();
argno=3;
push_call("match_extended",base);
//
    line(448);
    line(454);
    line(450);
    push_symbol(base+0);//toklist
    _clp_len(1);
    push_symbol(base+1);//n
    lt();
    if(!flag()) goto if_46_1;
        line(451);
        push(&ZERO);
        assign(base+3);//k
        pop();
    goto if_46_0;
    if_46_1:
    line(452);
        line(453);
        push_symbol(base+0);//toklist
        push_symbol(base+1);//n
        push_symbol(base+2);//nexttok
        _clp_xtxlegal(3);
        assign(base+3);//k
        pop();
    if_46_2:
    if_46_0:;
    line(455);
    push_symbol(base+3);//k
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_match_wild(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("match_wild",base);
//
    line(460);
    push_symbol(base+0);//toklist
    _clp_len(1);
    push_symbol(base+1);//n
    sub();
    addnum(1);
    push(&ZERO);
    _clp_max(2);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_result_regular(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("result_regular",base);
//
    line(465);
    line(468);
    {
    line(466);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//i
    lab_47_0:
    push_symbol(base+1);//match
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_47_2;
        line(467);
        push_symbol(base+0);//rlist
        push_symbol(base+1);//match
        push_symbol(base+2);//i
        idxr();
        _clp_aadd(2);
        pop();
    lab_47_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//i
    add();
    assign(base+2);//i
    goto lab_47_0;
    lab_47_2:;
    }
    line(469);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_result_dumbstr(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("result_dumbstr",base);
//
    line(474);
    push_symbol(base+1);//match
    push(&NIL);
    eqeq();
    if(flag()){
    binary("");
    }else{
    push_symbol(base+1);//match
    _clp_outline(1);
    }
    assign(base+2);//x
    pop();
    line(475);
    push_symbol(base+0);//rlist
    binary("\"");
    push_symbol(base+2);//x
    add();
    binary("\"");
    add();
    _clp_aadd(2);
    pop();
    line(476);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_result_stringify(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,5);
while(stack<base+17)PUSHNIL();
argno=5;
push_call("result_stringify",base);
//
    line(485);
    line(486);
    line(487);
    line(488);
    line(490);
    binary("(");
    binary("\"");
    add();
    binary("'");
    add();
    assign(base+16);//smartchar
    pop();
    line(494);
    line(492);
    push_symbol(base+1);//match
    push(&NIL);
    eqeq();
    if(!flag()) goto if_48_1;
        line(493);
        push(&NIL);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_48_1:
    if_48_0:;
    line(496);
    push_symbol(base+0);//rlist
    _clp_len(1);
    assign(base+5);//lr
    pop();
    line(497);
    push_symbol(base+1);//match
    _clp_len(1);
    assign(base+6);//lm
    pop();
    line(498);
    push_symbol(base+5);//lr
    addnum(1);
    assign(base+7);//imin
    pop();
    line(499);
    push_symbol(base+5);//lr
    push_symbol(base+6);//lm
    add();
    assign(base+8);//imax
    pop();
    line(500);
    array(0);
    assign(base+12);//sep
    pop();
    line(501);
    push(&ZERO);
    assign(base+11);//par
    pop();
    line(503);
    push_symbol(base+0);//rlist
    push_symbol(base+8);//imax
    _clp_asize(2);
    pop();
    line(526);
    {
    line(505);
    push(&ONE);
    int sg=sign();
    push_symbol(base+7);//imin
    assign(base+10);//i
    lab_49_0:
    push_symbol(base+8);//imax
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_49_2;
        line(506);
        push_symbol(base+1);//match
        push_symbol(base+10);//i
        push_symbol(base+5);//lr
        sub();
        idxr();
        assign(base+9);//token
        pop();
        line(507);
        push_symbol(base+9);//token
        push_symbol(base+0);//rlist
        push_symbol(base+10);//i
        assign(idxl());
        pop();
        line(513);
        line(509);
        push_symbol(base+9);//token
        binary("([{");
        ss();
        if(!flag()) goto if_50_1;
            line(510);
            push_symbol(base+11);//par
            dup();
            push(&ONE);
            add();
            assign(base+11);//par
            pop();
            pop();
        goto if_50_0;
        if_50_1:
        line(511);
        push_symbol(base+9);//token
        binary(")]}");
        ss();
        if(!flag()) goto if_50_2;
            line(512);
            push_symbol(base+11);//par
            dup();
            push(&ONE);
            sub();
            assign(base+11);//par
            pop();
            pop();
        if_50_2:
        if_50_0:;
        line(517);
        line(515);
        push_symbol(base+9);//token
        binary(",");
        eqeq();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+11);//par
        push(&ZERO);
        eqeq();
        }
        if(!flag()) goto if_51_1;
            line(516);
            push_symbol(base+12);//sep
            push_symbol(base+10);//i
            _clp_aadd(2);
            pop();
        if_51_1:
        if_51_0:;
        line(523);
        line(519);
        binary("\"");
        push_symbol(base+9);//token
        ss();
        if(!flag()){
        push(&FALSE);
        }else{
        binary("\"");
        push_symbol(base+3);//left
        eqeq();
        }
        if(!flag()) goto if_52_1;
            line(520);
            binary("'");
            assign(base+4);//right
            assign(base+3);//left
            pop();
        goto if_52_0;
        if_52_1:
        line(521);
        binary("'");
        push_symbol(base+9);//token
        ss();
        if(!flag()){
        push(&FALSE);
        }else{
        binary("'");
        push_symbol(base+3);//left
        eqeq();
        }
        if(!flag()) goto if_52_2;
            line(522);
            binary("\"");
            assign(base+4);//right
            assign(base+3);//left
            pop();
        if_52_2:
        if_52_0:;
    lab_49_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+10);//i
    add();
    assign(base+10);//i
    goto lab_49_0;
    lab_49_2:;
    }
    line(528);
    push_symbol(base+12);//sep
    _clp_len(1);
    assign(base+15);//ls
    pop();
    line(530);
    push_symbol(base+7);//imin
    assign(base+13);//il
    pop();
    line(531);
    push_symbol(base+15);//ls
    push(&ZERO);
    gt();
    if(flag()){
    push_symbol(base+12);//sep
    idxr0(1);
    addnum(-1);
    }else{
    push_symbol(base+8);//imax
    }
    assign(base+14);//ir
    pop();
    line(536);
    line(533);
    push_symbol(base+13);//il
    push_symbol(base+14);//ir
    lteq();
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+2);//smart
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+0);//rlist
    push_symbol(base+13);//il
    idxr();
    push(&ONE);
    _clp_left(2);
    push_symbol(base+16);//smartchar
    ss();
    }
    topnot();
    }
    if(!flag()) goto if_53_1;
        line(534);
        push_symbol(base+3);//left
        push_symbol(base+0);//rlist
        push_symbol(base+13);//il
        idxr();
        _clp_ltrim(1);
        add();
        push_symbol(base+0);//rlist
        push_symbol(base+13);//il
        assign(idxl());
        pop();
        line(535);
        push_symbol(base+0);//rlist
        push_symbol(base+14);//ir
        idxr();
        _clp_rtrim(1);
        push_symbol(base+4);//right
        add();
        push_symbol(base+0);//rlist
        push_symbol(base+14);//ir
        assign(idxl());
        pop();
    if_53_1:
    if_53_0:;
    line(555);
    line(538);
    push_symbol(base+15);//ls
    push(&ZERO);
    gt();
    if(!flag()) goto if_54_1;
        line(547);
        {
        line(540);
        push(&ONE);
        int sg=sign();
        number(2);
        assign(base+10);//i
        lab_55_0:
        push_symbol(base+15);//ls
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_55_2;
            line(541);
            push_symbol(base+12);//sep
            push_symbol(base+10);//i
            addnum(-1);
            idxr();
            addnum(1);
            assign(base+13);//il
            pop();
            line(542);
            push_symbol(base+12);//sep
            push_symbol(base+10);//i
            idxr();
            addnum(-1);
            assign(base+14);//ir
            pop();
            line(546);
            line(543);
            push_symbol(base+13);//il
            push_symbol(base+14);//ir
            lteq();
            if(!flag()){
            push(&FALSE);
            }else{
            push_symbol(base+2);//smart
            if(!flag()){
            push(&FALSE);
            }else{
            push_symbol(base+0);//rlist
            push_symbol(base+13);//il
            idxr();
            push(&ONE);
            _clp_left(2);
            push_symbol(base+16);//smartchar
            ss();
            }
            topnot();
            }
            if(!flag()) goto if_56_1;
                line(544);
                push_symbol(base+3);//left
                push_symbol(base+0);//rlist
                push_symbol(base+13);//il
                idxr();
                _clp_ltrim(1);
                add();
                push_symbol(base+0);//rlist
                push_symbol(base+13);//il
                assign(idxl());
                pop();
                line(545);
                push_symbol(base+0);//rlist
                push_symbol(base+14);//ir
                idxr();
                _clp_rtrim(1);
                push_symbol(base+4);//right
                add();
                push_symbol(base+0);//rlist
                push_symbol(base+14);//ir
                assign(idxl());
                pop();
            if_56_1:
            if_56_0:;
        lab_55_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+10);//i
        add();
        assign(base+10);//i
        goto lab_55_0;
        lab_55_2:;
        }
        line(549);
        push_symbol(base+12);//sep
        push_symbol(base+15);//ls
        idxr();
        addnum(1);
        assign(base+13);//il
        pop();
        line(550);
        push_symbol(base+8);//imax
        assign(base+14);//ir
        pop();
        line(554);
        line(551);
        push_symbol(base+13);//il
        push_symbol(base+14);//ir
        lteq();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+2);//smart
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+0);//rlist
        push_symbol(base+13);//il
        idxr();
        push(&ONE);
        _clp_left(2);
        push_symbol(base+16);//smartchar
        ss();
        }
        topnot();
        }
        if(!flag()) goto if_57_1;
            line(552);
            push_symbol(base+3);//left
            push_symbol(base+0);//rlist
            push_symbol(base+13);//il
            idxr();
            _clp_ltrim(1);
            add();
            push_symbol(base+0);//rlist
            push_symbol(base+13);//il
            assign(idxl());
            pop();
            line(553);
            push_symbol(base+0);//rlist
            push_symbol(base+14);//ir
            idxr();
            _clp_rtrim(1);
            push_symbol(base+4);//right
            add();
            push_symbol(base+0);//rlist
            push_symbol(base+14);//ir
            assign(idxl());
            pop();
        if_57_1:
        if_57_0:;
    if_54_1:
    if_54_0:;
    line(557);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_result_logify(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("result_logify",base);
//
    line(562);
    push_symbol(base+0);//rlist
    push_symbol(base+1);//match
    push(&NIL);
    eqeq();
    if(flag()){
    binary(".F.");
    }else{
    binary(".T.");
    }
    _clp_aadd(2);
    pop();
    line(563);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_markertype(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("markertype",base);
//
    line(568);
    push_symbol(base+0);//n
    number(1000);
    div();
    _clp_int(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_markerinfo(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("markerinfo",base);
//
    line(571);
    push_symbol(base+0);//n
    number(1000);
    modulo();
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_markervalue(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("markervalue",base);
//
    line(574);
    push_symbol(base+0);//type
    mulnum(1000);
    push_symbol(base+1);//info
    add();
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_nexttoken(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("nexttoken",base);
//
    line(579);
    push_symbol(base+0);//rule
    _clp_len(1);
    assign(base+3);//lr
    pop();
    line(585);
    lab_58_1:
    line(580);
    push_symbol(base+1);//n
    push(&ONE);
    add();
    assign(base+1);//n
    push_symbol(base+3);//lr
    lteq();
    if(!flag()) goto lab_58_2;
        line(581);
        push_symbol(base+0);//rule
        push_symbol(base+1);//n
        idxr();
        assign(base+2);//ntok
        pop();
        line(584);
        line(582);
        push_symbol(base+2);//ntok
        _clp_valtype(1);
        string(L"L");
        neeq();
        if(flag()){
        push(&TRUE);
        }else{
        push_symbol(base+2);//ntok
        }
        if(!flag()) goto if_59_1;
            line(583);
            goto lab_58_2;//exit
        if_59_1:
        if_59_0:;
    goto lab_58_1;
    lab_58_2:;
    line(586);
    push_symbol(base+2);//ntok
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

