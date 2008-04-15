
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

static cccdir:=getenv("CCCDIR")
static htmldir
 
****************************************************************************
function main()

    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated")})
    
    msgloop( makedlg("HtmlArea Demó")  )
    
    return NIL


****************************************************************************
function msgloop(dlg) 
local msg,url
 
    dlg:show  

    while( NIL!=(msg:=dlg:getmessage) )

        if( msg=="x"  ) 
            dlg:close

        elseif( msg=="choice"  ) 
            url:=htmldir+dlg:var:choice:selecteditem
            dlg:var:htmlarea:varput(url)
 
        end
    end

    return NIL
 

****************************************************************************
function makedlg( caption )

local dlg, tbar, choice, x 
local dir, n
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
 
    tbar:additem(choice:=jtcomboNew())
        choice:name:='choice'
        choice:tooltip:="Filé kiválasztás."
        choice:valid:=.t.
        dir:=directory( cccdir+"/doc/html/*.html")
        for n:=1 to len(dir)
            choice:additem(dir[n][1])
        next
    
    tbar:additem(x:=jtpushNew())
        x:name:='x' 
        x:text:='Exit'
        x:icon:=ICON_EXIT 
        x:mnemonic:="X"
 
    //-------------------------------
    // htmlarea
    //-------------------------------

    dlg:add(htmlarea:=jthtmlareaNew())
    htmlarea:name:="htmlarea"
    htmlarea:bottom:=24
    
    htmldir:="file://"
    if( dirsep()=="\" )
        htmldir+="/"
    end
    htmldir+=cccdir
    htmldir+="/doc/html/" 

    htmlarea:varput:=htmldir+choice:choicelist[1]

    dlg:varinst("main3x_demo_dialog")
    
    return dlg

****************************************************************************
 