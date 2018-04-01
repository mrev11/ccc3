
function main(lines:="200")

local x:=memoread("../filemap.cpp",.t.)::split(bin(10))
local cnt:=0,n

    set printer to log-data  additive
    set printer on
    set console off

    lines::=val

    for n:=1 to lines
        ?? n, x[1+n%len(x)], bin(13) + bin(10)
    next
    
    ?? n
    

