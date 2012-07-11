

function main()

local con:=dbconnectionNew("dbproba")
local page,n


    for n:=1 to 26
        page:=con:append
        page:content:=chr(asc("@")+n)+" "+time()
    next
    con:commit
    

