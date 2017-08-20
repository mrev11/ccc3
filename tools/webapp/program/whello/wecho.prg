

***************************************************************************************
function main(sessionid,sckstr,*)

    printlog()
    //set console off
    ? {*}
    webapp.demo.defaults()

    //ez nagyon megterheli a böngészőt
    //a timeoutok tesztelésére hasznos
    webapp.debug(.f.)

    echotest()


***************************************************************************************
static function echotest()

local data,n,k:=0

    data:=a"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    data+=data::lower
    data::=replicate(2000)

    webapp.innerhtml("display","WEcho")

    while( k<1000  )
        for n:=-29 to 20
            echo( (++k)::str::alltrim::str2bin + data::left(126+n) )
            ?? k
        next
        for n:=-29 to 20
            echo( (++k)::str::alltrim::str2bin + data::left( 65535+n) )
            ?? k
        next

        webapp.innerhtml("display","WEcho"+str(k))
    next

    sleep(1000)
    

***************************************************************************************
static function echo(snd)
local rsp

    memowrit( "log-snd",snd )
    websocket.writemessage( webapp.ffsocket(), a"CODE.echo('XX')"::strtran(a'XX',snd) )
    rsp:=websocket.readmessage( webapp.ffsocket() )

    if( rsp==NIL )
        ? "websocket closed"
        quit
    end
    memowrit( "log-rsp",rsp )

    if( snd==rsp )
        ? "egyezik  ", len(snd)
    else
        ? "eltér    ", len(snd)
        quit
    end


***************************************************************************************
    
    
