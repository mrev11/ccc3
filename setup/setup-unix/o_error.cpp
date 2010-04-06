//input: o_error.ppo (5.0.17)

#include <cccdef.h>

static void _blk_errorregister_0(int argno);
extern void _clp_classattrib(int argno);
extern void _clp_classmethod(int argno);
extern void _clp_classregister(int argno);
extern void _clp_errorclass(int argno);
extern void _clp_errorini(int argno);
extern void _clp_errornew(int argno);
static void _clp_errorregister(int argno);
extern void _clp_objectclass(int argno);
extern void _clp_objectini(int argno);
extern void _clp_objectnew(int argno);
static void _ini__clid_error();

class _method3_candefault: public _method3_{public: _method3_candefault():_method3_("candefault"){};}; static _method3_candefault _o_method_candefault;
class _method3_canretry: public _method3_{public: _method3_canretry():_method3_("canretry"){};}; static _method3_canretry _o_method_canretry;
class _method3_cansubstitute: public _method3_{public: _method3_cansubstitute():_method3_("cansubstitute"){};}; static _method3_cansubstitute _o_method_cansubstitute;
class _method3_description: public _method3_{public: _method3_description():_method3_("description"){};}; static _method3_description _o_method_description;
class _method3_filename: public _method3_{public: _method3_filename():_method3_("filename"){};}; static _method3_filename _o_method_filename;
class _method3_gencode: public _method3_{public: _method3_gencode():_method3_("gencode"){};}; static _method3_gencode _o_method_gencode;
class _method3_initialize: public _method3_{public: _method3_initialize():_method3_("initialize"){};}; static _method3_initialize _o_method_initialize;
class _method3_operation: public _method3_{public: _method3_operation():_method3_("operation"){};}; static _method3_operation _o_method_operation;
class _method3_oscode: public _method3_{public: _method3_oscode():_method3_("oscode"){};}; static _method3_oscode _o_method_oscode;
class _method3_severity: public _method3_{public: _method3_severity():_method3_("severity"){};}; static _method3_severity _o_method_severity;
class _method3_subcode: public _method3_{public: _method3_subcode():_method3_("subcode"){};}; static _method3_subcode _o_method_subcode;
class _method3_subsystem: public _method3_{public: _method3_subsystem():_method3_("subsystem"){};}; static _method3_subsystem _o_method_subsystem;
class _method3_tries: public _method3_{public: _method3_tries():_method3_("tries"){};}; static _method3_tries _o_method_tries;

MUTEX_CREATE(_mutex_clid_error);
static VALUE* _st_clid_error_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_clid_error);
    static stvar _st_clid_error(_ini__clid_error);
    MUTEX_UNLOCK(_mutex_clid_error);
    SIGNAL_UNLOCK();
    return _st_clid_error.ptr;
}

static void _ini__clid_error()
{
    _clp_errorregister(0);
}
//=======================================================================
void _clp_errorclass(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("errorclass",base);
//
    line(25);
    push_symbol(_st_clid_error_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_errorregister(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+1)PUSHNIL();
argno=0;
push_call("errorregister",base);
//
    line(29);
    string(L"error");
    _clp_objectclass(0);
    _clp_classregister(2);
    assign(base+0);//clid
    pop();
    line(31);
    push_symbol(base+0);//clid
    string(L"initialize");
    block(_blk_errorregister_0,0);
    _clp_classmethod(3);
    pop();
    line(32);
    push_symbol(base+0);//clid
    string(L"args");
    _clp_classattrib(2);
    pop();
    line(33);
    push_symbol(base+0);//clid
    string(L"candefault");
    _clp_classattrib(2);
    pop();
    line(34);
    push_symbol(base+0);//clid
    string(L"canretry");
    _clp_classattrib(2);
    pop();
    line(35);
    push_symbol(base+0);//clid
    string(L"cansubstitute");
    _clp_classattrib(2);
    pop();
    line(36);
    push_symbol(base+0);//clid
    string(L"cargo");
    _clp_classattrib(2);
    pop();
    line(37);
    push_symbol(base+0);//clid
    string(L"description");
    _clp_classattrib(2);
    pop();
    line(38);
    push_symbol(base+0);//clid
    string(L"filename");
    _clp_classattrib(2);
    pop();
    line(39);
    push_symbol(base+0);//clid
    string(L"gencode");
    _clp_classattrib(2);
    pop();
    line(40);
    push_symbol(base+0);//clid
    string(L"operation");
    _clp_classattrib(2);
    pop();
    line(41);
    push_symbol(base+0);//clid
    string(L"oscode");
    _clp_classattrib(2);
    pop();
    line(42);
    push_symbol(base+0);//clid
    string(L"severity");
    _clp_classattrib(2);
    pop();
    line(43);
    push_symbol(base+0);//clid
    string(L"subcode");
    _clp_classattrib(2);
    pop();
    line(44);
    push_symbol(base+0);//clid
    string(L"subsystem");
    _clp_classattrib(2);
    pop();
    line(45);
    push_symbol(base+0);//clid
    string(L"tries");
    _clp_classattrib(2);
    pop();
    line(47);
    push_symbol(base+0);//clid
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_errorregister_0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_errorregister_0",base);
//
    push_blkarg(base+1);//this
    _clp_errorini(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
void _clp_errornew(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+1)PUSHNIL();
argno=0;
push_call("errornew",base);
//
    line(52);
    _clp_errorclass(0);
    assign(base+0);//clid
    pop();
    line(53);
    push_symbol(base+0);//clid
    _clp_objectnew(1);
    _o_method_initialize.eval(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_errorini(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("errorini",base);
//
    line(65);
    push_symbol(base+0);//this
    _clp_objectini(1);
    pop();
    line(67);
    push_symbol(base+0);//this
    push(&FALSE);
    _o_method_candefault.eval(2);
    pop();
    line(68);
    push_symbol(base+0);//this
    push(&FALSE);
    _o_method_canretry.eval(2);
    pop();
    line(69);
    push_symbol(base+0);//this
    push(&FALSE);
    _o_method_cansubstitute.eval(2);
    pop();
    line(70);
    push_symbol(base+0);//this
    string(L"");
    _o_method_description.eval(2);
    pop();
    line(71);
    push_symbol(base+0);//this
    string(L"");
    _o_method_filename.eval(2);
    pop();
    line(72);
    push_symbol(base+0);//this
    string(L"");
    _o_method_operation.eval(2);
    pop();
    line(73);
    push_symbol(base+0);//this
    string(L"");
    _o_method_subsystem.eval(2);
    pop();
    line(74);
    push_symbol(base+0);//this
    push(&ZERO);
    _o_method_gencode.eval(2);
    pop();
    line(75);
    push_symbol(base+0);//this
    push(&ZERO);
    _o_method_oscode.eval(2);
    pop();
    line(76);
    push_symbol(base+0);//this
    push(&ZERO);
    _o_method_severity.eval(2);
    pop();
    line(77);
    push_symbol(base+0);//this
    push(&ZERO);
    _o_method_subcode.eval(2);
    pop();
    line(78);
    push_symbol(base+0);//this
    push(&ZERO);
    _o_method_tries.eval(2);
    pop();
    line(80);
    push_symbol(base+0);//this
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

