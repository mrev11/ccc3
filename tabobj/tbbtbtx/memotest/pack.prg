
#include "table.ch"


******************************************************************************************
function main()
local proba:=tabobj.probaNew()
    set dosconv fileshare
    proba:open(OPEN_EXCLUSIVE)
    proba:pack
    proba:close
    
******************************************************************************************
