//input: split.ppo (5.0.17)

#include <cccdef.h>

extern void _clp_aadd(int argno);
extern void _clp_at(int argno);
extern void _clp_len(int argno);
extern void _clp_split(int argno);
extern void _clp_substr(int argno);
extern void _clp_valtype(int argno);

//=======================================================================
void _clp_split(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+6)PUSHNIL();
argno=2;
push_call("split",base);
//
    line(24);
    array(0);
    assign(base+2);//wlist
    pop();
    push(&ZERO);
    assign(base+3);//n
    pop();
    line(25);
    push_symbol(base+0);//txt
    _clp_valtype(1);
    string(L"X");
    eqeq();
    if(flag()){
    binaryx("");
    }else{
    string(L"");
    }
    assign(base+5);//emp
    pop();
    line(29);
    line(27);
    push_symbol(base+1);//sep
    push(&NIL);
    eqeq();
    if(!flag()) goto if_1_1;
        line(28);
        string(L",");
        assign(base+1);//sep
        pop();
    if_1_1:
    if_1_0:;
    line(45);
    lab_2_1:
    line(31);
    push_symbol(base+3);//n
    push_symbol(base+0);//txt
    _clp_len(1);
    lt();
    if(!flag()) goto lab_2_2;
        line(33);
        push_symbol(base+0);//txt
        push_symbol(base+3);//n
        addnum(1);
        _clp_substr(2);
        assign(base+0);//txt
        pop();
        line(44);
        line(35);
        push_symbol(base+1);//sep
        push_symbol(base+0);//txt
        _clp_at(2);
        assign(base+4);//i
        push(&ZERO);
        eqeq();
        if(!flag()) goto if_3_1;
            line(36);
            push_symbol(base+2);//wlist
            push_symbol(base+0);//txt
            _clp_aadd(2);
            pop();
            line(37);
            push_symbol(base+0);//txt
            _clp_len(1);
            assign(base+3);//n
            pop();
        goto if_3_0;
        if_3_1:
        line(38);
        push_symbol(base+4);//i
        push(&ONE);
        eqeq();
        if(!flag()) goto if_3_2;
            line(39);
            push_symbol(base+2);//wlist
            push_symbol(base+5);//emp
            _clp_aadd(2);
            pop();
            line(40);
            push(&ONE);
            assign(base+3);//n
            pop();
        goto if_3_0;
        if_3_2:
        line(41);
            line(42);
            push_symbol(base+2);//wlist
            push_symbol(base+0);//txt
            push(&ONE);
            push_symbol(base+4);//i
            addnum(-1);
            _clp_substr(3);
            _clp_aadd(2);
            pop();
            line(43);
            push_symbol(base+4);//i
            assign(base+3);//n
            pop();
        if_3_3:
        if_3_0:;
    goto lab_2_1;
    lab_2_2:;
    line(47);
    push_symbol(base+2);//wlist
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

