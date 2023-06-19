//input: spawn.ppo (5.6.0)

#include <cccdef.h>

static void _blk_spawn_0(int argno);
extern void _clp_adel(int argno);
extern void _clp_array(int argno);
extern void _clp_break(int argno);
extern void _clp_errornew(int argno);
extern void _clp_evalarray(int argno);
extern void _clp_exec(int argno);
extern void _clp_ferror(int argno);
extern void _clp_fork(int argno);
extern void _clp_len(int argno);
extern void _clp_numand(int argno);
extern void _clp_spawn(int argno);
extern void _clp_str2bin(int argno);
extern void _clp_valtype(int argno);
extern void _clp_waitpid(int argno);

class _method6_args: public _method6_{public: _method6_args():_method6_("args"){};}; static _method6_args _o_method_args;
class _method6_description: public _method6_{public: _method6_description():_method6_("description"){};}; static _method6_description _o_method_description;
class _method6_operation: public _method6_{public: _method6_operation():_method6_("operation"){};}; static _method6_operation _o_method_operation;
class _method6_oscode: public _method6_{public: _method6_oscode():_method6_("oscode"){};}; static _method6_oscode _o_method_oscode;

//=======================================================================
void _clp_spawn(int argno)
{
VALUE *base=stack-argno;
while(stack<base+argno+11)PUSHNIL();
push_call("spawn",base);
//
    line(41);
    {int argc=1-1;
    {int i;for(i=0;i<argno;i++){argc++;push_symbol(base+i);}}
    array(argc);
    };
    assign(base+argno+0);//arg
    pop();
    line(42);
    line(43);
    line(44);
    line(45);
    line(46);
    block(_blk_spawn_0,0);
    assign(base+argno+8);//execblk
    pop();
    line(47);
    number(-1);
    assign(base+argno+9);//status
    pop();
    line(48);
    line(58);
    line(52);
    push_symbol(base+argno+0);//arg
    _clp_len(1);
    number(2);
    lt();
    if(!flag()) goto if_1_1;
        line(53);
        _clp_errornew(0);
        assign(base+argno+4);//err
        pop();
        line(54);
        push_symbol(base+argno+4);//err
        string(L"spawn");
        _o_method_operation.eval(2);
        pop();
        line(55);
        push_symbol(base+argno+4);//err
        string(L"argument error");
        _o_method_description.eval(2);
        pop();
        line(56);
        push_symbol(base+argno+4);//err
        push_symbol(base+argno+0);//arg
        _o_method_args.eval(2);
        pop();
        line(57);
        push_symbol(base+argno+4);//err
        _clp_break(1);
        pop();
    if_1_1:
    if_1_0:;
    line(72);
    line(60);
    push_symbol(base+argno+0);//arg
    idxr0(1);
    _clp_valtype(1);
    string(L"L");
    eqeq();
    if(!flag()) goto if_2_1;
        line(61);
        push(&FALSE);
        assign(base+argno+5);//path_flag
        pop();
        line(62);
        push_symbol(base+argno+0);//arg
        idxr0(1);
        assign(base+argno+6);//wait_flag
        pop();
    goto if_2_0;
    if_2_1:
    line(63);
    push_symbol(base+argno+0);//arg
    idxr0(1);
    _clp_valtype(1);
    string(L"N");
    eqeq();
    if(!flag()) goto if_2_2;
        line(64);
        push(&ZERO);
        push_symbol(base+argno+0);//arg
        idxr0(1);
        number(2);
        _clp_numand(2);
        neeq();
        assign(base+argno+5);//path_flag
        pop();
        line(65);
        push(&ZERO);
        push_symbol(base+argno+0);//arg
        idxr0(1);
        push(&ONE);
        _clp_numand(2);
        neeq();
        assign(base+argno+6);//wait_flag
        pop();
    goto if_2_0;
    if_2_2:
    line(66);
        line(67);
        _clp_errornew(0);
        assign(base+argno+4);//err
        pop();
        line(68);
        push_symbol(base+argno+4);//err
        string(L"spawn");
        _o_method_operation.eval(2);
        pop();
        line(69);
        push_symbol(base+argno+4);//err
        string(L"argument error");
        _o_method_description.eval(2);
        pop();
        line(70);
        push_symbol(base+argno+4);//err
        push_symbol(base+argno+0);//arg
        _o_method_args.eval(2);
        pop();
        line(71);
        push_symbol(base+argno+4);//err
        _clp_break(1);
        pop();
    if_2_3:
    if_2_0:;
    line(74);
    push_symbol(base+argno+0);//arg
    push(&ONE);
    _clp_adel(2);
    pop();
    line(75);
    push_symbol(base+argno+5);//path_flag
    push_symbol(base+argno+0);//arg
    push_symbol(base+argno+0);//arg
    _clp_len(1);
    assign2(idxxl());
    pop();
    line(90);
    {
    line(77);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+argno+1);//n
    lab_3_0:
    push_symbol(base+argno+0);//arg
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_3_2;
        line(89);
        line(78);
        push_symbol(base+argno+0);//arg
        push_symbol(base+argno+1);//n
        idxr();
        _clp_valtype(1);
        string(L"C");
        eqeq();
        if(!flag()) goto if_4_1;
            line(79);
            push_symbol(base+argno+0);//arg
            push_symbol(base+argno+1);//n
            idxr();
            _clp_str2bin(1);
            push_symbol(base+argno+0);//arg
            push_symbol(base+argno+1);//n
            assign2(idxxl());
            pop();
        goto if_4_0;
        if_4_1:
        line(80);
        push_symbol(base+argno+0);//arg
        push_symbol(base+argno+1);//n
        idxr();
        _clp_valtype(1);
        string(L"A");
        eqeq();
        if(!flag()) goto if_4_2;
            line(81);
            push_symbol(base+argno+0);//arg
            push_symbol(base+argno+1);//n
            idxr();
            _clp_len(1);
            _clp_array(1);
            assign(base+argno+2);//x
            pop();
            line(87);
            {
            line(82);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+argno+3);//i
            lab_5_0:
            push_symbol(base+argno+2);//x
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_5_2;
                line(83);
                push_symbol(base+argno+0);//arg
                push_symbol(base+argno+1);//n
                idxr();
                push_symbol(base+argno+3);//i
                idxr();
                push_symbol(base+argno+2);//x
                push_symbol(base+argno+3);//i
                assign2(idxxl());
                pop();
                line(86);
                line(84);
                push_symbol(base+argno+2);//x
                push_symbol(base+argno+3);//i
                idxr();
                _clp_valtype(1);
                string(L"C");
                eqeq();
                if(!flag()) goto if_6_1;
                    line(85);
                    push_symbol(base+argno+2);//x
                    push_symbol(base+argno+3);//i
                    idxr();
                    _clp_str2bin(1);
                    push_symbol(base+argno+2);//x
                    push_symbol(base+argno+3);//i
                    assign2(idxxl());
                    pop();
                if_6_1:
                if_6_0:;
            lab_5_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+argno+3);//i
            add();
            assign(base+argno+3);//i
            goto lab_5_0;
            lab_5_2:;
            }
            line(88);
            push_symbol(base+argno+2);//x
            push_symbol(base+argno+0);//arg
            push_symbol(base+argno+1);//n
            assign2(idxxl());
            pop();
        if_4_2:
        if_4_0:;
    lab_3_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+argno+1);//n
    add();
    assign(base+argno+1);//n
    goto lab_3_0;
    lab_3_2:;
    }
    line(92);
    _clp_fork(0);
    assign(base+argno+7);//pid
    pop();
    line(123);
    line(96);
    push_symbol(base+argno+7);//pid
    push(&ZERO);
    eqeq();
    if(!flag()) goto if_7_1;
        line(97);
        push_symbol(base+argno+8);//execblk
        push_symbol(base+argno+0);//arg
        _clp_evalarray(2);
        assign(base+argno+10);//result
        pop();
        line(105);
        _clp_errornew(0);
        assign(base+argno+4);//err
        pop();
        line(106);
        push_symbol(base+argno+4);//err
        string(L"spawn");
        _o_method_operation.eval(2);
        pop();
        line(107);
        push_symbol(base+argno+4);//err
        string(L"exec failed");
        _o_method_description.eval(2);
        pop();
        line(108);
        push_symbol(base+argno+4);//err
        push_symbol(base+argno+0);//arg
        _o_method_args.eval(2);
        pop();
        line(109);
        push_symbol(base+argno+4);//err
        _clp_ferror(0);
        _o_method_oscode.eval(2);
        pop();
        line(110);
        push_symbol(base+argno+4);//err
        _clp_break(1);
        pop();
    goto if_7_0;
    if_7_1:
    line(112);
    push_symbol(base+argno+6);//wait_flag
    if(!flag()) goto if_7_2;
        line(113);
        push_symbol(base+argno+7);//pid
        push_symbol_ref(base+argno+9);//status
        push(&ZERO);
        _clp_waitpid(3);
        pop();
        line(114);
        push_symbol(base+argno+9);//status
        assign(base+argno+10);//result
        pop();
    goto if_7_0;
    if_7_2:
    line(121);
        line(122);
        push_symbol(base+argno+7);//pid
        assign(base+argno+10);//result
        pop();
    if_7_3:
    if_7_0:;
    line(125);
    push_symbol(base+argno+10);//result
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_spawn_0(int argno)
{
//
    _clp_exec(argno-1);
//
*(stack-2)=*(stack-1);pop();
}
//=======================================================================

