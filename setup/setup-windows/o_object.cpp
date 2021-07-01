//input: o_object.ppo (5.2.0)

#include <cccdef.h>

static void _blk_objectregister_0(int argno);
static void _blk_objectregister_1(int argno);
static void _blk_objectregister_10(int argno);
static void _blk_objectregister_11(int argno);
static void _blk_objectregister_12(int argno);
static void _blk_objectregister_13(int argno);
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
static void _ini__clid_object();

class _method6_asarray: public _method6_{public: _method6_asarray():_method6_("asarray"){};}; static _method6_asarray _o_method_asarray;
class _method6_attrnames: public _method6_{public: _method6_attrnames():_method6_("attrnames"){};}; static _method6_attrnames _o_method_attrnames;
class _method6_attrvals: public _method6_{public: _method6_attrvals():_method6_("attrvals"){};}; static _method6_attrvals _o_method_attrvals;
class _method6_struct: public _method6_{public: _method6_struct():_method6_("struct"){};}; static _method6_struct _o_method_struct;

MUTEX_CREATE(_mutex_clid_object);
static VALUE* _st_clid_object_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_clid_object);
    static stvar _st_clid_object(_ini__clid_object);
    MUTEX_UNLOCK(_mutex_clid_object);
    SIGNAL_UNLOCK();
    return _st_clid_object.ptr;
}

