

#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()

    ?? "!LIB2EXE.BAT",arg[1]+".exe",BUILD_EXE;?
    
    TARGET:=BUILD_EXE+"/"+arg[1]+".exe"
    OUT:="out--lib2exe-"+arg[1]
    ERR:="error--lib2exe-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    EXENAME:=arg[1]
    LIBNAME:=arg[2]

    link_exe(arg,env)    
    

