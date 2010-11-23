


function main()

local fd
local map1,map2
local t

    fd:=fcreate("shared")
    chsize(fd,64)
    map1:=filemap.open(fd,"rw")
    fclose(fd)

    fd:=fopen("shared")
    map2:=filemap.open(fd,"r")
    fclose(fd)
    
    while(.t.)

        sleep(100)

        t:=time()::str2bin
        xvputbin(map1,7,len(t),t)  //0 based
        filemap.sync(map1)
        
        ? map2[8..15] //1 based
    end
