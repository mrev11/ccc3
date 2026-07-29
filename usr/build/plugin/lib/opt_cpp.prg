
#include "pluginenv.ch"



function opt_cpp(arg,env)

local options
local eol:=chr(10)
local cppopt
local bldopt
local inc,n

    dirmake(BUILD_OBJ)

    CMPOPT:=BUILD_OBJ+"/"+"opt--cpp-"+arg[1]

    set CHANNEL(options) to (CMPOPT)
    set CHANNEL(options) on

    ?? "-Dcompile_"+CCCVER+eol
    ?? "-Dcompile_"+CCCUNAME+eol
    ?? "-Dcompile_"+CCCBIN+eol
    ?? "-Dcompile_"+MSYSTEM+eol

    cppopt:=CCCDIR+"/usr/options/"+CCCUNAME+"/"+CCCBIN+"/cppver.opt"
    ?? memoread(cppopt)

    bldopt:=CCCDIR+"/usr/options/"+CCCUNAME+"/"+CCCBIN+"/"+BUILD_OPT
    ?? memoread(bldopt)

    inc:=BUILD_INC::split(" ")
    for n:=1 to len(inc)
        if( !empty(inc[n]) )
            ?? "-I"+inc[n]::strtran("\","/")::strtran(chr(13),"")+eol
        end
    next

    if( !empty(BUILD_CFG) .and. file(BUILD_CFG) )
        ?? memoread(BUILD_CFG)+eol
    end

    set CHANNEL(options) to
    set CHANNEL(options) off

