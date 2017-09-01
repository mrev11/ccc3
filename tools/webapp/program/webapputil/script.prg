
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
