
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

#include "inkey.ch"
#include "directry.ch"
#include "rnm.say"

*****************************************************************************
function main(fspec)
    set dosconv off
    set date format to "yyyy-mm-dd"
    rnm({|g|load(g,fspec)},{|g|readmodal(g,6)},{|g|store(g)})

*****************************************************************************
static function load(getlist,fs)

local l:=len(g_name1:varget)
local p:="@S"+alltrim(str(l))+" "+replicate("X",256) 
local d:=directory(fs,"D")

    if( len(d)!=1 )
        ? "File or directory not found:", fs
        quit
    end

    g_name1:preblock:={||.f.}
    g_date1:preblock:={||.f.}
    g_time1:preblock:={||.f.}

    g_name1:picture:=p
    g_name2:picture:=p
    g_time1:picture:="@R 99:99:99"
    g_time2:picture:="@R 99:99:99"

    g_name1:varput(fs)
    g_name2:varput(fs)
    g_date1:varput(d[1][F_DATE])
    g_date2:varput(d[1][F_DATE])
    g_time1:varput(d[1][F_TIME]::strtran(":",""))
    g_time2:varput(d[1][F_TIME]::strtran(":",""))

    g_date2:postblock:={|g|g:varget>=stod("19000101")}
    g_time2:postblock:={|g|timevalid(g:buffer)}

    g_name1:display
    g_name2:display
    g_date1:display
    g_date2:display
    g_time1:display
    g_time2:display

*****************************************************************************
static function store(getlist,fs)

local name1:=alltrim(g_name1:varget)
local name2:=alltrim(g_name2:varget)
local date1:=g_date1:varget
local date2:=g_date2:varget
local time1:=g_time1:varget
local time2:=g_time2:varget

    if( name1==name2 )
    elseif( !empty(getenv("WiNdIr")) )
        if( !upper(name1)==upper(name2) .and. fileexist(name2) )
            run( 'del "'+name2+'"' )
        end
        run( 'ren "'+name1+'" "'+name2+'"' )
    else
        run( 'mv  "'+name1+'" "'+name2+'"' )
    end
    
    if( date1==date2 .and. time1==time2 )
    else
        setfdati(name2,date2,transform(time2,"99:99:99")) //CA-Tools
    end
   
    return .t.
 
*****************************************************************************
 
    