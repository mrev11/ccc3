
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

#include "box.ch"
#include "getbrowse.say"

*************************************************************************************************
function main()
    getbrowse({|g|load(g)},{|g|setcursor(1),readmodal(g)},{|g|store(g)})
    ?


*************************************************************************************************
static function store(getlist)
local n
    for n:=1 to len(getlist)
        ? getlist[n]:name, getlist[n]:varget
    next
    return .t.


*************************************************************************************************
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

    g_aa:picture:="@S10 "+replicate("X",64)
#ifdef _CCC3_
    //UTF-8 kodolas
    g_aa:item("1 Van, aki forrón szereti!")
    g_aa:item("2 Próba szerencse")
    g_aa:item("3 Öt szép szűzlány őrült írót nyúz")
    g_aa:item("4 Van, aki forrón szereti!")
    g_aa:item("5 Próba szerencse")
    g_aa:item("6 Öt szép szűzlány őrült írót nyúz")
#else
    //lehetne itt latin2 kodolas
    //de akkor CCC3-bol nezve a z.exe 
    //panaszkodna a kodolasra
    g_aa:item("1 Van, aki forron szereti!")
    g_aa:item("2 Proba szerencse")
    g_aa:item("3 Ot szep szuzlany orult irot nyuz")
    g_aa:item("4 Van, aki forron szereti!")
    g_aa:item("5 Proba szerencse")
    g_aa:item("6 Ot szep szuzlany orult irot nyuz")
#endif
    g_aa:select(3)

    g_bb:picture:="@S10 "+replicate("X",64)
    g_bb:menu:=crm.orszagkod()
    g_bb:select("HU")

    //g_brw:liststruct
    g_brw::parbrw   //getek koze illesztett browse!
    
    aeval(getlist,{|g|g:display})


*************************************************************************************************
static function parbrw(b)

local dir:=directory(getenv("CCCDIR")+"/ccclib/src/*","DH")
local c,pos:=1

    c:=tbcolumnNew("FileName",{||dir[pos][1]})
    c:picture:="XXXXXXXXXXXX"
    //c:width:=len(c:picture) //Clipper hiba!
    c:footing:="FILENAME" 
    c:colorblock:={|x|if(".prg"$x,{3,4},{1,2})}
    b:addcolumn(c)

    c:=tbcolumnNew("Size",{||dir[pos][2]})
    c:picture:="999,999"
    c:footing:="SIZE" 
    b:addcolumn(c)

    c:=tbcolumnNew("Date",{||dir[pos][3]})
    c:picture:="D"
    c:footing:="DATE" 
    b:addcolumn(c)

    c:=tbcolumnNew("Time",{||dir[pos][4]})
    c:picture:="XXXXXXXX"
    c:footing:="TIME" 
    b:addcolumn(c)

    c:=tbcolumnNew("Attr",{||dir[pos][5]})
    c:picture:="XXX"
    c:footing:="ATTR" 
    b:addcolumn(c)
 
    b:gotopblock    := {||pos:=1}
    b:gobottomblock := {||pos:=len(dir)}
    b:skipblock     := {|n,p0|p0:=pos,pos+=n,pos::=min(len(dir))::max(1),pos-p0}

    b:headsep       := B_HD+B_DS8+B_HD 
    b:footsep       := B_HS+B_SS2+B_HS 
    b:colsep        := " "+B_VS+" " 
    b:colorspec     := "w+/bg,w+/b,rg+/bg,rg+/r"
    
    b:freeze        := 1


*************************************************************************************************
    