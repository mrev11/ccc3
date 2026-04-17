

function main( jsonfile )

local jsonstr:=memoread(jsonfile,.t.)
local json:=json_parser(jsonstr)

    jsonstr:=json_tostr(json)
    ? "---------------------------"
    ? json
    ? "---------------------------"
    ? jsonstr
    ? "---------------------------"
    