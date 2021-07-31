//input: deferror.ppo (5.3.0)

#include <cccdef.h>

static void _blk__0(int argno);
static void _blk__1(int argno);
static void _blk__2(int argno);
extern void _clp___quit(int argno);
extern void _clp___varprint(int argno);
extern void _clp_aadd(int argno);
extern void _clp_alert(int argno);
extern void _clp_bin2str(int argno);
extern void _clp_breakblock(int argno);
extern void _clp_callstack(int argno);
static void _clp_deferror(int argno);
static void _clp_defquit(int argno);
static void _clp_defsignal(int argno);
extern void _clp_empty(int argno);
extern void _clp_errorblock(int argno);
extern void _clp_errorclass(int argno);
extern void _clp_errorlevel(int argno);
extern void _clp_errornew(int argno);
extern void _clp_len(int argno);
extern void _clp_qout(int argno);
extern void _clp_qqout(int argno);
extern void _clp_quitblock(int argno);
extern void _clp_set(int argno);
extern void _clp_signal_description(int argno);
extern void _clp_signal_lock(int argno);
extern void _clp_signal_unlock(int argno);
extern void _clp_signalblock(int argno);
extern void _clp_thread_mutex_init(int argno);
extern void _clp_thread_mutex_lock(int argno);
extern void _clp_thread_mutex_unlock(int argno);
extern void _clp_valtype(int argno);
extern void _clp_varstack(int argno);
static void _ini__errorblk();
static void _ini__mutex();
static void _ini__quitblk();
static void _ini__signalblk();

class _method6_args: public _method6_{public: _method6_args():_method6_("args"){};}; static _method6_args _o_method_args;
class _method6_candefault: public _method6_{public: _method6_candefault():_method6_("candefault"){};}; static _method6_candefault _o_method_candefault;
class _method6_canretry: public _method6_{public: _method6_canretry():_method6_("canretry"){};}; static _method6_canretry _o_method_canretry;
class _method6_cansubstitute: public _method6_{public: _method6_cansubstitute():_method6_("cansubstitute"){};}; static _method6_cansubstitute _o_method_cansubstitute;
class _method6_classname: public _method6_{public: _method6_classname():_method6_("classname"){};}; static _method6_classname _o_method_classname;
class _method6_description: public _method6_{public: _method6_description():_method6_("description"){};}; static _method6_description _o_method_description;
class _method6_filename: public _method6_{public: _method6_filename():_method6_("filename"){};}; static _method6_filename _o_method_filename;
class _method6_gencode: public _method6_{public: _method6_gencode():_method6_("gencode"){};}; static _method6_gencode _o_method_gencode;
class _method6_isderivedfrom: public _method6_{public: _method6_isderivedfrom():_method6_("isderivedfrom"){};}; static _method6_isderivedfrom _o_method_isderivedfrom;
class _method6_operation: public _method6_{public: _method6_operation():_method6_("operation"){};}; static _method6_operation _o_method_operation;
class _method6_oscode: public _method6_{public: _method6_oscode():_method6_("oscode"){};}; static _method6_oscode _o_method_oscode;
class _method6_severity: public _method6_{public: _method6_severity():_method6_("severity"){};}; static _method6_severity _o_method_severity;
class _method6_subcode: public _method6_{public: _method6_subcode():_method6_("subcode"){};}; static _method6_subcode _o_method_subcode;
class _method6_subsystem: public _method6_{public: _method6_subsystem():_method6_("subsystem"){};}; static _method6_subsystem _o_method_subsystem;
class _method6_tries: public _method6_{public: _method6_tries():_method6_("tries"){};}; static _method6_tries _o_method_tries;

