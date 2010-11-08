


function main()

local fd,map,t

    fd:=fcreate("shared")
    chsize(fd,64)
    map:=filemap.open(fd,"rw")
    fclose(fd)
    
    while(.t.)
        sleep(100)
        t:=a"xxx"+time()::str2bin+a"yyy"
        xvputbin(map,10,len(t),t)
        //filemap.sync(map)
    end
