

function main(jsonfile, indent)
local json:=json_parser(memoread(jsonfile))
    json_print( json, indent=="indent")

