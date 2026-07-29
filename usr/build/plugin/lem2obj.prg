

#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()

    ?? "!LEM2OBJ.BAT",arg[1],arg[2]
    
    SOURCE:=arg[2]+"/"+arg[1]+".lem"
    DEPEND:=arg[3..]
    TARGET:=BUILD_OBJ+"/"+arg[1]+".obj"
    OUT:="out--lem2obj-"+arg[1]
    ERR:="error--lem2obj-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    opt_cpp(arg,env)
    cache_search(arg,env)
    compile_lem(arg,env)

    SOURCE:="ppo/"+arg[1]+".cpp"

    compile_cpp(arg,env)
    cache_store(arg,env)
    
    
