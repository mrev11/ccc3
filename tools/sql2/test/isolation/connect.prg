

//4 verzio: Oracle/Postgres, SERIALIZABLE/READ_COMMITTED


#include "sql.ch"


function connect()

local con

    if( getenv("ISOLATION_DB")=="O" )
        con:=sql2.oracle.sqlconnectionNew()  
    else
        con:=sql2.postgres.sqlconnectionNew()  
    end

    con:sqlisolationlevel(ISOL_SERIALIZABLE,.t.)
    //con:sqlisolationlevel(ISOL_READ_COMMITTED,.t.) //default


    ? con:classname,if(con:sqlisolationlevel==0,"READ_COMMITTED","SERIALIZABLE")

    return con


