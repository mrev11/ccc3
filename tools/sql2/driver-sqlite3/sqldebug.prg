
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

namespace sql2.sqlite3

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
