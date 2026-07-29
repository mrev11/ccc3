


#include "pluginenv.ch"



function def_quit(arg,env,code)

    if( code>0 )
        memowrit("error","")
        frename(OUT,ERR)
        ? memoread(ERR)
    end

    ?? "----------------------------------------------------------------";?

    ferase(OUT)

    errorlevel(code)
    quit


