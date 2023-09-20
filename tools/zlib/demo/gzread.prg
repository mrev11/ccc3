

// olvas egy gz fajlbol (kicsomagol)


#include "fileio.ch"

function main(fspec)

local fd:=fopen(fspec,FO_READ)
local gzd:=zlib.gzdopen(fd,"rb")
local buf:=replicate(bin(0),128),nbyte

    while( 0<(nbyte:=zlib.gzread(gzd,@buf,len(buf))) )
        ?? buf::left(nbyte)
    end

    zlib.gzclose(gzd)

    // fd-t nem kell kulon lezarni

