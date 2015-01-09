


function main()
local con
local tab
local rowset
local n:=0,row

    set date format 'yyyy-mm-dd'

    con:=sql2.mysql.sqlconnectionNew(":konto:konto:konto") //host,user,pw,db
    con:list
    ? con:version


    tab:=proba.tableEntityNew(con)
    rowset:=tab:select
    while( NIL!=(row:=rowset:next) )
        if( "rr"$row:nev  )
            row:nev::=alltrim+"!"
            row:update
        elseif( "ss"$row:nev  )
            row:delete
        end
    end
    
    con:sqlcommit


    ?