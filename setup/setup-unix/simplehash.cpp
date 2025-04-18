//input: ppo/simplehash.ppo (5.7.0.1)

#include <cccdef.h>

static void _blk_simplehashregister_0(int argno);
static void _blk_simplehashregister_1(int argno);
static void _blk_simplehashregister_10(int argno);
static void _blk_simplehashregister_11(int argno);
static void _blk_simplehashregister_12(int argno);
static void _blk_simplehashregister_13(int argno);
static void _blk_simplehashregister_14(int argno);
static void _blk_simplehashregister_15(int argno);
static void _blk_simplehashregister_16(int argno);
static void _blk_simplehashregister_17(int argno);
static void _blk_simplehashregister_18(int argno);
static void _blk_simplehashregister_19(int argno);
static void _blk_simplehashregister_2(int argno);
static void _blk_simplehashregister_20(int argno);
static void _blk_simplehashregister_3(int argno);
static void _blk_simplehashregister_4(int argno);
static void _blk_simplehashregister_5(int argno);
static void _blk_simplehashregister_6(int argno);
static void _blk_simplehashregister_7(int argno);
static void _blk_simplehashregister_8(int argno);
static void _blk_simplehashregister_9(int argno);
extern void _clp_array(int argno);
extern void _clp_classattrib(int argno);
extern void _clp_classmethod(int argno);
extern void _clp_classregister(int argno);
static void _clp_hash_index(int argno);
extern void _clp_hashcode(int argno);
extern void _clp_len(int argno);
extern void _clp_max(int argno);
extern void _clp_objectclass(int argno);
extern void _clp_objectnew(int argno);
extern void _clp_qout(int argno);
extern void _clp_simplehashclass(int argno);
extern void _clp_simplehashnew(int argno);
static void _clp_simplehashregister(int argno);
extern void _clp_valtype(int argno);

namespace _nsp_simplehash{
static void _clp_clear(int argno);
static void _clp_clone(int argno);
static void _clp_first(int argno);
static void _clp_firstkey(int argno);
static void _clp_firstvalue(int argno);
static void _clp_get(int argno);
static void _clp_hashitem(int argno);
static void _clp_initialize(int argno);
static void _clp_list(int argno);
static void _clp_listkey(int argno);
static void _clp_listvalue(int argno);
static void _clp_next(int argno);
static void _clp_nextkey(int argno);
static void _clp_nextvalue(int argno);
static void _clp_rehash(int argno);
static void _clp_remove(int argno);
static void _clp_set(int argno);
static void _clp_toarr(int argno);
static void _clp_toarrkey(int argno);
static void _clp_toarrvalue(int argno);
static void _clp_valuecount(int argno);
}//namespace simplehash

class _method6_first: public _method6_{public: _method6_first():_method6_("first"){};}; static _method6_first _o_method_first;
class _method6_firstkey: public _method6_{public: _method6_firstkey():_method6_("firstkey"){};}; static _method6_firstkey _o_method_firstkey;
class _method6_firstvalue: public _method6_{public: _method6_firstvalue():_method6_("firstvalue"){};}; static _method6_firstvalue _o_method_firstvalue;
class _method6_hasharray: public _method6_{public: _method6_hasharray():_method6_("hasharray"){};}; static _method6_hasharray _o_method_hasharray;
class _method6_hashitem: public _method6_{public: _method6_hashitem():_method6_("hashitem"){};}; static _method6_hashitem _o_method_hashitem;
class _method6_initialize: public _method6_{public: _method6_initialize():_method6_("initialize"){};}; static _method6_initialize _o_method_initialize;
class _method6_initialize_C_object: public _method6c_{public: _method6_initialize_C_object():_method6c_("initialize",_clp_objectclass){};}; static _method6_initialize_C_object _o_method_initialize_C_object;
class _method6_initsize: public _method6_{public: _method6_initsize():_method6_("initsize"){};}; static _method6_initsize _o_method_initsize;
class _method6_itemcount: public _method6_{public: _method6_itemcount():_method6_("itemcount"){};}; static _method6_itemcount _o_method_itemcount;
class _method6_iteridx: public _method6_{public: _method6_iteridx():_method6_("iteridx"){};}; static _method6_iteridx _o_method_iteridx;
class _method6_next: public _method6_{public: _method6_next():_method6_("next"){};}; static _method6_next _o_method_next;
class _method6_nextkey: public _method6_{public: _method6_nextkey():_method6_("nextkey"){};}; static _method6_nextkey _o_method_nextkey;
class _method6_nextvalue: public _method6_{public: _method6_nextvalue():_method6_("nextvalue"){};}; static _method6_nextvalue _o_method_nextvalue;
class _method6_rehash: public _method6_{public: _method6_rehash():_method6_("rehash"){};}; static _method6_rehash _o_method_rehash;
class _method6_set: public _method6_{public: _method6_set():_method6_("set"){};}; static _method6_set _o_method_set;
class _method6_valuecount: public _method6_{public: _method6_valuecount():_method6_("valuecount"){};}; static _method6_valuecount _o_method_valuecount;

