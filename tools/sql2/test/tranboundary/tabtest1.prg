
//teszt tábla generálás kamu adatokkal

function main(db,recnum:="0")   //db: P,M,O,D,L.
local con,tab,row
local seq,seqval,i,e

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
    
    recnum::=val  //rekordszám

    tab:=proba.tableEntityNew(con)
    begin           
        tab:drop   
    recover e
        ? e:description
    end             
    tab:create      

    seq:=con:sqlsequenceNew("konto.seqproba")
    seq:start:=1000   
    begin             
        seq:drop      
    recover e
        ? e:description
    end               
    seq:create        
    
    for i:=1 to recnum
        seqval:=seq:nextval
        row:=tab:instance
        row:szamlaszam  := seqval::str::alltrim::padl(24,"0")
        row:devnem      := "HUF"
        row:nev         := (asc('a')+seqval%26)::chr::replicate(20)
        row:egyenleg    := seqval+seqval/10
        row:sorszam     := seqval
        row:tulmenflag  := seqval%3==0
        row:konyvkelt   := date()+seqval%100
        row:megjegyzes  := "XXXXXXX"+str(seqval)+replicate("x",10)
        row:insert
        
        if( i%1000==0  )
            con:sqlcommit
            ?? "."
        end
    next
    con:sqlcommit

    con:sqldisconnect
    
