


#include "checkbox.say"

function main()
    checkbox({|*|load(*)},{|*|readmodal(*)},{|*|store(*)})



function load(getlist)
    g_a:varput:=.t.
    g_b:varput:=.t.
    getlist::aeval({|g|g:display})



function store(getlist)
    ? g_a:name, g_a:varget
    ? g_b:name, g_b:varget
    ? g_c:name, g_c:varget
    ? g_c2:name, g_c2:varget
    return .f. // nem lép ki
    