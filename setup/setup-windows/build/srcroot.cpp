//input: srcroot.ppo (5.6.0)

#include <cccdef.h>

extern void _clp_buildenv_src(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_empty(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_right(int argno);
extern void _clp_s_incdir(int argno);
extern void _clp_s_srcdir(int argno);
extern void _clp_srcroot(int argno);
extern void _clp_xsplit(int argno);

//=======================================================================
void _clp_srcroot(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+3)PUSHNIL();
argno=0;
push_call("srcroot",base);
//
    line(25);
    line(62);
    line(27);
    _clp_buildenv_src(0);
    assign(base+0);//srcroot
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_1_1;
        line(31);
        line(29);
        push_symbol(base+0);//srcroot
        push(&ONE);
        _clp_right(2);
        string(L"/\\");
        ss();
        topnot();
        if(!flag()) goto if_2_1;
            line(30);
            push_symbol(base+0);//srcroot
            _clp_dirsep(0);
            add();
            assign(base+0);//srcroot
            pop();
        if_2_1:
        if_2_0:;
        line(35);
        line(33);
        _clp_s_srcdir(0);
        push(&NIL);
        eqeq();
        if(!flag()) goto if_3_1;
            line(34);
            string(L".");
            _clp_s_srcdir(1);
            pop();
        if_3_1:
        if_3_0:;
        line(37);
        _clp_s_srcdir(0);
        string(L",;");
        _clp_xsplit(2);
        assign(base+1);//d
        pop();
        line(39);
        string(L"");
        _clp_s_srcdir(1);
        pop();
        line(46);
        {
        line(40);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+2);//n
        lab_4_0:
        push_symbol(base+1);//d
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
            line(45);
            line(41);
            push_symbol(base+1);//d
            push_symbol(base+2);//n
            idxr();
            push(&ONE);
            _clp_left(2);
            string(L"/\\");
            ss();
            if(!flag()) goto if_5_1;
                line(42);
                _clp_s_srcdir(0);
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                add();
                string(L";");
                add();
                _clp_s_srcdir(1);
                pop();
            goto if_5_0;
            if_5_1:
            line(43);
                line(44);
                _clp_s_srcdir(0);
                push_symbol(base+0);//srcroot
                add();
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                add();
                string(L";");
                add();
                _clp_s_srcdir(1);
                pop();
            if_5_2:
            if_5_0:;
        lab_4_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+2);//n
        add();
        assign(base+2);//n
        goto lab_4_0;
        lab_4_2:;
        }
        line(61);
        line(49);
        _clp_s_incdir(0);
        push(&NIL);
        neeq();
        if(!flag()) goto if_6_1;
            line(51);
            _clp_s_incdir(0);
            string(L",;");
            _clp_xsplit(2);
            assign(base+1);//d
            pop();
            line(53);
            string(L"");
            _clp_s_incdir(1);
            pop();
            line(60);
            {
            line(54);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+2);//n
            lab_7_0:
            push_symbol(base+1);//d
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_7_2;
                line(59);
                line(55);
                push_symbol(base+1);//d
                push_symbol(base+2);//n
                idxr();
                push(&ONE);
                _clp_left(2);
                string(L"/\\");
                ss();
                if(!flag()) goto if_8_1;
                    line(56);
                    _clp_s_incdir(0);
                    push_symbol(base+1);//d
                    push_symbol(base+2);//n
                    idxr();
                    add();
                    string(L";");
                    add();
                    _clp_s_incdir(1);
                    pop();
                goto if_8_0;
                if_8_1:
                line(57);
                    line(58);
                    _clp_s_incdir(0);
                    push_symbol(base+0);//srcroot
                    add();
                    push_symbol(base+1);//d
                    push_symbol(base+2);//n
                    idxr();
                    add();
                    string(L";");
                    add();
                    _clp_s_incdir(1);
                    pop();
                if_8_2:
                if_8_0:;
            lab_7_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+2);//n
            add();
            assign(base+2);//n
            goto lab_7_0;
            lab_7_2:;
            }
        if_6_1:
        if_6_0:;
    if_1_1:
    if_1_0:;
    line(64);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

