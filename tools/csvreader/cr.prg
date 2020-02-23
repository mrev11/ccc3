

function main(fspec:="a.csv")

local text

    text:=memoread(fspec,.t.)
    text::=strtran( x"0a",x"0d0a" )
    memowrit(fspec,text)
