//input: ppo/filespec.ppo (5.7.0.1)

#include <cccdef.h>

extern void _clp_empty(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_max(int argno);
extern void _clp_rat(int argno);
extern void _clp_substr(int argno);

namespace _nsp_filespec{
extern void _clp_absolute(int argno);
extern void _clp_basename(int argno);
extern void _clp_drive(int argno);
extern void _clp_extension(int argno);
static void _clp_lastsep(int argno);
extern void _clp_name(int argno);
extern void _clp_nameext(int argno);
extern void _clp_path(int argno);
extern void _clp_relative(int argno);
}//namespace filespec

namespace _nsp_filespec{
//=======================================================================
static void _clp_lastsep(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("filespec.lastsep",base);
//
    line(18);
    push(&ZERO);
    assign(base+1);//sep
    pop();
    line(19);
    push_symbol(base+1);//sep
    string(L"/");
    push_symbol(base+0);//fspec
    _clp_rat(2);
    _clp_max(2);
    assign(base+1);//sep
    pop();
    line(20);
    push_symbol(base+1);//sep
    string(L"\\");
    push_symbol(base+0);//fspec
    _clp_rat(2);
    _clp_max(2);
    assign(base+1);//sep
    pop();
    line(24);
    push_symbol(base+1);//sep
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_basename(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("filespec.basename",base);
//
    line(29);
    line(30);
    push_symbol(base+0);//fspec
    push_symbol(base+0);//fspec
    _clp_lastsep(1);
    addnum(1);
    _clp_substr(2);
    assign(base+2);//bn
    pop();
    line(36);
    line(31);
    push_symbol(base+1);//ext
    push(&NIL);
    neeq();
    cmp_187:;
    if(!flag()) goto if_1_1;
        line(32);
        push_symbol(base+1);//ext
        push_symbol(base+2);//bn
        _clp_rat(2);
        assign(base+3);//xp
        pop();
        line(35);
        line(33);
        push_symbol(base+3);//xp
        push_symbol(base+1);//ext
        _clp_len(1);
        add();
        addnum(-1);
        push_symbol(base+2);//bn
        _clp_len(1);
        eqeq();
        cmp_242:;
        if(!flag()) goto if_2_1;
            line(34);
            push_symbol(base+2);//bn
            push_symbol(base+3);//xp
            addnum(-1);
            _clp_left(2);
            assign(base+2);//bn
            pop();
        if_2_1:
        if_2_0:;
    if_1_1:
    if_1_0:;
    line(37);
    push_symbol(base+2);//bn
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_path(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("filespec.path",base);
//
    line(42);
    push_symbol(base+0);//fspec
    push(&ONE);
    push_symbol(base+0);//fspec
    _clp_lastsep(1);
    _clp_substr(3);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_nameext(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("filespec.nameext",base);
//
    line(47);
    push_symbol(base+0);//fspec
    push_symbol(base+0);//fspec
    _clp_lastsep(1);
    addnum(1);
    _clp_substr(2);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_name(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("filespec.name",base);
//
    line(52);
    push_symbol(base+0);//fspec
    _clp_lastsep(1);
    assign(base+1);//sep
    pop();
    line(53);
    string(L".");
    push_symbol(base+0);//fspec
    _clp_rat(2);
    assign(base+2);//dot
    pop();
    line(54);
    push_symbol(base+0);//fspec
    push_symbol(base+1);//sep
    addnum(1);
    push_symbol(base+2);//dot
    push_symbol(base+1);//sep
    gt();
    cmp_490:;
    if(flag()){
    push_symbol(base+2);//dot
    push_symbol(base+1);//sep
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
void _clp_extension(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("filespec.extension",base);
//
    line(59);
    push_symbol(base+0);//fspec
    _clp_lastsep(1);
    assign(base+1);//sep
    pop();
    line(60);
    string(L".");
    push_symbol(base+0);//fspec
    _clp_rat(2);
    assign(base+2);//dot
    pop();
    line(61);
    push_symbol(base+2);//dot
    push_symbol(base+1);//sep
    gt();
    cmp_587:;
    if(flag()){
    push_symbol(base+0);//fspec
    push_symbol(base+2);//dot
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
void _clp_absolute(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("filespec.absolute",base);
//
    line(74);
    line(66);
    push_symbol(base+0);//fspec
    _clp_empty(1);
    if(!flag()) goto if_3_1;
        line(67);
        push(&FALSE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_3_0;
    if_3_1:
    line(68);
    push_symbol(base+0);//fspec
    idxr0(1);
    string(L"/\\");
    ss();
    if(!flag()) goto if_3_2;
        line(69);
        push(&TRUE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_3_2:
    if_3_0:;
    line(75);
    push(&FALSE);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_relative(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("filespec.relative",base);
//
    line(80);
    push_symbol(base+0);//fspec
    _clp_absolute(1);
    topnot();
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_drive(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("filespec.drive",base);
//
    line(90);
    string(L"");
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

}//namespace filespec
