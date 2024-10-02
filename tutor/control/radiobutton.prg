


#include "radiobutton.say"

function main()
    radiobutton({|*|load(*)},{|*|readmodal(*)},{|*|store(*)})



function load(getlist)
local group_r:={}
local group_s:={}

    g_r1:addto(group_r)
    g_r2:addto(group_r)
    g_r3:addto(group_r)

    g_s1:addto(group_s)
    g_s2:addto(group_s)
    g_s3:addto(group_s)
    g_s4:addto(group_s)

    getlist::aeval({|g|g:display})



function store(getlist)
    ? g_r1:name, g_r1:varget
    ? g_r2:name, g_r2:varget
    ? g_r3:name, g_r3:varget
    ?
    ? g_s1:name, g_s1:varget
    ? g_s2:name, g_s2:varget
    ? g_s3:name, g_s3:varget
    ? g_s4:name, g_s4:varget
    ?
    return .f. // nem lép ki
    