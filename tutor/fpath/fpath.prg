
// megkeres egy filét a PATH-ban
// vagy csak kiírja a PATH-t

function main(fname)

local path:=getenv("PATH")::split(pathsep()),n

    for n:=1 to len(path)
    
        if( empty(path[n]) )
            loop
        end

        if( path[n][1]=='"' )
            path[n]:=path[n][2..len(path[n])-1]
        end

        if( fname==NIL )
            ? path[n]
        else    
            if( path[n]::right(1)!=dirsep() )
                path[n]+=dirsep()
            end
            if( file(path[n]+fname) )
                ? path[n]+fname
            end
        end
    next
    ? 
    
