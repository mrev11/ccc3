
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

//input: cloutput.ppo (5.0.18)

#include <cccdef.h>

static void _blk_outputregister_0(int argno);
static void _blk_outputregister_1(int argno);
static void _blk_outputregister_2(int argno);
static void _blk_outputregister_3(int argno);
static void _blk_outputregister_4(int argno);
extern void _clp_array(int argno);
extern void _clp_asize(int argno);
extern void _clp_classattrib(int argno);
extern void _clp_classmethod(int argno);
extern void _clp_classregister(int argno);
extern void _clp_len(int argno);
extern void _clp_objectclass(int argno);
extern void _clp_objectini(int argno);
extern void _clp_objectnew(int argno);
static void _clp_outputadd(int argno);
static void _clp_outputbuf(int argno);
extern void _clp_outputclass(int argno);
static void _clp_outputclear(int argno);
static void _clp_outputini(int argno);
static void _clp_outputlen(int argno);
extern void _clp_outputnew(int argno);
static void _clp_outputregister(int argno);
extern void _clp_valtype(int argno);
static void _ini__clid_output();

class _method3_buffer: public _method3_{public: _method3_buffer():_method3_("buffer"){};}; static _method3_buffer _o_method_buffer;
class _method3_bufidx: public _method3_{public: _method3_bufidx():_method3_("bufidx"){};}; static _method3_bufidx _o_method_bufidx;
class _method3_bufinc: public _method3_{public: _method3_bufinc():_method3_("bufinc"){};}; static _method3_bufinc _o_method_bufinc;
class _method3_initialize: public _method3_{public: _method3_initialize():_method3_("initialize"){};}; static _method3_initialize _o_method_initialize;

MUTEX_CREATE(_mutex_clid_output);
static VALUE* _st_clid_output_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_clid_output);
    static stvar _st_clid_output(_ini__clid_output);
    MUTEX_UNLOCK(_mutex_clid_output);
    SIGNAL_UNLOCK();
    return _st_clid_output.ptr;
}

