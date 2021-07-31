//input: rule.ppo (5.3.0)

#include <cccdef.h>

static void _blk_rule_df_get_0(int argno);
static void _blk_rule_tr_get_0(int argno);
extern void _clp_aadd(int argno);
extern void _clp_adel(int argno);
extern void _clp_array(int argno);
extern void _clp_asc(int argno);
extern void _clp_asize(int argno);
extern void _clp_asort(int argno);
extern void _clp_cx_df_get(int argno);
static void _clp_cx_set(int argno);
extern void _clp_cx_tr_get(int argno);
extern void _clp_int(int argno);
extern void _clp_len(int argno);
extern void _clp_rule_df_add(int argno);
extern void _clp_rule_df_del(int argno);
extern void _clp_rule_df_get(int argno);
extern void _clp_rule_if_add(int argno);
extern void _clp_rule_if_get(int argno);
extern void _clp_rule_search(int argno);
extern void _clp_rule_tr_add(int argno);
extern void _clp_rule_tr_get(int argno);
extern void _clp_strtran(int argno);
extern void _clp_upper(int argno);
extern void _clp_valtype(int argno);
static void _ini__rule_df();
static void _ini__rule_info();
static void _ini__rule_tr();

MUTEX_CREATE(_mutex_rule_tr);
static VALUE* _st_rule_tr_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_rule_tr);
    static stvar _st_rule_tr(_ini__rule_tr);
    MUTEX_UNLOCK(_mutex_rule_tr);
    SIGNAL_UNLOCK();
    return _st_rule_tr.ptr;
}
MUTEX_CREATE(_mutex_rule_df);
static VALUE* _st_rule_df_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_rule_df);
    static stvar _st_rule_df(_ini__rule_df);
    MUTEX_UNLOCK(_mutex_rule_df);
    SIGNAL_UNLOCK();
    return _st_rule_df.ptr;
}
MUTEX_CREATE(_mutex_rule_info);
static VALUE* _st_rule_info_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_rule_info);
    static stvar _st_rule_info(_ini__rule_info);
    MUTEX_UNLOCK(_mutex_rule_info);
    SIGNAL_UNLOCK();
    return _st_rule_info.ptr;
}
static VALUE* _st_cx_tr_ptr()
{
    static stvar _st_cx_tr;
    return _st_cx_tr.ptr;
}
static VALUE* _st_cx_df_ptr()
{
    static stvar _st_cx_df;
    return _st_cx_df.ptr;
}
MUTEX_CREATE(_mutex_sort_df);
static VALUE* _st_sort_df_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_sort_df);
    static stvar _st_sort_df(&TRUE);
    MUTEX_UNLOCK(_mutex_sort_df);
    SIGNAL_UNLOCK();
    return _st_sort_df.ptr;
}
MUTEX_CREATE(_mutex_sort_tr);
static VALUE* _st_sort_tr_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_sort_tr);
    static stvar _st_sort_tr(&TRUE);
    MUTEX_UNLOCK(_mutex_sort_tr);
    SIGNAL_UNLOCK();
    return _st_sort_tr.ptr;
}

static void _ini__rule_tr()
{
    array(0);
}

static void _ini__rule_df()
{
    array(0);
}

