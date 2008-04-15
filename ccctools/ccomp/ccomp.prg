
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

#include "spawn.ch"

// Végrehajt egy 
//
//  cmd arg1 @arg2 arg3 ... 
//
// alakú parancsot. Ha egy paraméter első karaktere @, 
// akkor az egy response filét jelöl, aminek tartalmát szavakra 
// vágva beilleszti a többi paraméter közé. A MinGW eszközökhöz 
// kell, amik nem  tudják parametereiket scriptből felszedni, 
// ráadásul a Windows parancssor hossza korlátozott.

******************************************************************************
function main()

local cmd:={},n:=0,arg,i

    // Rugalmasabb, de ez sem tud hosszú parancsokat kezelni.
    //
    // Batch filéknek átadott paraméterek összhossza 4K lehet.
    // A 4K-nál hosszabb batch parancsok így szállnak el:
    //  The following character string is too long: ...
    //
    // Ha exe programot indítunk spawn-nal, akkor a paraméterek 
    // összhossza kb. 32K lehet. CCC programok esetében az átvehető
    // paraméterek számát korlátozza a CCC stack mérete (2048 db).

    while( !empty(arg:=argv(++n)) )

        if( left(arg,1)=="@" )  
            arg:=memoread(substr(arg,2))
            arg:=strtran(arg,chr(13),"")
            arg:=strtran(arg,chr(10)," ")
            arg:=split(arg," ")
            for i:=1 to len(arg)
                if( !empty(arg[i]) )
                    aadd(cmd,arg[i])
                end
            next
        else
            aadd(cmd,arg)
        end
    end
    errorlevel(spawn(SPAWN_WAIT+SPAWN_PATH,cmd))
    return NIL


******************************************************************************
#ifdef REGEBBI_VALTOZAT

//Korábban a parancsot egy stringben raktuk össze,
//a Windows parancssor hossza azonban korlátozott.
 
function main()
local cmd:="",n:=0,arg

    while( !empty(arg:=argv(++n)) )

        if( left(arg,1)=="@" )  
            arg:=memoread(substr(arg,2))
            arg:=strtran(arg,chr(13),"")
            arg:=strtran(arg,chr(10)," ")
        end
        cmd+=" "+arg
    end
    errorlevel( run(cmd) )
    return NIL

#endif


******************************************************************************
 
 