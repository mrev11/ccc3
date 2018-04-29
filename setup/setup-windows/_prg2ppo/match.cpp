//input: match.ppo (5.0.21)

#include <cccdef.h>

extern void _clp_aadd(int argno);
extern void _clp_adel(int argno);
extern void _clp_array(int argno);
extern void _clp_asize(int argno);
extern void _clp_atail(int argno);
extern void _clp_cx_df_get(int argno);
extern void _clp_cx_tr_get(int argno);
extern void _clp_empty(int argno);
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
static void _ini_match1_match_count(VALUE*);
static void _ini_match1_match_leftb(VALUE*);
static void _ini_match1_match_state(VALUE*);

class _method3_add: public _method3_{public: _method3_add():_method3_("add"){};}; static _method3_add _o_method_add;
class _method3_buffer: public _method3_{public: _method3_buffer():_method3_("buffer"){};}; static _method3_buffer _o_method_buffer;
class _method3_bufidx: public _method3_{public: _method3_bufidx():_method3_("bufidx"){};}; static _method3_bufidx _o_method_bufidx;
class _method3_clear: public _method3_{public: _method3_clear():_method3_("clear"){};}; static _method3_clear _o_method_clear;
class _method3_get: public _method3_{public: _method3_get():_method3_("get"){};}; static _method3_get _o_method_get;
class _method3_index: public _method3_{public: _method3_index():_method3_("index"){};}; static _method3_index _o_method_index;
class _method3_len: public _method3_{public: _method3_len():_method3_("len"){};}; static _method3_len _o_method_len;
class _method3_next: public _method3_{public: _method3_next():_method3_("next"){};}; static _method3_next _o_method_next;
class _method3_unget: public _method3_{public: _method3_unget():_method3_("unget"){};}; static _method3_unget _o_method_unget;

