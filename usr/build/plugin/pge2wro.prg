


#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()
local base,pge,wro,sor

    ?? "!PGE2WRO.BAT",arg[1],arg[2];?

    base:=(arg[2]+"/"+arg[1])::strtran(".pge","")
    pge:=base+".pge"
    sor:=base+".sor"
    wro:=base+".wro"

    SOURCE:=pge
    TARGET:=wro
    OUT:="out--pge2wro-"+arg[1]
    ERR:="error--pge2wro-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    if( file(sor) )
        run( "pge2wro.exe -r "+sor+" "+pge+" 2>&1 >>"+OUT )
    else
        run( "pge2wro.exe "+pge+" 2>&1 >>"+OUT )
    end

    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)


