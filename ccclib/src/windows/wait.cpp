
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

#include <stdio.h>
#include <process.h>
#include <cccapi.h>

//MSVC-ben és MinGW-ben a spawn által visszaadott pid egyben
//WINDOWS HANDLE, amire várni lehet WaitForSingleObject-tel,
//pl. thread_mutex_lock( spawn(.f.,"program.exe") ) vár.
//
//Borland-ban a pid NEM HANDLE, azért a fenti várakozás nem megy.
//Borlandban implementálva van a tesztőleges childra váró wait,
//ami MSVC-ből és MinGW-ből hiányzik. Ezek pid=0-val sem tudnak várni.
//
//Windowson nincs implementálva a WNOHANG funkció, ami nem vár,
//csak jelzi, hogy kilépett-e már a child (és takarítja a zombikat).
//
//Windowson waitpid() harmadik paramétere nincs használatban.

//--------------------------------------------------------------------------
void _clp_wait(int argno)  

// Csak Borland-dal működik
//
// wait()          vár, míg egy child kilép
// wait(@status)   vár, míg egy child kilép + plusz exit infó

{
    CCC_PROLOG("wait",1);
    int status = 0; //kimenet

    #ifdef BORLAND
        int result = wait(&status); //OK, jó cwait(&status,0,0) is
    #endif
    #ifdef MSVC
        int result = _cwait(&status,0,0); //rossz, wait nincs
    #endif
    #ifdef MINGW
        int result = _cwait(&status,0,0); //rossz, wait nincs 
    #endif
    
    number(status);
    assign(PARPTR(1));
    _retni( result ) ;
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_waitpid(int argno)  

// waitpid(pid)             vár, míg pid kilép
// waitpid(pid,@status,0)   vár, míg pid kilép + plusz exit infó 
 
{
    CCC_PROLOG("waitpid",3);
    int pid    = ISNUMBER(1)?_parni(1):0;
    int status = 0; //kimenet
    int mode   = ISNUMBER(3)?_parni(3):0;

    #ifdef BORLAND
        int result = cwait(&status,pid,mode);
    #endif
    #ifdef MSVC
        int result = _cwait(&status,pid,mode);
    #endif
    #ifdef MINGW
        int result = _cwait(&status,pid,mode);
    #endif
    
    //a harmadik (mode) paraméter hatástalan
    //Windowson mindig vár (nincs WNOHANG mód)

    number(status);
    assign(PARPTR(2));
    _retni( result ) ;
    CCC_EPILOG();
}
 
//--------------------------------------------------------------------------

 