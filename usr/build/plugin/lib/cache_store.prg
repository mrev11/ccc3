
#include "pluginenv.ch"

function cache_store(arg,env)

local sum,dir,trg

    if( empty(BUILD_CACHE) )
        BUILD_CACHE:=HOME+"/.cache/build"
        dirmake(BUILD_CACHE)
    end

    if( !empty(SHASUM) .and. file(TARGET) .and. direxist(BUILD_CACHE) )
        // store object in cache
        sum:=SHASUM
        dir:=BUILD_CACHE+"/"+sum[1..2]
        dirmake(dir)
        trg:=dir+"/"+sum
        filecopy(TARGET,trg)
    end
    ?
    def_quit(arg,env,0)


