

#include "fileio.ch"
#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()
local cmd,params
local fdout

    ?? "!TAB2HTML.BAT",arg[1],arg[2];?

    SOURCE:=arg[2]+"/"+arg[1]+".msk"
    DEPEND:=arg[3..]
    TARGET:=arg[2]+"/"+arg[1]+".html"
    OUT:="out--tab2html-"+arg[1]
    ERR:="error--tab2html-"+arg[1]

    ferase(TARGET)
    ferase(OUT)
    ferase(ERR)

    params:="-r "
    params+=arg[2]+"/"+arg[1]+".tab "
    params+=arg[2]+"/"+arg[1]+" "
    params+=arg[2]+"/"+arg[1]+".html"

    cmd:="msk2html.exe "+params
    //run(cmd+" >"+OUT)
    fdout:=fopen(OUT,FO_CREATE+FO_TRUNCATE+FO_READWRITE)
    runredir(cmd,fdout,fdout)
    fclose(fdout)

    if( !empty(memoread(out)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)