MUTEX_CREATE(_mutex_mutex);
static VALUE* _st_mutex_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_mutex);
    static stvar _st_mutex(_ini__mutex);
    MUTEX_UNLOCK(_mutex_mutex);
    SIGNAL_UNLOCK();
    return _st_mutex.ptr;
}
MUTEX_CREATE(_mutex_quitblk);
static VALUE* _st_quitblk_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_quitblk);
    static stvar _st_quitblk(_ini__quitblk);
    MUTEX_UNLOCK(_mutex_quitblk);
    SIGNAL_UNLOCK();
    return _st_quitblk.ptr;
}
MUTEX_CREATE(_mutex_signalblk);
static VALUE* _st_signalblk_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_signalblk);
    static stvar _st_signalblk(_ini__signalblk);
    MUTEX_UNLOCK(_mutex_signalblk);
    SIGNAL_UNLOCK();
    return _st_signalblk.ptr;
}
MUTEX_CREATE(_mutex_errorblk);
static VALUE* _st_errorblk_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_errorblk);
    static stvar _st_errorblk(_ini__errorblk);
    MUTEX_UNLOCK(_mutex_errorblk);
    SIGNAL_UNLOCK();
    return _st_errorblk.ptr;
}
MUTEX_CREATE(_mutex_breakblk);
static VALUE* _st_breakblk_ptr()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(_mutex_breakblk);
    static stvar _st_breakblk(&NIL);
    MUTEX_UNLOCK(_mutex_breakblk);
    SIGNAL_UNLOCK();
    return _st_breakblk.ptr;
}

static void _ini__mutex()
{
    _clp_thread_mutex_init(0);
}

static void _ini__quitblk()
{
    block(_blk__0,0);
}

static void _ini__signalblk()
{
    block(_blk__1,0);
}

static void _ini__errorblk()
{
    block(_blk__2,0);
}

