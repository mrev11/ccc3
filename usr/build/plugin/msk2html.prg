


#include "fileio.ch"
#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()
local cmd
local fdout

    ?? "!MSK2HTML.BAT",arg;?
    
    asize(arg,2)
    if( arg[2]==NIL )
        SOURCE:=arg[1]
    else
        SOURCE:=arg[2]+"/"+arg[1]
    end

    //TARGET:=arg[2]+"/"+arg[1]+".html"
    OUT:="out--msk2html-"+arg[1]
    ERR:="error--msk2html-"+arg[1]

    //ferase(TARGET)
    ferase(OUT)
    ferase(ERR)


    cmd:="msk2html.exe "+SOURCE
    //run(cmd+" >"+OUT)
    fdout:=fopen(OUT,FO_CREATE+FO_TRUNCATE+FO_READWRITE)
    runredir(cmd,fdout,fdout)
    fclose(fdout)


    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)


