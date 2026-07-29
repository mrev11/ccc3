

#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()
local cmd,params

    ?? "!SOR2SAY.BAT",arg[1],arg[2];?

    SOURCE:=arg[2]+"/"+arg[1]+".msk"
    DEPEND:=arg[3..]
    TARGET:=arg[2]+"/"+arg[1]+".say"
    OUT:="out--sor2say-"+arg[1]
    ERR:="error--sor2say-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    params:="-r "
    params+=arg[2]+"/"+arg[1]+".sor "
    params+=arg[2]+"/"+arg[1]+" "
    params+=arg[2]+"/"+arg[1]+".say"

    cmd:="msk2say.exe "+params+" >"+OUT
    run( cmd)

    if( !empty(memoread(out)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)


