
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
    cls
    set date format to "yyyy/mm/dd"
    demo( {|g|load(g)},{|g|readmodal(g)},{|g|store(g)})
    return NIL
     

#include "demo.say"

********************************************************************
static function load(getlist)     

    //string demo
    g_s:picture:="@! "+replicate("N",len(g_s:varget()) )
    g_s:varput("QWERTY")
    g_s:postblock:={|g| 1==alert("Ezt akartad: "+;
                        alltrim(g:varget())+"?",{"Igen","Nem"})}

    //numeric demo
    g_n:picture:="@R 99.9999"
    g_n:varput(3.1415)

    //date demo
    g_d:varput(date())

    //logical demo
    g_l:picture:="L"
    g_l:varput(.t.)

    aeval(getlist,{|g|g:display()})                          
    return NIL
    
********************************************************************
static function store(getlist)    
local result:=.f.
    if( 1==alert("Minden rendben?",{"Igen","Nem"}) )
        ? "String  :", g_s:varget()
        ? "Numeric :", g_n:varget()
        ? "Date    :", g_d:varget()
        ? "Logical :", g_l:varget()
        result:=.t.
    end
    return result
    

********************************************************************

