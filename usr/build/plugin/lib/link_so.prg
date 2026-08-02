
#include "fileio.ch"
#include "pluginenv.ch"


function link_so(arg,env)

local rsp
local lpt,lib,n
local eol:=chr(10)
local cmd,tmp,x
local fdout

    RSPLNK:=BUILD_OBJ+"/rsp--so-"+arg[1]

    ferase(TARGET)
    ferase(RSPLNK)
    ferase(OUT)
    ferase(ERR)

    set channel(rsp) to (RSPLNK)
    set channel(rsp) on

    ?? "-shared"+eol
    ?? "-o "+TARGET+eol

    lpt:=BUILD_LPT::split(" ")
    for n:=1 to len(lpt)
        if( !empty(lpt[n]) )
            ?? "-L"+lpt[n]+eol
        end
    next

    for n:=2 to len(arg)
        ?? BUILD_OBJ+"/"+arg[n]+".obj"+eol
    next

    lib:=BUILD_LIB::split(" ")
    for n:=1 to len(lib)
        if( !empty(lib[n]) )
            ?? lib[n]+eol
        end
    next

    if( !empty(BUILD_LIBX) .and. file(BUILD_LIBX) )
        ?? memoread(BUILD_LIBX)+eol
    end

    ?? "-Wl,-soname="+arg[1]+".so"+eol

    ?? memoread( CCCDIR+"/usr/options/"+CCCUNAME+"/"+CCCBIN+"/link.opt")+eol

    set channel(rsp) to
    set channel(rsp) off

    cmd:="c++ "+memoread(RSPLNK)::strtran(eol," ")
    //run(cmd+" 2>"+OUT)
    fdout:=fopen(OUT,FO_CREATE+FO_TRUNCATE+FO_READWRITE)
    runredir(cmd,fdout,fdout)
    fclose(fdout)

    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)