static void _ini__rule_info()
{
    array(0);
}
//=======================================================================
void _clp_rule_tr_add(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("rule_tr_add",base);
//
    line(35);
    line(42);
    {
    line(38);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_1_0:
    push_symbol(base+0);//r
    idxr0(1);
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(41);
        line(39);
        push_symbol(base+0);//r
        idxr0(1);
        push_symbol(base+1);//n
        idxr();
        _clp_valtype(1);
        string(L"CX");
        ss();
        if(!flag()) goto if_2_1;
            line(40);
            push_symbol(base+0);//r
            idxr0(1);
            push_symbol(base+1);//n
            idxr();
            _clp_upper(1);
            push_symbol(base+0);//r
            idxr0(1);
            push_symbol(base+1);//n
            assign2(idxxl());
            pop();
        if_2_1:
        if_2_0:;
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
    line(44);
    push_symbol(_st_rule_tr_ptr());//global
    _clp_len(1);
    addnum(1);
    push_symbol(base+0);//r
    assign2(idxxl0(3));
    pop();
    line(45);
    push_symbol(_st_rule_tr_ptr());//global
    push_symbol(base+0);//r
    _clp_aadd(2);
    pop();
    line(47);
    push(&FALSE);
    assign(_st_sort_tr_ptr());//global
    pop();
    line(48);
    push(&NIL);
    assign(_st_cx_tr_ptr());//global
    pop();
    line(49);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_rule_tr_get(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("rule_tr_get",base);
//
    line(63);
    line(55);
    push_symbol(_st_sort_tr_ptr());//global
    topnot();
    if(!flag()) goto if_3_1;
        line(56);
        push(&TRUE);
        assign(_st_sort_tr_ptr());//global
        pop();
        line(57);
        push_symbol(_st_rule_tr_ptr());//global
        push(&NIL);
        push(&NIL);
        block(_blk_rule_tr_get_0,0);
        _clp_asort(4);
        pop();
    if_3_1:
    if_3_0:;
    line(65);
    push_symbol(_st_rule_tr_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_rule_tr_get_0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_rule_tr_get_0",base);
//
    push_blkarg(base+1);//x
    idxr0(1);
    idxr0(1);
    push_blkarg(base+2);//y
    idxr0(1);
    idxr0(1);
    lt();
    if(flag()){
    push(&TRUE);
    }else{
    push_blkarg(base+1);//x
    idxr0(1);
    idxr0(1);
    push_blkarg(base+2);//y
    idxr0(1);
    idxr0(1);
    eqeq();
    if(!flag()){
    push(&FALSE);
    }else{
    push_blkarg(base+1);//x
    idxr0(3);
    push_blkarg(base+2);//y
    idxr0(3);
    gt();
    }
    }
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
void _clp_rule_df_add(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("rule_df_add",base);
//
    line(70);
    push_symbol(_st_rule_df_ptr());//global
    _clp_len(1);
    addnum(1);
    push_symbol(base+0);//r
    assign2(idxxl0(3));
    pop();
    line(71);
    push_symbol(_st_rule_df_ptr());//global
    push_symbol(base+0);//r
    _clp_aadd(2);
    pop();
    line(72);
    push(&FALSE);
    assign(_st_sort_df_ptr());//global
    pop();
    line(73);
    push(&NIL);
    assign(_st_cx_df_ptr());//global
    pop();
    line(74);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_rule_df_del(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("rule_df_del",base);
//
    line(80);
    push(&ONE);
    assign(base+1);//n
    pop();
    line(89);
    lab_4_1:
    line(82);
    push_symbol(base+1);//n
    push_symbol(_st_rule_df_ptr());//global
    _clp_len(1);
    lteq();
    if(!flag()) goto lab_4_2;
        line(88);
        line(83);
        push_symbol(_st_rule_df_ptr());//global
        push_symbol(base+1);//n
        idxr();
        idxr0(1);
        idxr0(1);
        push_symbol(base+0);//symbol
        eqeq();
        if(!flag()) goto if_5_1;
            line(84);
            push_symbol(_st_rule_df_ptr());//global
            push_symbol(base+1);//n
            _clp_adel(2);
            pop();
            line(85);
            push_symbol(_st_rule_df_ptr());//global
            push_symbol(_st_rule_df_ptr());//global
            _clp_len(1);
            addnum(-1);
            _clp_asize(2);
            pop();
        goto if_5_0;
        if_5_1:
        line(86);
            line(87);
            push_symbol(base+1);//n
            dup();
            push(&ONE);
            add();
            assign(base+1);//n
            pop();
            pop();
        if_5_2:
        if_5_0:;
    goto lab_4_1;
    lab_4_2:;
    line(91);
    push(&FALSE);
    assign(_st_sort_df_ptr());//global
    pop();
    line(92);
    push(&NIL);
    assign(_st_cx_df_ptr());//global
    pop();
    line(93);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_rule_df_get(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("rule_df_get",base);
//
    line(110);
    line(99);
    push_symbol(_st_sort_df_ptr());//global
    topnot();
    if(!flag()) goto if_6_1;
        line(100);
        push(&TRUE);
        assign(_st_sort_df_ptr());//global
        pop();
        line(101);
        push_symbol(_st_rule_df_ptr());//global
        push(&NIL);
        push(&NIL);
        block(_blk_rule_df_get_0,0);
        _clp_asort(4);
        pop();
    if_6_1:
    if_6_0:;
    line(111);
    push_symbol(_st_rule_df_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_rule_df_get_0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_rule_df_get_0",base);
//
    push_blkarg(base+1);//x
    idxr0(1);
    idxr0(1);
    push_blkarg(base+2);//y
    idxr0(1);
    idxr0(1);
    lt();
    if(flag()){
    push(&TRUE);
    }else{
    push_blkarg(base+1);//x
    idxr0(1);
    idxr0(1);
    push_blkarg(base+2);//y
    idxr0(1);
    idxr0(1);
    eqeq();
    if(!flag()){
    push(&FALSE);
    }else{
    push_blkarg(base+1);//x
    idxr0(3);
    push_blkarg(base+2);//y
    idxr0(3);
    lt();
    }
    }
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
void _clp_rule_search(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+10)PUSHNIL();
argno=3;
push_call("rule_search",base);
//
    line(120);
    line(121);
    push_symbol(base+1);//symbol
    assign(base+5);//val0
    pop();
    line(122);
    push(&ZERO);
    assign(base+7);//ge
    pop();
    line(131);
    line(124);
    push_symbol(base+2);//cx
    push(&NIL);
    eqeq();
    if(!flag()) goto if_7_1;
        line(125);
        push(&ONE);
        assign(base+3);//nlow
        pop();
        line(126);
        push_symbol(base+0);//rule
        _clp_len(1);
        assign(base+4);//nhigh
        pop();
    goto if_7_0;
    if_7_1:
    line(127);
        line(128);
        push_symbol(base+1);//symbol
        _clp_asc(1);
        addnum(1);
        assign(base+9);//c
        pop();
        line(129);
        push_symbol(base+2);//cx
        push_symbol(base+9);//c
        idxr();
        assign(base+3);//nlow
        pop();
        line(130);
        push_symbol(base+2);//cx
        push_symbol(base+9);//c
        addnum(1);
        idxr();
        addnum(-1);
        assign(base+4);//nhigh
        pop();
    if_7_2:
    if_7_0:;
    line(148);
    lab_8_1:
    line(135);
    push_symbol(base+3);//nlow
    push_symbol(base+4);//nhigh
    lteq();
    if(!flag()) goto lab_8_2;
        line(139);
        push_symbol(base+3);//nlow
        push_symbol(base+4);//nhigh
        add();
        number(2);
        div();
        _clp_int(1);
        assign(base+8);//i
        pop();
        line(140);
        push_symbol(base+0);//rule
        push_symbol(base+8);//i
        idxr();
        idxr0(1);
        idxr0(1);
        assign(base+6);//val1
        pop();
        line(147);
        line(142);
        push_symbol(base+6);//val1
        push_symbol(base+5);//val0
        gteq();
        if(!flag()) goto if_9_1;
            line(143);
            push_symbol(base+8);//i
            assign(base+7);//ge
            pop();
            line(144);
            push_symbol(base+8);//i
            addnum(-1);
            assign(base+4);//nhigh
            pop();
        goto if_9_0;
        if_9_1:
        line(145);
            line(146);
            push_symbol(base+8);//i
            addnum(1);
            assign(base+3);//nlow
            pop();
        if_9_2:
        if_9_0:;
    goto lab_8_1;
    lab_8_2:;
    line(163);
    push_symbol(base+7);//ge
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_rule_if_add(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("rule_if_add",base);
//
    line(170);
    lab_10_1:
    line(168);
    binary(" ");
    push_symbol(base+0);//info
    ss();
    if(!flag()) goto lab_10_2;
        line(169);
        push_symbol(base+0);//info
        binary(" ");
        binary("");
        _clp_strtran(3);
        assign(base+0);//info
        pop();
    goto lab_10_1;
    lab_10_2:;
    line(171);
    push_symbol(_st_rule_info_ptr());//global
    push_symbol(base+0);//info
    _clp_upper(1);
    _clp_aadd(2);
    pop();
    line(172);
    push_symbol(_st_rule_info_ptr());//global
    _clp_len(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_rule_if_get(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("rule_if_get",base);
//
    line(177);
    push_symbol(_st_rule_info_ptr());//global
    push_symbol(base+0);//idx
    idxr();
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_cx_tr_get(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("cx_tr_get",base);
//
    line(185);
    line(182);
    push_symbol(_st_cx_tr_ptr());//global
    push(&NIL);
    eqeq();
    if(!flag()) goto if_11_1;
        line(183);
        number(257);
        _clp_array(1);
        assign(_st_cx_tr_ptr());//global
        pop();
        line(184);
        push_symbol(_st_rule_tr_ptr());//global
        push_symbol(_st_cx_tr_ptr());//global
        _clp_cx_set(2);
        pop();
    if_11_1:
    if_11_0:;
    line(186);
    push_symbol(_st_cx_tr_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_cx_df_get(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("cx_df_get",base);
//
    line(194);
    line(191);
    push_symbol(_st_cx_df_ptr());//global
    push(&NIL);
    eqeq();
    if(!flag()) goto if_12_1;
        line(192);
        number(257);
        _clp_array(1);
        assign(_st_cx_df_ptr());//global
        pop();
        line(193);
        push_symbol(_st_rule_df_ptr());//global
        push_symbol(_st_cx_df_ptr());//global
        _clp_cx_set(2);
        pop();
    if_12_1:
    if_12_0:;
    line(195);
    push_symbol(_st_cx_df_ptr());//global
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_cx_set(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+6)PUSHNIL();
argno=2;
push_call("cx_set",base);
//
    line(200);
    line(202);
    push_symbol(base+0);//rule
    _clp_len(1);
    assign(base+2);//lr
    pop();
    line(214);
    {
    line(204);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_13_0:
    push_symbol(base+2);//lr
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_13_2;
        line(209);
        push_symbol(base+0);//rule
        push_symbol(base+4);//n
        idxr();
        idxr0(1);
        idxr0(1);
        _clp_asc(1);
        addnum(1);
        assign(base+3);//c
        pop();
        line(213);
        line(211);
        push_symbol(base+1);//cx
        push_symbol(base+3);//c
        idxr();
        push(&NIL);
        eqeq();
        if(!flag()) goto if_14_1;
            line(212);
            push_symbol(base+4);//n
            push_symbol(base+1);//cx
            push_symbol(base+3);//c
            assign2(idxxl());
            pop();
        if_14_1:
        if_14_0:;
    lab_13_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_13_0;
    lab_13_2:;
    }
    line(216);
    push_symbol(base+2);//lr
    addnum(1);
    assign(base+5);//p
    pop();
    line(223);
    {
    line(217);
    number(-1);
    int sg=sign();
    number(257);
    assign(base+4);//n
    lab_15_0:
    push(&ONE);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_15_2;
        line(222);
        line(218);
        push_symbol(base+1);//cx
        push_symbol(base+4);//n
        idxr();
        push(&NIL);
        eqeq();
        if(!flag()) goto if_16_1;
            line(219);
            push_symbol(base+5);//p
            push_symbol(base+1);//cx
            push_symbol(base+4);//n
            assign2(idxxl());
            pop();
        goto if_16_0;
        if_16_1:
        line(220);
            line(221);
            push_symbol(base+1);//cx
            push_symbol(base+4);//n
            idxr();
            assign(base+5);//p
            pop();
        if_16_2:
        if_16_0:;
    lab_15_1:
    number(-1);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_15_0;
    lab_15_2:;
    }
    line(230);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

