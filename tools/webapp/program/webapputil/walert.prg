
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

//hagyományos Clipper alert megfelelője
//kivéve, hogy nincs escape lehetőség

namespace webapp

***************************************************************************************
function alert(text,alternatives)

local a:=<<ALERT>><div id="alert"><p><h3>TEXT</h3><p>ALTERNATIVES</div><<ALERT>>
local b:=<<BUTTON>><input type="button" value="@VALUE" id="@ID" onclick="XCODE.onclick_formdata(this.id)"/> <<BUTTON>>
local c:="",n,msg,data,choice

    if( empty(alternatives) )
        alternatives:={"Ok"}
    end
   
    for n:=1 to len(alternatives)
        c+=b
        c::=strtran("@VALUE",alternatives[n])
        c::=strtran("@ID","alert"+n::str::alltrim)
    next

    a::=strtran("ALTERNATIVES",c)
    a::=strtran("TEXT",text)
    a::=webapp.jsstring()

    webapp.script("XCODE.openalert("+a+")")
    webapp.focus("alert1")
    
    while( NIL!=(msg:=webapp.getmessage(@data)) )
        if( msg::startswith("formdata.") )
            choice:=data:source[6..]::val  //alertN -> N
            exit
        end
    end

    webapp.script("XCODE.closealert();")

    
    return choice // 1,2,3...  (nincs esc==0 lehetőség)

***************************************************************************************

