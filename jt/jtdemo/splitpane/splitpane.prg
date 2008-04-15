
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

function main()
    jtencoding("UTF-8")
    msgloop( makedlg() )


function msgloop(dlg)
    dlg:show()
    while( NIL!=dlg:getmessage() )
    end


function makedlg()
local dlg, split, split1, pnl1, pnl2, txt

    dlg:=jtdialogNew(4,16,24,96) 
    dlg:caption("SplitPane Demó")
    dlg:layout:="vbox"
    
    split:=dlg:add(jtsplitpaneNew())
    split:divider:=20
    split:orientation:="ver" 
 
    split1:=split:setitem(1,jtsplitpaneNew())
    split1:divider:=50
    split1:orientation:="hor" 
 
    pnl1:=split1:setitem(1,jtpanelNew())
    pnl1:additem(jtimage("../images/morgo.jpeg"))
    pnl1:hscroll:=.t.
    pnl1:vscroll:=.t.

    pnl2:=split1:setitem(2,jtpanelNew()) //üresen marad
    pnl2:text:="HOPP"

    txt:=split:setitem(2,jttextareaNew())
    txt:text:=memoread("splitpane.prg")
    
    return dlg

