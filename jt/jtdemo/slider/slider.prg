
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
    msgloop( makedlg() )

******************************************************************************
static function msgloop(dlg)
local msg
    dlg:show
    while( NIL!=(msg:=dlg:getmessage(1000)) )
        if(empty(msg))
            dlg:var:slider:changevalue(dlg:var:slider:value+1)
            dlg:var:label:changetext(str(dlg:var:slider:value))
        elseif(msg=="slider")
            ? ">",dlg:var:slider:varget
        end
    end

******************************************************************************
static function makedlg()

local dlg,slider,label

    dlg:=jtdialogNew(10,10,15,60)

    dlg:caption:="Slider Application" 
    dlg:layout:="vbox"

    label:=dlg:add(jtlabelNew())
    label:name:="label"
    

    slider:=dlg:add(jtsliderNew(1,1,3,50))
    slider:name:="slider"
    //slider:orientation:="v"
    //slider:inverted:=.t.
    slider:min:=0
    slider:max:=300
    slider:value:=20
    slider:minortick:=5
    slider:majortick:=60
    slider:painttick:=.t.
    slider:paintlabel:=.t.
    slider:valid:=.t.
   
    dlg:varinst("x")
    return dlg

******************************************************************************
 