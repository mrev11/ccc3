

********************************************************************************************
function textview.display(this)

local n
    dispbegin()
    for n:=1 to this:height
        this:displine(n)
    next 
    dispend()


********************************************************************************************
function textview.displine(this,n)

local text:=this:line(n)
local row:=this:top+n-1
local col:=this:left
local tbeg:=this:sftcol+1
local twid:=this:width
local color:=this:txtcolor

    text::=substr(tbeg,twid)::padr(twid)
    
    if( !empty(color) )
        @ row,col SAY text COLOR color
    else
        @ row,col SAY text
    end


********************************************************************************************

