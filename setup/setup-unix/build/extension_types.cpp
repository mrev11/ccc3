//input: extension_types.ppo (5.6.0)

#include <cccdef.h>

extern void _clp_extension_types(int argno);
extern void _clp_len(int argno);
extern void _clp_s_primary(int argno);
extern void _clp_s_resource(int argno);
extern void _clp_s_rules(int argno);

//=======================================================================
void _clp_extension_types(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+3)PUSHNIL();
argno=0;
push_call("extension_types",base);
//
    line(24);
    line(26);
    string(L"");
    _clp_s_primary(1);
    pop();
    line(27);
    string(L"");
    _clp_s_resource(1);
    pop();
    line(41);
    {
    line(29);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+2);//n
    lab_1_0:
    _clp_s_rules(0);
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(30);
        _clp_s_rules(0);
        push_symbol(base+2);//n
        idxr();
        idxr0(1);
        assign(base+0);//r1
        pop();
        line(31);
        _clp_s_rules(0);
        push_symbol(base+2);//n
        idxr();
        idxr0(2);
        assign(base+1);//r2
        pop();
        line(37);
        line(35);
        push_symbol(base+1);//r2
        string(L".obj");
        eqeq();
        if(!flag()) goto if_2_1;
            line(36);
            _clp_s_primary(0);
            push_symbol(base+0);//r1
            add();
            _clp_s_primary(1);
            pop();
        if_2_1:
        if_2_0:;
        line(40);
        line(38);
        push_symbol(base+1);//r2
        string(L".");
        add();
        string(L".obj.lib.exe.");
        ss();
        topnot();
        if(!flag()) goto if_3_1;
            line(39);
            _clp_s_resource(0);
            push_symbol(base+0);//r1
            add();
            _clp_s_resource(1);
            pop();
        if_3_1:
        if_3_0:;
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
    line(42);
    _clp_s_primary(0);
    string(L".");
    add();
    _clp_s_primary(1);
    pop();
    line(43);
    _clp_s_resource(0);
    string(L".");
    add();
    _clp_s_resource(1);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

