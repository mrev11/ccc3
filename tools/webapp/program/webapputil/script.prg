
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
local code:=<<code>>CODE.webapp.frame.style.display="$DISP";<<code>>
    code::=strtran("$DISP",if(flag,"block","none"))
    webapp.script(code)


***************************************************************************************
function border(flag)
local code:=<<code>>CODE.webapp.frame.style.borderStyle="$BORDER";<<code>>
    if( valtype(flag)=="L" )
        code::=strtran("$BORDER",if(flag,"solid","none"))
    else
        code::=strtran("$BORDER",flag)
    end
    webapp.script(code)


***************************************************************************************
function size(w,h)
local code:=""
local codew:=<<code>>CODE.webapp.frame.style.width="$WIDTH";<<code>>
local codesw:=<<code>>CODE.webapp.frame.save_width="$WIDTH";<<code>>
local codeh:=<<code>>CODE.webapp.frame.style.height="$HEIGHT";<<code>>
local codesh:=<<code>>CODE.webapp.frame.save_height="$HEIGHT";<<code>>
    if(w!=NIL)
        if( valtype(w)=="N" )
            w::=str::alltrim+"px"
        end
        code+=codew::strtran("$WIDTH",w::any2str::alltrim)
        code+=codesw::strtran("$WIDTH",w::any2str::alltrim)
    end
    if(h!=NIL)
        if( valtype(h)=="N" )
            h::=str::alltrim+"px"
        end
        code+=codeh::strtran("$HEIGHT",h::any2str::alltrim)
        code+=codesh::strtran("$HEIGHT",h::any2str::alltrim)
    end
    webapp.script(code)


***************************************************************************************
function debug(flag:=.t.)
    if( flag )
        script( "CODE.turndebug(true); ")
    else
        script( "CODE.turndebug(false); ")
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
function click(id)
local code:="CODE.webapp.document.getElementById('ID').click(); "
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
function echo(x)  //kuldje vissza a stringet
local code:=<<code>>CODE.echo('$STRING');<<code>>
    code::=strtran("$STRING",x)
    webapp.script(code)


***************************************************************************************
function formdata(x) //kuldjon formdatat x-bol
local code:=<<code>>CODE.formdata('$CTRLID');<<code>>
    code::=strtran("$CTRLID",x)
    webapp.script(code)
                 

***************************************************************************************
