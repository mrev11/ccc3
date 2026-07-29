
#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()

    ?? "!PRG2OBJ.BAT",arg[1],arg[2]
    
    SOURCE:=arg[2]+"/"+arg[1]+".prg"
    DEPEND:=arg[3..]
    TARGET:=BUILD_OBJ+"/"+arg[1]+".obj"
    OUT:="out--prg2obj-"+arg[1]
    ERR:="error--prg2obj-"+arg[1]
    
    //? "DEPEND", DEPEND

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    opt_prg(arg,env)
    cache_search(arg,env)
    compile_prg(arg,env)
    opt_ppo(arg,env)
    compile_ppo(arg,env)

    SOURCE:="ppo/"+arg[1]+".cpp"

    opt_cpp(arg,env)
    compile_cpp(arg,env)
    cache_store(arg,env)
    
    
