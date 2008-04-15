
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

//vbox layout
//toolbar lapozó gombokkal
//jtbrowse (szamla.bt) 
//search get a státusz sorban
//progressbar teszt
 
#include "table.ch"
#include "icons.ch"
 
static table

****************************************************************************
function main()

local dbfile:="szamla.bt" 

    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated")})
 
    table:=tabResource(dbfile) 
    
    if( table==NIL )
        alert("A filé foglalt!")
        quit
    end
    
    tabOpen(table,OPEN_EXCLUSIVE)
    //tabOpen(table)
    tabControl(table,"szamla")

    msgloop( makedlg("Demó BROWSE") )
    return NIL


****************************************************************************
function msgloop(dlg)

local msg

    dlg:show  
 
    while( NIL!=(msg:=dlg:getmessage) ) 
    
        //az alábbi funkciókat lehetne
        //a kontrollok blockjába is rakni
        
        if( msg=="x"  ) //x button
            quit
 
        elseif( msg=="ok"  ) //ok button
            dlg:close

        elseif( msg=="menuitem1"  ) 
            ? "alert:", alert("Van, aki forrón szereti!",{"Válasz-1","Válasz-22","Válasz-333"})

        elseif( msg=="menuitem3"  ) 
            msgloop( makedlg(dlg:caption+"@") )

        elseif( msg=="search"  ) 

            //név szerint kikeresi a kontrollt,
            //kiolvassa a tartalmát, azzal végrehajtja a seek-et,
            //és a kapott pozíció alatti lapot megjeleníti
        
            //tabSeek(table,dlg:getcontrol(msg):varget)
            //dlg:getcontrol("szamla"):pagecurrent 

            tabSeek(table,dlg:var:search:varget)   //újabb keletű megoldás
            dlg:var:szamla:pagecurrent             //újabb keletű megoldás 
 
        end
    end
    return NIL

 
****************************************************************************
function makedlg(caption)

local dlg
local tbar, pb,ok, x
local jtb:=mkbrowse() 
local status, label, search
 
    //dlg:=jtdialogNew() //üres dialog objektum
    dlg:=jtdialogNew(4,8,20,80) //üres dialog objektum
    dlg:name:="proba"
    dlg:layout:="vbox"
    dlg:caption:=caption+" "+dlg:dialogid 

    // menu

    dlg:add( pulldown1() ) //egy pulldown menü 
 
 
    // toolbar

    dlg:add( tbar:=jtb:mktoolbar() )
    tbar:additem(jthglueNew())
    tbar:additem(pb:=jtprogbarNew(0,1,0,24))  //;pb:name:="pbar"
   
    //A progressbar kontrollok default neve "progressbar".
    //Ha ezt megváltoztatjuk, akkor a messagebox nem talál
    //alkalmas kontrollt a felső ablakban, ezért létrehoz
    //egy új ablakot.

    tbar:additem(jthglueNew())

    ok:=jtpushNew()  
    ok:name:='ok' 
    ok:text:='OK'
    ok:tooltip:="Helptext for OK button"
    ok:icon:=ICON_MIDDLE 
    ok:mnemonic:="O"
    tbar:additem(ok)
 
    x:=jtpushNew()
    x:name:='x' 
    x:text:='Exit'
    x:tooltip:="Helptext for Exit button"
    x:icon:=ICON_EXIT 
    x:escape:=.t.  //nem kell ellenőrizni a kitöltést
    x:mnemonic:="X"
    tbar:additem(x)
 

    // table

    dlg:add( jtb )

    // status line (toolbar/panel)

    //dlg:add( status:=jtpanelNew() )
    dlg:add( status:=jttoolbarNew() )
    status:additem( label:=jtlabelNew() )
                    label:name:="label"
                    label:text:="Próba szerencse: 2002.08.20" 

    status:additem( jthglueNew() )

    status:additem( search:=jtgetNew(0,0,0,25) )
                    search:name:="search"
                    search:picture:="@R! 99999999-NNNNNNNN-99999999"
                    search:tooltip:=search:picture 
                    search:valid:=.t.

    status:additem( jthglueNew() )


    dlg:varinst("main1_demo_dialog")

    return dlg


