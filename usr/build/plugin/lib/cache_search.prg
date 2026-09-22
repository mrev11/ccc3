

#include "fileio.ch"
#include "pluginenv.ch"

******************************************************************************************
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
            filecopy_time(trg,TARGET)
            ?? " (from cache)";?
            def_quit(arg,env,0)
        end
    end


******************************************************************************************
static function filecopy_time(fsource,ftarget) // specialis: nem orzi meg a fajl idot

local fd1, fd2
local buf, nr, nw
local nbyte:=0

    fd1:=fopen(fsource,FO_READ)
    if( fd1<0 )
        return 0
    end

    ferase(ftarget)
    fd2:=fcreate(ftarget)
    if( fd2<0 )
        fclose(fd1)
        return 0
    end

    buf:=replicate(x"00",4096)
    nr:=fread(fd1,@buf,len(buf))
    while( nr>0 )
        nbyte+=(nw:=fwrite(fd2,buf,nr))
        if( nw!=nr )
            exit
        end
        nr:=fread(fd1,@buf,len(buf))
    end

    fclose(fd1)
    fclose(fd2)

    return nbyte

******************************************************************************************
