
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

//input: ascan.ppo (5.0.03x)

#include <cccdef.h>

static void _blk__asort_ascendblock_0(int argno);
extern void _clp__asort_ascendblock(int argno);
extern void _clp_acopy(int argno);
extern void _clp_aeval(int argno);
extern void _clp_afill(int argno);
extern void _clp_ascan(int argno);
extern void _clp_atail(int argno);
extern void _clp_eval(int argno);
extern void _clp_len(int argno);
extern void _clp_min(int argno);
extern void _clp_valtype(int argno);

//=======================================================================
void _clp_atail(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("atail",base);
//
    line(23);
    push_symbol(base+0);//arr
    _clp_len(1);
    assign(base+1);//x
    pop();
    line(24);
    push_symbol(base+1);//x
    push(&ZERO);
    lteq();
    if(flag()){
    push(&NIL);
    }else{
    push_symbol(base+0);//arr
    push_symbol(base+1);//x
    idxr();
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_ascan(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+6)PUSHNIL();
argno=4;
push_call("ascan",base);
//
    line(28);
    push(&ZERO);
    assign(base+4);//at
    pop();
    line(32);
    line(30);
    push_symbol(base+2);//st
    push(&NIL);
    eqeq();
    if(!flag()) goto if_1_1;
        line(31);
        push(&ONE);
        assign(base+2);//st
        pop();
    if_1_1:
    if_1_0:;
    line(36);
    line(34);
    push_symbol(base+3);//cn
    push(&NIL);
    eqeq();
    if(!flag()) goto if_2_1;
        line(35);
        push_symbol(base+0);//arr
        _clp_len(1);
        assign(base+3);//cn
        pop();
    if_2_1:
    if_2_0:;
    line(38);
    push_symbol(base+3);//cn
    push_symbol(base+0);//arr
    _clp_len(1);
    push_symbol(base+2);//st
    sub();
    addnum(1);
    _clp_min(2);
    assign(base+3);//cn
    pop();
    line(63);
    line(40);
    push_symbol(base+1);//blk
    _clp_valtype(1);
    string(L"B");
    eqeq();
    if(!flag()) goto if_3_1;
        line(47);
        {
        line(42);
        push(&ONE);
        int sg=sign();
        push_symbol(base+2);//st
        assign(base+5);//i
        lab_4_0:
        push_symbol(base+2);//st
        push_symbol(base+3);//cn
        add();
        addnum(-1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
            line(46);
            line(43);
            push_symbol(base+1);//blk
            push_symbol(base+0);//arr
            push_symbol(base+5);//i
            idxr();
            _clp_eval(2);
            if(!flag()) goto if_5_1;
                line(44);
                push_symbol(base+5);//i
                assign(base+4);//at
                pop();
                line(45);
                goto lab_4_2;//exit
            if_5_1:
            if_5_0:;
        lab_4_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+5);//i
        add();
        assign(base+5);//i
        goto lab_4_0;
        lab_4_2:;
        }
    goto if_3_0;
    if_3_1:
    line(49);
        line(62);
        {
        line(51);
        push(&ONE);
        int sg=sign();
        push_symbol(base+2);//st
        assign(base+5);//i
        lab_6_0:
        push_symbol(base+2);//st
        push_symbol(base+3);//cn
        add();
        addnum(-1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_6_2;
            line(61);
            line(58);
            push_symbol(base+0);//arr
            push_symbol(base+5);//i
            idxr();
            push_symbol(base+1);//blk
            neeq();
            topnot();
            if(!flag()) goto if_7_1;
                line(59);
                push_symbol(base+5);//i
                assign(base+4);//at
                pop();
                line(60);
                goto lab_6_2;//exit
            if_7_1:
            if_7_0:;
        lab_6_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+5);//i
        add();
        assign(base+5);//i
        goto lab_6_0;
        lab_6_2:;
        }
    if_3_2:
    if_3_0:;
    line(65);
    push_symbol(base+4);//at
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_aeval(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+5)PUSHNIL();
argno=4;
push_call("aeval",base);
//
    line(70);
    line(74);
    line(72);
    push_symbol(base+2);//st
    push(&NIL);
    eqeq();
    if(!flag()) goto if_8_1;
        line(73);
        push(&ONE);
        assign(base+2);//st
        pop();
    if_8_1:
    if_8_0:;
    line(78);
    line(76);
    push_symbol(base+3);//cn
    push(&NIL);
    eqeq();
    if(!flag()) goto if_9_1;
        line(77);
        push_symbol(base+0);//arr
        _clp_len(1);
        assign(base+3);//cn
        pop();
    if_9_1:
    if_9_0:;
    line(80);
    push_symbol(base+3);//cn
    push_symbol(base+0);//arr
    _clp_len(1);
    push_symbol(base+2);//st
    sub();
    addnum(1);
    _clp_min(2);
    assign(base+3);//cn
    pop();
    line(84);
    {
    line(82);
    push(&ONE);
    int sg=sign();
    push_symbol(base+2);//st
    assign(base+4);//i
    lab_10_0:
    push_symbol(base+2);//st
    push_symbol(base+3);//cn
    add();
    addnum(-1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_10_2;
        line(83);
        push_symbol(base+1);//blk
        push_symbol(base+0);//arr
        push_symbol(base+4);//i
        idxr();
        _clp_eval(2);
        pop();
    lab_10_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//i
    add();
    assign(base+4);//i
    goto lab_10_0;
    lab_10_2:;
    }
    line(86);
    push_symbol(base+0);//arr
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_afill(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+5)PUSHNIL();
argno=4;
push_call("afill",base);
//
    line(91);
    line(95);
    line(93);
    push_symbol(base+2);//st
    push(&NIL);
    eqeq();
    if(!flag()) goto if_11_1;
        line(94);
        push(&ONE);
        assign(base+2);//st
        pop();
    if_11_1:
    if_11_0:;
    line(99);
    line(97);
    push_symbol(base+3);//cn
    push(&NIL);
    eqeq();
    if(!flag()) goto if_12_1;
        line(98);
        push_symbol(base+0);//arr
        _clp_len(1);
        assign(base+3);//cn
        pop();
    if_12_1:
    if_12_0:;
    line(101);
    push_symbol(base+3);//cn
    push_symbol(base+0);//arr
    _clp_len(1);
    push_symbol(base+2);//st
    sub();
    addnum(1);
    _clp_min(2);
    assign(base+3);//cn
    pop();
    line(105);
    {
    line(103);
    push(&ONE);
    int sg=sign();
    push_symbol(base+2);//st
    assign(base+4);//i
    lab_13_0:
    push_symbol(base+2);//st
    push_symbol(base+3);//cn
    add();
    addnum(-1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_13_2;
        line(104);
        push_symbol(base+1);//x
        push_symbol(base+0);//arr
        push_symbol(base+4);//i
        assign(idxl());
        pop();
    lab_13_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//i
    add();
    assign(base+4);//i
    goto lab_13_0;
    lab_13_2:;
    }
    line(107);
    push_symbol(base+0);//arr
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_acopy(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,5);
while(stack<base+6)PUSHNIL();
argno=5;
push_call("acopy",base);
//
    line(112);
    line(116);
    line(114);
    push_symbol(base+2);//stsrc
    push(&NIL);
    eqeq();
    if(!flag()) goto if_14_1;
        line(115);
        push(&ONE);
        assign(base+2);//stsrc
        pop();
    if_14_1:
    if_14_0:;
    line(120);
    line(118);
    push_symbol(base+4);//sttrg
    push(&NIL);
    eqeq();
    if(!flag()) goto if_15_1;
        line(119);
        push(&ONE);
        assign(base+4);//sttrg
        pop();
    if_15_1:
    if_15_0:;
    line(124);
    line(122);
    push_symbol(base+3);//cn
    push(&NIL);
    eqeq();
    if(!flag()) goto if_16_1;
        line(123);
        push_symbol(base+0);//asrc
        _clp_len(1);
        assign(base+3);//cn
        pop();
    if_16_1:
    if_16_0:;
    line(126);
    push_symbol(base+3);//cn
    push_symbol(base+0);//asrc
    _clp_len(1);
    push_symbol(base+2);//stsrc
    sub();
    addnum(1);
    _clp_min(2);
    assign(base+3);//cn
    pop();
    line(127);
    push_symbol(base+3);//cn
    push_symbol(base+1);//atrg
    _clp_len(1);
    push_symbol(base+4);//sttrg
    sub();
    addnum(1);
    _clp_min(2);
    assign(base+3);//cn
    pop();
    line(131);
    {
    line(129);
    push(&ONE);
    int sg=sign();
    push(&ZERO);
    assign(base+5);//i
    lab_17_0:
    push_symbol(base+3);//cn
    addnum(-1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_17_2;
        line(130);
        push_symbol(base+0);//asrc
        push_symbol(base+2);//stsrc
        push_symbol(base+5);//i
        add();
        idxr();
        push_symbol(base+1);//atrg
        push_symbol(base+4);//sttrg
        push_symbol(base+5);//i
        add();
        assign(idxl());
        pop();
    lab_17_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+5);//i
    add();
    assign(base+5);//i
    goto lab_17_0;
    lab_17_2:;
    }
    line(133);
    push_symbol(base+1);//atrg
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp__asort_ascendblock(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("_asort_ascendblock",base);
//
    line(138);
    block(_blk__asort_ascendblock_0,0);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk__asort_ascendblock_0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk__asort_ascendblock_0",base);
//
    push_blkarg(base+1);//x
    push_blkarg(base+2);//y
    lt();
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================

