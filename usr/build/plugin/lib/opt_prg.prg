
#include "pluginenv.ch"



function opt_prg(arg,env)

local ch
local eol:=chr(10)
local inc,n

    dirmake("ppo")
    CMPOPT:="ppo/opt--prg-"+arg[1]
    ferase(CMPOPT)

    set CHANNEL(ch) to (CMPOPT)
    set CHANNEL(ch) on


    ?? "-Dcompile_"+CCCVER+eol
    ?? "-Dcompile_"+CCCUNAME+eol
    ?? "-Dcompile_"+CCCBIN+eol
    ?? "-Dcompile_"+MSYSTEM+eol

    ?? BUILD_PRE+eol

    inc:=BUILD_INC::split(" ")
    for n:=1 to len(inc)
        if( !empty(inc[n]) )
            ?? "-I"+inc[n]::strtran("@",":")+eol
        end
    end

    ?? "-dARROW"+eol
    ?? "-d_CCC_"+eol
    ?? "-d_CCC"+CCCVER+"_"+eol

    if( CCCUNAME == "linux" )
        ?? "-dUNIX"+eol
        ?? "-d_UNIX_"+eol
        ?? "-d_LINUX_"+eol

    elseif( CCCUNAME == "raspi" )
        ?? "-dUNIX"+eol
        ?? "-d_UNIX_"+eol
        ?? "-d_LINUX_"+eol
        ?? "-d_RASPI_"+eol

    elseif( CCCUNAME == "termux" )
        ?? "-dUNIX"+eol
        ?? "-d_UNIX_"+eol
        ?? "-d_LINUX_"+eol
        ?? "-d_TERMUX_"+eol

    elseif( CCCUNAME == "freebsd" )
        ?? "-dUNIX"+eol
        ?? "-d_UNIX_"+eol
        ?? "-d_FREEEBSD_"+eol

    elseif( CCCUNAME == "netbsd" )
        ?? "-dUNIX"+eol
        ?? "-d_UNIX_"+eol
        ?? "-d_NETBSD_"+eol

    elseif( CCCUNAME == "solaris" )
        ?? "-dUNIX"+eol
        ?? "-d_UNIX_"+eol
        ?? "-d_SOLARIS_"+eol

    elseif( CCCUNAME == "msys2" )
        ?? "-dWINDOWS"+eol
        ?? "-d_WINDOWS_"+eol
        ?? "-dWIN32"+eol
        ?? "-dMSYS2"+eol

    else
        ?? " unknown OS:",CCCUNAME
    end

    ??  memoread(CCCDIR+"/usr/options/"+CCCUNAME+"/"+CCCBIN+"/cppver.opt")

    ?? "-ustd1.ch"+eol

    set CHANNEL(ch) to
    set CHANNEL(ch) off





