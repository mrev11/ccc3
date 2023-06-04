//input: directory.ppo (5.6.0)

#include <cccdef.h>

extern void _clp___findfirst(int argno);
extern void _clp___findnext(int argno);
extern void _clp_array(int argno);
extern void _clp_asize(int argno);
extern void _clp_convertfspec2nativeformat(int argno);
extern void _clp_directory(int argno);
extern void _clp_empty(int argno);
extern void _clp_len(int argno);
extern void _clp_strtran(int argno);
extern void _clp_upper(int argno);

//=======================================================================
void _clp_directory(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+12)PUSHNIL();
argno=3;
push_call("directory",base);
//
    line(29);
    number(32);
    _clp_array(1);
    assign(base+3);//dlist
    pop();
    push(&ZERO);
    assign(base+4);//dlist_size
    pop();
    line(31);
    line(32);
    line(33);
    push(&FALSE);
    assign(base+7);//adddir
    pop();
    line(34);
    push(&FALSE);
    assign(base+8);//addhid
    pop();
    line(35);
    push(&FALSE);
    assign(base+9);//addsys
    pop();
    line(36);
    push(&TRUE);
    assign(base+10);//addlnk
    pop();
    line(37);
    push(&FALSE);
    assign(base+11);//lnktrg
    pop();
    line(43);
    line(39);
    push_symbol(base+0);//mask
    _clp_empty(1);
    if(!flag()) goto if_1_1;
        line(40);
        binary("*");
        assign(base+0);//mask
        pop();
    goto if_1_0;
    if_1_1:
    line(41);
        line(42);
        push_symbol(base+0);//mask
        _clp_convertfspec2nativeformat(1);
        assign(base+0);//mask
        pop();
    if_1_2:
    if_1_0:;
    line(52);
    line(45);
    push_symbol(base+1);//attr
    push(&NIL);
    neeq();
    if(!flag()) goto if_2_1;
        line(46);
        push_symbol(base+1);//attr
        _clp_upper(1);
        assign(base+1);//attr
        pop();
        line(47);
        string(L"-D");
        push_symbol(base+1);//attr
        ss();
        topnot();
        if(!flag()){
        push(&FALSE);
        }else{
        string(L"D");
        push_symbol(base+1);//attr
        ss();
        }
        assign(base+7);//adddir
        pop();
        line(48);
        string(L"-H");
        push_symbol(base+1);//attr
        ss();
        topnot();
        if(!flag()){
        push(&FALSE);
        }else{
        string(L"H");
        push_symbol(base+1);//attr
        ss();
        }
        assign(base+8);//addhid
        pop();
        line(49);
        string(L"-S");
        push_symbol(base+1);//attr
        ss();
        topnot();
        if(!flag()){
        push(&FALSE);
        }else{
        string(L"S");
        push_symbol(base+1);//attr
        ss();
        }
        assign(base+9);//addsys
        pop();
        line(50);
        string(L"-L");
        push_symbol(base+1);//attr
        ss();
        topnot();
        assign(base+10);//addlnk
        pop();
        line(51);
        string(L"@L");
        push_symbol(base+1);//attr
        ss();
        assign(base+11);//lnktrg
        pop();
    if_2_1:
    if_2_0:;
    line(59);
    push_symbol_ref(base+5);//handle
    push_symbol(base+0);//mask
    push_symbol(base+2);//binopt
    push_symbol(base+11);//lnktrg
    _clp___findfirst(4);
    assign(base+6);//fitem
    pop();
    line(87);
    lab_3_1:
    line(61);
    push(&NIL);
    push_symbol(base+6);//fitem
    neeq();
    if(!flag()) goto lab_3_2;
        line(65);
        push_symbol(base+6);//fitem
        idxr0(5);
        string(L"J");
        string(L"L");
        _clp_strtran(3);
        push_symbol(base+6);//fitem
        assign2(idxxl0(5));
        pop();
        line(67);
        push_symbol(base+6);//fitem
        idxr0(5);
        assign(base+1);//attr
        pop();
        line(84);
        line(69);
        string(L"D");
        push_symbol(base+1);//attr
        ss();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+7);//adddir
        topnot();
        }
        if(!flag()) goto if_4_1;
        goto if_4_0;
        if_4_1:
        line(71);
        string(L"S");
        push_symbol(base+1);//attr
        ss();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+9);//addsys
        topnot();
        }
        if(!flag()) goto if_4_2;
        goto if_4_0;
        if_4_2:
        line(73);
        string(L"H");
        push_symbol(base+1);//attr
        ss();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+8);//addhid
        topnot();
        }
        if(!flag()) goto if_4_3;
        goto if_4_0;
        if_4_3:
        line(75);
        string(L"L");
        push_symbol(base+1);//attr
        ss();
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+10);//addlnk
        topnot();
        }
        if(!flag()) goto if_4_4;
        goto if_4_0;
        if_4_4:
        line(77);
            line(82);
            line(80);
            push_symbol(base+4);//dlist_size
            push_symbol(base+3);//dlist
            _clp_len(1);
            gteq();
            if(!flag()) goto if_5_1;
                line(81);
                push_symbol(base+3);//dlist
                push_symbol(base+4);//dlist_size
                addnum(32);
                _clp_asize(2);
                pop();
            if_5_1:
            if_5_0:;
            line(83);
            push_symbol(base+6);//fitem
            push_symbol(base+3);//dlist
            push_symbol(base+4);//dlist_size
            push(&ONE);
            add();
            assign(base+4);//dlist_size
            assign2(idxxl());
            pop();
        if_4_5:
        if_4_0:;
        line(86);
        push_symbol_ref(base+5);//handle
        _clp___findnext(1);
        assign(base+6);//fitem
        pop();
    goto lab_3_1;
    lab_3_2:;
    line(92);
    push_symbol(base+3);//dlist
    push_symbol(base+4);//dlist_size
    _clp_asize(2);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

