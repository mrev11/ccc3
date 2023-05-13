

******************************************************************************************
function ReadMask(filnam)
local x:=memoread(filnam,.t.)
    if( empty(x) )
        ? "ERROR file not found:",filnam
        ?
        quit
    end
    return compat(x)


******************************************************************************************
static function compat(x) // regi msk-k konvertalasa
local n,ch,at,fg,bg

    n:=len(x)
    x::=left(n-(n%4)) // leszedi az esetleges EOF-ot

    ch:=screenchar(x)
    at:=screen_fg(x)  // eredeti fg-k  
    fg:=a""
    bg:=a""

    for n:=1 to len(at)
        if( asc(at[n])==7 )
            // normal
            fg+=bin(7) // w
            bg+=bin(0) // n
        else
            // inverse
            fg+=bin(0) // n
            bg+=bin(7) // w
        end
    next

    return screencompose(ch,fg,bg)


******************************************************************************************
