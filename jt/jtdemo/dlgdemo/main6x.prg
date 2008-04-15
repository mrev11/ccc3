
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

//jtconnect 
//fix layout
//tabbed pane
//browse fixen pozícionált kontrollban
//toolbar fixen pozícionált panelban
//progressbar programozás
//memoedit teszt

#include "icons.ch"
 
#include "tabdlg.dlg"
#include "panel1.pnl"
#include "panel2.pnl"
#include "panel3.pnl"

****************************************************************************
function main()

    set date format "yyyy-mm-dd"

    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})

    msgloop( makedlg("Demó dialog") )
    
    return NIL


****************************************************************************
function msgloop(dlg)

local msg
local v, f
local html_true:='<html><font face="ariel" size="5" color="green">True iimm</font></html>' 
local html_false:='<html><font face="ariel" size="5" color="red">False iimm</font></html>'
//local html_true:='<html><font size="5" color="green">True iimm</font></html>' 
//local html_false:='<html><font  size="5" color="red">False iimm</font></html>'
 
    dlg:show 
    dlg:var:table:pagefirst

    f:=dlg:var:f:varget 
    dlg:var:flag:changetext:=if(f,html_true,html_false)
    

    while( NIL!=(msg:=dlg:getmessage) ) 


        if( msg=="ok" )
            if( pbar(dlg) )
                dlg:close
            end
   
        elseif( msg=="x" )
             dlg:close //ez a preferált megoldás

            //dlg:exit //kilép a terminál
            //exit

        elseif( msg=="list" )
            ? v:=dlg:var:gszla:varget, valtype(v)
            ? v:=dlg:var:gsum:varget, valtype(v) 
            ? v:=dlg:var:gdate:varget, valtype(v) 
            ? v:=dlg:var:f:varget, valtype(v) 
            
        elseif( msg=="menuitem4" )
        
            //hozzáférés a kontrollokhoz
        
            ? dlg:f1:varget 
            ? dlg:f2:varget 
            ? dlg:f3:varget 

            ? dlg:r1:varget
            ? dlg:r2:varget 
            ? dlg:r3:varget 

            ? dlg:c1:varget
            ? dlg:c2:varget 
            ? dlg:c3:varget 
         
            ? dlg:datum:varget

            //kontrollok változtatása
            
            dlg:r1:varput(.t.) 
            dlg:f2:varput(dlg:caption)
            dlg:choice:varput(5)

            dlg:c1:varput(.t.)
            dlg:c2:varput(.t.)
            dlg:c3:varput(.t.)
            dlg:c4:varput(.t.)
            

            //az alábbi buttonok pulldown menüben vannak, 
            //ezért nincs a dialognak ilyen attribútuma,
            //a var beágyazott objektumon keresztül lehet őket megtalálni

            dlg:var:mcheck1:select(.t.) 
            dlg:var:mcheck2:select(.t.)
            dlg:var:mcheck3:select(.t.)
            dlg:var:mcheck4:select(.t.)
            dlg:var:mcheck5:select(.t.)
            dlg:var:mcheck6:select(.t.)
 
            dlg:var:mradio7:select(.t.)
            dlg:var:mradio10:select(.t.)
 

            //ezek meg egy panelban vannak, 
            //ezért nincs a dialognak ilyen attribútuma,
            //a var beágyazott objektumon keresztül lehet őket megtalálni

            dlg:var:b1:select(.t.) 
            dlg:var:b2:select(.t.)
            dlg:var:b3:select(.t.)
            dlg:var:b4:select(.t.)
            dlg:var:b5:select(.f.)
            dlg:var:b6:select(.f.)
            dlg:var:b7:select(.f.)
            dlg:var:b8:select(.f.)
            
            
            dlg:var:table:varput({3,5,6})
            
        elseif( msg=="f3" )

            if( dlg:f3:varget<3 )
                alert("Nem lehet kisebb 3-nál!")
                dlg:f3:setfocus
            elseif( dlg:f3:varget>4 )
                alert("Nem lehet nagyobb 4-nél!")
                dlg:f3:setfocus
            end
            
        end
        
        if( !f==dlg:var:f:varget  )
            f:=dlg:var:f:varget 
            dlg:var:flag:changetext:=if(f,html_true,html_false)
        end
        
 
    end
    
    return NIL


