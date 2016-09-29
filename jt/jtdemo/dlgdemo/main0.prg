
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

//fix layout
//összetett menü
//alert
//több dialogbox
//mindenféle kontrollok: get, check, radio
//browse fixen pozícionált kontrollban
//toolbar fixen pozícionált panelban
//progressbar programozás
//memoedit teszt

#include "directry.ch"
#include "icons.ch"

#include "pdialog.dlg"
 
****************************************************************************
function main()

    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})
    
    //pbar0()
    //pbar1()
 
    msgloop( makedlg("Demó dialog") )
    
    return NIL


****************************************************************************
function msgloop(dlg)
local msg

    dlg:show 
    
    dlg:adir:pagefirst

    while( NIL!=(msg:=dlg:getmessage) ) 

        if( msg=="ok" )
            if( pbar(dlg) )
                dlg:close
            end
   
        elseif( msg=="x" )
            //dlg:exit //kilép a terminál
            //quit
            dlg:close

        elseif( msg=="menuitem4" )
        
            //hozzáférés a kontrollokhoz
        
            ? dlg:f1:varget 
            ? dlg:f2:varget 
            ? dlg:f3:varget 
            ? dlg:adir:varget 

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
            //emiatt csak a var-on keresztül elérhetők

            dlg:var:mcheck1:select(.t.)
            dlg:var:mcheck2:select(.t.)
            dlg:var:mcheck3:select(.t.)
            dlg:var:mcheck4:select(.t.)
            dlg:var:mcheck5:select(.t.)
            dlg:var:mcheck6:select(.t.)
 
            dlg:var:mradio7:select(.t.)
            dlg:var:mradio10:select(.t.)
 
        end
    end
    
    return NIL


****************************************************************************
function makedlg( caption )

local dlg,m,group,n,c,dir

    dlg:=pdialogNew() //msk2dlg által generált dialog objektum
    dlg:caption:=caption+" "+dlg:dialogid

    // menu

    dlg:add( m:=pulldown1() ) 
             m:icon:=ICON_MIDDLE 

    dlg:add( m:=pulldown1x() ) 
             m:icon:=ICON_EXIT 
             m:tooltip:="Tooltip for a pulldown menu."
             m:additem(pulldown1x())

    dlg:add( m:=pulldown2() ) 

    dlg:add( m:=pulldown3() ) 
    
    //password
    
    dlg:pw:varput:="hopp"
    dlg:pw:actionblock:={||passw_verif(dlg)}
    
 
    // get

    dlg:f1:picture:="@RX! NNNNNNNN-99999999"
    dlg:f1:valid:=.t.
    dlg:f1:text:="ABCDERFH12345678"
    dlg:f1:tooltip:=dlg:f1:picture 

    dlg:f2:picture:="@R! XXXX-XXXX-XXXX-XXXX" 
    dlg:f2:valid:=.t.
    dlg:f2:text:="A&amp;BCD12&lt;678"
    dlg:f2:tooltip:=dlg:f2:picture  

    dlg:f3:picture:="@RN 999,999,999.9999" 
    dlg:f3:valid:=.t.
    dlg:f3:varput(3.1415)
    dlg:f3:tooltip:=dlg:f3:picture  
    
    dlg:datum:picture:="@RD"
    dlg:datum:tooltip:=dlg:datum:picture  
    //dlg:datum:text("2002-08-23")
    dlg:datum:varput(stod("20020823"))
 
    // combo
    
    dir:=directory("*.prg","H")
    dlg:choice:additem("Van, aki forrón szereti.")
    dlg:choice:additem("Próba szerencse.")
    for n:=1 to len(dir)
        dlg:choice:additem(dir[n][1])
    next
    dlg:choice:select(2)
    dlg:choice:tooltip:="Helpszöveg a combo boxhoz."
    dlg:choice:actionblock:={||dlg:f2:varput(dlg:choice:selecteditem)}

    // radio    

    dlg:r3:select 
    dlg:r3:valid:=.t. 

    //ha nincs megadva explicit radio group,
    //akkor a default grouphoz tartoznak a gombok

    //group:=radiogroup()
    //dlg:r1:setgroup(group)
    //dlg:r2:setgroup(group)
    //dlg:r3:setgroup(group) 
    //dlg:r4:setgroup(group)
 

    // check

    dlg:c1:select
    dlg:c1:valid:=.t.


    // table

    dlg:adir:array:=directory("*","H")

    dlg:adir:addcolumn("#row",{||dlg:adir:arraypos},"@RN 999,999") 
    dlg:adir:addcolumn("File",F_NAME,"@! XXXXXXXXXXXXXXXX") 
    dlg:adir:addcolumn("Size",F_SIZE,"@RN 999,999,999") 
    dlg:adir:addcolumn("Date",F_DATE,"@RD") 
    dlg:adir:addcolumn("Time",F_TIME,8) 
    dlg:adir:addcolumn("Attr",F_ATTR,4) 
    dlg:adir:tooltip:="öt szép szűzlány őrült írót nyúz"
    dlg:adir:maxrow:=10
    
    dlg:adir:mktoolbar( dlg:tbar )


    // status
    
    dlg:pnl:text:=""
    dlg:pnl:additem( jtlabel("Státuszsor-bal") )
    dlg:pnl:additem( jthglueNew() )
    dlg:pnl:additem( jtlabel("Státuszsor-közép") )
    dlg:pnl:additem( jthglueNew() )
    dlg:pnl:additem( jtlabel("Könyvnap:2002.08.27") )
 
    dlg:ok:mnemonic:="O"
    dlg:x:mnemonic:="X"
    
    dlg:varinst("main_demo_dialog")

    //etched,lowered,raised,empty,null
    //dlg:progressbar:border:="raised"
    dlg:pnl:border:="lowered"
    //dlg:ok:border:="raised"
    
    return dlg
    
 

