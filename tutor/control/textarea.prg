
#include "textarea.say"

*************************************************************************************************
function main()
    textarea({|g|load(g)}, {|g|readmodal(g)}, {|g|store(g)},50,50)
    ?

*************************************************************************************************
static function load(getlist)

    g_get1:varput:="Egyszer hopp"
    g_get2:varput:="Máskor kopp"

    g_area:varput:=memoread("textarea.prg")
    //g_area:modflag:=.f.

    g_mehet:execblock:={||NIL}  // GE_ESCAPE -> store()

    getlist::aeval({|g|g:display})


*************************************************************************************************
static function store(getlist)
local n
    for n:=1 to len(getlist)
        ? getlist[n]:name, getlist[n]:varget
    next
    return .t.


*************************************************************************************************