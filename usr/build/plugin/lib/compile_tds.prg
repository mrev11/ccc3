
#include "fileio.ch"
#include "pluginenv.ch"



function compile_tds(arg,env)

local cmd
local fdout


    SOURCE:=arg[2]+"/"+arg[1]+".tds"
    TARGET:="ppo/"+arg[1]+".prg"
    OUT:="out--tds2prg-"+arg[1]
    ERR:="error--tds2prg-"+arg[1]
    
    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    dirmake("ppo")

    cmd:="tds2prg.exe "+SOURCE
    //run(cmd+" >"+OUT)
    fdout:=fopen(OUT,FO_CREATE+FO_TRUNCATE+FO_READWRITE)
    runredir(cmd,fdout,fdout)
    fclose(fdout)
    frename(arg[2]+"/"+arg[1]+".prg","ppo/"+arg[1]+".prg")
    
    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)

