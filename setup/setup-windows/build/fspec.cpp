//input: fspec.ppo (5.3.0)

#include <cccdef.h>

extern void _clp_alltrim(int argno);
extern void _clp_fext(int argno);
extern void _clp_fext0(int argno);
extern void _clp_fname(int argno);
extern void _clp_fnameext(int argno);
extern void _clp_fpath(int argno);
extern void _clp_fpath0(int argno);
static void _clp_lastslash(int argno);
extern void _clp_left(int argno);
extern void _clp_max(int argno);
extern void _clp_rat(int argno);
extern void _clp_substr(int argno);

//=======================================================================
static void _clp_lastslash(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("lastslash",base);
//
    line(24);
    string(L"/");
    push_symbol(base+0);//name
    _clp_rat(2);
    string(L"\\");
    push_symbol(base+0);//name
    _clp_rat(2);
    _clp_max(2);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_fnameext(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("fnameext",base);
//
    line(29);
    push_symbol(base+0);//name
    _clp_lastslash(1);
    assign(base+1);//slpos
    pop();
    line(30);
    push_symbol(base+0);//name
    push_symbol(base+1);//slpos
    addnum(1);
    _clp_substr(2);
    assign(base+0);//name
    pop();
    line(31);
    push_symbol(base+0);//name
    _clp_alltrim(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_fname(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("fname",base);
//
    line(36);
    string(L".");
    push_symbol(base+0);//name
    _clp_rat(2);
    assign(base+1);//extpos
    pop();
    line(37);
    push_symbol(base+0);//name
    _clp_lastslash(1);
    assign(base+2);//slpos
    pop();
    line(42);
    line(38);
    push_symbol(base+1);//extpos
    push_symbol(base+2);//slpos
    gt();
    if(!flag()) goto if_1_1;
        line(39);
        push_symbol(base+0);//name
        push_symbol(base+2);//slpos
        addnum(1);
        push_symbol(base+1);//extpos
        push_symbol(base+2);//slpos
        sub();
        addnum(-1);
        _clp_substr(3);
        assign(base+0);//name
        pop();
    goto if_1_0;
    if_1_1:
    line(40);
        line(41);
        push_symbol(base+0);//name
        push_symbol(base+2);//slpos
        addnum(1);
        _clp_substr(2);
        assign(base+0);//name
        pop();
    if_1_2:
    if_1_0:;
    line(43);
    push_symbol(base+0);//name
    _clp_alltrim(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_fpath0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("fpath0",base);
//
    line(48);
    push_symbol(base+0);//name
    _clp_lastslash(1);
    assign(base+1);//slpos
    pop();
    line(51);
    line(49);
    push(&ZERO);
    push_symbol(base+1);//slpos
    lt();
    if(!flag()) goto if_2_1;
        line(50);
        push_symbol(base+0);//name
        push_symbol(base+1);//slpos
        addnum(-1);
        _clp_left(2);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_2_1:
    if_2_0:;
    line(52);
    string(L"");
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_fpath(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("fpath",base);
//
    line(57);
    push_symbol(base+0);//name
    _clp_lastslash(1);
    assign(base+1);//slpos
    pop();
    line(60);
    line(58);
    push(&ZERO);
    push_symbol(base+1);//slpos
    lt();
    if(!flag()) goto if_3_1;
        line(59);
        push_symbol(base+0);//name
        push_symbol(base+1);//slpos
        _clp_left(2);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_3_1:
    if_3_0:;
    line(61);
    string(L"");
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_fext(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("fext",base);
//
    line(66);
    string(L".");
    push_symbol(base+0);//name
    _clp_rat(2);
    assign(base+1);//extpos
    pop();
    line(67);
    push_symbol(base+0);//name
    _clp_lastslash(1);
    assign(base+2);//slpos
    pop();
    line(70);
    line(68);
    push_symbol(base+1);//extpos
    push_symbol(base+2);//slpos
    gt();
    if(!flag()) goto if_4_1;
        line(69);
        push_symbol(base+0);//name
        push_symbol(base+1);//extpos
        _clp_substr(2);
        _clp_alltrim(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_4_1:
    if_4_0:;
    line(71);
    string(L".");
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_fext0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("fext0",base);
//
    line(76);
    push_symbol(base+0);//name
    _clp_fext(1);
    number(2);
    _clp_substr(2);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

