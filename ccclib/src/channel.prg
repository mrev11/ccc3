

#clang
#include <cccapi.h>
#cend


******************************************************************************************
class channel(object)
    attrib  filespc     // file specifikacio
    attrib  fileptr     // FILE* (fopen return erteke)
    attrib  localname
    attrib  localflag

    method  open        // megnyitja
    method  close       // lezarja
    method  on          // berakja fileptr-t FP_CHANNEL-ba  -> qout kizarolag FP_CHANNEL-ba ir
    method  off         // kitorli fileptr-t FP_CHANNEL-bol -> qout FP_CONSOLE/FP_PRINTER/...-ba ir
    method  write       // ir bele
    method  writeln     // ir bele

    method  initialize


******************************************************************************************
static function channel.initialize(this,filespc)
    this:filespc:=filespc
    this:localflag:=.t.
    return this


******************************************************************************************
static function channel.open(this,additive:=.f.)
local fspc,fptr

    // Egyelore a channel-ek sosincsenek remote-olva.
    // Ha egyszer remote-olhatok lesznek, akkor fel kell 
    // majd ismerni a remote esetet, es ki kell kerulni
    // az itteni setlocalname transzformaciot.

    this:localname:=this:filespc
    if( this:localflag )
        this:localname::=setlocalname
    end
    fspc:=this:localname::convertfspec2nativeformat

#clang
    VALUE *stk=stack;
    push_symbol(LOCAL_fspc);
    str2bin(TOP());
    push_symbol(LOCAL_additive);
    const char *mode=flag()?"a":"w";
    FILE *fp=fopen(BINARYPTR(stk),mode);
    if( fp )
    {
        pointer(fp);
    }
    else
    {
        PUSHNIL();
    }
    assign(LOCAL_fptr);
    pop();
    stack=stk;
#cend
    this:fileptr:=fptr
    return this:fileptr!=NIL   // .t.=success, .f.=failed


******************************************************************************************
static function channel.close(this)
local fptr,result:=.t.
    fptr:=this:fileptr
    if( fptr!=NIL )
        if( fptr==channel.get_file_pointer() )
            channel.set_file_pointer(NIL)
        end
#clang
        VALUE *stk=stack;
        push_symbol(LOCAL_fptr);
        logical( !fclose((FILE*)stk->data.pointer) );
        assign(LOCAL_result);
        pop();
        stack=stk;
#cend
        this:fileptr:=NIL
    end
    return result // .t.=success, .f.=failed


******************************************************************************************
static function channel.on(this)
    channel.set_file_pointer(this:fileptr)

******************************************************************************************
function channel.off(this)  // nem static!
    if( this==NIL .or. this:fileptr==channel.get_file_pointer() )
        channel.set_file_pointer(NIL)
    end

******************************************************************************************
static function channel.write(this,*)
    this:on
    qqout(*[2..])
    this:off

******************************************************************************************
static function channel.writeln(this,*)
    this:on
    qqout(*[2..])
    qout()
    this:off

******************************************************************************************

