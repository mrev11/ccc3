//input: alert.ppo (5.3.0)

#include <cccdef.h>

static void _blk_alertblock_0(int argno);
extern void _clp_alert(int argno);
extern void _clp_alertblock(int argno);
static void _clp_default_alert(int argno);
extern void _clp_eval(int argno);
extern void _clp_len(int argno);
extern void _clp_qout(int argno);
extern void _clp_split(int argno);
extern void _clp_valtype(int argno);
static void _ini_alertblock_sblk(VALUE*);

//=======================================================================
void _clp_alert(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("alert",base);
//
    line(23);
    _clp_alertblock(0);
    push_symbol(base+0);//txt
    push_symbol(base+1);//alts
    _clp_eval(3);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_alertblock(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("alertblock",base);
//
    line(28);
    static stvarloc _st_sblk(_ini_alertblock_sblk,base);
    line(29);
    line(30);
    push_symbol(_st_sblk.ptr);//alertblock
    assign(base+1);//pblk
    pop();
    line(33);
    line(31);
    push_symbol(base+0);//blk
    _clp_valtype(1);
    string(L"B");
    eqeq();
    if(!flag()) goto if_1_1;
        line(32);
        push_symbol(base+0);//blk
        assign(_st_sblk.ptr);//alertblock
        pop();
    if_1_1:
    if_1_0:;
    line(34);
    push_symbol(base+1);//pblk
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _ini_alertblock_sblk(VALUE* base)
{
    block(_blk_alertblock_0,0);
}

static void _blk_alertblock_0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_alertblock_0",base);
//
    push_blkarg(base+1);//t
    push_blkarg(base+2);//a
    _clp_default_alert(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
static void _clp_default_alert(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("default_alert",base);
//
    line(39);
    line(40);
    string(L"ALERT");
    _clp_qout(1);
    pop();
    line(46);
    line(41);
    push_symbol(base+0);//txt
    _clp_valtype(1);
    string(L"C");
    eqeq();
    if(!flag()) goto if_2_1;
        line(42);
        push_symbol(base+0);//txt
        string(L";");
        _clp_split(2);
        assign(base+0);//txt
        pop();
        line(45);
        {
        line(43);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+1);//n
        lab_3_0:
        push_symbol(base+0);//txt
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_3_2;
            line(44);
            string(L" ");
            push_symbol(base+0);//txt
            push_symbol(base+1);//n
            idxr();
            _clp_qout(2);
            pop();
        lab_3_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+1);//n
        add();
        assign(base+1);//n
        goto lab_3_0;
        lab_3_2:;
        }
    if_2_1:
    if_2_0:;
    line(47);
    _clp_qout(0);
    pop();
    line(48);
    push(&ONE);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

