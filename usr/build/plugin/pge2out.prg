


#include "fileio.ch"
#include "pluginenv.ch"


function main(*)

local arg:={*}
local env:=pluginenv_init()
local base
local cmd
local fdout

    ?? "!PGE2OUT.BAT",arg[1],arg[2];?

    base:=(arg[2]+"/"+arg[1])::strtran(".pge","")

    SOURCE:=base+".pge"
    TARGET:=base+".out"
    OUT:="out--pge2out-"+arg[1]
    ERR:="error--pge2out-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    cmd:="pge2out.exe -f"+SOURCE+" -gOUT"
    //run(cmd+" 2>&1 >>"+OUT)
    fdout:=fopen(OUT,FO_CREATE+FO_APPEND+FO_READWRITE)
    runredir(cmd,fdout,fdout)
    fclose(fdout)


    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)


