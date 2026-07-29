
#include "pluginenv.ch"



function compile_lex(arg,env)
local cmd

    SOURCE:=arg[2]+"/"+arg[1]+".lex"
    TARGET:="ppo/"+arg[1]+".cpp"
    OUT:="out--lex2cpp-"+arg[1]
    ERR:="error--lex2cpp-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    dirmake("ppo")

    cmd:="flex.exe "+BUILD_LEX+" -oppo/"+arg[1]+".cpp "+SOURCE+" >"+OUT+" 2>&1"
    run(cmd)

    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end
    
    ferase(OUT)