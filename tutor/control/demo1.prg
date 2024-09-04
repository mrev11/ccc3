
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

#include "control.say"
 

******************************************************************************
function main()
    control({|g|load(g)},{|g|readmodal(g)},{|g|store(g)},10,10)


******************************************************************************
static function load(getlist)

local g1:={}
local g2:={}

    g_a:addto(g1)
    g_b:addto(g1)
    g_c:addto(g1)   ;g_c:varput(.t.)
    g_d:addto(g1)

    g_e:addto(g2)
    g_f:addto(g2)
    g_g:addto(g2)
    g_h:addto(g2)   ;g_h:varput(.t.)
    
    g_i:varput:=.t.
    g_j:varput:=.t.


    g_lst1:picture:="@S20 "+replicate("X",64)
    
    g_lst1:item("1 Van, aki forrón szereti!")
    g_lst1:item("2 Próba szerencse")
    g_lst1:item("3 Öt szép szűzlány őrült írót nyúz")
    g_lst1:item("4 Van, aki forrón szereti!")
    g_lst1:item("5 Próba szerencse")
    g_lst1:item("6 Öt szép szűzlány őrült írót nyúz")
    g_lst1:select(3)


    g_lst2:menu:=crm.orszagkod()
    g_lst2:block:={|x|g_lst2:menu[g_lst2:select(x)][1..2]}
    g_lst2:select("HU")
    g_lst2:picture:="XX"
    g_lst2:varput:="  "
  
    g_alt1:alternatives("Kutya/Macska/Nyúl")

    g_alt2:alternatives({"Magszem","Vállalk"}); g_alt2:choice("V")
    g_alt2:block:={|x|g_alt2:alternatives[g_alt2:choice(x)][1..1]}
    
    
    //g_a:postblock:={|g|if(g:varget,(alert("WRONG"),.f.),.t.)}
   
    aeval(getlist,{|g|g:display})


******************************************************************************
static function store(getlist)
local n
    for n:=1 to len(getlist)
        ? n, getlist[n]:varget::valtype, getlist[n]:name::padr(10), getlist[n]:varget
    next
    return .f.    



******************************************************************************