//=======================================================================
void _clp_match(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+15)PUSHNIL();
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
    line(136);
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
        line(93);
        push(&TRUE);
        assign(base+14);//beglin
        pop();
        line(129);
        lab_8_1:
        line(95);
        push_symbol(base+1);//inp
        _o_method_next.eval(1);
        assign(base+11);//token
        push(&NIL);
        neeq();
        if(!flag()) goto lab_8_2;
            line(97);
            push_symbol(base+11);//token
            _clp_upper(1);
            assign(base+11);//token
            pop();
            line(99);
            push(&FALSE);
            assign(base+10);//reptrn
            pop();
            line(111);
            line(101);
            push(&ZERO);
            push_symbol(base+4);//rtrn
            push_symbol(base+11);//token
            push_symbol(base+6);//cxtrn
            _clp_rule_search(3);
            assign(base+12);//n
            lt();
            if(!flag()) goto if_9_1;
                line(110);
                lab_10_1:
                line(102);
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
                    line(108);
                    line(103);
                    push_symbol(base+14);//beglin
                    if(flag()){
                    push(&TRUE);
                    }else{
                    push_symbol(base+4);//rtrn
                    push_symbol(base+12);//n
                    idxr();
                    idxr0(1);
                    _clp_atail(1);
                    push(&NIL);
                    neeq();
                    }
                    if(!flag()){
                    push(&FALSE);
                    }else{
                    push_symbol(base+4);//rtrn
                    push_symbol(base+12);//n
                    idxr();
                    push_symbol(base+1);//inp
                    push(&FALSE);
                    _clp_match1(3);
                    }
                    if(!flag()) goto if_11_1;
                        line(105);
                        push(&TRUE);
                        assign(base+10);//reptrn
                        pop();
                        line(106);
                        push(&TRUE);
                        assign(base+13);//reprocess
                        pop();
                        line(107);
                        goto lab_10_2;//exit
                    if_11_1:
                    if_11_0:;
                    line(109);
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
            line(128);
            line(117);
            push_symbol(base+10);//reptrn
            topnot();
            if(!flag()) goto if_12_1;
                line(118);
                push_symbol(base+1);//inp
                _o_method_get.eval(1);
                assign(base+11);//token
                pop();
                line(119);
                push_symbol(base+2);//out
                push_symbol(base+11);//token
                _o_method_add.eval(2);
                pop();
                line(127);
                line(121);
                push_symbol(base+11);//token
                _clp_empty(1);
                if(!flag()) goto if_13_1;
                goto if_13_0;
                if_13_1:
                line(123);
                push_symbol(base+11);//token
                binary(";");
                eqeq();
                if(!flag()) goto if_13_2;
                    line(124);
                    push(&TRUE);
                    assign(base+14);//beglin
                    pop();
                goto if_13_0;
                if_13_2:
                line(125);
                    line(126);
                    push(&FALSE);
                    assign(base+14);//beglin
                    pop();
                if_13_3:
                if_13_0:;
            if_12_1:
            if_12_0:;
        goto lab_8_1;
        lab_8_2:;
        line(135);
        line(131);
        push_symbol(base+13);//reprocess
        if(!flag()) goto if_14_1;
            line(132);
            push_symbol(base+1);//inp
            _o_method_clear.eval(1);
            pop();
            line(133);
            push_symbol(base+1);//inp
            push_symbol(base+2);//out
            _o_method_buffer.eval(1);
            push_symbol(base+2);//out
            _o_method_len.eval(1);
            _o_method_unget.eval(3);
            pop();
            line(134);
            push_symbol(base+2);//out
            _o_method_clear.eval(1);
            pop();
        if_14_1:
        if_14_0:;
    goto lab_1_1;
    lab_1_2:;
    line(138);
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
while(stack<base+19)PUSHNIL();
argno=3;
push_call("match1",base);
//
    line(152);
    push(&ZERO);
    assign(base+3);//match_level
    pop();
    line(154);
    static stvarloc _st_match_count(_ini_match1_match_count,base);
    line(155);
    static stvarloc _st_match_state(_ini_match1_match_state,base);
    line(156);
    static stvarloc _st_match_leftb(_ini_match1_match_leftb,base);
    line(158);
    push(&ZERO);
    assign(base+5);//mcount
    pop();
    line(159);
    push_symbol(base+0);//rule
    idxr0(1);
    assign(base+6);//leftside
    pop();
    line(160);
    push_symbol(base+0);//rule
    idxr0(2);
    assign(base+7);//rightside
    pop();
    line(161);
    push_symbol(base+6);//leftside
    _clp_len(1);
    _clp_array(1);
    assign(base+8);//matchlist
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
    push_symbol(base+5);//mcount
    push_symbol(_st_match_count.ptr);//match1
    push_symbol(base+3);//match_level
    assign2(idxxl());
    pop();
    push_symbol(base+4);//n
    push_symbol(_st_match_leftb.ptr);//match1
    push_symbol(base+3);//match_level
    assign2(idxxl());
    pop();
    push(&TRUE);
    push_symbol(_st_match_state.ptr);//match1
    push_symbol(base+3);//match_level
    assign2(idxxl());
    pop();
    line(287);
    {
    line(169);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_15_0:
    push_symbol(base+6);//leftside
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_15_2;
        line(171);
        push_symbol(base+6);//leftside
        push_symbol(base+4);//n
        idxr();
        assign(base+10);//token_rule
        pop();
        line(172);
        push_symbol(base+1);//inp
        push_symbol(base+5);//mcount
        addnum(1);
        _o_method_next.eval(2);
        assign(base+9);//token_input
        pop();
        line(177);
        lab_16_1:
        line(174);
        push_symbol(base+9);//token_input
        binary(" ");
        eqeq();
        if(!flag()) goto lab_16_2;
            line(175);
            push_symbol(base+5);//mcount
            dup();
            push(&ONE);
            add();
            assign(base+5);//mcount
            pop();
            pop();
            line(176);
            push_symbol(base+1);//inp
            push_symbol(base+5);//mcount
            addnum(1);
            _o_method_next.eval(2);
            assign(base+9);//token_input
            pop();
        goto lab_16_1;
        lab_16_2:;
        line(180);
        push_symbol(base+10);//token_rule
        _clp_valtype(1);
        assign(base+11);//type
        pop();
        line(208);
        line(183);
        push_symbol(base+11);//type
        string(L"L");
        eqeq();
        if(!flag()) goto if_17_1;
            line(206);
            line(185);
            push_symbol(base+10);//token_rule
            if(!flag()) goto if_18_1;
                line(186);
                push_symbol(_st_match_state.ptr);//match1
                push_symbol(base+3);//match_level
                idxr();
                assign(base+15);//x
                pop();
                line(187);
                push_symbol(base+3);//match_level
                dup();
                push(&ONE);
                add();
                assign(base+3);//match_level
                pop();
                pop();
                push_symbol(base+5);//mcount
                push_symbol(_st_match_count.ptr);//match1
                push_symbol(base+3);//match_level
                assign2(idxxl());
                pop();
                push_symbol(base+4);//n
                push_symbol(_st_match_leftb.ptr);//match1
                push_symbol(base+3);//match_level
                assign2(idxxl());
                pop();
                push(&TRUE);
                push_symbol(_st_match_state.ptr);//match1
                push_symbol(base+3);//match_level
                assign2(idxxl());
                pop();
                line(188);
                push_symbol(base+15);//x
                push_symbol(_st_match_state.ptr);//match1
                push_symbol(base+3);//match_level
                assign2(idxxl());
                pop();
            goto if_18_0;
            if_18_1:
            line(190);
                line(200);
                line(192);
                push_symbol(_st_match_state.ptr);//match1
                push_symbol(base+3);//match_level
                idxr();
                topnot();
                if(!flag()) goto if_19_1;
                    line(199);
                    {
                    line(197);
                    push(&ONE);
                    int sg=sign();
                    push_symbol(_st_match_leftb.ptr);//match1
                    push_symbol(base+3);//match_level
                    idxr();
                    assign(base+14);//i
                    lab_20_0:
                    push_symbol(base+4);//n
                    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_20_2;
                        line(198);
                        push(&NIL);
                        push_symbol(base+8);//matchlist
                        push_symbol(base+14);//i
                        assign2(idxxl());
                        pop();
                    lab_20_1:
                    push(&ONE);
                    dup();
                    sg=sign();
                    push_symbol(base+14);//i
                    add();
                    assign(base+14);//i
                    goto lab_20_0;
                    lab_20_2:;
                    }
                if_19_1:
                if_19_0:;
                line(205);
                line(202);
                push_symbol(base+3);//match_level
                push(&ONE);
                sub();
                assign(base+3);//match_level
                push(&ONE);
                lt();
                if(!flag()) goto if_21_1;
                    line(203);
                    push_symbol(base+6);//leftside
                    _clp_qout(1);
                    pop();
                    line(204);
                    string(nls_text(L"Unexpected ]"));
                    _clp_error(1);
                    pop();
                if_21_1:
                if_21_0:;
            if_18_2:
            if_18_0:;
            line(207);
            goto lab_15_1;//loop
        if_17_1:
        if_17_0:;
        line(213);
        line(211);
        push_symbol(_st_match_state.ptr);//match1
        push_symbol(base+3);//match_level
        idxr();
        topnot();
        if(!flag()) goto if_22_1;
            line(212);
            goto lab_15_1;//loop
        if_22_1:
        if_22_0:;
        line(282);
        line(216);
        push_symbol(base+11);//type
        string(L"CX");
        ss();
        if(!flag()) goto if_23_1;
            line(233);
            line(222);
            push_symbol(base+9);//token_input
            push(&NIL);
            eqeq();
            if(!flag()) goto if_24_1;
                line(223);
                push_symbol(_st_match_count.ptr);//match1
                push_symbol(base+3);//match_level
                idxr();
                assign(base+5);//mcount
                pop();
                push(&FALSE);
                push_symbol(_st_match_state.ptr);//match1
                push_symbol(base+3);//match_level
                assign2(idxxl());
                pop();
            goto if_24_0;
            if_24_1:
            line(225);
            push_symbol(base+2);//casesensitive
            if(!flag()){
            push(&FALSE);
            }else{
            push_symbol(base+9);//token_input
            push_symbol(base+10);//token_rule
            eqeq();
            topnot();
            }
            if(!flag()) goto if_24_2;
                line(226);
                push_symbol(_st_match_count.ptr);//match1
                push_symbol(base+3);//match_level
                idxr();
                assign(base+5);//mcount
                pop();
                push(&FALSE);
                push_symbol(_st_match_state.ptr);//match1
                push_symbol(base+3);//match_level
                assign2(idxxl());
                pop();
            goto if_24_0;
            if_24_2:
            line(228);
            push_symbol(base+2);//casesensitive
            topnot();
            if(!flag()){
            push(&FALSE);
            }else{
            push_symbol(base+9);//token_input
            _clp_upper(1);
            push_symbol(base+10);//token_rule
            eqeq();
            topnot();
            }
            if(!flag()) goto if_24_3;
                line(229);
                push_symbol(_st_match_count.ptr);//match1
                push_symbol(base+3);//match_level
                idxr();
                assign(base+5);//mcount
                pop();
                push(&FALSE);
                push_symbol(_st_match_state.ptr);//match1
                push_symbol(base+3);//match_level
                assign2(idxxl());
                pop();
            goto if_24_0;
            if_24_3:
            line(231);
                line(232);
                push_symbol(base+5);//mcount
                dup();
                push(&ONE);
                add();
                assign(base+5);//mcount
                pop();
                pop();
            if_24_4:
            if_24_0:;
        goto if_23_0;
        if_23_1:
        line(236);
        push_symbol(base+11);//type
        string(L"N");
        eqeq();
        if(!flag()) goto if_23_2;
            line(238);
            push_symbol(base+10);//token_rule
            _clp_markertype(1);
            assign(base+11);//type
            pop();
            line(239);
            push_symbol(base+10);//token_rule
            _clp_markerinfo(1);
            assign(base+12);//info
            pop();
            line(241);
            push_symbol(base+6);//leftside
            push_symbol(base+4);//n
            _clp_nexttoken(2);
            assign(base+16);//ntok
            pop();
            line(259);
            line(243);
            push_symbol(base+11);//type
            push(&ONE);
            eqeq();
            if(!flag()) goto if_25_1;
                line(244);
                push_symbol(base+1);//inp
                _o_method_buffer.eval(1);
                push_symbol(base+1);//inp
                push_symbol(base+5);//mcount
                addnum(1);
                _o_method_index.eval(2);
                push_symbol(base+16);//ntok
                _clp_match_regular(3);
                assign(base+13);//k
                pop();
            goto if_25_0;
            if_25_1:
            line(246);
            push_symbol(base+11);//type
            number(2);
            eqeq();
            if(!flag()) goto if_25_2;
                line(247);
                push_symbol(base+1);//inp
                _o_method_buffer.eval(1);
                push_symbol(base+1);//inp
                push_symbol(base+5);//mcount
                addnum(1);
                _o_method_index.eval(2);
                push_symbol(base+16);//ntok
                _clp_match_list(3);
                assign(base+13);//k
                pop();
            goto if_25_0;
            if_25_2:
            line(249);
            push_symbol(base+11);//type
            number(3);
            eqeq();
            if(!flag()) goto if_25_3;
                line(250);
                push_symbol(base+9);//token_input
                push_symbol(base+10);//token_rule
                _clp_match_restricted(2);
                assign(base+13);//k
                pop();
            goto if_25_0;
            if_25_3:
            line(252);
            push_symbol(base+11);//type
            number(4);
            eqeq();
            if(!flag()) goto if_25_4;
                line(253);
                push_symbol(base+1);//inp
                _o_method_buffer.eval(1);
                push_symbol(base+1);//inp
                push_symbol(base+5);//mcount
                addnum(1);
                _o_method_index.eval(2);
                push_symbol(base+16);//ntok
                _clp_match_extended(3);
                assign(base+13);//k
                pop();
            goto if_25_0;
            if_25_4:
            line(255);
            push_symbol(base+11);//type
            number(5);
            eqeq();
            if(!flag()) goto if_25_5;
                line(256);
                push_symbol(base+1);//inp
                _o_method_buffer.eval(1);
                push_symbol(base+1);//inp
                push_symbol(base+5);//mcount
                addnum(1);
                _o_method_index.eval(2);
                _clp_match_wild(2);
                assign(base+13);//k
                pop();
            goto if_25_0;
            if_25_5:
            line(257);
                line(258);
                push(&ZERO);
                assign(base+13);//k
                pop();
            if_25_6:
            if_25_0:;
            line(272);
            line(263);
            push_symbol(base+13);//k
            push(&ZERO);
            lteq();
            if(!flag()) goto if_26_1;
                line(264);
                push_symbol(_st_match_count.ptr);//match1
                push_symbol(base+3);//match_level
                idxr();
                assign(base+5);//mcount
                pop();
                push(&FALSE);
                push_symbol(_st_match_state.ptr);//match1
                push_symbol(base+3);//match_level
                assign2(idxxl());
                pop();
            goto if_26_0;
            if_26_1:
            line(265);
                line(266);
                push_symbol(base+13);//k
                _clp_array(1);
                assign(base+15);//x
                pop();
                line(269);
                {
                line(267);
                push(&ONE);
                int sg=sign();
                push(&ONE);
                assign(base+14);//i
                lab_27_0:
                push_symbol(base+13);//k
                if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_27_2;
                    line(268);
                    push_symbol(base+1);//inp
                    push_symbol(base+5);//mcount
                    push_symbol(base+14);//i
                    add();
                    _o_method_next.eval(2);
                    push_symbol(base+15);//x
                    push_symbol(base+14);//i
                    assign2(idxxl());
                    pop();
                lab_27_1:
                push(&ONE);
                dup();
                sg=sign();
                push_symbol(base+14);//i
                add();
                assign(base+14);//i
                goto lab_27_0;
                lab_27_2:;
                }
                line(270);
                push_symbol(base+5);//mcount
                push_symbol(base+13);//k
                add();
                assign(base+5);//mcount
                pop();
                line(271);
                push_symbol(base+15);//x
                push_symbol(base+8);//matchlist
                push_symbol(base+4);//n
                assign2(idxxl());
                pop();
            if_26_2:
            if_26_0:;
        goto if_23_0;
        if_23_2:
        line(274);
        push_symbol(base+11);//type
        string(L"U");
        eqeq();
        if(!flag()) goto if_23_3;
            line(281);
            line(275);
            push_symbol(base+9);//token_input
            push(&NIL);
            eqeq();
            if(!flag()) goto if_28_1;
            goto if_28_0;
            if_28_1:
            line(277);
            push_symbol(base+9);//token_input
            binary(";");
            eqeq();
            if(!flag()) goto if_28_2;
            goto if_28_0;
            if_28_2:
            line(279);
                line(280);
                push_symbol(_st_match_count.ptr);//match1
                push_symbol(base+3);//match_level
                idxr();
                assign(base+5);//mcount
                pop();
                push(&FALSE);
                push_symbol(_st_match_state.ptr);//match1
                push_symbol(base+3);//match_level
                assign2(idxxl());
                pop();
            if_28_3:
            if_28_0:;
        if_23_3:
        if_23_0:;
        line(286);
        line(284);
        push_symbol(base+3);//match_level
        push(&ONE);
        eqeq();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(_st_match_state.ptr);//match1
        push_symbol(base+3);//match_level
        idxr();
        topnot();
        }
        if(!flag()) goto if_29_1;
            line(285);
            goto lab_15_2;//exit
        if_29_1:
        if_29_0:;
    lab_15_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_15_0;
    lab_15_2:;
    }
    line(292);
    line(289);
    push_symbol(base+3);//match_level
    push(&ONE);
    neeq();
    if(!flag()) goto if_30_1;
        line(290);
        push_symbol(base+6);//leftside
        _clp_qout(1);
        pop();
        line(291);
        string(nls_text(L"Unbalanced ["));
        _clp_error(1);
        pop();
    if_30_1:
    if_30_0:;
    line(294);
    push_symbol(base+4);//n
    push_symbol(base+6);//leftside
    _clp_len(1);
    gt();
    assign(base+17);//result
    pop();
    line(305);
    line(296);
    push_symbol(base+17);//result
    if(!flag()) goto if_31_1;
        line(297);
        push_symbol(base+7);//rightside
        push_symbol(base+8);//matchlist
        _clp_replacelist(2);
        assign(base+18);//rlist
        pop();
        line(298);
        push_symbol(base+1);//inp
        _o_method_bufidx.eval(1);
        push_symbol(base+5);//mcount
        add();
        push_symbol(base+1);//inp
        swap();
        _o_method_bufidx.eval(2);
        pop();
        line(299);
        push_symbol(base+1);//inp
        push_symbol(base+18);//rlist
        _o_method_unget.eval(2);
        pop();
    if_31_1:
    if_31_0:;
    line(307);
    push_symbol(base+17);//result
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _ini_match1_match_count(VALUE* base)
{
    number(32);
    _clp_array(1);
}

