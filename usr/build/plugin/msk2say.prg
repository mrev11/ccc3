

#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()
local cmd,params

    ?? "!MSK2SAY.BAT",arg[1],arg[2];?

    SOURCE:=arg[2]+"/"+arg[1]+".msk"
    DEPEND:=arg[3..]
    TARGET:=arg[2]+"/"+arg[1]+".say"
    OUT:="out--msk2say-"+arg[1]
    ERR:="error--msk2say-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    params:=arg[2]+"/"+arg[1]+" "+arg[2]+"/"+arg[1]+".say"
    if( file(arg[2]+"/"+arg[1]+".sor") )
        params:="-r "+arg[2]+"/"+arg[1]+".sor "+params
    end

    cmd:="msk2say.exe "+params+" >"+OUT
    run( cmd)

    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)


