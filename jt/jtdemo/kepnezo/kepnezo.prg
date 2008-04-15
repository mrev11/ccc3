
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

//Egyszerű képmegjelenítő,
//ami a terminál filérendszerében található
//jpeg, gif, png képeket tudja megmutatni.


******************************************************************************
function main()
    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
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
local dlg:=jtdialogNew(4,16,24,96) 
local htm,bar,get,but

    dlg:caption:="Képnéző Demó" 
    dlg:layout:="vbox"
   
    htm:=dlg:add(jthtmlareaNew()) 
    //htm:bottom:=32
    htm:name:="htm"

    bar:=dlg:add(jttoolbarNew())  
    //bar:layout:="hbox"

    get:=bar:additem(jtgetNew())
    get:name:="fdesc"
    get:focusable:=.f.

    bar:additem(jthglueNew())
 
    but:=bar:additem(jtpushNew())
    but:text:="Kép választás"
    but:icon:="icons/22/fileopen.png"  
    but:tooltip:="Kiválasztja az új megjelenítendő képet"
    but:actionblock:={||valaszt(dlg)}
    
    dlg:varinst("kepnezo")
    
    
    return dlg


******************************************************************************
static function valaszt(dlg)

static wd

local ch,ff,fc:=jtfilechooserNew()

    if( wd!=NIL )
        fc:workdir:=wd
    end

    fc:caption:="Képválasztó"
    fc:text:="Megjelenít"
    fc:multiselect:=.f.
    fc:selectmode:="F" //csak filéket

    ff:=fc:addfilter(jtfilefilterNew())
    ff:description:="JPEG fájlok (*.jpeg *.jpg)"
    ff:addpattern("*.jpeg")
    ff:addpattern("*.jpg")
    ff:regexdir(jtfilepattern("*"))
 
    ff:=fc:addfilter(jtfilefilterNew())
    ff:description:="GIF fájlok (*.gif)"
    ff:addpattern("*.gif")
    ff:regexdir(jtfilepattern("*"))
 
    ff:=fc:addfilter(jtfilefilterNew())
    ff:description:="PNG fájlok (*.png)"
    ff:addpattern("*.png")
    ff:regexdir(jtfilepattern("*"))

    ff:=fc:addfilter(jtfilefilterNew())
    ff:description:="Minden fájl"
    ff:addpattern("*")
    ff:regexdir(jtfilepattern("*"))
    
    if( !empty(ch:=fc:getchoice) )
        wd:=fpath(ch[1])
        dlg:var:htm:varput('<html><img src="'+fspec2url(ch[1])+'"></html>')
        dlg:var:fdesc:varput(ch[1])
    end
 
    return NIL

******************************************************************************
static function fspec2url(fspec)   // abszolút fspec --> URL
    fspec:=strtran(fspec,"\","/")
    if( !left(fspec,1)=="/" )
        fspec:="/"+fspec
    end
    return "file:"+fspec

******************************************************************************
static function fpath(name)   // path
local slashpos:=max(rat("/",name),rat("\",name))
    if( 0<slashpos )
        return left(name,slashpos-1)
    end
    return ""

******************************************************************************
 