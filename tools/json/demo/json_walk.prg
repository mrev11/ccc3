
// demó:  így lehet kiszedni az adatokat egy json objektumból

******************************************************************************************
function main(jsonfile:="credit_transfer_json")

local json:=json_parser(memoread(jsonfile))
local root:="cstmrCdtTrf"
local codeblk:={|p,v|leaf(p,v)}
    json_walk(json,root,codeblk)
    ?


******************************************************************************************
static function leaf(path,value)
    ? path, "-->", value


******************************************************************************************
