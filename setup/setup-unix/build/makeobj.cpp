//input: ppo/makeobj.ppo (5.7.0.1)

#include <cccdef.h>

extern void _clp___quit(int argno);
extern void _clp_buildenv_bat(int argno);
extern void _clp_buildenv_obj(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_empty(int argno);
extern void _clp_errorlevel(int argno);
extern void _clp_file(int argno);
extern void _clp_ftime(int argno);
extern void _clp_len(int argno);
extern void _clp_makeobj(int argno);
extern void _clp_qout(int argno);
extern void _clp_run1(int argno);
extern void _clp_s_batext(int argno);
extern void _clp_s_debug(int argno);
extern void _clp_strtran(int argno);
extern void _clp_verifdep(int argno);

namespace _nsp_filespec{
extern void _clp_extension(int argno);
extern void _clp_name(int argno);
extern void _clp_path(int argno);
}//namespace filespec

//=======================================================================
void _clp_makeobj(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+12)PUSHNIL();
argno=1;
push_call("makeobj",base);
//
    line(25);
    push_symbol(base+0);//deplist
    idxr0(1);
    assign(base+1);//target
    pop();
    line(26);
    push_symbol(base+0);//deplist
    idxr0(2);
    assign(base+2);//depend
    pop();
    line(27);
    _clp_buildenv_obj(0);
    assign(base+3);//objdir
    pop();
    line(28);
    line(29);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(30);
    line(34);
    line(32);
    push_symbol(base+1);//target
    _nsp_filespec::_clp_extension(1);
    string(L".obj");
    eqeq();
    cmp_134:;
    if(!flag()) goto if_1_1;
        line(33);
        push_symbol(base+3);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+1);//target
        _nsp_filespec::_clp_name(1);
        add();
        push_symbol(base+1);//target
        _nsp_filespec::_clp_extension(1);
        add();
        assign(base+1);//target
        pop();
    if_1_1:
    if_1_0:;
    line(36);
    push_symbol(base+1);//target
    _clp_ftime(1);
    assign(base+4);//ttarget
    pop();
    line(39);
    line(37);
    push_symbol(base+4);//ttarget
    push(&NIL);
    eqeq();
    cmp_224:;
    if(!flag()) goto if_2_1;
        line(38);
        string(L"");
        assign(base+4);//ttarget
        pop();
    if_2_1:
    if_2_0:;
    line(43);
    line(41);
    _clp_s_debug(0);
    if(!flag()) goto if_3_1;
        line(42);
        push_symbol(base+1);//target
        string(L"[");
        push_symbol(base+4);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_3_1:
    if_3_0:;
    line(48);
    {
    line(45);
    push(&ONE);
    int sg=sign();
    number(2);
    assign(base+8);//n
    lab_4_0:
    push_symbol(base+0);//deplist
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
        line(46);
        push_symbol(base+0);//deplist
        push_symbol(base+8);//n
        idxr();
        assign(base+2);//depend
        pop();
        line(47);
        push_symbol(base+4);//ttarget
        push_symbol(base+2);//depend
        _clp_verifdep(2);
        if(flag()){
        push(&TRUE);
        }else{
        push_symbol(base+6);//update
        }
        assign(base+6);//update
        pop();
    lab_4_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+8);//n
    add();
    assign(base+8);//n
    goto lab_4_0;
    lab_4_2:;
    }
    line(52);
    line(50);
    _clp_s_debug(0);
    if(!flag()) goto if_5_1;
        line(51);
        _clp_qout(0);
        pop();
    if_5_1:
    if_5_0:;
    line(75);
    line(54);
    push_symbol(base+6);//update
    if(!flag()) goto if_6_1;
        line(56);
        _clp_buildenv_bat(0);
        _clp_dirsep(0);
        add();
        assign(base+7);//torun
        pop();
        line(57);
        push_symbol(base+7);//torun
        push_symbol(base+0);//deplist
        idxr0(2);
        _nsp_filespec::_clp_extension(1);
        string(L"2");
        add();
        push_symbol(base+0);//deplist
        idxr0(1);
        _nsp_filespec::_clp_extension(1);
        add();
        string(L".");
        string(L"");
        _clp_strtran(3);
        add();
        assign(base+7);//torun
        pop();
        line(58);
        push_symbol(base+7);//torun
        _clp_s_batext(0);
        add();
        assign(base+7);//torun
        pop();
        line(65);
        line(60);
        push_symbol(base+7);//torun
        _clp_file(1);
        topnot();
        if(!flag()) goto if_7_1;
            line(61);
            string(L"[");
            push_symbol(base+7);//torun
            add();
            string(L"]");
            add();
            string(nls_text(L"does not exist"));
            _clp_qout(2);
            pop();
            line(62);
            _clp_qout(0);
            pop();
            line(63);
            push(&ONE);
            _clp_errorlevel(1);
            pop();
            line(64);
            _clp___quit(0);
            pop();
        if_7_1:
        if_7_0:;
        line(67);
        push_symbol(base+0);//deplist
        idxr0(1);
        _nsp_filespec::_clp_name(1);
        assign(base+9);//p1
        pop();
        line(68);
        push_symbol(base+0);//deplist
        idxr0(2);
        _nsp_filespec::_clp_path(1);
        assign(base+10);//p2
        pop();
        push_symbol(base+10);//p2
        _clp_empty(1);
        if(flag()){
        string(L".");
        }else{
        push_symbol(base+10);//p2
        }
        assign(base+10);//p2
        pop();
        line(69);
        push_symbol(base+0);//deplist
        idxr0(2);
        assign(base+11);//p3
        pop();
        line(72);
        {
        line(70);
        push(&ONE);
        int sg=sign();
        number(3);
        assign(base+8);//n
        lab_8_0:
        push_symbol(base+0);//deplist
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_8_2;
            line(71);
            push_symbol(base+11);//p3
            string(L" ");
            push_symbol(base+0);//deplist
            push_symbol(base+8);//n
            idxr();
            add();
            add();
            assign(base+11);//p3
            pop();
        lab_8_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+8);//n
        add();
        assign(base+8);//n
        goto lab_8_0;
        lab_8_2:;
        }
        line(74);
        push_symbol(base+7);//torun
        string(L" ");
        add();
        push_symbol(base+9);//p1
        add();
        string(L" ");
        add();
        push_symbol(base+10);//p2
        add();
        string(L" '");
        add();
        push_symbol(base+11);//p3
        add();
        string(L"'");
        add();
        _clp_run1(1);
        pop();
    if_6_1:
    if_6_0:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

