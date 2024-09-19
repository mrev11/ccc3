
#define PRINT(x)    ? #x, x


function scale()
local scale,n


    scale:=" "    
    for n:=1 to 20
        scale+=str(10*n,10)
    next
    @ 0,0 say scale color "w+/n"

    scale:="0123456789"::replicate(20)::left(maxcol()+1)    
    @ 1,0 say scale color "w+/n"

    for n:=2 to maxrow()
        @ n,0 say str(n,2)+" "+replicate( chr(asc("A")+(n%26)),maxcol()-3)
    next

