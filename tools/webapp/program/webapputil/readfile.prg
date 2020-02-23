


namespace webapp

***************************************************************************************
function readfile(ctrlid,index:=1,mode:="dataurl")

 // mode:="binary"  // "AsBinaryString"
 // mode:="text"    // "AsText"
 // mode:="dataurl" // "AsDataURL"

local code:=<<CODE>>XCODE.readfile("$CTRLID",$INDEX,"$MODE")<<CODE>>
local data

    code::=strtran("$CTRLID",ctrlid)
    code::=strtran("$INDEX",index::str::alltrim) //1-tol indexel
    code::=strtran("$MODE",mode)

    webapp.script(code)
    webapp.waitmessage("readfile",@data)
    return data:gettext
    


***************************************************************************************
    