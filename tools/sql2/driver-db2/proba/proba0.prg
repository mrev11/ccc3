
#include "sql.ch"


#define SQL_SUCCESS 0

function main()

local con,stm,rc
local numcols,desc,n,i
local err

    con:=sql2.db2._db2_connect("sample")
    
    
    //? sql2.db2._db2_setautocommit(con,.t.)
    //? sql2.db2._db2_setautocommit(con,.f.)
    //? sql2.db2._db2_setisolation(con,ISOL_SERIALIZABLE)
    //? sql2.db2._db2_setisolation(con,ISOL_READ_COMMITTED)


    ? "isol", stm:=sql2.db2._db2_execdirect(con,"set isolation level read committed")
    rc:=sql2.db2._db2_retcode(stm)
    if( rc!=SQL_SUCCESS )
        err:=sqlerrorNew()
        sql2.db2._db2_getdiagrec(err,stm)
        break(err)
    end

    ? "isol", stm:=sql2.db2._db2_execdirect(con,"set isolation level serializable")
    rc:=sql2.db2._db2_retcode(stm)
    if( rc!=SQL_SUCCESS )
        err:=sqlerrorNew()
        sql2.db2._db2_getdiagrec(err,stm)
        break(err)
    end


//for n:=1 to 100
    ? "tran", stm:=sql2.db2._db2_execdirect(con,"commit")
    rc:=sql2.db2._db2_retcode(stm)
    if( rc!=SQL_SUCCESS )
        err:=sqlerrorNew()
        sql2.db2._db2_getdiagrec(err,stm)
        break(err)
    end
//next    
    
    ? "tran", stm:=sql2.db2._db2_execdirect(con,"rollback")
    rc:=sql2.db2._db2_retcode(stm)
    if( rc!=SQL_SUCCESS )
        err:=sqlerrorNew()
        sql2.db2._db2_getdiagrec(err,stm)
        break(err)
    end
    

    ? "employee", stm:=sql2.db2._db2_execdirect(con,"select * from emp")
    ? "version", stm:=sql2.db2._db2_execdirect(con,"select service_level from sysibmadm.env_inst_info")

    rc:=sql2.db2._db2_retcode(stm)
    if( rc!=SQL_SUCCESS )
        err:=sqlerrorNew()
        sql2.db2._db2_getdiagrec(err,stm)
        break(err)
    end

    ? "rowcount", sql2.db2._db2_rowcount(stm) //select-nél -1!
    
    ? "numcols", numcols:=sql2.db2._db2_numresultcols(stm)

    for i:=1 to numcols
        ? i, desc:=sql2.db2._db2_describecol(stm,i)
        if(desc==NIL)
            ?? rc:=sql2.db2._db2_retcode(stm)
            err:=sqlerrorNew()
            sql2.db2._db2_getdiagrec(err,stm)
            break(err)
        end
    next
    
    
    
    n:=0
    while( (rc:=sql2.db2._db2_fetch(stm))==SQL_SUCCESS )
        n++
        ? n
        for i:=1 to numcols
            ?? a"|  |"+sql2.db2._db2_getdata(stm,i)
        next
    end
    
    ? "number of fetched rows", n


    ? "closestatement", sql2.db2._db2_closestatement(stm)
    ? "disconnect", sql2.db2._db2_disconnect(con)
    ?
    