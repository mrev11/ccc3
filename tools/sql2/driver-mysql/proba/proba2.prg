


function main()

local con,q,n

    set date format 'yyyy-mm-dd'

    con:=sql2.mysql.sqlconnectionNew(":konto:konto:konto") //host,user,pw,db
    con:list
    ? con:version
    ? sql2.mysql._my_character_set_name(con:__conhandle__)  // latin1!
    


    q:=con:sqlqueryNew("select * from proba")
    ? q:__selectlist__
    
    while(q:next)
        ?   q:getchar(1),;
            q:getchar(2),;
            q:getchar(3),;
            q:getnumber(4)::str(10,2),;
            q:getnumber(5),;
            q:getlogical(6),;
            q:getdate(7),;
            q:getbinary(8)
    end

    con:sqldisconnect


    ?
    


//1 szamla        C   
//2 devnem        C
//3 megnevezes    C
//4 osszeg        N
//5 sorszam       N
//6 tulmenflag    L
//7 konyvkelt     D
//8 megjegyzes    M
