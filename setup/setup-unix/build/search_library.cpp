//input: ppo/search_library.ppo (5.7.0.1)

#include <cccdef.h>

extern void _clp_buildenv_lib(int argno);
extern void _clp_buildenv_lpt(int argno);
extern void _clp_buildenv_shr(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_empty(int argno);
extern void _clp_file(int argno);
extern void _clp_getenv(int argno);
extern void _clp_len(int argno);
extern void _clp_right(int argno);
extern void _clp_search_library(int argno);
extern void _clp_split(int argno);

//=======================================================================
void _clp_search_library(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+13)PUSHNIL();
argno=0;
push_call("search_library",base);
//
    line(31);
    _clp_buildenv_lpt(0);
    string(L" ");
    _clp_split(2);
    assign(base+0);//dirlist
    pop();
    line(32);
    _clp_buildenv_lib(0);
    string(L" ");
    _clp_split(2);
    assign(base+1);//liblist
    pop();
    line(33);
    _clp_buildenv_shr(0);
    assign(base+2);//sharing
    pop();
    line(35);
    string(L"");
    assign(base+5);//txt
    pop();
    line(36);
    line(37);
    static stvar _st_msys64;
    static int _ini_msys64=[=](){
        string(L"MSYS64");
        _clp_getenv(1);
        assign(_st_msys64.ptr);
        pop();
        return 1;
    }();
    line(132);
    {
    line(39);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+3);//n
    lab_1_0:
    push_symbol(base+1);//liblist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_1_2;
        line(43);
        line(41);
        push_symbol(base+1);//liblist
        push_symbol(base+3);//n
        idxr();
        assign(base+6);//f0
        _clp_empty(1);
        if(!flag()) goto if_2_1;
            line(42);
            goto lab_1_1;//loop
        if_2_1:
        if_2_0:;
        line(53);
        line(45);
        string(L".lib");
        push_symbol(base+6);//f0
        number(4);
        _clp_right(2);
        eqeq();
        cmp_238:;
        if(flag()){
        push(&TRUE);
        }else{
        string(L".a");
        push_symbol(base+6);//f0
        number(2);
        _clp_right(2);
        eqeq();
        cmp_257:;
        }
        if(flag()){
        push(&TRUE);
        }else{
        string(L".so");
        push_symbol(base+6);//f0
        number(3);
        _clp_right(2);
        eqeq();
        cmp_277:;
        }
        if(!flag()) goto if_3_1;
            line(46);
            push_symbol(base+6);//f0
            assign(base+7);//f1
            pop();
            line(47);
            push_symbol(base+6);//f0
            assign(base+8);//f2
            pop();
            line(48);
            push_symbol(base+6);//f0
            assign(base+9);//f3
            pop();
        goto if_3_0;
        if_3_1:
        line(49);
            line(50);
            push_symbol(base+6);//f0
            string(L".lib");
            add();
            assign(base+7);//f1
            pop();
            line(51);
            string(L"lib");
            push_symbol(base+6);//f0
            add();
            string(L".a");
            add();
            assign(base+8);//f2
            pop();
            line(52);
            string(L"lib");
            push_symbol(base+6);//f0
            add();
            string(L".so");
            add();
            assign(base+9);//f3
            pop();
        if_3_2:
        if_3_0:;
        line(106);
        {
        line(56);
        push(&ONE);
        int sg=sign();
        push(&ZERO);
        assign(base+4);//i
        lab_4_0:
        push_symbol(base+0);//dirlist
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
            line(70);
            line(58);
            push_symbol(base+4);//i
            push(&ZERO);
            lteq();
            cmp_417:;
            if(!flag()) goto if_5_1;
                line(59);
                push_symbol(base+7);//f1
                assign(base+10);//pf1
                pop();
                line(60);
                push_symbol(base+8);//f2
                assign(base+11);//pf2
                pop();
                line(61);
                push_symbol(base+9);//f3
                assign(base+12);//pf3
                pop();
            goto if_5_0;
            if_5_1:
            line(62);
                line(65);
                line(63);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_empty(1);
                if(!flag()) goto if_6_1;
                    line(64);
                    goto lab_4_1;//loop
                if_6_1:
                if_6_0:;
                line(67);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+7);//f1
                add();
                assign(base+10);//pf1
                pop();
                line(68);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+8);//f2
                add();
                assign(base+11);//pf2
                pop();
                line(69);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_dirsep(0);
                add();
                push_symbol(base+9);//f3
                add();
                assign(base+12);//pf3
                pop();
            if_5_2:
            if_5_0:;
            line(105);
            line(76);
            string(L"static");
            push_symbol(base+2);//sharing
            ss();
            if(!flag()) goto if_7_1;
                line(89);
                line(80);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_8_1;
                    line(81);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(82);
                    goto lab_4_2;//exit
                goto if_8_0;
                if_8_1:
                line(83);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_8_2;
                    line(84);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(85);
                    goto lab_4_2;//exit
                goto if_8_0;
                if_8_2:
                line(86);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_8_3;
                    line(87);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(88);
                    goto lab_4_2;//exit
                if_8_3:
                if_8_0:;
            goto if_7_0;
            if_7_1:
            line(91);
                line(104);
                line(95);
                push_symbol(base+12);//pf3
                _clp_file(1);
                if(!flag()) goto if_9_1;
                    line(96);
                    push_symbol(base+5);//txt
                    push_symbol(base+12);//pf3
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(97);
                    goto lab_4_2;//exit
                goto if_9_0;
                if_9_1:
                line(98);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_9_2;
                    line(99);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(100);
                    goto lab_4_2;//exit
                goto if_9_0;
                if_9_2:
                line(101);
                push_symbol(base+11);//pf2
                _clp_file(1);
                if(!flag()) goto if_9_3;
                    line(102);
                    push_symbol(base+5);//txt
                    push_symbol(base+11);//pf2
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(103);
                    goto lab_4_2;//exit
                if_9_3:
                if_9_0:;
            if_7_2:
            if_7_0:;
        lab_4_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+4);//i
        add();
        assign(base+4);//i
        goto lab_4_0;
        lab_4_2:;
        }
        line(123);
        line(109);
        push_symbol(base+4);//i
        push_symbol(base+0);//dirlist
        _clp_len(1);
        gt();
        cmp_875:;
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(_st_msys64.ptr);//search_library
        _clp_empty(1);
        topnot();
        }
        if(!flag()) goto if_10_1;
            line(122);
            {
            line(113);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+4);//i
            lab_11_0:
            push_symbol(base+0);//dirlist
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_11_2;
                line(116);
                line(114);
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                _clp_empty(1);
                if(flag()){
                push(&TRUE);
                }else{
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                idxr0(1);
                string(L"/\\");
                ss();
                topnot();
                }
                if(!flag()) goto if_12_1;
                    line(115);
                    goto lab_11_1;//loop
                if_12_1:
                if_12_0:;
                line(117);
                push_symbol(_st_msys64.ptr);//search_library
                push_symbol(base+0);//dirlist
                push_symbol(base+4);//i
                idxr();
                add();
                _clp_dirsep(0);
                add();
                push_symbol(base+7);//f1
                add();
                assign(base+10);//pf1
                pop();
                line(121);
                line(118);
                push_symbol(base+10);//pf1
                _clp_file(1);
                if(!flag()) goto if_13_1;
                    line(119);
                    push_symbol(base+5);//txt
                    push_symbol(base+10);//pf1
                    string(L" ");
                    add();
                    add();
                    assign(base+5);//txt
                    pop();
                    line(120);
                    goto lab_11_2;//exit
                if_13_1:
                if_13_0:;
            lab_11_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+4);//i
            add();
            assign(base+4);//i
            goto lab_11_0;
            lab_11_2:;
            }
        if_10_1:
        if_10_0:;
        line(131);
        line(125);
        push_symbol(base+4);//i
        push_symbol(base+0);//dirlist
        _clp_len(1);
        gt();
        cmp_1080:;
        if(!flag()) goto if_14_1;
            line(130);
            line(126);
            push_symbol(base+6);//f0
            push(&ONE);
            number(2);
            slice();
            string(L"-l");
            eqeq();
            cmp_1114:;
            if(!flag()) goto if_15_1;
                line(127);
                push_symbol(base+5);//txt
                push_symbol(base+6);//f0
                string(L" ");
                add();
                add();
                assign(base+5);//txt
                pop();
            goto if_15_0;
            if_15_1:
            line(128);
                line(129);
                push_symbol(base+5);//txt
                string(L"-l");
                push_symbol(base+6);//f0
                add();
                string(L" ");
                add();
                add();
                assign(base+5);//txt
                pop();
            if_15_2:
            if_15_0:;
        if_14_1:
        if_14_0:;
    lab_1_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+3);//n
    add();
    assign(base+3);//n
    goto lab_1_0;
    lab_1_2:;
    }
    line(134);
    push_symbol(base+5);//txt
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

