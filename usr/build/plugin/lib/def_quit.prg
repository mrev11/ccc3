


#include "pluginenv.ch"



function def_quit(arg,env,code)
local memo

    if( code>0 )
        memowrit("error","")
        frename(OUT,ERR)
        ? memo:=memoread(ERR)
        if( memo::right(1)!=chr(10) )
            ?
        end
    end

    ?? "----------------------------------------------------------------";?

    ferase(OUT)

    errorlevel(code)
    quit


