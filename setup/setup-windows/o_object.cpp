//input: o_object.ppo (5.6.0)

#include <cccdef.h>

static void _blk_objectregister_0(int argno);
static void _blk_objectregister_1(int argno);
static void _blk_objectregister_10(int argno);
static void _blk_objectregister_11(int argno);
static void _blk_objectregister_12(int argno);
static void _blk_objectregister_13(int argno);
static void _blk_objectregister_14(int argno);
static void _blk_objectregister_2(int argno);
static void _blk_objectregister_3(int argno);
static void _blk_objectregister_4(int argno);
static void _blk_objectregister_5(int argno);
static void _blk_objectregister_6(int argno);
static void _blk_objectregister_7(int argno);
static void _blk_objectregister_8(int argno);
static void _blk_objectregister_9(int argno);
extern void _clp_aadd(int argno);
static void _clp_ancestors(int argno);
extern void _clp_array(int argno);
extern void _clp_ascan(int argno);
extern void _clp_asort(int argno);
static void _clp_attrvals(int argno);
extern void _clp_classattrnames(int argno);
extern void _clp_classbaseid(int argno);
extern void _clp_classinheritstruct(int argno);
extern void _clp_classmethnames(int argno);
extern void _clp_classmethod(int argno);
extern void _clp_classname(int argno);
extern void _clp_classobjectlength(int argno);
extern void _clp_classregister(int argno);
static void _clp_clean(int argno);
extern void _clp_evalarray(int argno);
static void _clp_evalmethod(int argno);
extern void _clp_getclassid(int argno);
extern void _clp_getmethod(int argno);
extern void _clp_getobjectasarray(int argno);
static void _clp_isderivedfrom(int argno);
static void _clp_isderivedfrom1(int argno);
extern void _clp_len(int argno);
static void _clp_list(int argno);
static void _clp_liststruct(int argno);
extern void _clp_objectclass(int argno);
extern void _clp_objectini(int argno);
static void _clp_objectregister(int argno);
extern void _clp_padr(int argno);
extern void _clp_qout(int argno);
extern void _clp_valtype(int argno);

class _method6_asarray: public _method6_{public: _method6_asarray():_method6_("asarray"){};}; static _method6_asarray _o_method_asarray;
class _method6_attrnames: public _method6_{public: _method6_attrnames():_method6_("attrnames"){};}; static _method6_attrnames _o_method_attrnames;
class _method6_attrvals: public _method6_{public: _method6_attrvals():_method6_("attrvals"){};}; static _method6_attrvals _o_method_attrvals;
class _method6_struct: public _method6_{public: _method6_struct():_method6_("struct"){};}; static _method6_struct _o_method_struct;

