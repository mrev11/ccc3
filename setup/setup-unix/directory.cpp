//input: directory.ppo (5.0.21)

#include <cccdef.h>

extern void _clp____opendir(int argno);
extern void _clp____readdir(int argno);
extern void _clp____readlink(int argno);
extern void _clp_aadd(int argno);
extern void _clp_array(int argno);
extern void _clp_asize(int argno);
extern void _clp_bin2str(int argno);
extern void _clp_convertfspec2nativeformat(int argno);
extern void _clp_directory(int argno);
extern void _clp_empty(int argno);
extern void _clp_get_dosconv(int argno);
extern void _clp_len(int argno);
extern void _clp_like(int argno);
extern void _clp_lstat_st_mode(int argno);
extern void _clp_numand(int argno);
extern void _clp_ostime2dati(int argno);
extern void _clp_rat(int argno);
extern void _clp_s_isdir(int argno);
extern void _clp_s_islnk(int argno);
extern void _clp_stat(int argno);
extern void _clp_substr(int argno);
extern void _clp_upper(int argno);

//=======================================================================
void _clp_directory(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,3);
while(stack<base+23)PUSHNIL();
argno=3;
push_call("directory",base);
//
    line(53);
    number(32);
    _clp_array(1);
    assign(base+3);//dlist
    pop();
    push(&ZERO);
    assign(base+4);//dlist_size
    pop();
    line(54);
    _clp_get_dosconv(0);
    number(512);
    _clp_numand(2);
    push(&ZERO);
    neeq();
    assign(base+5);//fname_upper
    pop();
    line(55);
    _clp_get_dosconv(0);
    number(1024);
    _clp_numand(2);
    push(&ZERO);
    neeq();
    assign(base+6);//fspec_asterix
    pop();
    line(56);
    line(57);
    push(&FALSE);
    assign(base+16);//adddir
    pop();
    line(58);
    push(&TRUE);
    assign(base+18);//addlnk
    pop();
    line(59);
    push(&FALSE);
    assign(base+20);//lnktrg
    pop();
    line(60);
    line(61);
    line(67);
    line(63);
    push_symbol(base+0);//mask
    _clp_empty(1);
    if(!flag()) goto if_1_1;
        line(64);
        binary("*");
        assign(base+0);//mask
        pop();
    goto if_1_0;
    if_1_1:
    line(65);
        line(66);
        push_symbol(base+0);//mask
        _clp_convertfspec2nativeformat(1);
        assign(base+0);//mask
        pop();
    if_1_2:
    if_1_0:;
    line(69);
    push_symbol(base+2);//binopt
    _clp_empty(1);
    topnot();
    assign(base+2);//binopt
    pop();
    line(80);
    line(71);
    push(&ZERO);
    binary("/");
    push_symbol(base+0);//mask
    _clp_rat(2);
    assign(base+15);//i
    eqeq();
    if(!flag()) goto if_2_1;
        line(72);
        binary(".");
        assign(base+7);//dirspec
        pop();
        line(73);
        push_symbol(base+0);//mask
        assign(base+8);//fmask
        pop();
    goto if_2_0;
    if_2_1:
    line(74);
    push_symbol(base+15);//i
    push(&ONE);
    eqeq();
    if(!flag()) goto if_2_2;
        line(75);
        binary("/");
        assign(base+7);//dirspec
        pop();
        line(76);
        push_symbol(base+0);//mask
        number(2);
        _clp_substr(2);
        assign(base+8);//fmask
        pop();
    goto if_2_0;
    if_2_2:
    line(77);
        line(78);
        push_symbol(base+0);//mask
        push(&ONE);
        push_symbol(base+15);//i
        addnum(-1);
        _clp_substr(3);
        assign(base+7);//dirspec
        pop();
        line(79);
        push_symbol(base+0);//mask
        push_symbol(base+15);//i
        addnum(1);
        _clp_substr(2);
        assign(base+8);//fmask
        pop();
    if_2_3:
    if_2_0:;
    line(84);
    line(82);
    push_symbol(base+6);//fspec_asterix
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+8);//fmask
    binary("*.*");
    eqeq();
    }
    if(!flag()) goto if_3_1;
        line(83);
        binary("*");
        assign(base+8);//fmask
        pop();
    if_3_1:
    if_3_0:;
    line(91);
    line(86);
    push_symbol(base+1);//type
    push(&NIL);
    neeq();
    if(!flag()) goto if_4_1;
        line(87);
        push_symbol(base+1);//type
        _clp_upper(1);
        assign(base+1);//type
        pop();
        line(88);
        string(L"-D");
        push_symbol(base+1);//type
        ss();
        topnot();
        if(!flag()){
        push(&FALSE);
        }else{
        string(L"D");
        push_symbol(base+1);//type
        ss();
        }
        assign(base+16);//adddir
        pop();
        line(89);
        string(L"-L");
        push_symbol(base+1);//type
        ss();
        topnot();
        assign(base+18);//addlnk
        pop();
        line(90);
        string(L"@L");
        push_symbol(base+1);//type
        ss();
        assign(base+20);//lnktrg
        pop();
    if_4_1:
    if_4_0:;
    line(99);
    line(93);
    push_symbol(base+8);//fmask
    _clp_empty(1);
    topnot();
    if(!flag()){
    push(&FALSE);
    }else{
    binary("?");
    push_symbol(base+8);//fmask
    ss();
    topnot();
    }
    if(!flag()){
    push(&FALSE);
    }else{
    binary("*");
    push_symbol(base+8);//fmask
    ss();
    topnot();
    }
    if(!flag()) goto if_5_1;
        line(95);
        push_symbol(base+8);//fmask
        assign(base+9);//fname
        pop();
    goto if_5_0;
    if_5_1:
    line(96);
        line(97);
        push_symbol_ref(base+21);//dirstream
        push_symbol(base+7);//dirspec
        push(&TRUE);
        _clp____opendir(3);
        pop();
        line(98);
        push_symbol_ref(base+21);//dirstream
        _clp____readdir(1);
        assign(base+9);//fname
        pop();
    if_5_2:
    if_5_0:;
    line(152);
    lab_6_1:
    line(101);
    push(&NIL);
    push_symbol(base+9);//fname
    neeq();
    if(!flag()) goto lab_6_2;
        line(149);
        line(103);
        push_symbol(base+8);//fmask
        push_symbol(base+9);//fname
        _clp_like(2);
        if(!flag()) goto if_7_1;
            line(105);
            push_symbol(base+7);//dirspec
            binary("/");
            add();
            push_symbol(base+9);//fname
            add();
            assign(base+10);//dfname
            pop();
            line(106);
            push_symbol(base+10);//dfname
            _clp_stat(1);
            assign(base+12);//st
            pop();
            line(107);
            push_symbol(base+10);//dfname
            _clp_lstat_st_mode(1);
            assign(base+13);//lsm
            pop();
            line(148);
            line(109);
            push(&NIL);
            push_symbol(base+12);//st
            eqeq();
            if(flag()){
            push(&TRUE);
            }else{
            push(&NIL);
            push_symbol(base+13);//lsm
            eqeq();
            }
            if(!flag()) goto if_8_1;
            goto if_8_0;
            if_8_1:
            line(112);
            push_symbol(base+12);//st
            idxr0(3);
            _clp_s_isdir(1);
            assign(base+17);//isdir
            if(!flag()){
            push(&FALSE);
            }else{
            push_symbol(base+16);//adddir
            topnot();
            }
            if(!flag()) goto if_8_2;
            goto if_8_0;
            if_8_2:
            line(115);
            push_symbol(base+13);//lsm
            _clp_s_islnk(1);
            assign(base+19);//islnk
            if(!flag()){
            push(&FALSE);
            }else{
            push_symbol(base+18);//addlnk
            topnot();
            }
            if(!flag()) goto if_8_3;
            goto if_8_0;
            if_8_3:
            line(118);
                line(120);
                push_symbol(base+12);//st
                idxr0(12);
                _clp_ostime2dati(1);
                assign(base+14);//dati
                pop();
                line(122);
                string(L"");
                assign(base+11);//ftype
                pop();
                line(125);
                line(123);
                push_symbol(base+17);//isdir
                if(!flag()) goto if_9_1;
                    line(124);
                    push_symbol(base+11);//ftype
                    string(L"D");
                    add();
                    assign(base+11);//ftype
                    pop();
                if_9_1:
                if_9_0:;
                line(128);
                line(126);
                push_symbol(base+19);//islnk
                if(!flag()) goto if_10_1;
                    line(127);
                    push_symbol(base+11);//ftype
                    string(L"L");
                    add();
                    assign(base+11);//ftype
                    pop();
                if_10_1:
                if_10_0:;
                line(132);
                line(130);
                push_symbol(base+4);//dlist_size
                push_symbol(base+3);//dlist
                _clp_len(1);
                gteq();
                if(!flag()) goto if_11_1;
                    line(131);
                    push_symbol(base+3);//dlist
                    push_symbol(base+4);//dlist_size
                    addnum(32);
                    _clp_asize(2);
                    pop();
                if_11_1:
                if_11_0:;
                line(136);
                line(134);
                push_symbol(base+2);//binopt
                topnot();
                if(!flag()) goto if_12_1;
                    line(135);
                    push_symbol(base+9);//fname
                    _clp_bin2str(1);
                    assign(base+9);//fname
                    pop();
                if_12_1:
                if_12_0:;
                line(138);
                push_symbol(base+5);//fname_upper
                if(flag()){
                push_symbol(base+9);//fname
                _clp_upper(1);
                }else{
                push_symbol(base+9);//fname
                }
                push_symbol(base+12);//st
                idxr0(8);
                push_symbol(base+14);//dati
                idxr0(1);
                push_symbol(base+14);//dati
                idxr0(2);
                push_symbol(base+11);//ftype
                array(5);
                push_symbol(base+3);//dlist
                push_symbol(base+4);//dlist_size
                push(&ONE);
                add();
                assign(base+4);//dlist_size
                assign2(idxxl());
                pop();
                line(147);
                line(145);
                push_symbol(base+19);//islnk
                if(!flag()){
                push(&FALSE);
                }else{
                push_symbol(base+20);//lnktrg
                }
                if(!flag()){
                push(&FALSE);
                }else{
                push_symbol(base+10);//dfname
                push_symbol(base+2);//binopt
                _clp____readlink(2);
                assign(base+22);//linktarget
                push(&NIL);
                neeq();
                }
                if(!flag()) goto if_13_1;
                    line(146);
                    push_symbol(base+3);//dlist
                    push_symbol(base+4);//dlist_size
                    idxr();
                    push_symbol(base+22);//linktarget
                    _clp_aadd(2);
                    pop();
                if_13_1:
                if_13_0:;
            if_8_4:
            if_8_0:;
        if_7_1:
        if_7_0:;
        line(151);
        push_symbol_ref(base+21);//dirstream
        _clp____readdir(1);
        assign(base+9);//fname
        pop();
    goto lab_6_1;
    lab_6_2:;
    line(157);
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

