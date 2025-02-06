//input: ppo/ccomp.ppo (5.7.0.1)

#include <cccdef.h>

extern void _clp_aadd(int argno);
extern void _clp_argv(int argno);
extern void _clp_chr(int argno);
extern void _clp_empty(int argno);
extern void _clp_errorlevel(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_main(int argno);
extern void _clp_memoread(int argno);
extern void _clp_spawn(int argno);
extern void _clp_split(int argno);
extern void _clp_strtran(int argno);
extern void _clp_substr(int argno);

//=======================================================================
void _clp_main(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+4)PUSHNIL();
argno=0;
push_call("main",base);
//
    line(36);
    array(0);
    assign(base+0);//cmd
    pop();
    push(&ZERO);
    assign(base+1);//n
    pop();
    line(63);
    lab_1_1:
    line(48);
    push_symbol(base+1);//n
    push(&ONE);
    add();
    assign(base+1);//n
    _clp_argv(1);
    assign(base+2);//arg
    _clp_empty(1);
    topnot();
    if(!flag()) goto lab_1_2;
        line(62);
        line(50);
        push_symbol(base+2);//arg
        push(&ONE);
        _clp_left(2);
        string(L"@");
        eqeq();
        cmp_102:;
        if(!flag()) goto if_2_1;
            line(51);
            push_symbol(base+2);//arg
            number(2);
            _clp_substr(2);
            _clp_memoread(1);
            assign(base+2);//arg
            pop();
            line(52);
            push_symbol(base+2);//arg
            number(13);
            _clp_chr(1);
            string(L"");
            _clp_strtran(3);
            assign(base+2);//arg
            pop();
            line(53);
            push_symbol(base+2);//arg
            number(10);
            _clp_chr(1);
            string(L" ");
            _clp_strtran(3);
            assign(base+2);//arg
            pop();
            line(54);
            push_symbol(base+2);//arg
            string(L" ");
            _clp_split(2);
            assign(base+2);//arg
            pop();
            line(59);
            {
            line(55);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+3);//i
            lab_3_0:
            push_symbol(base+2);//arg
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_3_2;
                line(58);
                line(56);
                push_symbol(base+2);//arg
                push_symbol(base+3);//i
                idxr();
                _clp_empty(1);
                topnot();
                if(!flag()) goto if_4_1;
                    line(57);
                    push_symbol(base+0);//cmd
                    push_symbol(base+2);//arg
                    push_symbol(base+3);//i
                    idxr();
                    _clp_aadd(2);
                    pop();
                if_4_1:
                if_4_0:;
            lab_3_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+3);//i
            add();
            assign(base+3);//i
            goto lab_3_0;
            lab_3_2:;
            }
        goto if_2_0;
        if_2_1:
        line(60);
            line(61);
            push_symbol(base+0);//cmd
            push_symbol(base+2);//arg
            _clp_aadd(2);
            pop();
        if_2_2:
        if_2_0:;
    goto lab_1_1;
    lab_1_2:;
    line(64);
    number(3);
    push_symbol(base+0);//cmd
    _clp_spawn(2);
    _clp_errorlevel(1);
    pop();
    line(65);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

