
//listázza az egész táblát

#include "sql.ch"

function main(db)   //db: P,M,O,D,L.
local con,tab,rowset,row

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

    tab:=proba.tableEntityNew(con)
    rowset:=tab:select_ord //összes sor
    while( NIL!=(row:=rowset:next) )
        ? row:szamlaszam, ;
          row:devnem, ;
          row:nev, ;
          row:egyenleg::str(10,2), ;
          row:sorszam, ;
          row:tulmenflag, ;
          row:konyvkelt, ;
          row:megjegyzes
          //exit  //ha csak az első fetch-ig mérünk
    end
    rowset:close

    con:sqldisconnect
