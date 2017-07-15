
namespace webapp


***************************************************************************************
function logmessage(flag)
static st_flag:=.f.
    if( flag!=NIL )
        st_flag:=flag
    end
    return st_flag


***************************************************************************************
function getmessage(data,timeout)  // @data
local t0:=gettickcount(),t1,msg
    while(.t.)
        msg:=getmessage1(@data,timeout)


        if( msg==NIL )
            //megszakadt
            exit

        elseif( !empty(msg) )
            //kesz
            exit

        elseif( timeout==NIL )
            //vegtelen timeout, tovabb var

        else
            t1:=gettickcount()
            if( (t1-t0)<timeout )
                //maradt ido, tovabb var 
                timeout-=(t1-t0)
                t0:=t1
            else
                //lejart a timeout
                exit
            end
        end
    end
    return msg
    
//azert kellett ezt kozbeiktatni
//mert az edge-ben "technikai timeout"-ok keletkeznek
//1) olvashatot jelez a select, de nem jon semmi
//2) felpercenkent szolo pong-okat kuldozget
//
//korabban ez nem latszott, mert olyan message loopjaim voltak
//amik csendben fordultak egyet timeout eseten
//az ujabb page:loop azonban kilep timeoutra
//(hogy az alkalmazas tudjon jatszani a timeout-tal)


***************************************************************************************
function getmessage1(data,timeout)  // @data

local sck:=webapp.ffsocket()
local msg,prs,dom,err

    if( 0==select({sck},,,timeout) )
        return ""
    end

    msg:=websocket.readmessage(sck)


    if( logmessage() ) 
        ? "readmessage<<[",msg,"]"
    end 


    if( msg==NIL )
        return NIL  //kapcsolat megszakadt
    end

    if( empty(msg) )
        return ""   //close, ping, pong?
    end

    prs:=xmlparser2New()
    dom:=prs:parsestring(msg)
    
    if( dom:type=="formdata" )
        data:=webapp.formdataNew(dom)
        return dom:type+"."+data:source
    
    elseif( dom:type=="error" )
        err:=webapp.browsererrorNew()
        err:operation:="browser javascript eval"
        err:description:=dom:content[1]:gettext
        err:args:={dom:content[2]:gettext}
        break(err)

    elseif( dom:type=="warning" )
        ? "WARNING:", dom:content[1]:gettext, dom:content[2]:gettext
        data:=dom
        return dom:type  //C típus

    elseif( dom:type=="xxxx" )
        //egyéb specializált esetek
        data:=dom
        return dom:type  //C típus
    
    else
        //általános eset
        data:=dom
        return dom:type  //C típus
    end
    

***************************************************************************************
function waitmessage(msg,data,timeout)
local m,d
    while(.t.)
        m:=getmessage(@d,timeout)

        if( empty(m) )
            return m //megszakadt vagy timeout

        elseif( m==msg )
            data:=d
            return m //megjött a várt üzenet

        elseif( m=="error" )

        elseif( m=="warning" )
            //már ki van írva

        else
            ? "WAITMESSAGE:",m // valami jött, de nem az, amire várunk
        end
    end


***************************************************************************************
class browsererror(apperror)


***************************************************************************************


