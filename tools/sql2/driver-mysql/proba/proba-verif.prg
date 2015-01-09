


function main()

local con,q,prev,val,n:=0

    con:=sql2.mysql.sqlconnectionNew(":konto:konto:konto") //host,user,pw,db

    q:=con:sqlqueryNew("select * from proba order by id")
    
    while(q:next)
        val:=q:getchar(1)
        //? ++n,val
        if( val==prev )
            ? "HIBA", val
        end
        prev:=val
    end

    ?
