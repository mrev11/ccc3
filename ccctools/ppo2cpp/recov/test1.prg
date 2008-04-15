
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

function main() 
    main1()


function main1()

local e:=errorNew()

//local x:=e
//local x:=123
local x:={|s|upper(s)}
//local x:="van, aki forrón szereti"
//local x:={}

    e:candefault:=.t.
  
    begin

        ? "MAIN-1"
        hopp(x)
        ? "MAIN-2"

    recover  e ""
        ? "text", upper(e)

    recover  e {||NIL}
        ? "blokk", eval(e,"próba szerencse")

    recover  e 0
        ? "szám", e

    //recover /*using*/  e
    //    ? "RECOVER", e

    end  {||qout("BLOKK-main")}

    ? "OK"
    ?
    return NIL


function hopp(x)
    begin
        reccs(x)
    end {||qout("BLOKK-hopp"),break("hohó")}
    

function reccs(x)
    begin
        break(x)
    end {||qout("BLOKK-reccs")}
    
