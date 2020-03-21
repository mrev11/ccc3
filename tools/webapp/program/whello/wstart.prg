
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

// webapp.spawn

***************************************************************************************
function main(session_id,session_sck,*)

local html:=<<HTML>>
<p> <h3>wstart</h3>
BUTTONS
<p> <div id="result"></div>
<<HTML>>

local button:=<<BUTTTON>>
<input type='button', id='BUTID' value='BUTNAM' onclick="XCODE.onclick_formdata(this.id)"/>  
<<BUTTTON>>


local msg, data
local dir:=directory("program/*.exe")
local prev,b,n

    printlog(.t.)
    webapp.logmessage(.t.)

    webapp.demo.defaults()
    
    asort(dir,,,{|x,y| x[1]<y[1] })

    for n:=1 to len(dir)
        b:=button
        b::=strtran("BUTID",dir[n][1])
        b::=strtran("BUTNAM",dir[n][1])
        b::=strtran(".exe","")
        if( dir[n][1][1]!=prev )
            prev:=dir[n][1][1]
            b:="<p>"+b
        end
        html::=strtran("BUTTONS",b+"BUTTONS")
    next
    html::=strtran("BUTTONS","")
    
    webapp.uploaddisplay(html) 
   
    // message loop
    while( NIL!=(msg:=webapp.getmessage(@data)) )
        if( msg::startswith("formdata.") )
            if( data:source=="wstart"  )
                ? "wstart reloaded"
                webapp.exec(data:source+".exe",*)
            else
                ? "start", data:source+".exe"
                webapp.spawn(data:source+".exe",*)
            end
        end
    end
    
    
***************************************************************************************
