

function main()

local fd,map

    fd:=fopen("shared")
    map:=filemap.open(fd)
    fclose(fd)
    
    while(.t.)
        sleep(100)
        ? map[14..21]
    end
