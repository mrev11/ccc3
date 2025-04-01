//input: ppo/globvar.ppo (5.7.0.1)

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
extern void _clp_s_runcnt(int argno);
extern void _clp_s_shared(int argno);
extern void _clp_s_srcdir(int argno);
extern void _clp_s_version(int argno);
extern void _clp_simplehashnew(int argno);
extern void _clp_thread_mutex_init(int argno);
extern void _clp_thread_mutex_lock(int argno);
extern void _clp_thread_mutex_unlock(int argno);

//=======================================================================
void _clp_s_main(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_main",base);
//
    line(25);
    static stvar _st_xx;
    line(26);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(27);
    line(28);
    push_symbol(_st_mutex.ptr);//s_main
    _clp_thread_mutex_lock(1);
    pop();
    line(29);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_78:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_main
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_main
    }
    assign(base+1);//result
    pop();
    line(30);
    push_symbol(_st_mutex.ptr);//s_main
    _clp_thread_mutex_unlock(1);
    pop();
    line(31);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_libnam",base);
//
    line(35);
    static stvar _st_xx;
    line(36);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(37);
    line(38);
    push_symbol(_st_mutex.ptr);//s_libnam
    _clp_thread_mutex_lock(1);
    pop();
    line(39);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_192:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_libnam
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_libnam
    }
    assign(base+1);//result
    pop();
    line(40);
    push_symbol(_st_mutex.ptr);//s_libnam
    _clp_thread_mutex_unlock(1);
    pop();
    line(41);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_shared",base);
//
    line(45);
    static stvar _st_xx;
    line(46);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(47);
    line(48);
    push_symbol(_st_mutex.ptr);//s_shared
    _clp_thread_mutex_lock(1);
    pop();
    line(49);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_306:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_shared
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_shared
    }
    assign(base+1);//result
    pop();
    line(50);
    push_symbol(_st_mutex.ptr);//s_shared
    _clp_thread_mutex_unlock(1);
    pop();
    line(51);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_srcdir",base);
//
    line(55);
    static stvar _st_xx;
    line(56);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(57);
    line(58);
    push_symbol(_st_mutex.ptr);//s_srcdir
    _clp_thread_mutex_lock(1);
    pop();
    line(59);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_420:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_srcdir
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_srcdir
    }
    assign(base+1);//result
    pop();
    line(60);
    push_symbol(_st_mutex.ptr);//s_srcdir
    _clp_thread_mutex_unlock(1);
    pop();
    line(61);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_incdir",base);
//
    line(65);
    static stvar _st_xx;
    line(66);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(67);
    line(68);
    push_symbol(_st_mutex.ptr);//s_incdir
    _clp_thread_mutex_lock(1);
    pop();
    line(69);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_534:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_incdir
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_incdir
    }
    assign(base+1);//result
    pop();
    line(70);
    push_symbol(_st_mutex.ptr);//s_incdir
    _clp_thread_mutex_unlock(1);
    pop();
    line(71);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_libdir",base);
//
    line(75);
    static stvar _st_xx;
    line(76);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(77);
    line(78);
    push_symbol(_st_mutex.ptr);//s_libdir
    _clp_thread_mutex_lock(1);
    pop();
    line(79);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_648:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_libdir
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_libdir
    }
    assign(base+1);//result
    pop();
    line(80);
    push_symbol(_st_mutex.ptr);//s_libdir
    _clp_thread_mutex_unlock(1);
    pop();
    line(81);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_libfil",base);
//
    line(85);
    static stvar _st_xx;
    line(86);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(87);
    line(88);
    push_symbol(_st_mutex.ptr);//s_libfil
    _clp_thread_mutex_lock(1);
    pop();
    line(89);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_762:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_libfil
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_libfil
    }
    assign(base+1);//result
    pop();
    line(90);
    push_symbol(_st_mutex.ptr);//s_libfil
    _clp_thread_mutex_unlock(1);
    pop();
    line(91);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_quiet",base);
//
    line(95);
    static stvar _st_xx(&FALSE);
    line(96);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(97);
    line(98);
    push_symbol(_st_mutex.ptr);//s_quiet
    _clp_thread_mutex_lock(1);
    pop();
    line(99);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_879:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_quiet
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_quiet
    }
    assign(base+1);//result
    pop();
    line(100);
    push_symbol(_st_mutex.ptr);//s_quiet
    _clp_thread_mutex_unlock(1);
    pop();
    line(101);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_version",base);
//
    line(105);
    static stvar _st_xx(&FALSE);
    line(106);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(107);
    line(108);
    push_symbol(_st_mutex.ptr);//s_version
    _clp_thread_mutex_lock(1);
    pop();
    line(109);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_996:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_version
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_version
    }
    assign(base+1);//result
    pop();
    line(110);
    push_symbol(_st_mutex.ptr);//s_version
    _clp_thread_mutex_unlock(1);
    pop();
    line(111);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_debug",base);
//
    line(115);
    static stvar _st_xx(&FALSE);
    line(116);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(117);
    line(118);
    push_symbol(_st_mutex.ptr);//s_debug
    _clp_thread_mutex_lock(1);
    pop();
    line(119);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_1113:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_debug
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_debug
    }
    assign(base+1);//result
    pop();
    line(120);
    push_symbol(_st_mutex.ptr);//s_debug
    _clp_thread_mutex_unlock(1);
    pop();
    line(121);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_dry",base);
