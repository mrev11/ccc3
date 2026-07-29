
#include "pluginenv.ch"



function compile_prg(arg,env)

local cmd

    //SOURCE (valtozhat)
    TARGET:="ppo/"+arg[1]+".ppo"
    OUT:="out--prg2ppo-"+arg[1]
    ERR:="error--prg2ppo-"+arg[1]
    
    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    dirmake("ppo")

    cmd:="prg2ppo.exe "+SOURCE+" -o"+TARGET+" @"+CMPOPT+" >"+OUT
    run(cmd)
    
    if( !"Number of translate rules"$memoread(OUT) )
        def_quit(arg,env,1)
    end

    ferase(OUT)

