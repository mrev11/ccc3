//input: globvar.ppo (5.6.0)

#include <cccdef.h>

extern void _clp_omitted_hash(int argno);
extern void _clp_resource_hash(int argno);
extern void _clp_s_batext(int argno);
extern void _clp_s_debug(int argno);
extern void _clp_s_dry(int argno);
extern void _clp_s_incdir(int argno);
extern void _clp_s_libdir(int argno);
extern void _clp_s_libfil(int argno);
extern void _clp_s_libnam(int argno);
extern void _clp_s_libspec(int argno);
extern void _clp_s_main(int argno);
extern void _clp_s_primary(int argno);
extern void _clp_s_quiet(int argno);
extern void _clp_s_resource(int argno);
extern void _clp_s_rules(int argno);
extern void _clp_s_shared(int argno);
extern void _clp_s_srcdir(int argno);
extern void _clp_s_version(int argno);
extern void _clp_simplehashnew(int argno);

//=======================================================================
void _clp_s_main(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_main",base);
//
    line(77);
    static stvar _st_xx;
    line(78);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_main
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_main
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_libnam(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_libnam",base);
//
    line(82);
    static stvar _st_xx;
    line(83);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_libnam
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_libnam
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_shared(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_shared",base);
//
    line(87);
    static stvar _st_xx;
    line(88);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_shared
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_shared
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_srcdir(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_srcdir",base);
//
    line(92);
    static stvar _st_xx;
    line(93);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_srcdir
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_srcdir
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_incdir(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_incdir",base);
//
    line(97);
    static stvar _st_xx;
    line(98);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_incdir
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_incdir
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_libdir(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_libdir",base);
//
    line(102);
    static stvar _st_xx;
    line(103);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_libdir
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_libdir
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_libfil(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_libfil",base);
//
    line(107);
    static stvar _st_xx;
    line(108);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_libfil
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_libfil
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_quiet(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_quiet",base);
//
    line(112);
    static stvar _st_xx(&FALSE);
    line(113);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_quiet
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_quiet
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_version(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_version",base);
//
    line(117);
    static stvar _st_xx(&FALSE);
    line(118);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_version
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_version
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_debug(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_debug",base);
//
    line(122);
    static stvar _st_xx(&FALSE);
    line(123);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_debug
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_debug
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_dry(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_dry",base);
//
    line(127);
    static stvar _st_xx(&FALSE);
    line(128);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_dry
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_dry
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_primary(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_primary",base);
//
    line(132);
    static stvar _st_xx;
    line(133);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_primary
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_primary
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_resource(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_resource",base);
//
    line(137);
    static stvar _st_xx;
    line(138);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_resource
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_resource
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_libspec(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_libspec",base);
//
    line(142);
    static stvar _st_xx;
    line(143);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_libspec
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_libspec
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_rules(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_rules",base);
//
    line(147);
    static stvar _st_xx;
    static int _ini_xx=[=](){
        string(L".msk");
        string(L".dlg");
        array(2);
        string(L".msk");
        string(L".pnl");
        array(2);
        string(L".mnt");
        string(L".gpi");
        array(2);
        string(L".cls");
        string(L".och");
        array(2);
        string(L".msk");
        string(L".say");
        array(2);
        string(L".htm");
        string(L".ctm");
        array(2);
        string(L".msk");
        string(L".wro");
        array(2);
        string(L".pge");
        string(L".out");
        array(2);
        string(L".pge");
        string(L".wro");
        array(2);
        string(L".tdc");
        string(L".ch");
        array(2);
        string(L".asm");
        string(L".obj");
        array(2);
        string(L".c");
        string(L".obj");
        array(2);
        string(L".cpp");
        string(L".obj");
        array(2);
        string(L".tds");
        string(L".obj");
        array(2);
        string(L".prg");
        string(L".obj");
        array(2);
        string(L".y");
        string(L".obj");
        array(2);
        string(L".lem");
        string(L".obj");
        array(2);
        string(L".lex");
        string(L".obj");
        array(2);
        string(L".tdc");
        string(L".obj");
        array(2);
        string(L".obj");
        string(L".lib");
        array(2);
        string(L".obj");
        string(L".exe");
        array(2);
        array(21);
        assign(_st_xx.ptr);
        pop();
        return 1;
    }();
    line(170);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_rules
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_rules
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_batext(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("s_batext",base);
//
    line(174);
    static stvar _st_xx;
    line(175);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//s_batext
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_batext
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_resource_hash(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("resource_hash",base);
//
    line(179);
    static stvar _st_xx;
    static int _ini_xx=[=](){
        _clp_simplehashnew(0);
        assign(_st_xx.ptr);
        pop();
        return 1;
    }();
    line(180);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//resource_hash
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//resource_hash
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_omitted_hash(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("omitted_hash",base);
//
    line(184);
    static stvar _st_xx;
    static int _ini_xx=[=](){
        _clp_simplehashnew(0);
        assign(_st_xx.ptr);
        pop();
        return 1;
    }();
    line(185);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    if(flag()){
    push_symbol(_st_xx.ptr);//omitted_hash
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//omitted_hash
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

