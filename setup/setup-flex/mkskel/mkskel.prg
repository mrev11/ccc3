

function main()

local skel:=memoread("skel.txt")::split(chr(10)),n
local x

    ?? "/* File created from flex.skl via mkskel.sh */"
    ?

    ? '#include "flexdef.h"'
    ?

    ?  "const char *skel[] = {"

    for n:=1 to len(skel)
        x:=skel[n]
        x::=strtran('\','\\')
        x::=strtran('"','\"')
    
        ? '  "'+x+'",'
    next

    ? "  0"
    ? "};"
    ?
    ?
    