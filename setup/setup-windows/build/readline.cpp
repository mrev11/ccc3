//input: ppo/readline.ppo (5.7.2)

#include <cccdef.h>

static void _blk_readlineregister_0(int argno);
static void _blk_readlineregister_1(int argno);
extern void _clp_at(int argno);
extern void _clp_bin(int argno);
extern void _clp_classattrib(int argno);
extern void _clp_classmethod(int argno);
extern void _clp_classregister(int argno);
extern void _clp_len(int argno);
extern void _clp_objectclass(int argno);
extern void _clp_objectnew(int argno);
extern void _clp_readlineclass(int argno);
extern void _clp_readlinenew(int argno);
static void _clp_readlineregister(int argno);
extern void _clp_replicate(int argno);
extern void _clp_xvgetchar(int argno);
extern void _clp_xvmove(int argno);
extern void _clp_xvread(int argno);

namespace _nsp_readline{
static void _clp_initialize(int argno);
static void _clp_readline(int argno);
}//namespace readline

class _method6_buffer: public _method6_{public: _method6_buffer():_method6_("buffer"){};}; static _method6_buffer _o_method_buffer;
class _method6_endofline: public _method6_{public: _method6_endofline():_method6_("endofline"){};}; static _method6_endofline _o_method_endofline;
class _method6_fd: public _method6_{public: _method6_fd():_method6_("fd"){};}; static _method6_fd _o_method_fd;
class _method6_initialize: public _method6_{public: _method6_initialize():_method6_("initialize"){};}; static _method6_initialize _o_method_initialize;
class _method6_initialize_C_object: public _method6c_{public: _method6_initialize_C_object():_method6c_("initialize",_clp_objectclass){};}; static _method6_initialize_C_object _o_method_initialize_C_object;
class _method6_nbyte: public _method6_{public: _method6_nbyte():_method6_("nbyte"){};}; static _method6_nbyte _o_method_nbyte;

//=======================================================================

