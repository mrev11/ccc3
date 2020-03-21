
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

namespace webapp

using webapp script


***************************************************************************************
function disabled(*)
local arg:={*},n
local code:="XCODE.document.x.getElementById('ID').disabled=FLAG;"
local flag:='true'
local x:=""
    for n:=1 to len(arg)
        if( valtype(arg[n])=="L" )
            flag:=if(arg[n],'true','false')
        else
            x+=code::strtran("ID",arg[n])::strtran("FLAG",flag)
        end
    next
    script(x)
    
    //pl:
    // webapp.disabled(.t.,id1,id2,id3,.f.,id4,id5)
    //  id1,id2,id3 -> disabled
    //  id4,id5 -> enabled



***************************************************************************************
function data.pushed(*)
local arg:={*},n
local code:=<<CODE>>XCODE.document.x.getElementById('ID').setAttribute("data-pushed","FLAG");<<CODE>>
local flag:='true'
local x:=""
    for n:=1 to len(arg)
        if( valtype(arg[n])=="L" )
            flag:=if(arg[n],'true','false')
        else
            x+=code::strtran("ID",arg[n])::strtran("FLAG",flag)
        end
    next
    script(x)

    //pl:
    // webapp.data.pushed(.t.,id1,id2,id3,.f.,id4,id5)
    //  id1,id2,id3 -> data-pushed=true
    //  id4,id5 -> data-pushed=false
    

***************************************************************************************
function style.display(*)
local arg:={*},n
local code:="XCODE.document.x.getElementById('ID').style.display='MODE';"
local mode:="block"
local x:=""
    for n:=1 to len(arg)
        if( ","+arg[n]+"," $ ",inline,block,none,"  )
            mode:=arg[n]
        else
            x+=code::strtran("ID",arg[n])::strtran("MODE",mode)
        end
    next
    script(x)
    
    //pl:
    //webapp.style.display("none","editugyf","editkedv","block","errormsg")
    // editugyf, editkedv  ->  none (nem látható)
    // errormsg  ->  block (látható)


***************************************************************************************
    