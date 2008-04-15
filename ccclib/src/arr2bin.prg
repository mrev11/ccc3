
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


******************************************************************************
function arr2bin(avar)

local bvar:=a""
local n,v,lv,type
local err

    for n:=1 to len(avar)
        v:=avar[n]

        if( (type:=valtype(v))=="U" )         // 'U'
            bvar+=a"U"

        elseif(type=="X")                     // 'X999999value'
            lv:=len(v)
            bvar+=a"X"+str2bin(str(lv,6,0))+v

        elseif(type=="C")                     // 'C99value' vagy 'S99999value'
            v:=str2bin(v)
            lv:=len(v)
            if( lv<100 )
                bvar+=a"C"+str2bin(str(lv,2,0))+v
            else
                bvar+=a"S"+str2bin(str(lv,5,0))+v
            end

        elseif(type=="N")                     // 'N99value'
            v:=str2bin(alltrim(str(v)))
            bvar+=a"N"+str2bin(str(len(v),2,0))+v

        elseif(type=="D")                     // 'Dyyyymmdd'
            bvar+=a"D"+str2bin(dtos(v))

        elseif(type=="L")                     // 'LT' vagy 'LF'
            bvar+=a"L"+if(v,a"T",a"F")

        elseif(type=="A")                     // 'A99999value'
            v:=arr2bin(v)
            bvar+=a"A"+str2bin(str(len(v),5,0))+v

        else 
            bvar+=a"U"
        end
    next    

    return bvar
    
******************************************************************************
function bin2arr(bvar)

local avar:={}
local c:=1,type,v,lv

    while( c<=len(bvar) )
        type:=substr(bvar,c,1); c+=1

        if( type==a"U" )                      // 'U'
            aadd(avar,NIL)

        elseif( type==a"X" )                  // 'X999999value' 
            lv:=val(substr(bvar,c,6)); c+=6
            v:=substr(bvar,c,lv); c+=lv
            aadd(avar,v)

        elseif( type==a"C" )                  // 'C99value' 
            lv:=val(substr(bvar,c,2)); c+=2
            v:=substr(bvar,c,lv); c+=lv
            aadd(avar,bin2str(v))

        elseif( type==a"S" )                  // 'S99999value'
            lv:=val(substr(bvar,c,5)); c+=5
            v:=substr(bvar,c,lv); c+=lv
            aadd(avar,bin2str(v))

        elseif( type==a"N" )                  // 'N99value'
            lv:=val(substr(bvar,c,2)); c+=2
            v:=substr(bvar,c,lv); c+=lv
            aadd(avar,val(v))

        elseif( type==a"D" )                  // 'Dyyyymmdd'
            v:=substr(bvar,c,8); c+=8
            aadd(avar,stod(v))

        elseif( type==a"L" )                  // 'LT' vagy 'LF'
            v:=substr(bvar,c,1); c+=1
            aadd(avar, v==a"T")

        elseif( type==a"A" )                  // 'A99999value'
            lv:=val(substr(bvar,c,5)); c+=5
            v:=substr(bvar,c,lv); c+=lv
            aadd(avar,bin2arr(v))
         end
    end
    return avar


******************************************************************************
function arr2str(avar) // megjelenítéshez

local cvar:="{",n,v,type

    for n:=1 to len(avar)
        if( n>1 )
            cvar+=","
        end

        v:=avar[n]
        type:=valtype(v)

        if( type=="U" )     
            cvar+="NIL"

        elseif(type=="X")
            cvar+='a"'+bin2str(v)+'"'

        elseif(type=="C")
            cvar+='"'+v+'"'

        elseif(type=="N")
            cvar+=alltrim(str(v))

        elseif(type=="D")
            cvar+=dtoc(v)

        elseif(type=="L") 
            cvar+=if(v,".T.",".F.")

        elseif(type=="A")
            cvar+=arr2str(v)

        else 
            cvar+="[Type-"+type+"]"

        end
    next    

    return cvar+"}"


******************************************************************************
function any2str(value) // megjelenítéshez
local type:=valtype(value)

    if(type=="C")

    elseif(type=="X")
        value:=bin2str(value)

    elseif(type=="N")
        value:=str(value)

    elseif(type=="D")
        value:=dtoc(value)

    elseif(type=="L")
        value:=if(value,".T.",".F.")

    elseif(type=="A")
        value:=arr2str(value)

    elseif(type=="P")
        value:=l2hex(value)

    elseif(type=="U")
        value:="NIL"

    else
        value:="Type-"+type
    end
    
    return value


******************************************************************************
