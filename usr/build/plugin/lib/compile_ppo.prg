
#include "fileio.ch"
#include "pluginenv.ch"


function compile_ppo(arg,env)
local cmd
local fdout

    SOURCE:="ppo/"+arg[1]+".ppo"
    TARGET:="ppo/"+arg[1]+".cpp"
    OUT:="out--ppo2cpp-"+arg[1]
    ERR:="error--ppo2cpp-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    cmd:="ppo2cpp.exe -q "+SOURCE
    //run(cmd+" 2>"+OUT)
    fdout:=fopen(OUT,FO_CREATE+FO_TRUNCATE+FO_READWRITE)
    runredir(cmd,fdout,fdout)
    fclose(fdout)

    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end
    
    ferase(OUT)