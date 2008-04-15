
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

#define VBOX
//#define HBOX
//#define FIX

#define PANEL
//#define SMALL  //kis kép
#define BIG //nagy kép
 
#define MORGO       "../images/morgo.jpeg"
#define MIDDLE      "../images/middle.gif"

#include "proba.pnl"
    
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
    while( NIL!=(dlg:getmessage)  )
    end
    return NIL

******************************************************************************
static function makedlg()
local dlg,pnl,pnl1,lab 

    dlg:=jtdialogNew(10,10,24,50)

    //dlg:layout:="vbox"
    dlg:layout:="fix"

    //Ha a dlg layout-ja vbox (hbox, flow),
    //akkor a jtpanelNew-ban megadott koordináták hatástalanok,
    //mert a panelt a Jáva layout manager pozícionálja:
    //  vbox esetén az itemek egymás alá,
    //  hbox esetén az itemek egymás mellé,
    //  flow esetén balról jobbra, egymás mellé kerülnek.
    
    //Ha a dlg layout-ja fix, 
    //akkor érvényre jut az abszolút pozícionálás,
    //és a panel a megadott helyen lesz,
    //ilyenkor dlg-ben NINCS layout manager.

    dlg:caption:="Scroll Demó" 
    dlg:add(pnl:=jtPanelNew(2,5,10,30))

    #ifdef VBOX
        pnl:text:="vbox"
        pnl:layout:="vbox"
        pnl:vscroll:=.t.
        pnl:hscroll:=.t.
    #endif
    #ifdef HBOX
        pnl:text:="hbox"
        pnl:layout:="hbox"
        pnl:vscroll:=.t.
        pnl:hscroll:=.t.
    #endif
    #ifdef FIX
        pnl:text:="fix"
        pnl:layout:="fix"
    #endif

    //Ha a panel layout-ja hbox/vbox,
    //akkor a panelen belüli abszolút pozícionálás hatástalan,
    //mert a Jáva layout manager pozícionál,
    //ilyenkor a scrollbárok is működnek.
    
    //Ha a panel layout-ja fix,
    //akkor az abszolút pozícionálás működik,
    //de a scrollbarok nem, ui. a pnl:layout:="fix" utasítás 
    //Jáva értelemben kikapcsolja a panel layout managerét, 
    //így senki sem gondoskodik a scrollbárok elhelyezéséről.
 

#ifdef PANEL //Példa: scrollozható panelben fix panel 

    pnl:additem( probaNew() )
 
#else  // Példa: kép középre igazítva
 
    #ifdef VBOX
        pnl:additem(jtvglueNew())
        pnl1:=pnl:additem(jtpanelNew())
        pnl1:layout:="hbox"
        pnl1:border:="null"
        pnl1:additem(jthglueNew()) 
        pnl1:additem(lab:=jtlabelNew("Képfelirat"))
        pnl1:additem(jthglueNew()) 
        pnl:additem(jtvglueNew())
    #endif

    #ifdef HBOX
        //hbox-ban könnyebb középre rakni,
        //mert a lable vertikálisan magától
        //középre helyezkedik
    
        pnl:additem(jthglueNew())
        pnl:additem(lab:=jtlabelNew("Képfelirat"))
        pnl:additem(jthglueNew())
    #endif

    #ifdef FIX
        pnl:additem(lab:=jtlabelNew("Képfelirat"))

        //teljes terülte
        lab:top:=0
        lab:left:=0
        lab:bottom:=8
        lab:right:=25
    #endif
 
    #ifdef BIG
        lab:image:=memoread(MORGO,.t.)  //nagy kép
    #endif
    #ifdef SMALL
        lab:image:=memoread(MIDDLE,.t.) //kis kép
    #endif


#endif

    return dlg


******************************************************************************

 
