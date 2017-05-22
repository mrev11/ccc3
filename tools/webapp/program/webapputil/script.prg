
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
function setattrib(id,attr,value)
local code:="CODE.webapp.document.getElementById('ID').ATTR=VALUE; "
    code::=strtran("ID",id)
    code::=strtran("ATTR",attr)
    code::=strtran("VALUE",value::webapp.jsstring)
    script(code)


***************************************************************************************
function setmethod(id,meth,value)
local code:="CODE.webapp.document.getElementById('ID').METH=function(){VALUE}; "
    code::=strtran("ID",id)
    code::=strtran("METH",meth)
    code::=strtran("VALUE",value)
    webapp.script(code)


***************************************************************************************
function focus(id)
local code:="CODE.webapp.document.getElementById('ID').focus(); "
    code::=strtran("ID",id)
    script(code)

***************************************************************************************
function innerhtml(id,txt)
local code:="CODE.webapp.document.getElementById('ID').innerHTML=TXT; "
    code::=strtran("ID",id)
    code::=strtran("TXT",txt::webapp.jsstring)
    script(code)


***************************************************************************************
function style(id,prop,txt)
local code:="CODE.webapp.document.getElementById('ID').style.PROP=TXT; "
    code::=strtran("ID",id)
    code::=strtran("PROP",prop)
    code::=strtran("TXT",txt::webapp.jsstring)
    script(code)

//setattrib speciális esete 

***************************************************************************************
function echo(x)
local data
    webapp.script("CODE.echo('<"+x+"/>')")
    webapp.waitmessage(x,@data)
    return data


***************************************************************************************
function debug(flag:=.t.)
    if( flag )
        script( "CODE.turndebug(true); ")
    else
        script( "CODE.turndebug(false); ")
    end


***************************************************************************************
