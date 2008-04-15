
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
local dlg:=jtdialogNew(), pnl1, pnl

    dlg:caption:="GridLayout Application" 
    dlg:layout:="vbox"

    dlg:add(pnl1:=jtpanelNew())
    pnl1:border:="empty"
    pnl1:layout:="2,3"

    pnl1:additem( pnl:=jtpanelNew() ); pnl:text:="11" 
    pnl1:additem( pnl:=jtpanelNew() ); pnl:text:="12" 
    pnl1:additem( pnl:=jtpanelNew() ); pnl:text:="13" 
    pnl1:additem( pnl:=jtpanelNew() ); pnl:text:="21" 
    pnl1:additem( pnl:=jtpanelNew() ); pnl:text:="22" 
    pnl1:additem( pnl:=jtpanelNew() ); pnl:text:="23"

    return dlg

******************************************************************************
 