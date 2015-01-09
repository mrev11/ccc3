


function main()
local con
local tab
local rowset
local n:=0,row

    set date format 'yyyy-mm-dd'

    con:=sql2.mysql.sqlconnectionNew(":konto:konto:konto") //host,user,pw,db

    tab:=proba.tableEntityNew(con)

    rowset:=tab:select_tf({.t.})
    while( NIL!=(row:=rowset:next) )
        ? row:szamlaszam, ;
          row:devnem, ;
          row:nev, ;
          row:egyenleg::str(10,2), ;
          row:sorszam, ;
          row:tulmenflag, ;
          row:konyvkelt, ;
          row:megjegyzes
    end
    rowset:close
    ?


    rowset:=tab:select_tf({.f.})
    while( NIL!=(row:=rowset:next) )
        ? row:szamlaszam, ;
          row:devnem, ;
          row:nev, ;
          row:egyenleg::str(10,2), ;
          row:sorszam, ;
          row:tulmenflag, ;
          row:konyvkelt, ;
          row:megjegyzes
    end
    rowset:close
    ?

    rowset:=tab:select_bl({10})
    while( NIL!=(row:=rowset:next) )
        ? row:szamlaszam, ;
          row:devnem, ;
          row:nev, ;
          row:egyenleg::str(10,2), ;
          row:sorszam, ;
          row:tulmenflag, ;
          row:konyvkelt, ;
          row:megjegyzes
    end
    rowset:close
    ?
    