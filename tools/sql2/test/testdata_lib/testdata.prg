
static function testdata.init()
local libdata:=simplehashNew()
    libdata['testdata.c']:={|c|.testdata.c.tableEntityNew(c)}
    libdata['testdata.a']:={|c|.testdata.a.tableEntityNew(c)}
    libdata['testdata.b']:={|c|.testdata.b.tableEntityNew(c)}
    return libdata

function testdata(name,conn)
static libdata:=testdata.init(),blk
    if( name==NIL )
        return libdata //hashtable
    elseif( conn==NIL )
        return libdata[name] //codeblk
    else
        blk:=libdata[name]
        if( blk!=NIL )
            return eval(blk,conn) //tableentity
        end
    end
