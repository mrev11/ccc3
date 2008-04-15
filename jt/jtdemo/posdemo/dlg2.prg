
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
local dlg:=jtdialogNew(), pnl

    dlg:caption:="Dialog Demo 2" 
    dlg:layout:="vbox"

    pnl:=jtpanelNew()
    pnl:text:="Számlaszámok"
    pnl:layout:="vbox"
    //pnl:vscroll:=.t.
    //pnl:hscroll:=.t.
    pnl:additem( panel("Próba"          , "@RN 99999999"))
    pnl:additem( panel("Próba dátum"    , "@RDX 9999-99-99"))
    pnl:additem( panel("Próba szerencse", "@R! 99999999-NNNNNNNN-99999999"))
    pnl:additem( panel("Próba szere"    , "@R! 99999999-NNNNNNNN-99999999"))

    dlg:add(pnl)
 
    return dlg

******************************************************************************
static function label(x)
    return jtlabelNew(" "+padl(x,16)+": ")

******************************************************************************
static function get(p)
local w:=len(p)-at(" ",p) 
local g:=jtgetNew(0,1,0,w)
    g:picture:=p
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
 