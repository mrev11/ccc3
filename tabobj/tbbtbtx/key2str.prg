
*********************************************************************************************
function key2str(key)

local recno:=key::right(10)
local val:=key[1..len(key)-10]::bin2str
local rcn:=recno[1..4]::bin2hex
local pgn:=recno[5..8]::bin2hex
local idx:=recno[9..10]::bin2hex
    
    return "["+rcn+"-"+pgn+"-"+idx+"] ["+val+"]"

*********************************************************************************************
