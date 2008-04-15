
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

#define MORGO "../images/morgo.jpeg"
 
******************************************************************************
function main()
    ? jtversion()
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})
    jtencoding("UTF-8")
    jtcheckversion("0.9.11")    
    msgloop( makedlg() )
    return NIL

******************************************************************************
static function msgloop(dlg)
    dlg:show
    while( NIL!=dlg:getmessage )
    end
    return NIL

******************************************************************************
static function makedlg()

local dlg:=jtdialogNew(4,16,20,80)
local pnl,mm,mi

    dlg:caption:="Change Panel Application" 
    dlg:layout:="vbox"
    
    mm:=dlg:add(jtmenuNew())
    mm:text:="Panelcsere"
    mi:=mm:additem(jtmenuitemNew())
    mi:text:="Első panel"
    mi:actionblock:={|d| d:var:proba:changeitem(panel1()), d:varinst("x1") }

    mi:=mm:additem(jtmenuitemNew())
    mi:text:="Második panel"
    mi:actionblock:={|d| d:var:proba:changeitem(panel2()), d:varinst("x2") }

    mi:=mm:additem(jtmenuitemNew())
    mi:text:="Lista"
    mi:actionblock:={|d| d:list, qout(d:var:attrnames) }
    
    dlg:add( panel1() )
    dlg:varinst("x1")
    
    return dlg


******************************************************************************
static function panel1()
local pnl:=jtpanelNew()
    pnl:layout:="hbox"
    pnl:name:="proba"
    pnl:text:="Külső panel (1)"
    pnl:additem(jtlabel("HOPP-1"))
    return pnl
    

******************************************************************************
static function panel2()

local pnl:=jtpanelNew()
local pnl1, pnl2, bar, push, get

    pnl:layout:="vbox"
    pnl:name:="proba"
    pnl:text:="Külső panel (2)"
 
    pnl:additem(jtlabel("HOPP-2"))

    pnl1:=pnl:additem(jtpanelNew()) 
    pnl1:layout:="vbox"
    pnl1:text:="Belső panel"
    pnl2:=pnl1:additem(jtpanelNew()) 
    pnl2:hscroll:=.t.
    pnl2:vscroll:=.t.
    pnl2:additem(jtimage(MORGO))
    
    bar:=pnl:additem(jttoolbarNew())
   
    get:=bar:additem(jtgetNew(0,0,0,25))
    get:name:="get1"
    get:picture:="@R! 99999999-NNNNNNNN-99999999"
    get:varput:="111111112222222233333333"
    get:actionblock({|d|qout(d:var:get1:varget)})

    get:=bar:additem(jtgetNew(0,0,0,12))
    get:name:="get2"
    get:picture:="@RN 999,999.99999"
    get:varput:=3.14159
    get:actionblock({|d|qout(d:var:get2:varget)})

    push:=bar:additem(jtpushNew())
    push:text:="Alert"
    push:icon:="images/middle.gif"
    push:actionblock({||alert("HOPP")})

    push:=bar:additem(jtpushNew())
    push:text:="Exit"
    push:icon:="images/exit.gif"
    push:actionblock({|d|d:close})
 
 
    return pnl
    
 
******************************************************************************
