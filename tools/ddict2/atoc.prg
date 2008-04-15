
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

************************************************************************
#include "error.ch"

************************************************************************
function ctoa(cvar)
local avar:={}
local c:=1, type, vlen, v

    while( c<=len(cvar) )
        type:=substr(cvar, c, 1); c+=1
        vlen:=val(substr(cvar, c, 3)); c+=3
        v:=substr(cvar, c, vlen); c+=vlen

        if( type=="U" )
            aadd(avar, NIL)
        elseif(type=="C")
            aadd(avar, v)
        elseif(type=="N")
            aadd(avar, val(v))
        elseif(type=="D")
            aadd(avar, ctod(v))
        elseif(type=="L")
            aadd(avar, v=="T")
        elseif(type=="A")
            aadd(avar, ctoa(v) )
        end
    end
    return avar


************************************************************************
function atoc(avar)
local cvar:=""
local n, v, type
local err

    for n:=1 to len(avar)
        v:=avar[n]

        if( (type:=valtype(v))=="U" )
            cvar+="U"+str(0,3,0)
        elseif(type=="C")
            cvar+="C"+str(len(v),3,0)+v
        elseif(type=="N")
            v:=str(v)
            cvar+="N"+str(len(v),3,0)+v
        elseif(type=="D")
            v:=dtoc(v)
            cvar+="D"+str(len(v),3,0)+v
        elseif(type=="L")
            v:=if(v,"T","F")
            cvar+="L"+str(len(v),3,0)+v
        elseif(type=="A")
            v:=atoc(v)
            cvar+="A"+str(len(v),3,0)+v
        else 
            err:=errorNew()
            err:severity:=ES_ERROR
            err:subSystem:="Array conversion"
            err:description:="Wrong type "+type
            err:operation:="ATOC"
            break(err)
        end
    next    
    return cvar

************************************************************************
