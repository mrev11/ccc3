
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

//a filéneveket (rekurzívan) kisbetűre konvertálja
//a Linuxos frename rosszul működik NT share-eken

#include "directry.ch"

 
static s_rek    // -r rekurzívan 
static s_dir    // -d directoryneveket is
static s_pat    // -p csak az illeszkedő nevűeket (like)

*****************************************************************************
function main()

local arg:=argv(), n

    #ifdef _UNIX_
      //UNIX-on óvatos
      s_rek:=.f.
      s_dir:=.f.
      s_pat:=NIL
    #else
      s_rek:=.t.
      s_dir:=.t.
      s_pat:="*"
    #endif

    set dosconv off
    
    for n:=1 to len(arg)

        if( arg[n]=="-d" )
            s_dir:=.t.

        elseif( arg[n]=="-r" )
            s_rek:=.t.

        elseif( left(arg[n],2)=="-p" )
            s_pat:=substr(arg[n],3)

        else
            usage()
        end        
    next
    
    if( s_pat==NIL  )
        usage()
    end

    doproc()
    ?
    return NIL


*****************************************************************************
static function usage()
    ? "Usage: lower [-d] [-r] -p<pattern>"
    ?
    quit
    return NIL
 

*****************************************************************************
static function doproc()    

static indent:=0
local name,n,d,d1:={}

    d:=directory(fullmask(),"D-LH")
    
    for n:=1 to len(d)

        name:=d[n][F_NAME]

        if( "D"$d[n][F_ATTR] )
 
            if( !name=="." .and.;
                !name==".." .and.; 
                !"L"$d[n][F_ATTR] )

                aadd(d1,name)
            end

        elseif( !name==lower(name) )
            flower(name)
        end
    next
    
    d:=NIL
    
    
    for n:=1 to len(d1)

        name:=d1[n] 

        if( s_rek==.t. )
            if( 0<=dirchange(name) )
                ? space(indent)+name
                indent+=4
                doproc()
                dirchange("..")
                indent-=4
            else
                ? "DIRCHANGE ERROR: ["+name+"]",ferror(), curdir()
            end
        end

        if( s_dir==.t. .and. !name==lower(name)  )
            flower(name)
        end
        
        //Azért van dirchange-dzsel megírva rekurzió, 
        //mert frename csak a lokális directory subdirectoryait 
        //tudja átnevezni (miért?).
        //Nem lehet átnevezni olyan directoryt sem, ami aktuális
        //valamely más taskban.
    next
    
    return NIL

*****************************************************************************
static function flower(f) //workaround frename Linuxos hibájára
local s
    
    if( s_pat==NIL .or. like(s_pat,f) )

        //alert(f)
    
        #ifdef _UNIX_  
            frename(f,f+"~")
            s:=frename(f+"~",lower(f))
        #else
            s:=frename(f,lower(f))
        #endif
    
        if( s!=0 )
            ? "FRENAME ERROR: "+f
        end
    end

    return NIL

*****************************************************************************
 