//
    line(125);
    static stvar _st_xx(&FALSE);
    line(126);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(127);
    line(128);
    push_symbol(_st_mutex.ptr);//s_dry
    _clp_thread_mutex_lock(1);
    pop();
    line(129);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_1230:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_dry
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_dry
    }
    assign(base+1);//result
    pop();
    line(130);
    push_symbol(_st_mutex.ptr);//s_dry
    _clp_thread_mutex_unlock(1);
    pop();
    line(131);
    push_symbol(base+1);//result
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_s_runcnt(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_runcnt",base);
//
    line(135);
    static stvar _st_xx((double)0);
    line(136);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(137);
    line(138);
    push_symbol(_st_mutex.ptr);//s_runcnt
    _clp_thread_mutex_lock(1);
    pop();
    line(139);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_1347:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_runcnt
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_runcnt
    }
    assign(base+1);//result
    pop();
    line(140);
    push_symbol(_st_mutex.ptr);//s_runcnt
    _clp_thread_mutex_unlock(1);
    pop();
    line(141);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_primary",base);
//
    line(145);
    static stvar _st_xx;
    line(146);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(147);
    line(148);
    push_symbol(_st_mutex.ptr);//s_primary
    _clp_thread_mutex_lock(1);
    pop();
    line(149);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_1461:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_primary
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_primary
    }
    assign(base+1);//result
    pop();
    line(150);
    push_symbol(_st_mutex.ptr);//s_primary
    _clp_thread_mutex_unlock(1);
    pop();
    line(151);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_resource",base);
//
    line(155);
    static stvar _st_xx;
    line(156);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(157);
    line(158);
    push_symbol(_st_mutex.ptr);//s_resource
    _clp_thread_mutex_lock(1);
    pop();
    line(159);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_1575:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_resource
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_resource
    }
    assign(base+1);//result
    pop();
    line(160);
    push_symbol(_st_mutex.ptr);//s_resource
    _clp_thread_mutex_unlock(1);
    pop();
    line(161);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_libspec",base);
//
    line(165);
    static stvar _st_xx;
    line(166);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(167);
    line(168);
    push_symbol(_st_mutex.ptr);//s_libspec
    _clp_thread_mutex_lock(1);
    pop();
    line(169);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_1689:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_libspec
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_libspec
    }
    assign(base+1);//result
    pop();
    line(170);
    push_symbol(_st_mutex.ptr);//s_libspec
    _clp_thread_mutex_unlock(1);
    pop();
    line(171);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_rules",base);
//
    line(175);
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
    line(198);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(199);
    line(200);
    push_symbol(_st_mutex.ptr);//s_rules
    _clp_thread_mutex_lock(1);
    pop();
    line(201);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_2184:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_rules
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_rules
    }
    assign(base+1);//result
    pop();
    line(202);
    push_symbol(_st_mutex.ptr);//s_rules
    _clp_thread_mutex_unlock(1);
    pop();
    line(203);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("s_batext",base);
//
    line(207);
    static stvar _st_xx;
    line(208);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(209);
    line(210);
    push_symbol(_st_mutex.ptr);//s_batext
    _clp_thread_mutex_lock(1);
    pop();
    line(211);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_2298:;
    if(flag()){
    push_symbol(_st_xx.ptr);//s_batext
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//s_batext
    }
    assign(base+1);//result
    pop();
    line(212);
    push_symbol(_st_mutex.ptr);//s_batext
    _clp_thread_mutex_unlock(1);
    pop();
    line(213);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("resource_hash",base);
//
    line(217);
    static stvar _st_xx;
    static int _ini_xx=[=](){
        _clp_simplehashnew(0);
        assign(_st_xx.ptr);
        pop();
        return 1;
    }();
    line(218);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(219);
    line(220);
    push_symbol(_st_mutex.ptr);//resource_hash
    _clp_thread_mutex_lock(1);
    pop();
    line(221);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_2420:;
    if(flag()){
    push_symbol(_st_xx.ptr);//resource_hash
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//resource_hash
    }
    assign(base+1);//result
    pop();
    line(222);
    push_symbol(_st_mutex.ptr);//resource_hash
    _clp_thread_mutex_unlock(1);
    pop();
    line(223);
    push_symbol(base+1);//result
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
while(stack<base+2)PUSHNIL();
argno=1;
push_call("omitted_hash",base);
//
    line(227);
    static stvar _st_xx;
    static int _ini_xx=[=](){
        _clp_simplehashnew(0);
        assign(_st_xx.ptr);
        pop();
        return 1;
    }();
    line(228);
    static stvar _st_mutex;
    static int _ini_mutex=[=](){
        _clp_thread_mutex_init(0);
        assign(_st_mutex.ptr);
        pop();
        return 1;
    }();
    line(229);
    line(230);
    push_symbol(_st_mutex.ptr);//omitted_hash
    _clp_thread_mutex_lock(1);
    pop();
    line(231);
    push_symbol(base+0);//x
    push(&NIL);
    eqeq();
    cmp_2542:;
    if(flag()){
    push_symbol(_st_xx.ptr);//omitted_hash
    }else{
    push_symbol(base+0);//x
    assign(_st_xx.ptr);//omitted_hash
    }
    assign(base+1);//result
    pop();
    line(232);
    push_symbol(_st_mutex.ptr);//omitted_hash
    _clp_thread_mutex_unlock(1);
    pop();
    line(233);
    push_symbol(base+1);//result
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

