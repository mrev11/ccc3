
#define FILEMAP

************************************************************************************
function main(fspec:="a.csv")

local text,fd
local reader
local record,i

    set printer to log-demo
    set printer on

#ifdef FILEMAP
    fd:=fopen(fspec)
    text:=filemap.open(fd)
    fclose(fd)
#else
    text:=memoread(fspec)
#endif

    reader:=csvreaderNew(text,";")

    while( !empty( record:=reader:nextrecord ) )

        ? '----------------------------'
        for i:=1 to len(record)
            ? space(2*(i-1)),a'['+record[i]+a']'
        next
    end  
    ? '----------------------------'

    reader:free

#ifdef FILEMAP
    filemap.close(text)
#endif

    ?

************************************************************************************
