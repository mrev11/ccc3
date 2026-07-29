
#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()

    ?? "!OBJ2EXE.BAT",arg[1]+".exe",BUILD_EXE;?
    
    TARGET:=BUILD_EXE+"/"+arg[1]+".exe"
    OUT:="out--obj2exe-"+arg[1]
    ERR:="error--obj2exe-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    EXENAME:=arg[1]

    link_exe(arg,env)    

