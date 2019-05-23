
namespace webapp

***************************************************************************************
function ffsocket(sckstr)
static sck
    if(sckstr!=NIL)
        sck:=socketNew(sckstr::val)
    end
    return sck

***************************************************************************************
function script(x)
    if( !x::empty )
        websocket.writemessage(webapp.ffsocket(),x)
    end


***************************************************************************************
function visible(flag)
local code:=<<code>>XCODE.webapp.x.style.display="$DISP";<<code>>
    code::=strtran("$DISP",if(flag,"block","none"))
    webapp.script(code)


***************************************************************************************
function debug(flag:=.t.)
    if( flag )
        script( "XCODE.debug=true;")
    else
        script( "XCODE.debug=false;")
    end


***************************************************************************************
function setattrib(id,attr,value)
local code:="XCODE.document.x.getElementById('ID').ATTR=VALUE; "
    code::=strtran("ID",id)
    code::=strtran("ATTR",attr)
    code::=strtran("VALUE",value::webapp.jsstring)
    script(code)


***************************************************************************************
function setmethod(id,meth,value)
local code:="XCODE.document.x.getElementById('ID').METH=function(){VALUE}; "
    code::=strtran("ID",id)
    code::=strtran("METH",meth)
    code::=strtran("VALUE",value)
    webapp.script(code)


***************************************************************************************
function focus(id)
local code:="XCODE.document.x.getElementById('ID').focus(); "
    code::=strtran("ID",id)
    script(code)

***************************************************************************************
function click(id)
local code:="XCODE.document.x.getElementById('ID').click(); "
    code::=strtran("ID",id)
    script(code)

***************************************************************************************
function innerhtml(id,txt)
local code:="XCODE.document.x.getElementById('ID').innerHTML=TXT; "
    code::=strtran("ID",id)
    code::=strtran("TXT",txt::webapp.jsstring)
    script(code)


***************************************************************************************
function style(id,prop,txt)
local code:="XCODE.document.x.getElementById('ID').style.PROP=TXT; "
    code::=strtran("ID",id)
    code::=strtran("PROP",prop)
    code::=strtran("TXT",txt::webapp.jsstring)
    script(code)

//setattrib speciális esete 

***************************************************************************************
function echo(x)  //kuldje vissza a stringet
local code:=<<code>>XCODE.echo('$STRING');<<code>>
    code::=strtran("$STRING",x)
    webapp.script(code)


***************************************************************************************
function formdata(x) //kuldjon formdatat x-bol
local code:=<<code>>XCODE.formdata('$CTRLID');<<code>>
    code::=strtran("$CTRLID",x)
    webapp.script(code)
                 

***************************************************************************************
function isdefined(symbol)
local code:=<<CODE>>
    XCODE.send("<isdefined>"+($SYMBOL!=undefined).toString()+"</isdefined>")
<<CODE>>
local data
    webapp.script(code::strtran("$SYMBOL",symbol))
    webapp.waitmessage("isdefined",@data)
    return "true"==data:gettext


***************************************************************************************
function loadscript(url)
    webapp.script( 'XCODE.loadscript("$URL")'::strtran("$URL",url))


***************************************************************************************
function loadstyle(url)
    webapp.script('XCODE.loadstyle("$URL")'::strtran("$URL",url))

***************************************************************************************
function unloadstyle(url)
    webapp.script('XCODE.unloadstyle("$URL")'::strtran("$URL",url))


***************************************************************************************
function getpassword(srcid,salt1,salt2)
local code:=<<CODE>>XCODE.getpassword("$PASSWD","$SALT1","$SALT2")<<CODE>>
local data
    code::=strtran('$PASSWD',srcid)
    if(salt1==NIL)
        code::=strtran(',"$SALT1"','')
    else
        code::=strtran('$SALT1',salt1)
    end
    if(salt2==NIL)
        code::=strtran(',"$SALT2"','')
    else
        code::=strtran('$SALT2',salt2)
    end
    webapp.script(code)
    webapp.waitmessage("password",@data)
    return data:gettext


***************************************************************************************
function getpwstrength(srcid)
local code:=<<CODE>>XCODE.getpwstrength("$PASSWD")<<CODE>>
local data
    code::=strtran('$PASSWD',srcid)
    webapp.script(code)
    webapp.waitmessage("pwstrength",@data)
    return data:gettext::val // number   


***************************************************************************************
function selectedindex(ctrlid,idx)

//lekerdezi/beallitja a bongeszoben egy select selectedIdndex attributumat
//a formdata a selected option szovegevel dolgozik, ami nem mindig eleg

local code, data

    if( idx==NIL )
        //lekerdezes
        code:=<<CODE>>XCODE.send("<selectedindex>"+XCODE.document.x.getElementById('$CTRLID').selectedIndex.toString()+"</selectedindex>")<<CODE>>
        webapp.script(code::strtran("$CTRLID",ctrlid))
        webapp.waitmessage("selectedindex",@data)
        return data:gettext::val
    else
        //beallitas
        code:="XCODE.document.x.getElementById('$CTRLID').selectedIndex=$IDX"
        code::=strtran("$CTRLID",ctrlid)
        code::=strtran("$IDX",idx::str::alltrim)
        webapp.script(code)
        return NIL
    end


***************************************************************************************
