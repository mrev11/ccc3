


function main()
local con
local tab
local seq
local n,row,err

    set date format 'yyyy-mm-dd'

    con:=sql2.db2.sqlconnectionNew("@sample")
    con:list
    ? con:version


    tab:=proba.tableEntityNew(con)
    //tab:list
    
    begin
        tab:drop
    recover err <sqlerror>
        ? err:description
    end
    tab:create
    
    seq:=con:sqlsequenceNew("konto.seqproba")
    seq:start:=1001
    begin 
        seq:drop
    recover err <sqlerror>
        ? err:description
    end
    seq:create

    
    for n:=1 to 100
    
        row:=tab:instance
        row:szamlaszam  :=n::str::alltrim::padl(18,"0")+"abcdef"
        row:devnem      :="HUF"
        /*
        */        

        row:nev         := (asc('a')+n%26)::chr::replicate( 20 )
        row:egyenleg    :=n+n/10
        row:sorszam     :=seq:nextval
        row:tulmenflag  :=n%3==0
        row:konyvkelt   :=date()+n
        row:megjegyzes  :="XXXXXXX"+str(n)+replicate("x",10)+replicate("y",10)+replicate("z",10)
        row:insert
        
        if( n%10==0  )
            con:sqlcommit
            //row:insert
        end
        
    next
    
    con:sqlcommit
    ?