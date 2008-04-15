
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
//jtbrowse (array) 
//a browse előre megjelenítve

#include "icons.ch"
#include "directry.ch"
 
****************************************************************************
function main()

    ? "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
    ? argv()
    ? "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
    
    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated")})
 
    msgloop( makedlg("Demó DIALOG")  )

    return NIL


****************************************************************************
function msgloop(dlg)
local msg

    dlg:show  
    
    //mivel a kontrollok nem attribútumai a dialognak,
    //azért csak név szerinti kereséssel lehet őket megtalálni

    dlg:var:table:pagefirst
 

    while( NIL!=(msg:=dlg:getmessage) ) 

        // az itteni funkciók a kontrollok 
        // blockjaiban is lehetnének (pl. meuitem4)
        
        if( msg=="x"  ) //x button
            quit
 
        elseif( msg=="ok"  ) //ok button
            dlg:close
            

        elseif( msg=="menuitem1"  ) 
            ? "alert:", alert("Van, aki forrón szereti!",{"Válasz-1","Válasz-22","Válasz-333"})

        elseif( msg=="menuitem3"  ) 
            msgloop( makedlg(dlg:caption+"@") )

        end
    end
    return NIL


****************************************************************************
function makedlg( caption  )

local dlg
local tbar, ok, x 
local table
local status

    //sleep(3000)
 
    dlg:=jtdialogNew(5,6,15,50) //üres dialog objektum
    dlg:name:="proba"
    dlg:layout:="vbox"
    dlg:caption:=caption+" "+dlg:dialogid 

    // menu

    dlg:add( pulldown1() ) //egy pulldown menü 
    dlg:add( pulldown3() ) //egy pulldown menü 
 

    // table
    table:=jtbrowsearrayNew()
    table:name:='table'
    table:tooltip:="öt szép szűzlány őrült írót nyúz"
    table:array(directory(fullmask()))
    table:maxrow:=15
    table:addcolumn("#row",{||table:arraypos},"@RN 9999") 
    table:addcolumn("File",F_NAME,16) 
    table:addcolumn("Size",F_SIZE,"@RN 999,999") 
    table:addcolumn("Date",F_DATE,"@RD") 
    table:addcolumn("Time",F_TIME,8) 
    table:addcolumn("Attr",F_ATTR,4) 
    
    table:colortable:={{0xff,0,0},{0,0x80,0x80},{255,200,200}} //r,gb
    table:column[1]:colorblock:={|x|{0,3}}
    table:column[2]:colorblock:={|x|color2(x)}

    dlg:add(table)


    // toolbar
    
    tbar:=table:mktoolbar() 

    tbar:additem(jthglueNew())

    ok:=jtpushNew()  
    ok:name:='ok' 
    ok:text:='OK'
    ok:tooltip:="Helptext for OK button"
    ok:icon:=ICON_MIDDLE 
    tbar:additem(ok)

    x:=jtpushNew()
    x:name:='x' 
    x:text:='Exit'
    x:tooltip:="Helptext for Exit button"
    x:icon:=ICON_EXIT 
    x:escape:=.t.  //nem kell ellenőrizni a kitöltést
    x:mnemonic:="X"
    tbar:additem(x)
 
    dlg:add(tbar)
 
    // status line

    status:=jtpanelNew()
    status:additem( jtlabelNew(,,,,"XXXX") )
    status:additem( jthglueNew() )
    status:additem( jtlabelNew(,,,,"QWERTY") )
    status:additem( jthglueNew() )
    status:additem( jtlabelNew(,,,,"Próba szerencse: 2002.08.20") )

    dlg:add(status)
 

    dlg:varinst("main2_demo_dialog")
 
    return dlg


****************************************************************************
function color2(x)
    if( ".prg"$x )
        return {1,0}
    elseif( ".exe"$x )
        return {2,0}
    end
    return NIL

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
