
namespace webapp

//#define PRINT_MESSAGE

***************************************************************************************
function getmessage(data,timeout)  // @data

local sck:=webapp.ffsocket()
local msg,prs,dom,err

    if( 0==select({sck},,,timeout) )
        return ""
    end

    msg:=websocket.readmessage(sck)

    if( msg==NIL )
        return NIL  //kapcsolat megszakadt
    end

    if( empty(msg) )
        return ""   //close, ping, pong?
    end


    #ifdef PRINT_MESSAGE
        ? "---------------------------------------"
        ? msg
        ? "---------------------------------------"
    #endif
    
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