static void _blk__0(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
argno=1;
push_call("_blk__0",base);
//
    _clp_defquit(0);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk__1(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk__1",base);
//
    push_blkarg(base+1);//signum
    _clp_defsignal(1);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}

static void _blk__2(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("_blk__2",base);
//
    push_blkarg(base+1);//e
    push(&TRUE);
    _clp_deferror(2);
//
{*base=*(stack-1);stack=base+1;pop_call();}
}
//=======================================================================
void _clp_quitblock(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("quitblock",base);
//
    line(33);
    line(34);
    _clp_signal_lock(0);
    pop();
    push_symbol(_st_mutex_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(35);
    push_symbol(_st_quitblk_ptr());//global
    assign(base+1);//oldblk
    pop();
    line(38);
    line(36);
    push_symbol(base+0);//blk
    _clp_valtype(1);
    string(L"B");
    eqeq();
    if(!flag()) goto if_1_1;
        line(37);
        push_symbol(base+0);//blk
        assign(_st_quitblk_ptr());//global
        pop();
    if_1_1:
    if_1_0:;
    line(39);
    push_symbol(_st_mutex_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    _clp_signal_unlock(0);
    pop();
    line(40);
    push_symbol(base+1);//oldblk
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_defquit(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,0);
while(stack<base+0)PUSHNIL();
argno=0;
push_call("defquit",base);
//
    line(45);
    number(24);
    string(L"");
    _clp_set(2);
    pop();
    line(46);
    number(23);
    string(L"off");
    _clp_set(2);
    pop();
    line(47);
    number(19);
    string(L"");
    _clp_set(2);
    pop();
    line(48);
    number(18);
    string(L"off");
    _clp_set(2);
    pop();
    line(49);
    number(22);
    string(L"");
    _clp_set(2);
    pop();
    line(50);
    number(21);
    string(L"off");
    _clp_set(2);
    pop();
    line(51);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_signalblock(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("signalblock",base);
//
    line(56);
    line(57);
    _clp_signal_lock(0);
    pop();
    push_symbol(_st_mutex_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(58);
    push_symbol(_st_signalblk_ptr());//global
    assign(base+1);//oldblk
    pop();
    line(61);
    line(59);
    push_symbol(base+0);//blk
    push(&NIL);
    neeq();
    if(!flag()) goto if_2_1;
        line(60);
        push_symbol(base+0);//blk
        assign(_st_signalblk_ptr());//global
        pop();
    if_2_1:
    if_2_0:;
    line(62);
    push_symbol(_st_mutex_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    _clp_signal_unlock(0);
    pop();
    line(63);
    push_symbol(base+1);//oldblk
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_defsignal(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("defsignal",base);
//
    line(68);
    _clp_errornew(0);
    assign(base+1);//err
    pop();
    line(69);
    push_symbol(base+1);//err
    push_symbol(base+0);//signum
    _clp_signal_description(1);
    _o_method_description.eval(2);
    pop();
    line(70);
    push_symbol(base+1);//err
    push_symbol(base+0);//signum
    _o_method_subcode.eval(2);
    pop();
    line(71);
    push_symbol(base+1);//err
    string(L"SIGNAL");
    _o_method_subsystem.eval(2);
    pop();
    line(72);
    push_symbol(base+1);//err
    _clp_deferror(1);
    pop();
    line(73);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_errorblock(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("errorblock",base);
//
    line(78);
    line(79);
    _clp_signal_lock(0);
    pop();
    push_symbol(_st_mutex_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(80);
    push_symbol(_st_errorblk_ptr());//global
    assign(base+1);//oldblk
    pop();
    line(83);
    line(81);
    push_symbol(base+0);//blk
    _clp_valtype(1);
    string(L"B");
    eqeq();
    if(!flag()) goto if_3_1;
        line(82);
        push_symbol(base+0);//blk
        assign(_st_errorblk_ptr());//global
        pop();
    if_3_1:
    if_3_0:;
    line(84);
    push_symbol(_st_mutex_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    _clp_signal_unlock(0);
    pop();
    line(85);
    push_symbol(base+1);//oldblk
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
static void _clp_deferror(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+6)PUSHNIL();
argno=2;
push_call("deferror",base);
//
    line(91);
    line(92);
    string(L"");
    assign(base+3);//msg
    pop();
    line(93);
    array(0);
    assign(base+4);//opt
    pop();
    line(94);
    line(142);
    line(96);
    push_symbol(base+0);//e
    _clp_valtype(1);
    string(L"O");
    eqeq();
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+0);//e
    _clp_errorclass(0);
    _o_method_isderivedfrom.eval(2);
    }
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+1);//alert
    push(&TRUE);
    eqeq();
    }
    if(!flag()) goto if_4_1;
        line(100);
        line(98);
        push_symbol(base+0);//e
        _o_method_operation.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_5_1;
            line(99);
            push_symbol(base+3);//msg
            string(nls_text(L"Operation: "));
            push_symbol(base+0);//e
            _o_method_operation.eval(1);
            _clp_bin2str(1);
            add();
            add();
            assign(base+3);//msg
            pop();
        if_5_1:
        if_5_0:;
        line(104);
        line(102);
        push_symbol(base+0);//e
        _o_method_filename.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_6_1;
            line(103);
            push_symbol(base+3);//msg
            string(L";");
            string(nls_text(L"Filename: "));
            add();
            push_symbol(base+0);//e
            _o_method_filename.eval(1);
            _clp_bin2str(1);
            add();
            add();
            assign(base+3);//msg
            pop();
        if_6_1:
        if_6_0:;
        line(108);
        line(106);
        push_symbol(base+0);//e
        _o_method_description.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_7_1;
            line(107);
            push_symbol(base+3);//msg
            string(L";");
            string(nls_text(L"Description: "));
            add();
            push_symbol(base+0);//e
            _o_method_description.eval(1);
            _clp_bin2str(1);
            add();
            add();
            assign(base+3);//msg
            pop();
        if_7_1:
        if_7_0:;
        line(112);
        line(110);
        push_symbol(base+0);//e
        _o_method_subsystem.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_8_1;
            line(111);
            push_symbol(base+3);//msg
            string(L";");
            string(nls_text(L"Subsystem: "));
            add();
            push_symbol(base+0);//e
            _o_method_subsystem.eval(1);
            _clp_bin2str(1);
            add();
            add();
            assign(base+3);//msg
            pop();
        if_8_1:
        if_8_0:;
        line(116);
        line(114);
        push_symbol(base+3);//msg
        _clp_empty(1);
        if(!flag()) goto if_9_1;
            line(115);
            string(nls_text(L"Unknown error"));
            assign(base+3);//msg
            pop();
        if_9_1:
        if_9_0:;
        line(118);
        push_symbol(base+4);//opt
        string(nls_text(L"Quit"));
        _clp_aadd(2);
        pop();
        line(122);
        line(120);
        push_symbol(base+0);//e
        _o_method_canretry.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_10_1;
            line(121);
            push_symbol(base+4);//opt
            string(nls_text(L"Retry"));
            _clp_aadd(2);
            pop();
        if_10_1:
        if_10_0:;
        line(126);
        line(124);
        push_symbol(base+0);//e
        _o_method_candefault.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_11_1;
            line(125);
            push_symbol(base+4);//opt
            string(nls_text(L"Default"));
            _clp_aadd(2);
            pop();
        if_11_1:
        if_11_0:;
        line(130);
        lab_12_1:
        line(128);
        push_symbol(base+5);//cho
        _clp_empty(1);
        if(!flag()) goto lab_12_2;
            line(129);
            push_symbol(base+3);//msg
            push_symbol(base+4);//opt
            _clp_alert(2);
            assign(base+5);//cho
            pop();
        goto lab_12_1;
        lab_12_2:;
        line(141);
        line(132);
        push_symbol(base+4);//opt
        push_symbol(base+5);//cho
        idxr();
        string(nls_text(L"Quit"));
        eqeq();
        if(!flag()) goto if_13_1;
        goto if_13_0;
        if_13_1:
        line(135);
        push_symbol(base+4);//opt
        push_symbol(base+5);//cho
        idxr();
        string(nls_text(L"Retry"));
        eqeq();
        if(!flag()) goto if_13_2;
            line(136);
            push(&TRUE);
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        goto if_13_0;
        if_13_2:
        line(138);
        push_symbol(base+4);//opt
        push_symbol(base+5);//cho
        idxr();
        string(nls_text(L"Default"));
        eqeq();
        if(!flag()) goto if_13_3;
            line(139);
            push(&FALSE);
            {*base=*(stack-1);stack=base+1;pop_call();return;}
        if_13_3:
        if_13_0:;
    if_4_1:
    if_4_0:;
    line(144);
    string(nls_text(L"default error block evaluated"));
    _clp_qout(1);
    pop();
    line(214);
    line(146);
    push_symbol(base+0);//e
    _clp_valtype(1);
    string(L"O");
    eqeq();
    if(!flag()){
    push(&FALSE);
    }else{
    push_symbol(base+0);//e
    _clp_errorclass(0);
    _o_method_isderivedfrom.eval(2);
    }
    if(!flag()) goto if_14_1;
        line(148);
        string(nls_text(L"errorclass:"));
        push_symbol(base+0);//e
        _o_method_classname.eval(1);
        _clp_qout(2);
        pop();
        line(152);
        line(150);
        push_symbol(base+0);//e
        _o_method_operation.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_15_1;
            line(151);
            string(nls_text(L"operation:"));
            push_symbol(base+0);//e
            _o_method_operation.eval(1);
            _clp_qout(2);
            pop();
        if_15_1:
        if_15_0:;
        line(156);
        line(154);
        push_symbol(base+0);//e
        _o_method_description.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_16_1;
            line(155);
            string(nls_text(L"description:"));
            push_symbol(base+0);//e
            _o_method_description.eval(1);
            _clp_qout(2);
            pop();
        if_16_1:
        if_16_0:;
        line(167);
        line(158);
        push_symbol(base+0);//e
        _o_method_args.eval(1);
        _clp_valtype(1);
        string(L"A");
        eqeq();
        if(!flag()) goto if_17_1;
            line(159);
            string(nls_text(L"args:{"));
            _clp_qout(1);
            pop();
            line(165);
            {
            line(160);
            push(&ONE);
            int sg=sign();
            push(&ONE);
            assign(base+2);//i
            lab_18_0:
            push_symbol(base+0);//e
            _o_method_args.eval(1);
            _clp_len(1);
            if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_18_2;
                line(163);
                line(161);
                push_symbol(base+2);//i
                push(&ONE);
                gt();
                if(!flag()) goto if_19_1;
                    line(162);
                    string(L", ");
                    _clp_qqout(1);
                    pop();
                if_19_1:
                if_19_0:;
                line(164);
                push_symbol(base+0);//e
                _o_method_args.eval(1);
                push_symbol(base+2);//i
                idxr();
                _clp___varprint(1);
                pop();
            lab_18_1:
            push(&ONE);
            dup();
            sg=sign();
            push_symbol(base+2);//i
            add();
            assign(base+2);//i
            goto lab_18_0;
            lab_18_2:;
            }
            line(166);
            string(L"}");
            _clp_qqout(1);
            pop();
        if_17_1:
        if_17_0:;
        line(171);
        line(169);
        push_symbol(base+0);//e
        _o_method_candefault.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_20_1;
            line(170);
            string(nls_text(L"candefault:"));
            push_symbol(base+0);//e
            _o_method_candefault.eval(1);
            _clp_qout(2);
            pop();
        if_20_1:
        if_20_0:;
        line(175);
        line(173);
        push_symbol(base+0);//e
        _o_method_canretry.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_21_1;
            line(174);
            string(nls_text(L"canretry:"));
            push_symbol(base+0);//e
            _o_method_canretry.eval(1);
            _clp_qout(2);
            pop();
        if_21_1:
        if_21_0:;
        line(179);
        line(177);
        push_symbol(base+0);//e
        _o_method_cansubstitute.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_22_1;
            line(178);
            string(nls_text(L"cansubstitute:"));
            push_symbol(base+0);//e
            _o_method_cansubstitute.eval(1);
            _clp_qout(2);
            pop();
        if_22_1:
        if_22_0:;
        line(187);
        line(185);
        push_symbol(base+0);//e
        _o_method_filename.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_23_1;
            line(186);
            string(nls_text(L"filename:"));
            push_symbol(base+0);//e
            _o_method_filename.eval(1);
            _clp_qout(2);
            pop();
        if_23_1:
        if_23_0:;
        line(191);
        line(189);
        push_symbol(base+0);//e
        _o_method_gencode.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_24_1;
            line(190);
            string(nls_text(L"gencode:"));
            push_symbol(base+0);//e
            _o_method_gencode.eval(1);
            _clp_qout(2);
            pop();
        if_24_1:
        if_24_0:;
        line(195);
        line(193);
        push_symbol(base+0);//e
        _o_method_oscode.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_25_1;
            line(194);
            string(nls_text(L"oscode:"));
            push_symbol(base+0);//e
            _o_method_oscode.eval(1);
            _clp_qout(2);
            pop();
        if_25_1:
        if_25_0:;
        line(199);
        line(197);
        push_symbol(base+0);//e
        _o_method_severity.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_26_1;
            line(198);
            string(nls_text(L"severity:"));
            push_symbol(base+0);//e
            _o_method_severity.eval(1);
            _clp_qout(2);
            pop();
        if_26_1:
        if_26_0:;
        line(203);
        line(201);
        push_symbol(base+0);//e
        _o_method_subcode.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_27_1;
            line(202);
            string(nls_text(L"subcode:"));
            push_symbol(base+0);//e
            _o_method_subcode.eval(1);
            _clp_qout(2);
            pop();
        if_27_1:
        if_27_0:;
        line(207);
        line(205);
        push_symbol(base+0);//e
        _o_method_subsystem.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_28_1;
            line(206);
            string(nls_text(L"subsystem:"));
            push_symbol(base+0);//e
            _o_method_subsystem.eval(1);
            _clp_qout(2);
            pop();
        if_28_1:
        if_28_0:;
        line(211);
        line(209);
        push_symbol(base+0);//e
        _o_method_tries.eval(1);
        _clp_empty(1);
        topnot();
        if(!flag()) goto if_29_1;
            line(210);
            string(nls_text(L"tries:"));
            push_symbol(base+0);//e
            _o_method_tries.eval(1);
            _clp_qout(2);
            pop();
        if_29_1:
        if_29_0:;
    goto if_14_0;
    if_14_1:
    line(212);
        line(213);
        string(nls_text(L"errorclass:"));
        push_symbol(base+0);//e
        _clp_valtype(1);
        push_symbol(base+0);//e
        _clp_qout(3);
        pop();
    if_14_2:
    if_14_0:;
    line(216);
    push(&ZERO);
    _clp_callstack(1);
    pop();
    line(217);
    _clp_varstack(0);
    pop();
    line(218);
    push(&ONE);
    _clp_errorlevel(1);
    pop();
    line(219);
    _clp___quit(0);
    pop();
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_breakblock(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+2)PUSHNIL();
argno=1;
push_call("breakblock",base);
//
    line(224);
    line(225);
    _clp_signal_lock(0);
    pop();
    push_symbol(_st_mutex_ptr());//global
    _clp_thread_mutex_lock(1);
    pop();
    line(226);
    push_symbol(_st_breakblk_ptr());//global
    assign(base+1);//oldblk
    pop();
    line(229);
    line(227);
    push_symbol(base+0);//blk
    _clp_valtype(1);
    string(L"B");
    eqeq();
    if(!flag()) goto if_30_1;
        line(228);
        push_symbol(base+0);//blk
        assign(_st_breakblk_ptr());//global
        pop();
    if_30_1:
    if_30_0:;
    line(230);
    push_symbol(_st_mutex_ptr());//global
    _clp_thread_mutex_unlock(1);
    pop();
    _clp_signal_unlock(0);
    pop();
    line(231);
    push_symbol(base+1);//oldblk
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

