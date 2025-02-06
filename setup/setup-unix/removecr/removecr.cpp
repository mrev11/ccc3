//input: ppo/removecr.ppo (5.7.0.1)

#include <cccdef.h>

extern void _clp___quit(int argno);
extern void _clp_aclone(int argno);
extern void _clp_argv(int argno);
extern void _clp_chmod(int argno);
extern void _clp_chr(int argno);
extern void _clp_file(int argno);
extern void _clp_len(int argno);
extern void _clp_main(int argno);
extern void _clp_memoread(int argno);
extern void _clp_memowrit(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);
extern void _clp_setdosconv(int argno);
extern void _clp_stat_st_mode(int argno);
extern void _clp_strtran(int argno);

//=======================================================================
void _clp_main(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+6)PUSHNIL();
argno=1;
push_call("main",base);
//
    line(23);
    _clp_argv(0);
    _clp_aclone(1);
    assign(base+1);//opt
    pop();
    line(25);
    line(26);
    line(27);
    line(29);
    string(L"off");
    _clp_setdosconv(1);
    pop();
    line(37);
    {
    line(31);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_1_0:
    push_symbol(base+1);//opt
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(36);
        line(32);
        push_symbol(base+1);//opt
        push_symbol(base+2);//n
        idxr();
        string(L"-x");
        eqeq();
        cmp_119:;
        if(!flag()) goto if_2_1;
            line(33);
            _clp___quit(0);
            pop();
        goto if_2_0;
        if_2_1:
        line(34);
            line(35);
            push_symbol(base+1);//opt
            push_symbol(base+2);//n
            idxr();
            assign(base+0);//fspec
            pop();
        if_2_2:
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
    line(43);
    line(39);
    push_symbol(base+0);//fspec
    push(&NIL);
    eqeq();
    cmp_171:;
    if(!flag()) goto if_3_1;
        line(40);
        string(L"Usage: removecr <filespec>");
        _clp_qqout(1);
        pop();
        line(41);
        _clp_qout(0);
        pop();
        line(42);
        _clp___quit(0);
        pop();
    if_3_1:
    if_3_0:;
    line(49);
    line(44);
    push_symbol(base+0);//fspec
    _clp_file(1);
    topnot();
    if(!flag()) goto if_4_1;
        line(45);
        string(L"Usage: removecr <filespec>");
        _clp_qqout(1);
        pop();
        line(46);
        string(L" (file not found [");
        push_symbol(base+0);//fspec
        add();
        string(L"])");
        add();
        _clp_qqout(1);
        pop();
        line(47);
        _clp_qout(0);
        pop();
        line(48);
        _clp___quit(0);
        pop();
    if_4_1:
    if_4_0:;
    line(52);
    push_symbol(base+0);//fspec
    _clp_memoread(1);
    assign(base+3);//ftxt
    pop();
    line(53);
    push_symbol(base+3);//ftxt
    number(13);
    _clp_chr(1);
    string(L"");
    _clp_strtran(3);
    assign(base+4);//ftxt1
    pop();
    line(63);
    line(55);
    push_symbol(base+3);//ftxt
    push_symbol(base+4);//ftxt1
    eqeq();
    cmp_363:;
    topnot();
    if(!flag()) goto if_5_1;
        line(57);
        push_symbol(base+0);//fspec
        _clp_stat_st_mode(1);
        assign(base+5);//fmode
        pop();
        line(59);
        push_symbol(base+0);//fspec
        push_symbol(base+4);//ftxt1
        _clp_memowrit(2);
        pop();
        line(61);
        push_symbol(base+0);//fspec
        push_symbol(base+5);//fmode
        _clp_chmod(2);
        pop();
    if_5_1:
    if_5_0:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