static void _ini__clid_output()
{
    _clp_outputregister(0);
}
//=======================================================================
void _clp_outputclass(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("outputclass",base);
//
    line(36);
    push_symbol(_st_clid_output_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_outputregister(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+1)PUSHNIL();
argno=0;
push_call("outputregister",base);
//
    line(40);
    string(L"output");
    _clp_objectclass(0);
    _clp_classregister(2);
    assign(base+0);//clid
    pop();
    line(41);
    push_symbol(base+0);//clid
    string(L"initialize");
    block(_blk_outputregister_0,0);
    _clp_classmethod(3);
    pop();
    line(42);
    push_symbol(base+0);//clid
    string(L"add");
    block(_blk_outputregister_1,0);
    _clp_classmethod(3);
    pop();
    line(43);
    push_symbol(base+0);//clid
    string(L"len");
    block(_blk_outputregister_2,0);
    _clp_classmethod(3);
    pop();
    line(44);
    push_symbol(base+0);//clid
    string(L"buf");
    block(_blk_outputregister_3,0);
    _clp_classmethod(3);
    pop();
    line(45);
    push_symbol(base+0);//clid
    string(L"clear");
    block(_blk_outputregister_4,0);
    _clp_classmethod(3);
    pop();
    line(46);
    push_symbol(base+0);//clid
    string(L"buffer");
    _clp_classattrib(2);
    pop();
    line(47);
    push_symbol(base+0);//clid
    string(L"bufidx");
    _clp_classattrib(2);
    pop();
    line(48);
    push_symbol(base+0);//clid
    string(L"bufinc");
    _clp_classattrib(2);
    pop();
    line(49);
    push_symbol(base+0);//clid
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_outputregister_0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_outputregister_0",base);
//
    push_blkarg(base+1);//this
    push_blkarg(base+2);//s
    _clp_outputini(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_outputregister_1(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_outputregister_1",base);
//
    push_blkarg(base+1);//this
    push_blkarg(base+2);//t
    _clp_outputadd(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_outputregister_2(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_outputregister_2",base);
//
    push_blkarg(base+1);//this
    _clp_outputlen(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_outputregister_3(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_outputregister_3",base);
//
    push_blkarg(base+1);//this
    _clp_outputbuf(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_outputregister_4(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_outputregister_4",base);
//
    push_blkarg(base+1);//this
    _clp_outputclear(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
void _clp_outputnew(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("outputnew",base);
//
    line(54);
    _clp_outputclass(0);
    assign(base+1);//clid
    pop();
    line(55);
    push_symbol(base+1);//clid
    _clp_objectnew(1);
    push_symbol(base+0);//incsize
    _o_method_initialize.eval(2);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_outputini(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("outputini",base);
//
    line(61);
    push_symbol(base+0);//this
    _clp_objectini(1);
    pop();
    line(65);
    push_symbol(base+0);//this
    push_symbol(base+1);//size
    push(&NIL);
    neeq();
    if(flag()){
    push_symbol(base+1);//size
    }else{
    number(32);
    }
    _o_method_bufinc.eval(2);
    pop();
    line(66);
    push_symbol(base+0);//this
    push_symbol(base+0);//this
    _o_method_bufinc.eval(1);
    _clp_array(1);
    _o_method_buffer.eval(2);
    pop();
    line(67);
    push_symbol(base+0);//this
    push(&ONE);
    _o_method_bufidx.eval(2);
    pop();
    line(69);
    push_symbol(base+0);//this
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_outputadd(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+6)PUSHNIL();
argno=2;
push_call("outputadd",base);
//
    line(75);
    push_symbol(base+1);//t
    _clp_valtype(1);
    assign(base+3);//typt
    pop();
    line(83);
    line(77);
    push_symbol(base+3);//typt
    string(L"A");
    eqeq();
    if(!flag()) goto if_1_1;
        line(78);
        push_symbol(base+1);//t
        _clp_len(1);
        assign(base+4);//lent
        pop();
        line(79);
        push(&TRUE);
        assign(base+5);//arrflg
        pop();
    goto if_1_0;
    if_1_1:
    line(80);
        line(81);
        push(&ONE);
        assign(base+4);//lent
        pop();
        line(82);
        push(&FALSE);
        assign(base+5);//arrflg
        pop();
    if_1_2:
    if_1_0:;
    line(87);
    line(85);
    push_symbol(base+0);//this
    _o_method_bufidx.eval(1);
    push_symbol(base+4);//lent
    add();
    push_symbol(base+0);//this
    _o_method_buffer.eval(1);
    _clp_len(1);
    gt();
    if(!flag()) goto if_2_1;
        line(86);
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        push_symbol(base+0);//this
        _o_method_bufidx.eval(1);
        push_symbol(base+4);//lent
        add();
        push_symbol(base+0);//this
        _o_method_bufinc.eval(1);
        add();
        _clp_asize(2);
        pop();
    if_2_1:
    if_2_0:;
    line(97);
    line(89);
    push_symbol(base+5);//arrflg
    if(!flag()) goto if_3_1;
        line(93);
        {
        line(90);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+2);//n
        lab_4_0:
        push_symbol(base+4);//lent
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
            line(91);
            push_symbol(base+1);//t
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+0);//this
            _o_method_buffer.eval(1);
            push_symbol(base+0);//this
            _o_method_bufidx.eval(1);
            assign2(idxxl());
            pop();
            line(92);
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
        lab_4_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+2);//n
        add();
        assign(base+2);//n
        goto lab_4_0;
        lab_4_2:;
        }
    goto if_3_0;
    if_3_1:
    line(94);
        line(95);
        push_symbol(base+1);//t
        push_symbol(base+0);//this
        _o_method_buffer.eval(1);
        push_symbol(base+0);//this
        _o_method_bufidx.eval(1);
        assign2(idxxl());
        pop();
        line(96);
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
    if_3_2:
    if_3_0:;
    line(99);
    push_symbol(base+1);//t
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_outputlen(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("outputlen",base);
//
    line(104);
    push_symbol(base+0);//this
    _o_method_bufidx.eval(1);
    addnum(-1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_outputbuf(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("outputbuf",base);
//
    line(109);
    push_symbol(base+0);//this
    _o_method_buffer.eval(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_outputclear(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("outputclear",base);
//
    line(114);
    push_symbol(base+0);//this
    push_symbol(base+0);//this
    _o_method_bufinc.eval(1);
    _clp_array(1);
    _o_method_buffer.eval(2);
    pop();
    line(115);
    push_symbol(base+0);//this
    push(&ONE);
    _o_method_bufidx.eval(2);
    pop();
    line(116);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