****************************************************************************
function pulldown1()

local m, mi

    m:=jtmenuNew()
    m:text:="Egy pulldown menü"

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Listázza a kontrollokat"  
               mi:name:="menuitem1"
               mi:icon:=ICON_MIDDLE
               mi:tooltip:="Listázza a kontrollokat." 
               mi:actionblock:={|dlg|dlg:list}

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="This menuitem is disabled"  
               mi:name:="menuitem2"
               mi:enabled:=.f.
               mi:tooltip:="This menuitem is disabled." 
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Elindít egy alertet"  
               mi:name:="menuitem3"
               mi:tooltip:="Alert teszt." 
               mi:actionblock:={|dlg|qout("alert:",alert("Próba szerencse;Van, aki forrón szereti.",{"VÁLASZ-1","VÁLASZ-2","VÁLASZ-3","VÁLASZ-4"}))}
    
    m:additem( jtmenusepNew())
    
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Kontroll cserebere"
               mi:name:="menuitem4"
               mi:tooltip:="Kiolvassa az editálható kontrollok tartalmát." 

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Indít egy új dialogboxot"  
               mi:name:="menuitem5"
               mi:tooltip:="Indít egy új dialogboxot." 
               mi:actionblock:={|d,c|c:=d:caption+"@",msgloop(makedlg(c))}

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Memoedit teszt"  
               mi:name:="menuitem6"
               mi:tooltip:="Memóedit teszt." 
               mi:actionblock:={||memotest()}
 
    return m


****************************************************************************
function pulldown1x() //ugyanaz nevek nélkül

