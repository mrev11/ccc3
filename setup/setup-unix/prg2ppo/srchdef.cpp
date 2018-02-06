//input: srchdef.ppo (5.0.21)

#include <cccdef.h>

static void _blk_searchdefine_0(int argno);
extern void _clp_alltrim(int argno);
extern void _clp_ascan(int argno);
extern void _clp_len(int argno);
extern void _clp_rule_df_get(int argno);
extern void _clp_searchdefine(int argno);
extern void _clp_tokenize(int argno);

//=======================================================================
void _clp_searchdefine(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+10)PUSHNIL();
argno=1;
push_call("searchdefine",base);
//
    line(32);
    push(&NIL);
    assign(base+1);//result
    pop();
    line(33);
    push_symbol(base+0);//line
    _clp_alltrim(1);
    _clp_tokenize(1);
    assign(base+2);//toklist
    pop();
    line(34);
    push_symbol(base+2);//toklist
    _clp_len(1);
    assign(base+3);//lentok
    pop();
    line(35);
    push_symbol(base+3);//lentok
    push(&ONE);
    gteq();
    if(flag()){
    push_symbol(base+2);//toklist
    idxr0(1);
    }else{
    push(&NIL);
    }
    assign(base+4);//symbol
    pop();
    line(36);
    push_symbol(base+3);//lentok
    number(3);
    gteq();
    if(flag()){
    push_symbol(base+2);//toklist
    idxr0(3);
    }else{
    push(&NIL);
    }
    assign(base+5);//value
    pop();
    line(37);
    _clp_rule_df_get(0);
    assign(base+6);//rdef
    pop();
    line(45);
    line(39);
    push_symbol(base+4);//symbol
    push(&NIL);
    neeq();
    if(!flag()){
    push(&FALSE);
    }else{
    push(&ZERO);
    push_symbol(base+6);//rdef
    push_symbol_ref(base+4);//symbol
    block(_blk_searchdefine_0,1);
    _clp_ascan(2);
    assign(base+9);//n
    lt();
    }
    if(!flag()) goto if_1_1;
        line(42);
        push_symbol(base+6);//rdef
        push_symbol(base+9);//n
        idxr();
        idxr0(2);
        assign(base+7);//rside
        pop();
        line(43);
        push_symbol(base+7);//rside
        _clp_len(1);
        push(&ONE);
        gteq();
        if(flag()){
        push_symbol(base+7);//rside
        idxr0(1);
        }else{
        push(&NIL);
        }
        assign(base+8);//rvalue
        pop();
        line(44);
        push_symbol(base+8);//rvalue
        push_symbol(base+5);//value
        eqeq();
        assign(base+1);//result
        pop();
    if_1_1:
    if_1_0:;
    line(47);
    push_symbol(base+1);//result
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_searchdefine_0(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_searchdefine_0",base);
//
    push_blkarg(base+1);//r
    idxr0(1);
    idxr0(1);
    push_blkenv(env+0);//symbol
    eqeq();
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================