****************************************************************************
function makedlg( caption )

local dlg,m,group,n,c,d
local pane,table,navig
local label

    dlg:=tabdlgNew() //msk2dlg által generált dialog objektum
    dlg:caption:=caption+" "+dlg:dialogid

    // menu

    dlg:add( m:=pulldown1() ) 
             m:icon:=ICON_MIDDLE 

    dlg:add( m:=pulldown2() ) 
             m:icon:=ICON_EXIT 
             m:tooltip:="Tooltip for a pulldown menu."
             m:name:="pulldown"
             m:additem( jtmenusepNew() )
             m:additem( pulldown1x("Második szintű menü 1") )
             m:additem( pulldown1x("Második szintű menü 2") )
             
    dlg:add( jtmenusepNew() )         
 
    dlg:add( m:=pulldown3() ) 
 
    // get

    dlg:f1:picture:="@RX! NNNNNNNN-99999999"
    dlg:f1:valid:=.t.
    dlg:f1:text:="ABCDERFH12345678"
    dlg:f1:tooltip:=dlg:f1:picture 

  //dlg:f2:picture:="@R! XXXX-XXXX-XXXX-XXXX" 
    dlg:f2:valid:=.t.
    dlg:f2:text:="A&amp;BCD12&lt;678"
    dlg:f2:tooltip:=dlg:f2:picture  
  //dlg:f2:enabled:=.f.

    dlg:f3:picture:="@RFN 999,999,999.9999" 
    dlg:f3:valid:=.t.
    dlg:f3:varput(3.1415)
    dlg:f3:tooltip:=dlg:f3:picture  
    
    dlg:datum:picture:="@RDX"
    dlg:datum:tooltip:=dlg:datum:picture  
    //dlg:datum:text("2002-08-23")
    dlg:datum:varput(stod("20020823"))
 
    // combo
 
    dlg:choice:additem("Próba szerencse!")
    dlg:choice:additem("Van, aki forrón szereti.")
    dlg:choice:additem(cdata("xx<&xx"))
    for n:=1 to 10
        dlg:choice:additem("Próba"+str(n))
    next
    dlg:choice:select(2)
    dlg:choice:tooltip:="Helpszöveg a combo boxhoz."
    dlg:choice:actionblock:={||dlg:f2:varput(dlg:choice:selecteditem)}

    // radio    

    dlg:r1:selectedicon:=ICON_GREEN
    dlg:r1:icon:=ICON_RED
    dlg:r1:mnemonic:="S"
    dlg:r2:selectedicon:=ICON_GREEN
    dlg:r2:icon:=ICON_RED
    dlg:r2:mnemonic:="Z"
 
    dlg:r3:select 
    dlg:r3:valid:=.t. 
    dlg:r3:tooltip:="zöld=selected, piros=deselected" 
    dlg:r3:selectedicon:=ICON_GREEN
    dlg:r3:icon:=ICON_RED
    dlg:r3:mnemonic:="E"
 
    dlg:r4:selectedicon:=ICON_GREEN
    dlg:r4:icon:=ICON_RED
    dlg:r4:mnemonic:="R"
 
    //ha nincs megadva explicit radio group,
    //akkor a default grouphoz tartoznak a gombok

    //group:=radiogroup()
    //dlg:r1:setgroup(group)
    //dlg:r2:setgroup(group)
    //dlg:r3:setgroup(group) 
    //dlg:r4:setgroup(group)
 

    // check

    dlg:c1:select
    dlg:c1:tooltip:="zöld=selected, piros=deselected"
    //dlg:c1:valid:=.t.
    dlg:c1:actionblock:={||dlg:var:f:varput(dlg:c1:varget)}
    dlg:c1:mnemonic:="G"
    dlg:c1:focusable:=.f.
 
    dlg:c1:icon:=ICON_RED 
    dlg:c1:selectedicon:=ICON_GREEN 
    dlg:c2:icon:=ICON_RED 
    dlg:c2:selectedicon:=ICON_GREEN 
    dlg:c3:icon:=ICON_RED 
    dlg:c3:selectedicon:=ICON_GREEN 
    dlg:c4:icon:=ICON_RED 
    dlg:c4:selectedicon:=ICON_GREEN 
 

    // tabbed panes
    //dlg:tpane:placement:="b"
    dlg:tpane:additem( pane:=panel1New() )
    pane:text:="Címke1"
    pane:icon:=ICON_MIDDLE
    pane:tooltip:="Tooltip for pane1"

    pane:gszla:picture:="@RX! 99999999-NNNNNNNN"
    pane:gszla:tooltip:=pane:gszla:picture 
    pane:gszla:varput:="11112222AAAABBBB"

    pane:gsum:picture:="@RNX 99,999,999,999.99"
    pane:gsum:tooltip:=pane:gsum:picture 
    pane:gsum:varput:=111222333.99

    pane:gdate:picture:="@RDX"
    pane:gdate:tooltip:=pane:gdate:picture 
    pane:gdate:varput:=stod("20030101")
 
    pane:f:picture:="@LX!"
    pane:f:tooltip:="Logikai mező"
    pane:f:varput:=.f.
    pane:f:valid:=.t.
 
    pane:list:icon:=ICON_MIDDLE

    
    
    dlg:tpane:additem( pane:=panel2New() )
    pane:text:="Címke2"
    pane:icon:=ICON_MIDDLE
    pane:tooltip:="Tooltip for pane2"
    pane:kep:additem( label:=jticon(ICON_STEAM) )
    //pane:kep:additem( jtimage(MORGO) )
    label:name:="label"
    pane:kep:vscroll:=.t.
    pane:kep:hscroll:=.t.
    pane:kep:layout:="hbox"
 
    dlg:tpane:additem( pane:=jtpanelNew() )
    pane:layout:="vbox"
    pane:text:="Cimke3"
    pane:icon:=ICON_MIDDLE
    pane:tooltip:="Tooltip for pane3"

    pane:additem(table:=jtbrowsearrayNew())
    table:name:="table"
    table:array:=d:=directory(fullmask())
    for n:=1 to len(d)
        d[n][5]:=empty(d[n][5])
    next
    table:addcolumn("#row",{||table:arraypos},"@RN 9999") 
    table:addcolumn("File",1,"@R XXXXXXXXXXXXXXXX"):editable:=.t.
    table:addcolumn("Size",2,"@RN 999,999"):editable:=.t.
    table:addcolumn("Date",3,"@RD"):editable:=.t.
    table:addcolumn("Time",4,"@R 99:99:99"):editable:=.t.
    table:addcolumn("Attr",5,"@RL"):editable:=.t.
    table:tooltip:="öt szép szűzlány őrült írót nyúz"
    table:maxrow:=15

    pane:additem(navig:=table:mktoolbar)

 
    // status
    
    dlg:pnl:text:=""
    dlg:pnl:additem( label:=jtlabel("Státuszsor-bal") )
                     label:name:="statusbal"
    dlg:pnl:additem( jthglueNew() )
    dlg:pnl:additem( label:=jtlabel("Státuszsor-közép") )
                     label:name:="statuskozep"
    dlg:pnl:additem( jthglueNew() )
    dlg:pnl:additem( label:=jtlabel("Könyvnap:2002.08.27") )
                     label:name:="statusjobb"
    
    dlg:ok:mnemonic:="O"
    dlg:ok:focusable:=.f.
 
    dlg:x:escape:=.t.
    dlg:x:mnemonic:="X"
    
    dlg:varinst( "main6_dialog" )

    return dlg
 

