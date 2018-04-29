//input: day.ppo (5.0.21)

#include <cccdef.h>

extern void _clp___dat2num(int argno);
extern void _clp___setcentury(int argno);
extern void _clp__date_emptycharvalue(int argno);
extern void _clp__date_templatestring(int argno);
extern void _clp_cdow(int argno);
extern void _clp_cmonth(int argno);
extern void _clp_ctod(int argno);
static void _clp_ctos(int argno);
extern void _clp_day(int argno);
extern void _clp_dow(int argno);
extern void _clp_dtoc(int argno);
extern void _clp_dtos(int argno);
extern void _clp_empty(int argno);
extern void _clp_left(int argno);
extern void _clp_len(int argno);
extern void _clp_min(int argno);
extern void _clp_month(int argno);
extern void _clp_right(int argno);
extern void _clp_setdateformat(int argno);
extern void _clp_stod(int argno);
extern void _clp_strtran(int argno);
extern void _clp_substr(int argno);
extern void _clp_val(int argno);
extern void _clp_year(int argno);
static void _ini_cdow_d(VALUE*);
static void _ini_cmonth_m(VALUE*);

//=======================================================================
void _clp_day(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("day",base);
//
    line(25);
    line(23);
    push_symbol(base+0);//dat
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_1_1;
        line(24);
        push_symbol(base+0);//dat
        _clp_dtos(1);
        number(2);
        _clp_right(2);
        _clp_val(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_1_1:
    if_1_0:;
    line(26);
    push(&ZERO);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_dow(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("dow",base);
//
    line(33);
    line(31);
    push_symbol(base+0);//dat
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_2_1;
        line(32);
        push_symbol(base+0);//dat
        _clp___dat2num(1);
        addnum(6);
        number(7);
        modulo();
        addnum(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_2_1:
    if_2_0:;
    line(34);
    push(&ZERO);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_cdow(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("cdow",base);
//
    line(38);
    static stvarloc _st_d(_ini_cdow_d,base);
    line(39);
    push_symbol(_st_d.ptr);//cdow
    push_symbol(base+0);//dat
    _clp_dow(1);
    addnum(1);
    idxr();
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _ini_cdow_d(VALUE* base)
{
    string(L"");
    string(nls_text(L"Sunday"));
    string(nls_text(L"Monday"));
    string(nls_text(L"Tuesday"));
    string(nls_text(L"Wednesday"));
    string(nls_text(L"Thursday"));
    string(nls_text(L"Friday"));
    string(nls_text(L"Saturday"));
    array(8);
}
//=======================================================================
void _clp_month(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("month",base);
//
    line(46);
    line(44);
    push_symbol(base+0);//dat
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_3_1;
        line(45);
        push_symbol(base+0);//dat
        _clp_dtos(1);
        number(5);
        number(2);
        _clp_substr(3);
        _clp_val(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_3_1:
    if_3_0:;
    line(47);
    push(&ZERO);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_cmonth(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("cmonth",base);
//
    line(51);
    static stvarloc _st_m(_ini_cmonth_m,base);
    line(53);
    push_symbol(_st_m.ptr);//cmonth
    push_symbol(base+0);//dat
    _clp_month(1);
    addnum(1);
    idxr();
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}

static void _ini_cmonth_m(VALUE* base)
{
    string(L"");
    string(nls_text(L"January"));
    string(nls_text(L"February"));
    string(nls_text(L"March"));
    string(nls_text(L"April"));
    string(nls_text(L"May"));
    string(nls_text(L"June"));
    string(nls_text(L"July"));
    string(nls_text(L"August"));
    string(nls_text(L"September"));
    string(nls_text(L"October"));
    string(nls_text(L"November"));
    string(nls_text(L"December"));
    array(13);
}
//=======================================================================
void _clp_year(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("year",base);
//
    line(60);
    line(58);
    push_symbol(base+0);//dat
    _clp_empty(1);
    topnot();
    if(!flag()) goto if_4_1;
        line(59);
        push_symbol(base+0);//dat
        _clp_dtos(1);
        number(4);
        _clp_left(2);
        _clp_val(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_4_1:
    if_4_0:;
    line(61);
    push(&ZERO);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_ctod(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("ctod",base);
//
    line(67);
    push_symbol(base+0);//datstr
    _clp_ctos(1);
    assign(base+1);//s
    pop();
    line(71);
    line(69);
    push_symbol(base+1);//s
    _clp_len(1);
    number(8);
    neeq();
    if(!flag()) goto if_5_1;
        line(70);
        string(L"00000000");
        assign(base+1);//s
        pop();
    if_5_1:
    if_5_0:;
    line(72);
    push_symbol(base+1);//s
    _clp_stod(1);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_ctos(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+11)PUSHNIL();
argno=1;
push_call("ctos",base);
//
    line(78);
    _clp_setdateformat(0);
    assign(base+1);//dform
    pop();
    line(79);
    push_symbol(base+1);//dform
    _clp_len(1);
    assign(base+2);//lform
    pop();
    line(80);
    push_symbol(base+0);//datstr
    _clp_len(1);
    assign(base+3);//ldate
    pop();
    line(81);
    string(L"");
    assign(base+4);//y
    pop();
    string(L"");
    assign(base+5);//m
    pop();
    string(L"");
    assign(base+6);//d
    pop();
    line(89);
    line(83);
    push_symbol(base+2);//lform
    addnum(2);
    push_symbol(base+3);//ldate
    eqeq();
    if(!flag()) goto if_6_1;
        line(84);
        push_symbol(base+1);//dform
        string(L"yy");
        string(L"yyyy");
        _clp_strtran(3);
        assign(base+1);//dform
        pop();
        line(85);
        push_symbol(base+1);//dform
        _clp_len(1);
        assign(base+2);//lform
        pop();
    goto if_6_0;
    if_6_1:
    line(86);
    push_symbol(base+2);//lform
    push_symbol(base+3);//ldate
    addnum(2);
    eqeq();
    if(!flag()) goto if_6_2;
        line(87);
        push_symbol(base+1);//dform
        string(L"yyyy");
        string(L"yy");
        _clp_strtran(3);
        assign(base+1);//dform
        pop();
        line(88);
        push_symbol(base+1);//dform
        _clp_len(1);
        assign(base+2);//lform
        pop();
    if_6_2:
    if_6_0:;
    line(91);
    push_symbol(base+2);//lform
    push_symbol(base+3);//ldate
    _clp_min(2);
    assign(base+10);//lm
    pop();
    line(102);
    {
    line(93);
    push(&ONE);
    int sg=sign();
    push(&ONE);
    assign(base+7);//n
    lab_7_0:
    push_symbol(base+10);//lm
    if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_7_2;
        line(94);
        push_symbol(base+1);//dform
        push_symbol(base+7);//n
        push(&ONE);
        _clp_substr(3);
        assign(base+8);//c
        pop();
        line(101);
        line(95);
        push_symbol(base+8);//c
        string(L"y");
        eqeq();
        if(!flag()) goto if_8_1;
            line(96);
            push_symbol(base+4);//y
            push_symbol(base+0);//datstr
            push_symbol(base+7);//n
            push(&ONE);
            _clp_substr(3);
            add();
            assign(base+4);//y
            pop();
        goto if_8_0;
        if_8_1:
        line(97);
        push_symbol(base+8);//c
        string(L"m");
        eqeq();
        if(!flag()) goto if_8_2;
            line(98);
            push_symbol(base+5);//m
            push_symbol(base+0);//datstr
            push_symbol(base+7);//n
            push(&ONE);
            _clp_substr(3);
            add();
            assign(base+5);//m
            pop();
        goto if_8_0;
        if_8_2:
        line(99);
        push_symbol(base+8);//c
        string(L"d");
        eqeq();
        if(!flag()) goto if_8_3;
            line(100);
            push_symbol(base+6);//d
            push_symbol(base+0);//datstr
            push_symbol(base+7);//n
            push(&ONE);
            _clp_substr(3);
            add();
            assign(base+6);//d
            pop();
        if_8_3:
        if_8_0:;
    lab_7_1:
    push(&ONE);
    dup();
    sg=sign();
    push_symbol(base+7);//n
    add();
    assign(base+7);//n
    goto lab_7_0;
    lab_7_2:;
    }
    line(106);
    line(104);
    push_symbol(base+4);//y
    _clp_len(1);
    number(2);
    eqeq();
    if(!flag()) goto if_9_1;
        line(105);
        push_symbol(base+4);//y
        string(L"54");
        lt();
        if(flag()){
        string(L"20");
        }else{
        string(L"19");
        }
        push_symbol(base+4);//y
        add();
        assign(base+4);//y
        pop();
    if_9_1:
    if_9_0:;
    line(108);
    push_symbol(base+4);//y
    push_symbol(base+5);//m
    add();
    push_symbol(base+6);//d
    add();
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_dtoc(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+6)PUSHNIL();
argno=1;
push_call("dtoc",base);
//
    line(114);
    line(115);
    line(119);
    line(117);
    push_symbol(base+0);//dat
    _clp_empty(1);
    if(!flag()) goto if_10_1;
        line(118);
        _clp__date_emptycharvalue(0);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_10_1:
    if_10_0:;
    line(121);
    push_symbol(base+0);//dat
    _clp_dtos(1);
    assign(base+1);//s
    pop();
    line(122);
    _clp_setdateformat(0);
    assign(base+5);//dform
    pop();
    line(128);
    line(124);
    _clp___setcentury(0);
    if(!flag()) goto if_11_1;
        line(125);
        push_symbol(base+5);//dform
        string(L"yyyy");
        push_symbol(base+1);//s
        number(4);
        _clp_left(2);
        _clp_strtran(3);
        assign(base+5);//dform
        pop();
    goto if_11_0;
    if_11_1:
    line(126);
        line(127);
        push_symbol(base+5);//dform
        string(L"yy");
        push_symbol(base+1);//s
        number(3);
        number(2);
        _clp_substr(3);
        _clp_strtran(3);
        assign(base+5);//dform
        pop();
    if_11_2:
    if_11_0:;
    line(130);
    push_symbol(base+5);//dform
    string(L"mm");
    push_symbol(base+1);//s
    number(5);
    number(2);
    _clp_substr(3);
    _clp_strtran(3);
    assign(base+5);//dform
    pop();
    line(131);
    push_symbol(base+5);//dform
    string(L"dd");
    push_symbol(base+1);//s
    number(7);
    number(2);
    _clp_substr(3);
    _clp_strtran(3);
    assign(base+5);//dform
    pop();
    line(133);
    push_symbol(base+5);//dform
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp__date_emptycharvalue(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+1)PUSHNIL();
argno=0;
push_call("_date_emptycharvalue",base);
//
    line(139);
    _clp_setdateformat(0);
    assign(base+0);//dform
    pop();
    line(140);
    push_symbol(base+0);//dform
    string(L"y");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//dform
    pop();
    line(141);
    push_symbol(base+0);//dform
    string(L"m");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//dform
    pop();
    line(142);
    push_symbol(base+0);//dform
    string(L"d");
    string(L" ");
    _clp_strtran(3);
    assign(base+0);//dform
    pop();
    line(143);
    push_symbol(base+0);//dform
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp__date_templatestring(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+1)PUSHNIL();
argno=0;
push_call("_date_templatestring",base);
//
    line(148);
    _clp_setdateformat(0);
    assign(base+0);//dform
    pop();
    line(149);
    push_symbol(base+0);//dform
    string(L"y");
    string(L"9");
    _clp_strtran(3);
    assign(base+0);//dform
    pop();
    line(150);
    push_symbol(base+0);//dform
    string(L"m");
    string(L"9");
    _clp_strtran(3);
    assign(base+0);//dform
    pop();
    line(151);
    push_symbol(base+0);//dform
    string(L"d");
    string(L"9");
    _clp_strtran(3);
    assign(base+0);//dform
    pop();
    line(152);
    push_symbol(base+0);//dform
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

