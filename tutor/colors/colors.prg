


******************************************************************************************
function main()

local n,color
local r0,r1,r,c

    setcursor(0)
    cls

    // base colors

    for n:=0 to 15
        @ 1,4*n say "    " color color(n)
        @ 2,4*n say "    " color color(n)
    next

    // 6x6x6 color cube

    r0:=4
    r1:=0
    r:=0
    c:=0
    for n:=16 to 231
        @ r0+r1+r+0, 4*c say "    " color color(n)
        @ r0+r1+r+1, 4*c say "    " color color(n)
        c++
        if( c==18 )
            c:=0
            r++
            r1:=12*(r%2)
        end
    next

    // grey scale

    r0:=30
    r:=0
    c:=0
    for n:=232 to 255
        @ r0+r+0, 4*c say "    " color color(n)
        @ r0+r+1, 4*c say "    " color color(n)
        c++
        if( c==6 )
            c:=0
            r+=2
        end
    next

    inkey(0)



******************************************************************************************
static function color(n)
    return "w/#"+n::str::alltrim

******************************************************************************************

