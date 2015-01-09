


function main()
local con
local tab
local seq
local n,row

    set date format 'yyyy-mm-dd'

    con:=sql2.mysql.sqlconnectionNew(":konto:konto:konto") //host,user,pw,db
    con:list
    ? con:version


    tab:=proba.tableEntityNew(con)
    //tab:list
    
    begin
        tab:drop
    end
    tab:create
    
    seq:=con:sqlsequenceNew("seqproba")
    seq:start:=1000
    begin 
        seq:drop
    end
    seq:create

    
    for n:=1 to 100
    
        row:=tab:instance
        row:szamlaszam  :=n::str::alltrim::padl(24,"0")
        row:devnem      :="HUF"
        row:nev         := (asc('a')+n%26)::chr::replicate( 20 )
        row:egyenleg    :=n+n/10
        row:sorszam     :=seq:nextval
        row:tulmenflag  :=n%3==0
        row:konyvkelt   :=date()+n
        row:megjegyzes  :="XXXXXXX"+str(n)+replicate("x",10)
        
        row:insert
        
        if( n%10==0  )
            con:sqlcommit
            //row:insert
        end
        
    next
    
    con:sqlcommit
    ?