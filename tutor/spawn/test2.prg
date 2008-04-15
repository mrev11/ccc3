
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

//Windows/UNIX spawn, pipe example-2

#include "spawn.ch"

******************************************************************************
function main()

    if( argc()<=1 )
        parent()
    else
        child()
    end
    ?
    return NIL


******************************************************************************
static function parent()  //ír a pipe-ba

local n:=0
local pp:=pipe(),pr,pw
local env:={},c 

    pr:=pp[1] 
    pw:=fdup(pp[2],.f.);  fclose(pp[2]) 

    //Most pw nem öröklődik, 
    //ezért a childnak nem kell foglalkozni a lezárásával.

    aadd(env,"PATH="+getenv("PATH"))
    aadd(env,"LD_LIBRARY_PATH="+getenv("LD_LIBRARY_PATH"))
    aadd(env,"proba=szerencse")
    aadd(env,"vanaki=forrón szereti")
    
    //Figyelem:
    //UNIX-on nem működik egyszerre SPAWN_PATH és a környezet átadása, 
    //(nincs execvpe). Úgy működik, mintha SPAWN_PATH nem volna megadva.

    spawn(SPAWN_NOWAIT+SPAWN_PATH,"test2.exe",str(pr),env)
    
    fclose(pr)

    while( ++n<=3 )
        c:=chr(asc("a")+n-1) 
        ? "parent:",c, fwrite(pw,c)  
        sleep(1000)
    end

    fclose(pw)

    return NIL
 
 
******************************************************************************
static function child() //olvas a pipe-ból

local pr:=val(argv(1))
local buf:=replicate(a" ",32),nbyte

    ?
    run("set")

    ? "child :", getenv("proba")
    ? "child :", getenv("vanaki")
    ? "child :", getenv("PATH")

    while( 0<(nbyte:=fread(pr,@buf,len(buf)))     )
        ? "child :", upper(left(buf,nbyte))
    end
    
    fclose(pr)

    return NIL
 

******************************************************************************
 
    