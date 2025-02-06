//input: ppo/dbdefine.ppo (5.7.0.1)

#include <cccdef.h>

extern void _clp_aadd(int argno);
extern void _clp_alltrim(int argno);
extern void _clp_array(int argno);
extern void _clp_define(int argno);
extern void _clp_error(int argno);
extern void _clp_isalpha(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_markervalue(int argno);
extern void _clp_rule_df_add(int argno);
extern void _clp_tokenize(int argno);

//=======================================================================
void _clp_define(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+12)PUSHNIL();
argno=1;
push_call("define",base);
//
    line(26);
    push_symbol(base+0);//line
    _clp_alltrim(1);
    _clp_tokenize(1);
    assign(base+1);//toklist
    pop();
    line(27);
    push_symbol(base+1);//toklist
    _clp_len(1);
    assign(base+2);//lentok
    pop();
    line(28);
    line(29);
    line(30);
    push(&FALSE);
    assign(base+11);//strflag
    pop();
    line(108);
    line(32);
    push_symbol(base+2);//lentok
    push(&ONE);
    lt();
    cmp_125:;
    if(!flag()) goto if_1_1;
        line(33);
        string(nls_text(L"Invalid #define"));
        _clp_error(1);
        pop();
    goto if_1_0;
    if_1_1:
    line(35);
    push_symbol(base+2);//lentok
    push(&ONE);
    eqeq();
    cmp_155:;
    if(!flag()) goto if_1_2;
        line(36);
        push_symbol(base+1);//toklist
        idxr0(1);
        array(1);
        assign(base+5);//left
        pop();
        line(37);
        array(0);
        assign(base+6);//right
        pop();
    goto if_1_0;
    if_1_2:
    line(39);
    push_symbol(base+1);//toklist
    idxr0(2);
    binary("(");
    eqeq();
    cmp_208:;
    if(!flag()) goto if_1_3;
        line(42);
        push_symbol(base+1);//toklist
        idxr0(1);
        binary("(");
        array(2);
        assign(base+5);//left
        pop();
        line(52);
        {
        line(43);
        push(&ONE);
        int sg=sign();
        number(3);
        assign(base+3);//n
        lab_2_0:
        push_symbol(base+2);//lentok
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_2_2;
            line(51);
            line(44);
            push_symbol(base+1);//toklist
            push_symbol(base+3);//n
            idxr();
            binary(" ");
            eqeq();
            cmp_266:;
            if(!flag()) goto if_3_1;
            goto if_3_0;
            if_3_1:
            line(46);
            push_symbol(base+1);//toklist
            push_symbol(base+3);//n
            idxr();
            binary(")");
            eqeq();
            cmp_287:;
            if(!flag()) goto if_3_2;
                line(47);
                push_symbol(base+5);//left
                binary(")");
                _clp_aadd(2);
                pop();
                line(48);
                goto lab_2_2;//exit
            goto if_3_0;
            if_3_2:
            line(49);
                line(50);
                push_symbol(base+5);//left
                push_symbol(base+1);//toklist
                push_symbol(base+3);//n
                idxr();
                _clp_aadd(2);
                pop();
            if_3_3:
            if_3_0:;
        lab_2_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+3);//n
        add();
        assign(base+3);//n
        goto lab_2_0;
        lab_2_2:;
        }
        line(57);
        line(54);
        push_symbol(base+3);//n
        push_symbol(base+2);//lentok
        gt();
        cmp_371:;
        if(!flag()) goto if_4_1;
            line(56);
            string(nls_text(L"Invalid #define"));
            _clp_error(1);
            pop();
        if_4_1:
        if_4_0:;
        line(62);
        line(59);
        push_symbol(base+3);//n
        push_symbol(base+2);//lentok
        lt();
        cmp_408:;
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+1);//toklist
        push_symbol(base+3);//n
        addnum(1);
        idxr();
        binary(" ");
        eqeq();
        cmp_424:;
        }
        if(!flag()) goto if_5_1;
            line(61);
            push_symbol(base+3);//n
            dup();
            push(&ONE);
            add();
            assign(base+3);//n
            pop();
            pop();
        if_5_1:
        if_5_0:;
        line(66);
        push_symbol(base+2);//lentok
        push_symbol(base+3);//n
        sub();
        _clp_array(1);
        assign(base+6);//right
        pop();
        line(69);
        {
        line(67);
        push(&ONE);
        int sg=sign();
        push_symbol(base+3);//n
        addnum(1);
        assign(base+4);//i
        lab_6_0:
        push_symbol(base+2);//lentok
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_6_2;
            line(68);
            push_symbol(base+1);//toklist
            push_symbol(base+4);//i
            idxr();
            push_symbol(base+6);//right
            push_symbol(base+4);//i
            push_symbol(base+3);//n
            sub();
            assign2(idxxl());
            pop();
        lab_6_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+4);//i
        add();
        assign(base+4);//i
        goto lab_6_0;
        lab_6_2:;
        }
        line(71);
        push_symbol(base+5);//left
        _clp_len(1);
        assign(base+7);//ll
        pop();
        line(72);
        push_symbol(base+6);//right
        _clp_len(1);
        assign(base+8);//lr
        pop();
        line(92);
        {
        line(74);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+3);//n
        lab_7_0:
        push_symbol(base+8);//lr
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_7_2;
            line(75);
            push_symbol(base+6);//right
            push_symbol(base+3);//n
            idxr();
            assign(base+10);//token
            pop();
            line(76);
            push_symbol(base+10);//token
            push(&ONE);
            _clp_left(2);
            assign(base+9);//tt
            pop();
            line(90);
            line(78);
            push_symbol(base+9);//tt
            _clp_isalpha(1);
            if(flag()){
            push(&TRUE);
            }else{
            push_symbol(base+9);//tt
            binary("_");
            eqeq();
            cmp_622:;
            }
            if(!flag()) goto if_8_1;
                line(89);
                {
                line(79);
                number(2);
                int sg=sign();
                number(3);
                assign(base+4);//i
                lab_9_0:
                push_symbol(base+7);//ll
                if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_9_2;
                    line(88);
                    line(80);
                    push_symbol(base+10);//token
                    push_symbol(base+5);//left
                    push_symbol(base+4);//i
                    idxr();
                    eqeq();
                    cmp_652:;
                    if(!flag()) goto if_10_1;
                        line(86);
                        line(81);
                        push_symbol(base+11);//strflag
                        if(!flag()) goto if_11_1;
                            line(82);
                            binary(" ");
                            push_symbol(base+6);//right
                            push_symbol(base+3);//n
                            addnum(-1);
                            assign2(idxxl());
                            pop();
                            line(83);
                            number(3);
                            push_symbol(base+4);//i
                            _clp_markervalue(2);
                            push_symbol(base+6);//right
                            push_symbol(base+3);//n
                            assign2(idxxl());
                            pop();
                        goto if_11_0;
                        if_11_1:
                        line(84);
                            line(85);
                            push(&ONE);
                            push_symbol(base+4);//i
                            _clp_markervalue(2);
                            push_symbol(base+6);//right
                            push_symbol(base+3);//n
                            assign2(idxxl());
                            pop();
                        if_11_2:
                        if_11_0:;
                        line(87);
                        goto lab_9_2;//exit
                    if_10_1:
                    if_10_0:;
                lab_9_1:
                number(2);
                dup();
                sg=sign();
                push_symbol(base+4);//i
                add();
                assign(base+4);//i
                goto lab_9_0;
                lab_9_2:;
                }
            if_8_1:
            if_8_0:;
            line(91);
            push_symbol(base+10);//token
            binary("#");
            eqeq();
            cmp_802:;
            assign(base+11);//strflag
            pop();
        lab_7_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+3);//n
        add();
        assign(base+3);//n
        goto lab_7_0;
        lab_7_2:;
        }
        line(96);
        {
        line(94);
        number(2);
        int sg=sign();
        number(3);
        assign(base+3);//n
        lab_12_0:
        push_symbol(base+7);//ll
        addnum(-1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_12_2;
            line(95);
            push(&ONE);
            push(&ZERO);
            _clp_markervalue(2);
            push_symbol(base+5);//left
            push_symbol(base+3);//n
            assign2(idxxl());
            pop();
        lab_12_1:
        number(2);
        dup();
        sg=sign();
        push_symbol(base+3);//n
        add();
        assign(base+3);//n
        goto lab_12_0;
        lab_12_2:;
        }
    goto if_1_0;
    if_1_3:
    line(98);
        line(100);
        push_symbol(base+1);//toklist
        idxr0(1);
        array(1);
        assign(base+5);//left
        pop();
        line(102);
        push_symbol(base+1);//toklist
        idxr0(2);
        binary(" ");
        eqeq();
        cmp_909:;
        topnot();
        if(flag()){
        number(2);
        }else{
        number(3);
        }
        assign(base+3);//n
        pop();
        line(104);
        push_symbol(base+2);//lentok
        push_symbol(base+3);//n
        sub();
        addnum(1);
        _clp_array(1);
        assign(base+6);//right
        pop();
        line(107);
        {
        line(105);
        push(&ONE);
        int sg=sign();
        push_symbol(base+3);//n
        assign(base+4);//i
        lab_13_0:
        push_symbol(base+2);//lentok
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_13_2;
            line(106);
            push_symbol(base+1);//toklist
            push_symbol(base+4);//i
            idxr();
            push_symbol(base+6);//right
            push_symbol(base+4);//i
            push_symbol(base+3);//n
            sub();
            addnum(1);
            assign2(idxxl());
            pop();
        lab_13_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+4);//i
        add();
        assign(base+4);//i
        goto lab_13_0;
        lab_13_2:;
        }
    if_1_4:
    if_1_0:;
    line(110);
    push_symbol(base+5);//left
    push_symbol(base+6);//right
    push(&NIL);
    array(3);
    _clp_rule_df_add(1);
    pop();
    line(111);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

