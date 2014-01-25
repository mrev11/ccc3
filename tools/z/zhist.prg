
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

//a historyból választott filére indítja z-t

#include "box.ch"
#include "spawn.ch"


**********************************************************************   
function main()

local hist,choice:={},n
local screen,t:=0,l:=0,b:=maxrow()-0,r:=maxcol()-0

    hist:=zhome()+"history_uc.z"
    hist::=memoread(.t.)
    hist::=bin2arr

    for n:=1 to len(hist)
        if( file(hist[n][1]) )
            choice::aadd(hist[n][1])
        end
    next

    screen:=drawBox(t,l,b,r,B_SINGLE)
    n:=achoice(t+1,l+1,b-1,r-1,choice,,,1)
    while( n>0 )

        sleep(100)  //terminál frissítés (kurzor!)
        
        //MEGJEGYZÉS:
        //a program 2 szálon fut
        // 1) ez az egyik
        // 2) a terminál frissítés a másik
        //az első szálban (itt) elindítunk egy childot ugyanabban a terminálban
        //ilyenkor a másik szál is leáll és vár a child befejeződésére
        // -> az achoice-ban levő kurzorvisszaállítás is vár -> z-nek nincs kurzora
        //várni kell egy kicsit, hogy terminálfrissítés megtörténjen

        //run("z.exe "+choice[n] )
        spawn(SPAWN_WAIT+SPAWN_PATH,"z.exe",choice[n])

        drawBox(t,l,b,r,B_SINGLE)
        n:=achoice(t+1,l+1,b-1,r-1,choice,,,n)
    end
    restscreen(t,l,b,r,screen)


**********************************************************************   
static function fpath(fspec) //d:\path\ v. d:
local spos:=rat(dirsep(),fspec)
local cpos:=rat(":",fspec)
    return left(fspec,max(spos,cpos))


**********************************************************************   
static function zhome()
static home

    if( home==NIL )

        #ifdef _UNIX_
        home:=getenv("HOME")+"/.z/"  
        #else
        home:=fpath(exename()) 
        #endif
    
        if( !empty(getenv("ZHOME")) )
            home:=getenv("ZHOME")
        end

        if( !right(home,1)==dirsep() )
            home+=dirsep()
        end
    end
    
    return home
    

**********************************************************************   
