
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
        //con:sqlIsolationLevel(ISOL_SERIALIZABLE,.t.)  //session

        con:sqlexec("set session characteristics as transaction isolation level repeatable read")
        con:sqlcommit  //az isolation level beállítás csak a következő committól kezdve hat?
        
        //  Megjegyzés
        //
        //  9.1 előtti helyzet:
        //
        //  read uncommitted  -> read committed
        //  read committed    -> read committed
        //  repeatable read   -> serializable
        //  serializable      -> serializable
        //
        //  vagyis négy helyett valójában csak két különbőző szint volt.
        //
        //  9.1-től kezdve:
        //
        //  read uncommitted  -> read committed
        //  read committed    -> read committed
        //  repeatable read   -> serializable (a korábbi értelemben)
        //  serializable      -> true serializable
        //
        //  Tehát a régi értelemben vett síma MVCC serializable működéshez 
        //  9.1-től kezdve a REPEATABLE READ szintet kell beállítani.
        //  A beállítás hatástalan, ha nem követi egy commit (furcsa).
        //
        //  Kérdés, hogy ez bekerüljön-e az sql2 interfész könyvtárba.
        //  Az Oracle-nak eleve csak true serializable módja van (az viszont hibás).
        
        
    elseif( dbchoice=="L" )
        con:=sql2.sqlite3.sqlconnectionNew()  // "db1:db1=konto"
        con:sqlIsolationLevel(ISOL_SERIALIZABLE,.t.)  //hatástalan
    end
    
    ? con:version

    return con


***********************************************************************************************
function main(arg)

local con,tab,rs,row,n

    set date format "yyyy-mm-dd"
    
    con:=connect()

    tab:=proba.tableEntityNew(con)

    if( arg=="B" .or. arg=="W" )

        rs:=tab:select
        while( NIL!=(row:=rs:next) )
            ? row:szamlaszam, row:nev
            
            if( arg=="B" )
                if( "WHITE"$row:nev )
                    ??  "->", row:nev:="BLACK"
                else
                    //nem változtat
                end
            end
        
            if( arg=="W" )
                if( "BLACK"$row:nev )
                    ??  "->", row:nev:="WHITE"
                else
                    //nem változtat
                end
            end
        
            row:update
            sleep(100)
        end

        ? "------------------------------"
    end
    
    
    if( arg=="W" )
        sleep(500)
    end

    //a repeatable read ellenőrzése


    rs:=tab:select
    while( NIL!=(row:=rs:next) )
        ? row:szamlaszam, row:nev
    end

    con:sqlcommit
    ?


***********************************************************************************************