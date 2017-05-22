

***************************************************************************************
function main(sessionid,sckstr,*)
local data,x

    set alternate to log-wecho
    set alternate on

    ? {*}

    webapp.ffsocket(sckstr)

    webapp.script('CODE.webapp.frame.frameBorder="1";')
    webapp.script('CODE.frmaux.frame.style.display="block";')
    webapp.script('CODE.frmaux.frame.frameBorder="1";')
    frmaux.clear()
    //webapp.debug(.t.)

    webapp.innerhtml("display","WEcho")

    webapp.script('CODE.formdata("INIT");')
    x:=webapp.waitmessage("formdata.INIT",@data)
    frmaux.writeln(x)

    ? x:=webapp.echo("proba")
    
    echotest()

    sleep(2000)
    
    


***************************************************************************************
static function echotest()
local snd,rsp
local n

    for n:=-30 to 10

        snd:=replicate(a"ABCDEFGHIJKLMNOPQRSTUWVXYZabcdefghijklmnopqrstuwvxyz",2000)
        //snd::=left(65535+n)
        snd::=left(126+n)
    
        memowrit( "log-snd",snd )

        websocket.writemessage( webapp.ffsocket(), a"CODE.echo('XX')"::strtran(a'XX',snd) )
        rsp:=websocket.readmessage( webapp.ffsocket() )

        memowrit( "log-rsp",rsp )
        
        if( !snd==rsp )
            ? "eltér", n
        else
            ? "ok   ", n
        end
        
    next
    
***************************************************************************************
    
    
