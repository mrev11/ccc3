
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

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
