//input: ppo/prepro.ppo (5.7.0.1)

#include <cccdef.h>

extern void _clp_alltrim(int argno);
extern void _clp_bin(int argno);
extern void _clp_endofline(int argno);
extern void _clp_find_translate(int argno);
extern void _clp_left(int argno);
extern void _clp_leftspace(int argno);
extern void _clp_linepragma(int argno);
extern void _clp_match(int argno);
extern void _clp_nextline(int argno);
extern void _clp_outline(int argno);
extern void _clp_prepro(int argno);
extern void _clp_qqout(int argno);
extern void _clp_reproctxt(int argno);
extern void _clp_space(int argno);
extern void _clp_str(int argno);
extern void _clp_substr(int argno);
extern void _clp_tokenize(int argno);

//=======================================================================
void _clp_nextline(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("nextline",base);
//
    line(27);
    line(23);
    _clp_linepragma(0);
    if(!flag()) goto if_1_1;
        line(24);
        _clp_endofline(0);
        string(L"#line");
        add();
        push_symbol(base+0);//lineno
        _clp_str(1);
        _clp_alltrim(1);
        string(L"\"");
        push_symbol(base+1);//fname
        add();
        string(L"\"");
        add();
        _clp_qqout(3);
        pop();
    goto if_1_0;
    if_1_1:
    line(25);
        line(26);
        _clp_endofline(0);
        _clp_qqout(1);
        pop();
    if_1_2:
    if_1_0:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_prepro(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+6)PUSHNIL();
argno=1;
push_call("prepro",base);
//
    line(32);
    push_symbol(base+0);//line
    _clp_leftspace(1);
    assign(base+1);//indent
    pop();
    line(33);
    push_symbol(base+0);//line
    _clp_alltrim(1);
    _clp_tokenize(1);
    assign(base+2);//toklst
    pop();
    line(34);
    push_symbol(base+2);//toklst
    _clp_match(1);
    assign(base+3);//result
    pop();
    line(35);
    push_symbol(base+3);//result
    _clp_outline(1);
    assign(base+4);//output
    pop();
    line(36);
    push_symbol(base+4);//output
    _clp_find_translate(1);
    assign(base+5);//trnpos
    pop();
    line(51);
    line(38);
    push(&ZERO);
    push_symbol(base+5);//trnpos
    lt();
    cmp_259:;
    if(!flag()) goto if_2_1;
        line(43);
        line(40);
        push(&ONE);
        push_symbol(base+5);//trnpos
        lt();
        cmp_273:;
        if(!flag()) goto if_3_1;
            line(41);
            _clp_endofline(0);
            push_symbol(base+1);//indent
            _clp_space(1);
            add();
            _clp_qqout(1);
            pop();
            line(42);
            push_symbol(base+4);//output
            push_symbol(base+5);//trnpos
            addnum(-1);
            _clp_left(2);
            _clp_qqout(1);
            pop();
        if_3_1:
        if_3_0:;
        line(45);
        push_symbol(base+4);//output
        push_symbol(base+5);//trnpos
        _clp_substr(2);
        number(10);
        _clp_bin(1);
        add();
        _clp_reproctxt(1);
        pop();
    goto if_2_0;
    if_2_1:
    line(47);
        line(49);
        _clp_endofline(0);
        push_symbol(base+1);//indent
        _clp_space(1);
        add();
        _clp_qqout(1);
        pop();
        line(50);
        push_symbol(base+4);//output
        _clp_qqout(1);
        pop();
    if_2_2:
    if_2_0:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

