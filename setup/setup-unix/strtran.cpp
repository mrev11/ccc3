//input: strtran.ppo (5.3.0)

#include <cccdef.h>

extern void _clp_at(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_strtran(int argno);
extern void _clp_stuff(int argno);

//=======================================================================
void _clp_strtran(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,5);
while(stack<base+11)PUSHNIL();
argno=5;
push_call("_clp_strtran",base);
//
    line(30);
    push_symbol(base+1);//s1
    _clp_len(1);
    assign(base+5);//l1
    pop();
    line(31);
    push(&ONE);
    assign(base+7);//p1
    pop();
    line(32);
    push(&ZERO);
    assign(base+9);//no
    pop();
    line(33);
    push(&ZERO);
    assign(base+10);//chg
    pop();
    line(37);
    line(35);
    push_symbol(base+2);//s2
    push(&NIL);
    eqeq();
    if(!flag()) goto if_1_1;
        line(36);
        push_symbol(base+1);//s1
        push(&ZERO);
        _clp_left(2);
        assign(base+2);//s2
        pop();
    if_1_1:
    if_1_0:;
    line(38);
    push_symbol(base+2);//s2
    _clp_len(1);
    assign(base+6);//l2
    pop();
    line(48);
    lab_2_1:
    line(40);
    push_symbol(base+4);//cnt
    push(&NIL);
    eqeq();
    if(flag()){
    push(&TRUE);
    }else{
    push_symbol(base+10);//chg
    push_symbol(base+4);//cnt
    lt();
    }
    if(!flag()){
    push(&FALSE);
    }else{
    push(&ZERO);
    push_symbol(base+1);//s1
    push_symbol(base+0);//s
    push_symbol(base+7);//p1
    _clp_at(3);
    assign(base+8);//p
    lt();
    }
    if(!flag()) goto lab_2_2;
        line(47);
        line(41);
        push_symbol(base+3);//sta
        push(&NIL);
        neeq();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+9);//no
        push(&ONE);
        add();
        assign(base+9);//no
        push_symbol(base+3);//sta
        lt();
        }
        if(!flag()) goto if_3_1;
            line(42);
            push_symbol(base+8);//p
            addnum(1);
            assign(base+7);//p1
            pop();
        goto if_3_0;
        if_3_1:
        line(43);
            line(44);
            push_symbol(base+0);//s
            push_symbol(base+8);//p
            push_symbol(base+5);//l1
            push_symbol(base+2);//s2
            _clp_stuff(4);
            assign(base+0);//s
            pop();
            line(45);
            push_symbol(base+8);//p
            push_symbol(base+6);//l2
            add();
            assign(base+7);//p1
            pop();
            line(46);
            push_symbol(base+10);//chg
            dup();
            push(&ONE);
            add();
            assign(base+10);//chg
            pop();
            pop();
        if_3_2:
        if_3_0:;
    goto lab_2_1;
    lab_2_2:;
    line(49);
    push_symbol(base+0);//s
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

