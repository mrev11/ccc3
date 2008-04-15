
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
    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})
    msgloop( makedlg() )

******************************************************************************
static function msgloop(dlg)
local msg,key,node
    dlg:show
    while( NIL!=(msg:=dlg:getmessage) )
        if(msg=="demotree")
            key:=dlg:var:demotree:varget
            node:=dlg:var:demotree:findnode(key)
            ? "SELECTION:",key,if(node==NIL,"",node:text)
            sleep(1000)
        end
    end

******************************************************************************
static function makedlg()

local dlg:=jtdialogNew(),t,b,l
local bar,push

    dlg:caption:="Tree Application" 
    dlg:layout:="vbox"

    //dlg:add(t:=jttreeNew(10,10,20,40))
    dlg:add(t:=jttreeNew())

    t:name:="demotree"
    t:text:="Próba Szerencse"
    t:valid:=.t.
    //t:enabled:=.f.

    dlg:add(bar:=jttoolbarNew())
    
    mkpush(bar,t,t)

    t:addnode(b:=jttreenodeNew("Első ág"))              ; mkpush(bar,t,b)
    b:addnode(l:=jttreenodeNew("Levél A"))              ; mkpush(bar,t,l)
    b:addnode(l:=jttreenodeNew("Levél B"))              ; mkpush(bar,t,l)
    b:addnode(l:=jttreenodeNew("Levél C"))              ; mkpush(bar,t,l)

    t:addnode(b:=jttreenodeNew("Második ág"))           ; mkpush(bar,t,b)
    b:addnode(b:=jttreenodeNew("Harmadik ág"))          ; mkpush(bar,t,b)
    b:addnode(l:=jttreenodeNew("Levél D"))              ; mkpush(bar,t,l)
    b:addnode(l:=jttreenodeNew("Levél E"))              ; mkpush(bar,t,l)
    l:icon:="images/middle.gif"
    l:tooltip:="Ezen van spéci ikon és tooltip."
    
    dlg:varinst("demotree")
    
    return dlg

******************************************************************************
static function mkpush(bar,tree,node)
local push
    bar:additem(push:=jtpushNew(node:key))
    push:actionblock:={||tree:varput(node:key)}


******************************************************************************
 