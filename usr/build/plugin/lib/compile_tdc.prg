
#include "pluginenv.ch"



function compile_tdc(arg,env)
local cmd

    SOURCE:=arg[2]+"/"+arg[1]+".tdc"
    TARGET:="ppo/"+arg[1]+".prg"
    OUT:="out--tdc2prg-"+arg[1]
    ERR:="error--tdc2prg-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    dirmake("ppo")
        filecopy( SOURCE, "ppo/"+arg[1]+".tdc" )
        dirchange("ppo")
        cmd:="tdc2prg.exe "+arg[1]+".tdc >../"+OUT
        run(cmd)
    dirchange("..")

    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)