local m, mi

    m:=jtmenuNew()
    m:text:="Egy pulldown menü"

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Listázza a kontrollokat"  
               mi:icon:=ICON_MIDDLE
               mi:tooltip:="Listázza a kontrollokat." 
               mi:actionblock:={|dlg|dlg:list}

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="This menuitem is disabled"  
               mi:enabled:=.f.
               mi:tooltip:="This menuitem is disabled." 
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Elindít egy alertet"  
               mi:tooltip:="Alert teszt." 
               mi:actionblock:={|dlg|qout("alert:",alert("Próba szerencse;Van, aki forrón szereti.",{"VÁLASZ-1","VÁLASZ-2","VÁLASZ-3","VÁLASZ-4"}))}
    
    m:additem( jtmenusepNew())
    
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Kontroll cserebere"
               mi:tooltip:="Kiolvassa az editálható kontrollok tartalmát." 

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Indít egy új dialogboxot"  
               mi:tooltip:="Indít egy új dialogboxot." 
               mi:actionblock:={|d,c|c:=d:caption+"@",msgloop(makedlg(c))}

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Memoedit teszt"  
               mi:tooltip:="Memóedit teszt." 
               mi:actionblock:={||memotest()}
 
    return m

 
****************************************************************************
function pulldown2()

local m, mi

    m:=jtmenuNew()
    m:text:="Programindító menü"

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Demó: adatbázis browse"  
               mi:name:="main1.exe"
               mi:icon:=ICON_MIDDLE
               mi:tooltip:="Elindít egy programot: adatbázis browseolás." 
               mi:actionblock:=mkblock(mi:name)
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Demó: array browse"  
               mi:name:="main2.exe"
               mi:icon:=ICON_MIDDLE
               mi:tooltip:="Elindít egy programot: array browseolás." 
               mi:actionblock:=mkblock(mi:name)

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Demó: textarea"  
               mi:name:="main3.exe"
               mi:icon:=ICON_MIDDLE
               mi:tooltip:="Elindít egy programot: text megjelenítés." 
               mi:actionblock:=mkblock(mi:name)

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Demó: htmlarea"  
               mi:name:="main3x.exe"
               mi:icon:=ICON_MIDDLE
               mi:tooltip:="Elindít egy programot: html megjelenítés." 
               mi:actionblock:=mkblock(mi:name)
 
    m:additem( mi:=jtmenuitemNew() )
               mi:text:="Demó: kép átküldés"  
               mi:name:="main4.exe"
               mi:icon:=ICON_MIDDLE
               mi:tooltip:="Elindít egy programot: kép átküldve a terminálnak." 
               mi:actionblock:=mkblock(mi:name)

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
function menuitem()
local mi:=jtmenuitemNew() 
    mi:text:="Önálló menüpont!"
    mi:name:="menuitem5"
    return mi

****************************************************************************
function pbar0()
local n, pb:=jtprogbarNew()
    pb:setbar(0,"Türelem rózsát terem")
    for n:=1 to 100 step 5
        pb:setbar(n)
        sleep(200)
    next
    pb:setbar(0,"HOPP") 
    pb:clearbar
    return NIL


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

    for n:=1 to 100
        dlg:progressbar:setbar(n)
        sleep(50)
    next

    dlg:progressbar:setbar(0,"HOPP") 
    sleep(1000)
    dlg:progressbar:setbar(0,"") 
    
    return 1==alert("Befejezte a munkát?",{"Igen","Folytat"})


****************************************************************************
function message(pb,text)
    if( pb==NIL )
        pb:=jtprogbarNew() 
    elseif( text==NIL )
        pb:clearbar
        return NIL
    end
    pb:setbar(,text)
    return pb


****************************************************************************
function memotest()
local txt:=jtmemoedit(10,20,25,80,memoread("template.txt"),.f.) 
    if( txt==NIL )
        alert("Nem mentett!")
    end
    return NIL



****************************************************************************
function passw_verif(dlg)

local p:=a"hopp"
local s1:=a"Próba"
local s2:=crypto_bin2hex(crypto_rand_pseudo_bytes(4))
local x:=dlg:pw:getpassword(bin2str(s1),bin2str(s2))

    ? 1, p
    ? 2, p:=crypto_md5(p+s1)
    ? 3, p:=crypto_md5(p+s2)
    ? 4, p:=base64_encode(p)
    ? 5, p:=bin2str(p)
    ? 6, x
    
    if( p==x  )
        alert( "Jelszó OK" )
        dlg:pw:clear
    else
        alert( "Jelszó eltér" )
    end
    
    return NIL
 


****************************************************************************
 