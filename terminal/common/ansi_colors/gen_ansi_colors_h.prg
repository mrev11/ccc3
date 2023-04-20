

******************************************************************************************
function main()

local ansi:=ansi_colors()
local x,i
local r,g,b
local ansiidx


    set console off

    set alternate on
    set alternate to log-color

    for x:=0 to 127
        ansiidx:=colorext_to_ansi(x)
        ? x, rgbw(x), colorext_palette(x)::rgb, ansiidx-1, ansi[ansiidx]::rgb

        if( ansi[ansiidx][1]==ansi[ansiidx][2] .and.  ansi[ansiidx][1]==ansi[ansiidx][3] )
            ?? " GREY"
        end
    next
    ?

    for x:=1 to len(ansi)
        ? "ANSI", x-1, ansi[x]::rgb
    next
    ?


    set alternate to ansi_colors.h

    ? "static int ansi_colors[128]={"
    for x:=0 to 127
        if( x%8==0 )
            ?
        end
        ansiidx:=colorext_to_ansi(x)
        //? colorext_palette(x), ansi[ansiidx]
        ?? (ansiidx-1)::str(4)
        if( x<127 )
            ?? ","
        end
        
    next
    ?? "};"

    set alternate to 
    set alternate off
    set console on


    ?



******************************************************************************************
static function rgbw(x) // ccc color idex -> rgbw
local r,g,b,w

    w:=if(numand(x,1)==0," ","+")
    b:=x::numand(0b00000110)/2
    g:=x::numand(0b00011000)/8
    r:=x::numand(0b01100000)/32
    
    return r::str::alltrim+g::str::alltrim+b::str::alltrim+w


******************************************************************************************
static function rgb(rgb)
local x:=" ["

    x+=" "+rgb[1]::l2hex::padl(2,"0")
    x+=" "+rgb[2]::l2hex::padl(2,"0")
    x+=" "+rgb[3]::l2hex::padl(2,"0")
    x+=" ] "
    
    return x

******************************************************************************************
static function colorext_to_ansi(x)

static ansi:=ansi_colors()

local sum
local sumopt:=99999999
local idxopt:=0
local i,r,g,b

    {r,g,b}:=colorext_palette(x)

    if( r==g .and. r==b )
        // grey scale
        for i:=1 to ansi::len
            sum:=0.000001
            sum+=(r-ansi[i][1])*(r-ansi[i][1])
            sum+=(g-ansi[i][2])*(g-ansi[i][2])
            sum+=(b-ansi[i][3])*(b-ansi[i][3])
            sum::=sqrt
            if( sumopt>sum)
                sumopt:=sum
                idxopt:=i
            end
        next
        return idxopt
    end

    for i:=1 to ansi::len
        if( r==0 .and. ansi[i][1]!=0 )
            //kihagy
        elseif( g==0 .and. ansi[i][2]!=0 )
            //kihagy
        elseif( b==0 .and. ansi[i][3]!=0 )
            //kihagy
        else
            sum:=0.000001
            sum+=(r-ansi[i][1])*(r-ansi[i][1])
            sum+=(g-ansi[i][2])*(g-ansi[i][2])
            sum+=(b-ansi[i][3])*(b-ansi[i][3])
            sum::=sqrt
            
            if( sumopt>sum)
                sumopt:=sum
                idxopt:=i
            end
        end
    next
    return idxopt



******************************************************************************************
#ifdef NOTDEF

Az extidx szinkodolasrol:

    setcolor( "333/222+,w/n, ... " )
                   ^^^^
                   ||||
                   |||+---  +  minden osszetevot egy fokozattal megemel
                   ||+----  b  0,1,2,3
                   |+-----  g  0,1,2,3
                   +------  r  0,1,2,3

Peldaul 222+  minden osszetevoben az 5-os fokozatot jelenti,
azaz mindharom osszetevo erteke 0xa0.

              0    0+   1    1+   2    2+   3    3+
              0    1    2    3    4    5    6    7
int color[8]={0x00,0x20,0x40,0x60,0x80,0xa0,0xc0,0xff};

#endif
******************************************************************************************

