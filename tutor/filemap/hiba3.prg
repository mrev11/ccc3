
function main()

local fd,map

    ? fd:=fcreate("shared")
    fwrite(fd,"HOPP")
    ? fclose(fd)

    ? fd:=fopen("shared")           //readonly
    ? map:=filemap.open(fd,"r")     //read, OK
    filemap.close(map)
    ? map:=filemap.open(fd,"rw")    //read/write, nem megy

// EACCES  13  Permission denied 
// mert az fd csak readonly, nem lehet megnyitni rw-re.

