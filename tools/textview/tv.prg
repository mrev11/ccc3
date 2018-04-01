
#include "directry.ch"

**********************************************************************************************
function main(fspec,pos)

local tv,fd,map
local d:=directory(fspec)

    if( len(d)!=1 )
        ? "Not found:", fspec
        quit
    end
    
    if( d[1][F_SIZE]<100 )
        map:=memoread(fspec,.t.) 
    else
        fd:=fopen(fspec)
        map:=filemap.open(fd)
        fclose(fd)
    end

    //wallpaper()
    //tv:=textviewNew(map,4,10,24,70)
    tv:=textviewNew(map,1) //egy sor header

    tv:headerblk:={|x|header(x,fspec)}
    tv:mskcolor:="n/330,n/222+"
    tv:txtcolor:="n/w"
    
    if( pos!=NIL )
        tv:setpos(val(pos))
    end
    
    tv:loop

    ?? tv:offset
    

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
