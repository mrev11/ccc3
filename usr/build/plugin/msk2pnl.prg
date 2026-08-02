

#include "fileio.ch"
#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()
local cmd
local fdout

    ?? "!MSK2PNL.BAT",arg[1],arg[2];?

    SOURCE:=arg[2]+"/"+arg[1]+".msk"
    DEPEND:=arg[3..]
    TARGET:=arg[2]+"/"+arg[1]+".pnl"
    OUT:="out--msk2pnl-"+arg[1]
    ERR:="error--msk2pnl-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    cmd:="msk2dlg.exe --jtpanel "+SOURCE
    //run(cmd+" >"+OUT)
    fdout:=fopen(OUT,FO_CREATE+FO_TRUNCATE+FO_READWRITE)
    runredir(cmd,fdout,fdout)
    fclose(fdout)

    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)


