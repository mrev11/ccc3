
************************************************************************************
function main(fspec:="a.csv")

local text
local reader
local field

    set printer to log-demo
    set printer on

    text:=memoread(fspec,.t.)
    reader:=csvreaderNew(text,";")

    while( NIL!=( field:=reader:nextfield ) )
        ? reader:delim, field 
    end  

    reader:free
    ?

************************************************************************************
