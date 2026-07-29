

#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()

    ?? "!OBJ2SO.BAT",arg[1]+".so";?
    
    TARGET:=BUILD_OBJ+"/"+arg[1]+".so"
    OUT:="out--obj2so-"+arg[1]
    ERR:="error--obj2so-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    link_so(arg,env)    
    

