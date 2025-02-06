//input: ppo/normalize.ppo (5.7.0.1)

#include <cccdef.h>

extern void _clp_dirsep(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_normalize(int argno);
extern void _clp_strtran(int argno);
extern void _clp_substr(int argno);

//=======================================================================
void _clp_normalize(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+4)PUSHNIL();
argno=1;
push_call("normalize",base);
//
    line(28);
    line(39);
    {
    line(30);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_1_0:
    push_symbol(base+0);//todo
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(38);
        {
        line(31);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+1);//i
        lab_2_0:
        push_symbol(base+0);//todo
        push_symbol(base+2);//n
        idxr();
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_2_2;
            line(32);
            push_symbol(base+0);//todo
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+1);//i
            idxr();
            assign(base+3);//x
            pop();
            line(33);
            push_symbol(base+3);//x
            _clp_dirsep(0);
            string(L".");
            add();
            _clp_dirsep(0);
            add();
            _clp_dirsep(0);
            _clp_strtran(3);
            assign(base+3);//x
            pop();
            line(36);
            line(34);
            push_symbol(base+3);//x
            number(2);
            _clp_left(2);
            string(L".");
            _clp_dirsep(0);
            add();
            eqeq();
            cmp_178:;
            if(!flag()) goto if_3_1;
                line(35);
                push_symbol(base+3);//x
                number(3);
                _clp_substr(2);
                assign(base+3);//x
                pop();
            if_3_1:
            if_3_0:;
            line(37);
            push_symbol(base+3);//x
            push_symbol(base+0);//todo
            push_symbol(base+2);//n
            idxr();
            push_symbol(base+1);//i
            assign2(idxxl());
            pop();
        lab_2_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+1);//i
        add();
        assign(base+1);//i
        goto lab_2_0;
        lab_2_2:;
        }
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
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

