
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


#define LOWER(x) (x)

****************************************************************************
function procpar(par)
local n,p

    while( 0<(n:=at("$$(",par)) )        // ...$$(...)...
        p:=left(par,n-1)
        par:=substr(par,n+3)
        n:=at(")",par)
        p+=left(par,n-1)+"/$(BUILD_OBJ)/"+left(par,n-1)
        p+=substr(par,n+1)
        par:=p
    end

    while( 0<(n:=at("$(",par)) )         // ...$(...)...
        p:=left(par,n-1)
        par:=substr(par,n+2)
        n:=at(")",par)
        p+=getenv(left(par,n-1)) 
        p+=substr(par,n+1)
        par:=p
    end


    while( 0<(n:=at("$${",par)) )        // ...$${...}...
        p:=left(par,n-1)
        par:=substr(par,n+3)
        n:=at("}",par)
        p+=left(par,n-1)+"/$(BUILD_OBJ)/"+left(par,n-1)
        p+=substr(par,n+1)
        par:=p
    end

    while( 0<(n:=at("${",par)) )         // ...${...}...
        p:=left(par,n-1)
        par:=substr(par,n+2)
        n:=at("}",par)
        p+=getenv(left(par,n-1)) 
        p+=substr(par,n+1)
        par:=p
    end
 
    par:=strtran(par,"\",dirsep())
    par:=strtran(par,"/",dirsep())
    
    return if(left(par,1)=="=",LOWER(par),par)

****************************************************************************
