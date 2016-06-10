

*****************************************************************************
function view(b,search,replace)

local a:=brwArray(b)
local p:=brwArrayPos(b)
local x:=split(a[p][1],":")
local fspec:=x[1]
local line:=x[2]
local cmd:="z.exe "+fspec  //"z" nem jo!
local screen

  #ifdef _UNIX_
    if( line!=NIL )
        cmd+=" '-l"+line+"'"
    end

    if( search!=NIL )
        cmd+=" '-S"+search+"'"
    end

    if( replace!=NIL )
        cmd+=" '-p"+replace+"'" 
    end
 
    if( getenv("CCCTERM_INHERIT")=="yes" ) //2013.08.03
        brwHide(b)
        setcursor(1)
        run ( cmd )
        setcursor(0)
        brwShow(b)
    else
        //alert(cmd+"&")
        run( cmd+"&" ) //kulon ablak 
    end
    

  #else
    if( line!=NIL )
        cmd+=' "-l'+line+'"' 
    end

    if( search!=NIL )
        cmd+=' "-S'+search+'"'
    end

    if( replace!=NIL )
        cmd+=' "-p'+replace+'"'
    end
 
    run ( cmd  )

  #endif

    return .t.


*****************************************************************************
