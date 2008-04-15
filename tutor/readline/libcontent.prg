
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

//Globális Clipper függvények listázása.
//Demonstráció: readline, thread, pipe.

*****************************************************************************
function main(library_fspec)
local pipe:=pipe()
local th:=thread_create({||list(pipe[1])})
    run( "nm "+library_fspec+">&"+alltrim(str(pipe[2])) )
    fclose(pipe[2])
    thread_join(th)
    fclose(pipe[1])
    return NIL

*****************************************************************************
static function list(fd)
local input,line,pos
    input:=readlineNew(fd)
    while( NIL!=(line:=input:readline) )
        if( a":"$line )
            ? line
        elseif( a" T "$line .and. a"_clp_"$line )
            //?? "    ",line
            ?? "    ",getname(line);?
        end
    end
    ?
    return NIL

*****************************************************************************
static function getname(line)

// 00000000000001c0 T _ZN9_nsp_test11_nsp_vanaki11_nsp_forron8_clp_funEi
// 0000000000000000 T _Z19_clp_probaszerencsei

local t:=at(a"T",line)
local len,wlen,tag
local name:=a""

    line:=substr(line,t+2)
    line:=strtran(line,a"_ZN",a"")
    line:=strtran(line,a"_Z",a"")
    
    while( (len:=val(line))>0 )
        wlen:=len(alltrim(str(len)))
        tag:=substr(line,wlen+1,len) //_clp_name
        line:=substr(line,wlen+len+1)
        name+=a"."+substr(tag,6)
    end
    return substr(name,2)

*****************************************************************************
