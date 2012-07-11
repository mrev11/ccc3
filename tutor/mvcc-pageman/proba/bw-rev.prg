

function main(arg)

local con:=pageman.dbconnectionNew("dbproba")
local n,pgid,page,x



    for n:=1 to 26
        pgid:=pageman.num2hex(n,16)
        page:=con:read(pgid)
        ? pgid, ":",x:=page:content::bin2str
        
        if( arg=="B" )

            if( "WHITE"$x )
                ??  "->", page:content:="BLACK"
            else
                //nem változtat
            end
        end
        
        if( arg=="W" )

            if( "BLACK"$x )
                ??  "->", page:content:="WHITE"
            else
                //nem változtat
            end
        end
        
        
        inkey(0.1)
    next
    con:commit
    

