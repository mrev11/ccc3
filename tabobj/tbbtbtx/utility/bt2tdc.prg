
#include "table.ch"


function main(btfile)

local tab
local path,name
local index,column,col
local i,n

    if( btfile::right(3)!=".bt" )
        btfile+=".bt"
    end

    tab:=tabResource(btfile)
    path:=tabPath(tab)::lower
    name:=tabFile(tab)::lower
    index:=tabIndex(tab)
    column:=tabColumn(tab)

    set printer to "_"+name+".tdc"
    set printer on
    set console off

    ?? "!table "+name
    if( !empty(path) )
        ? "!path ",path::left(len(path)-1)
    end

    for i:=1 to len(index)
        ? "!index",index[i][1]::lower,index[i][2]::lower
        for n:=1 to len(index[i][3])
            col:=column[index[i][3][n]]
            ?? "",col[1]
        next
    next

    for n:=1 to len(column)
        ? "!field", column[n][1]::padr(12),  ; // name
                    column[n][2],            ; // type
                    column[n][3]::str(3),    ; // width
                    column[n][4]::str(2)       // decimal
    next
    ?


