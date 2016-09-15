
#include "inkey.ch"
#include "savex.ch"


**************************************************************************************
function play(brw)

local pplugin:=getenv("PPLUGIN")

local arr:=brwArray(brw)
local pos:=brwArrayPos(brw)
local mfile:=arr[pos][IDX_FILE]
local pp,buf:=bin(0)
local key,esc:=.f.

    if( empty(pplugin) )
        return NIL
    end

    while( !esc .and. pos<=len(arr) )

        pos:=brwArrayPos(brw)
        mfile:=arr[pos][IDX_FILE]

        pp:=child({pplugin,mfile}) //{pr,pw}
        while(  1==fread(pp[1],@buf,1) )
            ?? buf
            if( (key:=inkey())!=0 )
                fwrite(pp[2],bin(key),1)
                if( key==K_ESC )
                    esc:=.t.
                end
            end
        end
        fclose(pp[1])
        fclose(pp[2])

        zombi()

        if( !esc .and. pos<len(arr) )
            brw:down
            brw:stabilize 
            brwHighlight(brw)
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
