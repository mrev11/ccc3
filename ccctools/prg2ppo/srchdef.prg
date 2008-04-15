
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
function searchdefine(line)

//ez a program a #ifdef/#ifeq direktíváknak ad infót a szimbólumról
//line az #ifdef/#ifndef/#ifeq/#ifneq utáni rész, 1 vagy 2 szimbólum
//
//return érték: 
//  NIL, ha az első szimbólum nem definiált
//  .f., ha az első szimbólum definiált, de nem egyezik a másodikkal
//  .t., ha az első szimbólum definiált, és egyezik a másodikkal 

local result:=NIL
local toklist:=tokenize(alltrim(line))
local lentok:=len(toklist)
local symbol:=if(lentok>=1,toklist[1],NIL)
local value:=if(lentok>=3,toklist[3],NIL)
local rdef:=rule_df_get(),rside,rvalue,n
 
    if( symbol!=NIL .and.;
        0<(n:=ascan(rdef,{|r|r[1][1]==symbol})) ) 

        rside:=rdef[n][2]
        rvalue:=if(len(rside)>=1,rside[1],NIL)
        result:=rvalue==value
    end
    
    return result

*****************************************************************************
 