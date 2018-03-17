
namespace sql2.postgres

******************************************************************************
function sqldebug(stmt)

// hasznalat
// export SQLDEBUG=on                      (mindent listaz)
// export SQLDEBUG=on:commit:rollback      (csak ezeket listazza)
// export SQLDEBUG=off                     (semmit sem listaz)
// export SQLDEBUG=off:fetch               (csak ezeket nem listazza)
// export SQLDEBUG=x                       (barmi egyeb: mindent listaz)

static debug:=getenv("SQLDEBUG")
static count:=0
local n

    if( !empty(debug) )

        if( valtype(debug)=="C" )
            debug::=split(":")
        end

        for n:=2 to len(debug)
            if( debug[n] $ stmt )
                exit
            end
        next
        
        if( debug[1]=="on" .and. 1<len(debug) .and. len(debug)<n )
            //kihagy
        elseif( debug[1]=="off" .and. (1==len(debug) .or. n<=len(debug)) )
            //kihagy
        else
            stmt:=strtran(stmt,chr(10)," ")
            stmt:=strtran(stmt,chr(13)," ")
            ? ">>>>", (++count)::str::alltrim, alltrim(stmt)
        end
    end


******************************************************************************
