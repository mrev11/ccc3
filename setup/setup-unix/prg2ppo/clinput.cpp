
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

//input: clinput.ppo (5.0.03x)

#include <cccdef.h>

static void _blk_inputregister_0(int argno);
static void _blk_inputregister_1(int argno);
static void _blk_inputregister_2(int argno);
static void _blk_inputregister_3(int argno);
static void _blk_inputregister_4(int argno);
static void _blk_inputregister_5(int argno);
static void _blk_inputregister_6(int argno);
static void _blk_inputregister_7(int argno);
extern void _clp___quit(int argno);
extern void _clp_array(int argno);
extern void _clp_classattrib(int argno);
extern void _clp_classmethod(int argno);
extern void _clp_classregister(int argno);
extern void _clp_inputclass(int argno);
static void _clp_inputclear(int argno);
static void _clp_inputcont(int argno);
static void _clp_inputget(int argno);
static void _clp_inputindex(int argno);
static void _clp_inputini(int argno);
static void _clp_inputlen(int argno);
extern void _clp_inputnew(int argno);
static void _clp_inputnext(int argno);
static void _clp_inputregister(int argno);
static void _clp_inputunget(int argno);
extern void _clp_len(int argno);
extern void _clp_objectclass(int argno);
extern void _clp_objectini(int argno);
extern void _clp_objectnew(int argno);
extern void _clp_qout(int argno);
extern void _clp_valtype(int argno);
static void _ini__clid_input();

class _method_buffer: public _method2_{public: _method_buffer():_method2_("buffer"){};}; static _method_buffer _o_method_buffer;
class _method_bufidx: public _method2_{public: _method_bufidx():_method2_("bufidx"){};}; static _method_bufidx _o_method_bufidx;
class _method_initialize: public _method2_{public: _method_initialize():_method2_("initialize"){};}; static _method_initialize _o_method_initialize;
class _method_len: public _method2_{public: _method_len():_method2_("len"){};}; static _method_len _o_method_len;
class _method_next: public _method2_{public: _method_next():_method2_("next"){};}; static _method_next _o_method_next;
class _method_unget: public _method2_{public: _method_unget():_method2_("unget"){};}; static _method_unget _o_method_unget;

MUTEX_CREATE(_mutex_clid_input);
static VALUE* _st_clid_input_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_clid_input);
    static stvar _st_clid_input(_ini__clid_input);
    MUTEX_UNLOCK(_mutex_clid_input);
    SIGNAL_UNLOCK();
    return _st_clid_input.ptr;
}

