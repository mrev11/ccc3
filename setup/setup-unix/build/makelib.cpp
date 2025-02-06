//input: ppo/makelib.ppo (5.7.0.1)

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
extern void _clp_makelib(int argno);
extern void _clp_qout(int argno);
extern void _clp_run1(int argno);
extern void _clp_s_batext(int argno);
extern void _clp_s_debug(int argno);
extern void _clp_verifdep(int argno);

//=======================================================================
void _clp_makelib(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+12)PUSHNIL();
argno=2;
push_call("makelib",base);
//
    line(27);
    _clp_buildenv_obj(0);
    _clp_dirsep(0);
    add();
    push_symbol(base+0);//libnam
    add();
    string(L".lib");
    add();
    assign(base+2);//target
    pop();
    line(28);
    push(&FALSE);
    assign(base+6);//update
    pop();
    line(29);
    _clp_buildenv_bat(0);
    _clp_dirsep(0);
    add();
    string(L"obj2lib");
    add();
    _clp_s_batext(0);
    add();
    assign(base+7);//torun
    pop();
    line(30);
    _clp_buildenv_obj(0);
    assign(base+8);//objdir
    pop();
    line(31);
    _clp_buildenv_libdir(0);
    assign(base+10);//libdir
    pop();
    line(32);
    line(39);
    line(34);
    push_symbol(base+7);//torun
    _clp_file(1);
    topnot();
    if(!flag()) goto if_1_1;
        line(35);
        string(L"[");
        push_symbol(base+7);//torun
        add();
        string(L"]");
        add();
        string(nls_text(L"does not exist"));
        _clp_qout(2);
        pop();
        line(36);
        _clp_qout(0);
        pop();
        line(37);
        push(&ONE);
        _clp_errorlevel(1);
        pop();
        line(38);
        _clp___quit(0);
        pop();
    if_1_1:
    if_1_0:;
    line(41);
    push_symbol(base+7);//torun
    string(L" ");
    push_symbol(base+0);//libnam
    add();
    add();
    assign(base+7);//torun
    pop();
    line(43);
    push_symbol(base+2);//target
    _clp_ftime(1);
    assign(base+3);//ttarget
    pop();
    line(46);
    line(44);
    push_symbol(base+3);//ttarget
    push(&NIL);
    eqeq();
    cmp_294:;
    if(!flag()) goto if_2_1;
        line(45);
        string(L"");
        assign(base+3);//ttarget
        pop();
    if_2_1:
    if_2_0:;
    line(50);
    line(48);
    _clp_s_debug(0);
    if(!flag()) goto if_3_1;
        line(49);
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
    line(57);
    {
    line(52);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+9);//n
    lab_4_0:
    push_symbol(base+1);//object
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
        line(54);
        push_symbol(base+1);//object
        push_symbol(base+9);//n
        idxr();
        assign(base+4);//depend
        pop();
        line(55);
        push_symbol(base+8);//objdir
        _clp_dirsep(0);
        add();
        push_symbol(base+4);//depend
        add();
        string(L".obj");
        add();
        assign(base+4);//depend
        pop();
        line(56);
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
    line(61);
    line(59);
    _clp_s_debug(0);
    if(!flag()) goto if_5_1;
        line(60);
        _clp_qout(0);
        pop();
    if_5_1:
    if_5_0:;
    line(87);
    line(63);
    push_symbol(base+6);//update
    if(!flag()) goto if_6_1;
        line(68);
        {
        line(66);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+9);//n
        lab_7_0:
        push_symbol(base+1);//object
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_7_2;
            line(67);
            push_symbol(base+7);//torun
            string(L" ");
            push_symbol(base+1);//object
            push_symbol(base+9);//n
            idxr();
            add();
            add();
            assign(base+7);//torun
            pop();
        lab_7_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+9);//n
        add();
        assign(base+9);//n
        goto lab_7_0;
        lab_7_2:;
        }
        line(81);
        push_symbol(base+7);//torun
        _clp_run1(1);
        pop();
        line(86);
        line(83);
        push_symbol(base+10);//libdir
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_8_1;
            line(84);
            push_symbol(base+10);//libdir
            _clp_dirsep(0);
            add();
            push_symbol(base+0);//libnam
            add();
            string(L".lib");
            add();
            _clp_ferase(1);
            pop();
            line(85);
            push_symbol(base+2);//target
            push_symbol(base+10);//libdir
            _clp_dirsep(0);
            add();
            push_symbol(base+0);//libnam
            add();
            string(L".lib");
            add();
            _clp_filecopy(2);
            pop();
        if_8_1:
        if_8_0:;
    if_6_1:
    if_6_0:;
    line(90);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