****************************************************************************
/*
static function mkbrowse()
    
local jtb:=jtbrowseNew( tabBrowse(table) )

    brwColumn(jtb,"#recno",{||tabPosition(table)},"@RN 9,999,999")
    brwColumn(jtb,"Számlaszám",{||tabEvalColumn(table,1)},"@R! 99999999-NNNNNNNN-99999999")
    brwColumn(jtb,"Kód",{||tabEvalColumn(table,2)})
    brwColumn(jtb,"Dev",{||tabEvalColumn(table,3)})
    brwColumn(jtb,"Név",{||tabEvalColumn(table,4)})
    brwColumn(jtb,"Egyenleg",{||tabEvalColumn(table,5)},"@RN 999,999,999,999.99")
    brwColumn(jtb,"Túl",tabBlock(table,"tulmenflag"),"@L" )
    brwColumn(jtb,"Kivdat",tabBlock(table,"kivdatum"),"@RD")
 
    jtb:saveposblock:={||tabPosition(table)} // új
    jtb:restposblock:={|p|tabGoto(table,p)}  // új
    jtb:maxrow:=20                           // új

    jtb:name:="szamla"
    jtb:tooltip:="öt szép szűzlány őrült írót nyúz"
    
    //ezek is működnek
    //jtb:brwloop
    //brwShow(jtb)
    //brwLoop(jtb)
   
    return jtb
*/

****************************************************************************
static function mkbrowse()
    
local jtb:=jtbrowsetableNew()

    jtb:table:=table

    jtb:addcolumn("#recno",{||tabPosition(table)},"@RN 9,999,999")
    jtb:addcolumn("Számlaszám",{||tabEvalColumn(table,1)},"@R! 99999999-NNNNNNNN-99999999")
    jtb:addcolumn("Kód",{||tabEvalColumn(table,2)},3)
    jtb:addcolumn("Dev",{||tabEvalColumn(table,3)},3)
    jtb:addcolumn("Név",{||tabEvalColumn(table,4)},30)
    jtb:addcolumn("Egyenleg",{||tabEvalColumn(table,5)},"@RN 999,999,999,999.99")
    jtb:addcolumn("Túl",tabBlock(table,"tulmenflag"),"@L" )
    jtb:addcolumn("Kivdat",tabBlock(table,"kivdatum"),"@RD")
 
    jtb:maxrow:=20             

    jtb:name:="szamla"
    jtb:tooltip:="öt szép szűzlány őrült írót nyúz"
    
    return jtb

 
****************************************************************************
function pulldown1()

local m, mi

    m:=jtmenuNew()
    m:text:="Egy pulldown menü"
    m:tooltip:="Tooltip a pulldown menühöz."

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Elindít egy alertet" 
               mi:name:="menuitem1"
               mi:tooltip:="Tooltip: elindít egy alertet."
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Így néz ki egy letiltott menü" 
               mi:name:="menuitem2"
               mi:enabled:=.f.
               mi:tooltip:="Tooltip: Így néz ki egy letiltott menü."
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Elindít egy új dialogboxot" 
               mi:name:="menuitem3"
               mi:tooltip:="Tooltip: Elindít egy új dialogboxot."
    
    m:additem( jtmenusepNew())
    
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Listázza a kontrollok tartalmát" 
               mi:name:="menuitem4"
               mi:actionblock:={|d|d:list}
               mi:tooltip:="Tooltip: listázza a kontrollok tartalmát."

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Packolja az adattáblát" 
               mi:name:="menuitem5"
               mi:actionblock:={||tabPack(table)}
               mi:tooltip:="Tooltip: packolja az adattáblát."

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Progressbar teszt" 
               mi:name:="menuitem6"
               mi:actionblock:={||pbar1()}
               mi:tooltip:="Tooltip: progressbar teszt."
 
    return m

****************************************************************************
function pbar1()
local n, pb
    pb:=message(pb,"Türelem rózsát terem!")
    for n:=1 to 100
        message(pb,"Türelem rózsát terem"+str(n) )
        sleep(50)
    next
    message(pb)
    return NIL


****************************************************************************
function message(pb,text)
static sec
    if( pb==NIL )
        pb:=jtprogbarNew()
        pb:caption:=argv(0)
    elseif( text==NIL )
        pb:clearbar
        return NIL
    end
    if( !sec==seconds() )
        pb:setbar(0,text)
        pb:caption:=NIL
        sec:=seconds() 
    end
    return pb


****************************************************************************
 