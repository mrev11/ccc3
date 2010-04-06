//input: arr2bin.ppo (5.0.17)

#include <cccdef.h>

extern void _clp_aadd(int argno);
extern void _clp_alltrim(int argno);
extern void _clp_any2str(int argno);
extern void _clp_arr2bin(int argno);
extern void _clp_arr2str(int argno);
extern void _clp_bin2arr(int argno);
extern void _clp_bin2str(int argno);
extern void _clp_dtoc(int argno);
extern void _clp_dtos(int argno);
extern void _clp_l2hex(int argno);
extern void _clp_len(int argno);
extern void _clp_stod(int argno);
extern void _clp_str(int argno);
extern void _clp_str2bin(int argno);
extern void _clp_substr(int argno);
extern void _clp_val(int argno);
extern void _clp_valtype(int argno);

//=======================================================================
void _clp_arr2bin(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+7)PUSHNIL();
argno=1;
push_call("arr2bin",base);
//
    line(25);
    binary("");
    assign(base+1);//bvar
    pop();
    line(26);
    line(27);
    line(65);
    {
    line(29);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_1_0:
    push_symbol(base+0);//avar
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(30);
        push_symbol(base+0);//avar
        push_symbol(base+2);//n
        idxr();
        assign(base+3);//v
        pop();
        line(64);
        line(32);
        push_symbol(base+3);//v
        _clp_valtype(1);
        assign(base+5);//type
        string(L"U");
        eqeq();
        if(!flag()) goto if_2_1;
            line(33);
            push_symbol(base+1);//bvar
            binary("U");
            add();
            assign(base+1);//bvar
            pop();
        goto if_2_0;
        if_2_1:
        line(35);
        push_symbol(base+5);//type
        string(L"X");
        eqeq();
        if(!flag()) goto if_2_2;
            line(36);
            push_symbol(base+3);//v
            _clp_len(1);
            assign(base+4);//lv
            pop();
            line(37);
            push_symbol(base+1);//bvar
            binary("X");
            push_symbol(base+4);//lv
            number(6);
            push(&ZERO);
            _clp_str(3);
            _clp_str2bin(1);
            add();
            push_symbol(base+3);//v
            add();
            add();
            assign(base+1);//bvar
            pop();
        goto if_2_0;
        if_2_2:
        line(39);
        push_symbol(base+5);//type
        string(L"C");
        eqeq();
        if(!flag()) goto if_2_3;
            line(40);
            push_symbol(base+3);//v
            _clp_str2bin(1);
            assign(base+3);//v
            pop();
            line(41);
            push_symbol(base+3);//v
            _clp_len(1);
            assign(base+4);//lv
            pop();
            line(46);
            line(42);
            push_symbol(base+4);//lv
            number(100);
            lt();
            if(!flag()) goto if_3_1;
                line(43);
                push_symbol(base+1);//bvar
                binary("C");
                push_symbol(base+4);//lv
                number(2);
                push(&ZERO);
                _clp_str(3);
                _clp_str2bin(1);
                add();
                push_symbol(base+3);//v
                add();
                add();
                assign(base+1);//bvar
                pop();
            goto if_3_0;
            if_3_1:
            line(44);
                line(45);
                push_symbol(base+1);//bvar
                binary("S");
                push_symbol(base+4);//lv
                number(5);
                push(&ZERO);
                _clp_str(3);
                _clp_str2bin(1);
                add();
                push_symbol(base+3);//v
                add();
                add();
                assign(base+1);//bvar
                pop();
            if_3_2:
            if_3_0:;
        goto if_2_0;
        if_2_3:
        line(48);
        push_symbol(base+5);//type
        string(L"N");
        eqeq();
        if(!flag()) goto if_2_4;
            line(49);
            push_symbol(base+3);//v
            _clp_str(1);
            _clp_alltrim(1);
            _clp_str2bin(1);
            assign(base+3);//v
            pop();
            line(50);
            push_symbol(base+1);//bvar
            binary("N");
            push_symbol(base+3);//v
            _clp_len(1);
            number(2);
            push(&ZERO);
            _clp_str(3);
            _clp_str2bin(1);
            add();
            push_symbol(base+3);//v
            add();
            add();
            assign(base+1);//bvar
            pop();
        goto if_2_0;
        if_2_4:
        line(52);
        push_symbol(base+5);//type
        string(L"D");
        eqeq();
        if(!flag()) goto if_2_5;
            line(53);
            push_symbol(base+1);//bvar
            binary("D");
            push_symbol(base+3);//v
            _clp_dtos(1);
            _clp_str2bin(1);
            add();
            add();
            assign(base+1);//bvar
            pop();
        goto if_2_0;
        if_2_5:
        line(55);
        push_symbol(base+5);//type
        string(L"L");
        eqeq();
        if(!flag()) goto if_2_6;
            line(56);
            push_symbol(base+1);//bvar
            binary("L");
            push_symbol(base+3);//v
            if(flag()){
            binary("T");
            }else{
            binary("F");
            }
            add();
            add();
            assign(base+1);//bvar
            pop();
        goto if_2_0;
        if_2_6:
        line(58);
        push_symbol(base+5);//type
        string(L"A");
        eqeq();
        if(!flag()) goto if_2_7;
            line(59);
            push_symbol(base+3);//v
            _clp_arr2bin(1);
            assign(base+3);//v
            pop();
            line(60);
            push_symbol(base+1);//bvar
            binary("A");
            push_symbol(base+3);//v
            _clp_len(1);
            number(5);
            push(&ZERO);
            _clp_str(3);
            _clp_str2bin(1);
            add();
            push_symbol(base+3);//v
            add();
            add();
            assign(base+1);//bvar
            pop();
        goto if_2_0;
        if_2_7:
        line(62);
            line(63);
            push_symbol(base+1);//bvar
            binary("U");
            add();
            assign(base+1);//bvar
            pop();
        if_2_8:
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
    line(67);
    push_symbol(base+1);//bvar
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_bin2arr(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+6)PUSHNIL();
argno=1;
push_call("bin2arr",base);
//
    line(72);
    array(0);
    assign(base+1);//avar
    pop();
    line(73);
    push(&ONE);
    assign(base+2);//c
    pop();
    line(114);
    lab_4_1:
    line(75);
    push_symbol(base+2);//c
    push_symbol(base+0);//bvar
    _clp_len(1);
    lteq();
    if(!flag()) goto lab_4_2;
        line(76);
        push_symbol(base+0);//bvar
        push_symbol(base+2);//c
        push(&ONE);
        _clp_substr(3);
        assign(base+3);//type
        pop();
        push_symbol(base+2);//c
        push(&ONE);
        add();
        assign(base+2);//c
        pop();
        line(113);
        line(78);
        push_symbol(base+3);//type
        binary("U");
        eqeq();
        if(!flag()) goto if_5_1;
            line(79);
            push_symbol(base+1);//avar
            push(&NIL);
            _clp_aadd(2);
            pop();
        goto if_5_0;
        if_5_1:
        line(81);
        push_symbol(base+3);//type
        binary("X");
        eqeq();
        if(!flag()) goto if_5_2;
            line(82);
            push_symbol(base+0);//bvar
            push_symbol(base+2);//c
            number(6);
            _clp_substr(3);
            _clp_val(1);
            assign(base+5);//lv
            pop();
            push_symbol(base+2);//c
            number(6);
            add();
            assign(base+2);//c
            pop();
            line(83);
            push_symbol(base+0);//bvar
            push_symbol(base+2);//c
            push_symbol(base+5);//lv
            _clp_substr(3);
            assign(base+4);//v
            pop();
            push_symbol(base+2);//c
            push_symbol(base+5);//lv
            add();
            assign(base+2);//c
            pop();
            line(84);
            push_symbol(base+1);//avar
            push_symbol(base+4);//v
            _clp_aadd(2);
            pop();
        goto if_5_0;
        if_5_2:
        line(86);
        push_symbol(base+3);//type
        binary("C");
        eqeq();
        if(!flag()) goto if_5_3;
            line(87);
            push_symbol(base+0);//bvar
            push_symbol(base+2);//c
            number(2);
            _clp_substr(3);
            _clp_val(1);
            assign(base+5);//lv
            pop();
            push_symbol(base+2);//c
            number(2);
            add();
            assign(base+2);//c
            pop();
            line(88);
            push_symbol(base+0);//bvar
            push_symbol(base+2);//c
            push_symbol(base+5);//lv
            _clp_substr(3);
            assign(base+4);//v
            pop();
            push_symbol(base+2);//c
            push_symbol(base+5);//lv
            add();
            assign(base+2);//c
            pop();
            line(89);
            push_symbol(base+1);//avar
            push_symbol(base+4);//v
            _clp_bin2str(1);
            _clp_aadd(2);
            pop();
        goto if_5_0;
        if_5_3:
        line(91);
        push_symbol(base+3);//type
        binary("S");
        eqeq();
        if(!flag()) goto if_5_4;
            line(92);
            push_symbol(base+0);//bvar
            push_symbol(base+2);//c
            number(5);
            _clp_substr(3);
            _clp_val(1);
            assign(base+5);//lv
            pop();
            push_symbol(base+2);//c
            number(5);
            add();
            assign(base+2);//c
            pop();
            line(93);
            push_symbol(base+0);//bvar
            push_symbol(base+2);//c
            push_symbol(base+5);//lv
            _clp_substr(3);
            assign(base+4);//v
            pop();
            push_symbol(base+2);//c
            push_symbol(base+5);//lv
            add();
            assign(base+2);//c
            pop();
            line(94);
            push_symbol(base+1);//avar
            push_symbol(base+4);//v
            _clp_bin2str(1);
            _clp_aadd(2);
            pop();
        goto if_5_0;
        if_5_4:
        line(96);
        push_symbol(base+3);//type
        binary("N");
        eqeq();
        if(!flag()) goto if_5_5;
            line(97);
            push_symbol(base+0);//bvar
            push_symbol(base+2);//c
            number(2);
            _clp_substr(3);
            _clp_val(1);
            assign(base+5);//lv
            pop();
            push_symbol(base+2);//c
            number(2);
            add();
            assign(base+2);//c
            pop();
            line(98);
            push_symbol(base+0);//bvar
            push_symbol(base+2);//c
            push_symbol(base+5);//lv
            _clp_substr(3);
            assign(base+4);//v
            pop();
            push_symbol(base+2);//c
            push_symbol(base+5);//lv
            add();
            assign(base+2);//c
            pop();
            line(99);
            push_symbol(base+1);//avar
            push_symbol(base+4);//v
            _clp_val(1);
            _clp_aadd(2);
            pop();
        goto if_5_0;
        if_5_5:
        line(101);
        push_symbol(base+3);//type
        binary("D");
        eqeq();
        if(!flag()) goto if_5_6;
            line(102);
            push_symbol(base+0);//bvar
            push_symbol(base+2);//c
            number(8);
            _clp_substr(3);
            assign(base+4);//v
            pop();
            push_symbol(base+2);//c
            number(8);
            add();
            assign(base+2);//c
            pop();
            line(103);
            push_symbol(base+1);//avar
            push_symbol(base+4);//v
            _clp_stod(1);
            _clp_aadd(2);
            pop();
        goto if_5_0;
        if_5_6:
        line(105);
        push_symbol(base+3);//type
        binary("L");
        eqeq();
        if(!flag()) goto if_5_7;
            line(106);
            push_symbol(base+0);//bvar
            push_symbol(base+2);//c
            push(&ONE);
            _clp_substr(3);
            assign(base+4);//v
            pop();
            push_symbol(base+2);//c
            push(&ONE);
            add();
            assign(base+2);//c
            pop();
            line(107);
            push_symbol(base+1);//avar
            push_symbol(base+4);//v
            binary("T");
            eqeq();
            _clp_aadd(2);
            pop();
        goto if_5_0;
        if_5_7:
        line(109);
        push_symbol(base+3);//type
        binary("A");
        eqeq();
        if(!flag()) goto if_5_8;
            line(110);
            push_symbol(base+0);//bvar
            push_symbol(base+2);//c
            number(5);
            _clp_substr(3);
            _clp_val(1);
            assign(base+5);//lv
            pop();
            push_symbol(base+2);//c
            number(5);
            add();
            assign(base+2);//c
            pop();
            line(111);
            push_symbol(base+0);//bvar
            push_symbol(base+2);//c
            push_symbol(base+5);//lv
            _clp_substr(3);
            assign(base+4);//v
            pop();
            push_symbol(base+2);//c
            push_symbol(base+5);//lv
            add();
            assign(base+2);//c
            pop();
            line(112);
            push_symbol(base+1);//avar
            push_symbol(base+4);//v
            _clp_bin2arr(1);
            _clp_aadd(2);
            pop();
        if_5_8:
        if_5_0:;
    goto lab_4_1;
    lab_4_2:;
    line(115);
    push_symbol(base+1);//avar
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_arr2str(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+5)PUSHNIL();
argno=1;
push_call("arr2str",base);
//
    line(121);
    string(L"{");
    assign(base+1);//cvar
    pop();
    line(156);
    {
    line(123);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_6_0:
    push_symbol(base+0);//avar
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_6_2;
        line(126);
        line(124);
        push_symbol(base+2);//n
        push(&ONE);
        gt();
        if(!flag()) goto if_7_1;
            line(125);
            push_symbol(base+1);//cvar
            string(L",");
            add();
            assign(base+1);//cvar
            pop();
        if_7_1:
        if_7_0:;
        line(128);
        push_symbol(base+0);//avar
        push_symbol(base+2);//n
        idxr();
        assign(base+3);//v
        pop();
        line(129);
        push_symbol(base+3);//v
        _clp_valtype(1);
        assign(base+4);//type
        pop();
        line(155);
        line(131);
        push_symbol(base+4);//type
        string(L"U");
        eqeq();
        if(!flag()) goto if_8_1;
            line(132);
            push_symbol(base+1);//cvar
            string(L"NIL");
            add();
            assign(base+1);//cvar
            pop();
        goto if_8_0;
        if_8_1:
        line(134);
        push_symbol(base+4);//type
        string(L"X");
        eqeq();
        if(!flag()) goto if_8_2;
            line(135);
            push_symbol(base+1);//cvar
            string(L"a\"");
            push_symbol(base+3);//v
            _clp_bin2str(1);
            add();
            string(L"\"");
            add();
            add();
            assign(base+1);//cvar
            pop();
        goto if_8_0;
        if_8_2:
        line(137);
        push_symbol(base+4);//type
        string(L"C");
        eqeq();
        if(!flag()) goto if_8_3;
            line(138);
            push_symbol(base+1);//cvar
            string(L"\"");
            push_symbol(base+3);//v
            add();
            string(L"\"");
            add();
            add();
            assign(base+1);//cvar
            pop();
        goto if_8_0;
        if_8_3:
        line(140);
        push_symbol(base+4);//type
        string(L"N");
        eqeq();
        if(!flag()) goto if_8_4;
            line(141);
            push_symbol(base+1);//cvar
            push_symbol(base+3);//v
            _clp_str(1);
            _clp_alltrim(1);
            add();
            assign(base+1);//cvar
            pop();
        goto if_8_0;
        if_8_4:
        line(143);
        push_symbol(base+4);//type
        string(L"D");
        eqeq();
        if(!flag()) goto if_8_5;
            line(144);
            push_symbol(base+1);//cvar
            push_symbol(base+3);//v
            _clp_dtoc(1);
            add();
            assign(base+1);//cvar
            pop();
        goto if_8_0;
        if_8_5:
        line(146);
        push_symbol(base+4);//type
        string(L"L");
        eqeq();
        if(!flag()) goto if_8_6;
            line(147);
            push_symbol(base+1);//cvar
            push_symbol(base+3);//v
            if(flag()){
            string(L".T.");
            }else{
            string(L".F.");
            }
            add();
            assign(base+1);//cvar
            pop();
        goto if_8_0;
        if_8_6:
        line(149);
        push_symbol(base+4);//type
        string(L"A");
        eqeq();
        if(!flag()) goto if_8_7;
            line(150);
            push_symbol(base+1);//cvar
            push_symbol(base+3);//v
            _clp_arr2str(1);
            add();
            assign(base+1);//cvar
            pop();
        goto if_8_0;
        if_8_7:
        line(152);
            line(153);
            push_symbol(base+1);//cvar
            string(L"[Type-");
            push_symbol(base+4);//type
            add();
            string(L"]");
            add();
            add();
            assign(base+1);//cvar
            pop();
        if_8_8:
        if_8_0:;
    lab_6_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_6_0;
    lab_6_2:;
    }
    line(158);
    push_symbol(base+1);//cvar
    string(L"}");
    add();
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_any2str(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("any2str",base);
//
    line(163);
    push_symbol(base+0);//value
    _clp_valtype(1);
    assign(base+1);//type
    pop();
    line(190);
    line(165);
    push_symbol(base+1);//type
    string(L"C");
    eqeq();
    if(!flag()) goto if_9_1;
    goto if_9_0;
    if_9_1:
    line(167);
    push_symbol(base+1);//type
    string(L"X");
    eqeq();
    if(!flag()) goto if_9_2;
        line(168);
        push_symbol(base+0);//value
        _clp_bin2str(1);
        assign(base+0);//value
        pop();
    goto if_9_0;
    if_9_2:
    line(170);
    push_symbol(base+1);//type
    string(L"N");
    eqeq();
    if(!flag()) goto if_9_3;
        line(171);
        push_symbol(base+0);//value
        _clp_str(1);
        assign(base+0);//value
        pop();
    goto if_9_0;
    if_9_3:
    line(173);
    push_symbol(base+1);//type
    string(L"D");
    eqeq();
    if(!flag()) goto if_9_4;
        line(174);
        push_symbol(base+0);//value
        _clp_dtoc(1);
        assign(base+0);//value
        pop();
    goto if_9_0;
    if_9_4:
    line(176);
    push_symbol(base+1);//type
    string(L"L");
    eqeq();
    if(!flag()) goto if_9_5;
        line(177);
        push_symbol(base+0);//value
        if(flag()){
        string(L".T.");
        }else{
        string(L".F.");
        }
        assign(base+0);//value
        pop();
    goto if_9_0;
    if_9_5:
    line(179);
    push_symbol(base+1);//type
    string(L"A");
    eqeq();
    if(!flag()) goto if_9_6;
        line(180);
        push_symbol(base+0);//value
        _clp_arr2str(1);
        assign(base+0);//value
        pop();
    goto if_9_0;
    if_9_6:
    line(182);
    push_symbol(base+1);//type
    string(L"P");
    eqeq();
    if(!flag()) goto if_9_7;
        line(183);
        push_symbol(base+0);//value
        _clp_l2hex(1);
        assign(base+0);//value
        pop();
    goto if_9_0;
    if_9_7:
    line(185);
    push_symbol(base+1);//type
    string(L"U");
    eqeq();
    if(!flag()) goto if_9_8;
        line(186);
        string(L"NIL");
        assign(base+0);//value
        pop();
    goto if_9_0;
    if_9_8:
    line(188);
        line(189);
        string(L"Type-");
        push_symbol(base+1);//type
        add();
        assign(base+0);//value
        pop();
    if_9_9:
    if_9_0:;
    line(192);
    push_symbol(base+0);//value
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

