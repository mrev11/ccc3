
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

//manuális lock teszt: 
//testdata.a.value-t arg-gal növeli
//(első rekord)

#ifdef EMLEKEZTETO
    Elindítjuk:

    konkur-lock.exe  1000 &
    konkur-lock.exe 10000 &
    
    Az első processz 1000-zal, a második 10000-rel növeli 
    a mező értékét. Ha az alkalmazás nem lockolna, akkor
    az érték 1000-rel, VAGY 10000-rel módosulna, aszerint,
    hogy melyik program update-el később, noha helyesen
    az eredő egyenlegnek 1100-zal kell nőnie.
    
    Postgresben a lock-nak nem lehet timeout-ot megadni, ezért 
    az végtelen ideig vár (vagy az esetleges deadlock detektálásáig).
#endif


#include "sql.ch"


function main(arg)

local con,tbl,e1

    set date format "yyyy-mm-dd"
 
    con:=sqlConnect()  

    tbl:=testdata.a.tableEntityNew(con)

    e1:=tbl:find(1,LOCK_WAIT) //kulcs=1, lockflag=LOCK_WAIT
    e1:value+=val(arg)
    e1:update
    alert(arg+str(e1:value))
    con:sqlcommit  //elengedi a lockot

    con:sqldisconnect

    return NIL
 