****************************************************************************
function pulldown1()

local m, mi

    m:=jtmenuNew()
    m:text:="Egy pulldown menü"
    m:mnemonic:="M"

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Verziószámok"
               mi:actionblock:={||alert( "jterminal "+jtversion()+";jtlib "+jtlibversion())}

    m:additem( mi:=jtmenuitemNew() )
               mi:name:="menuitem1"
               mi:text:="Listázza a kontrollokat"  
               mi:icon:=ICON_MIDDLE
               mi:tooltip:=mi:text+"."
               mi:actionblock:={|dlg|dlg:list}

    m:additem( mi:=jtmenuitemNew() )
               mi:name:="menuitem2"
               mi:text:="Listázza a var objektum struktúráját"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={|dlg|dlg:var:liststruct}

    m:additem( mi:=jtmenuitemNew() )
               mi:name:="menuitem3"
               mi:text:="Disabled menuitem"  
               mi:enabled:=.f.
               mi:tooltip:="This menuitem is disabled." 
               mi:actionblock:={|dlg|dlg:list}

    m:additem( mi:=jtmenuitemNew() )
               mi:name:="menuitem4"
               mi:text:="Kontroll cserebere"
               mi:tooltip:=mi:text+"."
 

    m:additem( jtmenusepNew())
 
    m:additem( mi:=jtmenuitemNew() )
               mi:name:="menuitem5"
               mi:text:="Elindít egy alertet"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={|dlg|qout("alert:",alert("Próba szerencse;Van, aki forrón szereti.",{"VÁLASZ-1","VÁLASZ-2","VÁLASZ-3","VÁLASZ-4"}))}

    m:additem( mi:=jtmenuitemNew() )
               mi:name:="menuitem6"
               mi:text:="Indít egy új dialogboxot"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={|d,c|c:=d:caption+"@",msgloop(makedlg(c))}

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Indít egy új dialogboxot (jtconnect)"  
               mi:tooltip:=mi:text+"."
               //mi:actionblock:={|d,c|c:=d:caption+"@",msgloop(makedlg(c))}
               mi:actionblock:={||jtconnect("localhost",46006)} 
 
    m:additem( mi:=jtmenuitemNew() )
               mi:name:="menuitem7"
               mi:text:="Memoedit teszt"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={||memotest()}

    m:additem( mi:=jtmenusepNew() )
 
    m:additem( mi:=jtmenuitemNew() )
               mi:name:="menuitem8"
               mi:text:="FileChooser teszt"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={||fchoosetest()}

    m:additem( mi:=jtmenuitemNew() )
               mi:name:="menuitem_dirlist"
               mi:text:="Directory list teszt"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={||dirlisttest()}
 
    m:additem( mi:=jtmenuitemNew() )
               mi:name:="menuitem9"
               mi:text:="File upload teszt"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={||uploadtest()}

    m:additem( mi:=jtmenuitemNew() )
               mi:name:="menuitem10"
               mi:text:="File download teszt"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={||downloadtest()}

    m:additem( mi:=jtmenusepNew() )

    m:additem( mi:=jtmenuitemNew() )
               mi:name:="menuitem11"
               mi:text:="Change attributes 1"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={|dlg|changeattribs1(dlg)}

    m:additem( mi:=jtmenuitemNew() )
               mi:name:="menuitem12"
               mi:text:="Change attributes 2"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={|dlg|changeattribs2(dlg)}
 
    return m


