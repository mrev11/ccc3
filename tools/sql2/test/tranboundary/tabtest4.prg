
//mutatja, hogy a rollback
//automatikusan lezárja a rowsetet, 
//és ezért nem gyűlnek fel a lezáratlan statement handle-k
//annak ellenére, hogy a break miatt sosem kerül a vezérlés
//az explicit rowset:close-ra


#include "sql.ch"

function main(db)   //db: P,M,O,D,L.
local con,tab,rowset,row
local err,n,i

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


    for n:=1 to 1000
        begin
            rowset:=tab:select //összes sor
            i:=0
            while( NIL!=(row:=rowset:next) )
                ? row:szamlaszam, ;
                  row:devnem, ;
                  row:nev, ;
                  row:egyenleg::str(10,2), ;
                  row:sorszam, ;
                  row:tulmenflag, ;
                  row:konyvkelt, ;
                  row:megjegyzes
    
                if( ++i==2 )
                    break("HOPP")
                end
            end
            rowset:close

        recover err <C>
            ? err, n
            //con:sqlrollback
            forced_rollback(con)

        finally
            //rowset:close
        end
    next

    con:sqldisconnect


function forced_rollback(con)
local err
    begin
        con:sqlrollback

        //A rollback (commit) lezár
        //minden függőben evő queryt és rowsetet,
        //és ha volt mit lezárni, kivételt dob,
        //vagyis a tranzakcióhatárokon nem lehet
        //függő query és rowset.

    recover err <sqlerror>
        ? err:description

        //most már nincs függő query/rowset
        //tehát lehet rollbackelni

        con:sqlrollback
    end




