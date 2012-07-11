

function main()

local con:=dbconnectionNew("dbproba")
local pgid:=a"0"::replicate(16)
local page,n

    for n:=1 to 26
        ? pgid::=pgfield_increment
        page:=con:read(pgid)
        ?? " >> ", page:content+=str2bin(" "+time())
    next
    con:commit
    

