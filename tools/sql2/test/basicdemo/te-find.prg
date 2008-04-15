
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

//find változatai


function main()

local con,tableentity
local rowset,e0,e1,e2,key

    set date format "yyyy-mm-dd"
    set printer to log-te-find
    set printer on
 
    con:=sqlConnect()  

    tableentity:=proba.tableEntityNew(con)
    
    rowset:=tableentity:select
    
    e1:=rowset:next
    e1:=rowset:next //egy tetszőleges sor
    rowset:close
    e1:show
    ?

    //1. alternatíva
    //key:={e1:szamlaszam,e1:devnem}     //1a)
    //key:=tableentity:getprimarykey(e1) //1b)
    key:=e1:getprimarykey                //1c)
    e2:=tableentity:find(key)            //kulcsra keres
    e2:show
    ?

    //2. alternatíva
    e0:=tableentity:instance           //üres rowentity
    e0:szamlaszam:=e1:szamlaszam       //kulcsmező kitöltve
    e0:devnem:=e1:devnem               //kulcsmező kitöltve
    e2:=tableentity:find(e0)           //mintára keres
    e2:show
    ?

    //3. alternatíva
    e0:=tableentity:instance
    e0:szamlaszam:=e1:szamlaszam
    e0:devnem:=e1:devnem
    e2:=e0:find                        //mintára keres (mint az előbb)
    e2:show
    ?

    //mindegyik :show ugyanazokat az adatokat mutatja
    //noha e0, e1, e2 különböző objektumok (nem egymás referenciái)

    con:sqldisconnect

    return NIL
 
    