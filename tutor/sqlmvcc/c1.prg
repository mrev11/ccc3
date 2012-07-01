
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
static function getkey(key) //inkey wrapper
static skey:=0
local rkey
    if( key!=NIL )
        skey:=key
    elseif( skey!=NIL )
        sleep(100)
        rkey:=skey
        skey:=NIL
    else
        rkey:=inkey(1)
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
    
    begin
        tab:create
    end

    tab:zap
    row:=tab:instance
    row:szamlaszam :='111111112222222233333333'
    row:devnem     :="HUF"
    row:nev        :="A"::replicate(10)
    row:egyenleg   :=999.99
    row:tulmenflag :=.t.
    row:konyvkelt  :=date()
    row:megjegyzes :=NIL
    row:insert
    con:sqlcommit

    while( getkey()!=K_ESC  )
        
        //most olvas egyet

        rowset:=tab:select
        row:=rowset:next
        rowset:close
        if( row==NIL )
            ? "nincs egy sor sem"
            quit
        end
        ? row:nev::alltrim

        //amit olvasott, módosítja

        if( row:nev[1]=="Z" ) //nagy Z
            row:nev:="A"::replicate(10)
        elseif( row:nev[1]=="z" ) //kis z
            row:nev:="a"::replicate(10)
        else
            row:nev:=(row:nev::asc()+1)::chr::replicate(10)
        end

        //majd megpróbálja kiírni

        begin
            row:update
            sleep(1000) //többiek szivatása
            con:sqlcommit
            ?? " ->", row:nev::alltrim
            //siker

        recover err <sqlerror>
            con:sqlrollback
            ?? " ->", err:description
            getkey(32) //következő key: várakozás nélkül 32
            //ismétel
        end

        //tranzakcióhatár
    end

    ?

***********************************************************************************************
