
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

******************************************************************************
function main()

    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})
    jtencoding("UTF-8")
    
    msgloop( makedlg() )
    return NIL

******************************************************************************
static function msgloop(dlg)
local msg
    dlg:show
    while( NIL!=(msg:=dlg:getmessage)  )
        if( msg=="esc" )
            dlg:close

        elseif( msg=="tpane" )
            alert( "kiválasztva:"+str(dlg:var:tpane:varget) )

        elseif( msg=="b1" )
            //dlg:var:tpane:select(1)
            dlg:var:tpane:varput(1) //ugyanaz

        elseif( msg=="b2" )
            dlg:var:tpane:select(2)
           
        end
    end
    return NIL

******************************************************************************
static function makedlg()
local dlg,tpane,tbar,p,b

    dlg:=jtdialogNew(4,16,24,96) 
    dlg:caption:="TabPane Demó" 
    dlg:layout:="vbox"

    tpane:=dlg:add(jttabpaneNew())
    tpane:name:="tpane"
    tpane:valid:=.t.
    //tpane:placement:="b"
 
    p:=tpane:additem(jtpanelNew())
    p:name:="p1"
    p:text:="Első panel"
    p:tooltip:="Első panel tooltipje"
    p:mnemonic:="E"
    p:additem(jticon(ICON_STEAM))
    p:additem(pd1())
    p:bottom:=32

    p:=tpane:additem( jtpanelNew() )
    p:name:="p2"
    p:text:="Második panel"
    p:tooltip:="Második panel tooltipje"
    p:mnemonic:="M"
    p:additem(jticon(ICON_STEAM))
    p:additem(jticon(ICON_STEAM))
    p:additem(pd2())
 
    tbar:=dlg:add(jttoolbarNew())
 
    b:=tbar:additem(jtpushNew())
    b:name:="b1"
    b:text:="Első"
    b:tooltip:="Kiválasztja az első panelt."

    b:=tbar:additem(jtpushNew())
    b:name:="b2"
    b:text:="Második"
    b:tooltip:="Kiválasztja a második panelt."

    tbar:additem( jthglueNew() )

    b:=tbar:additem(jtpushNew())
    b:name:="esc"
    b:text:="Kilép"
    b:tooltip:="Program vége."
    b:icon:=ICON_EXIT 
        
    dlg:varinst("tpane")    
       
    return dlg


******************************************************************************
static function pd1()
local p,m

    p:=jtmenuNew()
    p:text:="Próba szerencse"    
    p:name:="pd1"
    p:mnemonic:="P"

    m:=p:additem(jtmenuitemNew())
    m:text:="Próba szerencse 1"
    m:name:="pd11"

    m:=p:additem(jtmenuitemNew())
    m:text:="Próba szerencse 2"
    m:name:="pd12"

    m:=p:additem(jtmenuitemNew())
    m:text:="Próba szerencse 3"
    m:name:="pd13"
    m:accelerator:="ctrl alt A"
    m:actionblock:={||alert("Próba szerencse 3")}

    return p

******************************************************************************
static function pd2()
local p,m

    p:=jtmenuNew()
    p:text:="Van aki forrón"    
    p:name:="pd2"
    p:mnemonic:="V"

    m:=p:additem(jtmenuitemNew())
    m:text:="Van aki forrón 1"
    m:name:="pd21"
    m:accelerator:="ctrl shift A"
    m:actionblock:={||alert("Van aki forrón 1")}

    m:=p:additem(jtmenuitemNew())
    m:text:="Van aki forrón 2"
    m:name:="pd22"

    m:=p:additem(jtmenuitemNew())
    m:text:="Van aki forrón 3"
    m:name:="pd23"

    return p

******************************************************************************