****************************************************************************
function pulldown1x(text) 
//ugyanaz, mint pulldown1, de automatikus nevekkel

local m, mi

    m:=jtmenuNew()
    m:text:=text
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Listázza a kontrollokat"  
               mi:icon:=ICON_MIDDLE
               mi:tooltip:=mi:text+"."
               mi:actionblock:={|dlg|dlg:list}

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Listázza a var objektum struktúráját"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={|dlg|dlg:var:liststruct}

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Disabled menuitem"  
               mi:enabled:=.f.
               mi:tooltip:="This menuitem is disabled." 
               mi:actionblock:={|dlg|dlg:list}

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Kontroll cserebere"
               mi:tooltip:=mi:text+"."
 

    m:additem( jtmenusepNew())
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Elindít egy alertet"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={|dlg|qout("alert:",alert("Próba szerencse;Van, aki forrón szereti.",{"VÁLASZ-1","VÁLASZ-2","VÁLASZ-3","VÁLASZ-4"}))}
               mi:accelerator:="ctrl R"
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Indít egy új dialogboxot (jtconnect)"  
               mi:tooltip:=mi:text+"."
               //mi:actionblock:={|d,c|c:=d:caption+"@",msgloop(makedlg(c))}
               mi:actionblock:={||jtconnect("localhost",46006)} 
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Memoedit teszt"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={||memotest()}
               mi:accelerator:="ctrl E"
 
    m:additem( mi:=jtmenusepNew() )
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="FileChooser teszt"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={||fchoosetest()}

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="File upload teszt"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={||uploadtest()}

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="File download teszt"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={||downloadtest()}

    m:additem( mi:=jtmenusepNew() )

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Change attributes 1"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={|dlg|changeattribs1(dlg)}

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Change attributes 2"  
               mi:tooltip:=mi:text+"."
               mi:actionblock:={|dlg|changeattribs2(dlg)}
 
    return m


