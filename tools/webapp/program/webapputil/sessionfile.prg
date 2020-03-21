
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


**************************************************************************************
function opensessionfile(doc) // megnyit egy sessiondirben levő dokumentumot
local url:='webapp/dnload/$SESSIONID/'+doc
    url::=strtran("$SESSIONID",webapp.session.id())
    webapp.script("window.open('$URL')"::strtran("$URL",url))


**************************************************************************************
function dnloadsessionfile(doc) //letölt egy sessiondirben levő dokumentumot
local url:='webapp/dnload/$SESSIONID/'+doc
local code:=<<CODE>>XCODE.dnloadlink.href="$URL";XCODE.dnloadlink.click();<<CODE>>
    url::=strtran("$SESSIONID",webapp.session.id())
    code::=strtran('$URL',url)
    webapp.script(code)


**************************************************************************************
function linksessionfile(id,doc,text:=doc) 

// Csinál egy linket az id elemben
// a link URL-je a doc-ra mutat (file a sessiondirben)
// a link szövege text

local link:="<a href='$URL' download target='_blank'>"+text+"</a>" //ez kell, ez HTML5
local url:='webapp/dnload/$SESSIONID/'+doc
    url::=strtran("$SESSIONID",webapp.session.id())
    link::=strtran("$URL",url)
    webapp.innerHTML(id,link)


**************************************************************************************
function sessionurl(fname)
//igy kell kepezni egy sessiondir-ben levo file URL-jet
    return "/webapp/dnload/"+webapp.session.id()+"/"+fname


**************************************************************************************
