

function plihash(v,flag)
static h:=simplehashNew()
    if( v==NIL )
        return h
    elseif( flag==NIL )
        return h[v]!=NIL
    end
    h[v]:=flag


function plxhash(v,flag)
static h:=simplehashNew()
    if( v==NIL )
        return h
    elseif( flag==NIL )
        return h[v]!=NIL
    end
    h[v]:=flag
