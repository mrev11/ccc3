//input: ppo/rules_from_build_bat.ppo (5.7.0.1)

#include <cccdef.h>

static void _blk_rules_from_build_bat_0(int argno);
extern void _clp_aadd(int argno);
extern void _clp_asize(int argno);
extern void _clp_asort(int argno);
extern void _clp_buildenv_bat(int argno);
static void _clp_cmp(int argno);
extern void _clp_directory(int argno);
extern void _clp_dirsep(int argno);
extern void _clp_file(int argno);
extern void _clp_len(int argno);
extern void _clp_rules_from_build_bat(int argno);
static void _clp_rulesort(int argno);
extern void _clp_s_batext(int argno);
extern void _clp_s_rules(int argno);
extern void _clp_split(int argno);
extern void _clp_strtran(int argno);

//=======================================================================
void _clp_rules_from_build_bat(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+3)PUSHNIL();
argno=0;
push_call("rules_from_build_bat",base);
//
    line(28);
    line(40);
    line(30);
    _clp_buildenv_bat(0);
    _clp_dirsep(0);
    add();
    string(L"prg2obj.bld");
    add();
    _clp_file(1);
    if(!flag()) goto if_1_1;
        line(31);
        string(L".bld");
        _clp_s_batext(1);
        pop();
    goto if_1_0;
    if_1_1:
    line(32);
    _clp_buildenv_bat(0);
    _clp_dirsep(0);
    add();
    string(L"prg2obj.bash");
    add();
    _clp_file(1);
    if(!flag()) goto if_1_2;
        line(33);
        string(L".bash");
        _clp_s_batext(1);
        pop();
    goto if_1_0;
    if_1_2:
    line(34);
    _clp_buildenv_bat(0);
    _clp_dirsep(0);
    add();
    string(L"prg2obj.sh");
    add();
    _clp_file(1);
    if(!flag()) goto if_1_3;
        line(35);
        string(L".sh");
        _clp_s_batext(1);
        pop();
    goto if_1_0;
    if_1_3:
    line(36);
    _clp_buildenv_bat(0);
    _clp_dirsep(0);
    add();
    string(L"prg2obj.msys2");
    add();
    _clp_file(1);
    if(!flag()) goto if_1_4;
        line(37);
        string(L".msys2");
        _clp_s_batext(1);
        pop();
    goto if_1_0;
    if_1_4:
    line(38);
    _clp_buildenv_bat(0);
    _clp_dirsep(0);
    add();
    string(L"prg2obj.bat");
    add();
    _clp_file(1);
    if(!flag()) goto if_1_5;
        line(39);
        string(L".bat");
        _clp_s_batext(1);
        pop();
    if_1_5:
    if_1_0:;
    line(42);
    _clp_s_rules(0);
    push(&ZERO);
    _clp_asize(2);
    pop();
    line(43);
    _clp_buildenv_bat(0);
    _clp_dirsep(0);
    add();
    string(L"*");
    add();
    _clp_s_batext(0);
    add();
    _clp_directory(1);
    assign(base+0);//d
    pop();
    line(51);
    {
    line(44);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+1);//n
    lab_2_0:
    push_symbol(base+0);//d
    _clp_len(1);
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_2_2;
        line(45);
        push_symbol(base+0);//d
        push_symbol(base+1);//n
        idxr();
        idxr0(1);
        _clp_s_batext(0);
        string(L"");
        _clp_strtran(3);
        string(L"2");
        _clp_split(2);
        assign(base+2);//rule
        pop();
        line(50);
        line(46);
        push_symbol(base+2);//rule
        _clp_len(1);
        number(2);
        eqeq();
        cmp_463:;
        if(!flag()) goto if_3_1;
            line(47);
            string(L".");
            push_symbol(base+2);//rule
            idxr0(1);
            add();
            push_symbol(base+2);//rule
            assign2(idxxl0(1));
            pop();
            line(48);
            string(L".");
            push_symbol(base+2);//rule
            idxr0(2);
            add();
            push_symbol(base+2);//rule
            assign2(idxxl0(2));
            pop();
            line(49);
            _clp_s_rules(0);
            push_symbol(base+2);//rule
            _clp_aadd(2);
            pop();
        if_3_1:
        if_3_0:;
    lab_2_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+1);//n
    add();
    assign(base+1);//n
    goto lab_2_0;
    lab_2_2:;
    }
    line(53);
    _clp_s_rules(0);
    push(&NIL);
    push(&NIL);
    block(_blk_rules_from_build_bat_0,0);
    _clp_asort(4);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}

static void _blk_rules_from_build_bat_0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("_blk_rules_from_build_bat_0",base);
//
    push_symbol(base+1);//x
    push_symbol(base+2);//y
    _clp_rulesort(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
static void _clp_rulesort(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("rulesort",base);
//
    line(60);
    line(61);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    cmp_653:;
    if(!flag()) goto if_4_1;
        string(L".exe");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_4_1:
    if_4_0:;
    line(62);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    cmp_707:;
    if(!flag()) goto if_5_1;
        string(L".so");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_5_1:
    if_5_0:;
    line(63);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    cmp_761:;
    if(!flag()) goto if_6_1;
        string(L".lib");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_6_1:
    if_6_0:;
    line(64);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    cmp_815:;
    if(!flag()) goto if_7_1;
        string(L".obj");
        push_symbol(base+0);//x
        push_symbol(base+1);//y
        _clp_cmp(3);
        assign(base+2);//result
        pop();
    if_7_1:
    if_7_0:;
    line(65);
    push_symbol(base+2);//result
    push(&NIL);
    eqeq();
    cmp_869:;
    if(!flag()) goto if_8_1;
        push_symbol(base+0);//x
        idxr0(1);
        push_symbol(base+1);//y
        idxr0(1);
        lt();
        cmp_889:;
        assign(base+2);//result
        pop();
    if_8_1:
    if_8_0:;
    line(66);
    push_symbol(base+2);//result
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_cmp(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+3)PUSHNIL();
argno=3;
push_call("cmp",base);
//
    line(73);
    line(69);
    push_symbol(base+1);//x
    idxr0(2);
    push_symbol(base+0);//ext
    eqeq();
    cmp_953:;
    if(!flag()) goto if_9_1;
        line(70);
        push_symbol(base+2);//y
        idxr0(2);
        push_symbol(base+0);//ext
        eqeq();
        cmp_973:;
        if(flag()){
        push_symbol(base+1);//x
        idxr0(1);
        push_symbol(base+2);//y
        idxr0(1);
        lt();
        cmp_985:;
        }else{
        push(&FALSE);
        }
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_9_0;
    if_9_1:
    line(71);
    push_symbol(base+2);//y
    idxr0(2);
    push_symbol(base+0);//ext
    eqeq();
    cmp_1014:;
    if(!flag()) goto if_9_2;
        line(72);
        push_symbol(base+1);//x
        idxr0(2);
        push_symbol(base+0);//ext
        eqeq();
        cmp_1034:;
        if(flag()){
        push_symbol(base+1);//x
        idxr0(1);
        push_symbol(base+2);//y
        idxr0(1);
        lt();
        cmp_1046:;
        }else{
        push(&TRUE);
        }
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_9_2:
    if_9_0:;
    line(74);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

