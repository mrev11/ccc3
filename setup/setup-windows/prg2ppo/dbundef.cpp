//input: dbundef.ppo (5.4.0)

#include <cccdef.h>

extern void _clp_alltrim(int argno);
extern void _clp_len(int argno);
extern void _clp_rule_df_del(int argno);
extern void _clp_tokenize(int argno);
extern void _clp_undef(int argno);

//=======================================================================
void _clp_undef(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("undef",base);
//
    line(23);
    push_symbol(base+0);//line
    _clp_alltrim(1);
    _clp_tokenize(1);
    assign(base+1);//toklist
    pop();
    line(24);
    push_symbol(base+1);//toklist
    _clp_len(1);
    push(&ZERO);
    gt();
    if(flag()){
    push_symbol(base+1);//toklist
    idxr0(1);
    }else{
    push(&NIL);
    }
    assign(base+2);//symbol
    pop();
    line(25);
    push_symbol(base+2);//symbol
    _clp_rule_df_del(1);
    pop();
    line(26);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

