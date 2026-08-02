
#include "fileio.ch"
#include "pluginenv.ch"



function compile_lem(arg,env)
local cmd
local fdout

    SOURCE:=arg[2]+"/"+arg[1]+".lem"
    TARGET:="ppo/"+arg[1]+".cpp"
    OUT:="out--lem2cpp-"+arg[1]
    ERR:="error--lem2cpp-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    dirmake("ppo")

    cmd:="lemon.exe -q o=ppo/"+arg[1]+".cpp "+SOURCE
    //run(cmd+" >"+OUT+" 2>&1")
    fdout:=fopen(OUT,FO_CREATE+FO_TRUNCATE+FO_READWRITE)
    runredir(cmd,fdout,fdout)
    fclose(fdout)


    if( ! ("pathsearch" $ memoread(OUT)) )
        // kerdes, hogyan lehet kitalalni
        // hogy rendben lefutott-e a lemon

        def_quit(arg,env,1)
    end

    ferase(OUT)