//=======================================================================

static VALUE* _st_clid_simplehash_ptr()
{
    static stvar _st_clid_simplehash;
    static int _ini_clid_simplehash=[=](){
        _clp_simplehashregister(0);
        assign(_st_clid_simplehash.ptr);
        pop();
        return 1;
    }();
    return _st_clid_simplehash.ptr;
}
//=======================================================================
void _clp_simplehashclass(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("simplehashclass",base);
//
    line(4);
    push_symbol(_st_clid_simplehash_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_simplehashregister(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+1)PUSHNIL();
argno=0;
push_call("simplehashregister",base);
//
    line(7);
    string(L"simplehash");
    ::_clp_objectclass(0);
    array(1);
    _clp_classregister(2);
    assign(base+0);//clid
    pop();
    line(8);
    push_symbol(base+0);//clid
    string(L"hasharray");
    _clp_classattrib(2);
    pop();
    line(9);
    push_symbol(base+0);//clid
    string(L"initsize");
    _clp_classattrib(2);
    pop();
    line(10);
    push_symbol(base+0);//clid
    string(L"itemcount");
    _clp_classattrib(2);
    pop();
    line(11);
    push_symbol(base+0);//clid
    string(L"iteridx");
    _clp_classattrib(2);
    pop();
    line(12);
    push_symbol(base+0);//clid
    string(L"initialize");
    block(_blk_simplehashregister_0,0);
    _clp_classmethod(3);
    pop();
    line(13);
    push_symbol(base+0);//clid
    string(L"hashitem");
    block(_blk_simplehashregister_1,0);
    _clp_classmethod(3);
    pop();
    line(14);
    push_symbol(base+0);//clid
    string(L"rehash");
    block(_blk_simplehashregister_2,0);
    _clp_classmethod(3);
    pop();
    line(15);
    push_symbol(base+0);//clid
    string(L"valuecount");
    block(_blk_simplehashregister_3,0);
    _clp_classmethod(3);
    pop();
    line(16);
    push_symbol(base+0);//clid
    string(L"clone");
    block(_blk_simplehashregister_4,0);
    _clp_classmethod(3);
    pop();
    line(17);
    push_symbol(base+0);//clid
    string(L"clear");
    block(_blk_simplehashregister_5,0);
    _clp_classmethod(3);
    pop();
    line(18);
    push_symbol(base+0);//clid
    string(L"set");
    block(_blk_simplehashregister_6,0);
    _clp_classmethod(3);
    pop();
    line(19);
    push_symbol(base+0);//clid
    string(L"get");
    block(_blk_simplehashregister_7,0);
    _clp_classmethod(3);
    pop();
    line(20);
    push_symbol(base+0);//clid
    string(L"remove");
    block(_blk_simplehashregister_8,0);
    _clp_classmethod(3);
    pop();
    line(21);
    push_symbol(base+0);//clid
    string(L"first");
    block(_blk_simplehashregister_9,0);
    _clp_classmethod(3);
    pop();
    line(22);
    push_symbol(base+0);//clid
    string(L"firstkey");
    block(_blk_simplehashregister_10,0);
    _clp_classmethod(3);
    pop();
    line(23);
    push_symbol(base+0);//clid
    string(L"firstvalue");
    block(_blk_simplehashregister_11,0);
    _clp_classmethod(3);
    pop();
    line(24);
    push_symbol(base+0);//clid
    string(L"next");
    block(_blk_simplehashregister_12,0);
    _clp_classmethod(3);
    pop();
    line(25);
    push_symbol(base+0);//clid
    string(L"nextkey");
    block(_blk_simplehashregister_13,0);
    _clp_classmethod(3);
    pop();
    line(26);
    push_symbol(base+0);//clid
    string(L"nextvalue");
    block(_blk_simplehashregister_14,0);
    _clp_classmethod(3);
    pop();
    line(27);
    push_symbol(base+0);//clid
    string(L"list");
    block(_blk_simplehashregister_15,0);
    _clp_classmethod(3);
    pop();
    line(28);
    push_symbol(base+0);//clid
    string(L"listkey");
    block(_blk_simplehashregister_16,0);
    _clp_classmethod(3);
    pop();
    line(29);
    push_symbol(base+0);//clid
    string(L"listvalue");
    block(_blk_simplehashregister_17,0);
    _clp_classmethod(3);
    pop();
    line(30);
    push_symbol(base+0);//clid
    string(L"toarr");
    block(_blk_simplehashregister_18,0);
    _clp_classmethod(3);
    pop();
    line(31);
    push_symbol(base+0);//clid
    string(L"toarrkey");
    block(_blk_simplehashregister_19,0);
    _clp_classmethod(3);
    pop();
    line(32);
    push_symbol(base+0);//clid
    string(L"toarrvalue");
    block(_blk_simplehashregister_20,0);
    _clp_classmethod(3);
    pop();
    line(33);
    push_symbol(base+0);//clid
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_simplehashregister_0(int argno)
{
//
    _nsp_simplehash::_clp_initialize(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_1(int argno)
{
//
    _nsp_simplehash::_clp_hashitem(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_2(int argno)
{
//
    _nsp_simplehash::_clp_rehash(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_3(int argno)
{
//
    _nsp_simplehash::_clp_valuecount(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_4(int argno)
{
//
    _nsp_simplehash::_clp_clone(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_5(int argno)
{
//
    _nsp_simplehash::_clp_clear(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_6(int argno)
{
//
    _nsp_simplehash::_clp_set(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_7(int argno)
{
//
    _nsp_simplehash::_clp_get(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_8(int argno)
{
//
    _nsp_simplehash::_clp_remove(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_9(int argno)
{
//
    _nsp_simplehash::_clp_first(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_10(int argno)
{
//
    _nsp_simplehash::_clp_firstkey(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_11(int argno)
{
//
    _nsp_simplehash::_clp_firstvalue(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_12(int argno)
{
//
    _nsp_simplehash::_clp_next(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_13(int argno)
{
//
    _nsp_simplehash::_clp_nextkey(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_14(int argno)
{
//
    _nsp_simplehash::_clp_nextvalue(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_15(int argno)
{
//
    _nsp_simplehash::_clp_list(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_16(int argno)
{
//
    _nsp_simplehash::_clp_listkey(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_17(int argno)
{
//
    _nsp_simplehash::_clp_listvalue(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_18(int argno)
{
//
    _nsp_simplehash::_clp_toarr(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_19(int argno)
{
//
    _nsp_simplehash::_clp_toarrkey(argno-1);
//
*(stack-2)=*(stack-1);pop();
}

static void _blk_simplehashregister_20(int argno)
{
//
    _nsp_simplehash::_clp_toarrvalue(argno-1);
//
*(stack-2)=*(stack-1);pop();
}
//=======================================================================
void _clp_simplehashnew(int argno)
{
    push(_st_clid_simplehash_ptr());
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
namespace _nsp_simplehash{
static void _clp_initialize(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("simplehash.initialize",base);
//
    line(70);
    line(72);
    push_symbol(base+0);//this
    _o_method_initialize_C_object.eval(1);
    pop();
    line(74);
    push_symbol(base+0);//this
    push(&ZERO);
    _o_method_itemcount.eval(2);
    pop();
    line(93);
    line(76);
    push_symbol(base+1);//data
    _clp_valtype(1);
    string(L"U");
    eqeq();
    cmp_1409:;
    if(!flag()) goto if_1_1;
        line(77);
        push_symbol(base+0);//this
        number(256);
        _o_method_initsize.eval(2);
        pop();
        line(78);
        push_symbol(base+0);//this
        push_symbol(base+0);//this
        _o_method_initsize.eval(1);
        _clp_array(1);
        _o_method_hasharray.eval(2);
        pop();
    goto if_1_0;
    if_1_1:
    line(80);
    push_symbol(base+1);//data
    _clp_valtype(1);
    string(L"N");
    eqeq();
    cmp_1471:;
    if(!flag()) goto if_1_2;
        line(81);
        push_symbol(base+0);//this
        push_symbol(base+1);//data
        number(4);
        _clp_max(2);
        _o_method_initsize.eval(2);
        pop();
        line(82);
        push_symbol(base+0);//this
        push_symbol(base+0);//this
        _o_method_initsize.eval(1);
        _clp_array(1);
        _o_method_hasharray.eval(2);
        pop();
    goto if_1_0;
    if_1_2:
    line(84);
        line(85);
        push_symbol(base+0);//this
        push_symbol(base+1);//data
        _o_method_initsize.eval(1);
        _o_method_initsize.eval(2);
        pop();
        line(86);
        push_symbol(base+0);//this
        push_symbol(base+0);//this
        _o_method_initsize.eval(1);
        _clp_array(1);
        _o_method_hasharray.eval(2);
        pop();
        line(88);
        push_symbol(base+1);//data
        _o_method_first.eval(1);
        assign(base+2);//item
        pop();
        line(92);
        lab_2_1:
        line(89);
        push(&NIL);
        push_symbol(base+2);//item
        neeq();
        cmp_1600:;
        if(!flag()) goto lab_2_2;
            line(90);
            push_symbol(base+0);//this
            push_symbol(base+2);//item
            idxr0(1);
            push_symbol(base+2);//item
            idxr0(2);
            _o_method_set.eval(3);
            pop();
            line(91);
            push_symbol(base+1);//data
            _o_method_next.eval(1);
            assign(base+2);//item
            pop();
        goto lab_2_1;
        lab_2_2:;
    if_1_3:
    if_1_0:;
    line(94);
    push_symbol(base+0);//this
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_hashitem(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("simplehash.hashitem",base);
//
    line(98);
    push_symbol(base+0);//this
    _o_method_hasharray.eval(1);
    push_symbol(base+1);//key
    _clp_hash_index(2);
    assign(base+2);//x
    pop();
    line(106);
    line(99);
    push_symbol(base+0);//this
    _o_method_hasharray.eval(1);
    push_symbol(base+2);//x
    idxr();
    push(&NIL);
    eqeq();
    cmp_1743:;
    if(!flag()) goto if_3_1;
        line(103);
        line(100);
        push_symbol(base+0);//this
        _o_method_itemcount.eval(1);
        push_symbol(base+0);//this
        _o_method_hasharray.eval(1);
        _clp_len(1);
        mulnum(0.66666);
        gteq();
        cmp_1761:;
        if(!flag()) goto if_4_1;
            line(101);
            push_symbol(base+0);//this
            _o_method_rehash.eval(1);
            pop();
            line(102);
            push_symbol(base+0);//this
            _o_method_hasharray.eval(1);
            push_symbol(base+1);//key
            _clp_hash_index(2);
            assign(base+2);//x
            pop();
        if_4_1:
        if_4_0:;
        line(104);
        push_symbol(base+1);//key
        push(&NIL);
        array(2);
        push_symbol(base+0);//this
        _o_method_hasharray.eval(1);
        push_symbol(base+2);//x
        assign2(idxxl());
        pop();
        line(105);
        push_symbol(base+0);//this
        _o_method_itemcount.eval(1);
        dup();
        push(&ONE);
        add();
        push_symbol(base+0);//this
        swap();
        _o_method_itemcount.eval(2);
        pop();
        pop();
    if_3_1:
    if_3_0:;
    line(107);
    push_symbol(base+0);//this
    _o_method_hasharray.eval(1);
    push_symbol(base+2);//x
    idxr();
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_rehash(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+8)PUSHNIL();
argno=1;
push_call("simplehash.rehash",base);
//
    line(112);
    push_symbol(base+0);//this
    _o_method_hasharray.eval(1);
    assign(base+1);//ha
    pop();
    push_symbol(base+1);//ha
    _clp_len(1);
    assign(base+2);//len
    pop();
    line(113);
    push_symbol(base+2);//len
    assign(base+5);//len1
    pop();
    push_symbol(base+0);//this
    _o_method_valuecount.eval(1);
    assign(base+6);//vc
    pop();
    line(122);
    line(115);
    push_symbol(base+5);//len1
    push_symbol(base+6);//vc
    mulnum(2);
    lt();
    cmp_1991:;
    if(!flag()) goto if_5_1;
        line(116);
        push_symbol(base+5);//len1
        number(2);
        mul();
        assign(base+5);//len1
        pop();
    goto if_5_0;
    if_5_1:
    line(117);
        line(121);
        lab_6_1:
        line(118);
        push_symbol(base+5);//len1
        number(2);
        div();
        push_symbol(base+0);//this
        _o_method_initsize.eval(1);
        gteq();
        cmp_2029:;
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+5);//len1
        number(2);
        div();
        push_symbol(base+6);//vc
        mulnum(2);
        gteq();
        cmp_2044:;
        }
        if(!flag()) goto lab_6_2;
            line(120);
            push_symbol(base+5);//len1
            number(2);
            div();
            assign(base+5);//len1
            pop();
        goto lab_6_1;
        lab_6_2:;
    if_5_2:
    if_5_0:;
    line(124);
    push_symbol(base+5);//len1
    _clp_array(1);
    assign(base+4);//ha1
    pop();
    line(130);
    {
    line(125);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_7_0:
    push_symbol(base+2);//len
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_7_2;
        line(129);
        line(126);
        push_symbol(base+1);//ha
        push_symbol(base+3);//n
        idxr();
        push(&NIL);
        neeq();
        cmp_2120:;
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+1);//ha
        push_symbol(base+3);//n
        idxr();
        idxr0(2);
        push(&NIL);
        neeq();
        cmp_2137:;
        }
        if(!flag()) goto if_8_1;
            line(127);
            push_symbol(base+4);//ha1
            push_symbol(base+1);//ha
            push_symbol(base+3);//n
            idxr();
            idxr0(1);
            _clp_hash_index(2);
            assign(base+7);//x
            pop();
            line(128);
            push_symbol(base+1);//ha
            push_symbol(base+3);//n
            idxr();
            push_symbol(base+4);//ha1
            push_symbol(base+7);//x
            assign2(idxxl());
            pop();
        if_8_1:
        if_8_0:;
    lab_7_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_7_0;
    lab_7_2:;
    }
    line(134);
    push_symbol(base+0);//this
    push_symbol(base+6);//vc
    _o_method_itemcount.eval(2);
    pop();
    line(135);
    push_symbol(base+0);//this
    push_symbol(base+4);//ha1
    _o_method_hasharray.eval(2);
    pop();
    line(136);
    push_symbol(base+0);//this
    push(&NIL);
    _o_method_iteridx.eval(2);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_valuecount(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+5)PUSHNIL();
argno=1;
push_call("simplehash.valuecount",base);
//
    line(141);
    push_symbol(base+0);//this
    _o_method_hasharray.eval(1);
    assign(base+1);//ha
    pop();
    push_symbol(base+1);//ha
    _clp_len(1);
    assign(base+2);//len
    pop();
    push(&ZERO);
    assign(base+4);//vc
    pop();
    line(146);
    {
    line(142);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_9_0:
    push_symbol(base+2);//len
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_9_2;
        line(145);
        line(143);
        push_symbol(base+1);//ha
        push_symbol(base+3);//n
        idxr();
        push(&NIL);
        neeq();
        cmp_2338:;
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+1);//ha
        push_symbol(base+3);//n
        idxr();
        idxr0(2);
        push(&NIL);
        neeq();
        cmp_2355:;
        }
        if(!flag()) goto if_10_1;
            line(144);
            push_symbol(base+4);//vc
            dup();
            push(&ONE);
            add();
            assign(base+4);//vc
            pop();
            pop();
        if_10_1:
        if_10_0:;
    lab_9_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_9_0;
    lab_9_2:;
    }
    line(147);
    push_symbol(base+4);//vc
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_clone(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("simplehash.clone",base);
//
    line(151);
    push_symbol(base+0);//this
    _clp_simplehashnew(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_clear(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("simplehash.clear",base);
//
    line(155);
    push_symbol(base+0);//this
    push(&NIL);
    _o_method_iteridx.eval(2);
    pop();
    line(156);
    push_symbol(base+0);//this
    push(&ZERO);
    _o_method_itemcount.eval(2);
    pop();
    line(157);
    push_symbol(base+0);//this
    push_symbol(base+0);//this
    _o_method_initsize.eval(1);
    _clp_array(1);
    _o_method_hasharray.eval(2);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_set(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+4)PUSHNIL();
argno=3;
push_call("simplehash.set",base);
//
    line(161);
    push_symbol(base+0);//this
    push_symbol(base+1);//key
    _o_method_hashitem.eval(2);
    assign(base+3);//item
    pop();
    line(162);
    push_symbol(base+2);//value
    push_symbol(base+3);//item
    assign2(idxxl0(2));
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_get(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("simplehash.get",base);
//
    line(166);
    push_symbol(base+0);//this
    _o_method_hasharray.eval(1);
    push_symbol(base+1);//key
    _clp_hash_index(2);
    assign(base+2);//x
    pop();
    line(167);
    line(170);
    line(168);
    push_symbol(base+0);//this
    _o_method_hasharray.eval(1);
    push_symbol(base+2);//x
    idxr();
    push(&NIL);
    neeq();
    cmp_2641:;
    if(!flag()) goto if_11_1;
        line(169);
        push_symbol(base+0);//this
        _o_method_hasharray.eval(1);
        push_symbol(base+2);//x
        idxr();
        idxr0(2);
        assign(base+3);//value
        pop();
    if_11_1:
    if_11_0:;
    line(171);
    push_symbol(base+3);//value
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_remove(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("simplehash.remove",base);
//
    line(175);
    push_symbol(base+0);//this
    _o_method_hasharray.eval(1);
    push_symbol(base+1);//key
    _clp_hash_index(2);
    assign(base+2);//x
    pop();
    line(176);
    line(180);
    line(177);
    push_symbol(base+0);//this
    _o_method_hasharray.eval(1);
    push_symbol(base+2);//x
    idxr();
    push(&NIL);
    neeq();
    cmp_2766:;
    if(!flag()) goto if_12_1;
        line(178);
        push_symbol(base+0);//this
        _o_method_hasharray.eval(1);
        push_symbol(base+2);//x
        idxr();
        idxr0(2);
        assign(base+3);//value
        pop();
        line(179);
        push(&NIL);
        push_symbol(base+0);//this
        _o_method_hasharray.eval(1);
        push_symbol(base+2);//x
        idxr();
        assign2(idxxl0(2));
        pop();
    if_12_1:
    if_12_0:;
    line(181);
    push_symbol(base+3);//value
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_first(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("simplehash.first",base);
//
    line(185);
    push_symbol(base+0);//this
    push(&ZERO);
    _o_method_iteridx.eval(2);
    pop();
    line(186);
    push_symbol(base+0);//this
    _o_method_next.eval(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_firstkey(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("simplehash.firstkey",base);
//
    line(190);
    push_symbol(base+0);//this
    push(&ZERO);
    _o_method_iteridx.eval(2);
    pop();
    line(191);
    push_symbol(base+0);//this
    _o_method_nextkey.eval(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_firstvalue(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("simplehash.firstvalue",base);
//
    line(195);
    push_symbol(base+0);//this
    push(&ZERO);
    _o_method_iteridx.eval(2);
    pop();
    line(196);
    push_symbol(base+0);//this
    _o_method_nextvalue.eval(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_next(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("simplehash.next",base);
//
    line(200);
    line(205);
    lab_13_1:
    line(201);
    push_symbol(base+0);//this
    _o_method_iteridx.eval(1);
    push(&ONE);
    add();
    push_symbol(base+0);//this
    swap();
    _o_method_iteridx.eval(2);
    assign(base+1);//i
    push_symbol(base+0);//this
    _o_method_hasharray.eval(1);
    _clp_len(1);
    lteq();
    cmp_3018:;
    if(!flag()) goto lab_13_2;
        line(204);
        line(202);
        push_symbol(base+0);//this
        _o_method_hasharray.eval(1);
        push_symbol(base+1);//i
        idxr();
        push(&NIL);
        neeq();
        cmp_3053:;
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+0);//this
        _o_method_hasharray.eval(1);
        push_symbol(base+1);//i
        idxr();
        idxr0(2);
        push(&NIL);
        neeq();
        cmp_3074:;
        }
        if(!flag()) goto if_14_1;
            line(203);
            push_symbol(base+0);//this
            _o_method_hasharray.eval(1);
            push_symbol(base+1);//i
            idxr();
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_14_1:
        if_14_0:;
    goto lab_13_1;
    lab_13_2:;
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_nextkey(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("simplehash.nextkey",base);
//
    line(209);
    push_symbol(base+0);//this
    _o_method_next.eval(1);
    assign(base+1);//x
    pop();
    line(210);
    push_symbol(base+1);//x
    push(&NIL);
    eqeq();
    cmp_3155:;
    if(flag()){
    push(&NIL);
    }else{
    push_symbol(base+1);//x
    idxr0(1);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_nextvalue(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("simplehash.nextvalue",base);
//
    line(214);
    push_symbol(base+0);//this
    _o_method_next.eval(1);
    assign(base+1);//x
    pop();
    line(215);
    push_symbol(base+1);//x
    push(&NIL);
    eqeq();
    cmp_3216:;
    if(flag()){
    push(&NIL);
    }else{
    push_symbol(base+1);//x
    idxr0(2);
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_list(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("simplehash.list",base);
//
    line(220);
    push_symbol(base+0);//this
    _o_method_first.eval(1);
    assign(base+1);//item
    pop();
    line(224);
    lab_15_1:
    line(221);
    push_symbol(base+1);//item
    push(&NIL);
    neeq();
    cmp_3276:;
    if(!flag()) goto lab_15_2;
        line(222);
        push_symbol(base+1);//item
        _clp_qout(1);
        pop();
        line(223);
        push_symbol(base+0);//this
        _o_method_next.eval(1);
        assign(base+1);//item
        pop();
    goto lab_15_1;
    lab_15_2:;
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_listkey(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("simplehash.listkey",base);
//
    line(228);
    push_symbol(base+0);//this
    _o_method_firstkey.eval(1);
    assign(base+1);//item
    pop();
    line(232);
    lab_16_1:
    line(229);
    push_symbol(base+1);//item
    push(&NIL);
    neeq();
    cmp_3358:;
    if(!flag()) goto lab_16_2;
        line(230);
        push_symbol(base+1);//item
        _clp_qout(1);
        pop();
        line(231);
        push_symbol(base+0);//this
        _o_method_nextkey.eval(1);
        assign(base+1);//item
        pop();
    goto lab_16_1;
    lab_16_2:;
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_listvalue(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("simplehash.listvalue",base);
//
    line(236);
    push_symbol(base+0);//this
    _o_method_firstvalue.eval(1);
    assign(base+1);//item
    pop();
    line(240);
    lab_17_1:
    line(237);
    push_symbol(base+1);//item
    push(&NIL);
    neeq();
    cmp_3440:;
    if(!flag()) goto lab_17_2;
        line(238);
        push_symbol(base+1);//item
        _clp_qout(1);
        pop();
        line(239);
        push_symbol(base+0);//this
        _o_method_nextvalue.eval(1);
        assign(base+1);//item
        pop();
    goto lab_17_1;
    lab_17_2:;
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_toarr(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+4)PUSHNIL();
argno=1;
push_call("simplehash.toarr",base);
//
    line(244);
    push(&ZERO);
    assign(base+3);//cnt
    pop();
    line(245);
    push_symbol(base+0);//this
    _o_method_valuecount.eval(1);
    _clp_array(1);
    assign(base+1);//arr
    pop();
    line(246);
    push_symbol(base+0);//this
    _o_method_first.eval(1);
    assign(base+2);//item
    pop();
    line(250);
    lab_18_1:
    line(247);
    push_symbol(base+2);//item
    push(&NIL);
    neeq();
    cmp_3562:;
    if(!flag()) goto lab_18_2;
        line(248);
        push_symbol(base+2);//item
        push_symbol(base+1);//arr
        push_symbol(base+3);//cnt
        push(&ONE);
        add();
        assign(base+3);//cnt
        assign2(idxxl());
        pop();
        line(249);
        push_symbol(base+0);//this
        _o_method_next.eval(1);
        assign(base+2);//item
        pop();
    goto lab_18_1;
    lab_18_2:;
    line(251);
    push_symbol(base+1);//arr
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_toarrkey(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+4)PUSHNIL();
argno=1;
push_call("simplehash.toarrkey",base);
//
    line(255);
    push(&ZERO);
    assign(base+3);//cnt
    pop();
    line(256);
    push_symbol(base+0);//this
    _o_method_valuecount.eval(1);
    _clp_array(1);
    assign(base+1);//arr
    pop();
    line(257);
    push_symbol(base+0);//this
    _o_method_firstkey.eval(1);
    assign(base+2);//key
    pop();
    line(261);
    lab_19_1:
    line(258);
    push_symbol(base+2);//key
    push(&NIL);
    neeq();
    cmp_3694:;
    if(!flag()) goto lab_19_2;
        line(259);
        push_symbol(base+2);//key
        push_symbol(base+1);//arr
        push_symbol(base+3);//cnt
        push(&ONE);
        add();
        assign(base+3);//cnt
        assign2(idxxl());
        pop();
        line(260);
        push_symbol(base+0);//this
        _o_method_nextkey.eval(1);
        assign(base+2);//key
        pop();
    goto lab_19_1;
    lab_19_2:;
    line(262);
    push_symbol(base+1);//arr
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
namespace _nsp_simplehash{
static void _clp_toarrvalue(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+4)PUSHNIL();
argno=1;
push_call("simplehash.toarrvalue",base);
//
    line(266);
    push(&ZERO);
    assign(base+3);//cnt
    pop();
    line(267);
    push_symbol(base+0);//this
    _o_method_valuecount.eval(1);
    _clp_array(1);
    assign(base+1);//arr
    pop();
    line(268);
    push_symbol(base+0);//this
    _o_method_firstvalue.eval(1);
    assign(base+2);//value
    pop();
    line(272);
    lab_20_1:
    line(269);
    push_symbol(base+2);//value
    push(&NIL);
    neeq();
    cmp_3826:;
    if(!flag()) goto lab_20_2;
        line(270);
        push_symbol(base+2);//value
        push_symbol(base+1);//arr
        push_symbol(base+3);//cnt
        push(&ONE);
        add();
        assign(base+3);//cnt
        assign2(idxxl());
        pop();
        line(271);
        push_symbol(base+0);//this
        _o_method_nextvalue.eval(1);
        assign(base+2);//value
        pop();
    goto lab_20_1;
    lab_20_2:;
    line(273);
    push_symbol(base+1);//arr
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
}//namespace simplehash
//=======================================================================
static void _clp_hash_index(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+5)PUSHNIL();
argno=2;
push_call("hash_index",base);
//
    line(281);
    push_symbol(base+0);//hash
    _clp_len(1);
    assign(base+2);//hlen
    pop();
    line(282);
    push_symbol(base+1);//key
    _clp_hashcode(1);
    assign(base+3);//hcode
    pop();
    line(283);
    push_symbol(base+3);//hcode
    push_symbol(base+2);//hlen
    modulo();
    assign(base+4);//hidx
    pop();
    line(293);
    lab_21_1:
    line(285);
    push(&TRUE);
    if(!flag()) goto lab_21_2;
        line(292);
        line(286);
        push(&NIL);
        push_symbol(base+0);//hash
        push_symbol(base+4);//hidx
        addnum(1);
        idxr();
        eqeq();
        cmp_3967:;
        if(!flag()) goto if_22_1;
            line(287);
            push_symbol(base+4);//hidx
            addnum(1);
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        goto if_22_0;
        if_22_1:
        line(288);
        push_symbol(base+1);//key
        push_symbol(base+0);//hash
        push_symbol(base+4);//hidx
        addnum(1);
        idxr();
        idxr0(1);
        eqeq();
        cmp_4003:;
        if(!flag()) goto if_22_2;
            line(289);
            push_symbol(base+4);//hidx
            addnum(1);
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        goto if_22_0;
        if_22_2:
        line(290);
        push_symbol(base+4);//hidx
        push(&ONE);
        add();
        assign(base+4);//hidx
        push_symbol(base+2);//hlen
        gteq();
        cmp_4046:;
        if(!flag()) goto if_22_3;
            line(291);
            push(&ZERO);
            assign(base+4);//hidx
            pop();
        if_22_3:
        if_22_0:;
    goto lab_21_1;
    lab_21_2:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

