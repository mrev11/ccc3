//input: split.ppo (5.3.0)

#include <cccdef.h>

extern void _clp_aadd(int argno);
extern void _clp_at(int argno);
extern void _clp_len(int argno);
extern void _clp_split(int argno);
extern void _clp_valtype(int argno);

//=======================================================================
void _clp_split(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+5)PUSHNIL();
argno=2;
push_call("split",base);
//
    if( ((base+0)->type==TYPE_NIL)||
       (((base+0)->type==TYPE_REF)&&
        ((base+0)->data.vref->value.type==TYPE_NIL))){
    line(22);
    string(L"");
    assign(base+0);//txt
    pop();
    }
    if( ((base+1)->type==TYPE_NIL)||
       (((base+1)->type==TYPE_REF)&&
        ((base+1)->data.vref->value.type==TYPE_NIL))){
    line(22);
    push_symbol(base+0);//txt
    _clp_valtype(1);
    string(L"X");
    eqeq();
    if(flag()){
    binary(",");
    }else{
    string(L",");
    }
    assign(base+1);//sep
    pop();
    }
    line(23);
    array(0);
    assign(base+2);//wlist
    pop();
    push(&ONE);
    assign(base+3);//n
    pop();
    line(28);
    lab_1_1:
    line(25);
    push(&ZERO);
    push_symbol(base+1);//sep
    push_symbol(base+0);//txt
    push_symbol(base+3);//n
    _clp_at(3);
    assign(base+4);//i
    lt();
    if(!flag()) goto lab_1_2;
        line(26);
        push_symbol(base+2);//wlist
        push_symbol(base+0);//txt
        push_symbol(base+3);//n
        push_symbol(base+4);//i
        addnum(-1);
        slice();
        _clp_aadd(2);
        pop();
        line(27);
        push_symbol(base+4);//i
        addnum(1);
        assign(base+3);//n
        pop();
    goto lab_1_1;
    lab_1_2:;
    line(35);
    line(33);
    push_symbol(base+0);//txt
    _clp_len(1);
    push_symbol(base+3);//n
    gteq();
    if(!flag()) goto if_2_1;
        line(34);
        push_symbol(base+2);//wlist
        push_symbol(base+0);//txt
        push_symbol(base+3);//n
        push(&NIL);
        slice();
        _clp_aadd(2);
        pop();
    if_2_1:
    if_2_0:;
    line(36);
    push_symbol(base+2);//wlist
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

