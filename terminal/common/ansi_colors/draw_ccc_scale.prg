


******************************************************************************************
function main()


local r,g,b

local code
local bg
local w:=10

    settermsize(50,84)

    for r:=0 to 3 
        for g:=0 to 3
            for b:=0 to 3
                code:=""
                code+=r::str::alltrim
                code+=g::str::alltrim
                code+=b::str::alltrim
                bg:=ccccolor_to_ansicolor(code)
                

                @ (r*4+g)*3   , b*w  say padr(code,w) color fg(bg)+"/"+code
                @ (r*4+g)*3+1 , b*w  say padr(""  ,w) color fg(bg)+"/"+code
                @ (r*4+g)*3+2 , b*w  say str (bg  ,w) color fg(bg)+"/"+code
            next
        next
    next



    for r:=0 to 3 
        for g:=0 to 3
            for b:=0 to 3
                code:=""
                code+=r::str::alltrim
                code+=g::str::alltrim
                code+=b::str::alltrim
                code+="+"
                bg:=ccccolor_to_ansicolor(code)

                @ (r*4+g)*3   , b*w+41  say padr(code,w) color fg(bg)+"/"+code
                @ (r*4+g)*3+1 , b*w+41  say padr(""  ,w) color fg(bg)+"/"+code
                @ (r*4+g)*3+2 , b*w+41  say str (bg  ,w) color fg(bg)+"/"+code
            next
        next
    next

    inkey(0)
    

******************************************************************************************
static function fg(bg)
local r,g,b,intensity
    {r,g,b}:=ansi_colors(bg+1)
    intensity:=0
    intensity+=r**2
    intensity+=g**2
    intensity+=b**2
    intensity::=sqrt
    return if(intensity>220,"n","w")
    

******************************************************************************************
    