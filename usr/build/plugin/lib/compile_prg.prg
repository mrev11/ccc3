
#include "fileio.ch"
#include "pluginenv.ch"


function compile_prg(arg,env)

local cmd
local fdout

    //SOURCE (valtozhat)
    TARGET:="ppo/"+arg[1]+".ppo"
    OUT:="out--prg2ppo-"+arg[1]
    ERR:="error--prg2ppo-"+arg[1]
    
    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    dirmake("ppo")

    cmd:="prg2ppo.exe "+SOURCE+" -o"+TARGET+" @"+CMPOPT
    //run(cmd+" >"+OUT)
    fdout:=fopen(OUT,FO_CREATE+FO_TRUNCATE+FO_READWRITE)
    runredir(cmd,fdout,fdout)
    fclose(fdout)
    
    if( !"Number of translate rules"$memoread(OUT) )
        def_quit(arg,env,1)
    end

    ferase(OUT)

