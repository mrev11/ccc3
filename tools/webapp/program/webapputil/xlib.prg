

namespace webapp

***************************************************************************************
function xlib.isdefined(idobj)
local code:=<<CODE>>
CODE.xlib.isdefined('$IDOBJ');
<<CODE>> 
local data
    code::=strtran("$IDOBJ",idobj)
    webapp.script(code)
    webapp.waitmessage("isdefined",@data)
    return "true"==data:gettext


***************************************************************************************
function xlib.save_innerHTML(idobj,idelem)
local code:=<<CODE>> 
CODE.xlib['$IDOBJ']=CODE.webapp.document.getElementById('$IDELEM').innerHTML; 
<<CODE>>
    code::=strtran("$IDOBJ",idobj)
    code::=strtran("$IDELEM",idelem)
    webapp.script(code)

***************************************************************************************
function xlib.save_outerHTML(idobj,idelem)
local code:=<<CODE>> 
CODE.xlib['$IDOBJ']=CODE.webapp.document.getElementById('$IDELEM').outerHTML; 
<<CODE>>
    code::=strtran("$IDOBJ",idobj)
    code::=strtran("$IDELEM",idelem)
    webapp.script(code)


***************************************************************************************
function xlib.set_innerHTML(idelem,idobj)
local code:=<<CODE>> 
CODE.webapp.document.getElementById('$IDELEM').innerHTML=CODE.xlib['$IDOBJ']; 
<<CODE>>
    code::=strtran("$IDOBJ",idobj)
    code::=strtran("$IDELEM",idelem)
    webapp.script(code)


***************************************************************************************
