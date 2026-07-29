//input: ppo/direxist.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_bin2str(int argno);
extern void _clp_direxist(int argno);
extern void _clp_fileexist(int argno);
extern void _clp_fileisexecutable(int argno);
extern void _clp_right(int argno);
extern void _clp_s_isdir(int argno);
extern void _clp_stat_st_mode(int argno);
extern void _clp_upper(int argno);

//=======================================================================
void _clp_direxist(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("direxist",base);
//
    line(24);
    line(25);
    push_symbol(base+0);//dirspec
    _clp_stat_st_mode(1);
    assign(base+1);//mode
    pop();
    line(26);
    push_symbol(base+1);//mode
    push(&NIL);
    neeq();
    cmp_53:;
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+1);//mode
    _clp_s_isdir(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_fileexist(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("fileexist",base);
//
    line(34);
    push_symbol(base+0);//fspec
    _clp_stat_st_mode(1);
    assign(base+1);//mode
    pop();
    line(35);
    push_symbol(base+1);//mode
    push(&NIL);
    neeq();
    cmp_112:;
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+1);//mode
    _clp_s_isdir(1);
    topnot();
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_fileisexecutable(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("fileisexecutable",base);
//
    line(42);
    push_symbol(base+0);//fspec
    _clp_fileexist(1);
    if(!flag()){
    push(&FALSE);
    }else{
    string(L".");
    push_symbol(base+0);//fspec
    number(3);
    _clp_right(2);
    _clp_upper(1);
    add();
    string(L".");
    add();
    _clp_bin2str(1);
    string(L".EXE.BAT.COM.");
    ss();
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

