

#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()
local base,pge,sor

    ?? "!MSK2WRO.BAT",arg[1],arg[2];?

    base:=(arg[2]+"/"+arg[1])::strtran(".msk","")

    SOURCE:=base+".msk"
    TARGET:=base+".wro"
    OUT:="out--msk2wro-"+arg[1]
    ERR:="error--msk2wro-"+arg[1]

    pge:=base+".temp"
    sor:=base+".sor"

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)
    ferase(pge)
  

    run( "msk2pge.exe -ur "+SOURCE+" "+pge+" 2>&1 >>"+OUT )
    
    if( file(sor) )
        run( "pge2wro.exe -r "+sor+" "+pge+" 2>&1 >>"+OUT )
    else
        run( "pge2wro.exe            "+pge+" 2>&1 >>"+OUT )
    end
    ferase(pge)

    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)


