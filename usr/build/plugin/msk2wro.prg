

#include "fileio.ch"
#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()
local base,pge,sor
local cmd
local fdout

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
  
    cmd:="msk2pge.exe -ur "+SOURCE+" "+pge
    //run(cmd+" 2>&1 >>"+OUT)
    fdout:=fopen(OUT,FO_CREATE+FO_APPEND+FO_READWRITE)
    runredir(cmd,fdout,fdout)
    fclose(fdout)
    
    if( file(sor) )
        cmd:="pge2wro.exe -r "+sor+" "+pge
    else
        cmd:="pge2wro.exe            "+pge
    end
    //run(cmd+" 2>&1 >>"+OUT)
    fdout:=fopen(OUT,FO_CREATE+FO_APPEND+FO_READWRITE)
    runredir(cmd,fdout,fdout)
    fclose(fdout)

    ferase(pge)

    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)


