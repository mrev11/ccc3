//input: ppo/match.ppo (5.7.0.1)

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

class _method6_add: public _method6_{public: _method6_add():_method6_("add"){};}; static _method6_add _o_method_add;
class _method6_buffer: public _method6_{public: _method6_buffer():_method6_("buffer"){};}; static _method6_buffer _o_method_buffer;
class _method6_bufidx: public _method6_{public: _method6_bufidx():_method6_("bufidx"){};}; static _method6_bufidx _o_method_bufidx;
class _method6_clear: public _method6_{public: _method6_clear():_method6_("clear"){};}; static _method6_clear _o_method_clear;
class _method6_get: public _method6_{public: _method6_get():_method6_("get"){};}; static _method6_get _o_method_get;
class _method6_index: public _method6_{public: _method6_index():_method6_("index"){};}; static _method6_index _o_method_index;
class _method6_len: public _method6_{public: _method6_len():_method6_("len"){};}; static _method6_len _o_method_len;
class _method6_next: public _method6_{public: _method6_next():_method6_("next"){};}; static _method6_next _o_method_next;
class _method6_unget: public _method6_{public: _method6_unget():_method6_("unget"){};}; static _method6_unget _o_method_unget;

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
        cmp_238:;
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
            cmp_262:;
            if(!flag()) goto if_3_1;
                line(68);
                lab_4_1:
                line(61);
                push_symbol(base+12);//n
                push_symbol(base+7);//lendef
                lteq();
                cmp_305:;
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
                cmp_312:;
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
        cmp_574:;
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
            cmp_616:;
            if(!flag()) goto if_9_1;
                line(110);
                lab_10_1:
                line(102);
                push_symbol(base+12);//n
                push_symbol(base+9);//lentrn
                lteq();
                cmp_659:;
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
                cmp_666:;
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
                    cmp_718:;
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
                cmp_881:;
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
    static stvar _st_match_count;
    static int _ini_match_count=[=](){
        number(32);
        _clp_array(1);
        assign(_st_match_count.ptr);
        pop();
        return 1;
    }();
    line(155);
    static stvar _st_match_state;
    static int _ini_match_state=[=](){
        number(32);
        _clp_array(1);
        assign(_st_match_state.ptr);
        pop();
        return 1;
    }();
    line(156);
    static stvar _st_match_leftb;
    static int _ini_match_leftb=[=](){
        number(32);
        _clp_array(1);
        assign(_st_match_leftb.ptr);
        pop();
        return 1;
    }();
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
        cmp_1363:;
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
        cmp_1432:;
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
                cmp_1610:;
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
            cmp_1727:;
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
            cmp_1777:;
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
            cmp_1839:;
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
        cmp_1908:;
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
            cmp_1983:;
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
            cmp_2048:;
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
            cmp_2113:;
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
            cmp_2154:;
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
            cmp_2219:;
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
            cmp_2299:;
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
        cmp_2447:;
        if(!flag()) goto if_23_3;
            line(281);
            line(275);
            push_symbol(base+9);//token_input
            push(&NIL);
            eqeq();
            cmp_2461:;
            if(!flag()) goto if_28_1;
            goto if_28_0;
            if_28_1:
            line(277);
            push_symbol(base+9);//token_input
            binary(";");
            eqeq();
            cmp_2477:;
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
        cmp_2543:;
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
    cmp_2587:;
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
    cmp_2639:;
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
        cmp_2876:;
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
            cmp_3060:;
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
        cmp_3103:;
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
            cmp_3168:;
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
            cmp_3201:;
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
            cmp_3238:;
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
            cmp_3275:;
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
            cmp_3330:;
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
            cmp_3385:;
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
            cmp_3440:;
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
    line(412);
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
        line(411);
        line(401);
        push_symbol(base+0);//rlist
        push_symbol(base+1);//n
        idxr();
        push_symbol(base+2);//gl
        eqeq();
        cmp_3610:;
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
            line(410);
            push_symbol(base+1);//n
            push(&ONE);
            sub();
            assign(base+1);//n
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
    line(414);
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
    line(428);
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
    line(434);
    push(&ZERO);
    assign(base+3);//k
    pop();
    push_symbol(base+0);//toklist
    _clp_len(1);
    assign(base+5);//lentok
    pop();
    line(486);
    line(445);
    push_symbol(base+2);//nexttok
    _clp_valtype(1);
    string(L"CX");
    ss();
    topnot();
    if(!flag()) goto if_44_1;
        line(461);
        lab_45_1:
        line(447);
        push_symbol(base+1);//n
        push_symbol(base+3);//k
        add();
        push_symbol(base+5);//lentok
        lteq();
        cmp_4007:;
        if(!flag()) goto lab_45_2;
            line(460);
            line(448);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            idxr();
            binary(",");
            eqeq();
            cmp_4030:;
            if(!flag()) goto if_46_1;
                line(450);
                push_symbol(base+3);//k
                push(&ONE);
                add();
                assign(base+3);//k
                pop();
            goto if_46_0;
            if_46_1:
            line(451);
            push(&ZERO);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            binary(",");
            _clp_xtxlegal(3);
            assign(base+4);//i
            lt();
            cmp_4056:;
            if(!flag()) goto if_46_2;
                line(453);
                push_symbol(base+3);//k
                push_symbol(base+4);//i
                addnum(1);
                add();
                assign(base+3);//k
                pop();
            goto if_46_0;
            if_46_2:
            line(454);
            push(&ZERO);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            _clp_xtxlegal(2);
            assign(base+4);//i
            lt();
            cmp_4119:;
            if(!flag()) goto if_46_3;
                line(456);
                push_symbol(base+3);//k
                push_symbol(base+4);//i
                add();
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            goto if_46_0;
            if_46_3:
            line(457);
                line(459);
                push_symbol(base+3);//k
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            if_46_4:
            if_46_0:;
        goto lab_45_1;
        lab_45_2:;
        line(463);
        push_symbol(base+3);//k
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_44_0;
    if_44_1:
    line(465);
        line(483);
        lab_47_1:
        line(466);
        push_symbol(base+1);//n
        push_symbol(base+3);//k
        add();
        push_symbol(base+5);//lentok
        lteq();
        cmp_4213:;
        if(!flag()) goto lab_47_2;
            line(482);
            line(467);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            idxr();
            push_symbol(base+2);//nexttok
            eqeq();
            cmp_4236:;
            if(!flag()) goto if_48_1;
                line(469);
                push_symbol(base+3);//k
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            goto if_48_0;
            if_48_1:
            line(470);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            idxr();
            binary(",");
            eqeq();
            cmp_4268:;
            if(!flag()) goto if_48_2;
                line(472);
                push_symbol(base+3);//k
                push(&ONE);
                add();
                assign(base+3);//k
                pop();
            goto if_48_0;
            if_48_2:
            line(473);
            push(&ZERO);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            push_symbol(base+2);//nexttok
            _clp_xtxlegal(3);
            assign(base+4);//i
            lt();
            cmp_4294:;
            if(!flag()) goto if_48_3;
                line(475);
                push_symbol(base+3);//k
                push_symbol(base+4);//i
                add();
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            goto if_48_0;
            if_48_3:
            line(476);
            push(&ZERO);
            push_symbol(base+0);//toklist
            push_symbol(base+1);//n
            push_symbol(base+3);//k
            add();
            binary(",");
            _clp_xtxlegal(3);
            assign(base+4);//i
            lt();
            cmp_4354:;
            if(!flag()) goto if_48_4;
                line(478);
                push_symbol(base+3);//k
                push_symbol(base+4);//i
                addnum(1);
                add();
                assign(base+3);//k
                pop();
            goto if_48_0;
            if_48_4:
            line(479);
                line(481);
                push(&ZERO);
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            if_48_5:
            if_48_0:;
        goto lab_47_1;
        lab_47_2:;
        line(485);
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
    line(491);
    push(&ZERO);
    assign(base+3);//k
    pop();
    line(499);
    line(493);
    push_symbol(base+0);//tokinp
    push(&NIL);
    neeq();
    cmp_4490:;
    if(!flag()) goto if_49_1;
        line(495);
        push_symbol(base+1);//tokrul
        _clp_markerinfo(1);
        _clp_rule_if_get(1);
        assign(base+2);//info
        pop();
        line(498);
        line(496);
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
            line(497);
            push(&ONE);
            assign(base+3);//k
            pop();
        if_50_1:
        if_50_0:;
    if_49_1:
    if_49_0:;
    line(501);
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
    line(507);
    line(513);
    line(509);
    push_symbol(base+0);//toklist
    _clp_len(1);
    push_symbol(base+1);//n
    lt();
    cmp_4644:;
    if(!flag()) goto if_51_1;
        line(510);
        push(&ZERO);
        assign(base+3);//k
        pop();
    goto if_51_0;
    if_51_1:
    line(511);
        line(512);
        push_symbol(base+0);//toklist
        push_symbol(base+1);//n
        push_symbol(base+2);//nexttok
        _clp_xtxlegal(3);
        assign(base+3);//k
        pop();
    if_51_2:
    if_51_0:;
    line(514);
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
    line(519);
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
    line(524);
    line(527);
    {
    line(525);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//i
    lab_52_0:
    push_symbol(base+1);//match
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_52_2;
        line(526);
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
    line(528);
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
    line(533);
    push_symbol(base+1);//match
    push(&NIL);
    eqeq();
    cmp_4888:;
    if(flag()){
    binary("");
    }else{
    push_symbol(base+1);//match
    _clp_outline(1);
    }
    assign(base+2);//x
    pop();
    line(534);
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
    line(535);
    push_symbol(base+0);//rlist
    push_symbol(base+3);//q
    push_symbol(base+2);//x
    add();
    push_symbol(base+3);//q
    add();
    _clp_aadd(2);
    pop();
    line(536);
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
    line(545);
    line(546);
    line(547);
    line(548);
    line(550);
    binary("(");
    binary("\"");
    add();
    binary("'");
    add();
    assign(base+16);//smartchar
    pop();
    line(554);
    line(552);
    push_symbol(base+1);//match
    push(&NIL);
    eqeq();
    cmp_5092:;
    if(!flag()) goto if_53_1;
        line(553);
        push(&NIL);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_53_1:
    if_53_0:;
    line(556);
    push_symbol(base+0);//rlist
    _clp_len(1);
    assign(base+5);//lr
    pop();
    line(557);
    push_symbol(base+1);//match
    _clp_len(1);
    assign(base+6);//lm
    pop();
    line(558);
    push_symbol(base+5);//lr
    addnum(1);
    assign(base+7);//imin
    pop();
    line(559);
    push_symbol(base+5);//lr
    push_symbol(base+6);//lm
    add();
    assign(base+8);//imax
    pop();
    line(560);
    array(0);
    assign(base+12);//sep
    pop();
    line(561);
    push(&ZERO);
    assign(base+11);//par
    pop();
    line(563);
    push_symbol(base+0);//rlist
    push_symbol(base+8);//imax
    _clp_asize(2);
    pop();
    line(586);
    {
    line(565);
    push(&ONE);
    int sg=sign();
    push_symbol(base+7);//imin
    assign(base+10);//i
    lab_54_0:
    push_symbol(base+8);//imax
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_54_2;
        line(566);
        push_symbol(base+1);//match
        push_symbol(base+10);//i
        push_symbol(base+5);//lr
        sub();
        idxr();
        assign(base+9);//token
        pop();
        line(567);
        push_symbol(base+9);//token
        push_symbol(base+0);//rlist
        push_symbol(base+10);//i
        assign2(idxxl());
        pop();
        line(573);
        line(569);
        push_symbol(base+9);//token
        binary("([{");
        ss();
        if(!flag()) goto if_55_1;
            line(570);
            push_symbol(base+11);//par
            dup();
            push(&ONE);
            add();
            assign(base+11);//par
            pop();
            pop();
        goto if_55_0;
        if_55_1:
        line(571);
        push_symbol(base+9);//token
        binary(")]}");
        ss();
        if(!flag()) goto if_55_2;
            line(572);
            push_symbol(base+11);//par
            dup();
            push(&ONE);
            sub();
            assign(base+11);//par
            pop();
            pop();
        if_55_2:
        if_55_0:;
        line(577);
        line(575);
        push_symbol(base+9);//token
        binary(",");
        eqeq();
        cmp_5330:;
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+11);//par
        push(&ZERO);
        eqeq();
        cmp_5337:;
        }
        if(!flag()) goto if_56_1;
            line(576);
            push_symbol(base+12);//sep
            push_symbol(base+10);//i
            _clp_aadd(2);
            pop();
        if_56_1:
        if_56_0:;
        line(583);
        line(579);
        binary("\"");
        push_symbol(base+9);//token
        ss();
        if(!flag()){
        push(&FALSE);
        }else{
        binary("\"");
        push_symbol(base+3);//left
        eqeq();
        cmp_5389:;
        }
        if(!flag()) goto if_57_1;
            line(580);
            binary("'");
            assign(base+4);//right
            assign(base+3);//left
            pop();
        goto if_57_0;
        if_57_1:
        line(581);
        binary("'");
        push_symbol(base+9);//token
        ss();
        if(!flag()){
        push(&FALSE);
        }else{
        binary("'");
        push_symbol(base+3);//left
        eqeq();
        cmp_5427:;
        }
        if(!flag()) goto if_57_2;
            line(582);
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
    line(588);
    push_symbol(base+12);//sep
    _clp_len(1);
    assign(base+15);//ls
    pop();
    line(590);
    push_symbol(base+7);//imin
    assign(base+13);//il
    pop();
    line(591);
    push_symbol(base+15);//ls
    push(&ZERO);
    gt();
    cmp_5501:;
    if(flag()){
    push_symbol(base+12);//sep
    idxr0(1);
    addnum(-1);
    }else{
    push_symbol(base+8);//imax
    }
    assign(base+14);//ir
    pop();
    line(596);
    line(593);
    push_symbol(base+13);//il
    push_symbol(base+14);//ir
    lteq();
    cmp_5531:;
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
        line(594);
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
        line(595);
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
    line(615);
    line(598);
    push_symbol(base+15);//ls
    push(&ZERO);
    gt();
    cmp_5656:;
    if(!flag()) goto if_59_1;
        line(607);
        {
        line(600);
        push(&ONE);
        int sg=sign();
        number(2);
        assign(base+10);//i
        lab_60_0:
        push_symbol(base+15);//ls
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_60_2;
            line(601);
            push_symbol(base+12);//sep
            push_symbol(base+10);//i
            addnum(-1);
            idxr();
            addnum(1);
            assign(base+13);//il
            pop();
            line(602);
            push_symbol(base+12);//sep
            push_symbol(base+10);//i
            idxr();
            addnum(-1);
            assign(base+14);//ir
            pop();
            line(606);
            line(603);
            push_symbol(base+13);//il
            push_symbol(base+14);//ir
            lteq();
            cmp_5724:;
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
                line(604);
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
                line(605);
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
        line(609);
        push_symbol(base+12);//sep
        push_symbol(base+15);//ls
        idxr();
        addnum(1);
        assign(base+13);//il
        pop();
        line(610);
        push_symbol(base+8);//imax
        assign(base+14);//ir
        pop();
        line(614);
        line(611);
        push_symbol(base+13);//il
        push_symbol(base+14);//ir
        lteq();
        cmp_5883:;
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
            line(612);
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
            line(613);
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
    line(617);
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
    line(622);
    push_symbol(base+0);//rlist
    push_symbol(base+1);//match
    push(&NIL);
    eqeq();
    cmp_6055:;
    if(flag()){
    binary(".F.");
    }else{
    binary(".T.");
    }
    _clp_aadd(2);
    pop();
    line(623);
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
    line(628);
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
    line(631);
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
    line(634);
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
    line(639);
    push_symbol(base+0);//rule
    _clp_len(1);
    assign(base+3);//lr
    pop();
    line(645);
    lab_63_1:
    line(640);
    push_symbol(base+1);//n
    push(&ONE);
    add();
    assign(base+1);//n
    push_symbol(base+3);//lr
    lteq();
    cmp_6233:;
    if(!flag()) goto lab_63_2;
        line(641);
        push_symbol(base+0);//rule
        push_symbol(base+1);//n
        idxr();
        assign(base+2);//ntok
        pop();
        line(644);
        line(642);
        push_symbol(base+2);//ntok
        _clp_valtype(1);
        string(L"L");
        neeq();
        cmp_6270:;
        if(flag()){
        push(&TRUE);
        }else{
        push_symbol(base+2);//ntok
        }
        if(!flag()) goto if_64_1;
            line(643);
            goto lab_63_2;//exit
        if_64_1:
        if_64_0:;
    goto lab_63_1;
    lab_63_2:;
    line(646);
    push_symbol(base+2);//ntok
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