static void _ini__clid_input()
{
    _clp_inputregister(0);
}
//=======================================================================
void _clp_inputclass(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("inputclass",base);
//
    line(27);
    push_symbol(_st_clid_input_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_inputregister(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+1)PUSHNIL();
argno=0;
push_call("inputregister",base);
//
    line(31);
    string(L"input");
    _clp_objectclass(0);
    _clp_classregister(2);
    assign(base+0);//clid
    pop();
    line(32);
    push_symbol(base+0);//clid
    string(L"initialize");
    block(_blk_inputregister_0,0);
    _clp_classmethod(3);
    pop();
    line(33);
    push_symbol(base+0);//clid
    string(L"next");
    block(_blk_inputregister_1,0);
    _clp_classmethod(3);
    pop();
    line(34);
    push_symbol(base+0);//clid
    string(L"get");
    block(_blk_inputregister_2,0);
    _clp_classmethod(3);
    pop();
    line(35);
    push_symbol(base+0);//clid
    string(L"unget");
    block(_blk_inputregister_3,0);
    _clp_classmethod(3);
    pop();
    line(36);
    push_symbol(base+0);//clid
    string(L"len");
    block(_blk_inputregister_4,0);
    _clp_classmethod(3);
    pop();
    line(37);
    push_symbol(base+0);//clid
    string(L"cont");
    block(_blk_inputregister_5,0);
    _clp_classmethod(3);
    pop();
    line(38);
    push_symbol(base+0);//clid
    string(L"index");
    block(_blk_inputregister_6,0);
    _clp_classmethod(3);
    pop();
    line(39);
    push_symbol(base+0);//clid
    string(L"clear");
    block(_blk_inputregister_7,0);
    _clp_classmethod(3);
    pop();
    line(40);
    push_symbol(base+0);//clid
    string(L"buffer");
    _clp_classattrib(2);
    pop();
    line(41);
    push_symbol(base+0);//clid
    string(L"bufidx");
    _clp_classattrib(2);
    pop();
    line(42);
    push_symbol(base+0);//clid
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_inputregister_0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+4)PUSHNIL();
argno=4;
push_call("_blk_inputregister_0",base);
//
    push_blkarg(base+1);//this
    push_blkarg(base+2);//s
    push_blkarg(base+3);//t
    _clp_inputini(3);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_inputregister_1(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_inputregister_1",base);
//
    push_blkarg(base+1);//this
    push_blkarg(base+2);//n
    _clp_inputnext(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_inputregister_2(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_inputregister_2",base);
//
    push_blkarg(base+1);//this
    _clp_inputget(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_inputregister_3(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+4)PUSHNIL();
argno=4;
push_call("_blk_inputregister_3",base);
//
    push_blkarg(base+1);//this
    push_blkarg(base+2);//t
    push_blkarg(base+3);//s
    _clp_inputunget(3);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_inputregister_4(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_inputregister_4",base);
//
    push_blkarg(base+1);//this
    _clp_inputlen(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_inputregister_5(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_inputregister_5",base);
//
    push_blkarg(base+1);//this
    _clp_inputcont(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_inputregister_6(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_inputregister_6",base);
//
    push_blkarg(base+1);//this
    push_blkarg(base+2);//i
    _clp_inputindex(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_inputregister_7(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_inputregister_7",base);
//
    push_blkarg(base+1);//this
    _clp_inputclear(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
void _clp_inputnew(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("inputnew",base);
//
    line(47);
    _clp_inputclass(0);
    assign(base+2);//clid
    pop();
    line(48);
    push_symbol(base+2);//clid
    _clp_objectnew(1);
    push_symbol(base+0);//size
    push_symbol(base+1);//toklist
    _o_method_initialize.eval(3);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_inputini(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("inputini",base);
//
    line(54);
    push_symbol(base+0);//this
    _clp_objectini(1);
    pop();
    line(58);
    push_symbol(base+0);//this
    push_symbol(base+1);//size
    _clp_array(1);
    _o_method_buffer.eval(2);
    pop();
    line(59);
    push_symbol(base+0);//this
    push_symbol(base+1);//size
    _o_method_bufidx.eval(2);
    pop();
    line(63);
    line(61);
    push_symbol(base+2);//toklist
    push(&NIL);
    neeq();
    if(!flag()) goto if_1_1;
        line(62);
        push_symbol(base+0);//this
        push_symbol(base+2);//toklist
        _o_method_unget.eval(2);
        pop();
    if_1_1:
    if_1_0:;
    line(65);
    push_symbol(base+0);//this
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_inputnext(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("inputnext",base);
//
    line(71);
    line(77);
    line(73);
    push_symbol(base+1);//n
    push(&NIL);
    eqeq();
    if(!flag()) goto if_2_1;
        line(74);
        push_symbol(base+0);//this
        _o_method_bufidx.eval(1);
        addnum(1);
        assign(base+2);//x
        pop();
    goto if_2_0;
    if_2_1:
    line(75);
        line(76);
        push_symbol(base+0);//this
        _o_method_bufidx.eval(1);
        push_symbol(base+1);//n
        add();
        assign(base+2);//x
        pop();
    if_2_2:
    if_2_0:;
    line(81);
    line(79);
    push(&ONE);
    push_symbol(base+2);//x
    lteq();
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+2);//x
    push_symbol(base+0);//this
    _o_method_buffer.eval(1);
    _clp_len(1);
    lteq();
    }
    if(!flag()) goto if_3_1;
        line(80);
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        push_symbol(base+2);//x
        idxr();
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_3_1:
    if_3_0:;
    line(82);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_inputget(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("inputget",base);
//
    line(87);
    push_symbol(base+0);//this
    _o_method_bufidx.eval(1);
    addnum(1);
    assign(base+1);//x
    pop();
    line(91);
    line(88);
    push(&ONE);
    push_symbol(base+1);//x
    lteq();
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+1);//x
    push_symbol(base+0);//this
    _o_method_buffer.eval(1);
    _clp_len(1);
    lteq();
    }
    if(!flag()) goto if_4_1;
        line(89);
        push_symbol(base+0);//this
        _o_method_bufidx.eval(1);
        dup();
        push(&ONE);
        add();
        push_symbol(base+0);//this
        swap();
        _o_method_bufidx.eval(2);
        pop();
        pop();
        line(90);
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        push_symbol(base+1);//x
        idxr();
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_4_1:
    if_4_0:;
    line(92);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_inputunget(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+6)PUSHNIL();
argno=3;
push_call("inputunget",base);
//
    line(98);
    push_symbol(base+1);//t
    _clp_valtype(1);
    assign(base+4);//typt
    pop();
    line(108);
    line(100);
    push_symbol(base+4);//typt
    string(L"A");
    eqeq();
    if(!flag()) goto if_5_1;
        line(103);
        line(101);
        push_symbol(base+2);//lent
        push(&NIL);
        eqeq();
        if(!flag()) goto if_6_1;
            line(102);
            push_symbol(base+1);//t
            _clp_len(1);
            assign(base+2);//lent
            pop();
        if_6_1:
        if_6_0:;
        line(104);
        push(&TRUE);
        assign(base+5);//arrflg
        pop();
    goto if_5_0;
    if_5_1:
    line(105);
        line(106);
        push(&ONE);
        assign(base+2);//lent
        pop();
        line(107);
        push(&FALSE);
        assign(base+5);//arrflg
        pop();
    if_5_2:
    if_5_0:;
    line(117);
    line(111);
    push_symbol(base+0);//this
    _o_method_bufidx.eval(1);
    push_symbol(base+2);//lent
    lt();
    if(!flag()) goto if_7_1;
        line(112);
        push_symbol(base+0);//this
        _o_method_bufidx.eval(1);
        push_symbol(base+2);//lent
        _clp_qout(2);
        pop();
        line(113);
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        _clp_qout(1);
        pop();
        line(114);
        push_symbol(base+1);//t
        _clp_qout(1);
        pop();
        line(115);
        string(nls_text(L"Input Stack Overflow"));
        _clp_qout(1);
        pop();
        line(116);
        _clp___quit(0);
        pop();
    if_7_1:
    if_7_0:;
    line(127);
    line(119);
    push_symbol(base+5);//arrflg
    if(!flag()) goto if_8_1;
        line(123);
        {
        line(120);
        number(-1);
        int sg=sign();
        push_symbol(base+2);//lent
        assign(base+3);//n
        lab_9_0:
        push(&ONE);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_9_2;
            line(121);
            push_symbol(base+1);//t
            push_symbol(base+3);//n
            idxr();
            push_symbol(base+0);//this
            _o_method_buffer.eval(1);
            push_symbol(base+0);//this
            _o_method_bufidx.eval(1);
            assign(idxl());
            pop();
            line(122);
            push_symbol(base+0);//this
            _o_method_bufidx.eval(1);
            dup();
            push(&ONE);
            sub();
            push_symbol(base+0);//this
            swap();
            _o_method_bufidx.eval(2);
            pop();
            pop();
        lab_9_1:
        number(-1);
        dup();
        sg=sign();
        push_symbol(base+3);//n
        add();
        assign(base+3);//n
        goto lab_9_0;
        lab_9_2:;
        }
    goto if_8_0;
    if_8_1:
    line(124);
        line(125);
        push_symbol(base+1);//t
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        push_symbol(base+0);//this
        _o_method_bufidx.eval(1);
        assign(idxl());
        pop();
        line(126);
        push_symbol(base+0);//this
        _o_method_bufidx.eval(1);
        dup();
        push(&ONE);
        sub();
        push_symbol(base+0);//this
        swap();
        _o_method_bufidx.eval(2);
        pop();
        pop();
    if_8_2:
    if_8_0:;
    line(129);
    push_symbol(base+1);//t
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_inputlen(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("inputlen",base);
//
    line(134);
    push_symbol(base+0);//this
    _o_method_buffer.eval(1);
    _clp_len(1);
    push_symbol(base+0);//this
    _o_method_bufidx.eval(1);
    sub();
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_inputcont(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("inputcont",base);
//
    line(139);
    push_symbol(base+0);//this
    _o_method_len.eval(1);
    _clp_array(1);
    assign(base+1);//a
    pop();
    line(142);
    {
    line(140);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_10_0:
    push_symbol(base+0);//this
    _o_method_len.eval(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_10_2;
        line(141);
        push_symbol(base+0);//this
        push_symbol(base+2);//n
        _o_method_next.eval(2);
        push_symbol(base+1);//a
        push_symbol(base+2);//n
        assign(idxl());
        pop();
    lab_10_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_10_0;
    lab_10_2:;
    }
    line(143);
    push_symbol(base+1);//a
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_inputindex(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("inputindex",base);
//
    line(148);
    push_symbol(base+0);//this
    _o_method_bufidx.eval(1);
    push_symbol(base+1);//i
    add();
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_inputclear(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("inputclear",base);
//
    line(153);
    push_symbol(base+0);//this
    push_symbol(base+0);//this
    _o_method_buffer.eval(1);
    _clp_len(1);
    _o_method_bufidx.eval(2);
    pop();
    line(154);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

