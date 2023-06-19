//input: readpar.ppo (5.6.0)

#include <cccdef.h>

extern void _clp_aadd(int argno);
extern void _clp_ains(int argno);
extern void _clp_at(int argno);
extern void _clp_buildenv_bat(int argno);
extern void _clp_chr(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_empty(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_memoread(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);
extern void _clp_readpar(int argno);
extern void _clp_s_debug(int argno);
extern void _clp_split(int argno);
extern void _clp_strtran(int argno);

//=======================================================================
void _clp_readpar(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+7)PUSHNIL();
argno=3;
push_call("readpar",base);
//
    line(24);
    push_symbol(base+0);//parfil
    _clp_memoread(1);
    assign(base+3);//par
    pop();
    line(31);
    line(26);
    push_symbol(base+3);//par
    _clp_empty(1);
    if(!flag()) goto if_1_1;
        line(30);
        _clp_buildenv_bat(0);
        _clp_dirsep(0);
        add();
        push_symbol(base+0);//parfil
        add();
        _clp_memoread(1);
        assign(base+3);//par
        pop();
    if_1_1:
    if_1_0:;
    line(39);
    line(33);
    _clp_s_debug(0);
    if(!flag()) goto if_2_1;
        line(38);
        line(34);
        push_symbol(base+3);//par
        _clp_empty(1);
        if(!flag()) goto if_3_1;
            line(35);
            string(L"Build parfile empty:");
            push_symbol(base+0);//parfil
            _clp_qqout(2);
            pop();
            _clp_qout(0);
            pop();
        goto if_3_0;
        if_3_1:
        line(36);
            line(37);
            string(L"Build parfile:");
            push_symbol(base+0);//parfil
            _clp_qqout(2);
            pop();
            _clp_qout(0);
            pop();
        if_3_2:
        if_3_0:;
    if_2_1:
    if_2_0:;
    line(41);
    push_symbol(base+3);//par
    number(13);
    _clp_chr(1);
    string(L"");
    _clp_strtran(3);
    assign(base+3);//par
    pop();
    line(42);
    push_symbol(base+3);//par
    number(10);
    _clp_chr(1);
    _clp_split(2);
    assign(base+3);//par
    pop();
    line(58);
    {
    line(44);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+4);//n
    lab_4_0:
    push_symbol(base+3);//par
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
        line(45);
        push_symbol(base+3);//par
        push_symbol(base+4);//n
        idxr();
        assign(base+5);//p
        pop();
        line(48);
        line(46);
        string(L"#");
        push_symbol(base+5);//p
        ss();
        if(!flag()) goto if_5_1;
            line(47);
            push_symbol(base+5);//p
            string(L"#");
            push_symbol(base+5);//p
            _clp_at(2);
            addnum(-1);
            _clp_left(2);
            assign(base+5);//p
            pop();
        if_5_1:
        if_5_0:;
        line(50);
        push_symbol(base+5);//p
        string(L" ");
        _clp_split(2);
        assign(base+5);//p
        pop();
        line(57);
        {
        line(51);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+6);//i
        lab_6_0:
        push_symbol(base+5);//p
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_6_2;
            line(56);
            line(52);
            push_symbol(base+5);//p
            push_symbol(base+6);//i
            idxr();
            _clp_empty(1);
            topnot();
            if(!flag()) goto if_7_1;
                line(53);
                push_symbol(base+1);//opt
                push(&NIL);
                _clp_aadd(2);
                pop();
                line(54);
                push_symbol(base+1);//opt
                push_symbol(base+2);//optx
                push(&ONE);
                add();
                assign(base+2);//optx
                _clp_ains(2);
                pop();
                line(55);
                push_symbol(base+5);//p
                push_symbol(base+6);//i
                idxr();
                push_symbol(base+1);//opt
                push_symbol(base+2);//optx
                assign2(idxxl());
                pop();
            if_7_1:
            if_7_0:;
        lab_6_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+6);//i
        add();
        assign(base+6);//i
        goto lab_6_0;
        lab_6_2:;
        }
    lab_4_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+4);//n
    add();
    assign(base+4);//n
    goto lab_4_0;
    lab_4_2:;
    }
    line(59);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

