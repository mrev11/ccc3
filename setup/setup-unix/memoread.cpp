//input: memoread.ppo (5.3.0)

#include <cccdef.h>

extern void _clp___maxstrlen(int argno);
extern void _clp_bin2str(int argno);
extern void _clp_empty(int argno);
extern void _clp_fclose(int argno);
extern void _clp_fcreate(int argno);
extern void _clp_fopen(int argno);
extern void _clp_fread(int argno);
extern void _clp_fseek(int argno);
extern void _clp_fwrite(int argno);
extern void _clp_len(int argno);
extern void _clp_memoread(int argno);
extern void _clp_memowrit(int argno);
extern void _clp_replicate(int argno);
extern void _clp_str2bin(int argno);
extern void _clp_valtype(int argno);

//=======================================================================
void _clp_memoread(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+5)PUSHNIL();
argno=2;
push_call("memoread",base);
//
    line(31);
    binaryx("");
    assign(base+4);//buffer
    pop();
    line(42);
    line(33);
    push(&ZERO);
    push_symbol(base+0);//fspec
    number(64);
    _clp_fopen(2);
    assign(base+2);//fd
    lteq();
    if(!flag()){
    push(&FALSE);
    }else{
    push(&ZERO);
    push_symbol(base+2);//fd
    push(&ZERO);
    number(2);
    _clp_fseek(3);
    assign(base+3);//len
    lt();
    }
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+3);//len
    _clp___maxstrlen(0);
    lt();
    }
    if(!flag()) goto if_1_1;
        line(37);
        push_symbol(base+2);//fd
        push(&ZERO);
        _clp_fseek(2);
        pop();
        line(38);
        binaryx("20");
        push_symbol(base+3);//len
        _clp_replicate(2);
        assign(base+4);//buffer
        pop();
        line(41);
        line(39);
        push(&ZERO);
        push_symbol(base+2);//fd
        push_symbol_ref(base+4);//buffer
        push_symbol(base+3);//len
        _clp_fread(3);
        gt();
        if(!flag()) goto if_2_1;
            line(40);
            binaryx("");
            assign(base+4);//buffer
            pop();
        if_2_1:
        if_2_0:;
    if_1_1:
    if_1_0:;
    line(43);
    push_symbol(base+2);//fd
    _clp_fclose(1);
    pop();
    line(46);
    line(44);
    push_symbol(base+1);//binopt
    _clp_empty(1);
    if(!flag()) goto if_3_1;
        line(45);
        push_symbol(base+4);//buffer
        _clp_bin2str(1);
        assign(base+4);//buffer
        pop();
    if_3_1:
    if_3_0:;
    line(47);
    push_symbol(base+4);//buffer
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_memowrit(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+5)PUSHNIL();
argno=2;
push_call("memowrit",base);
//
    line(51);
    push(&FALSE);
    assign(base+2);//success
    pop();
    line(61);
    line(52);
    push(&ZERO);
    push_symbol(base+0);//fspec
    _clp_fcreate(1);
    assign(base+3);//fd
    lteq();
    if(!flag()) goto if_4_1;
        line(55);
        line(53);
        push_symbol(base+1);//data
        _clp_valtype(1);
        string(L"C");
        eqeq();
        if(!flag()) goto if_5_1;
            line(54);
            push_symbol(base+1);//data
            _clp_str2bin(1);
            assign(base+1);//data
            pop();
        if_5_1:
        if_5_0:;
        line(56);
        push_symbol(base+3);//fd
        push_symbol(base+1);//data
        _clp_fwrite(2);
        assign(base+4);//nbyte
        pop();
        line(57);
        push_symbol(base+3);//fd
        _clp_fclose(1);
        pop();
        line(60);
        line(58);
        push_symbol(base+4);//nbyte
        push_symbol(base+1);//data
        _clp_len(1);
        eqeq();
        if(!flag()) goto if_6_1;
            line(59);
            push(&TRUE);
            assign(base+2);//success
            pop();
        if_6_1:
        if_6_0:;
    if_4_1:
    if_4_0:;
    line(62);
    push_symbol(base+2);//success
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

