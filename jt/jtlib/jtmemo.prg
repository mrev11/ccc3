
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

//compatibility

******************************************************************************
function jtmemoedit(t,l,b,r,text,editable)

local dlg:=jtdialogNew(t,l,b,r)
local txt,bar,but,msg

    dlg:layout:="vbox"

    dlg:add(bar:=jttoolbarNew())

    bar:additem(jthglueNew())

    bar:additem(but:=jtpushNew()) 
        but:name:="ok" 
        but:text:="Ok" 
        but:icon:="images/middle.gif"

    bar:additem(but:=jtpushNew()) 
        but:name:="esc" 
        but:text:="Esc"
        but:mnemonic:="ESCAPE" //Alt-Esc
        but:icon:="images/exit.gif"
 

    dlg:add(txt:=jttextareaNew())
    txt:name:="txt"
    txt:bottom:=32
    txt:focusable:=if(editable==NIL,.t.,editable)
    txt:text:=text
    
    
    dlg:show
    
    while( NIL!=(msg:=dlg:getmessage) )

        if( msg=="ok" )
            text:=txt:varget
            dlg:close

        elseif( msg=="esc" ) 
            text:=NIL
            dlg:close
        end
    end
    
    return text
    
****************************************************************************
 
