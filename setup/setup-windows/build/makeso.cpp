//input: makeso.ppo (5.6.0)

#include <cccdef.h>

extern void _clp___quit(int argno);
extern void _clp_buildenv_bat(int argno);
extern void _clp_buildenv_libdir(int argno);
extern void _clp_buildenv_obj(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_empty(int argno);
extern void _clp_errorlevel(int argno);
extern void _clp_ferase(int argno);
extern void _clp_file(int argno);
extern void _clp_filecopy(int argno);
extern void _clp_ftime(int argno);
extern void _clp_len(int argno);
extern void _clp_makeso(int argno);
extern void _clp_qout(int argno);
extern void _clp_run1(int argno);
extern void _clp_s_batext(int argno);
extern void _clp_s_debug(int argno);
extern void _clp_verifdep(int argno);

//=======================================================================
void _clp_makeso(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+11)PUSHNIL();
argno=2;
push_call("makeso",base);
//
    line(25);
    _clp_buildenv_obj(0);
    _clp_dirsep(0);
    add();
    string(L"lib");
    add();
    push_symbol(base+0);//libnam
    add();
    string(L".so");
    add();
    assign(base+2);//target
    pop();
    line(26);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(27);
    _clp_buildenv_bat(0);
    _clp_dirsep(0);
    add();
    string(L"obj2so");
    add();
    _clp_s_batext(0);
    add();
    assign(base+7);//torun
    pop();
    line(28);
    _clp_buildenv_obj(0);
    assign(base+8);//objdir
    pop();
    line(29);
    _clp_buildenv_libdir(0);
    assign(base+10);//libdir
    pop();
    line(36);
    line(31);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_1_1;
        line(32);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
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
    if_1_1:
    if_1_0:;
    line(38);
    push_symbol(base+7);//torun
    string(L" lib");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(40);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(43);
    line(41);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    if(!flag()) goto if_2_1;
        line(42);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_2_1:
    if_2_0:;
    line(47);
    line(45);
    _clp_s_debug(0);
    if(!flag()) goto if_3_1;
        line(46);
        push_symbol(base+2);//target
        string(L"[");
        push_symbol(base+3);//ttarget
        add();
        string(L"]");
        add();
        _clp_qout(2);
        pop();
    if_3_1:
    if_3_0:;
    line(55);
    {
    line(49);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_4_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
        line(51);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(52);
        push_symbol(base+7);//torun
        string(L" ");
        push_symbol(base+4);//depend
        add();
        add();
        assign(base+7);//torun
        pop();
        line(53);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(54);
        push_symbol(base+3);//ttarget
        push_symbol(base+4);//depend
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
    push_symbol(base+9);//n
    add();
    assign(base+9);//n
    goto lab_4_0;
    lab_4_2:;
    }
    line(59);
    line(57);
    _clp_s_debug(0);
    if(!flag()) goto if_5_1;
        line(58);
        _clp_qout(0);
        pop();
    if_5_1:
    if_5_0:;
    line(68);
    line(61);
    push_symbol(base+6);//update
    if(!flag()) goto if_6_1;
        line(62);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
        line(67);
        line(64);
        push_symbol(base+10);//libdir
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_7_1;
            line(65);
            push_symbol(base+10);//libdir
            _clp_dirsep(0);
            add();
            string(L"lib");
            add();
            push_symbol(base+0);//libnam
            add();
            string(L".so");
            add();
            _clp_ferase(1);
            pop();
            line(66);
            push_symbol(base+2);//target
            push_symbol(base+10);//libdir
            _clp_dirsep(0);
            add();
            string(L"lib");
            add();
            push_symbol(base+0);//libnam
            add();
            string(L".so");
            add();
            _clp_filecopy(2);
            pop();
        if_7_1:
        if_7_0:;
    if_6_1:
    if_6_0:;
    line(70);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

