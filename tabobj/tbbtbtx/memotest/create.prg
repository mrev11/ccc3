
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
local n, a:="a",x

    set dosconv fileshare

    proba:create
    proba:open(OPEN_EXCLUSIVE)
    proba:zap

    rand(seconds())
    
    for n:=0 to 999
        proba:append
        x:=chr(asc(a)+n%26)
        proba:proba:=x
        x::=replicate(random()%500)
        proba:dbmchr:="<"+x+">"
        proba:dbmbin:=upper(proba:dbmchr)
        proba:length:=len(proba:dbmchr)
    next


    prn(proba)

    proba:close

    ?     
    
******************************************************************************************
static function prn(proba)
    proba:gotop
    while(!proba:eof)
        ? proba:proba, proba:length,  proba:dbmchr , proba:dbmbin
        proba:skip
    end


******************************************************************************************
