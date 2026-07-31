

#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()
local cmd,params

    ?? "!MSK2DLG.BAT",arg[1],arg[2];?

    SOURCE:=arg[2]+"/"+arg[1]+".msk"
    DEPEND:=arg[3..]
    TARGET:=arg[2]+"/"+arg[1]+".dlg"
    OUT:="out--msk2dlg-"+arg[1]
    ERR:="error--msk2dlg-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)


    run( "msk2dlg.exe --jtdialog "+SOURCE+" >"+OUT)


    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)


