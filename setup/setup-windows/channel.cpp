//input: ppo/channel.ppo (5.7.2)

#include <cccdef.h>

static void _blk_channelregister_0(int argno);
static void _blk_channelregister_1(int argno);
static void _blk_channelregister_2(int argno);
static void _blk_channelregister_3(int argno);
static void _blk_channelregister_4(int argno);
static void _blk_channelregister_5(int argno);
static void _blk_channelregister_6(int argno);
extern void _clp_channelclass(int argno);
extern void _clp_channelnew(int argno);
static void _clp_channelregister(int argno);
extern void _clp_classattrib(int argno);
extern void _clp_classmethod(int argno);
extern void _clp_classregister(int argno);
extern void _clp_convertfspec2nativeformat(int argno);
extern void _clp_objectclass(int argno);
extern void _clp_objectnew(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);
extern void _clp_setlocalname(int argno);

namespace _nsp_channel{
static void _clp_close(int argno);
extern void _clp_get_file_pointer(int argno);
static void _clp_initialize(int argno);
extern void _clp_off(int argno);
static void _clp_on(int argno);
static void _clp_open(int argno);
extern void _clp_set_file_pointer(int argno);
static void _clp_write(int argno);
static void _clp_writeln(int argno);
}//namespace channel

class _method6_fileptr: public _method6_{public: _method6_fileptr():_method6_("fileptr"){};}; static _method6_fileptr _o_method_fileptr;
class _method6_filespc: public _method6_{public: _method6_filespc():_method6_("filespc"){};}; static _method6_filespc _o_method_filespc;
class _method6_initialize: public _method6_{public: _method6_initialize():_method6_("initialize"){};}; static _method6_initialize _o_method_initialize;
class _method6_localflag: public _method6_{public: _method6_localflag():_method6_("localflag"){};}; static _method6_localflag _o_method_localflag;
class _method6_localname: public _method6_{public: _method6_localname():_method6_("localname"){};}; static _method6_localname _o_method_localname;
class _method6_off: public _method6_{public: _method6_off():_method6_("off"){};}; static _method6_off _o_method_off;
class _method6_on: public _method6_{public: _method6_on():_method6_("on"){};}; static _method6_on _o_method_on;


//CLANG
#include <cccapi.h>
//CEND

//=======================================================================

