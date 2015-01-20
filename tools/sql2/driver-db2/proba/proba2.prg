

#define NULL(x)   if(q:isnull(x),"null","   ")

function main()

local con,q,n

    set date format 'yyyy-mm-dd'

    con:=sql2.db2.sqlconnectionNew("@sample")
    ? con:version
    

    q:=con:sqlqueryNew("select * from konto.proba")
    ? q:__selectlist__
    
    while(q:next)
        ?   q:getchar(1),NULL(1),;
            q:getchar(2),NULL(2),;
            q:getchar(3),NULL(3),;
            q:getnumber(4)::str(10,2),NULL(4),;
            q:getnumber(5),NULL(5),;
            q:getlogical(6),NULL(6),;
            q:getdate(7),NULL(8),;
            q:getbinary(8),NULL(8)
        
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
