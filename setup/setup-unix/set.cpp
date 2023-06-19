//input: set.ppo (5.6.0)

#include <cccdef.h>

extern void _clp___alternate(int argno);
extern void _clp___clr2num(int argno);
extern void _clp___extra(int argno);
extern void _clp___printer(int argno);
extern void _clp___setcentury(int argno);
extern void _clp_alltrim(int argno);
extern void _clp_eval(int argno);
extern void _clp_get_dosconv(int argno);
extern void _clp_lower(int argno);
extern void _clp_reset_dosconv(int argno);
extern void _clp_set(int argno);
extern void _clp_set_dosconv(int argno);
extern void _clp_setalternate(int argno);
extern void _clp_setaltfile(int argno);
extern void _clp_setcolor(int argno);
extern void _clp_setconfirm(int argno);
extern void _clp_setconsole(int argno);
extern void _clp_setcursor(int argno);
extern void _clp_setdateformat(int argno);
extern void _clp_setdosconv(int argno);
extern void _clp_setextra(int argno);
extern void _clp_setextrafile(int argno);
extern void _clp_setinsert(int argno);
extern void _clp_setlocalname(int argno);
extern void _clp_setprinter(int argno);
extern void _clp_setprintfile(int argno);
extern void _clp_strtran(int argno);
extern void _clp_valtype(int argno);

