
#include "fileio.ch"
#include "pluginenv.ch"



function compile_cpp(arg,env)

local cmd
local fdout
local eol:=chr(10)

    dirmake("object")

    // SOURCE (valtozo)
    TARGET:=BUILD_OBJ+"/"+arg[1]+".obj"
    OUT:="out--cpp2obj-"+arg[1]
    ERR:="error--cpp2obj-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    cmd:="c++ "+memoread(CMPOPT)::strtran(eol," ")+" -o "+TARGET+" -c "+SOURCE
    //run(cmd+" 2>"+OUT)
    fdout:=fopen(OUT,FO_CREATE+FO_TRUNCATE+FO_READWRITE)
    runredir(cmd,fdout,fdout)
    fclose(fdout)

    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)

    if( !empty(BUILD_CPP) )
        dirmake(BUILD_CPP)
        filecopy(SOURCE,BUILD_CPP+dirsep()+filespec.basename(SOURCE))
    end




