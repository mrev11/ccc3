
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
function translate(line,cmdflg)

local rule:=token_translate(alltrim(line)) 
local ls:=rule[1], rs:=rule[2]
local n,i,name,info

    //? line, cmdflg
    //? ls
    //? rs

    //itt a markerek ábrázolása a következő: {name,type[,info]}

    for n:=1 to len(rs)
        
        if( valtype(rs[n])=="A" )

            name:=rs[n][1]
        
            for i:=1 to len(ls)
                if( valtype(ls[i])=="A" .and. ls[i][1]==name )
                    rs[n]:=rs[n][2]+i
                    exit
                end
            next

            if( i>len(ls) )
                ? "left :",rule[1]
                ? "right:",rule[2]
                error(a"Result marker not defined ["+name+a"]")
            end
        end
    next

    for n:=1 to len(ls)
        if( valtype(ls[n])=="A" )
            if( len(ls[n])>2 )
                info:=rule_if_add(ls[n][3])
                ls[n]:=ls[n][2]+info
            else
                ls[n]:=ls[n][2]
            end
        end
    next

    rule_tr_add(rule)
    
    if(cmdflg)
        aadd(rule[1],NIL) //NIL jelzi a #command-okat
    end
 
    //? "left :",rule[1]
    //? "right:",rule[2]
    //? "count:",rule[3]
    
    return NIL    
    

*****************************************************************************
 