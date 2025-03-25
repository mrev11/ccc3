//input: ppo/psort.ppo (5.7.0.1)

#include <cccdef.h>

extern void _clp_len(int argno);
extern void _clp_psort(int argno);
static void _clp_ruleidx(int argno);
extern void _clp_s_rules(int argno);

namespace _nsp_filespec{
extern void _clp_extension(int argno);
}//namespace filespec

//=======================================================================
void _clp_psort(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("psort",base);
//
    line(24);
    push_symbol(base+0);//x
    idxr0(2);
    _nsp_filespec::_clp_extension(1);
    push_symbol(base+0);//x
    idxr0(1);
    _nsp_filespec::_clp_extension(1);
    _clp_ruleidx(2);
    assign(base+2);//ix
    pop();
    line(25);
    push_symbol(base+1);//y
    idxr0(2);
    _nsp_filespec::_clp_extension(1);
    push_symbol(base+1);//y
    idxr0(1);
    _nsp_filespec::_clp_extension(1);
    _clp_ruleidx(2);
    assign(base+3);//iy
    pop();
    line(26);
    push_symbol(base+2);//ix
    push_symbol(base+3);//iy
    eqeq();
    cmp_149:;
    if(flag()){
    push_symbol(base+0);//x
    idxr0(1);
    push_symbol(base+1);//y
    idxr0(1);
    lt();
    cmp_161:;
    }else{
    push_symbol(base+2);//ix
    push_symbol(base+3);//iy
    lt();
    cmp_173:;
    }
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_ruleidx(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("ruleidx",base);
//
    line(31);
    line(36);
    {
    line(32);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_1_0:
    _clp_s_rules(0);
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(35);
        line(33);
        push_symbol(base+0);//e1
        _clp_s_rules(0);
        push_symbol(base+2);//n
        idxr();
        idxr0(1);
        eqeq();
        cmp_241:;
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+1);//e2
        _clp_s_rules(0);
        push_symbol(base+2);//n
        idxr();
        idxr0(2);
        eqeq();
        cmp_263:;
        }
        if(!flag()) goto if_2_1;
            line(34);
            push_symbol(base+2);//n
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_2_1:
        if_2_0:;
    lab_1_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+2);//n
    add();
    assign(base+2);//n
    goto lab_1_0;
    lab_1_2:;
    }
    line(37);
    push(&ZERO);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

