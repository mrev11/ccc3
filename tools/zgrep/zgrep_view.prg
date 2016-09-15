
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

*****************************************************************************
function view(b,search,replace)

local a:=brwArray(b)
local p:=brwArrayPos(b)
local x:=split(a[p][1],":")
local fspec:=x[1]
local line:=x[2]
local cmd:="z.exe '"+fspec::strtran("'","\'")+"'"  //"z" nem jo!
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
