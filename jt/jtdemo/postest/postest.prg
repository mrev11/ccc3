
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

//Példa jtpanelek méretezésére

#define MORGO "../images/morgo.jpeg"
 

******************************************************************************
function main()
    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})
    msgloop( makedlg() )
    return NIL

******************************************************************************
static function msgloop(dlg)
local msg
    dlg:show
    while( NIL!=(dlg:getmessage)  )
    end
    return NIL


******************************************************************************
static function makedlg()
local dlg,tpn,pnl
    
    dlg:=jtdialogNew(4,4,16,80)
    dlg:caption:="PosTest Application" 
    dlg:layout:="vbox"
 
    dlg:add(tpn:=jttabpaneNew()) 
    tpn:additem(makepnl1("Első példa"))
    tpn:additem(makepnl2("Második példa"))
    tpn:additem(makepnl3("Harmadik példa"))
    tpn:additem(makepnl4("Negyedik példa"))
    tpn:additem(makepnl5("Ötödik példa"))
    
    return dlg
 


******************************************************************************
static function makepnl1(txt)

local  dlg,pnl,lab 

    dlg:=jtpanelNew()
    dlg:layout:="vbox"
    dlg:text:=txt

    dlg:additem( pnl:=jtpanelNew() )
    pnl:text:="Egy panel"
    
    dlg:additem( lab:=jtlabelNew() )
    lab:text:="A lábléc szövege."
    lab:alignx:="center"
    
    //Ha csak egy label van alul, az fix magasságú. 
    //label helyett lehet jtget, az sem magas
    //label helyett lehet jtpush, az sem magas 
    //label helyett lehet jttextarea, az a panelhez hasonlóan magas
    
    return dlg
    

******************************************************************************
static function makepnl2(txt)

local  dlg,pnl,pnl2

    dlg:=jtpanelNew()
    dlg:text:=txt
    dlg:layout:="vbox"

    dlg:additem(pnl:=jtpanelNew())
    pnl:text:="Egy panel"
    
    dlg:additem(pnl2:=jtpanelNew())  //még egy panel
    pnl2:layout:="hbox"
    pnl2:additem( jtlabelNew("Próba szerencse.") )
    pnl2:additem( jthglueNew() )
    pnl2:additem( jtlabelNew("Van, aki forrón szereti.") )
    
    
    //A két panel egyforma magas.
    //A panelek pozícionálása a szokásos koordinátákkal hatástalan, 
    //mivel az őket tartalmazó komponenes (dlg) layoutja vbox.
    //A koordinátás pozícionálás csak a fix layoutnál működne.
    
    //Kivéve, 
    //hogy panel a getPreferredSize kérdésre nem mond kisebb 
    //méretet, mint ami a koordinátás pozícionálásból adódik,
    //lásd a következő példát ...
    
    return dlg
    

******************************************************************************
static function makepnl3(txt)

local  dlg,pnl,pnl2

    dlg:=jtpanelNew()
    dlg:text:=txt
    dlg:layout:="vbox"

    dlg:additem(pnl:=jtpanelNew())
    pnl:text:="Egy panel"
    pnl:bottom:=100

    //Ez a példa csak abban különbözik az előzőtől,
    //hogy a felső panel 100 nagynak mondja magát a 
    //getPreferredSize kérdésre.
    
    //Tanulságos megnézni, hogyan jelenik meg az alábbi kép:

    pnl:additem(jtimage(MORGO))
    pnl:vscroll:=.t.
    
    dlg:additem(pnl2:=jtpanelNew())  //még egy panel
    pnl2:layout:="hbox"
    pnl2:additem( jtlabelNew("Próba szerencse.") )
    pnl2:additem( jthglueNew() )
    pnl2:additem( jtlabelNew("Van, aki forrón szereti.") )
  
    
    return dlg
    

******************************************************************************
static function makepnl4(txt)

local  dlg,pnl,pnl2

    dlg:=jtpanelNew()
    dlg:text:=txt
    dlg:layout:="vbox"

    dlg:additem(pnl:=jtpanelNew())
    pnl:text:="Egy panel"
    pnl:bottom:=100

    //Az előző példa korrekt képmegjelenítéssel.
 
    pnl:additem( pnl2:=jtpanelNew() )    
    pnl2:additem(jtimage(MORGO))
    pnl2:border:="empty"
    pnl2:vscroll:=.t.
    
    dlg:additem(pnl2:=jtpanelNew())  //még egy panel
    pnl2:layout:="hbox"
    pnl2:additem( jtlabelNew("Próba szerencse.") )
    pnl2:additem( jthglueNew() )
    pnl2:additem( jtlabelNew("Van, aki forrón szereti.") )
  
    
    return dlg
    
 
******************************************************************************
static function makepnl5(txt)

local dlg,pnl,pnl2 

    dlg:=jtpanelNew()
    dlg:text:=txt
    dlg:layout:="vbox"

    dlg:additem(pnl:=jtpanelNew())
    pnl:text:="Egy panel"
    pnl:bottom:=8                   //magas panel

    dlg:additem(pnl:=jtpanelNew())
    pnl:text:="Még egy panel"
    pnl:bottom:=16                  //kétszer olyan magas panel
                                    
    dlg:additem(pnl2:=jtpanelNew()) //még egy panel
    pnl2:layout:="hbox"
    pnl2:additem( jtlabelNew("Próba szerencse.") )
    pnl2:additem( jthglueNew() )
    pnl2:additem( jtlabelNew("Van, aki forrón szereti.") )
    
    return dlg
    
 
******************************************************************************
