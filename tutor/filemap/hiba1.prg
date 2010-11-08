
function main()

local fd:=fopen("demo.prg"),n

    for n:=1 to 1000000
        ?? n,""
        filemap.open(fd)
    next

// A lezáratlanul hagyott map-ok fogyasztják a rendszer erőforrásait.
// A fenti példa nálam 32-biten n=65503-nál száll el ENOMEM=12="Out of memory"
// hibával (vagyis elfogy a címtér). 64-biten nehezebben fogy el a címtér,
// de lehet, hogy ott más korlátba ütközünk.


