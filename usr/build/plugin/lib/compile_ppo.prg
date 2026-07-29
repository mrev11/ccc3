
#include "pluginenv.ch"



function compile_ppo(arg,env)
local cmd

    SOURCE:="ppo/"+arg[1]+".ppo"
    TARGET:="ppo/"+arg[1]+".cpp"
    OUT:="out--ppo2cpp-"+arg[1]
    ERR:="error--ppo2cpp-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    cmd:="ppo2cpp.exe -q "+SOURCE+" 2>"+OUT
    run(cmd)

    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end
    
    ferase(OUT)