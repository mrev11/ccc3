
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


#include "icons.ch"
 
****************************************************************************
function main()

    set printer to log-3
    set printer on


    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated")})
    
    ? jtencoding()
    jtencoding("UTF-8")
    
    msgloop( makedlg("TextArea Demo Prog")  )
    
    return NIL


****************************************************************************
function msgloop(dlg) 
local msg,txt
 
    dlg:show  

    while( NIL!=(msg:=dlg:getmessage) )

        if( msg=="x"  ) 
            memowrit("save.bak",dlg:var:tarea:varget)
            dlg:close

        elseif( msg=="choice"  ) 
            txt:=memoread(dlg:var:choice:selecteditem)
            dlg:var:tarea:varput(txt)

        elseif( msg=="wrap"  ) 
            dlg:var:tarea:linewrap:=dlg:var:wrap:varget
            dlg:var:tarea:changelinewrap

        end
    end

    return NIL
 

****************************************************************************
function makedlg( caption )

local dlg
local tbar, choice, x 
local dir, n
local tarea
local wrap

    dlg:=jtdialogNew(5,6,22,78) //üres dialog objektum
    dlg:name:="proba"
    dlg:layout:="vbox"
    dlg:caption:=caption

    //-------------------------------
    // toolbar
    //-------------------------------

    dlg:add(tbar:=jttoolbarNew())
    
    tbar:additem(wrap:=jtcheckNew("Linewrap"))

    wrap:varput(.t.)
    wrap:name:="wrap"
    wrap:valid:=.t.
    

    tbar:additem(jthglueNew()) 
 
    tbar:additem(choice:=jtcomboNew())
        choice:name:='choice'
        choice:tooltip:="Filé kiválasztás."
        choice:valid:=.t.
        dir:=directory("*.txt")
        for n:=1 to len(dir)
            choice:additem(dir[n][1])
        next
    
    tbar:additem(x:=jtpushNew())
        x:name:='x' 
        x:text:='Exit'
        x:icon:=ICON_EXIT 
        x:mnemonic:="X"
 
    //-------------------------------
    // textarea
    //-------------------------------

    dlg:add(tarea:=jttextareaNew())
    tarea:name:="tarea"
    //tarea:bottom:=6
    //tarea:right:=32
    //tarea:focusable:=.f.
    tarea:varput:=memoread(choice:choicelist[1])
    tarea:linewrap:=wrap:varget
    dlg:varinst("main3_demo_dialog")
    
    return dlg


****************************************************************************
