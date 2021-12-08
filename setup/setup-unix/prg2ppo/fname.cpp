//input: fname.ppo (5.4.0)

#include <cccdef.h>

extern void _clp_fbase(int argno);
extern void _clp_fext(int argno);
extern void _clp_fname(int argno);
extern void _clp_fpath(int argno);
extern void _clp_left(int argno);
extern void _clp_max(int argno);
extern void _clp_rat(int argno);
extern void _clp_substr(int argno);

//=======================================================================
void _clp_fpath(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("fpath",base);
//
    line(23);
    string(L"\\");
    push_symbol(base+0);//fspec
    _clp_rat(2);
    assign(base+1);//spos
    pop();
    line(24);
    string(L":");
    push_symbol(base+0);//fspec
    _clp_rat(2);
    assign(base+2);//cpos
    pop();
    line(25);
    push_symbol(base+0);//fspec
    push_symbol(base+1);//spos
    push_symbol(base+2);//cpos
    _clp_max(2);
    _clp_left(2);
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
    string(L"\\");
    push_symbol(base+0);//fspec
    _clp_rat(2);
    assign(base+1);//spos
    pop();
    line(31);
    string(L":");
    push_symbol(base+0);//fspec
    _clp_rat(2);
    assign(base+2);//cpos
    pop();
    line(32);
    push_symbol(base+0);//fspec
    push_symbol(base+1);//spos
    push_symbol(base+2);//cpos
    _clp_max(2);
    addnum(1);
    _clp_substr(2);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_fbase(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+4)PUSHNIL();
argno=1;
push_call("fbase",base);
//
    line(37);
    string(L"\\");
    push_symbol(base+0);//fspec
    _clp_rat(2);
    assign(base+1);//spos
    pop();
    line(38);
    string(L":");
    push_symbol(base+0);//fspec
    _clp_rat(2);
    assign(base+2);//cpos
    pop();
    line(39);
    string(L".");
    push_symbol(base+0);//fspec
    _clp_rat(2);
    assign(base+3);//ppos
    pop();
    line(40);
    push_symbol(base+1);//spos
    push_symbol(base+2);//cpos
    _clp_max(2);
    assign(base+1);//spos
    pop();
    line(41);
    push_symbol(base+0);//fspec
    push_symbol(base+1);//spos
    addnum(1);
    push_symbol(base+3);//ppos
    push_symbol(base+1);//spos
    gt();
    if(flag()){
    push_symbol(base+3);//ppos
    push_symbol(base+1);//spos
    sub();
    addnum(-1);
    }else{
    push(&NIL);
    }
    _clp_substr(3);
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
    line(46);
    string(L"\\");
    push_symbol(base+0);//fspec
    _clp_rat(2);
    assign(base+1);//spos
    pop();
    line(47);
    string(L".");
    push_symbol(base+0);//fspec
    _clp_rat(2);
    assign(base+2);//ppos
    pop();
    line(48);
    push_symbol(base+2);//ppos
    push_symbol(base+1);//spos
    gt();
    if(flag()){
    push_symbol(base+0);//fspec
    push_symbol(base+2);//ppos
    _clp_substr(2);
    }else{
    string(L"");
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

