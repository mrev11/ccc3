
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
    ? jtversion()
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})
    jtencoding("UTF-8")
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
local dlg:=jtdialogNew(10,10,25,70),lab,pnl
    dlg:layout:="fix"
    dlg:caption:="HTML-Label Demó" 

    dlg:add(pnl:=jtpanelNew())
    pnl:top:=0
    pnl:left:=0
    pnl:bottom:=10
    pnl:right:=5
    pnl:text:="10x5"

    dlg:add(lab:=jtlabelNew())
    lab:top:=0
    lab:left:=10
    lab:bottom:=10
    lab:right:=50
 
    //lab:valign:="top"  //hol legyen a szöveg a komponens belsejében?
    //lab:valign:="center" //hol legyen a szöveg a komponens belsejében? 
    lab:valign:="bottom" //hol legyen a szöveg a komponens belsejében? 
    
    lab:varput( memoread("text.html") )
    
    return dlg

******************************************************************************
 