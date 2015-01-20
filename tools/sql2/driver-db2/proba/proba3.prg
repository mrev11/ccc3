


#include "sql.ch"


function main()

local con,query,fc,rc,n

    con:=sql2.db2.sqlconnectionNew("@sample")
    query:=con:sqlqueryNew("select * from employee")
    ? fc:=query:fcount
    ? query:__selectlist__

    rc:=0    
    while( query:next  )
        ? ++rc 
        for n:=1 to fc
            ?? "|  |"+query:getchar(n)
        next
    end
    query:close


    query:=con:sqlqueryNew("values nextval for seqproba")
    query:next
    ? query:getnumber(1)
    query:close



    con:sqldisconnect
    
    
/*
    stmidx:=sql2.db2._db2_execdirect(con,"values nextval for seqproba")
    ? rc:=sql2.db2._db2_retcode(stmidx)
    if( rc!=0 )
        err:=sqlerrorNew()
        sql2.db2._db2_getdiagrec(err,stmidx)
        break(err)
    end


    for n:=1 to 5
        ? sql2.db2._db2_fetch(stmidx)
        ?? sql2.db2._db2_getdata(stmidx,1)
    next


    sql2.db2._db2_closestatement(stmidx)
*/    
    
    ?
