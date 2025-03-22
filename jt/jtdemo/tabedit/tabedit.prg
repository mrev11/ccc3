
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
#include "table.szamla.tdh"
#include "icons.ch"
 
****************************************************************************
function main()

    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated")})
    
    SZAMLA:open //:=OPEN_EXCLUSIVE
    SZAMLA:control:="szamla"

    msgloop( makedlg("Számla BROWSE") )


****************************************************************************
function msgloop(dlg)

local msg

    dlg:show  
    dlg:var:szamla:pagefirst
 
    while( NIL!=(msg:=dlg:getmessage) ) 
    
        //ezek actionblockokban is lehetnének
        
        if( msg=="x"  ) //x button
            quit
 
        elseif( msg=="ok"  ) //ok button
            dlg:close

        elseif( msg=="search"  ) 

            SZAMLA:seek(dlg:var:search:varget)
            dlg:var:szamla:pagecurrent
        end
    end

 
****************************************************************************
function makedlg(caption)

local dlg
local tbar,ok,x
local jtb:=mkbrowse()
local status,label,search
 
    dlg:=jtdialogNew(4,8,20,80) //üres dialog objektum
    dlg:name:="proba"
    dlg:layout:="vbox"
    dlg:caption:=caption+" "+dlg:dialogid 

    // menu

    dlg:add( pulldown1(dlg) ) //egy pulldown menü 
 
    // toolbar

    tbar:=dlg:add(jtb:mktoolbar)
    tbar:additem(jthglueNew())

    ok:=tbar:additem(jtpushNew())
    ok:name:='ok' 
    ok:text:='OK'
    ok:tooltip:="Helptext for OK button"
    ok:icon:=ICON_MIDDLE 
    ok:mnemonic:="O"
 
    x:=tbar:additem(jtpushNew())
    x:name:='x' 
    x:text:='Exit'
    x:tooltip:="Helptext for Exit button"
    x:icon:=ICON_EXIT 
    x:escape:=.t.  //nem kell ellenőrizni a kitöltést
    x:mnemonic:="X"

    // table

    dlg:add(jtb)

    // status line (toolbar/panel)

    //dlg:add( status:=jtpanelNew() )
    dlg:add( status:=jttoolbarNew() )
    status:additem( label:=jtlabelNew() )
                    label:name:="label"
                    label:text:="Próba szerencse: 2007.04.10" 

    status:additem( jthglueNew() )

    status:additem( search:=jtgetNew(0,0,0,25) )
                    search:name:="search"
                    search:picture:="@R! 99999999-NNNNNNNN-99999999"
                    search:tooltip:=search:picture 
                    search:valid:=.t.

    status:additem( jthglueNew() )

    dlg:varinst("tabedit_demo_dialog")

    return dlg


****************************************************************************
static function mkbrowse()
    
local jtb:=jtbrowsetableNew()

    jtb:table:=SZAMLA:table

    jtb:addcolumn("#recno",{||SZAMLA:position()},"@RN 9,999,999")
    jtb:addcolumn("Számlaszám",{||SZAMLA_SZAMLASZAM},"@R! 99999999-NNNNNNNN-99999999")
    jtb:addcolumn("Kód",{||SZAMLA_SZAMLAKOD},3)
    jtb:addcolumn("Dev",{||SZAMLA_DEVNEM},3)


    //readonly
    //jtb:addcolumn("Név",{||SZAMLA_NEV},30)

    //editál, automatikusan ment, de OPEN_EXCLUSIVE kell neki
    //jtb:addcolumn("Név",tabBlock(SZAMLA:table,"nev"),30):editable:=.t. //editálható blokk

    //editál, automatikusan lockol
    jtb:addcolumn("Név",tabAutoBlock(SZAMLA:table,"nev"),30):editable:=.t. //editálható blokk


    jtb:addcolumn("Egyenleg",{||SZAMLA_EGYENLEG},"@RN 999,999,999,999.99")
    jtb:addcolumn("Túl",tabAutoBlock(SZAMLA:table,"tulmenflag"),"@L" ):editable:=.t.
    jtb:addcolumn("Kivdat",{||SZAMLA_KIVDATUM},"@RD")
 
    jtb:maxrow:=10             
    jtb:name:="szamla"
    jtb:tooltip:="Táblaeditáló demó alkalmazás"
    
    return jtb

 
****************************************************************************
function pulldown1(dlg)

local m, mi

    m:=jtmenuNew()
    m:text:="Egy pulldown menü"
    m:tooltip:="Tooltip a pulldown menühöz."

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Elindít egy új dialogboxot" 
               mi:name:="menuitem3"
               mi:tooltip:="Elindít egy új dialogboxot."
               mi:actionblock({||msgloop(makedlg("Számla BROWSE"))})
    
    m:additem( jtmenusepNew())

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Lista" 
               mi:name:="menuitem7"
               mi:tooltip:="Listázza a kiválasztott rekordokat."
               mi:actionblock:={||prnrec(dlg)}

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Edit" 
               mi:name:="menuitem8"
               mi:tooltip:="Editálja a kiválasztott rekordot."
               mi:actionblock:={||editrec(dlg)}
 
    return m
    
****************************************************************************
static function tabAutoBlock(table,fld)

//Ez a gyakorlatban nem megfelelő
//(mert nincs hibakezelés, nem törődik más lockokkal, stb.),
//de érzékelteti a megoldási lehetőségeket,
//egyébként ezt nem tartom követendő útnak.

local blk:=tabBlock(table,fld)
    return {|x|if(x==NIL,eval(blk),autolock(table,blk,x))}
    
static function autolock(table,blk,x)
    tabRLock(table)
    ? "record locked", tabPosition(table)
    ? eval(blk), "<--", x
    eval(blk,x)
    tabUnLock(table)
    ? "record unlocked", tabPosition(table)


****************************************************************************
static function prnrec(dlg)

//Itt az a fő tanulság,
//hogyan lehet megtalálni a kiválasztott rekordokat.

local brw:=dlg:var:szamla
//local sel:=brw:selectedindices, n
local sel:=brw:varget, n //ugyanaz

    ? "-------------------------------------------------"
    ? "current page ", brw:row2pos
    ? "selected rows", sel 

    for n:=1 to len(sel)
        //ciklus a kiválasztott sorokra
        if( !brw:restpos(sel[n]) )
            //nem lehet rossz
        else
            ? SZAMLA:position, SZAMLA_SZAMLASZAM, SZAMLA_EGYENLEG, SZAMLA_NEV
        end
    next

****************************************************************************
static function editrec(dlg)

local brw:=dlg:var:szamla
local sel:=brw:selectedindices

    if( len(sel)!=1 )
        alert("Ki kell választani egy rekordot")
    elseif( !brw:restpos(sel[1]) )
        alert("Hibás pozícionálás") //nem lehet
    else
        if( szladlg() )
            brw:pagereload
        end
    end

****************************************************************************

 