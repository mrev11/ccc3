//input: outline.ppo (5.6.0)

#include <cccdef.h>

extern void _clp_alltrim(int argno);
extern void _clp_len(int argno);
extern void _clp_outline(int argno);

//=======================================================================
void _clp_outline(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+4)PUSHNIL();
argno=1;
push_call("outline",base);
//
    line(24);
    binary("");
    assign(base+1);//result
    pop();
    line(34);
    {
    line(26);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_1_0:
    push_symbol(base+0);//toklist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(31);
        line(28);
        push(&NIL);
        push_symbol(base+0);//toklist
        push_symbol(base+3);//n
        idxr();
        assign(base+2);//token
        eqeq();
        if(!flag()) goto if_2_1;
            line(30);
            goto lab_1_2;//exit
        if_2_1:
        if_2_0:;
        line(33);
        push_symbol(base+1);//result
        push_symbol(base+2);//token
        add();
        assign(base+1);//result
        pop();
    lab_1_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_1_0;
    lab_1_2:;
    }
    line(36);
    push_symbol(base+1);//result
    _clp_alltrim(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

