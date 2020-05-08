

*********************************************************************************************
function computername() 
local name:=termgetenv("COMPUTERNAME")
    if( name==NIL )
        name:=""
    end
    return name


*********************************************************************************************
function workstatid()
local name:=termgetenv("WORKSTATID")
    if( name==NIL )
        name:=""
    end
    return name

*********************************************************************************************
