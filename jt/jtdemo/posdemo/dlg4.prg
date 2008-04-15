
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

#include "demo.dlg"
 
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
local dlg:=demoNew(), pnl
    dlg:caption:="Dialog Demo 4" 

    pnl:=jtpanelNew()
    pnl:text:="Számlaszámok"
    pnl:icon:="images/blue.gif"
    pnl:layout:="vbox"
    pnl:additem( panel("Próba"          , "@R! 99999999-NNNNNNNN-99999999"))
    pnl:additem( panel("Próba szere"    , "@R! 99999999-NNNNNNNN-99999999"))
    pnl:additem( panel("Próba szerencse", "@R! 99999999-NNNNNNNN-99999999"))
    pnl:additem( panel("Próba szere"    , "@R! 99999999-NNNNNNNN-99999999"))
    dlg:tpane:additem(pnl)
 
    pnl:=jtpanelNew()
    pnl:text:="Összegek"
    pnl:icon:="images/red.gif"
    pnl:layout:="vbox"
    pnl:additem( panel("Próba"          , "@RN 999,999,999,999"))
    pnl:additem( panel("Próba szere"    , "@RN 999,999,999,999.99"))
    pnl:additem( panel("Próba szerencse", "@RN 999,999,999.999999"))
    dlg:tpane:additem(pnl)
 
    return dlg


******************************************************************************
static function label(x)
    return jtlabelNew(" "+padr(x,16)+": ")

******************************************************************************
static function get(p)
local w:=len(p)-at(" ",p) 
local g:=jtgetNew(0,1,0,w)
static cnt:=0
    g:picture:=p
    g:valid:=.t.
    g:name:="get"+alltrim(str( ++cnt ))  //kell valamilyen név!
    return g

******************************************************************************
static function panel(x,p)
local pn:=jtpanelNew()
    pn:layout:="hbox"
    pn:border:="null"
    pn:additem( label(x) )
    pn:additem( get(p) )
    return pn

******************************************************************************
 