//input: verifdep.ppo (5.6.0)

#include <cccdef.h>

extern void _clp___quit(int argno);
extern void _clp_errorlevel(int argno);
extern void _clp_ftime(int argno);
extern void _clp_qout(int argno);
extern void _clp_s_debug(int argno);
extern void _clp_s_dry(int argno);
extern void _clp_verifdep(int argno);

//=======================================================================
void _clp_verifdep(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+4)PUSHNIL();
argno=2;
push_call("verifdep",base);
//
    line(25);
    push(&FALSE);
    assign(base+2);//update
    pop();
    line(26);
    push_symbol(base+1);//depend
    _clp_ftime(1);
    assign(base+3);//tdepend
    pop();
    line(40);
    line(28);
    push_symbol(base+3);//tdepend
    push(&NIL);
    eqeq();
    if(!flag()) goto if_1_1;
        line(36);
        line(29);
        _clp_s_dry(0);
        if(!flag()) goto if_2_1;
            line(30);
            string(L"");
            assign(base+3);//tdepend
            pop();
        goto if_2_0;
        if_2_1:
        line(31);
            line(32);
            push_symbol(base+1);//depend
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(33);
            _clp_qout(0);
            pop();
            line(34);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(35);
            _clp___quit(0);
            pop();
        if_2_2:
        if_2_0:;
    goto if_1_0;
    if_1_1:
    line(38);
    push_symbol(base+0);//ttarget
    push_symbol(base+3);//tdepend
    lt();
    if(!flag()) goto if_1_2;
        line(39);
        push(&TRUE);
        assign(base+2);//update
        pop();
    if_1_2:
    if_1_0:;
    line(44);
    line(42);
    _clp_s_debug(0);
    if(!flag()) goto if_3_1;
        line(43);
        string(L"  ");
        push_symbol(base+1);//depend
        string(L"[");
        push_symbol(base+3);//tdepend
        add();
        string(L"]");
        add();
        push_symbol(base+0);//ttarget
        push_symbol(base+3);//tdepend
        lt();
        if(flag()){
        string(L"UPDATE");
        }else{
        string(L"");
        }
        _clp_qout(4);
        pop();
    if_3_1:
    if_3_0:;
    line(46);
    push_symbol(base+2);//update
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

