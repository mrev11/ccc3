
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


static clip

******************************************************************************
function main()
    ? jtversion()
    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    //quitblock({||qout(argv(0)+" terminated"+endofline())})
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
        end
    end

******************************************************************************
static function makedlg()

local dlg:=jtdialogNew(),t,b,l
local bar,push,get

    dlg:caption:="Tree Edit Application" 
    dlg:layout:="vbox"

    //dlg:add(t:=jttreeNew(10,10,20,40))
    dlg:add(t:=jttreeNew())

    t:name:="demotree"
    t:text:="Próba Szerencse"
    t:valid:=.t.
    //t:enabled:=.f.


    t:addnode(b:=jttreenodeNew("Első ág"))
    b:addnode(l:=jttreenodeNew("Levél A"))
    b:addnode(l:=jttreenodeNew("Levél B"))
    b:addnode(l:=jttreenodeNew("Levél C"))

    t:addnode(b:=jttreenodeNew("Második ág"))
    b:addnode(b:=jttreenodeNew("Harmadik ág"))
    b:addnode(l:=jttreenodeNew("Levél D")) 
    b:addnode(l:=jttreenodeNew("Levél E"))
    l:icon:="images/middle.gif"
    l:tooltip:="Ezen van spéci ikon és tooltip."


    dlg:add(bar:=jttoolbarNew())

    push:=bar:additem(jtpushNew("Add"))
    push:actionblock:={||add(dlg)}

    push:=bar:additem(jtpushNew("Del"))
    push:actionblock:={||del(dlg)}

    push:=bar:additem(jtpushNew("Cut"))
    push:actionblock:={||cut(dlg)}

    push:=bar:additem(jtpushNew("Copy"))
    push:actionblock:={||copy(dlg)}

    push:=bar:additem(jtpushNew("Paste Last"))
    push:actionblock:={||paste_last(dlg)}

    push:=bar:additem(jtpushNew("Paste Before"))
    push:actionblock:={||paste_before(dlg)}


    get:=bar:additem(jtgetNew())
    get:actionblock:={||changetext(dlg)}
    get:name:="get"

    dlg:varinst("demotree")
    
    return dlg

******************************************************************************
static function add(dlg)

local key:=dlg:var:demotree:varget  //a kiválasztott node kulcsa
local node,parent

    if( !empty(key) )
        node:=jttreenodeNew()
        dlg:var:demotree:changeaddnode(key,node)

        parent:=dlg:var:demotree:findnode(key)
        if( NIL!=parent .and. len(parent:nodelist)==1 )
            dlg:var:demotree:varput(node:key) //kiválasztja (ha első)
        end
    end

******************************************************************************
static function del(dlg)
local key:=dlg:var:demotree:varget
    if( !empty(key) )
        dlg:var:demotree:changedelnode(key)
        dlg:var:demotree:varput("") //megszűnt a kiválasztás
    end

******************************************************************************
static function cut(dlg) //del+clip
local key:=dlg:var:demotree:varget
    if( !empty(key) )
        clip:=dlg:var:demotree:changedelnode(key)
        if( clip!=NIL )
            clip:=clip:clone
        end
        dlg:var:demotree:varput("") //megszűnt a kiválasztás
    end

******************************************************************************
static function copy(dlg)
local key:=dlg:var:demotree:varget
    if( !empty(key) )
        clip:=dlg:var:demotree:findnode(key)
        if( clip!=NIL )
            clip:=clip:clone
        end
    end

******************************************************************************
static function paste_last(dlg)
local key:=dlg:var:demotree:varget
    if( !empty(key) .and. !empty(clip) )
        dlg:var:demotree:changeaddnode(key,clip:clone) //utolsó gyerek
    end

******************************************************************************
static function paste_before(dlg)
local key:=dlg:var:demotree:varget
    if( !empty(key) .and. !empty(clip) )
        dlg:var:demotree:changeinsnode(key,clip:clone) //bal szomszéd
    end

******************************************************************************
static function changetext(dlg)
local key:=dlg:var:demotree:varget
local txt:=dlg:var:get:varget
    if( !empty(key) .and. !empty(txt) )
        dlg:var:demotree:changetext(key,txt)
    end

******************************************************************************

 