
******************************************************************************************
function main()
local n,color

    set alternate to "log-ansi_rgb_h"
    set alternate on
    set console off

    ? "static char ANSI_RGB[257][3]={"

    for n:=1 to 256
        color:=ansi_colors(n)
        ? "{", color[1]::hex, ",", color[2]::hex, ",", color[3]::hex, "}, //"+str(n-1,4)
    next

    ? "{0,0,0}};"
    ? <<XXX>>

void ansi_rgb(int x, int *r, int *g, int *b)
{
    *r=ANSI_RGB[x][0];
    *g=ANSI_RGB[x][1];
    *b=ANSI_RGB[x][2];
}
<<XXX>>

******************************************************************************************
static function hex(x)
    x::=l2hex::padl(2,"0")
    return "0x"+x


******************************************************************************************
