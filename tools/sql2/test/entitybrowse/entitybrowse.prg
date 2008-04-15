
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

//tableentity browse-olás jterminállal

//#define ALLCOLUMNS

#define  ICON_TOP        "icons/22/top.png" 
#define  ICON_DOWN       "icons/22/down.png" 
#define  ICON_EXEC       "icons/22/exec.png"  

******************************************************************************
function main()
local con

    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})

    set printer to log
    set printer on

    set date format "yyyy-mm-dd"
    con:=sqlConnect()

    msgloop( makedlg(con) )
    
    classListAll()
    
    return NIL


******************************************************************************
static function msgloop(dlg)
    dlg:show
    eval(dlg:var:top:actionblock)
    while( NIL!=dlg:getmessage )
    end
    return NIL


******************************************************************************
static function makedlg(con)

local dlg:=jtdialogNew(5,10,15,80)
local brw,bar,but

local tentity:=proba.tableEntityNew(con)

    dlg:caption:="TableEntity Browse Test" 
    dlg:layout:="vbox"

    brw:=dlg:add(jtbrowseentityNew())
    brw:name:="brw"

    #ifdef ALLCOLUMNS
        brw:addcolumns(tentity)
    #else
        //brw:addcolumn("Számlaszám",tentity:getcolumn("szamlaszam"),"@RC 99999999-NNNNNNNN-99999999")
        brw:addcolumn("Számlaszám",tentity:getcolumn("szamlaszam"),"@RC XXXXXXXX-XXXXXXXX-XXXXXXXX")
        brw:addcolumn("Megnevezés",tentity:getcolumn("nev"),30):editable:=.t.
        brw:addcolumn("Dev",tentity:getcolumn("devnem"),"@R!C AAA")
        brw:addcolumn("Könyvkelt",tentity:getcolumn("konyvkelt"),"@RD")
        brw:addcolumn("Túl",tentity:getcolumn("tulmenflag"),"@RL")
        brw:addcolumn("Egyenleg",tentity:getcolumn("egyenleg"),"@RN 999,999,999.99")
        #endif
    #endif
    
    bar:=dlg:add(jttoolbarNew())

    but:=bar:additem(jtpushNew())
    but:name:="top"
    but:icon:=ICON_TOP
    but:actionblock:={||brw:rowset:=tentity:select,brw:next}

    but:=bar:additem(jtpushNew())
    but:name:="next"
    but:icon:=ICON_DOWN
    but:actionblock:={||brw:next}

    but:=bar:additem(jtpushNew())
    but:name:="list"
    but:icon:=ICON_EXEC
    but:text:="List"
    but:actionblock:={|r|r:=brw:currentrow,if(r==NIL,alert("No selected row!"),r:show)}
    
    
    dlg:varinst("x")
    return dlg


******************************************************************************
