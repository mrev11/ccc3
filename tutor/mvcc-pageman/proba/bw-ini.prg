
//ezt üres adatbázisba




function main()

local con:=pageman.dbconnectionNew("dbproba")
local page,n



    for n:=1 to 26
        page:=con:append
        page:content:=if( n%3==0, "BLACK", "WHITE" )
    next
    con:commit
    

