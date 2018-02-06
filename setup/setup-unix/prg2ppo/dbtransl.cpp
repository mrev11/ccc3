//input: dbtransl.ppo (5.0.21)

#include <cccdef.h>

extern void _clp_aadd(int argno);
extern void _clp_alltrim(int argno);
extern void _clp_error(int argno);
extern void _clp_len(int argno);
extern void _clp_qout(int argno);
extern void _clp_rule_if_add(int argno);
extern void _clp_rule_tr_add(int argno);
extern void _clp_token_translate(int argno);
extern void _clp_translate(int argno);
extern void _clp_valtype(int argno);

//=======================================================================
void _clp_translate(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+9)PUSHNIL();
argno=2;
push_call("translate",base);
//
    line(24);
    push_symbol(base+0);//line
    _clp_alltrim(1);
    _clp_token_translate(1);
    assign(base+2);//rule
    pop();
    line(25);
    push_symbol(base+2);//rule
    idxr0(1);
    assign(base+3);//ls
    pop();
    push_symbol(base+2);//rule
    idxr0(2);
    assign(base+4);//rs
    pop();
    line(26);
    line(53);
    {
    line(34);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+5);//n
    lab_1_0:
    push_symbol(base+4);//rs
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(52);
        line(36);
        push_symbol(base+4);//rs
        push_symbol(base+5);//n
        idxr();
        _clp_valtype(1);
        string(L"A");
        eqeq();
        if(!flag()) goto if_2_1;
            line(38);
            push_symbol(base+4);//rs
            push_symbol(base+5);//n
            idxr();
            idxr0(1);
            assign(base+7);//name
            pop();
            line(45);
            {
            line(40);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+6);//i
            lab_3_0:
            push_symbol(base+3);//ls
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_3_2;
                line(44);
                line(41);
                push_symbol(base+3);//ls
                push_symbol(base+6);//i
                idxr();
                _clp_valtype(1);
                string(L"A");
                eqeq();
                if(!flag()){
                push(&FALSE);
                }else{
                push_symbol(base+3);//ls
                push_symbol(base+6);//i
                idxr();
                idxr0(1);
                push_symbol(base+7);//name
                eqeq();
                }
                if(!flag()) goto if_4_1;
                    line(42);
                    push_symbol(base+4);//rs
                    push_symbol(base+5);//n
                    idxr();
                    idxr0(2);
                    push_symbol(base+6);//i
                    add();
                    push_symbol(base+4);//rs
                    push_symbol(base+5);//n
                    assign2(idxxl());
                    pop();
                    line(43);
                    goto lab_3_2;//exit
                if_4_1:
                if_4_0:;
            lab_3_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+6);//i
            add();
            assign(base+6);//i
            goto lab_3_0;
            lab_3_2:;
            }
            line(51);
            line(47);
            push_symbol(base+6);//i
            push_symbol(base+3);//ls
            _clp_len(1);
            gt();
            if(!flag()) goto if_5_1;
                line(48);
                string(L"left :");
                push_symbol(base+2);//rule
                idxr0(1);
                _clp_qout(2);
                pop();
                line(49);
                string(L"right:");
                push_symbol(base+2);//rule
                idxr0(2);
                _clp_qout(2);
                pop();
                line(50);
                binary("Result marker not defined [");
                push_symbol(base+7);//name
                add();
                binary("]");
                add();
                _clp_error(1);
                pop();
            if_5_1:
            if_5_0:;
        if_2_1:
        if_2_0:;
    lab_1_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+5);//n
    add();
    assign(base+5);//n
    goto lab_1_0;
    lab_1_2:;
    }
    line(64);
    {
    line(55);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+5);//n
    lab_6_0:
    push_symbol(base+3);//ls
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_6_2;
        line(63);
        line(56);
        push_symbol(base+3);//ls
        push_symbol(base+5);//n
        idxr();
        _clp_valtype(1);
        string(L"A");
        eqeq();
        if(!flag()) goto if_7_1;
            line(62);
            line(57);
            push_symbol(base+3);//ls
            push_symbol(base+5);//n
            idxr();
            _clp_len(1);
            number(2);
            gt();
            if(!flag()) goto if_8_1;
                line(58);
                push_symbol(base+3);//ls
                push_symbol(base+5);//n
                idxr();
                idxr0(3);
                _clp_rule_if_add(1);
                assign(base+8);//info
                pop();
                line(59);
                push_symbol(base+3);//ls
                push_symbol(base+5);//n
                idxr();
                idxr0(2);
                push_symbol(base+8);//info
                add();
                push_symbol(base+3);//ls
                push_symbol(base+5);//n
                assign2(idxxl());
                pop();
            goto if_8_0;
            if_8_1:
            line(60);
                line(61);
                push_symbol(base+3);//ls
                push_symbol(base+5);//n
                idxr();
                idxr0(2);
                push_symbol(base+3);//ls
                push_symbol(base+5);//n
                assign2(idxxl());
                pop();
            if_8_2:
            if_8_0:;
        if_7_1:
        if_7_0:;
    lab_6_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+5);//n
    add();
    assign(base+5);//n
    goto lab_6_0;
    lab_6_2:;
    }
    line(66);
    push_symbol(base+2);//rule
    _clp_rule_tr_add(1);
    pop();
    line(70);
    line(68);
    push_symbol(base+1);//cmdflg
    if(!flag()) goto if_9_1;
        line(69);
        push_symbol(base+2);//rule
        idxr0(1);
        push(&NIL);
        _clp_aadd(2);
        pop();
    if_9_1:
    if_9_0:;
    line(76);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

