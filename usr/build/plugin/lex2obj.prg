

#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()

    ?? "!LEX2OBJ.BAT",arg[1],arg[2]
    
    SOURCE:=arg[2]+"/"+arg[1]+".lex"
    DEPEND:=arg[3..]
    TARGET:=BUILD_OBJ+"/"+arg[1]+".obj"
    OUT:="out--lex2obj-"+arg[1]
    ERR:="error--lex2obj-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    opt_cpp(arg,env)
    cache_search(arg,env)
    compile_lex(arg,env)

    SOURCE:="ppo/"+arg[1]+".cpp"

    compile_cpp(arg,env)
    cache_store(arg,env)
    
    