static void _ini__clid_object()
{
    _clp_objectregister(0);
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
    string(L"classname");
    block(_blk_objectregister_1,0);
    _clp_classmethod(3);
    pop();
    line(39);
    push_symbol(base+0);//clid
    string(L"baseid");
    block(_blk_objectregister_2,0);
    _clp_classmethod(3);
    pop();
    line(40);
    push_symbol(base+0);//clid
    string(L"attrnames");
    block(_blk_objectregister_3,0);
    _clp_classmethod(3);
    pop();
    line(41);
    push_symbol(base+0);//clid
    string(L"methnames");
    block(_blk_objectregister_4,0);
    _clp_classmethod(3);
    pop();
    line(42);
    push_symbol(base+0);//clid
    string(L"length");
    block(_blk_objectregister_5,0);
    _clp_classmethod(3);
    pop();
    line(43);
    push_symbol(base+0);//clid
    string(L"struct");
    block(_blk_objectregister_6,0);
    _clp_classmethod(3);
    pop();
    line(44);
    push_symbol(base+0);//clid
    string(L"asarray");
    block(_blk_objectregister_7,0);
    _clp_classmethod(3);
    pop();
    line(45);
    push_symbol(base+0);//clid
    string(L"attrvals");
    block(_blk_objectregister_8,0);
    _clp_classmethod(3);
    pop();
    line(46);
    push_symbol(base+0);//clid
    string(L"list");
    block(_blk_objectregister_9,0);
    _clp_classmethod(3);
    pop();
    line(47);
    push_symbol(base+0);//clid
    string(L"liststruct");
    block(_blk_objectregister_10,0);
    _clp_classmethod(3);
    pop();
    line(48);
    push_symbol(base+0);//clid
    string(L"ancestors");
    block(_blk_objectregister_11,0);
    _clp_classmethod(3);
    pop();
    line(49);
    push_symbol(base+0);//clid
    string(L"isderivedfrom");
    block(_blk_objectregister_12,0);
    _clp_classmethod(3);
    pop();
    line(50);
    push_symbol(base+0);//clid
    string(L"evalmethod");
    block(_blk_objectregister_13,0);
    _clp_classmethod(3);
    pop();
    line(52);
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
    push_blkarg(base+1);//this
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
    push_blkarg(base+1);//this
    _clp_getclassid(1);
    _clp_classname(1);
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
    push_blkarg(base+1);//this
    _clp_getclassid(1);
    _clp_classbaseid(1);
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
    push_blkarg(base+1);//this
    _clp_getclassid(1);
    _clp_classattrnames(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_4(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_objectregister_4",base);
//
    push_blkarg(base+1);//this
    _clp_getclassid(1);
    _clp_classmethnames(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_5(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_objectregister_5",base);
//
    push_blkarg(base+1);//this
    _clp_getclassid(1);
    _clp_classobjectlength(1);
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
    push_blkarg(base+1);//this
    _clp_getclassid(1);
    _clp_classinheritstruct(1);
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
    push_blkarg(base+1);//this
    _clp_getobjectasarray(1);
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
    push_blkarg(base+1);//this
    _clp_attrvals(1);
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
    push_blkarg(base+1);//this
    _clp_list(1);
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
    push_blkarg(base+1);//this
    _clp_liststruct(1);
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
    push_blkarg(base+1);//this
    _clp_ancestors(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_12(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_objectregister_12",base);
//
    push_blkarg(base+1);//this
    push_blkarg(base+2);//o
    _clp_isderivedfrom(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_objectregister_13(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+4)PUSHNIL();
argno=4;
push_call("_blk_objectregister_13",base);
//
    push_blkarg(base+1);//this
    push_blkarg(base+2);//meth
    push_blkarg(base+3);//args
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
    line(61);
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
    line(67);
    push_symbol(base+0);//this
    _o_method_attrnames.eval(1);
    assign(base+1);//names
    pop();
    line(68);
    push_symbol(base+0);//this
    _o_method_asarray.eval(1);
    assign(base+2);//values
    pop();
    line(69);
    push_symbol(base+1);//names
    _clp_len(1);
    assign(base+3);//acount
    pop();
    line(70);
    push_symbol(base+3);//acount
    _clp_array(1);
    assign(base+4);//anamevalue
    pop();
    line(74);
    {
    line(72);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+5);//i
    lab_1_0:
    push_symbol(base+3);//acount
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(73);
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
    lab_1_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+5);//i
    add();
    assign(base+5);//i
    goto lab_1_0;
    lab_1_2:;
    }
    line(76);
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
    line(81);
    push_symbol(base+0);//this
    _o_method_attrvals.eval(1);
    assign(base+1);//attrvals
    pop();
    line(84);
    {
    line(82);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//i
    lab_2_0:
    push_symbol(base+1);//attrvals
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_2_2;
        line(83);
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
    lab_2_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//i
    add();
    assign(base+2);//i
    goto lab_2_0;
    lab_2_2:;
    }
    line(85);
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
    line(90);
    push_symbol(base+0);//this
    _o_method_struct.eval(1);
    assign(base+1);//is
    pop();
    line(93);
    {
    line(91);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//i
    lab_3_0:
    push_symbol(base+1);//is
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_3_2;
        line(92);
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
    line(94);
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
while(stack<base+7)PUSHNIL();
argno=1;
push_call("ancestors",base);
//
    line(100);
    push_symbol(base+0);//this
    _clp_getclassid(1);
    assign(base+1);//clid
    pop();
    line(101);
    push_symbol(base+1);//clid
    _clp_classinheritstruct(1);
    assign(base+2);//is
    pop();
    line(102);
    array(0);
    assign(base+4);//a
    pop();
    line(118);
    {
    line(104);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_4_0:
    push_symbol(base+2);//is
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
        line(106);
        push(&FALSE);
        assign(base+6);//van
        pop();
        line(113);
        {
        line(108);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+5);//i
        lab_5_0:
        push_symbol(base+4);//a
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_5_2;
            line(112);
            line(109);
            push_symbol(base+2);//is
            push_symbol(base+3);//n
            idxr();
            idxr0(3);
            push_symbol(base+4);//a
            push_symbol(base+5);//i
            idxr();
            eqeq();
            if(!flag()) goto if_6_1;
                line(110);
                push(&TRUE);
                assign(base+6);//van
                pop();
                line(111);
                goto lab_5_2;//exit
            if_6_1:
            if_6_0:;
        lab_5_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+5);//i
        add();
        assign(base+5);//i
        goto lab_5_0;
        lab_5_2:;
        }
        line(117);
        line(115);
        push_symbol(base+6);//van
        topnot();
        if(!flag()) goto if_7_1;
            line(116);
            push_symbol(base+4);//a
            push_symbol(base+2);//is
            push_symbol(base+3);//n
            idxr();
            idxr0(3);
            _clp_aadd(2);
            pop();
        if_7_1:
        if_7_0:;
    lab_4_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_4_0;
    lab_4_2:;
    }
    line(120);
    push_symbol(base+4);//a
    _clp_asort(1);
    pop();
    line(124);
    {
    line(122);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+5);//i
    lab_8_0:
    push_symbol(base+4);//a
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_8_2;
        line(123);
        push_symbol(base+4);//a
        push_symbol(base+5);//i
        idxr();
        _clp_classname(1);
        push_symbol(base+4);//a
        push_symbol(base+5);//i
        assign2(idxxl());
        pop();
    lab_8_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+5);//i
    add();
    assign(base+5);//i
    goto lab_8_0;
    lab_8_2:;
    }
    line(126);
    push_symbol(base+4);//a
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
    line(131);
    push_symbol(base+0);//this
    _clp_getclassid(1);
    assign(base+2);//cld
    pop();
    line(132);
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
    line(133);
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
    line(137);
    line(147);
    line(138);
    push_symbol(base+1);//clb
    push_symbol(base+0);//cld
    eqeq();
    if(!flag()) goto if_9_1;
        line(139);
        push(&TRUE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_9_0;
    if_9_1:
    line(140);
        line(141);
        push_symbol(base+0);//cld
        _clp_classbaseid(1);
        assign(base+2);//baseid
        pop();
        line(146);
        {
        line(142);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+3);//n
        lab_10_0:
        push_symbol(base+2);//baseid
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_10_2;
            line(145);
            line(143);
            push_symbol(base+2);//baseid
            push_symbol(base+3);//n
            idxr();
            push_symbol(base+1);//clb
            _clp_isderivedfrom1(2);
            if(!flag()) goto if_11_1;
                line(144);
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
    line(148);
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
    line(157);
    line(158);
    line(159);
    push_symbol(base+0);//this
    _clp_getclassid(1);
    push_symbol(base+1);//methname
    _clp_getmethod(2);
    assign(base+6);//blk
    pop();
    line(173);
    line(161);
    push_symbol(base+6);//blk
    _clp_valtype(1);
    string(L"N");
    eqeq();
    if(!flag()) goto if_12_1;
        line(166);
        line(162);
        push_symbol(base+2);//args
        _clp_len(1);
        push(&ONE);
        lt();
        if(!flag()) goto if_13_1;
            line(163);
            push_symbol(base+0);//this
            _o_method_asarray.eval(1);
            push_symbol(base+6);//blk
            idxr();
            assign(base+3);//ret
            pop();
        goto if_13_0;
        if_13_1:
        line(164);
            line(165);
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
    line(167);
        line(168);
        push_symbol(base+0);//this
        array(1);
        assign(base+4);//par
        pop();
        line(171);
        {
        line(169);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+5);//n
        lab_14_0:
        push_symbol(base+2);//args
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_14_2;
            line(170);
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
        line(172);
        push_symbol(base+6);//blk
        push_symbol(base+4);//par
        _clp_evalarray(2);
        assign(base+3);//ret
        pop();
    if_12_2:
    if_12_0:;
    line(174);
    push_symbol(base+3);//ret
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

