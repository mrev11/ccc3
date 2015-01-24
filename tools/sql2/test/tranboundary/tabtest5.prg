
//mutatja, hogyan lehet két connection-nel
//egy tábla minden rekordjára végrehajtani egy tranzakciót
//melynek eredménye commit vagy rollback

#include "sql.ch"

function main(db)   //db: P,M,O,D,L.

local con,tab,rowset,row
local con2,tab2,row2
local n:=0

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
    con2:=con:duplicate

    tab:=proba.tableEntityNew(con)
    tab2:=proba.tableEntityNew(con2)

    rowset:=tab:select //összes sor
    while( NIL!=(row:=rowset:next) )
        
        if(++n%1000==0)
            ?? "."
        end

        //kamu tranzakció ...
        row2:=tab2:find(row)        
        if( row2:tulmenflag )
            row2:nev::=alltrim+"*"
            row2:update
            con2:sqlcommit
            //sikeres
        else
            con2:sqlrollback
            //sikertelen
        end
    end
    rowset:close

    con:sqldisconnect
    con2:sqldisconnect