static VALUE* _st_clid_object_ptr()
{
    static stvar _st_clid_object;
    static int _ini_clid_object=[=](){
        _clp_objectregister(0);
        assign(_st_clid_object.ptr);
        pop();
        return 1;
    }();
    return _st_clid_object.ptr;
}
//=======================================================================
void _clp_objectclass(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("objectclass",base);
//
    line(31);
    push_symbol(_st_clid_object_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_objectregister(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+1)PUSHNIL();
argno=0;
push_call("objectregister",base);
//
    line(35);
    string(L"object");
    push(&NIL);
    _clp_classregister(2);
    assign(base+0);//clid
    pop();
    line(37);
    push_symbol(base+0);//clid
    string(L"initialize");
    block(_blk_objectregister_0,0);
    _clp_classmethod(3);
    pop();
    line(38);
    push_symbol(base+0);//clid
    string(L"clean");
    block(_blk_objectregister_1,0);
    _clp_classmethod(3);
    pop();
    line(39);
    push_symbol(base+0);//clid
    string(L"classname");
    block(_blk_objectregister_2,0);
    _clp_classmethod(3);
    pop();
    line(40);
    push_symbol(base+0);//clid
    string(L"baseid");
    block(_blk_objectregister_3,0);
    _clp_classmethod(3);
    pop();
    line(41);
    push_symbol(base+0);//clid
    string(L"attrnames");
    block(_blk_objectregister_4,0);
    _clp_classmethod(3);
    pop();
    line(42);
    push_symbol(base+0);//clid
    string(L"methnames");
    block(_blk_objectregister_5,0);
    _clp_classmethod(3);
    pop();
    line(43);
    push_symbol(base+0);//clid
    string(L"length");
    block(_blk_objectregister_6,0);
    _clp_classmethod(3);
    pop();
    line(44);
    push_symbol(base+0);//clid
    string(L"struct");
    block(_blk_objectregister_7,0);
    _clp_classmethod(3);
    pop();
    line(45);
    push_symbol(base+0);//clid
    string(L"asarray");
    block(_blk_objectregister_8,0);
    _clp_classmethod(3);
    pop();
    line(46);
    push_symbol(base+0);//clid
    string(L"attrvals");
    block(_blk_objectregister_9,0);
    _clp_classmethod(3);
    pop();
    line(47);
    push_symbol(base+0);//clid
    string(L"list");
    block(_blk_objectregister_10,0);
    _clp_classmethod(3);
    pop();
    line(48);
    push_symbol(base+0);//clid
    string(L"liststruct");
    block(_blk_objectregister_11,0);
    _clp_classmethod(3);
    pop();
    line(49);
    push_symbol(base+0);//clid
    string(L"ancestors");
    block(_blk_objectregister_12,0);
    _clp_classmethod(3);
    pop();
    line(50);
    push_symbol(base+0);//clid
    string(L"isderivedfrom");
    block(_blk_objectregister_13,0);
    _clp_classmethod(3);
    pop();
    line(51);
    push_symbol(base+0);//clid
    string(L"evalmethod");
    block(_blk_objectregister_14,0);
    _clp_classmethod(3);
    pop();
    line(53);
    push_symbol(base+0);//clid
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_objectregister_0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_objectregister_0",base);
//
    push_symbol(base+1);//this
    _clp_objectini(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_1(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_objectregister_1",base);
//
    push_symbol(base+1);//this
    _clp_clean(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_2(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_objectregister_2",base);
//
    push_symbol(base+1);//this
    _clp_getclassid(1);
    _clp_classname(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_3(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_objectregister_3",base);
//
    push_symbol(base+1);//this
    _clp_getclassid(1);
    _clp_classbaseid(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_4(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_objectregister_4",base);
//
    push_symbol(base+1);//this
    _clp_getclassid(1);
    push_symbol(base+2);//id
    _clp_classattrnames(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_5(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_objectregister_5",base);
//
    push_symbol(base+1);//this
    _clp_getclassid(1);
    push_symbol(base+2);//id
    _clp_classmethnames(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_6(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_objectregister_6",base);
//
    push_symbol(base+1);//this
    _clp_getclassid(1);
    _clp_classobjectlength(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_7(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_objectregister_7",base);
//
    push_symbol(base+1);//this
    _clp_getclassid(1);
    _clp_classinheritstruct(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_8(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_objectregister_8",base);
//
    push_symbol(base+1);//this
    _clp_getobjectasarray(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_9(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_objectregister_9",base);
//
    push_symbol(base+1);//this
    _clp_attrvals(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_10(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_objectregister_10",base);
//
    push_symbol(base+1);//this
    _clp_list(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_11(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_objectregister_11",base);
//
    push_symbol(base+1);//this
    _clp_liststruct(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_12(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_objectregister_12",base);
//
    push_symbol(base+1);//this
    _clp_ancestors(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_13(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_objectregister_13",base);
//
    push_symbol(base+1);//this
    push_symbol(base+2);//o
    _clp_isderivedfrom(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_14(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+4)PUSHNIL();
argno=4;
push_call("_blk_objectregister_14",base);
//
    push_symbol(base+1);//this
    push_symbol(base+2);//meth
    push_symbol(base+3);//args
    _clp_evalmethod(3);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
void _clp_objectini(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("objectini",base);
//
    line(62);
    push_symbol(base+0);//this
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_clean(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("clean",base);
//
    line(67);
    line(70);
    {
    line(68);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_1_0:
    push_symbol(base+0);//this
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(69);
        push(&NIL);
        push_symbol(base+0);//this
        push_symbol(base+1);//n
        assign2(idxxl());
        pop();
    lab_1_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+1);//n
    add();
    assign(base+1);//n
    goto lab_1_0;
    lab_1_2:;
    }
    line(71);
    push_symbol(base+0);//this
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_attrvals(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+6)PUSHNIL();
argno=1;
push_call("attrvals",base);
//
    line(77);
    push_symbol(base+0);//this
    _o_method_attrnames.eval(1);
    assign(base+1);//names
    pop();
    line(78);
    push_symbol(base+0);//this
    _o_method_asarray.eval(1);
    assign(base+2);//values
    pop();
    line(79);
    push_symbol(base+1);//names
    _clp_len(1);
    assign(base+3);//acount
    pop();
    line(80);
    push_symbol(base+3);//acount
    _clp_array(1);
    assign(base+4);//anamevalue
    pop();
    line(84);
    {
    line(82);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+5);//i
    lab_2_0:
    push_symbol(base+3);//acount
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_2_2;
        line(83);
        push_symbol(base+1);//names
        push_symbol(base+5);//i
        idxr();
        push_symbol(base+2);//values
        push_symbol(base+5);//i
        idxr();
        array(2);
        push_symbol(base+4);//anamevalue
        push_symbol(base+5);//i
        assign2(idxxl());
        pop();
    lab_2_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+5);//i
    add();
    assign(base+5);//i
    goto lab_2_0;
    lab_2_2:;
    }
    line(86);
    push_symbol(base+4);//anamevalue
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_list(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("list",base);
//
    line(91);
    push_symbol(base+0);//this
    _o_method_attrvals.eval(1);
    assign(base+1);//attrvals
    pop();
    line(94);
    {
    line(92);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//i
    lab_3_0:
    push_symbol(base+1);//attrvals
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_3_2;
        line(93);
        push_symbol(base+2);//i
        push_symbol(base+1);//attrvals
        push_symbol(base+2);//i
        idxr();
        idxr0(1);
        number(24);
        _clp_padr(2);
        string(L"[");
        push_symbol(base+1);//attrvals
        push_symbol(base+2);//i
        idxr();
        idxr0(2);
        string(L"]");
        _clp_qout(5);
        pop();
    lab_3_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//i
    add();
    assign(base+2);//i
    goto lab_3_0;
    lab_3_2:;
    }
    line(95);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_liststruct(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("liststruct",base);
//
    line(100);
    push_symbol(base+0);//this
    _o_method_struct.eval(1);
    assign(base+1);//is
    pop();
    line(103);
    {
    line(101);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//i
    lab_4_0:
    push_symbol(base+1);//is
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
        line(102);
        push_symbol(base+2);//i
        push_symbol(base+1);//is
        push_symbol(base+2);//i
        idxr();
        idxr0(1);
        number(24);
        _clp_padr(2);
        push_symbol(base+1);//is
        push_symbol(base+2);//i
        idxr();
        idxr0(2);
        push_symbol(base+1);//is
        push_symbol(base+2);//i
        idxr();
        idxr0(3);
        _clp_classname(1);
        _clp_qout(4);
        pop();
    lab_4_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//i
    add();
    assign(base+2);//i
    goto lab_4_0;
    lab_4_2:;
    }
    line(104);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_ancestors(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+5)PUSHNIL();
argno=1;
push_call("ancestors",base);
//
    line(110);
    push_symbol(base+0);//this
    _clp_getclassid(1);
    array(1);
    assign(base+1);//a
    pop();
    line(111);
    push(&ZERO);
    assign(base+2);//n
    pop();
    line(120);
    lab_5_1:
    line(113);
    push_symbol(base+2);//n
    push(&ONE);
    add();
    assign(base+2);//n
    push_symbol(base+1);//a
    _clp_len(1);
    lteq();
    if(!flag()) goto lab_5_2;
        line(114);
        push_symbol(base+1);//a
        push_symbol(base+2);//n
        idxr();
        _clp_classbaseid(1);
        assign(base+3);//base
        pop();
        line(119);
        {
        line(115);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+4);//i
        lab_6_0:
        push_symbol(base+3);//base
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_6_2;
            line(118);
            line(116);
            push(&ZERO);
            push_symbol(base+1);//a
            push_symbol(base+3);//base
            push_symbol(base+4);//i
            idxr();
            _clp_ascan(2);
            eqeq();
            if(!flag()) goto if_7_1;
                line(117);
                push_symbol(base+1);//a
                push_symbol(base+3);//base
                push_symbol(base+4);//i
                idxr();
                _clp_aadd(2);
                pop();
            if_7_1:
            if_7_0:;
        lab_6_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+4);//i
        add();
        assign(base+4);//i
        goto lab_6_0;
        lab_6_2:;
        }
    goto lab_5_1;
    lab_5_2:;
    line(121);
    push_symbol(base+1);//a
    _clp_asort(1);
    pop();
    line(124);
    {
    line(122);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_8_0:
    push_symbol(base+1);//a
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_8_2;
        line(123);
        push_symbol(base+1);//a
        push_symbol(base+2);//n
        idxr();
        _clp_classname(1);
        push_symbol(base+1);//a
        push_symbol(base+2);//n
        assign2(idxxl());
        pop();
    lab_8_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_8_0;
    lab_8_2:;
    }
    line(125);
    push_symbol(base+1);//a
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_isderivedfrom(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("isderivedfrom",base);
//
    line(130);
    push_symbol(base+0);//this
    _clp_getclassid(1);
    assign(base+2);//cld
    pop();
    line(131);
    push_symbol(base+1);//o
    _clp_valtype(1);
    string(L"N");
    neeq();
    if(flag()){
    push_symbol(base+1);//o
    _clp_getclassid(1);
    }else{
    push_symbol(base+1);//o
    }
    assign(base+3);//clb
    pop();
    line(132);
    push_symbol(base+2);//cld
    push_symbol(base+3);//clb
    _clp_isderivedfrom1(2);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_isderivedfrom1(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("isderivedfrom1",base);
//
    line(136);
    line(146);
    line(137);
    push_symbol(base+1);//clb
    push_symbol(base+0);//cld
    eqeq();
    if(!flag()) goto if_9_1;
        line(138);
        push(&TRUE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_9_0;
    if_9_1:
    line(139);
        line(140);
        push_symbol(base+0);//cld
        _clp_classbaseid(1);
        assign(base+2);//baseid
        pop();
        line(145);
        {
        line(141);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+3);//n
        lab_10_0:
        push_symbol(base+2);//baseid
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_10_2;
            line(144);
            line(142);
            push_symbol(base+2);//baseid
            push_symbol(base+3);//n
            idxr();
            push_symbol(base+1);//clb
            _clp_isderivedfrom1(2);
            if(!flag()) goto if_11_1;
                line(143);
                push(&TRUE);
                {*base=*(stack-1);stack=base+1;pop_call();return;}
            if_11_1:
            if_11_0:;
        lab_10_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+3);//n
        add();
        assign(base+3);//n
        goto lab_10_0;
        lab_10_2:;
        }
    if_9_2:
    if_9_0:;
    line(147);
    push(&FALSE);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_evalmethod(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+7)PUSHNIL();
argno=3;
push_call("evalmethod",base);
//
    line(156);
    line(157);
    line(158);
    push_symbol(base+0);//this
    _clp_getclassid(1);
    push_symbol(base+1);//methname
    _clp_getmethod(2);
    assign(base+6);//blk
    pop();
    line(172);
    line(160);
    push_symbol(base+6);//blk
    _clp_valtype(1);
    string(L"N");
    eqeq();
    if(!flag()) goto if_12_1;
        line(165);
        line(161);
        push_symbol(base+2);//args
        _clp_len(1);
        push(&ONE);
        lt();
        if(!flag()) goto if_13_1;
            line(162);
            push_symbol(base+0);//this
            _o_method_asarray.eval(1);
            push_symbol(base+6);//blk
            idxr();
            assign(base+3);//ret
            pop();
        goto if_13_0;
        if_13_1:
        line(163);
            line(164);
            push_symbol(base+2);//args
            idxr0(1);
            push_symbol(base+0);//this
            _o_method_asarray.eval(1);
            push_symbol(base+6);//blk
            assign2(idxxl());
            assign(base+3);//ret
            pop();
        if_13_2:
        if_13_0:;
    goto if_12_0;
    if_12_1:
    line(166);
        line(167);
        push_symbol(base+0);//this
        array(1);
        assign(base+4);//par
        pop();
        line(170);
        {
        line(168);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+5);//n
        lab_14_0:
        push_symbol(base+2);//args
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_14_2;
            line(169);
            push_symbol(base+4);//par
            push_symbol(base+2);//args
            push_symbol(base+5);//n
            idxr();
            _clp_aadd(2);
            pop();
        lab_14_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+5);//n
        add();
        assign(base+5);//n
        goto lab_14_0;
        lab_14_2:;
        }
        line(171);
        push_symbol(base+6);//blk
        push_symbol(base+4);//par
        _clp_evalarray(2);
        assign(base+3);//ret
        pop();
    if_12_2:
    if_12_0:;
    line(173);
    push_symbol(base+3);//ret
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

