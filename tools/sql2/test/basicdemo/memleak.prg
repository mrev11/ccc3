
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

//Ellenőrzi, hogy a rowset-ek nem vesztenek-e memóriát.
//Mutatja, hogy a 9iR2 kliens könyvtár eszi a memóriát.
//A 8.0.4 és 10g változatok kliens könyvtára jó.

//AMD-64-en az Oracle 10g kliens fogyasztja a memóriát.
//AMD-64-en a Potgres 7.4.5 kliens nem fogyasztja a memóriát.
//Tehát a hiba nem lehet az Oracle kliensprogram Flex részében,
//ami az Oracle és a Postgres esetében ugyanaz.

//Megjegyzés:
//AMD-64-es Ubuntura nincs 64-bites Oracle kliens,
//de a SuSE-ra szánt 64-bites Oracle csomagból sikerült 
//kiszedni a minimális működéshez elegendő könyvtárakat
//(de pl. sqlplus már nincs).


******************************************************************************
function main()

local con,tabent
local rowset,e1,key
local sec0:=seconds()
local sec1:=seconds()
local cnt:=0

    set date format "yyyy-mm-dd"

    thread_create({||gcthread()}) //folyamatos szemétgyűjtés

    con:=sqlConnect()  

    tabent:=testdata.a.tableEntityNew(con)

    rowset:=tabent:select
    e1:=rowset:next
    e1:=rowset:next //egy tetszőleges sor
    rowset:close
    e1:show

    key:=e1:getprimarykey

    while(.t.)
        e1:=tabent:find(key)
        //e1:show

        ++cnt
        if( seconds()>sec1 )
            sec1:=seconds()
            ? cnt, int(cnt/(seconds()-sec0))
        end
    end

    return NIL
 

******************************************************************************
static function gcthread()
    while(.t.)
        gc()
        sleep(100)
    end
    return NIL

******************************************************************************


    