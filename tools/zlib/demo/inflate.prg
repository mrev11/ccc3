
#include "fileio.ch"


******************************************************************************************
function main(fspec)

local fdout:=fopen("out",FO_CREATE+FO_TRUNCATE+FO_WRITE)
local fdin:=fopen(fspec,FO_READ)
local map:=filemap.open(fdin)
local offs:=1,incr:=4096,part,chunk
local strm

    fclose(fdin)

    strm:=zlib.inflateinit2()
    while( offs<=len(map) )
        part:=map::substr(offs,incr)
        chunk:=zlib.inflate(strm,part)
        fwrite(fdout,chunk)
        offs+=incr
    end

    filemap.close(map)
    fclose(fdout)


******************************************************************************************
