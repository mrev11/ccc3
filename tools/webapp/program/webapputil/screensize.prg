
namespace webapp

*********************************************************************************************
function screen_size()
local code:=<<CODE>>
    XCODE.echo( "<screen.size>"+screen.width+","+screen.height+"</screen.size>"  );
<<CODE>>
local msg,data,size
    webapp.script(code)
    msg:=webapp.getmessage(@data)
    size:=data:gettext::split
    size[1]::=val
    size[2]::=val
    return size

*********************************************************************************************
function screen_width()
local code:=<<CODE>>
    XCODE.echo( "<screen.width>"+screen.width+"</screen.width>"  );
<<CODE>>
local msg,data
    webapp.script(code)
    msg:=webapp.getmessage(@data)
    return data:gettext::val

*********************************************************************************************
function screen_height()
local code:=<<CODE>>
    XCODE.echo( "<screen.height>"+screen.height+"</screen.height>"  );
<<CODE>>
local msg,data
    webapp.script(code)
    msg:=webapp.getmessage(@data)
    return data:gettext::val


*********************************************************************************************
function window_size()
local code:=<<CODE>>
    XCODE.echo( "<window.size>"+window.innerWidth.toString()+","+window.innerHeight.toString()+"</window.size>"  );
<<CODE>>
local msg,data,size
    webapp.script(code)
    msg:=webapp.getmessage(@data)
    size:=data:gettext::split
    size[1]::=val
    size[2]::=val
    return size

*********************************************************************************************
function window_width()
local code:=<<CODE>>
    XCODE.echo( "<window.width>"+window.innerWidth+"</window.width>"  );
<<CODE>>
local msg,data
    webapp.script(code)
    msg:=webapp.getmessage(@data)
    return data:gettext::val

*********************************************************************************************
function window_height()
local code:=<<CODE>>
    XCODE.echo( "<window.height>"+window.innerHeight+"</window.height>"  );
<<CODE>>
local msg,data
    webapp.script(code)
    msg:=webapp.getmessage(@data)
    return data:gettext::val

*********************************************************************************************
