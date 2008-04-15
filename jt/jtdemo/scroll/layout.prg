
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

//#define VBOX
#define HBOX
//#define FIX

#define BIG         //nagy kép
//#define SMALL       //kis kép

#define MORGO       "../images/morgo.jpeg"
#define MIDDLE      "../images/middle.gif"
 

****************************************************************************
function main()
    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    msgloop( makedlg("Layout Demó") )
    return NIL

****************************************************************************
function msgloop(dlg)    
    dlg:show 
    while( NIL!=dlg:getmessage ) 
    end
    return NIL

****************************************************************************
function makedlg( caption)

local dlg
 
    dlg:=jtdialogNew(4,10,21,80) //üres dialog objektum
    dlg:name:="proba"
    dlg:layout:="fix"
    dlg:caption:=caption
 
    #ifdef HBOX 
        addhpanel(dlg,1,2,14,50) 
        addhpanel(dlg,1,52,6,64)
    #endif

    #ifdef VBOX 
        addvpanel(dlg,1,2,14,50) 
        addvpanel(dlg,1,52,6,64)
    #endif

    #ifdef FIX 
        addfpanel(dlg,1,2,14,50) 
        addfpanel(dlg,1,52,6,64)
    #endif
    
    dlg:add(jtlabelNew(15,0,15,64,replicate("X",64)))
    dlg:add(jtlabelNew( 0,0, 0,64,replicate("X",64)))
 
    return dlg


****************************************************************************
static function addhpanel(dlg,t,l,b,r)   //hor: {hglue|image|hglue}

local panel:=jtpanelNew(t,l,b,r)    

    dlg:add(panel) 
    panel:vscroll:=.t.
    panel:hscroll:=.t.
    panel:layout:="hbox"
    panel:text:="hbox"

    panel:additem(jthglueNew())

    #ifdef BIG
        panel:additem(jtimage(MORGO))
    #endif
    #ifdef SMALL
        panel:additem(jtimage(MIDDLE))
    #endif

    panel:additem(jthglueNew())
    return NIL

****************************************************************************
static function addvpanel(dlg,t,l,b,r) //ver: {vglue|image|vglue}

local panel:=jtpanelNew(t,l,b,r)    

    dlg:add(panel) 
    panel:vscroll:=.t.
    panel:hscroll:=.t.
    panel:layout:="vbox"
    panel:text:="vbox"

    panel:additem(jtvglueNew())

    #ifdef BIG
        panel:additem(jtimage(MORGO))
    #endif
    #ifdef SMALL
        panel:additem(jtimage(MIDDLE))
    #endif

    panel:additem(jtvglueNew())
    return NIL


****************************************************************************
static function addfpanel(dlg,t,l,b,r)

local panel:=jtpanelNew(t,l,b,r), lab

    dlg:add(panel) 
    //panel:vscroll:=.t.  //fix pozícionálásnál hatástalan
    //panel:hscroll:=.t.  //fix pozícionálásnál hatástalan 
    panel:layout:="fix"
    panel:text:="fix"

    //lab a panel teljes területét megkapja:
    panel:additem( lab:=jtlabelNew(0,0,b-t,r-l,"TEXT") ) 

    #ifdef BIG
        lab:image:=memoread(MORGO,.t.)
    #endif

    #ifdef SMALL
        lab:image:=memoread(MIDDLE,.t.)
    #endif

    return NIL
 
****************************************************************************
 


 