
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

//mutatja, hogy a commit/rollback
//automatikusan lezárja a query-t,
//ezért a fetchelés hamarabb befejeződik,
//mint ahány sor van
//(a statement handle-k nem szaporodnak fel)


#include "sql.ch"

function main(db)   //db: P,M,O,D,L.
local con,query,n,e

    set date format 'yyyy-mm-dd'

    if( db$'M')
        con:=sql2.mysql.sqlconnectionNew() 
    elseif( db$'P')
        con:=sql2.postgres.sqlconnectionNew() 
    elseif( db$'D')
        con:=sql2.db2.sqlconnectionNew() 
    elseif( db$'O')
        con:=sql2.oracle.sqlconnectionNew() 
    elseif( db$'L')
        con:=sql2.sqlite3.sqlconnectionNew() 
    end
    ? con:version

    query:=con:sqlqueryNew("select count(1) from konto.proba")
    while( query:next )
        ? "rowcount", query:getchar(1)
    end
    query:close




    query:=con:sqlqueryNew("select * from konto.proba order by szamla")
    ? query:__selectlist__
    n:=0    
    while( query:next )
        ? ++n, query:getchar(1),query:getchar(2),query:getchar(3)
        if( n%5==0 )
            ? "commit"
            //con:sqlcommit
            forced_tranend({||con:sqlcommit})
        end
    end
    query:close

    ?

    query:=con:sqlqueryNew("select * from konto.proba order by szamla")
    n:=0    
    while( query:next )
        ? ++n, query:getchar(1),query:getchar(2),query:getchar(3)
        if( n%5==0 )
            ? "rollback"
            //con:sqlrollback
            forced_tranend({||con:sqlrollback})
        end
    end
    query:close

    con:sqldisconnect
    




static function forced_tranend(blk)
local err
    begin
        eval(blk)

        //A rollback (commit) lezár
        //minden függőben evő queryt és rowsetet,
        //és ha volt mit lezárni, kivételt dob,
        //vagyis a tranzakcióhatárokon nem lehet
        //feldolgozás alatt álló query és rowset.

    recover err <sqlerror>
        ? err:description

        //most már nincs függő query/rowset
        //tehát lehet rollbackelni

        eval(blk)
    end







