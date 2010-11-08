
function main()

local fd,map

    ? fd:=fcreate("shared")
    fwrite(fd,"HOPP")
    ? fclose(fd)

    ? fd:=fopen("shared")
    map:=filemap.open(fd,"r")


    ? map                 // kiírja: HOPP
    filemap.close(map)
    ? map                 // hiba: null pointer, mert már le van zárva

