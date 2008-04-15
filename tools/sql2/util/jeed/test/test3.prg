
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
local tds:="tds"+dirsep()+"szlmegj.tds"
local dom
local table
local viewer
local rowset
local row

    set date format "yyyy-mm-dd"

    dom:=tdsutil.tds2dom(tds)
    table:=tdsutil.dom2tabent(con,dom)    


    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})

    viewer:=jtentityeditorNew(table,.t.)//(table,editflag)
    viewer:show("select",,.t.) //(select,{bind},top)
    
    ?
