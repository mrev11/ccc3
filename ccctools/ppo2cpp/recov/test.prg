
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

function main(arg)

local e,x

    if( arg!=NIL )
        x:=mkexception(arg)
    end

    begin

        ? "MAIN-1"
        hopp(x)
        ? "MAIN-2"

    recover  e err2New()
        ? "rec2", e:classname

    recover  e err1New()
        ? "rec1", e:classname

    recover  e errorNew()
        ? "rec0", e:classname
    
    recover using e
        ? "recover any error", e

    end {||qout("BLOKK-MAIN")}
    ?
    return NIL


function hopp(x)
local e

    begin
        ? "HOPP-1"
        reccs(x)
        ? "HOPP-2"

    recover  e  {}
        ? "rec5 (array)", e[1]

    recover  e  ""
        ? "rec4 (string)", upper(e)

    recover  e  err3New()
        ? "rec3", e:classname

    end  {||qout("BLOKK-HOPP")}
    return NIL


*****************************************************************************
function reccs(x)

local e

    begin
        ? "RECCS-1"
        if(x!=NIL)
            break(x)
        end
        ? "RECCS-2"

    recover  e  {||NIL}
        ? "rec7 (blokk)", eval(e,"próba szerencse")

    recover  e 0
        ? "rec6 (szám)", e+1

    end {||qout("BLOKK-RECCS")}
    return NIL

*****************************************************************************
function mkexception(arg)
local x

    if( arg=="0" )
        x:=errorNew()
        x:operation:="error"
        x:description:="teszt hiba"

    elseif( arg=="1" )
        x:=err1New()
        x:operation:="err1"
        x:description:="teszt hiba"

    elseif( arg=="2" )
        x:=err2New()
        x:operation:="err2"
        x:description:="teszt hiba"

    elseif( arg=="3" )
        x:=err3New()
        x:operation:="err3"
        x:description:="teszt hiba"

    elseif( arg=="4" )
        x:="text-hiba"

    elseif( arg=="5" )
        x:={"ARRAY-HIBA"}

    elseif( arg=="6" )
        x:=100

    elseif( arg=="7" )
        x:={|p|upper(p)}
    
    else
        x:=.t.
    end
    
    return x

*****************************************************************************
