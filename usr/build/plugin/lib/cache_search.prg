

#include "pluginenv.ch"



function cache_search(arg,env)

local ctx
local dep,n
local sum,dir,trg
local memo

    if( empty(BUILD_CACHE) )
        BUILD_CACHE:=HOME+"/.cache/build"
        dirmake(BUILD_CACHE)
    end

    if( direxist(BUILD_CACHE) .and. !empty(DEPEND) )
        ctx:=crypto_sha256_init()
        crypto_sha256_update(ctx,memo:=memoread(CMPOPT,.t.))
        if( empty(memo) )
            ? "WARNING", "cannot read dependency", CMPOPT
            return NIL
        end

        dep:=DEPEND
        for n:=1 to len(dep)
            if( !empty(dep[n]) )
                crypto_sha256_update(ctx,memo:=memoread(dep[n],.t.))
                if( empty(memo) )
                    ? "WARNING", "cannot read dependency", alltrim(str(n)), dep[n]
                    return NIL
                end
            end
        next
        sum:=crypto_sha256_final(ctx)
        sum::=bin2hex[1..64]
        SHASUM:=sum
        dir:=BUILD_CACHE+"/"+sum[1..2]
        trg:=dir+"/"+sum

        //? dir, ">>>", TARGET, DEPEND
        if( BUILD_USECACHE!="no" .and. file(trg) )
            // object exists in cache
            dirmake("object")
            filecopy(trg,TARGET)
            ?? " (from cache)";?
            def_quit(arg,env,0)
        end
    end
