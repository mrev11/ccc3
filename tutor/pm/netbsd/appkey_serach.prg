

#include "inkey.ch"
#include "search.say"

#define BR_SEARCH   1

*********************************************************************************************
function appkey_search(b,k)
    if( k==K_F3 )
        search({|gl|load(gl,b,k)},{|gl|readmodal(gl)},{|gl|find(gl,b,k)})

    elseif( k==K_SH_F3 )
        find_next(b)
        return .t.

    elseif( k==K_CTRL_F3 )
        find_prev(b)
        return .t.
    end

*********************************************************************************************
static function load(getlist,b,k)
    g_search:picture:="@K "+replicate("X",len(g_search:varget))
    g_search:varput(brwSlot(b,BR_SEARCH))
    g_search:display

*********************************************************************************************
static function find(getlist,b,k)
local arr:=brwArray(b)
local ss:=g_search:varget::alltrim,n
    brwSlot(b,BR_SEARCH,ss)
    if( !empty(ss) )
        for n:=1 to len(arr)
            if( ss$arr[n][1] )
                brwStabilize(b)
                brwArrayPos(b,n)
                b:refreshall
                exit
            end
        next
    end
    return .t.

*********************************************************************************************
static function find_next(b)
local arr:=brwArray(b)
local ss:=brwSlot(b,BR_SEARCH),n
    if( !empty(ss) )
        for n:=brwArrayPos(b)+1 to len(arr)
            if( ss$arr[n][1] )
                brwStabilize(b)
                brwArrayPos(b,n)
                b:refreshall
                exit
            end
        next
    end

*********************************************************************************************
static function find_prev(b)
local arr:=brwArray(b)
local ss:=brwSlot(b,BR_SEARCH),n
    if( !empty(ss) )
        for n:=brwArrayPos(b)-1 to 1 step -1
            if( ss$arr[n][1] )
                brwStabilize(b)
                brwArrayPos(b,n)
                b:refreshall
                exit
            end
        next
    end

*********************************************************************************************
