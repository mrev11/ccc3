

#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()
local cmd,params

    ?? "!TDC2TDH.BAT",arg[1],arg[2];?

    SOURCE:=arg[2]+"/"+arg[1]+".tdc"
    DEPEND:=arg[3..]
    TARGET:="table."+arg[1]+".tdh"
    OUT:="out--tdc2tdh-"+arg[1]
    ERR:="error--tdc2tdh    -"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    cmd:="tdc2tdh.exe "+SOURCE+" >"+OUT
    run(cmd)

    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)
