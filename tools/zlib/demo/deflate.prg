

// hogyan lehet egyben es darabonkent tomoriteni?

******************************************************************************************
function main(fspec)
local x:=memoread(fspec,.t.)
    deflate_whole(x)
    deflate_chunk(x)
    ?

******************************************************************************************
static function deflate_whole(x)
    memowrit("whole.gz",zlib.deflate(x))


******************************************************************************************
static function deflate_chunk(x)

local offs:=1,incr:=4096
local part,chunk
local strm,z:=a''

    strm:=zlib.deflateinit2()
    while( offs<=len(x) )
        part:=substr(x,offs,incr)
        chunk:=zlib.deflate(strm,part)
        if( len(chunk)>0 )
            z+=chunk
            ?? "!"
        else
            ?? "."
        end
        offs+=incr
    end
    z+=zlib.deflate(strm,a'',.t.) //flush
    memowrit("chunk.gz",z)


******************************************************************************************
