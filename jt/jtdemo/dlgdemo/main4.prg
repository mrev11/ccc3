
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

//szerver oldalról átküldött jpeg megjelenítése

#include "icons.ch"
 

****************************************************************************
function main()
 
    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated")})
 
    msgloop( makedlg("Image Demó") )
    
    return NIL
 

****************************************************************************
function msgloop(dlg)    
local msg
 
    dlg:show 

    while( NIL!=(msg:=dlg:getmessage) ) 

        if( msg=="x"  ) 
            //dlg:exit //kliép a terminál 
            quit
 
        elseif( msg=="ok"  )
            dlg:close

        elseif( msg=="new"  ) 
            msgloop( makedlg( dlg:caption+"@" ) )
 
        end
    end

    return NIL


****************************************************************************
function makedlg(caption)

local dlg
local tbar, okbut, xbut, newbut
local panel, label
 
    dlg:=jtdialogNew(5,6,22,78) //üres dialog objektum
    dlg:name:="proba"
    dlg:layout:="vbox"
    dlg:caption:=caption

    //--------------------------
    // toolbar
    //--------------------------

    dlg:add(tbar:=jttoolbarNew())

    tbar:additem(okbut:=jtpushNew())
        okbut:name:='ok' 
        okbut:text:='OK'
        okbut:tooltip:="Helptext for OK button"
        okbut:icon:=ICON_MIDDLE 

    tbar:additem(newbut:=jtpushNew())
        newbut:name:='new' 
        newbut:text:='New'
        newbut:tooltip:="Helptext for New button"
        newbut:icon:=ICON_NETWORK 
 
    tbar:additem(xbut:=jtpushNew())
        xbut:name:='x' 
        xbut:text:='Exit'
        xbut:tooltip:="Helptext for Exit button"
        xbut:icon:=ICON_EXIT
        xbut:mnemonic:="X"
 
    //--------------------------
    // panel
    //--------------------------
    
    dlg:add( panel:=jtpanelNew() )
    panel:layout:="vbox"
    panel:text:="vbox layout"
    panel:vscroll:=.t.
    panel:hscroll:=.t.
    
    panel:additem(label:=jtlabelNew())
    label:image:=memoread(MORGO,.t.) //binárisan átküldött image

    dlg:varinst("main4_demo_dialog")
    
    return dlg
    
****************************************************************************