//=======================================================================
void _clp_set(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+4)PUSHNIL();
argno=4;
push_call("_clp_set",base);
//
    line(69);
    line(27);
    push_symbol(base+0);//spec
    number(17);
    eqeq();
    if(!flag()) goto if_1_1;
        line(28);
        push_symbol(base+1);//newset
        _clp_setconsole(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_1_0;
    if_1_1:
    line(30);
    push_symbol(base+0);//spec
    number(23);
    eqeq();
    if(!flag()) goto if_1_2;
        line(31);
        push_symbol(base+1);//newset
        _clp_setprinter(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_1_0;
    if_1_2:
    line(33);
    push_symbol(base+0);//spec
    number(24);
    eqeq();
    if(!flag()) goto if_1_3;
        line(34);
        push_symbol(base+1);//newset
        push_symbol(base+2);//mode
        push_symbol(base+3);//xmode
        _clp_setprintfile(3);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_1_0;
    if_1_3:
    line(36);
    push_symbol(base+0);//spec
    number(18);
    eqeq();
    if(!flag()) goto if_1_4;
        line(37);
        push_symbol(base+1);//newset
        _clp_setalternate(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_1_0;
    if_1_4:
    line(39);
    push_symbol(base+0);//spec
    number(19);
    eqeq();
    if(!flag()) goto if_1_5;
        line(40);
        push_symbol(base+1);//newset
        push_symbol(base+2);//mode
        push_symbol(base+3);//xmode
        _clp_setaltfile(3);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_1_0;
    if_1_5:
    line(42);
    push_symbol(base+0);//spec
    number(21);
    eqeq();
    if(!flag()) goto if_1_6;
        line(43);
        push_symbol(base+1);//newset
        _clp_setextra(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_1_0;
    if_1_6:
    line(45);
    push_symbol(base+0);//spec
    number(22);
    eqeq();
    if(!flag()) goto if_1_7;
        line(46);
        push_symbol(base+1);//newset
        push_symbol(base+2);//mode
        push_symbol(base+3);//xmode
        _clp_setextrafile(3);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_1_0;
    if_1_7:
    line(48);
    push_symbol(base+0);//spec
    number(16);
    eqeq();
    if(!flag()) goto if_1_8;
        line(49);
        push_symbol(base+1);//newset
        _clp_setcursor(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_1_0;
    if_1_8:
    line(51);
    push_symbol(base+0);//spec
    number(15);
    eqeq();
    if(!flag()) goto if_1_9;
        line(52);
        push_symbol(base+1);//newset
        _clp_setcolor(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_1_0;
    if_1_9:
    line(54);
    push_symbol(base+0);//spec
    number(29);
    eqeq();
    if(!flag()) goto if_1_10;
        line(55);
        push_symbol(base+1);//newset
        _clp_setinsert(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_1_0;
    if_1_10:
    line(57);
    push_symbol(base+0);//spec
    number(30);
    eqeq();
    if(!flag()) goto if_1_11;
    goto if_1_0;
    if_1_11:
    line(60);
    push_symbol(base+0);//spec
    number(27);
    eqeq();
    if(!flag()) goto if_1_12;
        line(61);
        push_symbol(base+1);//newset
        _clp_setconfirm(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_1_0;
    if_1_12:
    line(63);
    push_symbol(base+0);//spec
    number(4);
    eqeq();
    if(!flag()) goto if_1_13;
        line(64);
        push_symbol(base+1);//newset
        _clp_setdateformat(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_1_0;
    if_1_13:
    line(66);
    push_symbol(base+0);//spec
    number(39);
    eqeq();
    if(!flag()) goto if_1_14;
        line(67);
        push_symbol(base+1);//newset
        _clp_setdosconv(1);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_1_14:
    if_1_0:;
    line(70);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_setprintfile(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+4)PUSHNIL();
argno=3;
push_call("setprintfile",base);
//
    line(75);
    static stvar _st_setting;
    line(76);
    push_symbol(_st_setting.ptr);//setprintfile
    assign(base+3);//oldsetting
    pop();
    line(85);
    line(78);
    push_symbol(base+0);//p1
    push(&NIL);
    eqeq();
    if(!flag()) goto if_2_1;
    goto if_2_0;
    if_2_1:
    line(81);
    push_symbol(base+0);//p1
    _clp_valtype(1);
    string(L"C");
    eqeq();
    if(!flag()) goto if_2_2;
        line(82);
        push_symbol(base+0);//p1
        assign(_st_setting.ptr);//setprintfile
        pop();
        line(83);
        push_symbol(base+0);//p1
        push_symbol(base+1);//p2
        push_symbol(base+2);//p3
        _clp___printer(3);
        pop();
    if_2_2:
    if_2_0:;
    line(86);
    push_symbol(base+3);//oldsetting
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_setaltfile(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+4)PUSHNIL();
argno=3;
push_call("setaltfile",base);
//
    line(91);
    static stvar _st_setting;
    line(92);
    push_symbol(_st_setting.ptr);//setaltfile
    assign(base+3);//oldsetting
    pop();
    line(101);
    line(94);
    push_symbol(base+0);//p1
    push(&NIL);
    eqeq();
    if(!flag()) goto if_3_1;
    goto if_3_0;
    if_3_1:
    line(97);
    push_symbol(base+0);//p1
    _clp_valtype(1);
    string(L"C");
    eqeq();
    if(!flag()) goto if_3_2;
        line(98);
        push_symbol(base+0);//p1
        assign(_st_setting.ptr);//setaltfile
        pop();
        line(99);
        push_symbol(base+0);//p1
        push_symbol(base+1);//p2
        push_symbol(base+2);//p3
        _clp___alternate(3);
        pop();
    if_3_2:
    if_3_0:;
    line(102);
    push_symbol(base+3);//oldsetting
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_setextrafile(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+4)PUSHNIL();
argno=3;
push_call("setextrafile",base);
//
    line(107);
    static stvar _st_setting;
    line(108);
    push_symbol(_st_setting.ptr);//setextrafile
    assign(base+3);//oldsetting
    pop();
    line(117);
    line(110);
    push_symbol(base+0);//p1
    push(&NIL);
    eqeq();
    if(!flag()) goto if_4_1;
    goto if_4_0;
    if_4_1:
    line(113);
    push_symbol(base+0);//p1
    _clp_valtype(1);
    string(L"C");
    eqeq();
    if(!flag()) goto if_4_2;
        line(114);
        push_symbol(base+0);//p1
        assign(_st_setting.ptr);//setextrafile
        pop();
        line(115);
        push_symbol(base+0);//p1
        push_symbol(base+1);//p2
        push_symbol(base+2);//p3
        _clp___extra(3);
        pop();
    if_4_2:
    if_4_0:;
    line(118);
    push_symbol(base+3);//oldsetting
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_setcolor(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("setcolor",base);
//
    line(123);
    static stvar _st_setting(L"W/N,N/W,W/N,W/N,W/N,W/N,W/N");
    line(124);
    push_symbol(_st_setting.ptr);//setcolor
    assign(base+1);//oldsetting
    pop();
    line(133);
    line(126);
    push_symbol(base+0);//newset
    push(&NIL);
    eqeq();
    if(!flag()) goto if_5_1;
    goto if_5_0;
    if_5_1:
    line(129);
    push_symbol(base+0);//newset
    _clp_valtype(1);
    string(L"C");
    eqeq();
    if(!flag()) goto if_5_2;
        line(130);
        push_symbol(base+0);//newset
        assign(_st_setting.ptr);//setcolor
        pop();
        line(131);
        push_symbol(base+0);//newset
        _clp___clr2num(1);
        pop();
    if_5_2:
    if_5_0:;
    line(134);
    push_symbol(base+1);//oldsetting
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_setinsert(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("setinsert",base);
//
    line(139);
    static stvar _st_setting(&TRUE);
    line(140);
    push_symbol(_st_setting.ptr);//setinsert
    assign(base+1);//oldsetting
    pop();
    line(148);
    line(142);
    push_symbol(base+0);//newset
    push(&NIL);
    eqeq();
    if(!flag()) goto if_6_1;
    goto if_6_0;
    if_6_1:
    line(145);
    push_symbol(base+0);//newset
    _clp_valtype(1);
    string(L"L");
    eqeq();
    if(!flag()) goto if_6_2;
        line(146);
        push_symbol(base+0);//newset
        assign(_st_setting.ptr);//setinsert
        pop();
    if_6_2:
    if_6_0:;
    line(149);
    push_symbol(base+1);//oldsetting
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_setconfirm(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("setconfirm",base);
//
    line(154);
    static stvar _st_setting(&TRUE);
    line(155);
    push_symbol(_st_setting.ptr);//setconfirm
    assign(base+1);//oldsetting
    pop();
    line(163);
    line(157);
    push_symbol(base+0);//newset
    push(&NIL);
    eqeq();
    if(!flag()) goto if_7_1;
    goto if_7_0;
    if_7_1:
    line(160);
    push_symbol(base+0);//newset
    _clp_valtype(1);
    string(L"L");
    eqeq();
    if(!flag()) goto if_7_2;
        line(161);
        push_symbol(base+0);//newset
        assign(_st_setting.ptr);//setconfirm
        pop();
    if_7_2:
    if_7_0:;
    line(164);
    push_symbol(base+1);//oldsetting
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_setdateformat(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+3)PUSHNIL();
argno=2;
push_call("setdateformat",base);
//
    line(169);
    static stvar _st_setting(L"yy.mm.dd");
    line(170);
    push_symbol(_st_setting.ptr);//setdateformat
    assign(base+2);//oldsetting
    pop();
    line(178);
    line(172);
    push_symbol(base+0);//newset
    push(&NIL);
    eqeq();
    if(!flag()) goto if_8_1;
    goto if_8_0;
    if_8_1:
    line(175);
    push_symbol(base+0);//newset
    _clp_valtype(1);
    string(L"C");
    eqeq();
    if(!flag()) goto if_8_2;
        line(176);
        push_symbol(base+0);//newset
        _clp_alltrim(1);
        _clp_lower(1);
        assign(_st_setting.ptr);//setdateformat
        pop();
    if_8_2:
    if_8_0:;
    line(179);
    push_symbol(base+2);//oldsetting
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp___setcentury(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("__setcentury",base);
//
    line(185);
    _clp_setdateformat(0);
    assign(base+1);//dform
    pop();
    line(186);
    string(L"yyyy");
    push_symbol(base+1);//dform
    ss();
    assign(base+2);//prevstate
    pop();
    line(202);
    line(188);
    push_symbol(base+0);//arg
    push(&NIL);
    neeq();
    if(!flag()) goto if_9_1;
        line(190);
        push_symbol(base+1);//dform
        string(L"yyyy");
        string(L"?");
        _clp_strtran(3);
        assign(base+1);//dform
        pop();
        line(191);
        push_symbol(base+1);//dform
        string(L"yy");
        string(L"?");
        _clp_strtran(3);
        assign(base+1);//dform
        pop();
        line(199);
        line(193);
        push_symbol(base+0);//arg
        _clp_valtype(1);
        string(L"L");
        eqeq();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+0);//arg
        }
        if(flag()){
        push(&TRUE);
        }else{
        push_symbol(base+0);//arg
        _clp_valtype(1);
        string(L"C");
        eqeq();
        if(!flag()){
        push(&FALSE);
        }else{
        string(L"on");
        push_symbol(base+0);//arg
        _clp_alltrim(1);
        _clp_lower(1);
        eqeq();
        }
        }
        if(!flag()) goto if_10_1;
            line(196);
            push_symbol(base+1);//dform
            string(L"?");
            string(L"yyyy");
            _clp_strtran(3);
            assign(base+1);//dform
            pop();
        goto if_10_0;
        if_10_1:
        line(197);
            line(198);
            push_symbol(base+1);//dform
            string(L"?");
            string(L"yy");
            _clp_strtran(3);
            assign(base+1);//dform
            pop();
        if_10_2:
        if_10_0:;
        line(201);
        push_symbol(base+1);//dform
        _clp_setdateformat(1);
        pop();
    if_9_1:
    if_9_0:;
    line(203);
    push_symbol(base+2);//prevstate
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_setdosconv(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("setdosconv",base);
//
    line(208);
    _clp_get_dosconv(0);
    assign(base+1);//prevset
    pop();
    line(227);
    line(209);
    push_symbol(base+0);//newset
    push(&NIL);
    eqeq();
    if(!flag()) goto if_11_1;
    goto if_11_0;
    if_11_1:
    line(212);
    push_symbol(base+0);//newset
    _clp_valtype(1);
    string(L"N");
    eqeq();
    if(!flag()) goto if_11_2;
        line(213);
        push_symbol(base+0);//newset
        _clp_set_dosconv(1);
        pop();
    goto if_11_0;
    if_11_2:
    line(215);
    push_symbol(base+0);//newset
    _clp_lower(1);
    string(L"fileshare");
    eqeq();
    if(!flag()) goto if_11_3;
        line(216);
        number(4096);
        _clp_set_dosconv(1);
        pop();
    goto if_11_0;
    if_11_3:
    line(218);
    push_symbol(base+0);//newset
    _clp_lower(1);
    string(L"off");
    eqeq();
    if(!flag()) goto if_11_4;
        line(219);
        push(&ZERO);
        _clp_set_dosconv(1);
        pop();
    goto if_11_0;
    if_11_4:
    line(221);
    push_symbol(base+0);//newset
    _clp_lower(1);
    string(L"on");
    eqeq();
    if(!flag()) goto if_11_5;
        line(222);
        _clp_reset_dosconv(0);
        pop();
    goto if_11_0;
    if_11_5:
    line(224);
    push_symbol(base+0);//newset
    _clp_lower(1);
    string(L"default");
    eqeq();
    if(!flag()) goto if_11_6;
        line(225);
        _clp_reset_dosconv(0);
        pop();
    if_11_6:
    if_11_0:;
    line(228);
    push_symbol(base+1);//prevset
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_setlocalname(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("setlocalname",base);
//
    line(233);
    static stvar _st_blklocalname;
    line(234);
    line(243);
    line(235);
    push_symbol(base+0);//x
    _clp_valtype(1);
    string(L"B");
    eqeq();
    if(!flag()) goto if_12_1;
        line(236);
        push_symbol(_st_blklocalname.ptr);//setlocalname
        assign(base+1);//prevblk
        pop();
        line(237);
        push_symbol(base+0);//x
        assign(_st_blklocalname.ptr);//setlocalname
        pop();
        line(238);
        push_symbol(base+1);//prevblk
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_12_0;
    if_12_1:
    line(239);
    push_symbol(_st_blklocalname.ptr);//setlocalname
    _clp_valtype(1);
    string(L"B");
    eqeq();
    if(!flag()) goto if_12_2;
        line(240);
        push_symbol(_st_blklocalname.ptr);//setlocalname
        push_symbol(base+0);//x
        _clp_eval(2);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    goto if_12_0;
    if_12_2:
    line(241);
        line(242);
        push_symbol(base+0);//x
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_12_3:
    if_12_0:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

