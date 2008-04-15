
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

//többszörösen egymásba skatulyázott panelek

#include "icons.ch"
 
****************************************************************************
function main()

    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated")})
    
    msgloop( makedlg("Panel Demó") )
    
    return NIL


****************************************************************************
function msgloop(dlg)    
local msg
 
    dlg:show 

    while( NIL!=(msg:=dlg:getmessage) ) 
        
        if( msg=="x"  ) //x button
            //dlg:exit //kliép a terminál 
            quit
 
        elseif( msg=="ok"  ) //ok button
            dlg:close

        elseif( msg=="menuitem1"  ) 
            ? "alert:", alert("Van, aki forrón szereti!",{"Válasz-1","Válasz-22","Válasz-333"})

        elseif( msg=="menuitem3"  ) 
            msgloop( makedlg( dlg:caption+"@" ) )

        end
    end

    return NIL
 

****************************************************************************
function makedlg( caption)

local dlg

local group,n,c
local tbar, ok, x
local panel,panel1,panel2,panel3,panel4
local label
local status
 
    dlg:=jtdialogNew(5,6,22,78) //üres dialog objektum
    dlg:name:="proba"
    dlg:layout:="vbox"
    dlg:caption:=caption

    // menu

    dlg:add( pulldown1() ) //egy pulldown menü 
    dlg:add( menuitem() )  //önálló menü (nem jó az elhelyezése)

    //-------------------------
    // toolbar
    //-------------------------
 
    dlg:add(tbar:=jttoolbarNew())

    tbar:additem(jthglueNew())

    tbar:additem(ok:=jtpushNew())
        ok:name:='ok' 
        ok:text:='OK'
        ok:tooltip:="Helptext for OK button"
        ok:icon:=ICON_MIDDLE 

    tbar:additem(x:=jtpushNew())
        x:name:='x' 
        x:text:='Exit'
        x:icon:=ICON_EXIT 
        x:mnemonic:="X"
 
    //-------------------------
    // panel
    //-------------------------
 
    dlg:add(panel:=jtpanelNew())
    //panel:vscroll:=.t.
    //panel:hscroll:=.t.
    panel:layout:="hbox"
    panel:text:="hbox panel"

    panel:additem( panel1:=jtpanelNew() )
    panel1:layout:="vbox"
    panel1:text:="vbox panel1"
    panel1:vscroll:=.t.
    labelsto(panel1)
 
    panel:additem( panel2:=jtpanelNew() )
    panel2:layout:="vbox"
    panel2:text:="vbox panel2"

    panel2:additem( panel3:=jtpanelNew() )
    panel3:vscroll:=.t.
    panel3:hscroll:=.t.
    panel3:layout:="hbox"
    panel3:text:="hbox panel3"
    labelsto(panel3)

    panel2:additem( panel4:=jtpanelNew() )
    panel4:layout:="hbox"
    panel4:text:="hbox panel4"
    labelsto(panel4)

    //-------------------------
    // status
    //-------------------------
 
    dlg:add(status:=jtpanelNew())
    status:additem( jtlabelNew(,,,,"Hopp") )
    status:additem( jthglueNew() )
    status:additem( jtlabelNew(,,,,"QWERTY") )
    status:additem( jthglueNew() )
    status:additem( jtlabelNew(,,,,"Próba szerencse!") )

    dlg:varinst("main5_demo_dialog")
    
    return dlg


****************************************************************************
function pulldown1()

local m, mi

    m:=jtmenuNew()
    m:text:="Egy pulldown menü"

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Próba szerencse 1 (alert)"
               mi:name:="menuitem1"

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Próba szerencse 2"
               mi:name:="menuitem2"
               mi:enabled:=.f.

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Próba szerencse 3 (newdialog)"
               mi:name:="menuitem3"
    
    m:additem( jtmenusepNew())
    
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Próba szerencse 4"
               mi:name:="menuitem4"
 
    return m

****************************************************************************
function menuitem()
local mi:=jtmenuitemNew() 
    mi:text:="Önálló menüpont!"
    mi:name:="menuitem5"
    mi:tooltip:="Önálló menüpont, nem jó az elhelyezése!" 
    mi:actionblock:={||alert("Próba szerencse!")}
    return mi

****************************************************************************
function labelsto(panel)
local label

    panel:additem(label:=jtlabelNew()); label:icon:=ICON_STEAM
    panel:additem(label:=jtlabelNew()); label:icon:=ICON_EXIT
    panel:additem(label:=jtlabelNew()); label:icon:=ICON_MIDDLE
    panel:additem(label:=jtlabelNew()); label:icon:=ICON_COLORIZE
    panel:additem(label:=jtlabelNew()); label:icon:=ICON_CONFIGURE
    panel:additem(label:=jtlabelNew()); label:icon:=ICON_EXEC
    
    return NIL

****************************************************************************
 