
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

#include "postest.pnl"

******************************************************************************
function main()
    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})
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
local dlg,bar,b,pnl,p
local text:=<<TEXT>>Próba szerencse
  Próba szerencse
    Próba szerencse
      Próba szerencse
<<TEXT>>

    dlg:=jtdialogNew()
    dlg:caption:="Postest Application" 
    dlg:layout:="vbox"
    
    bar:=dlg:add(jttoolbarNew())
    bar:additem(jtlabelNew("Szerencse:"))
    bar:additem(jtgetNew(0,1,0,10)):picture:="@RDXE"
    bar:additem(jtcomboNew()):additem("Őrült író szép")
    bar:additem(jtpushNew("Próba")):icon:="icons/22/exec.png"
    bar:additem(jtradioNew("Próba"))
    bar:additem(jtcheckNew("Próba"))
    bar:additem(jtgetNew(0,1,0,10))
    //bar:additem(jtgetNew())
    //bar:additem(jtprogbarNew()):name:="pb1"
    bar:additem(jtsliderNew(0,1,0,1)):name:="pb1"

    bar:=dlg:add(jttoolbarNew())
    bar:additem(  jtlabelNew(0,1,0,10)):text:="Szerencse:"
    bar:additem(    jtgetNew(0,1,0,10)):picture:="@RDXE"
    bar:additem(  jtcomboNew(0,1,0,10)):additem("Őrült író szép")
    bar:additem(b:=jtpushNew(0,1,0,10)):text:="Próba"; b:icon:="icons/22/exec.png"
    bar:additem(  jtradioNew(0,1,0,10)):text:="Próba"
    bar:additem(  jtcheckNew(0,1,0,10)):text:="Próba"
    bar:additem(    jtgetNew(0,1,0,10))
    bar:additem(jtprogbarNew(0,1,0,10)):name:="pb2"

    bar:=dlg:add(jttoolbarNew())
    bar:additem(  jtlabelNew(0,1,0,04)):text:="Szerencse:"
    bar:additem(    jtgetNew(0,1,0,04)):picture:="@RDXE"
    bar:additem(  jtcomboNew(0,1,0,04)):additem("Őrült író szép")
    bar:additem(   jtpushNew(0,1,0,04)):text:="Próba"
    bar:additem(  jtradioNew(0,1,0,04)):text:="Próba"
    bar:additem(  jtcheckNew(0,1,0,04)):text:="Próba"
    bar:additem(    jtgetNew())
    bar:additem(jtprogbarNew(0,1,0,04)):name:="pb3"

    bar:=dlg:add(jttoolbarNew())
    bar:additem(  jtlabelNew(0,1,0,20)):text:="Szerencse:"
    bar:additem(    jtgetNew(0,1,0,20)):picture:="@RDXE"
    bar:additem(  jtcomboNew(0,1,0,20)):additem("Őrült író szép")
    bar:additem(   jtpushNew(0,1,0,20)):text:="Próba"
    bar:additem(  jtradioNew(0,1,0,20)):text:="Próba"
    bar:additem(  jtcheckNew(0,1,0,20)):text:="Próba"
    bar:additem(    jtgetNew(0,1,0,20))
    bar:additem(jtprogbarNew(0,1,0,20)):name:="pb4"

    dlg:add(pnl:=postestNew())
    
    pnl:get1:varput("ABCDEFGH")
    pnl:get2:varput("ABCDEFGH")
    pnl:get3:varput("ABCDEFGH")
    pnl:get4:varput("ABCDEFGH")

    pnl:l1:additem("Próba szerencse")
    pnl:l1:additem("Vanaki forrón szereti")

    pnl:tpn:additem(p:=jtpanelNew("p1")); p:additem(jticon("images/middle.gif"))
    pnl:tpn:additem(p:=jtpanelNew("p2")); p:additem(jticon("images/network.gif"))
    
    pnl:txt:varput(text)
    pnl:htm:varput("<html>"+text)
    
    pnl:tbl:addcolumn("Column1",{||"xxxx"},"@RC XXXX")
    pnl:tbl:addcolumn("Column2",{||"xxxx"},"@RC XXXX")

    //pnl:w3:painttick:=.t.
    //pnl:w3:paintlabel:=.t.

    //h/vexpand true
    pnl:top:=0
    pnl:left:=0
    pnl:bottom:=0
    pnl:right:=0

    return dlg

******************************************************************************
 