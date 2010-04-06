//input: fspec.ppo (5.0.17)

#include <cccdef.h>

extern void _clp_alltrim(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_fext(int argno);
extern void _clp_fext0(int argno);
extern void _clp_fname(int argno);
extern void _clp_fnameext(int argno);
extern void _clp_fpath(int argno);
extern void _clp_fpath0(int argno);
extern void _clp_left(int argno);
extern void _clp_rat(int argno);
extern void _clp_substr(int argno);

//=======================================================================
void _clp_fnameext(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("fnameext",base);
//
    line(23);
    _clp_dirsep(0);
    push_symbol(base+0);//name
    _clp_rat(2);
    assign(base+1);//bslpos
    pop();
    line(24);
    push_symbol(base+0);//name
    push_symbol(base+1);//bslpos
    addnum(1);
    _clp_substr(2);
    assign(base+0);//name
    pop();
    line(25);
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
    line(30);
    string(L".");
    push_symbol(base+0);//name
    _clp_rat(2);
    assign(base+1);//extpos
    pop();
    line(31);
    _clp_dirsep(0);
    push_symbol(base+0);//name
    _clp_rat(2);
    assign(base+2);//bslpos
    pop();
    line(36);
    line(32);
    push_symbol(base+1);//extpos
    push_symbol(base+2);//bslpos
    gt();
    if(!flag()) goto if_1_1;
        line(33);
        push_symbol(base+0);//name
        push_symbol(base+2);//bslpos
        addnum(1);
        push_symbol(base+1);//extpos
        push_symbol(base+2);//bslpos
        sub();
        addnum(-1);
        _clp_substr(3);
        assign(base+0);//name
        pop();
    goto if_1_0;
    if_1_1:
    line(34);
        line(35);
        push_symbol(base+0);//name
        push_symbol(base+2);//bslpos
        addnum(1);
        _clp_substr(2);
        assign(base+0);//name
        pop();
    if_1_2:
    if_1_0:;
    line(37);
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
    line(42);
    _clp_dirsep(0);
    push_symbol(base+0);//name
    _clp_rat(2);
    assign(base+1);//bslpos
    pop();
    line(45);
    line(43);
    push(&ZERO);
    push_symbol(base+1);//bslpos
    lt();
    if(!flag()) goto if_2_1;
        line(44);
        push_symbol(base+0);//name
        push_symbol(base+1);//bslpos
        addnum(-1);
        _clp_left(2);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_2_1:
    if_2_0:;
    line(46);
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
    line(51);
    _clp_dirsep(0);
    push_symbol(base+0);//name
    _clp_rat(2);
    assign(base+1);//bslpos
    pop();
    line(54);
    line(52);
    push(&ZERO);
    push_symbol(base+1);//bslpos
    lt();
    if(!flag()) goto if_3_1;
        line(53);
        push_symbol(base+0);//name
        push_symbol(base+1);//bslpos
        _clp_left(2);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_3_1:
    if_3_0:;
    line(55);
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
    line(59);
    string(L".");
    push_symbol(base+0);//name
    _clp_rat(2);
    assign(base+1);//extpos
    pop();
    line(60);
    _clp_dirsep(0);
    push_symbol(base+0);//name
    _clp_rat(2);
    assign(base+2);//bslpos
    pop();
    line(63);
    line(61);
    push_symbol(base+1);//extpos
    push_symbol(base+2);//bslpos
    gt();
    if(!flag()) goto if_4_1;
        line(62);
        push_symbol(base+0);//name
        push_symbol(base+1);//extpos
        _clp_substr(2);
        _clp_alltrim(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_4_1:
    if_4_0:;
    line(64);
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
    line(69);
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

