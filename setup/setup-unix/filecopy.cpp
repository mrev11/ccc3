//input: filecopy.ppo (5.6.0)

#include <cccdef.h>

extern void _clp_chmod(int argno);
extern void _clp_chown(int argno);
extern void _clp_fclose(int argno);
extern void _clp_fcreate(int argno);
extern void _clp_ferase(int argno);
extern void _clp_filecopy(int argno);
extern void _clp_fopen(int argno);
extern void _clp_fread(int argno);
extern void _clp_fwrite(int argno);
extern void _clp_len(int argno);
extern void _clp_replicate(int argno);
extern void _clp_stat(int argno);
extern void _clp_utime(int argno);

//=======================================================================
void _clp_filecopy(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+9)PUSHNIL();
argno=2;
push_call("filecopy",base);
//
    line(27);
    line(28);
    line(29);
    push(&ZERO);
    assign(base+8);//nbyte
    pop();
    line(31);
    push_symbol(base+0);//fsource
    _clp_stat(1);
    assign(base+2);//st1
    pop();
    line(32);
    push_symbol(base+0);//fsource
    push(&ZERO);
    _clp_fopen(2);
    assign(base+3);//fd1
    pop();
    line(35);
    line(33);
    push_symbol(base+3);//fd1
    push(&ZERO);
    lt();
    if(!flag()) goto if_1_1;
        line(34);
        push(&ZERO);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_1_1:
    if_1_0:;
    line(37);
    push_symbol(base+1);//ftarget
    _clp_ferase(1);
    pop();
    line(38);
    push_symbol(base+1);//ftarget
    _clp_fcreate(1);
    assign(base+4);//fd2
    pop();
    line(42);
    line(39);
    push_symbol(base+4);//fd2
    push(&ZERO);
    lt();
    if(!flag()) goto if_2_1;
        line(40);
        push_symbol(base+3);//fd1
        _clp_fclose(1);
        pop();
        line(41);
        push(&ZERO);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_2_1:
    if_2_0:;
    line(44);
    binaryx("00");
    number(4096);
    _clp_replicate(2);
    assign(base+5);//buf
    pop();
    line(45);
    push_symbol(base+3);//fd1
    push_symbol_ref(base+5);//buf
    push_symbol(base+5);//buf
    _clp_len(1);
    _clp_fread(3);
    assign(base+6);//nr
    pop();
    line(52);
    lab_3_1:
    line(46);
    push_symbol(base+6);//nr
    push(&ZERO);
    gt();
    if(!flag()) goto lab_3_2;
        line(47);
        push_symbol(base+8);//nbyte
        push_symbol(base+4);//fd2
        push_symbol(base+5);//buf
        push_symbol(base+6);//nr
        _clp_fwrite(3);
        assign(base+7);//nw
        add();
        assign(base+8);//nbyte
        pop();
        line(50);
        line(48);
        push_symbol(base+7);//nw
        push_symbol(base+6);//nr
        neeq();
        if(!flag()) goto if_4_1;
            line(49);
            goto lab_3_2;//exit
        if_4_1:
        if_4_0:;
        line(51);
        push_symbol(base+3);//fd1
        push_symbol_ref(base+5);//buf
        push_symbol(base+5);//buf
        _clp_len(1);
        _clp_fread(3);
        assign(base+6);//nr
        pop();
    goto lab_3_1;
    lab_3_2:;
    line(54);
    push_symbol(base+3);//fd1
    _clp_fclose(1);
    pop();
    line(55);
    push_symbol(base+4);//fd2
    _clp_fclose(1);
    pop();
    line(61);
    line(57);
    push_symbol(base+2);//st1
    push(&NIL);
    neeq();
    if(!flag()) goto if_5_1;
        line(58);
        push_symbol(base+1);//ftarget
        push_symbol(base+2);//st1
        idxr0(11);
        push_symbol(base+2);//st1
        idxr0(12);
        _clp_utime(3);
        pop();
        line(59);
        push_symbol(base+1);//ftarget
        push_symbol(base+2);//st1
        idxr0(3);
        _clp_chmod(2);
        pop();
        line(60);
        push_symbol(base+1);//ftarget
        push_symbol(base+2);//st1
        idxr0(5);
        push_symbol(base+2);//st1
        idxr0(6);
        _clp_chown(3);
        pop();
    if_5_1:
    if_5_0:;
    line(63);
    push_symbol(base+8);//nbyte
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

