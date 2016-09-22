
#include "inkey.ch"
#include "savex.ch"
#include "statvar.ch"


**************************************************************************************
function play(brw)

local play:=getenv("PLAY")
local arr:=brwArray(brw)
local pos:=brwArrayPos(brw)
local pp,buf:=bin(0)
local lastkey,key
local aplay,n

    if( empty(arr) .or. empty(play) )
        return NIL
    end
   
    play::=alltrim 
    while( "  "$play )
        play::=strtran("  "," ")
    end
    if( !"%f"$play )
        play+=' %f'
    end

    while( lastkey!=K_ESC )

        aplay:=split(play," ")
        for n:=1 to len(aplay)
            aplay[n]::=strtran("%f",arr[pos][IDX_FILE])
            aplay[n]::=strtran("%w",s_work)
            aplay[n]::=strtran("%s",s_save)
        next
        pp:=child(aplay)

        while(  1==fread(pp[1],@buf,1) )
            ?? buf
            if( (key:=inkey())!=0 )
                fwrite(pp[2],bin(key),1)
                lastkey:=key
            end
        end
        fclose(pp[1])
        fclose(pp[2])

        zombi()

        brw:down
        brw:stabilize 
        brwHighlight(brw)
        
        if( pos<brwArrayPos(brw) )
            pos:=brwArrayPos(brw)
        else
            exit
        end
    end


**************************************************************************************
static function zombi()
#ifdef _UNIX_
    while( 0<waitpid(,,1) ) //1==WNOHANG (csak UNIX)
        //zombiek takarítása
    end
#endif


**************************************************************************************
