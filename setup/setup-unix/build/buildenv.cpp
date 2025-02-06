//input: ppo/buildenv.ppo (5.7.0.1)

#include <cccdef.h>

extern void _clp_buildenv_bat(int argno);
extern void _clp_buildenv_bindir(int argno);
extern void _clp_buildenv_dbg(int argno);
extern void _clp_buildenv_exe(int argno);
extern void _clp_buildenv_inc(int argno);
extern void _clp_buildenv_lib(int argno);
extern void _clp_buildenv_libdir(int argno);
extern void _clp_buildenv_lpt(int argno);
extern void _clp_buildenv_obj(int argno);
extern void _clp_buildenv_shr(int argno);
extern void _clp_buildenv_src(int argno);
extern void _clp_buildenv_thr(int argno);
extern void _clp_getenv(int argno);
extern void _clp_list_buildenv(int argno);
extern void _clp_putenv(int argno);
extern void _clp_qout(int argno);

//=======================================================================
void _clp_buildenv_bat(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("buildenv_bat",base);
//
    line(25);
    string(L"BUILD_BAT");
    assign(base+1);//env
    pop();
    line(26);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_40:;
    if(flag()){
    push_symbol(base+1);//env
    _clp_getenv(1);
    }else{
    push_symbol(base+1);//env
    string(L"=");
    add();
    push_symbol(base+0);//x
    add();
    _clp_putenv(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_buildenv_bindir(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("buildenv_bindir",base);
//
    line(31);
    string(L"BUILD_BINDIR");
    assign(base+1);//env
    pop();
    line(32);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_113:;
    if(flag()){
    push_symbol(base+1);//env
    _clp_getenv(1);
    }else{
    push_symbol(base+1);//env
    string(L"=");
    add();
    push_symbol(base+0);//x
    add();
    _clp_putenv(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_buildenv_dbg(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("buildenv_dbg",base);
//
    line(37);
    string(L"BUILD_DBG");
    assign(base+1);//env
    pop();
    line(38);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_186:;
    if(flag()){
    push_symbol(base+1);//env
    _clp_getenv(1);
    }else{
    push_symbol(base+1);//env
    string(L"=");
    add();
    push_symbol(base+0);//x
    add();
    _clp_putenv(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_buildenv_exe(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("buildenv_exe",base);
//
    line(43);
    string(L"BUILD_EXE");
    assign(base+1);//env
    pop();
    line(44);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_259:;
    if(flag()){
    push_symbol(base+1);//env
    _clp_getenv(1);
    }else{
    push_symbol(base+1);//env
    string(L"=");
    add();
    push_symbol(base+0);//x
    add();
    _clp_putenv(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_buildenv_inc(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("buildenv_inc",base);
//
    line(49);
    string(L"BUILD_INC");
    assign(base+1);//env
    pop();
    line(50);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_332:;
    if(flag()){
    push_symbol(base+1);//env
    _clp_getenv(1);
    }else{
    push_symbol(base+1);//env
    string(L"=");
    add();
    push_symbol(base+0);//x
    add();
    _clp_putenv(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_buildenv_lib(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("buildenv_lib",base);
//
    line(55);
    string(L"BUILD_LIB");
    assign(base+1);//env
    pop();
    line(56);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_405:;
    if(flag()){
    push_symbol(base+1);//env
    _clp_getenv(1);
    }else{
    push_symbol(base+1);//env
    string(L"=");
    add();
    push_symbol(base+0);//x
    add();
    _clp_putenv(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_buildenv_libdir(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("buildenv_libdir",base);
//
    line(61);
    string(L"BUILD_LIBDIR");
    assign(base+1);//env
    pop();
    line(62);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_478:;
    if(flag()){
    push_symbol(base+1);//env
    _clp_getenv(1);
    }else{
    push_symbol(base+1);//env
    string(L"=");
    add();
    push_symbol(base+0);//x
    add();
    _clp_putenv(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_buildenv_lpt(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("buildenv_lpt",base);
//
    line(67);
    string(L"BUILD_LPT");
    assign(base+1);//env
    pop();
    line(68);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_551:;
    if(flag()){
    push_symbol(base+1);//env
    _clp_getenv(1);
    }else{
    push_symbol(base+1);//env
    string(L"=");
    add();
    push_symbol(base+0);//x
    add();
    _clp_putenv(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_buildenv_obj(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("buildenv_obj",base);
//
    line(73);
    string(L"BUILD_OBJ");
    assign(base+1);//env
    pop();
    line(74);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_624:;
    if(flag()){
    push_symbol(base+1);//env
    _clp_getenv(1);
    }else{
    push_symbol(base+1);//env
    string(L"=");
    add();
    push_symbol(base+0);//x
    add();
    _clp_putenv(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_buildenv_shr(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("buildenv_shr",base);
//
    line(79);
    string(L"BUILD_SHR");
    assign(base+1);//env
    pop();
    line(80);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_697:;
    if(flag()){
    push_symbol(base+1);//env
    _clp_getenv(1);
    }else{
    push_symbol(base+1);//env
    string(L"=");
    add();
    push_symbol(base+0);//x
    add();
    _clp_putenv(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_buildenv_src(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("buildenv_src",base);
//
    line(85);
    string(L"BUILD_SRC");
    assign(base+1);//env
    pop();
    line(86);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_770:;
    if(flag()){
    push_symbol(base+1);//env
    _clp_getenv(1);
    }else{
    push_symbol(base+1);//env
    string(L"=");
    add();
    push_symbol(base+0);//x
    add();
    _clp_putenv(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_buildenv_thr(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("buildenv_thr",base);
//
    line(91);
    string(L"BUILD_THR");
    assign(base+1);//env
    pop();
    line(92);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_843:;
    if(flag()){
    push_symbol(base+1);//env
    _clp_getenv(1);
    }else{
    push_symbol(base+1);//env
    string(L"=");
    add();
    push_symbol(base+0);//x
    add();
    _clp_putenv(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_list_buildenv(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("list_buildenv",base);
//
    line(98);
    string(L"BUILD_BAT    =");
    _clp_buildenv_bat(0);
    _clp_qout(2);
    pop();
    line(99);
    string(L"BUILD_BINDIR =");
    _clp_buildenv_bindir(0);
    _clp_qout(2);
    pop();
    line(100);
    string(L"BUILD_DBG    =");
    _clp_buildenv_dbg(0);
    _clp_qout(2);
    pop();
    line(101);
    string(L"BUILD_EXE    =");
    _clp_buildenv_exe(0);
    _clp_qout(2);
    pop();
    line(102);
    string(L"BUILD_INC    =");
    _clp_buildenv_inc(0);
    _clp_qout(2);
    pop();
    line(103);
    string(L"BUILD_LIB    =");
    _clp_buildenv_lib(0);
    _clp_qout(2);
    pop();
    line(104);
    string(L"BUILD_LIBDIR =");
    _clp_buildenv_libdir(0);
    _clp_qout(2);
    pop();
    line(105);
    string(L"BUILD_LPT    =");
    _clp_buildenv_lpt(0);
    _clp_qout(2);
    pop();
    line(106);
    string(L"BUILD_OBJ    =");
    _clp_buildenv_obj(0);
    _clp_qout(2);
    pop();
    line(107);
    string(L"BUILD_SHR    =");
    _clp_buildenv_shr(0);
    _clp_qout(2);
    pop();
    line(108);
    string(L"BUILD_SRC    =");
    _clp_buildenv_src(0);
    _clp_qout(2);
    pop();
    line(109);
    string(L"BUILD_THR    =");
    _clp_buildenv_thr(0);
    _clp_qout(2);
    pop();
    line(110);
    _clp_qout(0);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

