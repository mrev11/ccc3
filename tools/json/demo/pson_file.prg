

// demó: egy pson fájlból felépíti a json objektumot

******************************************************************************************
function main( psonfile:="credit_transfer_pson" )
local pson:=memoread(psonfile)
local request:=pson_parser(pson)

    ? json_tostr(request,.t.)

******************************************************************************************

