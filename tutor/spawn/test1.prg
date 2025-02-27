
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

//Windows/UNIX spawn, pipe example-1

#include "spawn.ch"

******************************************************************************
function main()
   
    if( argc()<=1 )
        parent()
    else
        child()
    end
    ?


******************************************************************************
static function parent()  //ír a pipe-ba

local n:=0
local pp:=pipe()
local pr:=pp[1]
local pw:=pp[2]
local env:={},c 

    //Ha beállítjuk a child környezetét, akkor be kell
    //állítani LD_LIBRARY_PATH-t is, máskülönben a child
    //nem találja meg az so-kat.

    aadd(env,"PATH="+getenv("PATH"))
    aadd(env,"LD_LIBRARY_PATH="+getenv("LD_LIBRARY_PATH"))
    aadd(env,"proba=szerencse")
    aadd(env,"vanaki=forrón szereti")
    
    //át kell adni pr-t és pw-t is,
    //pw-t csak azért, hogy a child lezárhassa,
    //máskülönben pr olvasása vég nélkül vár

    spawn(SPAWN_NOWAIT, {"test1.exe", str(pr), str(pw)}, env )
    
    fclose(pr)

    while( ++n<=26 )
        c:=chr(asc("a")+n-1) 
        ? "parent:",c
        fwrite(pw,c)  
        sleep(200)
    end

    fclose(pw)

 
******************************************************************************
static function child() //olvas a pipe-ból

local pr:=val(argv(1))
local pw:=val(argv(2))
local buf:=replicate(a" ",32),nbyte

    fclose(pw)

    while( 0<(nbyte:=fread(pr,@buf,len(buf)))     )
        ?? "  child:", upper(left(buf,nbyte))
    end

    ?
    ? "CHILD proba :", getenv("proba")
    ? "CHILD vanaki:", getenv("vanaki")
    ? "CHILD PATH  :", getenv("PATH")
    
    fclose(pr)
    ?

******************************************************************************
 
    