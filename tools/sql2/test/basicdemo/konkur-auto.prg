
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

//automatikus lock teszt: 
//testdata.a.value-t arg-gal növeli
//(második rekord)

#ifdef EMLEKEZTETO
    Elindítjuk:

    konkur-auto.exe  1000 &
    konkur-auto.exe 10000 &
    
    Az első processz 1000-zal, a második 10000-rel növeli 
    a mező értékét. Ha az alkalmazás nem lockolna, akkor
    az eredő egyenleg 1000-zal, VAGY 10000-rel módosulna, 
    aszerint, hogy melyik program update-el később, noha  
    helyesen az egyenlegnek 1100-zal kell nőnie.
    
    Itt nem explicit lockolással történik a konkurrencia kezelés,
    hanem beállítjuk az ISOL_SER tranzakció izolációt.
    Ekkor, ha a szerver nem tudja automatikus lockolásokkal 
    sorosítani a tranzakciót, runtime error keletkezik,
    rollback-elünk, és ismétlünk.
#endif


#include "sql.ch"


function main(arg)

local con,tbl,e1,err
local flag:=.t. //session=.t., transaction=.f.

    set date format "yyyy-mm-dd"
 
    con:=sqlConnect()
    con:sqlIsolationLevel(ISOL_SER,flag) 

    tbl:=testdata.a.tableEntityNew(con)

    while( .t. )
        begin
            e1:=tbl:find(2)  //kulcs=2, lockflag=NIL
            e1:value+=val(arg)
            e1:update
            alert(arg+str(e1:value))
            con:sqlcommit  //elengedi a lockot
            exit

        recover err <sqlserialerror>
            con:sqlrollback
            if( 2==alert(err:description,{"Retry","Quit"}) )
                break(err)
            end
        end
    end
    
    con:sqldisconnect

    return NIL
 
    