

function main(fname)
local data

    if( fname==NIL .or. !file(fname) )
        ?? "Usage: checksum.exe <fname>"
        ?
        quit
    end

    data:=memoread(fname,.t.)

    ?? crc32(data)::l2hex::upper::padl(8,'0'), len(data), fname
    ?
    