****************************************************************************
function pulldown2()

local m, mi

    m:=jtmenuNew()
    m:text:="Programindító menü"
    m:mnemonic:="P"

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Demó: adatbázis browse"  
               mi:name:="main1.exe"
               mi:icon:=ICON_MIDDLE
               mi:tooltip:="Elindít egy programot: adatbázis browseolás." 
               //mi:actionblock:=mkblock(mi:name)
               mi:actionblock:={||jtconnect("localhost",46001)}
               mi:accelerator:="ctrl D"
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Demó: array browse"  
               mi:name:="main2.exe"
               mi:icon:=ICON_MIDDLE
               mi:tooltip:="Elindít egy programot: array browseolás." 
               //mi:actionblock:=mkblock(mi:name)
               mi:actionblock:={||jtconnect("localhost",46002)}
               mi:accelerator:="ctrl B"
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Demó: text megjelenítés"  
               mi:name:="main3.exe"
               mi:icon:=ICON_MIDDLE
               mi:tooltip:="Elindít egy programot: text megjelenítés." 
               //mi:actionblock:=mkblock(mi:name)
               mi:actionblock:={||jtconnect("localhost",46003)}
               mi:accelerator:="ctrl T"
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Demó: HTML megjelenítés"  
               mi:name:="main3x.exe"
               mi:icon:=ICON_MIDDLE
               mi:tooltip:="Elindít egy programot: HTML megjelenítés." 
               mi:actionblock:={||jtconnect("localhost",46004)} 
               //mi:actionblock:=mkblock(mi:name)
               mi:accelerator:="ctrl H"
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Demó: kép átküldés"  
               mi:name:="main4.exe"
               mi:icon:=ICON_MIDDLE
               mi:tooltip:="Elindít egy programot: kép átküldve a terminálnak." 
               mi:actionblock:={||jtconnect("localhost",46005)} 
               //mi:actionblock:=mkblock(mi:name)

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Demó: panelek"  
               mi:name:="main5.exe"
               mi:icon:=ICON_MIDDLE
               mi:tooltip:="Elindít egy programot: egymásba skatulyázott panelek." 
               mi:actionblock:=mkblock(mi:name)
 
    return m


****************************************************************************
function pulldown3()

local m, mi

    m:=jtmenuNew()
    m:text:="Button menü"
    m:mnemonic:="B"
 
    m:additem( mi:=jtmenucheckNew() )
               mi:text:="Próba szerencse 1"  
               mi:name:="mcheck1"
               mi:tooltip:="Tooltip:"+mi:text

    m:additem( mi:=jtmenucheckNew() )
               mi:text:="Próba szerencse 2"  
               mi:name:="mcheck2"
               mi:tooltip:="Tooltip:"+mi:text
 
    m:additem( mi:=jtmenucheckNew() )
               mi:text:="Próba szerencse 3"  
               mi:name:="mcheck3"
               mi:tooltip:="Tooltip:"+mi:text
               
    m:additem( jtmenusepNew() )               

    m:additem( mi:=jtmenucheckNew() )
               mi:text:="Próba szerencse 4"  
               mi:name:="mcheck4"
               mi:tooltip:="Tooltip:"+mi:text
               mi:valid:=.t.
 
    m:additem( mi:=jtmenucheckNew() )
               mi:text:="Próba szerencse 5"  
               mi:name:="mcheck5"
               mi:tooltip:="Tooltip:"+mi:text
               mi:state:=.t.
 
    m:additem( mi:=jtmenucheckNew() )
               mi:text:="Próba szerencse 6"  
               mi:name:="mcheck6"
               mi:tooltip:="Tooltip:"+mi:text
               mi:enabled:=.f.


    m:additem( jtmenusepNew() )
 
    m:additem( mi:=jtmenuradioNew() )
               mi:text:="Próba szerencse 7"  
               mi:name:="mradio7"
               mi:tooltip:="Tooltip:"+mi:text
               mi:valid:=.t.
 
    m:additem( mi:=jtmenuradioNew() )
               mi:text:="Próba szerencse 8"  
               mi:name:="mradio8"
               mi:tooltip:="Tooltip:"+mi:text
               mi:state:=.t.
 
    m:additem( mi:=jtmenuradioNew() )
               mi:text:="Próba szerencse 9"  
               mi:name:="mradio9"
               mi:tooltip:="Tooltip:"+mi:text
 
    m:additem( jtmenusepNew() )               
 
    m:additem( mi:=jtmenuradioNew() )
               mi:text:="Próba szerencse 10"  
               mi:name:="mradio10"
               mi:tooltip:="Tooltip:"+mi:text
 
    m:additem( mi:=jtmenuradioNew() )
               mi:text:="Próba szerencse 11"  
               mi:name:="mradio11"
               mi:tooltip:="Tooltip:"+mi:text
 
    return m

 
