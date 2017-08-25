

namespace webapp

***************************************************************************************
function xlib.isdefined(idobj)
local code:=<<CODE>>
XCODE.xlib.isdefined('$IDOBJ');
<<CODE>> 
local data
    code::=strtran("$IDOBJ",idobj)
    webapp.script(code)
    webapp.waitmessage("isdefined",@data)
    return "true"==data:gettext


***************************************************************************************
function xlib.save_innerHTML(idobj,idelem)
local code:=<<CODE>> 
XCODE.xlib['$IDOBJ']=XCODE.document.x.getElementById('$IDELEM').innerHTML; 
<<CODE>>
    code::=strtran("$IDOBJ",idobj)
    code::=strtran("$IDELEM",idelem)
    webapp.script(code)

***************************************************************************************
function xlib.save_outerHTML(idobj,idelem)
local code:=<<CODE>> 
XCODE.xlib['$IDOBJ']=XCODE.document.x.getElementById('$IDELEM').outerHTML; 
<<CODE>>
    code::=strtran("$IDOBJ",idobj)
    code::=strtran("$IDELEM",idelem)
    webapp.script(code)


***************************************************************************************
function xlib.set_innerHTML(idelem,idobj)
local code:=<<CODE>> 
XCODE.document.x.getElementById('$IDELEM').innerHTML=XCODE.xlib['$IDOBJ']; 
<<CODE>>
    code::=strtran("$IDOBJ",idobj)
    code::=strtran("$IDELEM",idelem)
    webapp.script(code)


***************************************************************************************