static void _ini_match1_match_state(VALUE* base)
{
    number(32);
    _clp_array(1);
}

static void _ini_match1_match_leftb(VALUE* base)
{
    number(32);
    _clp_array(1);
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
    line(320);
    array(0);
    assign(base+2);//rlist
    pop();
    line(321);
    line(322);
    push(&FALSE);
    assign(base+9);//optional
    pop();
    line(323);
    push(&FALSE);
    assign(base+12);//glue
    pop();
    line(383);
    {
    line(325);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_32_0:
    push_symbol(base+0);//rightside
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_32_2;
        line(326);
        push_symbol(base+0);//rightside
        push_symbol(base+4);//n
        idxr();
        assign(base+3);//x
        pop();
        line(344);
        line(328);
        push_symbol(base+3);//x
        _clp_valtype(1);
        string(L"L");
        eqeq();
        if(!flag()) goto if_33_1;
            line(342);
            line(329);
            push_symbol(base+3);//x
            if(!flag()) goto if_34_1;
                line(330);
                push(&TRUE);
                assign(base+9);//optional
                pop();
                line(331);
                push(&FALSE);
                assign(base+10);//optstat
                pop();
                line(332);
                push_symbol(base+2);//rlist
                _clp_len(1);
                assign(base+11);//optlen
                pop();
            goto if_34_0;
            if_34_1:
            line(333);
                line(334);
                push(&FALSE);
                assign(base+9);//optional
                pop();
                line(341);
                line(335);
                push_symbol(base+10);//optstat
                topnot();
                if(!flag()) goto if_35_1;
                    line(340);
                    push_symbol(base+2);//rlist
                    push_symbol(base+11);//optlen
                    _clp_asize(2);
                    pop();
                if_35_1:
                if_35_0:;
            if_34_2:
            if_34_0:;
            line(343);
            goto lab_32_1;//loop
        if_33_1:
        if_33_0:;
        line(382);
        line(346);
        push_symbol(base+3);//x
        _clp_valtype(1);
        string(L"CX");
        ss();
        if(!flag()) goto if_36_1;
            line(347);
            push_symbol(base+2);//rlist
            push_symbol(base+3);//x
            _clp_aadd(2);
            pop();
            line(351);
            line(349);
            push_symbol(base+3);//x
            binary("##");
            eqeq();
            if(!flag()) goto if_37_1;
                line(350);
                push(&TRUE);
                assign(base+12);//glue
                pop();
            if_37_1:
            if_37_0:;
        goto if_36_0;
        if_36_1:
        line(353);
        push_symbol(base+3);//x
        _clp_valtype(1);
        string(L"N");
        eqeq();
        if(!flag()) goto if_36_2;
            line(355);
            push_symbol(base+3);//x
            _clp_markertype(1);
            assign(base+6);//type
            pop();
            line(356);
            push_symbol(base+3);//x
            _clp_markerinfo(1);
            assign(base+7);//info
            pop();
            line(357);
            push_symbol(base+1);//matchlist
            push_symbol(base+7);//info
            idxr();
            assign(base+8);//match
            pop();
            line(361);
            line(359);
            push_symbol(base+8);//match
            push(&NIL);
            neeq();
            if(!flag()) goto if_38_1;
                line(360);
                push(&TRUE);
                assign(base+10);//optstat
                pop();
            if_38_1:
            if_38_0:;
            line(381);
            line(363);
            push_symbol(base+6);//type
            push(&ONE);
            eqeq();
            if(!flag()) goto if_39_1;
                line(364);
                push_symbol(base+2);//rlist
                push_symbol(base+8);//match
                _clp_result_regular(2);
                pop();
            goto if_39_0;
            if_39_1:
            line(366);
            push_symbol(base+6);//type
            number(2);
            eqeq();
            if(!flag()) goto if_39_2;
                line(367);
                push_symbol(base+2);//rlist
                push_symbol(base+8);//match
                _clp_result_dumbstr(2);
                pop();
            goto if_39_0;
            if_39_2:
            line(369);
            push_symbol(base+6);//type
            number(3);
            eqeq();
            if(!flag()) goto if_39_3;
                line(370);
                push_symbol(base+2);//rlist
                push_symbol(base+8);//match
                push(&FALSE);
                binary("\"");
                binary("\"");
                _clp_result_stringify(5);
                pop();
            goto if_39_0;
            if_39_3:
            line(372);
            push_symbol(base+6);//type
            number(4);
            eqeq();
            if(!flag()) goto if_39_4;
                line(373);
                push_symbol(base+2);//rlist
                push_symbol(base+8);//match
                push(&TRUE);
                binary("\"");
                binary("\"");
                _clp_result_stringify(5);
                pop();
            goto if_39_0;
            if_39_4:
            line(375);
            push_symbol(base+6);//type
            number(5);
            eqeq();
            if(!flag()) goto if_39_5;
                line(376);
                push_symbol(base+2);//rlist
                push_symbol(base+8);//match
                push(&FALSE);
                binary("{||");
                binary("}");
                _clp_result_stringify(5);
                pop();
            goto if_39_0;
            if_39_5:
            line(378);
            push_symbol(base+6);//type
            number(6);
            eqeq();
            if(!flag()) goto if_39_6;
                line(379);
                push_symbol(base+2);//rlist
                push_symbol(base+8);//match
                _clp_result_logify(2);
                pop();
            if_39_6:
            if_39_0:;
        if_36_2:
        if_36_0:;
    lab_32_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_32_0;
    lab_32_2:;
    }
    line(387);
    line(385);
    push_symbol(base+12);//glue
    if(!flag()) goto if_40_1;
        line(386);
        push_symbol(base+2);//rlist
        _clp_glue(1);
        pop();
    if_40_1:
    if_40_0:;
    line(389);
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
    line(398);
    binary("##");
    assign(base+2);//gl
    pop();
    binary("\"");
    binary("'");
    add();
    assign(base+3);//qq
    pop();
    line(411);
    {
    line(400);
    push(&ONE);
    int sg=sign();
    number(2);
    assign(base+1);//n
    lab_41_0:
    push_symbol(base+0);//rlist
    _clp_len(1);
    addnum(-1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_41_2;
        line(410);
        line(401);
        push_symbol(base+0);//rlist
        push_symbol(base+1);//n
        idxr();
        push_symbol(base+2);//gl
        eqeq();
        if(!flag()) goto if_42_1;
            line(406);
            line(402);
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
            if(!flag()) goto if_43_1;
                line(403);
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
                assign2(idxxl());
                pop();
            goto if_43_0;
            if_43_1:
            line(404);
                line(405);
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
                assign2(idxxl());
                pop();
            if_43_2:
            if_43_0:;
            line(407);
            push_symbol(base+0);//rlist
            push_symbol(base+1);//n
            _clp_adel(2);
            pop();
            line(408);
            push_symbol(base+0);//rlist
            push_symbol(base+1);//n
            _clp_adel(2);
            pop();
            line(409);
            push_symbol(base+0);//rlist
            push_symbol(base+0);//rlist
            _clp_len(1);
            addnum(-2);
            _clp_asize(2);
            pop();
        if_42_1:
        if_42_0:;
    lab_41_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+1);//n
    add();
    assign(base+1);//n
    goto lab_41_0;
    lab_41_2:;
    }
    line(413);
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
    line(427);
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
stack=base+min(argno,3);
while(stack<base+6)PUSHNIL();
argno=3;
push_call("match_list",base);
//
    line(433);
    push(&ZERO);
    assign(base+3);//k
    pop();
    push_symbol(base+0);//toklist
    _clp_len(1);
    assign(base+5);//lentok
    pop();
    line(485);
    line(444);
    push_symbol(base+2);//nexttok
    _clp_valtype(1);
    string(L"CX");
    ss();
    topnot();
    if(!flag()) goto if_44_1;
        line(460);
        lab_45_1:
        line(446);
        push_symbol(base+1);//n
        push_symbol(base+3);//k
        add();
        push_symbol(base+5);//lentok
        lteq();
        if(!flag()) goto lab_45_2;
            line(459);
            line(447);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            idxr();
            binary(",");
            eqeq();
            if(!flag()) goto if_46_1;
                line(449);
                push_symbol(base+3);//k
                push(&ONE);
                add();
                assign(base+3);//k
                pop();
            goto if_46_0;
            if_46_1:
            line(450);
            push(&ZERO);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            binary(",");
            _clp_xtxlegal(3);
            assign(base+4);//i
            lt();
            if(!flag()) goto if_46_2;
                line(452);
                push_symbol(base+3);//k
                push_symbol(base+4);//i
                addnum(1);
                add();
                assign(base+3);//k
                pop();
            goto if_46_0;
            if_46_2:
            line(453);
            push(&ZERO);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            _clp_xtxlegal(2);
            assign(base+4);//i
            lt();
            if(!flag()) goto if_46_3;
                line(455);
                push_symbol(base+3);//k
                push_symbol(base+4);//i
                add();
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            goto if_46_0;
            if_46_3:
            line(456);
                line(458);
                push_symbol(base+3);//k
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            if_46_4:
            if_46_0:;
        goto lab_45_1;
        lab_45_2:;
        line(462);
        push_symbol(base+3);//k
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_44_0;
    if_44_1:
    line(464);
        line(482);
        lab_47_1:
        line(465);
        push_symbol(base+1);//n
        push_symbol(base+3);//k
        add();
        push_symbol(base+5);//lentok
        lteq();
        if(!flag()) goto lab_47_2;
            line(481);
            line(466);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            idxr();
            push_symbol(base+2);//nexttok
            eqeq();
            if(!flag()) goto if_48_1;
                line(468);
                push_symbol(base+3);//k
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            goto if_48_0;
            if_48_1:
            line(469);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            idxr();
            binary(",");
            eqeq();
            if(!flag()) goto if_48_2;
                line(471);
                push_symbol(base+3);//k
                push(&ONE);
                add();
                assign(base+3);//k
                pop();
            goto if_48_0;
            if_48_2:
            line(472);
            push(&ZERO);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            push_symbol(base+2);//nexttok
            _clp_xtxlegal(3);
            assign(base+4);//i
            lt();
            if(!flag()) goto if_48_3;
                line(474);
                push_symbol(base+3);//k
                push_symbol(base+4);//i
                add();
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            goto if_48_0;
            if_48_3:
            line(475);
            push(&ZERO);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            binary(",");
            _clp_xtxlegal(3);
            assign(base+4);//i
            lt();
            if(!flag()) goto if_48_4;
                line(477);
                push_symbol(base+3);//k
                push_symbol(base+4);//i
                addnum(1);
                add();
                assign(base+3);//k
                pop();
            goto if_48_0;
            if_48_4:
            line(478);
                line(480);
                push(&ZERO);
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            if_48_5:
            if_48_0:;
        goto lab_47_1;
        lab_47_2:;
        line(484);
        push(&ZERO);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_44_2:
    if_44_0:;
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
    line(490);
    push(&ZERO);
    assign(base+3);//k
    pop();
    line(498);
    line(492);
    push_symbol(base+0);//tokinp
    push(&NIL);
    neeq();
    if(!flag()) goto if_49_1;
        line(494);
        push_symbol(base+1);//tokrul
        _clp_markerinfo(1);
        _clp_rule_if_get(1);
        assign(base+2);//info
        pop();
        line(497);
        line(495);
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
        if(!flag()) goto if_50_1;
            line(496);
            push(&ONE);
            assign(base+3);//k
            pop();
        if_50_1:
        if_50_0:;
    if_49_1:
    if_49_0:;
    line(500);
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
    line(506);
    line(512);
    line(508);
    push_symbol(base+0);//toklist
    _clp_len(1);
    push_symbol(base+1);//n
    lt();
    if(!flag()) goto if_51_1;
        line(509);
        push(&ZERO);
        assign(base+3);//k
        pop();
    goto if_51_0;
    if_51_1:
    line(510);
        line(511);
        push_symbol(base+0);//toklist
        push_symbol(base+1);//n
        push_symbol(base+2);//nexttok
        _clp_xtxlegal(3);
        assign(base+3);//k
        pop();
    if_51_2:
    if_51_0:;
    line(513);
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
    line(518);
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
    line(523);
    line(526);
    {
    line(524);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//i
    lab_52_0:
    push_symbol(base+1);//match
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_52_2;
        line(525);
        push_symbol(base+0);//rlist
        push_symbol(base+1);//match
        push_symbol(base+2);//i
        idxr();
        _clp_aadd(2);
        pop();
    lab_52_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//i
    add();
    assign(base+2);//i
    goto lab_52_0;
    lab_52_2:;
    }
    line(527);
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
while(stack<base+4)PUSHNIL();
argno=2;
push_call("result_dumbstr",base);
//
    line(532);
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
    line(533);
    binary("\"");
    push_symbol(base+2);//x
    ss();
    if(flag()){
    binary("'");
    }else{
    binary("\"");
    }
    assign(base+3);//q
    pop();
    line(534);
    push_symbol(base+0);//rlist
    push_symbol(base+3);//q
    push_symbol(base+2);//x
    add();
    push_symbol(base+3);//q
    add();
    _clp_aadd(2);
    pop();
    line(535);
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
    line(544);
    line(545);
    line(546);
    line(547);
    line(549);
    binary("(");
    binary("\"");
    add();
    binary("'");
    add();
    assign(base+16);//smartchar
    pop();
    line(553);
    line(551);
    push_symbol(base+1);//match
    push(&NIL);
    eqeq();
    if(!flag()) goto if_53_1;
        line(552);
        push(&NIL);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_53_1:
    if_53_0:;
    line(555);
    push_symbol(base+0);//rlist
    _clp_len(1);
    assign(base+5);//lr
    pop();
    line(556);
    push_symbol(base+1);//match
    _clp_len(1);
    assign(base+6);//lm
    pop();
    line(557);
    push_symbol(base+5);//lr
    addnum(1);
    assign(base+7);//imin
    pop();
    line(558);
    push_symbol(base+5);//lr
    push_symbol(base+6);//lm
    add();
    assign(base+8);//imax
    pop();
    line(559);
    array(0);
    assign(base+12);//sep
    pop();
    line(560);
    push(&ZERO);
    assign(base+11);//par
    pop();
    line(562);
    push_symbol(base+0);//rlist
    push_symbol(base+8);//imax
    _clp_asize(2);
    pop();
    line(585);
    {
    line(564);
    push(&ONE);
    int sg=sign();
    push_symbol(base+7);//imin
    assign(base+10);//i
    lab_54_0:
    push_symbol(base+8);//imax
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_54_2;
        line(565);
        push_symbol(base+1);//match
        push_symbol(base+10);//i
        push_symbol(base+5);//lr
        sub();
        idxr();
        assign(base+9);//token
        pop();
        line(566);
        push_symbol(base+9);//token
        push_symbol(base+0);//rlist
        push_symbol(base+10);//i
        assign2(idxxl());
        pop();
        line(572);
        line(568);
        push_symbol(base+9);//token
        binary("([{");
        ss();
        if(!flag()) goto if_55_1;
            line(569);
            push_symbol(base+11);//par
            dup();
            push(&ONE);
            add();
            assign(base+11);//par
            pop();
            pop();
        goto if_55_0;
        if_55_1:
        line(570);
        push_symbol(base+9);//token
        binary(")]}");
        ss();
        if(!flag()) goto if_55_2;
            line(571);
            push_symbol(base+11);//par
            dup();
            push(&ONE);
            sub();
            assign(base+11);//par
            pop();
            pop();
        if_55_2:
        if_55_0:;
        line(576);
        line(574);
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
        if(!flag()) goto if_56_1;
            line(575);
            push_symbol(base+12);//sep
            push_symbol(base+10);//i
            _clp_aadd(2);
            pop();
        if_56_1:
        if_56_0:;
        line(582);
        line(578);
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
        if(!flag()) goto if_57_1;
            line(579);
            binary("'");
            assign(base+4);//right
            assign(base+3);//left
            pop();
        goto if_57_0;
        if_57_1:
        line(580);
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
        if(!flag()) goto if_57_2;
            line(581);
            binary("\"");
            assign(base+4);//right
            assign(base+3);//left
            pop();
        if_57_2:
        if_57_0:;
    lab_54_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+10);//i
    add();
    assign(base+10);//i
    goto lab_54_0;
    lab_54_2:;
    }
    line(587);
    push_symbol(base+12);//sep
    _clp_len(1);
    assign(base+15);//ls
    pop();
    line(589);
    push_symbol(base+7);//imin
    assign(base+13);//il
    pop();
    line(590);
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
    line(595);
    line(592);
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
    if(!flag()) goto if_58_1;
        line(593);
        push_symbol(base+3);//left
        push_symbol(base+0);//rlist
        push_symbol(base+13);//il
        idxr();
        _clp_ltrim(1);
        add();
        push_symbol(base+0);//rlist
        push_symbol(base+13);//il
        assign2(idxxl());
        pop();
        line(594);
        push_symbol(base+0);//rlist
        push_symbol(base+14);//ir
        idxr();
        _clp_rtrim(1);
        push_symbol(base+4);//right
        add();
        push_symbol(base+0);//rlist
        push_symbol(base+14);//ir
        assign2(idxxl());
        pop();
    if_58_1:
    if_58_0:;
    line(614);
    line(597);
    push_symbol(base+15);//ls
    push(&ZERO);
    gt();
    if(!flag()) goto if_59_1;
        line(606);
        {
        line(599);
        push(&ONE);
        int sg=sign();
        number(2);
        assign(base+10);//i
        lab_60_0:
        push_symbol(base+15);//ls
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_60_2;
            line(600);
            push_symbol(base+12);//sep
            push_symbol(base+10);//i
            addnum(-1);
            idxr();
            addnum(1);
            assign(base+13);//il
            pop();
            line(601);
            push_symbol(base+12);//sep
            push_symbol(base+10);//i
            idxr();
            addnum(-1);
            assign(base+14);//ir
            pop();
            line(605);
            line(602);
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
            if(!flag()) goto if_61_1;
                line(603);
                push_symbol(base+3);//left
                push_symbol(base+0);//rlist
                push_symbol(base+13);//il
                idxr();
                _clp_ltrim(1);
                add();
                push_symbol(base+0);//rlist
                push_symbol(base+13);//il
                assign2(idxxl());
                pop();
                line(604);
                push_symbol(base+0);//rlist
                push_symbol(base+14);//ir
                idxr();
                _clp_rtrim(1);
                push_symbol(base+4);//right
                add();
                push_symbol(base+0);//rlist
                push_symbol(base+14);//ir
                assign2(idxxl());
                pop();
            if_61_1:
            if_61_0:;
        lab_60_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+10);//i
        add();
        assign(base+10);//i
        goto lab_60_0;
        lab_60_2:;
        }
        line(608);
        push_symbol(base+12);//sep
        push_symbol(base+15);//ls
        idxr();
        addnum(1);
        assign(base+13);//il
        pop();
        line(609);
        push_symbol(base+8);//imax
        assign(base+14);//ir
        pop();
        line(613);
        line(610);
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
        if(!flag()) goto if_62_1;
            line(611);
            push_symbol(base+3);//left
            push_symbol(base+0);//rlist
            push_symbol(base+13);//il
            idxr();
            _clp_ltrim(1);
            add();
            push_symbol(base+0);//rlist
            push_symbol(base+13);//il
            assign2(idxxl());
            pop();
            line(612);
            push_symbol(base+0);//rlist
            push_symbol(base+14);//ir
            idxr();
            _clp_rtrim(1);
            push_symbol(base+4);//right
            add();
            push_symbol(base+0);//rlist
            push_symbol(base+14);//ir
            assign2(idxxl());
            pop();
        if_62_1:
        if_62_0:;
    if_59_1:
    if_59_0:;
    line(616);
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
    line(621);
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
    line(622);
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
    line(627);
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
    line(630);
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
    line(633);
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
    line(638);
    push_symbol(base+0);//rule
    _clp_len(1);
    assign(base+3);//lr
    pop();
    line(644);
    lab_63_1:
    line(639);
    push_symbol(base+1);//n
    push(&ONE);
    add();
    assign(base+1);//n
    push_symbol(base+3);//lr
    lteq();
    if(!flag()) goto lab_63_2;
        line(640);
        push_symbol(base+0);//rule
        push_symbol(base+1);//n
        idxr();
        assign(base+2);//ntok
        pop();
        line(643);
        line(641);
        push_symbol(base+2);//ntok
        _clp_valtype(1);
        string(L"L");
        neeq();
        if(flag()){
        push(&TRUE);
        }else{
        push_symbol(base+2);//ntok
        }
        if(!flag()) goto if_64_1;
            line(642);
            goto lab_63_2;//exit
        if_64_1:
        if_64_0:;
    goto lab_63_1;
    lab_63_2:;
    line(645);
    push_symbol(base+2);//ntok
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

