//input: ppo/ftime.ppo (5.7.0.1)

#include <cccdef.h>

extern void _clp_directory(int argno);
extern void _clp_dtos(int argno);
extern void _clp_ftime(int argno);
extern void _clp_len(int argno);

//=======================================================================
void _clp_ftime(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("ftime",base);
//
    line(26);
    push_symbol(base+0);//fspec
    string(L"H");
    _clp_directory(2);
    assign(base+1);//d
    pop();
    line(29);
    line(27);
    push_symbol(base+1);//d
    _clp_len(1);
    push(&ONE);
    eqeq();
    cmp_62:;
    if(!flag()) goto if_1_1;
        line(28);
        push_symbol(base+1);//d
        idxr0(1);
        idxr0(3);
        _clp_dtos(1);
        string(L"-");
        add();
        push_symbol(base+1);//d
        idxr0(1);
        idxr0(4);
        add();
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_1_1:
    if_1_0:;
    line(30);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