****************************************************************************
static function mkblock(x)
    return {||jtrun(x)} 

****************************************************************************
function pbar(dlg)
local n

    //default        : nem mutat szöveget
    //text="percent" : automatikusan mutatja a %-okat
    //text="bármi"   : megjeleníti a szöveget
    //text=""        : üreset mutat

    if( dlg:c1:varget )
        dlg:progressbar:setbar(0,"percent")
    else
        dlg:progressbar:setbar(0,"Türelem rózsát terem") 
    end

    for n:=1 to 100 step 5
        dlg:progressbar:setbar(n)
        sleep(150)
    next

    dlg:progressbar:setbar(0,"HOPP") 
    sleep(1000)
    dlg:progressbar:setbar(0,"") 
    
    return 1==alert("Befejezte a munkát?",{"Igen","Folytat"})


****************************************************************************
function memotest()
local txt:=jtmemoedit(10,20,25,80,memoread("main6.prg"),.f.) 
    if( txt==NIL )
        alert("Nem mentett!")
    end
    return NIL


****************************************************************************
function fchoosetest()

local ff, fc:=jtfilechooserNew() 

    fc:workdir:="/home/vermes/jt/jtlib"
    fc:caption:="CCC File Chooser"
    fc:text:="HOPP"
    fc:multiselect:=.t.
    fc:selectmode:="F" //csak filéket
    
    fc:addfilter( ff:=jtfilefilterNew() )
                  ff:description:="Java source/class files"
                  ff:addpattern("*.java")
                  ff:addpattern("*.class")
                  ff:regexdir(jtfilepattern("*"))
 
    fc:addfilter( ff:=jtfilefilterNew() )
                  ff:description:="CCC (translated) program files"
                  ff:addpattern("*.cpp")
                  ff:addpattern("*.ppo")
                  ff:addpattern("*.prg")
                  ff:regexdir(jtfilepattern("*"))
 
    fc:addfilter( ff:=jtfilefilterNew() )
                  ff:description:="Binary program files"
                  ff:addpattern("*.exe")
                  ff:addpattern("*.obj")
                  ff:addpattern("*.lib")
                  ff:addpattern("*.so")
                  ff:regexdir(jtfilepattern("*"))

    //Ilyen lehetőségek vannak

    //? fc:getchoice //ez a legáltalánosabb eset

    //? jtfilechooser("*.prg")
    ? jtfilechooser({"*.prg","*.ppo","*.cpp"})
    //? jtfilechooser("/home/vermes/jt/jtlib/*.prg|*.ppo|*.cpp")

    return NIL


****************************************************************************
function dirlisttest()
    dl1("*.java") 
    dl1("*.bat|*.java") 
    dl1("getutil/*.java") 
    dl1("*.bat","D") 
    dl1(,"D") 

    dl2(          , "*.java"           ,          ) 
    dl2(          , "*.bat|*.java"     ,          ) 
    dl2("getutil" , "*.java"           ,          ) 
    dl2(          , "*.bat"            ,"getutil" ) 
    dl2(          , ""                 , "*"      )  

    return NIL
 

static function dl1(mask,attr)
local dirlist, n
    dirlist:=jtdirectory(mask,attr)
    ? "============================="
    ? mask, attr
    ? "============================="
    for n:=1 to len( dirlist )
        ? dirlist[n]
    next
    return NIL


