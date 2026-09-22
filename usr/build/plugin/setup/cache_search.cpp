//input: ppo/cache_search.ppo (5.8.0)

#include <cccdef.h>

extern void _clp_alltrim(int argno);
extern void _clp_bin2hex(int argno);
extern void _clp_cache_search(int argno);
extern void _clp_crypto_sha256_final(int argno);
extern void _clp_crypto_sha256_init(int argno);
extern void _clp_crypto_sha256_update(int argno);
extern void _clp_def_quit(int argno);
extern void _clp_direxist(int argno);
extern void _clp_dirmake(int argno);
extern void _clp_empty(int argno);
extern void _clp_fclose(int argno);
extern void _clp_fcreate(int argno);
extern void _clp_ferase(int argno);
extern void _clp_file(int argno);
static void _clp_filecopy_time(int argno);
extern void _clp_fopen(int argno);
extern void _clp_fread(int argno);
extern void _clp_fwrite(int argno);
extern void _clp_len(int argno);
extern void _clp_memoread(int argno);
extern void _clp_pluginenv(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);
extern void _clp_replicate(int argno);
extern void _clp_str(int argno);

//=======================================================================
void _clp_cache_search(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+9)PUSHNIL();
argno=2;
push_call("cache_search",base);
//
    line(9);
    line(10);
    line(11);
    line(12);
    line(17);
    line(14);
    push_symbol(base+1);//env
    string(L"BUILD_CACHE");
    _clp_pluginenv(2);
    _clp_empty(1);
    if(!flag()) goto if_1_1;
        line(15);
        push_symbol(base+1);//env
        string(L"BUILD_CACHE");
        push_symbol(base+1);//env
        string(L"HOME");
        _clp_pluginenv(2);
        string(L"/.cache/build");
        add();
        _clp_pluginenv(3);
        pop();
        line(16);
        push_symbol(base+1);//env
        string(L"BUILD_CACHE");
        _clp_pluginenv(2);
        _clp_dirmake(1);
        pop();
    if_1_1:
    if_1_0:;
    line(51);
    line(19);
    push_symbol(base+1);//env
    string(L"BUILD_CACHE");
    _clp_pluginenv(2);
    _clp_direxist(1);
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+1);//env
    string(L"DEPEND");
    _clp_pluginenv(2);
    _clp_empty(1);
    topnot();
    }
    if(!flag()) goto if_2_1;
        line(20);
        _clp_crypto_sha256_init(0);
        assign(base+2);//ctx
        pop();
        line(21);
        push_symbol(base+2);//ctx
        push_symbol(base+1);//env
        string(L"CMPOPT");
        _clp_pluginenv(2);
        push(&TRUE);
        _clp_memoread(2);
        assign(base+8);//memo
        _clp_crypto_sha256_update(2);
        pop();
        line(25);
        line(22);
        push_symbol(base+8);//memo
        _clp_empty(1);
        if(!flag()) goto if_3_1;
            line(23);
            string(L"WARNING");
            string(L"cannot read dependency");
            push_symbol(base+1);//env
            string(L"CMPOPT");
            _clp_pluginenv(2);
            _clp_qout(3);
            pop();
            line(24);
            push(&NIL);
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_3_1:
        if_3_0:;
        line(27);
        push_symbol(base+1);//env
        string(L"DEPEND");
        _clp_pluginenv(2);
        assign(base+3);//dep
        pop();
        line(36);
        {
        line(28);
        push(&ONE);
        int sg=sign();
        push(&ONE);
        assign(base+4);//n
        lab_4_0:
        push_symbol(base+3);//dep
        _clp_len(1);
        if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_4_2;
            line(35);
            line(29);
            push_symbol(base+3);//dep
            push_symbol(base+4);//n
            idxr();
            _clp_empty(1);
            topnot();
            if(!flag()) goto if_5_1;
                line(30);
                push_symbol(base+2);//ctx
                push_symbol(base+3);//dep
                push_symbol(base+4);//n
                idxr();
                push(&TRUE);
                _clp_memoread(2);
                assign(base+8);//memo
                _clp_crypto_sha256_update(2);
                pop();
                line(34);
                line(31);
                push_symbol(base+8);//memo
                _clp_empty(1);
                if(!flag()) goto if_6_1;
                    line(32);
                    string(L"WARNING");
                    string(L"cannot read dependency");
                    push_symbol(base+4);//n
                    _clp_str(1);
                    _clp_alltrim(1);
                    push_symbol(base+3);//dep
                    push_symbol(base+4);//n
                    idxr();
                    _clp_qout(4);
                    pop();
                    line(33);
                    push(&NIL);
                    {*base=*(stack-1);stack=base+1;pop_call();return;}
                if_6_1:
                if_6_0:;
            if_5_1:
            if_5_0:;
        lab_4_1:
        push(&ONE);
        dup();
        sg=sign();
        push_symbol(base+4);//n
        add();
        assign(base+4);//n
        goto lab_4_0;
        lab_4_2:;
        }
        line(37);
        push_symbol(base+2);//ctx
        _clp_crypto_sha256_final(1);
        assign(base+5);//sum
        pop();
        line(38);
        push_symbol(base+5);//sum
        _clp_bin2hex(1);
        push(&ONE);
        number(64);
        slice();
        assign(base+5);//sum
        pop();
        line(39);
        push_symbol(base+1);//env
        string(L"SHASUM");
        push_symbol(base+5);//sum
        _clp_pluginenv(3);
        pop();
        line(40);
        push_symbol(base+1);//env
        string(L"BUILD_CACHE");
        _clp_pluginenv(2);
        string(L"/");
        add();
        push_symbol(base+5);//sum
        push(&ONE);
        number(2);
        slice();
        add();
        assign(base+6);//dir
        pop();
        line(41);
        push_symbol(base+6);//dir
        string(L"/");
        add();
        push_symbol(base+5);//sum
        add();
        assign(base+7);//trg
        pop();
        line(50);
        line(44);
        push_symbol(base+1);//env
        string(L"BUILD_USECACHE");
        _clp_pluginenv(2);
        string(L"no");
        neeq();
        cmp_768:;
        if(!flag()){
        push(&FALSE);
        }else{
        push_symbol(base+7);//trg
        _clp_file(1);
        }
        if(!flag()) goto if_7_1;
            line(46);
            string(L"object");
            _clp_dirmake(1);
            pop();
            line(47);
            push_symbol(base+7);//trg
            push_symbol(base+1);//env
            string(L"TARGET");
            _clp_pluginenv(2);
            _clp_filecopy_time(2);
            pop();
            line(48);
            string(L" (from cache)");
            _clp_qqout(1);
            pop();
            _clp_qout(0);
            pop();
            line(49);
            push_symbol(base+0);//arg
            push_symbol(base+1);//env
            push(&ZERO);
            _clp_def_quit(3);
            pop();
        if_7_1:
        if_7_0:;
    if_2_1:
    if_2_0:;
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_filecopy_time(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+8)PUSHNIL();
argno=2;
push_call("filecopy_time",base);
//
    line(57);
    line(58);
    line(59);
    push(&ZERO);
    assign(base+7);//nbyte
    pop();
    line(61);
    push_symbol(base+0);//fsource
    push(&ZERO);
    _clp_fopen(2);
    assign(base+2);//fd1
    pop();
    line(64);
    line(62);
    push_symbol(base+2);//fd1
    push(&ZERO);
    lt();
    cmp_999:;
    if(!flag()) goto if_8_1;
        line(63);
        push(&ZERO);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_8_1:
    if_8_0:;
    line(66);
    push_symbol(base+1);//ftarget
    _clp_ferase(1);
    pop();
    line(67);
    push_symbol(base+1);//ftarget
    _clp_fcreate(1);
    assign(base+3);//fd2
    pop();
    line(71);
    line(68);
    push_symbol(base+3);//fd2
    push(&ZERO);
    lt();
    cmp_1061:;
    if(!flag()) goto if_9_1;
        line(69);
        push_symbol(base+2);//fd1
        _clp_fclose(1);
        pop();
        line(70);
        push(&ZERO);
        {*base=*(stack-1);stack=base+1;pop_call();return;}
    if_9_1:
    if_9_0:;
    line(73);
    binaryx("00");
    number(4096);
    _clp_replicate(2);
    assign(base+4);//buf
    pop();
    line(74);
    push_symbol(base+2);//fd1
    push_symbol_ref(base+4);//buf
    push_symbol(base+4);//buf
    _clp_len(1);
    _clp_fread(3);
    assign(base+5);//nr
    pop();
    line(81);
    lab_10_1:
    line(75);
    push_symbol(base+5);//nr
    push(&ZERO);
    gt();
    cmp_1169:;
    if(!flag()) goto lab_10_2;
        line(76);
        push_symbol(base+7);//nbyte
        push_symbol(base+3);//fd2
        push_symbol(base+4);//buf
        push_symbol(base+5);//nr
        _clp_fwrite(3);
        assign(base+6);//nw
        add();
        assign(base+7);//nbyte
        pop();
        line(79);
        line(77);
        push_symbol(base+6);//nw
        push_symbol(base+5);//nr
        neeq();
        cmp_1222:;
        if(!flag()) goto if_11_1;
            line(78);
            goto lab_10_2;//exit
        if_11_1:
        if_11_0:;
        line(80);
        push_symbol(base+2);//fd1
        push_symbol_ref(base+4);//buf
        push_symbol(base+4);//buf
        _clp_len(1);
        _clp_fread(3);
        assign(base+5);//nr
        pop();
    goto lab_10_1;
    lab_10_2:;
    line(83);
    push_symbol(base+2);//fd1
    _clp_fclose(1);
    pop();
    line(84);
    push_symbol(base+3);//fd2
    _clp_fclose(1);
    pop();
    line(86);
    push_symbol(base+7);//nbyte
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

