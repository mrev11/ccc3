
#include "inkey.ch"
#include "sql.ch"

***********************************************************************************************
static function connect()
local con
local dbchoice:=memoread("DBCHOICE")::alltrim[1]

    if( dbchoice=="O" )
        con:=sql2.oracle.sqlconnectionNew()
        con:sqlIsolationLevel(ISOL_SERIALIZABLE,.t.)  //session

    elseif( dbchoice=="P" )
        con:=sql2.postgres.sqlconnectionNew()
        con:sqlIsolationLevel(ISOL_SERIALIZABLE,.t.)  //session

    elseif( dbchoice=="L" )
        con:=sql2.sqlite3.sqlconnectionNew()  // "db1:db1=konto"
        con:sqlIsolationLevel(ISOL_SERIALIZABLE,.t.)  //hatástalan
    end
    
    ? con:version

    return con


***********************************************************************************************
function main()

local con,tab,row,n

    set date format "yyyy-mm-dd"
    
    con:=connect()
    
    
    tab:=proba.tableEntityNew(con)
    
    begin
        tab:create
    end
    tab:zap
    
    for n:=0 to 9
        row:=tab:instance
        row:szamlaszam :=replicate(chr(asc("0")+n),24)
        row:devnem     :="HUF"
        row:nev        :=if( n%3==0,"BLACK","WHITE")
        row:insert
    next

    con:sqlcommit


***********************************************************************************************