static function dl2(wdir,fmask,dmask)
local dirlist, n
    dirlist:=jtdirlist(wdir,fmask,dmask)
    ? "============================="
    ? wdir,"|",fmask,"|",dmask
    ? "============================="
    for n:=1 to len( dirlist )
        ? dirlist[n]
    next
    return NIL
 
****************************************************************************
function uploadtest()
local n,fc:=jtfilechooser("*.prg|*.ppo|*.cpp")
    dirmake("upload")
    for n:=1 to len(fc)
        jtupload( fc[n], "upload/up"+alltrim(str(n))  )
    next
    return NIL


****************************************************************************
function downloadtest()
    jtdownload( "main6.prg", "download/main6.prg", stod("20031010"), "15:30:30" )
    return NIL
 

****************************************************************************
function changeattribs1(dlg)
local c, n

    c:=dlg:var:menuitem1 
    c:changetext("HOPP")
    c:changetooltip( "Menuitem disabled." )
    c:changeicon(ICON_MIDDLE)
    c:changeenabled(.f.)

    c:=dlg:var:pulldown 
    c:changetext("HOPP")
    c:changetooltip( "Menu disabled." )
    //c:changeicon(ICON_EXIT)
    c:changeenabled(.f.)

    c:=dlg:var:label
    c:changeimage(memoread(MORGO,.t.))

    c:=dlg:var:statusbal
    c:changetext("HOPP")
    c:changetooltip:=c:text
    c:changeicon(ICON_MIDDLE)

    c:=dlg:var:c1
    c:changetext("HOPP")
    c:changetooltip:=c:text

    c:=dlg:var:r1
    c:changetext("HOPP")
    c:changetooltip:=c:text

    c:=dlg:var:ok
    c:changetext:="HOPP"
    c:changetooltip:=c:text
    //c:changeicon:=ICON_MIDDLE
    c:changeenabled(.f.)

    dlg:f3:changepicture:="@R! AAAAAAAA-99999999" 
    dlg:f3:changetooltip:=dlg:f3:picture  
    dlg:f3:varput("AAAABBBB11112222")

    dlg:choice:choicelist:={}
    dlg:choice:additem("PRÓBA SZERENCSE!")
    dlg:choice:additem("VAN, AKI FORRÓN SZERETI.")
    dlg:choice:changelist

    dlg:choice:changeinsert("HOPP",2)
    dlg:choice:changeinsert("KOPP",2)
    dlg:choice:changeappend("Türelem rózsát terem!")
    dlg:choice:changedelete("HOPP")
  
 
    return NIL


****************************************************************************
function changeattribs2(dlg)
local c, n

    c:=dlg:var:menuitem1 
    c:changetext("Listázza a kontrollokat")
    c:changetooltip( c:text+"." )
    c:changeicon("")
    c:changeenabled(.t.)

    c:=dlg:var:pulldown 
    c:changetext("Pulldown")
    c:changetooltip( "Now enabled." )
    //c:changeicon("")
    c:changeenabled(.t.)

    c:=dlg:var:label
    c:changeicon(ICON_STEAM)

    c:=dlg:var:statusbal
    c:changetext("Státuszsor-bal")
    c:changetooltip:=c:text
    c:changeicon("")

    c:=dlg:var:c1
    c:changetext("Csekkbox")
    c:changetooltip:=c:text

    c:=dlg:var:r1
    c:changetext("Radiógomb")
    c:changetooltip:=c:text

    c:=dlg:var:ok
    c:changetext:="Ok"
    c:changetooltip:=c:text
    c:changeicon:=""
    c:changeenabled(.t.)

    dlg:f3:changepicture:="@RN 999,999,999.9999" 
    dlg:f3:changetooltip:=dlg:f3:picture  
    dlg:f3:varput(3.1415)


    dlg:choice:choicelist:={}
    dlg:choice:additem("Próba szerencse!")
    dlg:choice:additem("Van, aki forrón szereti.")
    for n:=1 to 10
        dlg:choice:additem("Próba"+str(n))
    next
    dlg:choice:changelist
 
    return NIL

****************************************************************************
 

 