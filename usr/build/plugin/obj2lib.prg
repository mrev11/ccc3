
#include "fileio.ch"
#include "pluginenv.ch"

function main(*)

local arg:={*}
local env:=pluginenv_init()

local rsp
local eol:=chr(10)
local obj,n
local cmd
local fdout

    ?? "!OBJ2LIB.BAT",arg[1]+".lib",BUILD_EXE;?

    TARGET:=BUILD_OBJ+"/"+arg[1]+".lib"
    RSPLIB:=BUILD_OBJ+"/rsp--lib-"+arg[1]
    OUT:="out--obj2lib-"+arg[1]
    ERR:="out--obj2lib-"+arg[1]
    
    ferase(TARGET)
    ferase(RSPLIB)
    ferase(OUT)
    ferase(ERR)
    
    LIBNAME:=arg[1]
   
    set CHANNEL(rsp) to (RSPLIB) 
    set CHANNEL(rsp) on


    if(  file(BUILD_OBJ+"/objects-"+LIBNAME) )
        // MSYS2
        obj:=memoread(BUILD_OBJ+"/objects-"+LIBNAME)::split(eol)
        for n:=1 to len(obj)
            ?? BUILD_OBJ+"/"+obj[n]::strtran(chr(13),"")+eol
        next
    else
        // Linux
        for n:=2 to len(arg)
            ?? BUILD_OBJ+"/"+arg[n]+".obj"+eol
        next
    end

    set CHANNEL(rsp) to
    set CHANNEL(rsp) off

    cmd:="ar -c -q "+TARGET+" "+memoread(RSPLIB)::strtran(eol," ")
    //run(cmd+" 2>"+OUT)
    fdout:=fopen(OUT,FO_CREATE+FO_TRUNCATE+FO_READWRITE)
    runredir(cmd,fdout,fdout)
    fclose(fdout)
    
    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end

    ferase(OUT)
    def_quit(arg,env,0)


    