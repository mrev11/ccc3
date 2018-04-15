

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
local pos:=0,lss,tss

    text::=substr(tbeg,twid)::padr(twid)

    @ row,col SAY text COLOR color

    //kiemeli a search stringet (elhagyhato)

    while( !empty(this:searchstring) .and. ;
           0<(pos:=at(this:searchstring,this:line(n),pos+1)) )

        tss:=this:searchstring
        lss:=this:searchstring::len

        if( pos<tbeg )
            col:=0
            tss::=right(lss-tbeg+pos)::left(twid)
        else
            col:=pos-tbeg
            tss::=left(twid-col)
        end
        //? col, "["+tss+"]", color::logcolor(2)
        @ row,col SAY tss COLOR color::logcolor(2)
    end

********************************************************************************************