static VALUE* _st_clid_channel_ptr()
{
    static stvar _st_clid_channel;
    static int _ini_clid_channel=[=](){
        _clp_channelregister(0);
        assign(_st_clid_channel.ptr);
        pop();
        return 1;
    }();
    return _st_clid_channel.ptr;
}
//=======================================================================
void _clp_channelclass(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("channelclass",base);
//
    line(4);
    push_symbol(_st_clid_channel_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_channelregister(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+1)PUSHNIL();
argno=0;
push_call("channelregister",base);
//
    line(7);
    string(L"channel");
    ::_clp_objectclass(0);
    array(1);
    _clp_classregister(2);
    assign(base+0);//clid
    pop();
    line(8);
    push_symbol(base+0);//clid
    string(L"filespc");
    _clp_classattrib(2);
    pop();
    line(9);
    push_symbol(base+0);//clid
    string(L"fileptr");
    _clp_classattrib(2);
    pop();
    line(10);
    push_symbol(base+0);//clid
    string(L"localname");
    _clp_classattrib(2);
    pop();
    line(11);
    push_symbol(base+0);//clid
    string(L"localflag");
    _clp_classattrib(2);
    pop();
    line(12);
    push_symbol(base+0);//clid
    string(L"open");
    block(_blk_channelregister_0,0);
    _clp_classmethod(3);
    pop();
    line(13);
    push_symbol(base+0);//clid
    string(L"close");
    block(_blk_channelregister_1,0);
    _clp_classmethod(3);
    pop();
    line(14);
    push_symbol(base+0);//clid
    string(L"on");
    block(_blk_channelregister_2,0);
    _clp_classmethod(3);
    pop();
    line(15);
    push_symbol(base+0);//clid
    string(L"off");
    block(_blk_channelregister_3,0);
    _clp_classmethod(3);
    pop();
    line(16);
    push_symbol(base+0);//clid
    string(L"write");
    block(_blk_channelregister_4,0);
    _clp_classmethod(3);
    pop();
    line(17);
    push_symbol(base+0);//clid
    string(L"writeln");
    block(_blk_channelregister_5,0);
    _clp_classmethod(3);
    pop();
    line(18);
    push_symbol(base+0);//clid
    string(L"initialize");
    block(_blk_channelregister_6,0);
    _clp_classmethod(3);
    pop();
    line(19);
    push_symbol(base+0);//clid
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_channelregister_0(int argno)
{
//
    _nsp_channel::_clp_open(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_channelregister_1(int argno)
{
//
    _nsp_channel::_clp_close(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_channelregister_2(int argno)
{
//
    _nsp_channel::_clp_on(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_channelregister_3(int argno)
{
//
    _nsp_channel::_clp_off(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_channelregister_4(int argno)
{
//
    _nsp_channel::_clp_write(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_channelregister_5(int argno)
{
//
    _nsp_channel::_clp_writeln(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_channelregister_6(int argno)
{
//
    _nsp_channel::_clp_initialize(argno-1);
//
*(stack-2)=*(stack-1);pop();
}
//=======================================================================
void _clp_channelnew(int argno)
{
    push(_st_clid_channel_ptr());
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
namespace _nsp_channel{
static void _clp_initialize(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("channel.initialize",base);
//
    line(45);
    push_symbol(base+0);//this
    push_symbol(base+1);//filespc
    _o_method_filespc.eval(2);
    pop();
    line(46);
    push_symbol(base+0);//this
    push(&TRUE);
    _o_method_localflag.eval(2);
    pop();
    line(47);
    push_symbol(base+0);//this
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace channel
//=======================================================================
namespace _nsp_channel{
static void _clp_open(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("channel.open",base);
//
    if( ((base+1)->type==TYPE_NIL)||
       (((base+1)->type==TYPE_REF)&&
        ((base+1)->data.vref->value.type==TYPE_NIL))){
    line(51);
    push(&FALSE);
    assign(base+1);//additive
    pop();
    }
    line(52);
    line(59);
    push_symbol(base+0);//this
    push_symbol(base+0);//this
    _o_method_filespc.eval(1);
    _o_method_localname.eval(2);
    pop();
    line(62);
    line(60);
    push_symbol(base+0);//this
    _o_method_localflag.eval(1);
    if(!flag()) goto if_1_1;
        line(61);
        push_symbol(base+0);//this
        _o_method_localname.eval(1);
        _clp_setlocalname(1);
        push_symbol(base+0);//this
        swap();
        _o_method_localname.eval(2);
        pop();
    if_1_1:
    if_1_0:;
    line(63);
    push_symbol(base+0);//this
    _o_method_localname.eval(1);
    _clp_convertfspec2nativeformat(1);
    assign(base+2);//fspc
    pop();
    line(64);
    {//clang
    #define LOCAL_this (base+0)
    #define LOCAL_additive (base+1)
    #define LOCAL_fspc (base+2)
    #define LOCAL_fptr (base+3)
    
    VALUE *stk=stack;
    push_symbol(LOCAL_fspc);
    str2bin(TOP());
    push_symbol(LOCAL_additive);
    const char *mode=flag()?"a":"w";
    FILE *fp=fopen(BINARYPTR(stk),mode);
    if( fp )
    {
        pointer(fp);
    }
    else
    {
        PUSHNIL();
    }
    assign(LOCAL_fptr);
    pop();
    stack=stk;

    #undef LOCAL_this
    #undef LOCAL_additive
    #undef LOCAL_fspc
    #undef LOCAL_fptr
    }//cend
    line(84);
    push_symbol(base+0);//this
    push_symbol(base+3);//fptr
    _o_method_fileptr.eval(2);
    pop();
    line(85);
    push_symbol(base+0);//this
    _o_method_fileptr.eval(1);
    push(&NIL);
    neeq();
    cmp_817:;
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace channel
//=======================================================================
namespace _nsp_channel{
static void _clp_close(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("channel.close",base);
//
    line(90);
    push(&TRUE);
    assign(base+2);//result
    pop();
    line(91);
    push_symbol(base+0);//this
    _o_method_fileptr.eval(1);
    assign(base+1);//fptr
    pop();
    line(105);
    line(92);
    push_symbol(base+1);//fptr
    push(&NIL);
    neeq();
    cmp_878:;
    if(!flag()) goto if_2_1;
        line(95);
        line(93);
        push_symbol(base+1);//fptr
        _nsp_channel::_clp_get_file_pointer(0);
        eqeq();
        cmp_892:;
        if(!flag()) goto if_3_1;
            line(94);
            push(&NIL);
            _nsp_channel::_clp_set_file_pointer(1);
            pop();
        if_3_1:
        if_3_0:;
        line(96);
        {//clang
        #define LOCAL_this (base+0)
        #define LOCAL_fptr (base+1)
        #define LOCAL_result (base+2)
        
        VALUE *stk=stack;
        push_symbol(LOCAL_fptr);
        logical( !fclose((FILE*)stk->data.pointer) );
        assign(LOCAL_result);
        pop();
        stack=stk;

        #undef LOCAL_this
        #undef LOCAL_fptr
        #undef LOCAL_result
        }//cend
        line(104);
        push_symbol(base+0);//this
        push(&NIL);
        _o_method_fileptr.eval(2);
        pop();
    if_2_1:
    if_2_0:;
    line(106);
    push_symbol(base+2);//result
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace channel
//=======================================================================
namespace _nsp_channel{
static void _clp_on(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("channel.on",base);
//
    line(111);
    push_symbol(base+0);//this
    _o_method_fileptr.eval(1);
    _nsp_channel::_clp_set_file_pointer(1);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace channel
//=======================================================================
namespace _nsp_channel{
void _clp_off(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("channel.off",base);
//
    line(117);
    line(115);
    push_symbol(base+0);//this
    push(&NIL);
    eqeq();
    cmp_1035:;
    if(flag()){
    push(&TRUE);
    }else{
    push_symbol(base+0);//this
    _o_method_fileptr.eval(1);
    _nsp_channel::_clp_get_file_pointer(0);
    eqeq();
    cmp_1046:;
    }
    if(!flag()) goto if_4_1;
        line(116);
        push(&NIL);
        _nsp_channel::_clp_set_file_pointer(1);
        pop();
    if_4_1:
    if_4_0:;
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace channel
//=======================================================================
namespace _nsp_channel{
static void _clp_write(int argno)
{
VALUE *base=stack-argno;
while(stack<base+1)PUSHNIL();
while(stack<base+max(argno,1)+0)PUSHNIL();
argno=max(argno,1);
push_call("channel.write",base);
//
    line(121);
    push_symbol(base+0);//this
    _o_method_on.eval(1);
    pop();
    line(122);
    {int argc=0+1-1;
    {
    number(2);
    if(TOP()->type==TYPE_NIL){pop();number(1);} else
    if(TOP()->type!=TYPE_NUMBER) error_arg("*[x..]",TOP(),1);
    int xl=D2INT(TOP()->data.number);pop();xl=max(xl,1)-1+0;
    push(&NIL);
    if(TOP()->type==TYPE_NIL){pop();number(argno);} else
    if(TOP()->type!=TYPE_NUMBER) error_arg("*[..x]",TOP(),1);
    int xh=D2INT(TOP()->data.number)+0;pop();xh=min(xh,argno);
    int i;for(i=xl;i<xh;i++){argc++;push(base+i);}
    }
    _clp_qqout(argc);
    };
    pop();
    line(123);
    push_symbol(base+0);//this
    _o_method_off.eval(1);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace channel
//=======================================================================
namespace _nsp_channel{
static void _clp_writeln(int argno)
{
VALUE *base=stack-argno;
while(stack<base+1)PUSHNIL();
while(stack<base+max(argno,1)+0)PUSHNIL();
argno=max(argno,1);
push_call("channel.writeln",base);
//
    line(127);
    push_symbol(base+0);//this
    _o_method_on.eval(1);
    pop();
    line(128);
    {int argc=0+1-1;
    {
    number(2);
    if(TOP()->type==TYPE_NIL){pop();number(1);} else
    if(TOP()->type!=TYPE_NUMBER) error_arg("*[x..]",TOP(),1);
    int xl=D2INT(TOP()->data.number);pop();xl=max(xl,1)-1+0;
    push(&NIL);
    if(TOP()->type==TYPE_NIL){pop();number(argno);} else
    if(TOP()->type!=TYPE_NUMBER) error_arg("*[..x]",TOP(),1);
    int xh=D2INT(TOP()->data.number)+0;pop();xh=min(xh,argno);
    int i;for(i=xl;i<xh;i++){argc++;push(base+i);}
    }
    _clp_qqout(argc);
    };
    pop();
    line(129);
    _clp_qout(0);
    pop();
    line(130);
    push_symbol(base+0);//this
    _o_method_off.eval(1);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace channel
//=======================================================================

