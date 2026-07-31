
#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()

    ?? "!TDS2OBJ.BAT",arg[1],arg[2]
    
    SOURCE:=arg[2]+"/"+arg[1]+".tds"
    DEPEND:=arg[3..]
    TARGET:=BUILD_OBJ+"/"+arg[1]+".obj"
    OUT:="out--tds2obj-"+arg[1]
    ERR:="error--tds2obj-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    opt_prg(arg,env)
    cache_search(arg,env)
    compile_tds(arg,env)

    SOURCE:="ppo/"+arg[1]+".prg"
    compile_prg(arg,env)
    opt_ppo(arg,env)
    compile_ppo(arg,env)

    SOURCE:="ppo/"+arg[1]+".cpp"
    opt_cpp(arg,env)
    compile_cpp(arg,env)
    cache_store(arg,env)
    
    
