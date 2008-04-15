
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

#include "directry.ch"

static s_cmd
static s_skip


*****************************************************************************
function main()

local arg:=argv(), n

    set dosconv off
    
    for n:=1 to len(arg)
        if( left(arg[n],2)=="-c" )
            s_cmd:=substr(arg[n],3) 

        elseif( left(arg[n],2)=="-s" ) 
            s_skip:=substr(arg[n],3) 
            
        else //compatibility
            s_cmd:=arg[n]
 
        end
    next

    doproc()
    ?
    return NIL

*****************************************************************************
static function doproc()    

local name,n,d,d1:={}

    //alert(curdir())

    if( empty(s_cmd) )
        ? curdir()
    else
        run(s_cmd)
    end

    d:=directory(fullmask(),"D")
    
    for n:=1 to len(d)
        name:=alltrim(d[n][F_NAME])

        if( "D"$d[n][F_ATTR] .and.;
            !"L"$d[n][F_ATTR] .and. !name=="." .and.!name==".." )

            if( empty(s_skip) .or. !upper(name)$upper(s_skip) )
                aadd(d1,name)
            end
        end
    next
   
    d:=NIL
    
    for n:=1 to len(d1)
        name:=d1[n] 
        if( 0<=dirchange(name) )
             doproc()
             dirchange("..")
        end
    next
    
    return NIL

*****************************************************************************
