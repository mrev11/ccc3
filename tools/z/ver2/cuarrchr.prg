
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

//TARTALOM  : array transzformációk
//STATUS    : általános könyvtárba kéne tenni
//            
//
//function _chr2arr(cvar)   // resource kiolvasáshoz
//function _arr2chr(avar)   // resource tároláshoz
//function _arr2str(avar)   // megjelenítéshez
//function _any2str(value)  // megjelenítéshez

*************************************************************************
function _chr2arr(cvar)

local avar:={}
local c:=1,type,v,lv

    while( c<=len(cvar) )
        type:=substr(cvar,c,1); c+=1

        if( type=="U" )                       // 'U'
            aadd(avar,NIL)

        elseif( type=="C" )                   // 'C99value' 
            lv:=val(substr(cvar,c,2)); c+=2
            v:=substr(cvar,c,lv); c+=lv
            aadd(avar,v)

        elseif( type=="S" )                   // 'S99999value'
            lv:=val(substr(cvar,c,5)); c+=5
            v:=substr(cvar,c,lv); c+=lv
            aadd(avar,v)

        elseif( type=="N" )                   // 'N99value'
            lv:=val(substr(cvar,c,2)); c+=2
            v:=substr(cvar,c,lv); c+=lv
            aadd(avar,val(v))

        elseif( type=="D" )                   // 'Dyyyymmdd'
            v:=substr(cvar,c,8); c+=8
            aadd(avar,stod(v))

        elseif( type=="L" )                   // 'LT' vagy 'LF'
            v:=substr(cvar,c,1); c+=1
            aadd(avar, v=="T")

        elseif( type=="A" )                   // 'A99999value'
            lv:=val(substr(cvar,c,5)); c+=5
            v:=substr(cvar,c,lv); c+=lv
            aadd(avar,_chr2arr(v))

        end
    end
    return avar


*************************************************************************
function _arr2chr(avar)

local cvar:=""
local n,v,lv,type
local err

    for n:=1 to len(avar)
        v:=avar[n]

        if( (type:=valtype(v))=="U" )         // 'U'
            cvar+="U"

        elseif(type=="C")                     // 'C99value' vagy 'S99999value'
            lv:=len(v)
            if( lv<100 )
                cvar+="C"+str(lv,2,0)+v
            else
                cvar+="S"+str(lv,5,0)+v
            end

        elseif(type=="N")                     // 'N99value'
            v:=alltrim(str(v))
            cvar+="N"+str(len(v),2,0)+v

        elseif(type=="D")                     // 'Dyyyymmdd'
            cvar+="D"+dtos(v)

        elseif(type=="L")                     // 'LT' vagy 'LF'
            cvar+="L"+if(v,"T","F")

        elseif(type=="A")                     // 'A99999value'
            v:=_arr2chr(v)
            cvar+="A"+str(len(v),5,0)+v

        elseif(type=="B")                     // 'U'
            cvar+="U"

        elseif(type=="O")                     // 'OOBJECT'
            cvar+="U"

        else 
            cvar+="U"

        end
    next    

    return cvar
    

*************************************************************************
function _arr2str(avar) // megjelenítéshez

local cvar:="{",n,v,type

    for n:=1 to len(avar)
        if( n>1 )
            cvar+=","
        end

        v:=avar[n]
        type:=valtype(v)

        if( type=="U" )     
            cvar+="NIL"

        elseif(type=="C")
            cvar+='"'+v+'"'

        elseif(type=="N")
            cvar+=alltrim(str(v))

        elseif(type=="D")
            cvar+=dtoc(v)

        elseif(type=="L") 
            cvar+=if(v,".T.",".F.")

        elseif(type=="A")
            cvar+=_arr2str(v)

        else 
            cvar+="[Type-"+type+"]"

        end
    next    

    return cvar+"}"


*************************************************************************
function _any2str(value) // megjelenítéshez
local type:=valtype(value)

    if(type=="C")

    elseif(type=="N")
        value:=str(value)

    elseif(type=="D")
        value:=dtoc(value)

    elseif(type=="L")
        value:=if(value,".T.",".F.")

    elseif(type=="A")
        value:=_arr2str(value)

    elseif(type=="U")
        value:="NIL"

    else
        value:="Type-"+type
    end
    
    return value


*************************************************************************
