
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

#include "table.ch"
 
******************************************************************************
function main()
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})
    jtcheckversion("0.9.11")    
    msgloop( makedlg() )
    return NIL

******************************************************************************
static function msgloop(dlg)
local msg
    dlg:show
    while( NIL!=(msg:=dlg:getmessage()) )
    end
    return NIL

******************************************************************************
static function makedlg()
local dlg:=jtdialogNew(4,16,24,96),pnl
    dlg:caption:="TabView 1.0"
    dlg:layout:="vbox"
    setmenu(dlg)
    pnl:=dlg:add(jtpanelNew())
    pnl:name:="panel"
    dlg:varinst("tabview0")
    return dlg

******************************************************************************
static function setmenu(dlg)
local m,mi

    m:=dlg:add(jtmenuNew())
    m:text:="File"
    m:mnemonic:="f"
 
    mi:=m:additem(jtmenuitemNew())
    mi:text:="Open"
    mi:mnemonic:="o"
    mi:accelerator:="ctrl O"
    mi:icon:="images/middle.gif"
    mi:actionblock:={|d|menuopen(d)}

    mi:=m:additem(jtmenuitemNew())
    mi:text:="Exit"
    mi:mnemonic:="x"
    mi:icon:="images/exit.gif"
    mi:actionblock:={|d|d:close}

    dlg:add(jtmenusepNew())

    m:=dlg:add(jtmenuNew())
    m:text:="Help"
    m:icon:="icons/16/help.png"
    m:mnemonic:="h"
 
    mi:=m:additem(jtmenuitemNew())
    mi:text:="About"
    mi:mnemonic:="b"
    mi:actionblock:={||alert("ComFirm (C) 2004")}
    
    return NIL

******************************************************************************
static function menuopen(dlg)

local ff,fc:=jtfilechooserNew(),ch

static wd
 
    fc:caption:="TabView"
    fc:text:="Open"
    fc:multiselect:=.f.
    fc:selectmode:="F" //csak filéket

    if( wd==NIL )
        fc:workdir:=curdir()
    else
        fc:workdir:=wd
    end

    ff:=fc:addfilter(jtfilefilterNew())
    ff:description:="bt fájlok (*.bt)"
    ff:addpattern("*.bt")
    ff:regexdir(jtfilepattern("*"))
 
    if( !empty(ch:=fc:getchoice) )
        setpanel(dlg,ch[1])
        wd:=fpath(ch[1])
    end
 
    return NIL

******************************************************************************
static function fpath(name)   // path
local slashpos:=max(rat("/",name),rat("\",name))
    if( 0<slashpos )
        return left(name,slashpos-1)
    end
    return ""
 
******************************************************************************
static function setpanel(dlg,fn)

local pnl:=jtpanelNew(0,0,64,80),brw,bar

    pnl:layout:="vbox"
    pnl:name:="panel"

    brw:=mkbrowse(fn) 
    if( brw!=NIL )
        pnl:additem(brw)
        bar:=pnl:additem(brw:mktoolbar)
        bar:additem(jthglueNew())
        bar:additem(jtlabel(fn))
        bar:additem(jthglueNew())
        dlg:var:panel:changeitem(pnl)
        dlg:varinst("tabview1") 
        sleep(200) //!?
        brw:pagefirst
    else
        dlg:var:panel:changeitem(pnl)
        dlg:varinst("tabview0") 
    end

    return NIL

******************************************************************************
static function mkbrowse(fn)

static tb

local br,n,col,typ,nam,wid,dec,blk,pic 

    if( tb!=NIL )
        tabClose(tb)
    end

    tb:=tabResource(fn) 

    if( tb==NIL .or. !tabOpen(tb,,{||.f.}) )
        alert("A filé foglalt!")
        return NIL
    end
    
    br:=jtbrowsetableNew() 
    br:table:=tb

    br:addcolumn("#recno",{||tabPosition(tb)},"@RN 9,999,999")
    
    for n:=1 to tabFCount(tb)
        col:=tabColumn(tb)[n]
        typ:=col[COL_TYPE]
        nam:=col[COL_NAME] 
        wid:=col[COL_WIDTH] 
        dec:=col[COL_DEC] 
        blk:=mkblock(tb,n)
        
        if( typ=="C" )
            pic:="@C "+replicate("X",wid)
            blk:=mkblocklat2(tb,n)
 
        elseif( typ=="N" )
            pic:=replicate("9",wid)
            if( dec>0 )
                pic+="."+replicate("9",dec)
                pic:=right(pic,wid)
            end
            pic:="@RN "+pic
 
        elseif( typ=="D" )
            pic:="@D"

        elseif( typ=="L" )
            pic:="@L"
        end
    
        br:addcolumn(nam,blk,pic)
    next

    br:maxrow:=20
    br:name:="br"

    return br

******************************************************************************
static function mkblock(tb,n)
    return {||tabEvalColumn(tb,n)}

static function mkblocklat2(tb,n)
    return {||tabEvalColumn(tb,n)}

******************************************************************************
 