
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


#include "icons.ch"

******************************************************************************
function main()
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})
    jtencoding("UTF-8")
    msgloop( makedlg() )

******************************************************************************
static function msgloop(dlg)
local msg
    dlg:show

    while( NIL!=(msg:=dlg:getmessage)  )
        if( "push"$msg )
            pushed(dlg,msg)
            
        elseif( msg=="tpane" )
            enablebut(dlg)
        end
    end

******************************************************************************
static function makedlg()
local dlg,tpane,cpanel,tbar,p,b

    dlg:=jtdialogNew(4,16,24,96) 
    dlg:caption:="TabPane Demó" 
    dlg:layout:="vbox"
    
    cpanel:=dlg:add(jtpanelNew())
    cpanel:name:="cpanel" //erre megy majd a changeitem

    //tpane:=dlg:add(jttabpaneNew())
    tpane:=cpanel:additem(jttabpaneNew())

    tpane:name:="tpane"
    tpane:valid:=.t.
    //tpane:placement:="b"
 
    p:=tpane:additem(panel("Első panel"))
    p:=tpane:additem(panel("Második panel"))
    p:=tpane:additem(panel("Harmadik panel"))
 
    tbar:=dlg:add(jttoolbarNew())

    b:=tbar:additem(jtpushNew())
    b:name:="break"
    b:text:="Berak"
    b:tooltip:="Berak egy új panelt a végére."
    b:icon:="images/green.gif"
    b:actionblock({||berak(dlg)})

    b:=tbar:additem(jtpushNew())
    b:name:="kivesz"
    b:text:="Kivesz"
    b:tooltip:="Kiveszi az aktív panelt."
    b:icon:="images/red.gif"
    b:actionblock({||kivesz(dlg)})
    b:enabled:=.f.

    tbar:additem(jthglueNew())

    b:=tbar:additem(jtpushNew())
    b:name:="esc"
    b:text:="Kilép"
    b:tooltip:="Program vége."
    b:icon:=ICON_EXIT 
    b:actionblock({||dlg:close})
        
    return dlg

******************************************************************************
static function panel(text)

static cnt:=0

local p:=jtpanelNew()
local x:="ABCDEFGH",let,i,n,g,b

local megj:=<<COMMENT>><html>
<H2>Megjegyzések</H2>
<font face="arial">
<ul>
<li>
  Minden jtelem leszármazottnak van örökölt changeitem metódusa,
  de a terminál csak a <b>névvel rendelkező jtpanel</b> kontrollok 
  changeitem metódusát dolgozza fel. Ezért van közbeiktatva a "cpanel", 
  hogy erre legyen alkalmazható a changeitem.

<li>  
  Tehát a changitem-mel panel egységekben lehet változtatni
  a dialogboxot: a panel belsejét teljes egészében kicseréli.
  Jelen esetben ez nem túl gazdaságos, mert lényegében az egész
  ablakot újraküldi. Ráadásul pislog, amit nem lehet kijavítani.

<li>
  Ha a tabpane paneljeiben menü van, akkor a kiválasztott fülekkel
  a menük is automatikusan cserélődnek. Kiderült, hogy a cpanel 
  közbeiktatása ront a dolgon, mert a megváltozott menü nem mindig 
  látszik azonnal, csak miután valami kiváltja az ablak újrarajzolását. 
  Az 1.1.06-os jterminal ezért a menük cseréjénél packolja az ablakot.

<li>  
  Az 1.1.06-os jterminal nem próbál nem létező fülhöz tartozó
  menüt beállítani a dialogban -> nem száll el -> egyszerűbb 
  az alkalmazást megírni, mert kevesebbet kell törődni a fülek
  számolgatásával.

<li>  
  A berak()-ban _varlist_ és _blklist_ törlése 
  újrainicializálja a kontrollok és  akcióblokkok
  hash tábláját.

<li>  
  A varinst módszer a jelen demóban nem alkalmazható,
  mert a dialogbox változatai nem ismertek, és nem volna célszerű
  minden változathoz egy statikus osztályt kreálni.
<li>  
  Ilyen terminált használsz: <b> JTVERSION </b>
</ul>
<<COMMENT>>

    cnt++
    text+=" ("+alltrim(str(cnt))+")"

    p:text:=text
    p:layout:="vbox"
    
    if( cnt<=1 )
        megj:=strtran(megj,"JTVERSION",jtversion())
        p:additem(jtlabelNew(megj))
    else
        p:additem(jtlabelNew(strtran('<html><H2>TEXT</H2><font face="arial">','TEXT',text)))

        g:=p:additem(jtgetNew(1,1,1,20))
        g:name:="get"+alltrim(str(cnt))
        g:text:=upper(g:name)
        g:alignx:="left"

        b:=p:additem(jtpushNew())
        b:name:="push"+alltrim(str(cnt))
        b:text:="Ezt nyomd meg"
    end

    n:=1+(cnt-1)%3
    for i:=1 to n
        let:=substr(x,i,1)
        p:additem( pulldown(strtran(text,")",let+")"),i) )
    end

    return p

******************************************************************************
static function pulldown(text,n)
local p,m,i

    p:=jtmenuNew()
    p:text:=text
    
    for i:=1 to n+1
        m:=p:additem(jtmenuitemNew())
        m:text:=text+" MenuItem"+"-"+alltrim(str(i))
        m:actionblock( mkblock(m:text) )
    next

    return p

******************************************************************************
static function mkblock(x)
    return {||jtalert(x)}

******************************************************************************
static function berak(dlg)

local cpanel:=dlg:getcontrolbyname("cpanel")
local tpane:=dlg:getcontrolbyname("tpane")

    tpane:additem( panel("Egy új panel") )
    tpane:varput(len(tpane:itemlist)) //fölhozza
    enablebut(dlg)
    cpanel:changeitem(cpanel)

    dlg:_blklist_:=NIL
    dlg:_varlist_:=NIL

******************************************************************************
static function kivesz(dlg)

local cpanel:=dlg:getcontrolbyname("cpanel")
local tpane:=dlg:getcontrolbyname("tpane")
local len:=len(tpane:itemlist)
local x:=tpane:varget //a kiválasztottat törli

    adel(tpane:itemlist,x) 
    asize(tpane:itemlist,--len)
    tpane:varput(1) //kiválasztja az elsőt
    enablebut(dlg)
    cpanel:changeitem(cpanel)
    
    //cpanel:changeitem
    //a legújabb verzióval ez is elég
    //de egyelőre menjen a régivel is

    dlg:_blklist_:=NIL
    dlg:_varlist_:=NIL

******************************************************************************
static function pushed(dlg,butnam)

local getnam:=strtran(butnam,"push","get")
local but:=dlg:getcontrolbyname(butnam)
local get:=dlg:getcontrolbyname(getnam)

    ? getnam, butnam, get:varget
    jtalert( getnam+" "+butnam+" "+get:varget)

******************************************************************************
static function enablebut(dlg)

local tpn:=dlg:getcontrolbyname("tpane")
local but:=dlg:getcontrolbyname("kivesz")

    if( but:enabled!=(tpn:varget!=1) )
        but:changeenabled:=(tpn:varget!=1)
    end

******************************************************************************
