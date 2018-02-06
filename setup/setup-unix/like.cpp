//input: like.ppo (5.0.21)

#include <cccdef.h>

extern void _clp_len(int argno);
extern void _clp_like(int argno);
extern void _clp_substr(int argno);
extern void _clp_valtype(int argno);

//=======================================================================
void _clp_like(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+8)PUSHNIL();
argno=2;
push_call("like",base);
//
    line(24);
    line(25);
    push_symbol(base+1);//str
    _clp_valtype(1);
    assign(base+5);//type
    pop();
    line(26);
    push_symbol(base+5);//type
    string(L"X");
    eqeq();
    if(flag()){
    binary("?");
    }else{
    string(L"?");
    }
    assign(base+6);//qm
    pop();
    line(27);
    push_symbol(base+5);//type
    string(L"X");
    eqeq();
    if(flag()){
    binary("*");
    }else{
    string(L"*");
    }
    assign(base+7);//st
    pop();
    line(55);
    {
    line(29);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//i
    lab_1_0:
    push_symbol(base+1);//str
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(54);
        line(31);
        push_symbol(base+0);//minta
        push_symbol(base+2);//i
        push(&ONE);
        _clp_substr(3);
        push_symbol(base+6);//qm
        eqeq();
        if(!flag()) goto if_2_1;
        goto if_2_0;
        if_2_1:
        line(34);
        push_symbol(base+0);//minta
        push_symbol(base+2);//i
        push(&ONE);
        _clp_substr(3);
        push_symbol(base+7);//st
        eqeq();
        if(!flag()) goto if_2_2;
            line(36);
            push_symbol(base+0);//minta
            push_symbol(base+2);//i
            addnum(1);
            _clp_substr(2);
            assign(base+4);//w
            pop();
            line(40);
            line(38);
            push_symbol(base+4);//w
            _clp_len(1);
            push(&ZERO);
            eqeq();
            if(!flag()) goto if_3_1;
                line(39);
                push(&TRUE);
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            if_3_1:
            if_3_0:;
            line(46);
            {
            line(42);
            push(&ONE);
            int sg=sign();
            push_symbol(base+2);//i
            assign(base+3);//j
            lab_4_0:
            push_symbol(base+1);//str
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
                line(45);
                line(43);
                push_symbol(base+4);//w
                push_symbol(base+1);//str
                push_symbol(base+3);//j
                _clp_substr(2);
                _clp_like(2);
                if(!flag()) goto if_5_1;
                    line(44);
                    push(&TRUE);
                    {*base=*(stack-1);stack=base+1;pop_call();return;}
                if_5_1:
                if_5_0:;
            lab_4_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+3);//j
            add();
            assign(base+3);//j
            goto lab_4_0;
            lab_4_2:;
            }
            line(47);
            push(&FALSE);
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        goto if_2_0;
        if_2_2:
        line(49);
        push_symbol(base+0);//minta
        push_symbol(base+2);//i
        push(&ONE);
        _clp_substr(3);
        push_symbol(base+1);//str
        push_symbol(base+2);//i
        push(&ONE);
        _clp_substr(3);
        eqeq();
        if(!flag()) goto if_2_3;
        goto if_2_0;
        if_2_3:
        line(52);
            line(53);
            push(&FALSE);
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_2_4:
        if_2_0:;
    lab_1_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//i
    add();
    assign(base+2);//i
    goto lab_1_0;
    lab_1_2:;
    }
    line(61);
    line(57);
    push_symbol(base+1);//str
    _clp_len(1);
    push_symbol(base+0);//minta
    _clp_len(1);
    gt();
    if(!flag()) goto if_6_1;
        line(58);
        push(&FALSE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_6_0;
    if_6_1:
    line(59);
    push_symbol(base+1);//str
    _clp_len(1);
    push_symbol(base+0);//minta
    _clp_len(1);
    eqeq();
    if(!flag()) goto if_6_2;
        line(60);
        push(&TRUE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_6_2:
    if_6_0:;
    line(70);
    {
    line(66);
    push(&ONE);
    int sg=sign();
    push_symbol(base+1);//str
    _clp_len(1);
    addnum(1);
    assign(base+2);//i
    lab_7_0:
    push_symbol(base+0);//minta
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_7_2;
        line(69);
        line(67);
        push_symbol(base+0);//minta
        push_symbol(base+2);//i
        push(&ONE);
        _clp_substr(3);
        push_symbol(base+7);//st
        eqeq();
        topnot();
        if(!flag()) goto if_8_1;
            line(68);
            push(&FALSE);
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_8_1:
        if_8_0:;
    lab_7_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//i
    add();
    assign(base+2);//i
    goto lab_7_0;
    lab_7_2:;
    }
    line(72);
    push(&TRUE);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

