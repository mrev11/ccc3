//input: ppo/search_include.ppo (5.7.0.1)

#include <cccdef.h>

static void _blk_adddep_0(int argno);
static void _blk_byrules_0(int argno);
static void _blk_byrules_1(int argno);
extern void _clp_aadd(int argno);
static void _clp_adddep(int argno);
extern void _clp_alltrim(int argno);
extern void _clp_ascan(int argno);
extern void _clp_at(int argno);
static void _clp_byhand(int argno);
static void _clp_byrules(int argno);
extern void _clp_chr(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_fext(int argno);
extern void _clp_file(int argno);
extern void _clp_fname(int argno);
extern void _clp_fpath(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_resource_hash(int argno);
extern void _clp_s_rules(int argno);
static void _clp_search_file(int argno);
extern void _clp_search_include(int argno);
extern void _clp_strtran(int argno);
extern void _clp_substr(int argno);

//=======================================================================
void _clp_search_include(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+13)PUSHNIL();
argno=4;
push_call("search_include",base);
//
    line(25);
    number(10);
    _clp_chr(1);
    assign(base+4);//nl
    pop();
    line(26);
    string(L"#include");
    assign(base+5);//include
    pop();
    line(27);
    push_symbol(base+5);//include
    _clp_len(1);
    assign(base+6);//lenincl
    pop();
    line(28);
    push(&ZERO);
    assign(base+8);//n2
    pop();
    line(65);
    lab_1_1:
    line(30);
    push_symbol(base+5);//include
    push_symbol(base+0);//txt
    push_symbol(base+8);//n2
    addnum(1);
    _clp_at(3);
    assign(base+7);//n1
    push(&ZERO);
    gt();
    cmp_153:;
    if(!flag()) goto lab_1_2;
        line(34);
        line(32);
        push(&ZERO);
        push_symbol(base+4);//nl
        push_symbol(base+0);//txt
        push_symbol(base+7);//n1
        push_symbol(base+6);//lenincl
        add();
        _clp_at(3);
        assign(base+8);//n2
        eqeq();
        cmp_167:;
        if(!flag()) goto if_2_1;
            line(33);
            push_symbol(base+0);//txt
            _clp_len(1);
            addnum(1);
            assign(base+8);//n2
            pop();
        if_2_1:
        if_2_0:;
        line(36);
        push_symbol(base+0);//txt
        push_symbol(base+7);//n1
        push_symbol(base+6);//lenincl
        add();
        push_symbol(base+8);//n2
        push_symbol(base+7);//n1
        sub();
        push_symbol(base+6);//lenincl
        sub();
        _clp_substr(3);
        assign(base+9);//line
        pop();
        line(37);
        push_symbol(base+9);//line
        number(9);
        _clp_chr(1);
        string(L"");
        _clp_strtran(3);
        assign(base+9);//line
        pop();
        line(38);
        push_symbol(base+9);//line
        _clp_alltrim(1);
        assign(base+9);//line
        pop();
        line(46);
        line(40);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"\"");
        eqeq();
        cmp_360:;
        if(!flag()) goto if_3_1;
            line(41);
            string(L"\"");
            assign(base+10);//delim
            pop();
        goto if_3_0;
        if_3_1:
        line(42);
        push_symbol(base+9);//line
        push(&ONE);
        _clp_left(2);
        string(L"<");
        eqeq();
        cmp_401:;
        if(!flag()) goto if_3_2;
            line(43);
            string(L">");
            assign(base+10);//delim
            pop();
        goto if_3_0;
        if_3_2:
        line(44);
            line(45);
            goto lab_1_1;//loop
        if_3_3:
        if_3_0:;
        line(50);
        line(48);
        push(&ZERO);
        push_symbol(base+10);//delim
        push_symbol(base+9);//line
        number(2);
        _clp_at(3);
        assign(base+11);//dpos
        eqeq();
        cmp_443:;
        if(!flag()) goto if_4_1;
            line(49);
            goto lab_1_1;//loop
        if_4_1:
        if_4_0:;
        line(52);
        push_symbol(base+9);//line
        number(2);
        push_symbol(base+11);//dpos
        addnum(-2);
        _clp_substr(3);
        assign(base+12);//f
        pop();
        line(53);
        push_symbol(base+12);//f
        string(L"/");
        _clp_dirsep(0);
        _clp_strtran(3);
        assign(base+12);//f
        pop();
        line(54);
        push_symbol(base+12);//f
        string(L"\\");
        _clp_dirsep(0);
        _clp_strtran(3);
        assign(base+12);//f
        pop();
        line(64);
        line(56);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byrules(4);
        if(!flag()) goto if_5_1;
        goto if_5_0;
        if_5_1:
        line(59);
        push_symbol(base+12);//f
        push_symbol(base+1);//dep
        push_symbol(base+2);//dir
        push_symbol(base+3);//todo
        _clp_byhand(4);
        if(!flag()) goto if_5_2;
        goto if_5_0;
        if_5_2:
        line(62);
        if_5_3:
        if_5_0:;
    goto lab_1_1;
    lab_1_2:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_byhand(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+5)PUSHNIL();
argno=4;
push_call("byhand",base);
//
    line(76);
    push_symbol(base+2);//dir
    push_symbol(base+0);//f
    _clp_search_file(2);
    assign(base+4);//pn
    pop();
    line(81);
    line(78);
    push_symbol(base+4);//pn
    push(&NIL);
    neeq();
    cmp_756:;
    if(!flag()) goto if_6_1;
        line(79);
        push_symbol(base+1);//dep
        push_symbol(base+4);//pn
        _clp_adddep(2);
        pop();
        line(80);
        push(&TRUE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_6_1:
    if_6_0:;
    line(82);
    push(&FALSE);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_byrules(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+12)PUSHNIL();
argno=4;
push_call("byrules",base);
//
    line(92);
    push_symbol(base+0);//fil
    _clp_fname(1);
    assign(base+4);//f
    pop();
    line(93);
    push_symbol(base+0);//fil
    _clp_fext(1);
    assign(base+5);//e
    pop();
    line(94);
    line(95);
    line(96);
    line(97);
    push(&FALSE);
    assign(base+11);//result
    pop();
    line(103);
    line(99);
    push_symbol(base+5);//e
    string(L".ch");
    eqeq();
    cmp_924:;
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+4);//f
    idxr0(1);
    string(L"_");
    eqeq();
    cmp_937:;
    topnot();
    }
    if(!flag()) goto if_7_1;
        line(102);
        push(&FALSE);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_7_1:
    if_7_0:;
    line(130);
    {
    line(105);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//i
    lab_8_0:
    _clp_s_rules(0);
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_8_2;
        line(129);
        line(107);
        _clp_s_rules(0);
        push_symbol(base+9);//i
        idxr();
        idxr0(2);
        push_symbol(base+5);//e
        eqeq();
        cmp_1009:;
        if(!flag()) goto if_9_1;
            line(109);
            _clp_s_rules(0);
            push_symbol(base+9);//i
            idxr();
            idxr0(1);
            assign(base+8);//e0
            pop();
            line(128);
            line(114);
            push(&NIL);
            _clp_resource_hash(0);
            push_symbol(base+4);//f
            push_symbol(base+8);//e0
            add();
            idxr();
            assign(base+7);//r
            neeq();
            cmp_1048:;
            if(!flag()) goto if_10_1;
                line(115);
                push_symbol(base+7);//r
                _clp_fpath(1);
                assign(base+6);//p
                pop();
                line(116);
                push_symbol(base+1);//dep
                push_symbol(base+6);//p
                push_symbol(base+4);//f
                add();
                push_symbol(base+5);//e
                add();
                _clp_adddep(2);
                pop();
                line(126);
                line(117);
                push(&ZERO);
                push_symbol(base+3);//todo
                push_symbol_ref(base+6);//p
                push_symbol_ref(base+4);//f
                push_symbol_ref(base+5);//e
                block(_blk_byrules_0,3);
                _clp_ascan(2);
                assign(base+10);//x
                eqeq();
                cmp_1131:;
                if(!flag()) goto if_11_1;
                    line(118);
                    push_symbol(base+3);//todo
                    push_symbol(base+6);//p
                    push_symbol(base+4);//f
                    add();
                    push_symbol(base+5);//e
                    add();
                    push_symbol(base+6);//p
                    push_symbol(base+4);//f
                    add();
                    push_symbol(base+8);//e0
                    add();
                    array(2);
                    _clp_aadd(2);
                    pop();
                goto if_11_0;
                if_11_1:
                line(119);
                push(&ZERO);
                push_symbol(base+3);//todo
                push_symbol(base+10);//x
                idxr();
                push_symbol_ref(base+6);//p
                push_symbol_ref(base+4);//f
                push_symbol_ref(base+8);//e0
                block(_blk_byrules_1,3);
                _clp_ascan(2);
                eqeq();
                cmp_1245:;
                if(!flag()) goto if_11_2;
                    line(120);
                    push_symbol(base+3);//todo
                    push_symbol(base+10);//x
                    idxr();
                    push_symbol(base+6);//p
                    push_symbol(base+4);//f
                    add();
                    push_symbol(base+8);//e0
                    add();
                    _clp_aadd(2);
                    pop();
                if_11_2:
                if_11_0:;
                line(127);
                push(&TRUE);
                assign(base+11);//result
                pop();
            if_10_1:
            if_10_0:;
        if_9_1:
        if_9_0:;
    lab_8_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+9);//i
    add();
    assign(base+9);//i
    goto lab_8_0;
    lab_8_2:;
    }
    line(131);
    push_symbol(base+11);//result
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_byrules_0(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_byrules_0",base);
//
    push_symbol(base+1);//x
    idxr0(1);
    push_symbol(env+0);//p
    push_symbol(env+1);//f
    add();
    push_symbol(env+2);//e
    add();
    eqeq();
    cmp_1159:;
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk_byrules_1(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_byrules_1",base);
//
    push_symbol(base+1);//x
    push_symbol(env+0);//p
    push_symbol(env+1);//f
    add();
    push_symbol(env+2);//e0
    add();
    eqeq();
    cmp_1269:;
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
static void _clp_search_file(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("search_file",base);
//
    line(137);
    line(144);
    {
    line(139);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_12_0:
    push_symbol(base+0);//dirlist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_12_2;
        line(140);
        push_symbol(base+0);//dirlist
        push_symbol(base+2);//n
        idxr();
        _clp_dirsep(0);
        add();
        push_symbol(base+1);//fnamext
        add();
        assign(base+3);//pathname
        pop();
        line(143);
        line(141);
        push_symbol(base+3);//pathname
        _clp_file(1);
        if(!flag()) goto if_13_1;
            line(142);
            push_symbol(base+3);//pathname
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_13_1:
        if_13_0:;
    lab_12_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_12_0;
    lab_12_2:;
    }
    line(145);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_adddep(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("adddep",base);
//
    line(151);
    line(149);
    push(&ZERO);
    push_symbol(base+0);//dep
    push_symbol_ref(base+1);//x
    block(_blk_adddep_0,1);
    _clp_ascan(2);
    eqeq();
    cmp_1531:;
    if(!flag()) goto if_14_1;
        line(150);
        push_symbol(base+0);//dep
        push_symbol(base+1);//x
        _clp_aadd(2);
        pop();
    if_14_1:
    if_14_0:;
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_adddep_0(int argno)
{
VALUE *base=stack-argno;
VALUE *env=blkenv(base);
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk_adddep_0",base);
//
    push_symbol(base+1);//d
    push_symbol(env+0);//x
    eqeq();
    cmp_1550:;
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================

