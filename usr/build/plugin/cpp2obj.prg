
#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()

    ?? "!CPP2OBJ.BAT",arg[1],arg[2]
    
    SOURCE:=arg[2]+"/"+arg[1]+".cpp"
    DEPEND:=arg[3..]
    TARGET:=BUILD_OBJ+"/"+arg[1]+".obj"
    OUT:="out--cpp2obj-"+arg[1]
    ERR:="error--cpp2obj-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    opt_cpp(arg,env)
    cache_search(arg,env)
    compile_cpp(arg,env)
    cache_store(arg,env)
    
    
