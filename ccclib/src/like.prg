
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
function like(minta,str) //CA-tools (Csiszár Levente)

local i,j,w
local type:=valtype(str)
local qm:=if(type=="X",a"?","?")
local st:=if(type=="X",a"*","*")

    for i:=1 to len(str)

        if( substr(minta,i,1)==qm )
            //mehet
 
        elseif( substr(minta,i,1)==st )

            w:=substr(minta,i+1)

            if( len(w)==0 )
                return .t.
            end

            for j:=i to len(str)
                if( like(w,substr(str,j)) )
                    return .t.
                end
            end
            return .f.

        elseif( substr(minta,i,1)==substr(str,i,1) )
            //mehet

        else
            return .f.
        end
    end 

    if( len(str)>len(minta) )
        return .f.
    elseif( len(str)==len(minta) )
        return .t.
    end

    //a minta végén még van illeszteni való 
    //akkor illeszkedik, ha ez csupa csillag

    for i:=len(str)+1 to len(minta)
        if( !substr(minta,i,1)==st )
            return .f.
        end
    end 

    return .t.

*****************************************************************************

 