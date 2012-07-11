
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
