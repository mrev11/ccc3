

// ir egy gz fajlba (tomorit)

#include "fileio.ch"


function main(fspec)

local map:=memoread(fspec,.t.)
local offs:=1,incr:=128

local fd:=fopen(fspec+".gz",FO_CREATE+FO_TRUNCATE+FO_WRITE)
local gzd:=zlib.gzdopen(fd,"wb6")

    while( offs<=len(map) )
        zlib.gzwrite(gzd,map::substr(offs,incr))
        offs+=incr
    end

    zlib.gzclose(gzd)

    // fd-t nem kell kulon lezarni

