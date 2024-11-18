
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

#include "table.ch"


******************************************************************************************
function main()
local proba:=tabobj.probaNew()
local n,x
local cnt:=0

    set dosconv fileshare

    set printer to ("log-write-"+getpid()::str::alltrim)
    set printer on

    proba:create
    proba:open(OPEN_SHARED)

    rand(seconds())

    while(.t.)
        proba:gotop
        while( !proba:eof )
            proba:rlock
                proba:dbmchr:=""
                proba:dbmbin:=a""
                proba:length:=len(proba:dbmchr)
            proba:unlock
            proba:skip
        end
    
        proba:gotop
        while( !proba:eof )
            proba:rlock
                x:=proba:proba::left(1)
                x::=replicate(random()%1000)
                proba:dbmchr:="<"+x+">"
                proba:dbmbin:=proba:dbmchr::upper
                proba:length:=len(proba:dbmchr)
            proba:unlock
            proba:skip
        end
        
        ? ++cnt
        run( "pgstat.exe proba.bt" )
        
        if( 27==inkey(0.1) )
            exit
        end
    end
    
    proba:close

    ?     
    
******************************************************************************************
