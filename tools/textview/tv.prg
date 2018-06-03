
#include "directry.ch"

**********************************************************************************************
function main(fspec,search)

local tv,fd,map
local hist:=history_load(fspec)[1] //{fspec,offset,search}

    if( !file(fspec:=hist[1]) )
        alert("'"+fspec+"' not found!",{"Quit"}) 
        quit
    end

    fd:=fopen(fspec)
    map:=filemap.open(fd)
    fclose(fd)

    //wallpaper()
    //tv:=textviewNew(map,4,10,24,70)
    tv:=textviewNew(map,1) //egy sor header

    tv:headerblk:={|x|header(x,fspec)}
    tv:mskcolor:="n/330,n/222+"
    tv:txtcolor:="n/w"
    
    if( !empty(hist[2]) )
        tv:setpos(hist[2])
    end

    if( search!=NIL )
       tv:searchstring:=search
    elseif( !empty(hist[3]) )
       tv:searchstring:=hist[3]
    end
 
    tv:loop
    
    history_store(fspec,tv)


**********************************************************************************************
static function wallpaper()  //a pozicionalas tesztelesehez
local n
    for n:=0 to maxrow()
        @ n,0 say replicate("X",maxcol()+1)
    next

**********************************************************************************************
static function header(x,fspec)

local hdrtxt:=""
local offset
local totlen

    offset:=x:offset
    totlen:=max(1,x:text::len) //ne legyen 0!
    
    hdrtxt+=" $FSPEC"
    hdrtxt+=" "+offset::str::alltrim+"/"+totlen::str::alltrim
    hdrtxt+=" "+(offset/totlen*100)::round(0)::str(4)+"% "
    hdrtxt::=strtran("$FSPEC",fspec::padr(x:right-x:left+7-len(hdrtxt)))

    @ x:top-1,x:left say hdrtxt color x:mskcolor


**********************************************************************************************
