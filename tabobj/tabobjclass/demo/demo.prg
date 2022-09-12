

#include "table.ch"


function main()

local t
local col,n

    set dosconv fileshare

    t:=tabcassaNew("cassa")

    col:=t:tab_column
    for n:=1 to len(col)
        ? n, col[n]
    next
    ?

    ? t:open(OPEN_EXCLUSIVE)
    t:pack
    t:suppindex({"penztaros","cassa",{"penztaros"}})
    t:suppindex({"sorbefbiz","cassa",{"sorbefbiz"}})
    ? t:open(OPEN_SHARED)


    
    col:=t:tab_column
    for n:=1 to len(col)
        ? n, col[n]
    next
    ?

    t:liststruct  
    
    t:control("penztaros")
    t:control("sorbefbiz")
    
    t:gotop

    ? "   PÉNZTAR SZÁMALSZÁM               PÉNZTÁROS SORBEFBIZ"
    ? "-------------------------------------------------------"
    while( !t:eof )
        t:rlock
        ++t:sorbefbiz
        t:unlock
        ? t:penztar, t:szamlaszam, t:penztaros, t:sorbefbiz, t:ugyfelazon
        t:skip
    end
    
    //t:dropindex("penztaros")

    ?