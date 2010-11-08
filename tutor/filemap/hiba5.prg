
#include "fileio.ch"



function main()

local fd,map
local text:=a"Ötszép szűzlány őrült írót nyúz."

    fd:=fcreate("shared")
    chsize(fd,64)
    fclose(fd)

    fd:=fopen("shared",FO_READWRITE)
    //map:=filemap.open(fd,"rw")    //ezzel működne
    map:=filemap.open(fd,"r")       //readonly
    
    xvputbin(map,0,len(text),text)  //readonly -> invalid memory reference

    filemap.close(map)

// SIGSEGV invalid memory reference,
// mert a map readonly, ezért nem enged bele írni.
