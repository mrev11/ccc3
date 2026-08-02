//input: ppo/runredir.ppo (5.7.2)

#include <cccdef.h>

extern void _clp_fdup(int argno);
extern void _clp_runredir(int argno);
extern void _clp_spawn(int argno);
extern void _clp_split(int argno);
extern void _clp_strtran(int argno);
extern void _clp_valtype(int argno);

//=======================================================================
void _clp_runredir(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+5)PUSHNIL();
argno=3;
push_call("runredir",base);
//
    line(8);
    line(9);
    line(17);
    line(11);
    push_symbol(base+0);//cmd
    _clp_valtype(1);
    string(L"C");
    eqeq();
    cmp_60:;
    if(!flag()) goto if_1_1;
        line(15);
        lab_2_1:
        line(13);
        string(L"  ");
        push_symbol(base+0);//cmd
        ss();
        if(!flag()) goto lab_2_2;
            line(14);
            push_symbol(base+0);//cmd
            string(L"  ");
            string(L" ");
            _clp_strtran(3);
            assign(base+0);//cmd
            pop();
        goto lab_2_1;
        lab_2_2:;
        line(16);
        push_symbol(base+0);//cmd
        string(L" ");
        _clp_split(2);
        assign(base+0);//cmd
        pop();
    if_1_1:
    if_1_0:;
    line(19);
    push(&ONE);
    push(&FALSE);
    _clp_fdup(2);
    assign(base+3);//fd1save
    pop();
    line(20);
    number(2);
    push(&FALSE);
    _clp_fdup(2);
    assign(base+4);//fd2save
    pop();
    line(44);
    line(22);
    push_symbol(base+2);//fd2
    push(&NIL);
    eqeq();
    cmp_208:;
    if(!flag()) goto if_3_1;
        line(27);
        line(24);
        push_symbol(base+1);//fd1
        push(&NIL);
        neeq();
        cmp_222:;
        if(!flag()) goto if_4_1;
            line(26);
            push_symbol(base+1);//fd1
            push(&ONE);
            push(&TRUE);
            _clp_fdup(3);
            pop();
        if_4_1:
        if_4_0:;
    goto if_3_0;
    if_3_1:
    line(29);
    push_symbol(base+1);//fd1
    push(&NIL);
    eqeq();
    cmp_274:;
    if(!flag()) goto if_3_2;
        line(34);
        line(31);
        push_symbol(base+2);//fd2
        push(&NIL);
        neeq();
        cmp_288:;
        if(!flag()) goto if_5_1;
            line(33);
            push_symbol(base+2);//fd2
            number(2);
            push(&TRUE);
            _clp_fdup(3);
            pop();
        if_5_1:
        if_5_0:;
    goto if_3_0;
    if_3_2:
    line(36);
    push_symbol(base+1);//fd1
    push_symbol(base+2);//fd2
    neeq();
    cmp_340:;
    if(!flag()) goto if_3_3;
        line(38);
        push_symbol(base+1);//fd1
        push(&ONE);
        push(&TRUE);
        _clp_fdup(3);
        pop();
        line(39);
        push_symbol(base+2);//fd2
        number(2);
        push(&TRUE);
        _clp_fdup(3);
        pop();
    goto if_3_0;
    if_3_3:
    line(41);
        line(42);
        push_symbol(base+1);//fd1
        push(&ONE);
        push(&TRUE);
        _clp_fdup(3);
        pop();
        line(43);
        push(&ONE);
        number(2);
        _clp_fdup(2);
        pop();
    if_3_4:
    if_3_0:;
    line(46);
    number(3);
    push_symbol(base+0);//cmd
    _clp_spawn(2);
    pop();
    line(48);
    push_symbol(base+3);//fd1save
    push(&ONE);
    push(&TRUE);
    _clp_fdup(3);
    pop();
    line(49);
    push_symbol(base+4);//fd2save
    number(2);
    push(&TRUE);
    _clp_fdup(3);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

