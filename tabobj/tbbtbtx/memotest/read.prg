
#include "table.ch"


******************************************************************************************
function main()
local proba:=tabobj.probaNew()
local x,y

    set dosconv fileshare

    proba:open

    while( 27!=inkey(0.1))
        proba:gotop
        while( !proba:eof )
            x:=proba:dbmchr
            y:=proba:dbmbin
            proba:skip
        end
        ?? "."
    end

    proba:close

******************************************************************************************
