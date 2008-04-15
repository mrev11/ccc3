
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

static htmlroot:="file:///"+curdir()+"/texmenu/html/"
 
****************************************************************************
function main()

    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated")})
    
    alert("Ehhez előzőleg el kell indítani xs-t!")
    
    msgloop( makedlg("Executive Demó")  )
    
    return NIL


****************************************************************************
function msgloop(dlg) 
local msg,url
local ip,port,ssl
 
    dlg:show  

    while( NIL!=(msg:=dlg:getmessage) )

        if( msg=="x"  ) 
            dlg:close

        elseif( msg=="ok"  ) 
            ? dlg:var:htmlarea:varget
 
        elseif( msg=="htmlarea"  ) 
            ? url:=dlg:var:htmlarea:varget
            url:=split(url,"/")
            asize(url,5)
 
            if( url[2]=="jtconnect" )
                ip:=url[3]
                port:=val(url[4])
                ssl:=url[5]=="ssl" 
                jtconnect(ip,port,ssl)
            end
        end
    end

    return NIL
 

****************************************************************************
function makedlg( caption )

local dlg, tbar, x
local htmlarea

    dlg:=jtdialogNew(5,6,22,78) //üres dialog objektum
    dlg:name:="proba"
    dlg:layout:="vbox"
    dlg:caption:=caption

    //-------------------------------
    // toolbar
    //-------------------------------

    dlg:add(tbar:=jttoolbarNew())

    tbar:additem(jthglueNew()) 
 
    tbar:additem(x:=jtpushNew())
        x:name:='ok' 
        x:text:='Ok'
        x:icon:=ICON_EXEC
        x:mnemonic:="O"

    tbar:additem(x:=jtpushNew())
        x:name:='x' 
        x:text:='Exit'
        x:icon:=ICON_EXIT 
        x:mnemonic:="X"
 
    //-------------------------------
    // htmlarea
    //-------------------------------

    dlg:add(htmlarea:=jthtmlareaNew())
    htmlarea:bottom:=32
    htmlarea:name:="htmlarea"
    htmlarea:followlink:=.f.
    htmlarea:valid:=.t.
    htmlarea:varput(htmlroot+"texmenu.html")

    dlg:varinst("executive")
    
    return dlg

****************************************************************************
 