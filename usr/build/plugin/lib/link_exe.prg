

#include "pluginenv.ch"


function link_exe(arg,env)

local rsp
local lpt,lib,n
local eol:=chr(10)
local cmd,tmp,x
local null:=if(dirsep()=="/","/dev/null","NUL")

    TARGET:=BUILD_EXE+"/"+arg[1]+".exe"
    RSPLNK:=BUILD_OBJ+"/rsp--exe-"+arg[1]

    ferase(TARGET)
    ferase(RSPLNK)
    ferase(OUT)
    ferase(ERR)

    set channel(rsp) to (RSPLNK)
    set channel(rsp) on

    ?? "-o "+TARGET+eol

    lpt:=BUILD_LPT::split(" ")
    for n:=1 to len(lpt)
        if( !empty(lpt[n]) )
            ?? "-L"+lpt[n]+eol
        end
    next

    ?? "-Wl,--start-group"+eol

    if( empty(LIBNAME) )
        // main+obj2+obj3...
        if( file( BUILD_OBJ+"/objects-"+EXENAME ) )
            ?? memoread(BUILD_OBJ+"/objects-"+EXENAME)+eol
        else
            for n:=1 to len(arg)
                ?? BUILD_OBJ+"/"+arg[n]+".obj"+eol
            next
        end
    else
        // main+lib
        ?? BUILD_OBJ+"/"+EXENAME+".obj"+eol
        ?? BUILD_OBJ+"/"+LIBNAME+".lib"+eol
    end

    lib:=BUILD_LIB::split(" ")
    for n:=1 to len(lib)
        if( !empty(lib[n]) )
            ?? lib[n]+eol
        end
    next

    if( !empty(BUILD_LIBX) .and. file(BUILD_LIBX) )
        ?? memoread(BUILD_LIBX)+eol
    end

    ?? "-Wl,--end-group"+eol

    OPT:=CCCDIR+"/usr/options/"+CCCUNAME+"/"+CCCBIN+"/link.opt"
    if( BUILD_SHR=="fullstatic" )
        ?? memoread(OPT)::strtran("-rdynamic","-static")+eol
    else
        ?? memoread(OPT)+eol
    end
    set CHANNEL(rsp) off
    set CHANNEL(rsp) to

    rsp:=memoread(RSPLNK)
    cmd:="c++ "+rsp::strtran(eol," ")+" 2>"+OUT
    run(cmd)

    if( !empty(memoread(OUT)) )
        def_quit(arg,env,1)
    end
    ferase(OUT)

    if( dirsep()=="/" )
        // Windowson a git neha nem tud kilepni
        // ami az egesz forditas leallasat okozza

        // readelf --string-dump .comment $TARGET
        tmp:=BUILD_OBJ+"/log-comid-"+arg[1]
        run( 'git log --pretty=format:"%h %ai" -1  2>'+null+' 1>'+tmp )
        if( !empty(x:=memoread(tmp)) )
            x:="COMMITID["+x+"] "
            cat(TARGET,x)
        end
        ferase(tmp)
    
        tmp:=BUILD_OBJ+"/log-cccbn-"+arg[1]
        run( "cccbn.exe -n 2>"+null+" 1>"+tmp )
        if( !empty(x:=memoread(tmp)) )
            cat(TARGET,x)
        end
        ferase(tmp)
    end

    def_quit(arg,env,0)



static function cat(fspec,x)
local ch
    set CHANNEL(ch) to (fspec) additive
    set CHANNEL(ch) on
    ?? x
    set CHANNEL(ch) to
    set CHANNEL(ch) off

