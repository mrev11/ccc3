
#include "page.ch"

*************************************************************************
function readpage(filnam)

local page:=array(TOT_ROW)
local pgestr:=readmask(filnam)
local pgelen:=len(pgestr)
local rowpos,n

    for n:=1 to TOT_ROW
        if( (rowpos:=(n-1)*TOT_COL*4+1)<pgelen )
            page[n]:=substr(pgestr,rowpos,TOT_COL*4)
        else
            page[n]:=emprow()
        end
    next

    return page


*************************************************************************
function emprow() // egy ures sor (szinkoddal)
static empty_row
    if( empty_row==NIL )
        empty_row:=replicate(empchr(),TOT_COL)
    end
    return empty_row


*************************************************************************
function empchr() // egy ures karakter (szinkoddal)
static empty_chr
    if( empty_chr==NIL )
        empty_chr:=screencompose(chr(32),bin(7),bin(0))
    end
    return empty_chr


*************************************************************************
