//input: ppo/ascan.ppo (5.7.0.1)

#include <cccdef.h>

static void _blk__asort_ascendblock_0(int argno);
extern void _clp__asort_ascendblock(int argno);
extern void _clp_aadd(int argno);
extern void _clp_acat(int argno);
extern void _clp_acopy(int argno);
extern void _clp_addel(int argno);
extern void _clp_adel(int argno);
extern void _clp_aeval(int argno);
extern void _clp_afill(int argno);
extern void _clp_aiins(int argno);
extern void _clp_ains(int argno);
extern void _clp_apop(int argno);
extern void _clp_apush(int argno);
extern void _clp_arev(int argno);
extern void _clp_ascan(int argno);
extern void _clp_asize(int argno);
extern void _clp_eval(int argno);
extern void _clp_len(int argno);
extern void _clp_min(int argno);
extern void _clp_valtype(int argno);

//=======================================================================
void _clp_ascan(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+6)PUSHNIL();
argno=4;
push_call("ascan",base);
//
    line(24);
    push(&ZERO);
    assign(base+4);//at
    pop();
    line(28);
    line(26);
    push_symbol(base+2);//st
    push(&NIL);
    eqeq();
    cmp_55:;
    if(!flag()) goto if_1_1;
        line(27);
        push(&ONE);
        assign(base+2);//st
        pop();
    if_1_1:
    if_1_0:;
    line(32);
    line(30);
    push_symbol(base+3);//cn
    push(&NIL);
    eqeq();
    cmp_88:;
    if(!flag()) goto if_2_1;
        line(31);
        push_symbol(base+0);//arr
        _clp_len(1);
        assign(base+3);//cn
        pop();
    if_2_1:
    if_2_0:;
    line(34);
    push_symbol(base+3);//cn
    push_symbol(base+0);//arr
    _clp_len(1);
    push_symbol(base+2);//st
    sub();
    addnum(1);
    _clp_min(2);
    assign(base+3);//cn
    pop();
    line(59);
    line(36);
    push_symbol(base+1);//blk
    _clp_valtype(1);
    string(L"B");
    eqeq();
    cmp_178:;
    if(!flag()) goto if_3_1;
        line(43);
        {
        line(38);
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
            line(42);
            line(39);
            push_symbol(base+1);//blk
            push_symbol(base+0);//arr
            push_symbol(base+5);//i
            idxr();
            _clp_eval(2);
            if(!flag()) goto if_5_1;
                line(40);
                push_symbol(base+5);//i
                assign(base+4);//at
                pop();
                line(41);
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
    line(45);
        line(58);
        {
        line(47);
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
            line(57);
            line(54);
            push_symbol(base+0);//arr
            push_symbol(base+5);//i
            idxr();
            push_symbol(base+1);//blk
            neeq();
            cmp_304:;
            topnot();
            if(!flag()) goto if_7_1;
                line(55);
                push_symbol(base+5);//i
                assign(base+4);//at
                pop();
                line(56);
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
    line(61);
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
    line(66);
    line(70);
    line(68);
    push_symbol(base+2);//st
    push(&NIL);
    eqeq();
    cmp_402:;
    if(!flag()) goto if_8_1;
        line(69);
        push(&ONE);
        assign(base+2);//st
        pop();
    if_8_1:
    if_8_0:;
    line(74);
    line(72);
    push_symbol(base+3);//cn
    push(&NIL);
    eqeq();
    cmp_435:;
    if(!flag()) goto if_9_1;
        line(73);
        push_symbol(base+0);//arr
        _clp_len(1);
        assign(base+3);//cn
        pop();
    if_9_1:
    if_9_0:;
    line(76);
    push_symbol(base+3);//cn
    push_symbol(base+0);//arr
    _clp_len(1);
    push_symbol(base+2);//st
    sub();
    addnum(1);
    _clp_min(2);
    assign(base+3);//cn
    pop();
    line(80);
    {
    line(78);
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
        line(79);
        push_symbol(base+1);//blk
        push_symbol(base+0);//arr
        push_symbol(base+4);//i
        idxr();
        push_symbol(base+4);//i
        _clp_eval(3);
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
    line(82);
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
    line(87);
    line(91);
    line(89);
    push_symbol(base+2);//st
    push(&NIL);
    eqeq();
    cmp_618:;
    if(!flag()) goto if_11_1;
        line(90);
        push(&ONE);
        assign(base+2);//st
        pop();
    if_11_1:
    if_11_0:;
    line(95);
    line(93);
    push_symbol(base+3);//cn
    push(&NIL);
    eqeq();
    cmp_651:;
    if(!flag()) goto if_12_1;
        line(94);
        push_symbol(base+0);//arr
        _clp_len(1);
        assign(base+3);//cn
        pop();
    if_12_1:
    if_12_0:;
    line(97);
    push_symbol(base+3);//cn
    push_symbol(base+0);//arr
    _clp_len(1);
    push_symbol(base+2);//st
    sub();
    addnum(1);
    _clp_min(2);
    assign(base+3);//cn
    pop();
    line(101);
    {
    line(99);
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
        line(100);
        push_symbol(base+1);//x
        push_symbol(base+0);//arr
        push_symbol(base+4);//i
        assign2(idxxl());
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
    line(103);
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
    line(108);
    line(112);
    line(110);
    push_symbol(base+2);//stsrc
    push(&NIL);
    eqeq();
    cmp_821:;
    if(!flag()) goto if_14_1;
        line(111);
        push(&ONE);
        assign(base+2);//stsrc
        pop();
    if_14_1:
    if_14_0:;
    line(116);
    line(114);
    push_symbol(base+4);//sttrg
    push(&NIL);
    eqeq();
    cmp_854:;
    if(!flag()) goto if_15_1;
        line(115);
        push(&ONE);
        assign(base+4);//sttrg
        pop();
    if_15_1:
    if_15_0:;
    line(120);
    line(118);
    push_symbol(base+3);//cn
    push(&NIL);
    eqeq();
    cmp_887:;
    if(!flag()) goto if_16_1;
        line(119);
        push_symbol(base+0);//asrc
        _clp_len(1);
        assign(base+3);//cn
        pop();
    if_16_1:
    if_16_0:;
    line(122);
    push_symbol(base+3);//cn
    push_symbol(base+0);//asrc
    _clp_len(1);
    push_symbol(base+2);//stsrc
    sub();
    addnum(1);
    _clp_min(2);
    assign(base+3);//cn
    pop();
    line(123);
    push_symbol(base+3);//cn
    push_symbol(base+1);//atrg
    _clp_len(1);
    push_symbol(base+4);//sttrg
    sub();
    addnum(1);
    _clp_min(2);
    assign(base+3);//cn
    pop();
    line(127);
    {
    line(125);
    push(&ONE);
    int sg=sign();
    push(&ZERO);
    assign(base+5);//i
    lab_17_0:
    push_symbol(base+3);//cn
    addnum(-1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_17_2;
        line(126);
        push_symbol(base+0);//asrc
        push_symbol(base+2);//stsrc
        push_symbol(base+5);//i
        add();
        idxr();
        push_symbol(base+1);//atrg
        push_symbol(base+4);//sttrg
        push_symbol(base+5);//i
        add();
        assign2(idxxl());
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
    line(129);
    push_symbol(base+1);//atrg
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_aiins(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("aiins",base);
//
    line(134);
    push_symbol(base+0);//a
    push_symbol(base+0);//a
    _clp_len(1);
    addnum(1);
    _clp_asize(2);
    pop();
    line(135);
    push_symbol(base+0);//a
    push_symbol(base+1);//x
    _clp_ains(2);
    pop();
    line(136);
    push_symbol(base+2);//v
    push_symbol(base+0);//a
    push_symbol(base+1);//x
    assign2(idxxl());
    pop();
    line(137);
    push_symbol(base+0);//a
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_addel(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("addel",base);
//
    line(142);
    push_symbol(base+0);//a
    push_symbol(base+1);//x
    _clp_adel(2);
    pop();
    line(143);
    push_symbol(base+0);//a
    push_symbol(base+0);//a
    _clp_len(1);
    addnum(-1);
    _clp_asize(2);
    pop();
    line(144);
    push_symbol(base+0);//a
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_apush(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("apush",base);
//
    line(149);
    push_symbol(base+0);//a
    push_symbol(base+1);//v
    _clp_aadd(2);
    pop();
    line(150);
    push_symbol(base+1);//v
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_apop(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("apop",base);
//
    line(155);
    push_symbol(base+0);//a
    _clp_len(1);
    assign(base+1);//len
    pop();
    line(159);
    line(156);
    push_symbol(base+1);//len
    push(&ONE);
    gteq();
    cmp_1338:;
    if(!flag()) goto if_18_1;
        line(157);
        push_symbol(base+0);//a
        push_symbol(base+1);//len
        idxr();
        assign(base+2);//v
        pop();
        line(158);
        push_symbol(base+0);//a
        push_symbol(base+1);//len
        addnum(-1);
        _clp_asize(2);
        pop();
    if_18_1:
    if_18_0:;
    line(160);
    push_symbol(base+2);//v
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_arev(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+4)PUSHNIL();
argno=1;
push_call("arev",base);
//
    line(165);
    push_symbol(base+0);//a
    _clp_len(1);
    assign(base+1);//len
    pop();
    line(170);
    {
    line(166);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_19_0:
    push_symbol(base+1);//len
    number(2);
    div();
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_19_2;
        line(167);
        push_symbol(base+0);//a
        push_symbol(base+2);//n
        idxr();
        assign(base+3);//x
        pop();
        line(168);
        push_symbol(base+0);//a
        push_symbol(base+1);//len
        push_symbol(base+2);//n
        sub();
        addnum(1);
        idxr();
        push_symbol(base+0);//a
        push_symbol(base+2);//n
        assign2(idxxl());
        pop();
        line(169);
        push_symbol(base+3);//x
        push_symbol(base+0);//a
        push_symbol(base+1);//len
        push_symbol(base+2);//n
        sub();
        addnum(1);
        assign2(idxxl());
        pop();
    lab_19_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_19_0;
    lab_19_2:;
    }
    line(171);
    push_symbol(base+0);//a
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_acat(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+5)PUSHNIL();
argno=2;
push_call("acat",base);
//
    line(176);
    line(177);
    push_symbol(base+0);//a
    _clp_len(1);
    assign(base+2);//lena
    pop();
    line(178);
    push_symbol(base+1);//b
    _clp_len(1);
    assign(base+3);//lenb
    pop();
    line(179);
    push_symbol(base+0);//a
    push_symbol(base+2);//lena
    push_symbol(base+3);//lenb
    add();
    _clp_asize(2);
    pop();
    line(182);
    {
    line(180);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_20_0:
    push_symbol(base+3);//lenb
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_20_2;
        line(181);
        push_symbol(base+1);//b
        push_symbol(base+4);//n
        idxr();
        push_symbol(base+0);//a
        push_symbol(base+2);//lena
        push_symbol(base+4);//n
        add();
        assign2(idxxl());
        pop();
    lab_20_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_20_0;
    lab_20_2:;
    }
    line(183);
    push_symbol(base+0);//a
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
    line(188);
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
    push_symbol(base+1);//x
    push_symbol(base+2);//y
    lt();
    cmp_1714:;
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================

