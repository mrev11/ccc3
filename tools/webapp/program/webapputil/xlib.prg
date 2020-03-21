
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
