
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

//Demonstrálja 
//  a tds-ből dinanikusan felszedett tableentity használatát,
//  a jtentityeditor használatát programból.

function main()

local con:=sqlconnect()
local tds:="tds"+dirsep()+"entity.konto.szla_kamjut.tds"
local dom
local table
local viewer
local rowset
local row

    set date format "yyyy-mm-dd"

    dom:=tdsutil.tds2dom(tds)
    table:=tdsutil.dom2tabent(con,dom)    
    //table:list

    rowset:=table:select_egyenleg({"11300081%",10000000})
    while( (row:=rowset:next)!=NIL  )
        ? row:szamlaszam, row:nev, transform(row:egyenleg,"999,999,999,999.99")
    end

    //jtencoding("ISO-8859-1") //default
    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})

    viewer:=jtentityeditorNew(table)

    //viewer:show()
    //viewer:show("select",,.t.)
    viewer:show("select_egyenleg",{"11300081%",10000000},.t.)
    //viewer:show("select_szamla",{"11300081%"},.t.)

    ?
