

#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()
local cmd,params

    ?? "!MSK2PNL.BAT",arg[1],arg[2];?

    SOURCE:=arg[2]+"/"+arg[1]+".msk"
    DEPEND:=arg[3..]
    TARGET:=arg[2]+"/"+arg[1]+".pnl"
    OUT:="out--msk2pnl-"+arg[1]
    ERR:="error--msk2pnl-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)


    run( "msk2dlg.exe --jtpanel "+SOURCE+" >"+OUT)


    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)


