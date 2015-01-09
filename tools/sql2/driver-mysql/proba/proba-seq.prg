


function main(ini)

local con
local seq,val,n

    con:=sql2.mysql.sqlconnectionNew(":konto:konto:konto") //host,user,pw,db

    seq:=con:sqlsequenceNew("seqproba")
    seq:start:=1000

    if( !empty(ini) )
        begin 
            seq:drop
        end
        seq:create


        begin
            con:sqlexec("drop table proba")
        end
        con:sqlexec("create table  proba (id varchar(10) primary key)")

        quit
    end

    for n:=1 to 100
        val:=seq:nextval::str::alltrim::padl(10,"0")

        con:sqlexec("insert into  proba (id) values (:1)",{val} )
        
        
        if( n%10==0 )
            con:sqlcommit
            ?? "."
        end
    next

    con:sqlcommit


    con:sqldisconnect


    ?
    