static VALUE* _st_clid_readline_ptr()
{
    static stvar _st_clid_readline;
    static int _ini_clid_readline=[=](){
        _clp_readlineregister(0);
        assign(_st_clid_readline.ptr);
        pop();
        return 1;
    }();
    return _st_clid_readline.ptr;
}
//=======================================================================
void _clp_readlineclass(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("readlineclass",base);
//
    line(4);
    push_symbol(_st_clid_readline_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_readlineregister(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+1)PUSHNIL();
argno=0;
push_call("readlineregister",base);
//
    line(7);
    string(L"readline");
    ::_clp_objectclass(0);
    array(1);
    _clp_classregister(2);
    assign(base+0);//clid
    pop();
    line(8);
    push_symbol(base+0);//clid
    string(L"initialize");
    block(_blk_readlineregister_0,0);
    _clp_classmethod(3);
    pop();
    line(9);
    push_symbol(base+0);//clid
    string(L"fd");
    _clp_classattrib(2);
    pop();
    line(10);
    push_symbol(base+0);//clid
    string(L"buffer");
    _clp_classattrib(2);
    pop();
    line(11);
    push_symbol(base+0);//clid
    string(L"nbyte");
    _clp_classattrib(2);
    pop();
    line(12);
    push_symbol(base+0);//clid
    string(L"endofline");
    _clp_classattrib(2);
    pop();
    line(13);
    push_symbol(base+0);//clid
    string(L"readline");
    block(_blk_readlineregister_1,0);
    _clp_classmethod(3);
    pop();
    line(14);
    push_symbol(base+0);//clid
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_readlineregister_0(int argno)
{
//
    _nsp_readline::_clp_initialize(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_readlineregister_1(int argno)
{
//
    _nsp_readline::_clp_readline(argno-1);
//
*(stack-2)=*(stack-1);pop();
}
//=======================================================================
void _clp_readlinenew(int argno)
{
    push(_st_clid_readline_ptr());
    _clp_objectnew(1);
    dup();
    int i;
    for(i=0; i<argno; i++)
    {
        *(stack-2-i)=*(stack-3-i);
    }
    *(stack-2-argno)=*(stack-1);
    pop();
    _o_method_initialize.eval(1+argno);
}
//=======================================================================
namespace _nsp_readline{
static void _clp_initialize(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("readline.initialize",base);
//
    line(44);
    push_symbol(base+0);//this
    _o_method_initialize_C_object.eval(1);
    pop();
    line(45);
    push_symbol(base+0);//this
    push_symbol(base+1);//fd
    _o_method_fd.eval(2);
    pop();
    line(46);
    push_symbol(base+0);//this
    binary("");
    _o_method_buffer.eval(2);
    pop();
    line(47);
    push_symbol(base+0);//this
    push(&ZERO);
    _o_method_nbyte.eval(2);
    pop();
    line(48);
    push_symbol(base+0);//this
    number(10);
    _clp_bin(1);
    _o_method_endofline.eval(2);
    pop();
    line(49);
    push_symbol(base+0);//this
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace readline
//=======================================================================
namespace _nsp_readline{
static void _clp_readline(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+4)PUSHNIL();
argno=1;
push_call("readline.readline",base);
//
    line(54);
    line(56);
    push_symbol(base+0);//this
    _o_method_endofline.eval(1);
    push_symbol(base+0);//this
    _o_method_buffer.eval(1);
    _clp_at(2);
    assign(base+2);//eolpos
    pop();
    line(69);
    lab_1_1:
    line(57);
    push_symbol(base+2);//eolpos
    push(&ZERO);
    lteq();
    cmp_528:;
    if(flag()){
    push(&TRUE);
    }else{
    push_symbol(base+0);//this
    _o_method_nbyte.eval(1);
    push_symbol(base+2);//eolpos
    lt();
    cmp_539:;
    }
    if(!flag()) goto lab_1_2;
        line(60);
        line(58);
        push_symbol(base+0);//this
        _o_method_nbyte.eval(1);
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        _clp_len(1);
        gteq();
        cmp_558:;
        if(!flag()) goto if_2_1;
            line(59);
            push_symbol(base+0);//this
            _o_method_buffer.eval(1);
            binaryx("00");
            number(4096);
            _clp_replicate(2);
            add();
            push_symbol(base+0);//this
            swap();
            _o_method_buffer.eval(2);
            pop();
        if_2_1:
        if_2_0:;
        line(61);
        push_symbol(base+0);//this
        _o_method_fd.eval(1);
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        push_symbol(base+0);//this
        _o_method_nbyte.eval(1);
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        _clp_len(1);
        push_symbol(base+0);//this
        _o_method_nbyte.eval(1);
        sub();
        _clp_xvread(4);
        assign(base+3);//nbyte
        pop();
        line(67);
        line(62);
        push_symbol(base+3);//nbyte
        push(&ZERO);
        gt();
        cmp_691:;
        if(!flag()) goto if_3_1;
            line(63);
            push_symbol(base+0);//this
            _o_method_nbyte.eval(1);
            push_symbol(base+3);//nbyte
            add();
            push_symbol(base+0);//this
            swap();
            _o_method_nbyte.eval(2);
            pop();
        goto if_3_0;
        if_3_1:
        line(64);
            line(65);
            push(&NIL);
            assign(base+2);//eolpos
            pop();
            line(66);
            goto lab_1_2;//exit
        if_3_2:
        if_3_0:;
        line(68);
        push_symbol(base+0);//this
        _o_method_endofline.eval(1);
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        _clp_at(2);
        assign(base+2);//eolpos
        pop();
    goto lab_1_1;
    lab_1_2:;
    line(80);
    line(71);
    push_symbol(base+2);//eolpos
    push(&NIL);
    neeq();
    cmp_785:;
    if(!flag()) goto if_4_1;
        line(72);
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        push(&ZERO);
        push_symbol(base+2);//eolpos
        _clp_xvgetchar(3);
        assign(base+1);//line
        pop();
        line(73);
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        push(&ZERO);
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        push_symbol(base+2);//eolpos
        push_symbol(base+0);//this
        _o_method_nbyte.eval(1);
        push_symbol(base+2);//eolpos
        sub();
        push_symbol(base+0);//this
        swap();
        _o_method_nbyte.eval(2);
        _clp_xvmove(5);
        pop();
    goto if_4_0;
    if_4_1:
    line(74);
    push_symbol(base+0);//this
    _o_method_nbyte.eval(1);
    push(&ZERO);
    gt();
    cmp_895:;
    if(!flag()) goto if_4_2;
        line(75);
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        push(&ZERO);
        push_symbol(base+0);//this
        _o_method_nbyte.eval(1);
        _clp_xvgetchar(3);
        assign(base+1);//line
        pop();
        line(76);
        push_symbol(base+0);//this
        binary("");
        _o_method_buffer.eval(2);
        pop();
        line(77);
        push_symbol(base+0);//this
        push(&ZERO);
        _o_method_nbyte.eval(2);
        pop();
    goto if_4_0;
    if_4_2:
    line(78);
        line(79);
        push(&NIL);
        assign(base+1);//line
        pop();
    if_4_3:
    if_4_0:;
    line(81);
    push_symbol(base+1);//line
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace readline
//=======================================================================

