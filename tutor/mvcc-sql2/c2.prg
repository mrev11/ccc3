
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

#include "inkey.ch"
#include "sql.ch"


***********************************************************************************************
static function getkey(key)  //inkey wrapper
static skey:=0
local rkey
    if( key!=NIL )
        skey:=key
    elseif( skey!=NIL )
        sleep(100)
        rkey:=skey
        skey:=NIL
    else
        rkey:=inkey(3)
    end    
    return rkey


***********************************************************************************************
function main()

local con,err
local tab,row,rowset
local key

    set date format "yyyy-mm-dd"
    
    con:=connect()
    
    
    tab:=proba.tableEntityNew(con)

    while( (key:=getkey())!=K_ESC )

        if( key==0 )
            //nem nyomtak semmit,
            //nincs tranzakcióhatár, 
            //ugyanabban a tranazkcióban újra végrehajtja a selectet,
            //ugyanazt kell kapnia akkor is, ha egy másik program közben változtatott!

        elseif( key==32 )

            con:sqlrollback //tranzakcióhatár

            //az új tranzakcióban a select már látja
            //az adatbázisban időközben bekövetkezett változásokat
        end
    
        //most olvas egyet
        
        rowset:=tab:select
        row:=rowset:next
        rowset:close
        if( row==NIL )
            ? "nincs egy sor sem"
            quit
        end
        ? row:nev::alltrim

        if( key!=0 .and. key!=32  ) 
            // amit olvasott, módosítja

            if( row:nev::isupper )
                row:nev::=lower  //NAGY -> kisbetű
            else
                row:nev::=upper  //kis -> NAGYBETŰ
            end

            //majd megpróbálja kiírni

            begin
                row:update
                sleep(1000) //többiek szivatása
                con:sqlcommit //tranzakcióhatár
                ?? " ->", row:nev::alltrim
                //siker

            recover err <sqlerror>
                ?? " ->", err:description
                con:sqlrollback //tranzakcióhatár
                
                //Oracle (SERIALIZABLE)
                //hiba: 'ORA-08177: can't serialize access for this transaction'
                //rollback nélkül hiába ismétlünk, nem engedi befejezni a tranzakciót
                //még akkor sem, ha a konkurens processz már kilépett
                //midenképpen végtelen ciklus lesz (Oracle=SQLite3)

                //Postgres (SERIALIZABLE)
                //hiba: 'PG-40001 could not serialize access due to concurrent update'
                //mindegy, hogy ott van-e a rollback,
                //ui. hiba esetén a Postgres magától csinál egy rollback-et

                //SQLite3
                //hiba: 'database is locked'
                //rollback nélkül hiába ismétlünk, nem engedi befejezni a tranzakciót
                //még akkor sem, ha a konkurens processz már kilépett
                //midenképpen végtelen ciklus lesz (Oracle=SQLite3)

                //ismétel 
                getkey(64) //következő key: várakozás nélkül 64
            end
        end
    end

    ?

***********************************************************************************************
