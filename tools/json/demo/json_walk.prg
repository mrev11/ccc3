
// demó:  így lehet kiszedni az adatokat egy json objektumból

******************************************************************************************
function main(jsonfile:="credit_transfer_json")

local json:=json_parser(memoread(jsonfile))
local root:="cstmrCdtTrf"

local blkleaf:={|p,v|cbleaf(p,v)}
local blkelem:={|p,v|cbelem(p,v)}
local blkmemb//:={|p,v|cbmemb(p,v)}

    json_walk(json,root,blkleaf,blkelem,blkmemb)
    ?


******************************************************************************************
static function cbleaf(path,value)
    ? "VAL", path, "-->", value

static function cbelem(path,element)
    ? "e  ", path, "-->", element::oref

static function cbmemb(path,member)
    ? "m  ", path, "-->", member:name


******************************************************************************************
